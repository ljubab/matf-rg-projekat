//
// Created by ljuba on 7/20/26.
//
#include "../include/DirectionalLight.h"

DirectionalLight::DirectionalLight()
    : direction(0.0f, 0.0f, 0.0f), ambient(glm::vec3(1.0f, 1.0f, 1.0f)), diffuse(glm::vec3(1.0f, 1.0f, 1.0f)),
    specular(glm::vec3(1.0f, 1.0f, 1.0f)) {}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular) {}

void DirectionalLight::setDirection(glm::vec3 new_direction) {
    direction = new_direction;
}

void DirectionalLight::setAmbient(glm::vec3 new_ambient) {
    ambient = new_ambient;
}

void DirectionalLight::setDiffuse(glm::vec3 new_diffuse) {
    diffuse = new_diffuse;
}

void DirectionalLight::setSpecular(glm::vec3 new_specular) {
    specular = new_specular;
}

glm::vec3 DirectionalLight::getDirection() const {
    return direction;
}

glm::vec3 DirectionalLight::getAmbient() const {
    return ambient;
}

glm::vec3 DirectionalLight::getDiffuse() const {
    return diffuse;
}

glm::vec3 DirectionalLight::getSpecular() const {
    return specular;
}

void DirectionalLight::apply(engine::resources::Shader* shader) const {
    shader->set_vec3("light.direction", direction);
    shader->set_vec3("light.ambient", ambient);
    shader->set_vec3("light.diffuse", diffuse);
    shader->set_vec3("light.specular", specular);
}