//
// Created by ljuba on 7/24/26.
//

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "glm/vec3.hpp"
#include <../../engine/include/engine/resources/Shader.hpp>

class SpotLight {
public:
    SpotLight();
    SpotLight(bool enabled, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff,
               float constant, float linear, float quadratic,
               glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);
    void setConstant(float constant);
    void setLinear(float linear);
    void setQuadratic(float quadratic);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);

    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    float getCutOff() const;
    float getOuterCutOff() const;
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;

    void toggle();
    void apply(engine::resources::Shader * shader) const;
private:
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

#endif //SPOTLIGHT_H
