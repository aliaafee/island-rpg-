uniform float size;
uniform float iTime;
uniform float spam;

uniform vec3 worldPosition;
uniform vec3 screenPosition;

uniform vec2 screenSize;
uniform vec2 textureSize;

/**
 * Adapted from "A Perlin Simplex Noise C++ Implementation (1D, 2D, 3D)."
 * by Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * source: https://github.com/SRombauts/SimplexNoise
 */

//Parameters of fractal noise
float mFrequency = 1.;
float mAmplitude = 1.;
float mLacunarity = 2.;
float mPersistence = 0.5;

int perm[256];

// Skewing/Unskewing factors for 2D
const float F2 = 0.366025403; // F2 = (sqrt(3) - 1) / 2
const float G2 = 0.211324865; // G2 = (3 - sqrt(3)) / 6   = F2 / (1 + 2 * K)

void generate_hash_table() {
    perm[0] = 151;
    perm[1] = 160;
    perm[2] = 137;
    perm[3] = 91;
    perm[4] = 90;
    perm[5] = 15;
    perm[6] = 131;
    perm[7] = 13;
    perm[8] = 201;
    perm[9] = 95;
    perm[10] = 96;
    perm[11] = 53;
    perm[12] = 194;
    perm[13] = 233;
    perm[14] = 7;
    perm[15] = 225;
    perm[16] = 140;
    perm[17] = 36;
    perm[18] = 103;
    perm[19] = 30;
    perm[20] = 69;
    perm[21] = 142;
    perm[22] = 8;
    perm[23] = 99;
    perm[24] = 37;
    perm[25] = 240;
    perm[26] = 21;
    perm[27] = 10;
    perm[28] = 23;
    perm[29] = 190;
    perm[30] = 6;
    perm[31] = 148;
    perm[32] = 247;
    perm[33] = 120;
    perm[34] = 234;
    perm[35] = 75;
    perm[36] = 0;
    perm[37] = 26;
    perm[38] = 197;
    perm[39] = 62;
    perm[40] = 94;
    perm[41] = 252;
    perm[42] = 219;
    perm[43] = 203;
    perm[44] = 117;
    perm[45] = 35;
    perm[46] = 11;
    perm[47] = 32;
    perm[48] = 57;
    perm[49] = 177;
    perm[50] = 33;
    perm[51] = 88;
    perm[52] = 237;
    perm[53] = 149;
    perm[54] = 56;
    perm[55] = 87;
    perm[56] = 174;
    perm[57] = 20;
    perm[58] = 125;
    perm[59] = 136;
    perm[60] = 171;
    perm[61] = 168;
    perm[62] = 68;
    perm[63] = 175;
    perm[64] = 74;
    perm[65] = 165;
    perm[66] = 71;
    perm[67] = 134;
    perm[68] = 139;
    perm[69] = 48;
    perm[70] = 27;
    perm[71] = 166;
    perm[72] = 77;
    perm[73] = 146;
    perm[74] = 158;
    perm[75] = 231;
    perm[76] = 83;
    perm[77] = 111;
    perm[78] = 229;
    perm[79] = 122;
    perm[80] = 60;
    perm[81] = 211;
    perm[82] = 133;
    perm[83] = 230;
    perm[84] = 220;
    perm[85] = 105;
    perm[86] = 92;
    perm[87] = 41;
    perm[88] = 55;
    perm[89] = 46;
    perm[90] = 245;
    perm[91] = 40;
    perm[92] = 244;
    perm[93] = 102;
    perm[94] = 143;
    perm[95] = 54;
    perm[96] = 65;
    perm[97] = 25;
    perm[98] = 63;
    perm[99] = 161;
    perm[100] = 1;
    perm[101] = 216;
    perm[102] = 80;
    perm[103] = 73;
    perm[104] = 209;
    perm[105] = 76;
    perm[106] = 132;
    perm[107] = 187;
    perm[108] = 208;
    perm[109] = 89;
    perm[110] = 18;
    perm[111] = 169;
    perm[112] = 200;
    perm[113] = 196;
    perm[114] = 135;
    perm[115] = 130;
    perm[116] = 116;
    perm[117] = 188;
    perm[118] = 159;
    perm[119] = 86;
    perm[120] = 164;
    perm[121] = 100;
    perm[122] = 109;
    perm[123] = 198;
    perm[124] = 173;
    perm[125] = 186;
    perm[126] = 3;
    perm[127] = 64;
    perm[128] = 52;
    perm[129] = 217;
    perm[130] = 226;
    perm[131] = 250;
    perm[132] = 124;
    perm[133] = 123;
    perm[134] = 5;
    perm[135] = 202;
    perm[136] = 38;
    perm[137] = 147;
    perm[138] = 118;
    perm[139] = 126;
    perm[140] = 255;
    perm[141] = 82;
    perm[142] = 85;
    perm[143] = 212;
    perm[144] = 207;
    perm[145] = 206;
    perm[146] = 59;
    perm[147] = 227;
    perm[148] = 47;
    perm[149] = 16;
    perm[150] = 58;
    perm[151] = 17;
    perm[152] = 182;
    perm[153] = 189;
    perm[154] = 28;
    perm[155] = 42;
    perm[156] = 223;
    perm[157] = 183;
    perm[158] = 170;
    perm[159] = 213;
    perm[160] = 119;
    perm[161] = 248;
    perm[162] = 152;
    perm[163] = 2;
    perm[164] = 44;
    perm[165] = 154;
    perm[166] = 163;
    perm[167] = 70;
    perm[168] = 221;
    perm[169] = 153;
    perm[170] = 101;
    perm[171] = 155;
    perm[172] = 167;
    perm[173] = 43;
    perm[174] = 172;
    perm[175] = 9;
    perm[176] = 129;
    perm[177] = 22;
    perm[178] = 39;
    perm[179] = 253;
    perm[180] = 19;
    perm[181] = 98;
    perm[182] = 108;
    perm[183] = 110;
    perm[184] = 79;
    perm[185] = 113;
    perm[186] = 224;
    perm[187] = 232;
    perm[188] = 178;
    perm[189] = 185;
    perm[190] = 112;
    perm[191] = 104;
    perm[192] = 218;
    perm[193] = 246;
    perm[194] = 97;
    perm[195] = 228;
    perm[196] = 251;
    perm[197] = 34;
    perm[198] = 242;
    perm[199] = 193;
    perm[200] = 238;
    perm[201] = 210;
    perm[202] = 144;
    perm[203] = 12;
    perm[204] = 191;
    perm[205] = 179;
    perm[206] = 162;
    perm[207] = 241;
    perm[208] = 81;
    perm[209] = 51;
    perm[210] = 145;
    perm[211] = 235;
    perm[212] = 249;
    perm[213] = 14;
    perm[214] = 239;
    perm[215] = 107;
    perm[216] = 49;
    perm[217] = 192;
    perm[218] = 214;
    perm[219] = 31;
    perm[220] = 181;
    perm[221] = 199;
    perm[222] = 106;
    perm[223] = 157;
    perm[224] = 184;
    perm[225] = 84;
    perm[226] = 204;
    perm[227] = 176;
    perm[228] = 115;
    perm[229] = 121;
    perm[230] = 50;
    perm[231] = 45;
    perm[232] = 127;
    perm[233] = 4;
    perm[234] = 150;
    perm[235] = 254;
    perm[236] = 138;
    perm[237] = 236;
    perm[238] = 205;
    perm[239] = 93;
    perm[240] = 222;
    perm[241] = 114;
    perm[242] = 67;
    perm[243] = 29;
    perm[244] = 24;
    perm[245] = 72;
    perm[246] = 243;
    perm[247] = 141;
    perm[248] = 128;
    perm[249] = 195;
    perm[250] = 78;
    perm[251] = 66;
    perm[252] = 215;
    perm[253] = 61;
    perm[254] = 156;
    perm[255] = 180;
}

int hashv(int i) {
    return perm[i];
}

/**
 * Adapted from "Noise - simplex - 2D."
 * by iq
 *
 * Source: https://www.shadertoy.com/view/Msf3WH
*/

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

    vec4 shallow_color = vec4(0.192156862745098, 0.6627450980392157, 0.9333333333333333, 1.0);
    vec4 deep_color = vec4(0.09, 0.3, 0.43, 1.);

    float depth = fractal(4, x / size, y / size);
    //depth = depth * depth;

    vec4 col = mix(deep_color, shallow_color, vec4(depth)) + water_color(x, y, iTime, 3.);

    //if(depth > 0.2) {
    //    col.w = 0.;
   //}

    gl_FragColor = col;
}