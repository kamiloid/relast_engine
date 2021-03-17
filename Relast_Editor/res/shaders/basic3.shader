#shader v
#version 330 core

layout(location = 0) in vec4 i_pos;
layout(location = 1) in vec4 i_color;
layout(location = 2) in vec2 i_tex_coords;
layout(location = 3) in vec3 i_normal;

uniform vec4 u_color;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 vo_pos;
out vec4 vo_color;
out vec2 vo_tex_coords;
out vec3 vo_normal;

void main()
{
	vo_pos = vec3(u_model * i_pos);
	gl_Position = u_projection * u_view * u_model * i_pos;
	vo_color = u_color * i_color;
	vo_tex_coords = vec2(i_tex_coords.x, i_tex_coords.y);
	vo_normal = vec3(transpose(inverse(u_model))) * i_normal;
};


#shader f
#version 330 core

layout(location = 0) out vec4 color;

struct Light
{
	vec3 position;
	vec3 ambient_col;
	vec3 diffuse_col;
	vec3 specular_col;

	float ambient_level;
	float diffuse_level;
	float specular_level;
};
struct Material
{
	sampler2D diffuse_map;
	sampler2D specular_map;

	vec3 ambient_col;
	vec3 diffuse_col;
	vec3 specular_col;
	float shininess;
};

uniform Light u_light1;
uniform Material u_material1;
uniform vec3 u_camera_pos;

in vec3 vo_pos;
in vec4 vo_color;
in vec2 vo_tex_coords;
in vec3 vo_normal;

uniform sampler2D u_texture;
void main()
{
	//texture
	float tex_coords_mag = sqrt(vo_tex_coords.x * vo_tex_coords.x + vo_tex_coords.y * vo_tex_coords.y);
	//color = tex_coords_mag > 0.0f ? texture(u_texture, vo_tex_coords) * vo_color : vo_color;
	color = tex_coords_mag > 0.0f ? texture(u_material1.diffuse_map, vo_tex_coords) * vec4(u_material1.ambient_col, 1.0) : vec4(u_material1.ambient_col, 1.0);

	//ambient
	vec4 ambient = vec4(u_light1.ambient_col * u_material1.ambient_col * u_light1.ambient_level, 1.0);

	//diffuse
	vec3 normal = vo_normal;
	vec3 light_dir = normalize(u_light1.position - vo_pos);
	float diffuse_factor = max(dot(normal, light_dir), 0.0);
	vec4 diffuse = vec4(u_light1.diffuse_col * u_material1.diffuse_col * diffuse_factor * u_light1.diffuse_level, 1.0);

	//specular
	vec3 vew_dir = normalize(u_camera_pos - vo_pos);
	vec3 reflec_dir = reflect(-light_dir, normal);
	float specular_factor = pow(max(dot(u_camera_pos, reflec_dir), 0.0), u_material1.shininess);
	vec4 specular = vec4(u_light1.specular_col * specular_factor * u_material1.specular_col * u_light1.specular_level * vec3(texture(u_material1.specular_map, vo_tex_coords)), 1.0);

	color = color * (ambient + diffuse + specular);

	if (color.a < 0.1)
		discard;
};