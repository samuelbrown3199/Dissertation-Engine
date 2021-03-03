#version 330

struct Light
{
    vec3 direction;
    vec3 position;

	int lightType;

    vec3 diffuseLight;
    vec3 specularLight;

    float constant;
    float linear;
    float quadratic;
    float intensity;
};

uniform int numberOfLights;
uniform Light lights[20];
uniform vec3 u_AmbientLight;
uniform float u_AmbientLightStrength;

struct Material
{
	sampler2D diffuseTexture;
    sampler2D specularTexture;
    float shininess;
};
uniform Material material;

uniform vec3 u_ViewPos;

in vec2 i_TexCoord;
in vec3 i_Normal;
in vec3 i_FragPos;
in mat4 i_ViewMat;

vec3 CalculateAmbientLight()
{
    vec3 ambient = u_AmbientLight * vec3(texture(material.diffuseTexture, i_TexCoord)) * u_AmbientLightStrength;
	return ambient;
}

vec3 CalculateDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction - i_FragPos);
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //combine results

    vec3 diffuse = light.diffuseLight * diff * vec3(texture(material.diffuseTexture, i_TexCoord));
    vec3 specular = light.specularLight * spec * vec3(texture(material.specularTexture, i_TexCoord));

    //float shadow = CalculateShadow(diff);
    //return (/*shadow */ (diffuse + specular));
    return (diffuse + specular);
}

vec3 CalculatePointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 diffuse  = light.diffuseLight  * diff * vec3(texture(material.diffuseTexture, i_TexCoord));
    vec3 specular = light.specularLight * spec * vec3(texture(material.specularTexture, i_TexCoord));
    diffuse  *= attenuation * light.intensity;
    specular *= attenuation * light.intensity;
    return (diffuse + specular);
}

void main()
{
    vec3 viewDir = normalize(u_ViewPos - i_FragPos);
	vec3 result = CalculateAmbientLight();
	
	for(int i = 0; i < numberOfLights; i++)
	{	
		if(lights[i].lightType == 0)
		{
			result += CalculateDirLight(lights[i], i_Normal, viewDir);
		}
		else
		{
			result += CalculatePointLight(lights[i], i_Normal, i_FragPos, viewDir);
		}
	}

	gl_FragColor = vec4(result, 1.0);
}