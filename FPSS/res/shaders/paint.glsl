#shader vertex

#version 460 core

layout (location = 0) in vec3 vec_pos;
layout (location = 1) in vec3 vec_normal;
layout (location = 2) in vec2 a_tex_coords;

layout (location = 3) in mat4 model;

uniform mat4 PV;

void main () {
	gl_Position = PV * model * vec4(vec_pos, 1.0);
}

#shader fragment

#version 460 core

out vec4 color;

void main() {
	color = vec4(0.0, 0.0, 0.0, 0.0);
}