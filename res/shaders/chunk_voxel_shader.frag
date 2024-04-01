#version 460 core
out vec4 FragColor;

in vec2 uv;
flat in uint texID;

uniform sampler2DArray tex;

void main()
{
	FragColor = texture(tex, vec3(uv, texID));
}