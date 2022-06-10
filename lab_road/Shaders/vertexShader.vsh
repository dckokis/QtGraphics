#version 460
attribute highp vec4 posAttr;


uniform highp vec4 normal;


uniform highp mat4 totalMatrix;

uniform float x_size;
uniform float z_size;


out vec4 norm;
out vec4 globalPos;
out vec2 uv;

void main()
{

   float unused = z_size;
   uv = vec2(posAttr.x/x_size, -posAttr.z);

   norm = vec4(normalize(mat3(transpose(inverse(totalMatrix))) * normal.xyz), 0);

   globalPos = totalMatrix*vec4(posAttr);


   gl_Position = globalPos;
}
