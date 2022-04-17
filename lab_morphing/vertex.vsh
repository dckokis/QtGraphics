#version 330

uniform highp mat4 matrix;
uniform highp float morphRate;
uniform vec3 lightColor;
in highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    highp vec4 transformedPos = posAttr;

    transformedPos.x = posAttr.x * sqrt(1.0f - ((posAttr.y * posAttr.y + posAttr.z * posAttr.z) / 2.0f
                                                - posAttr.y * posAttr.y * posAttr.z * posAttr.z / 3.0f) * morphRate);

    transformedPos.y = posAttr.y * sqrt(1.0f - ((posAttr.x * posAttr.x + posAttr.z * posAttr.z) / 2.0f
                                                - posAttr.x * posAttr.x * posAttr.z * posAttr.z / 3.0f) * morphRate);

    transformedPos.z = posAttr.z * sqrt(1.0f - ((posAttr.x * posAttr.x + posAttr.y * posAttr.y) / 2.0f
                                                - posAttr.x * posAttr.x * posAttr.y * posAttr.y / 3.0f) * morphRate);

    gl_Position = matrix * transformedPos;
    col = colAttr;
}
