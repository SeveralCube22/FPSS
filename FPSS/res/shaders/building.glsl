#shader vertex

#version 460 core

layout (location = 0) in vec3 vec_pos;
layout (location = 1) in vec3 vec_normal;
layout (location = 2) in vec2 a_tex_coords;

layout (location = 3) in mat4 model;

uniform mat4 PV;

out vec2 tex_coords;

void main () {
	gl_Position = PV * model * vec4(vec_pos, 1.0);
	tex_coords = a_tex_coords;
}

#shader fragment

#version 460 core

in vec2 tex_coords;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main() {
	color = texture(texture_diffuse1, tex_coords);
}