#version 330 core
in vec2 p_uv;
in vec4 p_color;
out vec4 out_color;

uniform sampler2D displacement_img;
uniform sampler2D img;

void main() {
    out_color = mix(texture(displacement_img, p_uv), texture(img, p_uv), 0.8);
}
