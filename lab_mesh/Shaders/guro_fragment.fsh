#version 330

uniform vec4 objectColor;
uniform vec4 directedColor;

uniform vec3 viewPos;
uniform vec3 directedPos;

uniform float ka;
uniform float kd;
uniform float ks;

uniform int isDirected;

varying vec3 fragPos;
varying vec3 normal;

vec4 directed(vec3 fragPos, vec3 normal)
{
    vec4 ambCol = vec4(1, 1, 1, 0.f);
    vec4 ambient = ka * ambCol;

    /* diffuse */
    vec3 lightDir = normalize(directedPos);
    float diff = kd * max(dot(normal, lightDir), 0.f);
    vec4 diffuse = diff * directedColor;

    /* specular */
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = normalize(lightDir + viewDir);
    
    float spec = pow(max(dot(normal, reflectDir), 0.0), 128);
    vec4 specular = ks * spec * directedColor;


    return (diffuse + specular);
}

void main()
{
    gl_FragColor = isDirected * directed(fragPos, normal) * objectColor;
}