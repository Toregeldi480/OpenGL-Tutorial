#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float ambientStrength = 0.1;
  float specularStrength = 0.5;
  int shininess = 64;

  vec3 ambient = ambientStrength * lightColor;
  vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;
  vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), shininess) * lightColor * specularStrength;

  vec3 result = (ambient + diffuse + specular) * objectColor;
  FragColor = vec4(result, 1.0); 
}

