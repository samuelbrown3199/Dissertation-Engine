#version 330
layout(location = 0)in vec3 a_Position;
layout(location = 1)in vec2 a_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec2 i_TexCoord;

void main()
{
	i_TexCoord = a_TexCoords;
	gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0);
}