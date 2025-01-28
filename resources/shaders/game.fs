#version 330 core

in vec3 fragPos;
in vec2 texCoord;
in float height;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D inTexture; // Base texture
uniform vec3 lightPos;          // Light position
uniform vec3 viewPos;           // Camera position
uniform vec3 lightColor;        // Light color

vec3 difuseLight = vec3(0.5, 0.5, 0.5);
vec3 ambientLight = vec3(0.5, 0.5, 0.5);
vec3 specularLight = vec3(1.0, 1.0, 1.0);

void main()
{
    
    // ambient
    vec3 ambient = ambientLight * texture(inTexture, texCoord).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = ambientLight * diff * texture(inTexture, texCoord).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularLight * spec * texture(inTexture, texCoord).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
