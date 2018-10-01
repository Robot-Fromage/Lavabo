// Version du GLSL
#version 330 compatibility

in vec3 in_Vertex;
in vec3 in_Normal;

out float depth;

// Fonction main
void main()
{
    vec4 computedpos = gl_ModelViewProjectionMatrix * vec4(in_Vertex, 1.0);
    depth = computedpos.w;
    gl_Position = computedpos;
}
