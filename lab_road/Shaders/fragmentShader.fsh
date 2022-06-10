#version 460
in vec4 norm;
in vec4 globalPos;
in vec2 uv;

uniform float mixParameter;

uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;


uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 specularColor;
uniform vec3 viewPos;

uniform vec3 lightPos;

//uniform vec3 texActivation;

uniform sampler2D texRock;
uniform sampler2D texRoad;
uniform sampler2D texCracks;


void main()
{
   vec3 col = mix(texture( texRock, uv ).rgb, texture( texRoad, uv ).rgb, mixParameter) * texture( texCracks, uv ).rgb;

   vec3 ambient = ambientIntensity*ambientColor;

   vec3 norm = norm.xyz;
   vec3 lightDirection = normalize(lightPos - globalPos.xyz);
   float diffuseValue = diffuseIntensity*max(dot(norm, lightDirection), 0.0);
   vec3 diffuse = diffuseValue*lightColor;
   vec3 viewDirection = normalize(viewPos - globalPos.xyz);
   vec3 reflectionDirection = reflect(-lightDirection, norm);
   float specularValue = pow(max(dot(viewDirection, reflectionDirection), 0.0), 32.0);
   vec3 specular = specularIntensity*specularValue*lightColor;

   gl_FragColor = vec4((ambient)*col, 1.0);
};
