#shader v
#version 330 core

layout(location = 0) in vec4 i_pos;
layout(location = 1) in vec4 i_color;
layout(location = 2) in vec2 i_tex_coords;

uniform vec4 u_color;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 vo_color;
out vec2 vo_tex_coords;

void main()
{
	gl_Position = u_projection * u_view * u_model * i_pos;
	vo_color = u_color * i_color;
	vo_tex_coords = vec2(i_tex_coords.x, i_tex_coords.y);
};


#shader f
#version 330 core

layout(location = 0) out vec4 color;

in vec4 vo_color;
in vec2 vo_tex_coords;

uniform sampler2D u_texture;
void main()
{
	float tex_coords_mag = sqrt(vo_tex_coords.x * vo_tex_coords.x + vo_tex_coords.y * vo_tex_coords.y);
	color = tex_coords_mag > 0.0f ? texture(u_texture, vo_tex_coords) * vo_color : vo_color;
	if (color.a < 0.1)
		discard;
};