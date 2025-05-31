#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 uViewPos;
uniform vec3 uLightPos;
uniform vec3 uLightColor;

uniform vec3 uKa;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

out vec4 FragColor;

void main()
{
    // Ambient
    vec3 ambient = uKa * uLightColor * 0.2;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uKd * diff * uLightColor;

    // Specular
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    vec3 specular = uKs * spec * uLightColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(clamp(result, 0.0, 1.0), 1.0);  // clamping to [0,1]
}
