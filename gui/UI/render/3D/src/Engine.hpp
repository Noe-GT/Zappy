/*
*** EPITECH PROJECT, 2024
*** zap
*** File description:
*** Engine.hpp
*/
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <SFML/OpenGL.hpp>
#include "Structs.hpp"
#include "Camera.hpp"

class Cache;

class Engine {
public:
    Engine();
    ~Engine();
    void initialize();
    void addObj(const std::string& objPath, const std::string& mtlPath, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
    void update(const Camera& camera, float width = 1920, float height = 1080);
    void draw(const Camera& camera);
    void clearObjects();
    size_t getObjectCount() const;
    std::unordered_map<std::string, std::shared_ptr<Cache>> &getCache();
    glm::vec3 screenToWorld(int mouseX, int mouseY, float screenWidth, float screenHeight, const Camera& camera);

    bool _shadering;

private:
    void loadOBJ(Cache& model);
    void loadMTL(Cache& model);
    void loadShaders();
    void processInstance(const Cache& cache, const InstanceData& instance);
    bool rayTriangleIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDir, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, glm::vec3& intersectionPoint, float& distance);
    void updateEmissiveLights(const Camera& camera);

    std::unordered_map<std::string, std::shared_ptr<Cache>> _modelCache;
    std::vector<RenderBatch> _renderBatches;

    GLuint _shadowProgram;
    GLuint _simpleShaderProgram;
    GLuint _vertexShader;
    GLuint _fragmentShader;
    GLuint _simpleVertexShader;
    GLuint _simpleFragmentShader;
    GLuint _emissiveLocation;
    GLint _mvpLocation;
    GLint _modelLocation;
    GLint _viewLocation;
    GLint _projectionLocation;
    GLint _colorLocation;
    GLint _hasTextureLocation;
    GLint _textureLocation;
    GLint _lightPosLocation;
    GLint _viewPosLocation;
    GLint _ambientLocation;
    GLint _diffuseLocation;
    GLint _specularLocation;
    GLint _shininessLocation;
    GLint _simpleModelLocation;
    GLint _simpleViewLocation;
    GLint _simpleProjectionLocation;
    GLint _simpleColorLocatio;
    GLint _simpleHasTextureLocation;
    GLint _simpleTextureLocation;
    GLint _simpleColorLocation;
    GLint _numEmissiveLightsLocation;
    GLint _emissiveLightPosLocation;
    GLint _emissiveLightColorLocation;
    GLint _mainLightPosLocation;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;

};

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;
extern const char* simpleVertexShaderSource;
extern const char* simpleFragmentShaderSource;
