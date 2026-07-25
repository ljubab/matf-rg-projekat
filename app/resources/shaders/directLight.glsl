//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.00));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}

//#shader fragment
#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D tex;
    float ambient;
    float diffuse;
    float specular;
    float shiness;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    bool enabled;
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform SpotLight spotLight;

vec3 calcDirLight() {
    vec3 texColor = texture(material.tex, TexCoords).rgb;

    //ambient
    vec3 ambient = dirLight.ambient * material.ambient * texColor;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * material.diffuse * diff * texColor;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
    vec3 specular = dirLight.specular * material.specular * spec;

    return ambient + diffuse + specular;
}

vec3 calcSpotLight() {
    vec3 texColor = texture(material.tex, TexCoords).rgb;

    //ambient
    vec3 ambient = spotLight.ambient * material.ambient * texColor;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * material.diffuse * diff * texColor;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
    vec3 specular = spotLight.specular * material.specular * spec;

    float distance = length(spotLight.position - FragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * distance * distance);

    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}

void main() {
    //    vec3 result = texture(material.tex, TexCoords).rgb;
    vec3 result = calcDirLight();

    if(spotLight.enabled) {
        result += calcSpotLight();
    }

    FragColor = vec4(result, 1.0);
}