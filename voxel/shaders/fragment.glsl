#version 460 core

in vec3 texCoords;
out vec4 pixelColor;

uniform sampler2D textureSample;

uniform sampler2DArray textureArray; 

void main()
{
   pixelColor = texture(textureArray, texCoords);
}
