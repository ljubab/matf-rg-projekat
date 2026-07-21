//
// Created by ljuba on 7/20/26.
//

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <../../engine/include/engine/resources/Shader.hpp>
#include <../../engine/libs/glm/glm/glm.hpp>

class DirectionalLight {
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void setDirection(glm::vec3 new_direction);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

    glm::vec3 getDirection() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;

    void apply(engine::resources::Shader * shader) const;
private:
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};



#endif //DIRECTIONALLIGHT_H
