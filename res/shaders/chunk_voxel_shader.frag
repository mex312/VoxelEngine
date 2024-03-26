#version 460 core
out vec4 FragColor;

in vec2 uv;
flat in int texID;

uniform sampler2DArray tex;

void main()
{
//	FragColor = vec4(uv, 0.0f, 1.0f);
	FragColor = texture(tex, vec3(uv, texID));
}