#version 330

struct Light
{
    vec3 direction;
    vec3 position;

    vec3 diffuseLight;
    vec3 specularLight;

    float constant;
    float linear;
    float quadratic;
};

uniform Light lights;
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

vec3 CalculateDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    //specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //combine results
    vec3 ambient = u_AmbientLight * vec3(texture(material.diffuseTexture, i_TexCoord)) * u_AmbientLightStrength;
    vec3 diffuse = light.diffuseLight * diff * vec3(texture(material.diffuseTexture, i_TexCoord));
    vec3 specular = light.specularLight * spec * vec3(texture(material.specularTexture, i_TexCoord));

    //float shadow = CalculateShadow(diff);
    //return (/*shadow */ (diffuse + specular) + ambient);
    return (diffuse + specular) + ambient;
}

vec3 CalculatePointLight(Light light)
{
    float distance = length(light.position - i_FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    vec3 color = texture(material.diffuseTexture, i_TexCoord).rgb;
    vec3 normal = normalize(i_Normal);
    vec3 lightColor = light.diffuseLight;
    // ambient
    vec3 ambient = u_AmbientLightStrength * u_AmbientLight;
    // diffuse
    vec3 lightDir = normalize(light.position - i_FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * light.diffuseLight;
    // specular
    vec3 viewDir = normalize(u_ViewPos - i_FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * light.specularLight;    
    // calculate shadow
    //float shadow = ShadowCalculation(fragPos);
    
    //ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 lighting = (ambient + /*(1.0 - shadow) */ (diffuse + specular)) * color;    
    return lighting;
}

void main()
{
    vec3 viewDir = normalize(u_ViewPos - i_FragPos);
	//vec3 result = CalculateDirLight(lights, i_Normal, viewDir);
    vec3 result = CalculatePointLight(lights);

	gl_FragColor = vec4(result, 1.0);
}