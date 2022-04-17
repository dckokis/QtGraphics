#version 330

uniform vec4 objectColor;
uniform vec4 ambientColor;
uniform vec4 directedColor;
uniform vec4 pointColor;
uniform vec4 projectorColor;

uniform vec3 viewPos;
uniform vec3 directedPos;
uniform vec3 pointPos;
uniform vec3 projectorPos;
uniform vec3 projDir;

uniform float ka;
uniform float kd;
uniform float ks;

uniform int isAmbient;
uniform int isPoint;
uniform int isDirected;
uniform int isProjector;

varying vec3 fragPos;
varying vec3 normal;

vec4 ambient()
{
    vec4 ambient = ka * ambientColor;
    return ambient;
}


vec4 directed(vec3 fragPos, vec3 normal)
{
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


vec4 point(vec3 fragPos, vec3 normal)
{
    /* diffuse */
    vec3 lightDir = normalize(pointPos - fragPos);
    float diff = kd * max(dot(normal, lightDir), 0.f);
    vec4 diffuse = diff * pointColor;

    /* specular */
    vec3 viewDir = normalize(fragPos - viewPos);
    vec3 reflectDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, reflectDir), .0f), 256);
    vec4 specular = ks * spec * pointColor;
    float lightDistance = abs((pointPos.x - fragPos.x)*(pointPos.x - fragPos.x) +
                            (pointPos.y - fragPos.y)*(pointPos.y - fragPos.y) +
                            (pointPos.z - fragPos.z)*(pointPos.z - fragPos.z));
    return (diffuse + specular) * (1 + 1/pow(lightDistance, 2));
}


vec4 projector(vec3 fragPos, vec3 normal)
{
    /* diffuse */
    vec3 lightDir = normalize(projectorPos - fragPos);
    float diff = kd * max(dot(normal, lightDir), 0.f);
    vec4 diffuse = diff * projectorColor;

    /* specular */
    vec3 viewDir = normalize(fragPos - viewPos);
    vec3 reflectDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, reflectDir), 0.f), 2);
    vec4 specular = ks * spec * projectorColor;

    float max = 0.05, min = 0.001;


    float theta = abs(acos(dot(-lightDir, normalize(projDir))));
    float intensity = clamp((theta - min) / (max - min), 0.f, 1.f);

    float lightDistance = abs((projectorPos.x - fragPos.x)*(projectorPos.x - fragPos.x) +
                              (projectorPos.y - fragPos.y)*(projectorPos.y - fragPos.y) +
                              (projectorPos.z - fragPos.z)*(projectorPos.z - fragPos.z));

    return (1-intensity) * 4 *(diffuse + specular) * (1 + 1/pow(lightDistance, 2));
}


void main()
{
    gl_FragColor = (isAmbient * ambient() + isPoint * point(fragPos, normal) + isDirected * directed(fragPos, normal) + isProjector * projector(fragPos, normal)) * objectColor;
}