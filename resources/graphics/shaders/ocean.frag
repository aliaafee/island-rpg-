uniform float size;
uniform float iTime;
uniform float spam;

uniform vec3 worldPosition;
uniform vec3 screenPosition;

uniform vec2 screenSize;
uniform vec2 textureSize;

/**
 * Adapted from "Noise - simplex - 2D."
 * by iq
 *
 * Source: https://www.shadertoy.com/view/Msf3WH
*/

//Parameters of fractal noise
float mFrequency = 1.;
float mAmplitude = 1.;
float mLacunarity = 2.;
float mPersistence = 0.5;

vec2 hash(vec2 p) // replace this by something better
    {
    p = vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)));
    return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}

float noise(float x, float y) {
    vec2 p = vec2(x, y);

    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;

    vec2 i = floor(p + (p.x + p.y) * K1);
    vec2 a = p - i + (i.x + i.y) * K2;
    float m = step(a.y, a.x);
    vec2 o = vec2(m, 1.0 - m);
    vec2 b = a - o + K2;
    vec2 c = a - 1.0 + 2.0 * K2;
    vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
    vec3 n = h * h * h * h * vec3(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));
    return dot(n, vec3(70.0));
}

float fractal(int octaves, float x, float y) {
    float noise_output = 0.f;
    float denom = 0.f;
    float frequency = mFrequency;
    float amplitude = mAmplitude;

    for(int i = 0; i < octaves; i++) {
        noise_output += (amplitude * noise(x * frequency, y * frequency));
        denom += amplitude;

        frequency *= mLacunarity;
        amplitude *= mPersistence;
    }

    return (noise_output / denom);
}

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

    float x = (fragCoord.x * textureSize.x + worldPosition.x) / screenSize.x;
    float y = (fragCoord.y * textureSize.y + worldPosition.y) / screenSize.y;

    //vec4 shallow_color = vec4(0.192156862745098, 0.6627450980392157, 0.9333333333333333, 1.0);
    //vec4 deep_color = vec4(0.09, 0.3, 0.43, 1.);

    vec4 shallow_color = vec4(0, 0.5, 0.74, 1);
    vec4 deep_color = vec4(0.09, 0.3, 0.43, 1.);

    float depth = fractal(4, x / size, y / size);
    //depth = depth * depth;

    vec4 col = mix(deep_color, shallow_color, vec4(depth)) + water_color(x, y, iTime, 3.);

    //if(depth > 0.2) {
    //    col.w = 0.;
   //}

    gl_FragColor = col;
}