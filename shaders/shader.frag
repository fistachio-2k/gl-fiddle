#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform float mixCof;

void main()
{
    FragColor = mix(texture(ourTexture0, texCoord), texture(ourTexture1, texCoord), mixCof) * vec4(ourColor, 1.0);
}