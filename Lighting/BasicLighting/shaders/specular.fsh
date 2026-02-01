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
  float specularStrength = 0.5;
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  vec3 result = pow(max(dot(viewDir, reflectDir), 0.0), 32) * specularStrength * lightColor;
  FragColor = vec4(result, 1.0); 
}

