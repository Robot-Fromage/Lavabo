// Version du GLSL
#version 330 compatibility

// IN
in vec3 in_Vertex;
in vec3 in_Normal;

// UNIFORM
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 normalMatrix;

// OUT
out vec3 vcolor;

// Fonction main
void main()
{
    vcolor = normalize( normalMatrix * in_Normal );
    gl_Position = projection * view * model * vec4( in_Vertex, 1.0 );
}
