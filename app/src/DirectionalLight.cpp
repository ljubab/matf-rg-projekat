//
// Created by ljuba on 7/20/26.
//
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
    : direction(0.0f, 0.0f, 0.0f)
    , ambient(glm::vec3(1.0f, 1.0f, 1.0f))
    , diffuse(glm::vec3(1.0f, 1.0f, 1.0f))
    , specular(glm::vec3(1.0f, 1.0f, 1.0f)) {}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : direction(direction)
    , ambient(ambient)
    , diffuse(diffuse)
    , specular(specular) {}

void DirectionalLight::apply(engine::resources::Shader *shader) const {
    shader->set_vec3("dirLight.direction", direction);
    shader->set_vec3("dirLight.ambient", ambient);
    shader->set_vec3("dirLight.diffuse", diffuse);
    shader->set_vec3("dirLight.specular", specular);
}