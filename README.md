# HW7 – Phong Shading Implementation Report (OpenGL + GLSL)
## 202011378 차현준
🔷 1. main_Phong_Shader.cpp – Main Application Entry
<br>
This file contains the OpenGL setup, shader program creation, buffer allocation, transformation matrix preparation, and the render loop.

<br>
<br>
🔸 setupBuffers()
<br>
This function initializes geometry by calling create_scene() (from sphere_scene.cpp) which generates a high-resolution sphere mesh.

<br>
Vertex Buffer Object (VBO), Normal Buffer Object (NBO), and Element Buffer Object (EBO) are created and populated.

<br>
These buffers are then associated with a Vertex Array Object (VAO) and linked to shader attributes (aPos, aNormal).

<br>
<br>
🔸 render()
<br>
Clears the screen and enables depth testing.

<br>
Sets up transformation matrices:

<br>
model: object transformation (scaled and translated).

<br>
view: camera looking down -Z.

<br>
projection: perspective projection.

<br>
Calculates and passes the normal matrix (uNormalMatrix) to preserve correct normal orientation under non-uniform transforms.

<br>
Passes lighting and material properties as uniforms:

<br>
uLightPos, uLightColor: Light properties.

<br>
uKa, uKd, uKs, uShininess: Material properties.

<br>
Calls glDrawElements() to render the sphere mesh with Phong shading.

<br>
<br>
🔷 2. sphere_scene.cpp – Procedural Sphere Generation
<br>
This file generates the mesh geometry (vertex positions, normals, and triangle indices) for a sphere using parametric sampling.

<br>
<br>
🔸 Key Concepts
<br>
Uses stacks and slices to define resolution.

<br>
For each latitude and longitude, computes the sphere’s Cartesian coordinates using spherical coordinates.

<br>
Also calculates smooth per-vertex normals using normalized positions (ideal for Phong shading).

<br>
Triangle indices are computed for mesh connectivity.

<br>
<br>
🔸 Output Buffers
gVertexBuffer → flat array of vertex positions.

gNormalBuffer → flat array of normals.

gIndexBuffer → triangle indices.

gNumVertices, gNumTriangles store array sizes.

These are used by main_Phong_Shader.cpp.

<br>
<br>
🔷 3. Phong.vert – Vertex Shader
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uNormalMatrix;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(uModel * vec4(aPos, 1.0));     // Transformed position
    Normal = normalize(uNormalMatrix * aNormal); // Corrected normal

    gl_Position = uProjection * uView * vec4(FragPos, 1.0); // Final position
}
<br>
<br>
🔸 Purpose
Applies transformations to vertex position and normal.

Passes world-space position (FragPos) and corrected normal to the fragment shader.

<br>
<br>
🔷 4. Phong.frag – Fragment Shader
#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 uViewPos;
uniform vec3 uLightPos;
uniform vec3 uLightColor;

uniform vec3 uKa, uKd, uKs;
uniform float uShininess;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);
    vec3 viewDir  = normalize(uViewPos - FragPos);

    vec3 ambient = uKa * uLightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uKd * diff * uLightColor;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    vec3 specular = uKs * spec * uLightColor;

    vec3 result = ambient + diffuse + specular;
    result = pow(result, vec3(1.0 / 2.2));
    FragColor = vec4(clamp(result, 0.0, 1.0), 1.0);
}
<br>
<br>
🔸 Purpose
<br>
Implements the Phong reflection model:

<br>
Ambient: constant light.

<br>
Diffuse: based on angle between light and normal.

<br>
Specular: based on viewer’s reflection direction.

<br>
Produces a smooth, shiny rendering of the sphere with visible highlights and shading.

<br>
<br>
🔷 5. shader_util.{h,cpp} – Shader Management (Utility)
#pragma once
#include <glad/glad.h>

GLuint CreateShaderProgram(const char* vertexPath, const char* fragmentPath);
shader_util.cpp (simplified structure)
Reads shader source code from file.

Compiles vertex and fragment shaders.

Links them into a shader program.

Reports compile or link errors to the console.

Used in main_Phong_Shader.cpp as:

shaderProgram = CreateShaderProgram("Phong.vert", "Phong.frag");
<br>
<br>
📌 Result Summary
<br>
A smooth shaded high-resolution sphere is rendered using the Phong lighting model.
<br>
Materials and lighting are parameterized using uniform variables.
<br>
Normal vectors are properly transformed using the normal matrix.
<br>
The scene reacts correctly to light direction, intensity, and viewer position.
<br>
All buffers and shaders are modularized and structured for reuse.


![image](https://github.com/user-attachments/assets/b7748d7c-a368-4a8a-9c90-9256e6c3952e)

