//
// Created by ljuba on 7/24/26.
//

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "glm/vec3.hpp"
#include <engine/resources/Shader.hpp>

struct SpotLight {
    SpotLight();
    SpotLight(bool enabled, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff,
              float constant, float linear, float quadratic,
              glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void toggle();
    void apply(engine::resources::Shader *shader) const;

    bool enabled;

    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif//SPOTLIGHT_H
