#version 330 core

layout(location = 0) in vec3 aPos;   // Vertex position
layout(location = 1) in vec2 aTexCoord; // Texture coordinates
layout(location = 2) in vec3 aNormal;   // Normals

out vec3 fragPos;       // To pass position to fragment shader
out vec2 texCoord;      // To pass texture coordinates
out float height;       // To pass height for blending
out vec3 Normal;     // Normal vector in world space



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    fragPos = vec3(model * vec4(aPos, 1.0));
    texCoord = aTexCoord;
    height = aPos.y; // Pass the height for blending
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
}
