attribute vec3 in_Position;
attribute vec2 in_TexCoords;

varying vec2 texCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(in_Position, 1.0);
	texCoord = in_TexCoords;
}