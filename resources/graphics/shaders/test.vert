#version 150

uniform vec3 screenPosition;

uniform mat4 viewMatrix;

in vec4 position;
//in vec4 texCoord;

out vec2 texCoordV;

void main() {
    // transform the vertex position
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_Position = viewMatrix * position;
    gl_Position = viewMatrix * position;

    texCoordV = gl_Position.xy;

    // transform the texture coordinates
    //gl_TexCoord[0] = viewMatrix * gl_MultiTexCoord0;

    // forward the vertex color
    //gl_FrontColor = gl_Color;
    //gl_Position = vec3(0, 0, 0);
}