#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_uv;
out vec2 p_uv;
out vec4 p_color;

uniform int displacement_img_height;
uniform int displacement_img_width;
uniform int max_pixel_offset;
uniform sampler2D displacement_img;
uniform sampler2D img;

void main() {
    vec4 color = texture(displacement_img, v_uv);
    float gray = dot(vec3(0.3f, 0.59f, 0.11f), color.rgb);
    float offset_x = (gray - 0.5f) * (max_pixel_offset / float(displacement_img_width));
    float offset_y = (gray - 0.5f) * (max_pixel_offset / float(displacement_img_height));
    gl_Position = vec4(v_pos.x + offset_x, v_pos.y + offset_y, v_pos.z, 1.0f);
    p_uv = v_uv;
}
