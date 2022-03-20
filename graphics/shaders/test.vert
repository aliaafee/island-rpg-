#version 150

uniform vec3 screenPosition;

uniform mat4 viewMatrix, projMatrix;
in vec4 position;

out vec2 texCoord;

void main() {
    // transform the vertex position
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = position;

    texCoord.x = position.x;
    texCoord.y = position.y;

    // transform the texture coordinates
    //gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    //gl_FrontColor = gl_Color;
    //gl_Position = vec3(0, 0, 0);
}