#version 330 core
out vec4 FragColor;
in vec3 outputPos;

void main()
{
	FragColor = vec4(outputPos, 1.0f);
}