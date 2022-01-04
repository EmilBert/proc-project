#version 330 core

#define MAX 100

// Outputs colors in RGBA
out vec4 FragColor;


in vec3 crntPos;
in vec3 Normal;
in vec3 color;
//in vec2 texCoord;

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
	float	specularLight		= 0.30f;
	vec3	viewDirection		= normalize(camPos - crntPos);
	vec3	reflectionDirection = reflect(-lightDirection, normal);
	float	specAmount			= pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float	specular			= specAmount * specularLight;
	

	float posy = crntPos.y/6.4;
	vec3 white = vec3(1,1,1);
	vec3 black = vec3(0.5,0.5,0.5);

	//vec3 fcolor;
	//fcolor = mix(black, white, smoothstep(0.0, 0.5, posy));

	
	vec3 color1 = vec3(0.43,0.44,0.45);
	vec3 color2 = vec3(0.761, 0.698, 0.502);
	vec3 color3 = vec3(0,0.6,0);
	vec3 color4 = vec3(0.0,0.8,0.0);
	vec3 color5 = vec3(1,1,1);
	vec3 color6 = vec3(1,1,1);

	vec3 fcolor;

	fcolor = mix(color1, color2, smoothstep(0.0, 0.2, posy));
	fcolor = mix(fcolor, color3, smoothstep(0.2, 0.4, posy));
	fcolor = mix(fcolor, color4, smoothstep(0.4, 0.6, posy));
	fcolor = mix(fcolor, color5, smoothstep(0.6, 0.7, posy));
	fcolor = mix(fcolor, color6, smoothstep(0.7, 1,	  posy));
	

	//vec3 fcolor = mix(black, white, smoothstep(0, 0.4, posy));

	// outputs final color
	FragColor = vec4(color, 1.0f)* lightColor * (diffuse + ambient + specular);
	//*fcolor

}

