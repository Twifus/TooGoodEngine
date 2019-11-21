#version 330 core

layout (location = 0) in vec3 in_vertex;
layout (location = 1) in vec4 in_color;

// Uniform

uniform mat4 projection;
uniform mat4 modelview;

out vec4 color;

// Fonction main

void main()
{
    gl_Position = projection * modelview * vec4(in_vertex, 1.0);

    color = in_color;
}
