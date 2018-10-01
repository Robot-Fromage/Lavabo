// Version du GLSL
#version 330 compatibility

in vec3 in_Vertex;
in vec3 in_Normal;

out vec3 vcolor;

// Fonction main
void main()
{
    vcolor = in_Normal;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(in_Vertex, 1.0);
}
