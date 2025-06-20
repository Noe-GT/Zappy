/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Engine.cpp - Version modifiée avec éclairage Phong
*/
#include "Engine.hpp"
#include "Cache.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <set>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Engine::Engine(): _shadowProgram(0), _vertexShader(0), _fragmentShader(0), _shadering(false)
{
    this->_renderBatches.reserve(10000);
}


Engine::~Engine()
{
    clearObjects();
    glDeleteProgram(_shadowProgram);
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
}

void Engine::initialize()
{
    static bool glewInitialized = false;
    if (!glewInitialized) {
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
            exit (84);
        glewInitialized = true;
    }
    loadShaders();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return;
}

void Engine::addObj(const std::string& objPath, const std::string& mtlPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    std::string cacheKey = objPath + "|" + mtlPath;
    std::shared_ptr<Cache> cache = _modelCache[cacheKey];

    if (!cache) {
        cache = std::make_shared<Cache>(objPath, mtlPath);
        loadMTL(*cache);
        loadOBJ(*cache);
        cache->generateBuffers();
        _modelCache[cacheKey] = cache;
    }

    InstanceData instance;
    instance.transform = Transform(position, rotation, scale);
    instance.materialIndex = 0;
    cache->instances.push_back(instance);
    return;
}

void Engine::loadShaders()
{
    this->_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->_vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(this->_vertexShader);

    this->_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->_fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(this->_fragmentShader);

    this->_shadowProgram = glCreateProgram();
    glAttachShader(this->_shadowProgram, this->_vertexShader);
    glAttachShader(this->_shadowProgram, this->_fragmentShader);
    glLinkProgram(this->_shadowProgram);

    this->_modelLocation = glGetUniformLocation(this->_shadowProgram, "model");
    this->_viewLocation = glGetUniformLocation(this->_shadowProgram, "view");
    this->_projectionLocation = glGetUniformLocation(this->_shadowProgram, "projection");
    this->_colorLocation = glGetUniformLocation(this->_shadowProgram, "color");
    this->_hasTextureLocation = glGetUniformLocation(this->_shadowProgram, "hasTexture");
    this->_textureLocation = glGetUniformLocation(this->_shadowProgram, "ourTexture");
    this->_lightPosLocation = glGetUniformLocation(this->_shadowProgram, "lightPos");
    this->_viewPosLocation = glGetUniformLocation(this->_shadowProgram, "viewPos");
    this->_ambientLocation = glGetUniformLocation(this->_shadowProgram, "material.ambient");
    this->_diffuseLocation = glGetUniformLocation(this->_shadowProgram, "material.diffuse");
    this->_specularLocation = glGetUniformLocation(this->_shadowProgram, "material.specular");
    this->_shininessLocation = glGetUniformLocation(this->_shadowProgram, "material.shininess");

    this->_simpleVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->_simpleVertexShader, 1, &simpleVertexShaderSource, NULL);
    glCompileShader(this->_simpleVertexShader);

    this->_simpleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->_simpleFragmentShader, 1, &simpleFragmentShaderSource, NULL);
    glCompileShader(this->_simpleFragmentShader);

    this->_simpleShaderProgram = glCreateProgram();
    glAttachShader(this->_simpleShaderProgram, this->_simpleVertexShader);
    glAttachShader(this->_simpleShaderProgram, this->_simpleFragmentShader);
    glLinkProgram(this->_simpleShaderProgram);

    this->_simpleModelLocation = glGetUniformLocation(this->_simpleShaderProgram, "model");
    this->_simpleViewLocation = glGetUniformLocation(this->_simpleShaderProgram, "view");
    this->_simpleProjectionLocation = glGetUniformLocation(this->_simpleShaderProgram, "projection");
    this->_simpleColorLocation = glGetUniformLocation(this->_simpleShaderProgram, "color");
    this->_simpleHasTextureLocation = glGetUniformLocation(this->_simpleShaderProgram, "hasTexture");
    this->_simpleTextureLocation = glGetUniformLocation(this->_simpleShaderProgram, "ourTexture");
    return;
}

void Engine::loadOBJ(Cache& model)
{
    std::ifstream file(model.objPath);
    int currentMaterial = -1;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << model.objPath << std::endl;
        return;
    }
    model.model.vertices.reserve(1000);
    model.model.texCoords.reserve(1000);
    model.model.normals.reserve(1000);
    model.model.faces.reserve(1000);

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            model.model.vertices.push_back(glm::vec3(x, y, z));
        }
        else if (type == "vt") {
            float u, v;
            iss >> u >> v;
            model.model.texCoords.push_back(glm::vec2(u, 1.0f - v));
        }
        else if (type == "vn") {
            float x, y, z;
            iss >> x >> y >> z;
            model.model.normals.push_back(glm::vec3(x, y, z));
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
            std::vector<int> normIndices;
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
                if (vnIdx > 0)
                    normIndices.push_back(vnIdx - 1);
            }
            if (face.size() >= 3) {
                model.model.faces.push_back(face);
                model.model.texIndices.push_back(texIndices);
                model.model.normalIndices.push_back(normIndices);
                model.model.materialIndices.push_back(currentMaterial);
            }
        }
    }
}

void Engine::loadMTL(Cache& model)
{
    std::ifstream file(model.mtlPath);
    std::string line;
    Material* currentMaterial = nullptr;
    if (!file.is_open()) {
        Material defaultMat;
        defaultMat.name = "default";
        model.materials.push_back(defaultMat);
        return;
    }
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
                currentMaterial->ambient = glm::vec4(r, g, b, 1.0f);
            }
            else if (type == "Kd") {
                float r, g, b;
                iss >> r >> g >> b;
                currentMaterial->diffuse = glm::vec4(r, g, b, 1.0f);
            }
            else if (type == "Ks") {
                float r, g, b;
                iss >> r >> g >> b;
                currentMaterial->specular = glm::vec4(r, g, b, 1.0f);
            }
            else if (type == "Ns") {
                iss >> currentMaterial->shininess;
            }
            else if (type == "map_Kd") {
                std::string texPath;
                iss >> texPath;

                size_t lastSlash = model.mtlPath.find_last_of("/\\");
                std::string fullPath = (lastSlash != std::string::npos) ?
                    model.mtlPath.substr(0, lastSlash + 1) + texPath : texPath;
                glGenTextures(1, &currentMaterial->textureID);
                glBindTexture(GL_TEXTURE_2D, currentMaterial->textureID);
                stbi_set_flip_vertically_on_load(true);
                int width, height, nrChannels;
                unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
                if (data) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    currentMaterial->hasTexture = true;
                    currentMaterial->texturePath = fullPath;
                    stbi_image_free(data);
                } else {
                    glDeleteTextures(1, &currentMaterial->textureID);
                    currentMaterial->textureID = 0;
                    currentMaterial->hasTexture = false;
                }
            }
        }
    }
    if (model.materials.empty()) {
        Material defaultMat;
        defaultMat.name = "default";
        model.materials.push_back(defaultMat);
    }
    return;
}

void Engine::update(const Camera& camera, float width, float height)
{
    this->_renderBatches.clear();
    this->_viewMatrix = camera.getViewMatrix();
    this->_projectionMatrix = glm::perspective(glm::radians(60.0f), width / height, 0.1f, 100.0f);

    for (auto& cache: _modelCache) {
        if (cache.second->instances.empty())
            continue;
        for (auto& instance : cache.second->instances) {
            glm::vec3 delta = instance.transform.position - camera.position;
            if (glm::dot(delta, delta) < 2000) {
                glm::vec3 toObject = glm::normalize(delta);
                glm::vec3 forward = camera.getFront();
                if (glm::dot(toObject, forward) > -0.5f) {
                    processInstance(*cache.second, instance);
                }
            }
        }
    }
    if (_renderBatches.size() > 1) {
        std::sort(_renderBatches.begin(), _renderBatches.end(),
            [](const RenderBatch& a, const RenderBatch& b) {
                return a.depth < b.depth;
            });
    }
}

void Engine::processInstance(const Cache& cache, const InstanceData& instance)
{
    if (!cache.model.buffersGenerated)
        return;

    glm::mat4 modelMatrix = instance.transform.getMatrix();
    glm::vec3 worldPos = glm::vec3(modelMatrix[3]);
    glm::vec3 viewPos = glm::vec3(_viewMatrix * glm::vec4(worldPos, 1.0f));
    float depth = -viewPos.z;
    const Model& model = cache.model;

    for (size_t i = 0; i < model.materialRanges.size(); ++i) {
        const auto& range = model.materialRanges[i];
        int materialIdx = model.materialForRange[i];
        RenderBatch batch;
        batch.material = &cache.materials[materialIdx < static_cast<int> (cache.materials.size()) ? materialIdx : 0];
        batch.VAO = model.VAO;
        batch.indexCount = range.second;
        batch.indexOffset = range.first * 4;
        batch.modelMatrix = modelMatrix;
        batch.depth = depth;
        batch.materialIndex = materialIdx;
        this->_renderBatches.push_back(batch);
    }
}

void Engine::draw(const Camera& camera)
{
    GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (_shadering) {
        glUseProgram(this->_shadowProgram);
        if (_viewLocation != -1)
            glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
        if (_projectionLocation != -1)
            glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
    } else {
        glUseProgram(this->_simpleShaderProgram);
        if (_simpleViewLocation != -1)
            glUniformMatrix4fv(_simpleViewLocation, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
        if (_simpleProjectionLocation != -1)
            glUniformMatrix4fv(_simpleProjectionLocation, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
    }
    if (_shadering) {
        if (_lightPosLocation != -1)
            glUniform3fv(_lightPosLocation, 1, glm::value_ptr(camera.position));
        if (_viewPosLocation != -1)
            glUniform3fv(_viewPosLocation, 1, glm::value_ptr(camera.position));
    }
    for (const auto& batch : _renderBatches) {
        if (batch.VAO == 0 || batch.indexCount == 0)
            continue;
        if (_shadering) {
            if (_modelLocation != -1)
                glUniformMatrix4fv(_modelLocation, 1, GL_FALSE, glm::value_ptr(batch.modelMatrix));
        } else {
            if (_simpleModelLocation != -1)
                glUniformMatrix4fv(_simpleModelLocation, 1, GL_FALSE, glm::value_ptr(batch.modelMatrix));
        }
        if (batch.material) {
            if (_shadering) {
                if (_ambientLocation != -1)
                    glUniform3fv(_ambientLocation, 1, glm::value_ptr(glm::vec3(batch.material->ambient)));
                if (_diffuseLocation != -1)
                    glUniform3fv(_diffuseLocation, 1, glm::value_ptr(glm::vec3(batch.material->diffuse)));
                if (_specularLocation != -1)
                    glUniform3fv(_specularLocation, 1, glm::value_ptr(glm::vec3(batch.material->specular)));
                if (_shininessLocation != -1)
                    glUniform1f(_shininessLocation, batch.material->shininess);
            } else {
                if (_simpleColorLocation != -1)
                    glUniform4fv(_simpleColorLocation, 1, glm::value_ptr(batch.material->diffuse));
            }
            if (batch.material->hasTexture && batch.material->textureID != 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, batch.material->textureID);
                if (_shadering) {
                    if (_hasTextureLocation != -1)
                        glUniform1i(_hasTextureLocation, 1);
                    if (_textureLocation != -1)
                        glUniform1i(_textureLocation, 0);
                } else {
                    if (_simpleHasTextureLocation != -1)
                        glUniform1i(_simpleHasTextureLocation, 1);
                    if (_simpleTextureLocation != -1)
                        glUniform1i(_simpleTextureLocation, 0);
                }
            } else {
                if (_shadering) {
                    if (_hasTextureLocation != -1)
                        glUniform1i(_hasTextureLocation, 0);
                } else {
                    if (_simpleHasTextureLocation != -1)
                        glUniform1i(_simpleHasTextureLocation, 0);
                }
            }
        } else {
            if (_shadering) {
                glm::vec3 defaultAmbient(0.2f, 0.2f, 0.2f);
                glm::vec3 defaultDiffuse(0.8f, 0.8f, 0.8f);
                glm::vec3 defaultSpecular(1.0f, 1.0f, 1.0f);
                float defaultShininess = 32.0f;
                if (_ambientLocation != -1)
                    glUniform3fv(_ambientLocation, 1, glm::value_ptr(defaultAmbient));
                if (_diffuseLocation != -1)
                    glUniform3fv(_diffuseLocation, 1, glm::value_ptr(defaultDiffuse));
                if (_specularLocation != -1)
                    glUniform3fv(_specularLocation, 1, glm::value_ptr(defaultSpecular));
                if (_shininessLocation != -1)
                    glUniform1f(_shininessLocation, defaultShininess);
            } else {
                glm::vec4 defaultColor(0.8f, 0.8f, 0.8f, 1.0f);
                if (_simpleColorLocation != -1)
                    glUniform4fv(_simpleColorLocation, 1, glm::value_ptr(defaultColor));
            }
            if (_shadering) {
                if (_hasTextureLocation != -1)
                    glUniform1i(_hasTextureLocation, 0);
            } else {
                if (_simpleHasTextureLocation != -1)
                    glUniform1i(_simpleHasTextureLocation, 0);
            }
        }
        glBindVertexArray(batch.VAO);
        glDrawElements(GL_TRIANGLES, batch.indexCount, GL_UNSIGNED_INT, (void*)batch.indexOffset);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(currentProgram);
}

glm::vec3 Engine::screenToWorld(int mouseX, int mouseY, float screenWidth, float screenHeight, const Camera& camera)
{
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;
    glm::vec4 rayClip(x, y, -1.0f, 1.0f);
    glm::vec4 rayEye = glm::inverse(_projectionMatrix) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
    glm::vec3 rayWorld = glm::vec3(glm::inverse(_viewMatrix) * rayEye);
    rayWorld = glm::normalize(rayWorld);
    glm::vec3 rayOrigin = camera.position;
    glm::vec3 rayDirection = rayWorld;
    float closestDistance = std::numeric_limits<float>::max();
    glm::vec3 closestPoint(-2, -2, -2);
    for (const auto& cacheEntry : _modelCache) {
        const std::shared_ptr<Cache>& cache = cacheEntry.second;
        for (const auto& instance : cache->instances) {
            glm::mat4 modelMatrix = instance.transform.getMatrix();
            for (size_t faceIdx = 0; faceIdx < cache->model.faces.size(); ++faceIdx) {
                const auto& face = cache->model.faces[faceIdx];
                if (face.size() < 3)
                    continue;
                for (size_t i = 1; i < face.size() - 1; ++i) {
                    glm::vec3 v0 = cache->model.vertices[face[0]];
                    glm::vec3 v1 = cache->model.vertices[face[i]];
                    glm::vec3 v2 = cache->model.vertices[face[i + 1]];
                    v0 = glm::vec3(modelMatrix * glm::vec4(v0, 1.0f));
                    v1 = glm::vec3(modelMatrix * glm::vec4(v1, 1.0f));
                    v2 = glm::vec3(modelMatrix * glm::vec4(v2, 1.0f));
                    glm::vec3 intersectionPoint;
                    float distance;
                    if (rayTriangleIntersect(rayOrigin, rayDirection, v0, v1, v2, intersectionPoint, distance)) {
                        if (distance < closestDistance && distance > 0.0f) {
                            closestDistance = distance;
                            closestPoint = intersectionPoint;
                        }
                    }
                }
            }
        }
    }

    return closestPoint;
}

bool Engine::rayTriangleIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, glm::vec3& intersectionPoint, float& distance)
{
    const float EPSILON = 0.0000001f;

    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 h = glm::cross(rayDir, edge2);
    float a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    float f = 1.0f / a;
    glm::vec3 s = rayOrigin - v0;
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return false;

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(rayDir, q);
    if (v < 0.0f || u + v > 1.0f)
        return false;

    float t = f * glm::dot(edge2, q);
    if (t > EPSILON) {
        distance = t;
        intersectionPoint = rayOrigin + rayDir * t;
        return true;
    }
    return false;
}

void Engine::clearObjects()
{
    _modelCache.clear();
    _renderBatches.clear();
}

size_t Engine::getObjectCount() const
{
    size_t count = 0;
    for (const auto& pair: _modelCache)
        count += pair.second->instances.size();
    return count;
}

std::unordered_map<std::string, std::shared_ptr<Cache>> &Engine::getCache()
{
    return _modelCache;
}

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool hasTexture;
uniform sampler2D ourTexture;

void main()
{
    vec3 ambient = 0.5 * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 litVec = normalize(lightPos - FragPos);
    float diff = max(dot(norm, litVec), 0.0);
    vec3 diffuse = diff * material.diffuse;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-litVec, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular;

    vec3 result = ambient + diffuse + specular;

    if (hasTexture) {
        vec4 texColor = texture(ourTexture, TexCoord);
        FragColor = vec4(result, 1.0) * texColor;
    } else {
        FragColor = vec4(result, 1.0);
    }
}
)";

const char* simpleVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";

const char* simpleFragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform vec4 color = vec4(0.8, 0.8, 0.8, 1.0);
uniform bool hasTexture = false;
uniform sampler2D ourTexture;
void main()
{
    if (hasTexture) {
        vec4 texColor = texture(ourTexture, TexCoord);
        FragColor = texColor * color;
    } else {
        FragColor = color;
    }
}
)";