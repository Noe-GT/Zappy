#include "Engine.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include "Cache.hpp"
Engine::Engine()
{
    trianglesToRender.reserve(10000);
}

Engine::~Engine()
{
    clearObjects();
}

bool Engine::addObj(const std::string& objPath, const std::string& mtlPath, sf::Vector3f position, sf::Vector3f rotation, sf::Vector3f scale)
{
    std::string cacheKey = objPath + "|" + mtlPath;
    auto cache = modelCache[cacheKey];
    if (!cache) {
        cache = std::make_shared<Cache>(objPath, mtlPath);
        if (!loadResources(*cache)) {
            std::cerr << "Failed to load resources for: " << objPath << std::endl;
            modelCache.erase(cacheKey);
            return false;
        }
        modelCache[cacheKey] = cache;
    }
    InstanceData instance;
    instance.transform = Transform(position, rotation, scale);
    instance.materialIndex = 0;
    cache->instances.push_back(instance);
    return true;
}

bool Engine::loadMTL(Cache& model)
{
    std::ifstream file(model.mtlPath);
    if (!file.is_open()) {
        Material defaultMat;
        defaultMat.name = "default";
        model.materials.push_back(defaultMat);
        return true;
    }
    std::string line;
    Material* currentMaterial = nullptr;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "newmtl") {
            Material mat;
            iss >> mat.name;
            model.materials.push_back(mat);
            currentMaterial = &model.materials.back();
        }
        else if (currentMaterial) {
            if (type == "Ka") {
                float r, g, b;
                iss >> r >> g >> b;
                currentMaterial->ambient = sf::Color(r * 255, g * 255, b * 255);
            }
            else if (type == "Kd") {
                float r, g, b;
                iss >> r >> g >> b;
                currentMaterial->diffuse = sf::Color(r * 255, g * 255, b * 255);
            }
            else if (type == "Ks") {
                float r, g, b;
                iss >> r >> g >> b;
                currentMaterial->specular = sf::Color(r * 255, g * 255, b * 255);
            }
            else if (type == "Ns")
                iss >> currentMaterial->shininess;
            else if (type == "map_Kd") {
                std::string texPath;
                iss >> texPath;
                size_t lastSlash = model.mtlPath.find_last_of("/\\");
                std::string fullPath = (lastSlash != std::string::npos) ?
                    model.mtlPath.substr(0, lastSlash + 1) + texPath : texPath;
                if (!currentMaterial->diffuseTexture.loadFromFile(fullPath))
                    std::cerr << "Failed to load texture: " << fullPath << std::endl;
                else
                    currentMaterial->hasTexture = true;
            }
        }
    }
    return true;
}

bool Engine::loadOBJ(Cache& model)
{
    std::ifstream file(model.objPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << model.objPath << std::endl;
        return false;
    }
    std::string line;
    int currentMaterial = -1;
    model.model.vertices.reserve(1000);
    model.model.texCoords.reserve(1000);
    model.model.faces.reserve(1000);
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') \
            continue;
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            model.model.vertices.push_back(sf::Vector3f(x, y, z));
        }
        else if (type == "vt") {
            float u, v;
            iss >> u >> v;
            model.model.texCoords.push_back(sf::Vector2f(u, 1.f - v));
        }
        else if (type == "usemtl") {
            std::string matName;
            iss >> matName;
            for (size_t i = 0; i < model.materials.size(); ++i) {
                if (model.materials[i].name == matName) {
                    currentMaterial = static_cast<int>(i);
                    break;
                }
            }
        }
        else if (type == "f") {
            std::vector<int> face;
            std::vector<int> texIndices;
            std::string token;
            while (iss >> token) {
                std::replace(token.begin(), token.end(), '/', ' ');
                std::istringstream viss(token);
                int vIdx = 0, vtIdx = 0, vnIdx = 0;
                viss >> vIdx >> vtIdx >> vnIdx;
                if (vIdx > 0)
                    face.push_back(vIdx - 1);
                if (vtIdx > 0)
                    texIndices.push_back(vtIdx - 1);
            }
            if (face.size() >= 3) {
                model.model.faces.push_back(face);
                model.model.texIndices.push_back(texIndices);
                model.model.materialIndices.push_back(currentMaterial);
            }
        }
    }
    return true;
}

bool Engine::loadResources(Cache& model)
{
    return loadMTL(model) && loadOBJ(model);
}

void Engine::update(const Camera& camera, float width, float height)
{
    auto start = std::chrono::high_resolution_clock::now();
    trianglesToRender.clear();
    const float maxRenderDistance = 50.0f;
    const float maxRenderDistanceSq = maxRenderDistance * maxRenderDistance;
    float cosYaw = std::cos(camera.yaw);
    float sinYaw = std::sin(camera.yaw);
    float cosPitch = std::cos(camera.pitch);
    float sinPitch = std::sin(camera.pitch);
    float fov = 60.0f * static_cast<float>(M_PI) / 180.0f;
    float aspectRatio = width / height;
    float tanHalfFov = std::tan(fov / 2.0f);
    for (auto& pair : modelCache) {
        auto& Cache = pair.second;
        if (Cache->instances.empty())
            continue;
        for (auto& instance : Cache->instances) {
            sf::Vector3f delta = instance.transform.position - camera.position;
            float distanceSq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
            if (distanceSq < maxRenderDistanceSq) {
                sf::Vector3f toObject = delta;
                float distance = std::sqrt(distanceSq);
                if (distance > 0.01f) {
                    toObject.x /= distance;
                    toObject.y /= distance;
                    toObject.z /= distance;
                }
                float camX = toObject.x * cosYaw + toObject.z * sinYaw;
                float camZ = -toObject.x * sinYaw + toObject.z * cosYaw;
                float camY = toObject.y * cosPitch - camZ * sinPitch;
                camZ = toObject.y * sinPitch + camZ * cosPitch;
                if (camZ > 0) {
                    float projX = camX / (camZ * tanHalfFov * aspectRatio);
                    float projY = camY / (camZ * tanHalfFov);
                    if (std::abs(projX) < 1.5f && std::abs(projY) < 1.5f)
                        processInstance(*Cache, instance, camera, width, height, cosYaw, sinYaw, cosPitch, sinPitch, tanHalfFov, aspectRatio);
                }
            }
        }
    }

    if (trianglesToRender.size() > 1) {
        std::sort(trianglesToRender.begin(), trianglesToRender.end(),
            [](const TriangleData& a, const TriangleData& b) {
                return a.depth > b.depth;
            });
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    static int frameCount = 0;
    frameCount++;
}

void Engine::processInstance(const Cache& Cache, const InstanceData& instance, const Camera& camera, float width, float height, float cosYaw, float sinYaw, float cosPitch, float sinPitch, float tanHalfFov, float aspectRatio)
{
    const Model& model = Cache.model;
    const Transform& transform = instance.transform;
    float cosX = std::cos(transform.rotation.x);
    float sinX = std::sin(transform.rotation.x);
    float cosY = std::cos(transform.rotation.y);
    float sinY = std::sin(transform.rotation.y);
    float cosZ = std::cos(transform.rotation.z);
    float sinZ = std::sin(transform.rotation.z);
    size_t faceStep = 1;
    //FIXME: do a good geometry simplification if needed here
    for (size_t i = 0; i < model.faces.size(); i += faceStep) {
        const auto& face = model.faces[i];
        if (face.size() < 3)
            continue;
        int materialIndex = (i < model.materialIndices.size()) ? model.materialIndices[i] : instance.materialIndex;
        const Material* material = (materialIndex >= 0 && materialIndex < static_cast<int>(Cache.materials.size())) ? &Cache.materials[materialIndex] : &Cache.materials[0];
        for (size_t j = 1; j < face.size() - 1; ++j) {
            TriangleData triData;
            triData.vertices.resize(3);
            triData.vertices.setPrimitiveType(sf::Triangles);
            triData.material = material;
            int indices[3] = {0, static_cast<int>(j), static_cast<int>(j + 1)};
            sf::Vector3f worldPos[3];
            float avgZ = 0;
            bool shouldSkip = false;
            for (int k = 0; k < 3; ++k) {
                sf::Vector3f localPos = model.vertices[face[indices[k]]];
                localPos.x *= transform.scale.x;
                localPos.y *= transform.scale.y;
                localPos.z *= transform.scale.z;
                float x = localPos.x, y = localPos.y, z = localPos.z;
                float y1 = y * cosX - z * sinX;
                float z1 = y * sinX + z * cosX;
                float x1 = x * cosY + z1 * sinY;
                z1 = -x * sinY + z1 * cosY;
                float x2 = x1 * cosZ - y1 * sinZ;
                float y2 = x1 * sinZ + y1 * cosZ;
                worldPos[k] = sf::Vector3f(x2 + transform.position.x, y2 + transform.position.y, z1 + transform.position.z );
                sf::Vector3f camSpacePos = worldPos[k] - camera.position;
                float camX = camSpacePos.x * cosYaw + camSpacePos.z * sinYaw;
                float camZ = -camSpacePos.x * sinYaw + camSpacePos.z * cosYaw;
                float camY = camSpacePos.y * cosPitch - camZ * sinPitch;
                camZ = camSpacePos.y * sinPitch + camZ * cosPitch;
                if (camZ <= 0.01f) {
                    shouldSkip = true;
                    break;
                }
                avgZ += camZ;
                float projX = camX / (camZ * tanHalfFov * aspectRatio);
                float projY = camY / (camZ * tanHalfFov);
                triData.vertices[k].position = sf::Vector2f((projX + 1.0f) * width * 0.5f, (1.0f - projY) * height * 0.5f);
                if (material->hasTexture && i < model.texIndices.size() &&
                    indices[k] < static_cast<int>(model.texIndices[i].size())) {
                    int texIdx = model.texIndices[i][indices[k]];
                    if (texIdx >= 0 && texIdx < static_cast<int>(model.texCoords.size())) {
                        const sf::Vector2f& texCoord = model.texCoords[texIdx];
                        triData.vertices[k].texCoords = sf::Vector2f(
                            texCoord.x * material->diffuseTexture.getSize().x,
                            texCoord.y * material->diffuseTexture.getSize().y
                        );
                    }
                }
                triData.vertices[k].color = material->diffuse;
            }
            if (shouldSkip)
                continue;
            sf::Vector3f edge1 = worldPos[1] - worldPos[0];
            sf::Vector3f edge2 = worldPos[2] - worldPos[0];
            sf::Vector3f normal(edge1.y * edge2.z - edge1.z * edge2.y, edge1.z * edge2.x - edge1.x * edge2.z, edge1.x * edge2.y - edge1.y * edge2.x);
            sf::Vector3f viewDir = worldPos[0] - camera.position;
            float dot = normal.x * viewDir.x + normal.y * viewDir.y + normal.z * viewDir.z;
            if (dot < 0) {
                triData.depth = avgZ / 3.0f;
                trianglesToRender.push_back(std::move(triData));
            }
        }
    }
}

void Engine::draw(sf::RenderWindow& window)
{
    for (auto& triData : trianglesToRender) {
        sf::RenderStates states;
        if (triData.material->hasTexture)
            states.texture = &triData.material->diffuseTexture;
        window.draw(triData.vertices, states);
    }
}

void Engine::clearObjects()
{
    modelCache.clear();
    trianglesToRender.clear();
}

size_t Engine::getObjectCount() const
{
    size_t count = 0;
    for (const auto& pair : modelCache)
        count += pair.second->instances.size();
    return count;
}

sf::Vector2f Engine::project(const sf::Vector3f& point, float width, float height, const Camera& camera) const
{
    sf::Vector3f translatedPoint = point - camera.position;
    float cosYaw = std::cos(camera.yaw);
    float sinYaw = std::sin(camera.yaw);
    float cosPitch = std::cos(camera.pitch);
    float sinPitch = std::sin(camera.pitch);
    float x = translatedPoint.x * cosYaw + translatedPoint.z * sinYaw;
    float z = -translatedPoint.x * sinYaw + translatedPoint.z * cosYaw;
    float y = translatedPoint.y * cosPitch - z * sinPitch;
    z = translatedPoint.y * sinPitch + z * cosPitch;
    if (z <= 0.01f)
        z = 0.01f;
    float fov = 60.0f * static_cast<float>(M_PI) / 180.0f;
    float aspectRatio = width / height;
    float tanHalfFov = std::tan(fov / 2.0f);
    float projX = x / (z * tanHalfFov * aspectRatio);
    float projY = y / (z * tanHalfFov);
    return sf::Vector2f((projX + 1.0f) * width * 0.5f, (1.0f - projY) * height * 0.5f );
}

sf::Vector3f Engine::crossProduct(const sf::Vector3f& a, const sf::Vector3f& b) const
{
    return sf::Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
