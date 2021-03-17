#shader v
#version 330 core

layout(location = 0) in vec4 i_pos;
layout(location = 1) in vec4 i_color;

uniform vec4 u_color;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 vo_color;

void main()
{
	gl_Position = u_projection * u_view * u_model * i_pos;
	vo_color = u_color * i_color;
};


#shader f
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_amblight_color;
uniform vec3 u_diflight_dir;
uniform float u_amblight_intensity;
uniform float u_diflight_intensity;

in vec4 vo_color;

uniform sampler2D u_texture;
void main()
{
	color = vo_color;

	vec4 color_base = vec4(u_amblight_color, 1.0);
	vec4 amblight = color_base * u_amblight_intensity;

	float diffuse_factor = dot(normalize(vo_normal), normalize(u_diflight_dir));
	diffuse_factor = max(diffuse_factor, 0.0f);

	vec4 difflight = color_base * diffuse_factor * u_diflight_intensity;


	color = color * (amblight + difflight);
};