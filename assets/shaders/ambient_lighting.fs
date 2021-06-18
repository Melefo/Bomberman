#version 330

in vec2 fragTexCoord; // Position of the fs texel in the screen (0.0 - 1.0)
in vec4 fragColor; // The color of the basic screen (without anything)

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec4 color;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord)*fragColor*colDiffuse;

    float red = abs(color.r * texelColor.r * fragColor.r * colDiffuse.r);
    float green = abs(color.g * texelColor.g * fragColor.g * colDiffuse.g);
    float blue = abs(color.b * texelColor.b * fragColor.b * colDiffuse.b);
    float alpha = abs(color.a * texelColor.a * fragColor.a * colDiffuse.a);

    finalColor = vec4(red, green, blue, alpha);
}