//
// Created by ljuba on 7/20/26.
//

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <../../engine/include/engine/resources/Shader.hpp>
#include <../../engine/libs/glm/glm/glm.hpp>

struct DirectionalLight {
    DirectionalLight();
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void apply(engine::resources::Shader *shader) const;

    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


#endif//DIRECTIONALLIGHT_H
