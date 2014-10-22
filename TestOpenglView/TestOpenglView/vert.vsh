#version 150

in vec4 position;
in vec4 colour;

out vec4 colourV;

void main (void)
{
    colourV = colour;
    gl_Position = position;
}
