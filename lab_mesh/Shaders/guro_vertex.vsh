#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

attribute vec3 posAttr;
attribute vec3 normAttr;

varying vec3 fragPos;
varying vec3 normal;


void main()
{
    fragPos = vec3(model * vec4(posAttr, 1.0f));
    normal = normalize(vec3(mat4(transpose(inverse(model))) * vec4(normAttr, 1.0f)));

    gl_Position = projection * view * model * vec4(posAttr, 1.0f);
}