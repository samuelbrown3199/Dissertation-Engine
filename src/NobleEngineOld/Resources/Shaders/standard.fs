#version 330

struct Material
{
	sampler2D diffuseTexture;
};
uniform Material material;
in vec2 i_TexCoord;

void main()
{
	vec4 result = texture(material.diffuseTexture, i_TexCoord);
	gl_FragColor = result;
}