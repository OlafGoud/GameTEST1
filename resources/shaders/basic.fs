#version 330 core

in vec3 fragPos;
in vec2 texCoord;
in float height;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D grassTexture; // Base texture
uniform sampler2D rockTexture;  // Mountain texture
uniform vec3 lightPos;          // Light position
uniform vec3 viewPos;           // Camera position
uniform vec3 lightColor;        // Light color

void main()
{
    // Blend factor based on height (adjust thresholds as needed)
    float blendFactor = smoothstep(1.0, 3.0, height); // Transition between 20 and 40 units in height

    // Sample both textures
    vec4 grass = texture(grassTexture, texCoord);
    vec4 rock = texture(rockTexture, texCoord);

    // Blend textures
    vec4 blendedTexture = mix(grass, rock, blendFactor);

    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine texture color with lighting
    vec3 lighting = lightColor * (diffuse + specular + ambient);
    FragColor = vec4(blendedTexture.rgb, blendedTexture.a);
}
