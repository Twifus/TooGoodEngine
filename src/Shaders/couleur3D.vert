#version 150 core

in vec3 in_Vertex;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;

// Fonction main

void main()
{
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
}
