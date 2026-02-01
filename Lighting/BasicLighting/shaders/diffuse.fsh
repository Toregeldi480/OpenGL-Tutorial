#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main()
{
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);

  vec3 result = max(dot(norm, lightDir), 0.0) * objectColor * lightColor;
  FragColor = vec4(result, 1.0); 
}

