#version 460 core

in vec3 vertexColor;
in vec2 vertexUV;
out vec4 FragColor;

uniform sampler2D uTexture;

void main(){
    vec4 texColor = texture(uTexture, vertexUV);
    FragColor = vec4(texColor.rgb * vertexColor, texColor.a);
}