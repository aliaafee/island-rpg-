/*
    Adapted from shader by Qugurun
    available at https://www.shadertoy.com/view/wt2GRt

*/

uniform sampler2D texture;

uniform float iTime;

uniform vec3 worldPosition;
uniform vec3 screenPosition;

uniform vec2 screenSize;
uniform vec2 textureSize;

void main() {
    vec2 fragCoord = gl_TexCoord[0].xy;

    // Translate world position
    vec2 uv;
    uv.x = (fragCoord.x * textureSize.x + worldPosition.x) / screenSize.x;
    uv.y = (fragCoord.y * textureSize.y + worldPosition.y) / screenSize.y;

    // Scale
    uv *= 3.;

    vec4 texture_color = vec4(0.192156862745098, 0.6627450980392157, 0.9333333333333333, 1.0);

    // Speed
    vec4 k = vec4(iTime) * 1.;

    // Dont really know what is going on here :)
    k.xy = uv * 7.0;
    float val1 = length(0.5 - fract(k.xyw *= mat3(vec3(-2.0, -1.0, 0.0), vec3(3.0, -1.0, 1.0), vec3(1.0, -1.0, -1.0)) * 0.5));
    float val2 = length(0.5 - fract(k.xyw *= mat3(vec3(-2.0, -1.0, 0.0), vec3(3.0, -1.0, 1.0), vec3(1.0, -1.0, -1.0)) * 0.2));
    float val3 = length(0.5 - fract(k.xyw *= mat3(vec3(-2.0, -1.0, 0.0), vec3(3.0, -1.0, 1.0), vec3(1.0, -1.0, -1.0)) * 0.5));
    vec4 color = vec4(pow(min(min(val1, val2), val3), 7.0) * 5.0);

    gl_FragColor = texture_color + color;
}