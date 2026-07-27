#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform Spotlight spotlight;

void main()
{
    vec3 norm = normalize(Normal);

    // Directional Light
    // vec3 lightDir = normalize(-directionalLight.direction);
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  

    // float diff = max(dot(norm, lightDir), 0.0);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // vec3 ambient = directionalLight.ambient * texture(material.diffuse, TexCoords).rgb;
    // vec3 diffuse = directionalLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    // vec3 specular = directionalLight.specular * (spec * texture(material.specular, TexCoords).rgb);
    // vec3 emission = texture(material.emission, TexCoords).rgb;

    // Point Light
    // float distance = length(pointLight.position - FragPos);
    // float attenuation = 1.0 / 
    // (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * distance * distance);

    // vec3 lightDir = normalize(pointLight.position - FragPos);
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  

    // float diff = max(dot(norm, lightDir), 0.0);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // vec3 ambient = pointLight.ambient * texture(material.diffuse, TexCoords).rgb;
    // vec3 diffuse = pointLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    // vec3 specular = pointLight.specular * (spec * texture(material.specular, TexCoords).rgb);
    // vec3 emission = texture(material.emission, TexCoords).rgb;

    // ambient *= attenuation;
    // diffuse *= attenuation;
    // specular *= attenuation;

    // Spotlight 
    float distance = length(spotlight.position - FragPos);
    float attenuation = 1.0 / 
    (spotlight.constant + spotlight.linear * distance + spotlight.quadratic * distance * distance);

    vec3 lightDir = normalize(spotlight.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float theta = dot(lightDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutOff - spotlight.outerCutOff;
    float intensity = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = max(dot(norm, lightDir), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = spotlight.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = spotlight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    vec3 specular = spotlight.specular * (spec * texture(material.specular, TexCoords).rgb);
    vec3 emission = texture(material.emission, TexCoords).rgb;

    diffuse *= intensity;
    specular *= intensity;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
   
    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
} 


