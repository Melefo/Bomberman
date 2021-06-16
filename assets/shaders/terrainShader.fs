#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 mapSize;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord)*fragColor;
    vec2 posOnMap = vec2((fragTexCoord.x * mapSize.x), (fragTexCoord.y * mapSize.y));
    vec4 brightColor = vec4(texelColor.r + 0.2,
                        texelColor.g + 0.2,
                        texelColor.b + 0.2,
                        255);
    finalColor = texelColor;

    if (mod(posOnMap.x, 20.0) > 10.0
    && mod(posOnMap.x, 20.0) < 20.0
    && mod(posOnMap.y, 20.0) > 10.0
    && mod(posOnMap.y, 20.0) < 20.0)
        finalColor = brightColor;
    if (mod(posOnMap.x, 20.0) > 0.0
    && mod(posOnMap.x, 20.0) < 10.0
    && mod(posOnMap.y, 20.0) > 0.0
    && mod(posOnMap.y, 20.0) < 10.0)
        finalColor = brightColor;
}
