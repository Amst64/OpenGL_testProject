
#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 outputPos;
uniform vec3 ourPos;
void main()
{
	gl_Position = vec4(aPos.x + ourPos.x, aPos.y + ourPos.y, aPos.z + ourPos.z, 1.0f);
	outputPos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
}