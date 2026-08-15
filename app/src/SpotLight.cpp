//
// Created by ljuba on 7/24/26.
//

#include "../include/SpotLight.h"

#include <glm/glm.hpp>

SpotLight::SpotLight()
    : enabled(false), position(glm::vec3(0.0f, 0.0f, 0.0f)), direction(glm::vec3(0.0f, -1.0f, 0.0f)),
    cutOff(glm::cos(glm::radians(12.5f))), outerCutOff(glm::cos(glm::radians(17.5f))),
    constant(1.0f), linear(0.09f), quadratic(0.032f),
    ambient(glm::vec3(0.0f)), diffuse(glm::vec3(0.8f)), specular(glm::vec3(1.0f)) {}

SpotLight::SpotLight(bool enabled, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff,
        float constant, float linear, float quadratic,
        glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : enabled(enabled), position(position), direction(glm::normalize(direction)),
    cutOff(cutOff), outerCutOff(outerCutOff),
    constant(constant), linear(linear), quadratic(quadratic),
    ambient(ambient), diffuse(diffuse), specular(specular) {}

void SpotLight::toggle() {
    enabled ^= 1;
}

void SpotLight::apply(engine::resources::Shader* shader) const {
    shader->set_bool("spotLight.enabled", enabled);
    shader->set_vec3("spotLight.position", position);
    shader->set_vec3("spotLight.direction", direction);

    shader->set_float("spotLight.cutOff", cutOff);
    shader->set_float("spotLight.outerCutOff", outerCutOff);

    shader->set_float("spotLight.constant", constant);
    shader->set_float("spotLight.linear", linear);
    shader->set_float("spotLight.quadratic", quadratic);

    shader->set_vec3("spotLight.ambient", ambient);
    shader->set_vec3("spotLight.diffuse", diffuse);
    shader->set_vec3("spotLight.specular", specular);
}
