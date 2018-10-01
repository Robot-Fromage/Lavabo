// Version du GLSL
#version 330 compatibility

in vec3 vcolor;

// Fonction main
void main()
{
	gl_FragColor = vec4( vcolor, 1. );
}
