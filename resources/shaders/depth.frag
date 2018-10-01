// Version du GLSL
#version 330 compatibility


in float depth;


// Fonction main
void main()
{
	gl_FragColor = vec4( depth, depth, depth, 1. );
}
