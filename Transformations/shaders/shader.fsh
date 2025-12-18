#version 330 core
out vec4 FragColor;
in vec3 VertexColor0;

void main() 
{
  FragColor = vec4(VertexColor0, 1.0);
}
