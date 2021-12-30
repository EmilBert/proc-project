#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

//uniform sampler2D tex0;
//uniform vec4 lightColor;
//uniform vec3 lightPos;
uniform vec3 camPos;

vec3 lightPos = vec3(0.0f, 110.0f, 0.0f);
vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.30f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	// outputs final color
	FragColor = vec4(color, 1.0f)* lightColor * (diffuse + ambient + specular);
}