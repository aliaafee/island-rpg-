//uniform sampler2D texture;

uniform float iTime;
uniform float spam;

uniform vec3 worldPosition;
uniform vec3 screenPosition;

uniform vec2 screenSize;
uniform vec2 textureSize;

/**
 * Adapted from "2D Top Down Water."
 * by Qugurun
 *
 * Source: https://www.shadertoy.com/view/wt2GRt
*/

vec4 water_color(float x, float y, float t, float scale) {;
    vec4 k = vec4(t) * 1.;
    k.x = x * 7.0 * scale;
    k.y = y * 7.0 * scale;
    float val1 = length(0.5 - fract(k.xyw *= mat3(vec3(-2.0, -1.0, 0.0), vec3(3.0, -1.0, 1.0), vec3(1.0, -1.0, -1.0)) * 0.5));
    float val2 = length(0.5 - fract(k.xyw *= mat3(vec3(-2.0, -1.0, 0.0), vec3(3.0, -1.0, 1.0), vec3(1.0, -1.0, -1.0)) * 0.2));
    float val3 = length(0.5 - fract(k.xyw *= mat3(vec3(-2.0, -1.0, 0.0), vec3(3.0, -1.0, 1.0), vec3(1.0, -1.0, -1.0)) * 0.5));

    return vec4(pow(min(min(val1, val2), val3), 7.0) * 5.0);
}

void main() {
    vec2 fragCoord = gl_TexCoord[0].xy;

    // Translate world position
    float x = (fragCoord.x * textureSize.x + worldPosition.x) / screenSize.x;
    float y = (fragCoord.y * textureSize.y + worldPosition.y) / screenSize.y;

    vec4 shallow_color = vec4(0.192156862745098, 0.6627450980392157, 0.9333333333333333, 1.0);
    vec4 deep_color = vec4(0.09, 0.3, 0.43, 1.);

    float depth = 1.;

    vec4 texture_color;
    texture_color = mix(shallow_color, deep_color, vec4(depth));

    vec4 ocean_color = shallow_color + water_color(x, y, iTime, 3.);

    gl_FragColor = ocean_color;
    //gl_FragColor = vec4(0.6);

    //gl_FragColor = deep_color + water_color(x, y, iTime, 3.);
}