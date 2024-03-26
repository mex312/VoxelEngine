#version 460 core
layout (location = 0) in uint quad_data;
layout (location = 1) in uint inst_data;
layout (location = 2) in uint inst_tex;

out vec2 uv;
out int texID;

uniform mat4 MVP;

void main()
{
    uvec3 q_pos = uvec3(quad_data & 1u, (quad_data >> 1u) & 1u, 0);
    uv = q_pos.xy;

    uint rotation = inst_data >> 30;

    uint id = gl_DrawID;

    rotation = id == 5 ? (rotation + 2u) & 3u : rotation;


    q_pos = ((rotation & 2u) > 0) ? (uvec3(1, 1, 0) ^ q_pos) : q_pos;
    q_pos = ((rotation & 1u) > 0) ? (uvec3(q_pos.y, 1u ^ q_pos.x, 0)) : q_pos;


    q_pos = (id == 2u || id == 3u || id == 5u)  ? (uvec3(1, 0, 1) ^ q_pos.xyz) : (q_pos);
    q_pos = (((id ^ 5u) & 5u) == 4u) ? (uvec3(1, 0, 0) ^ q_pos.zyx) : (q_pos);
    q_pos = ((id & 4u) > 0)  ? (uvec3(0, 1, 0) ^ q_pos.xzy) : (q_pos);


    vec3 translation = vec3(
    (inst_data) & 0x3Fu,
    (inst_data >> 6u) & 0x3Fu,
    (inst_data >> 12u) & 0x3Fu
    );

    gl_Position = MVP * vec4(q_pos + translation, 1.0f);
}