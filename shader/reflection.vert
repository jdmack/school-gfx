#version 120

uniform vec3 CameraPosition;
uniform mat3x3 NormalMatrix;
uniform mat4x4 ModelMatrix;

void main()
{
    vec4 position = gl_ModelViewMatrix * gl_Vertex;

	//vec4 camera;
	//camera = gl_ModelViewMatrix * camera;
    //vec3 Reflection = reflect(position.xyz - CameraPosition, normalize(gl_Normal));

    vec3 Reflection = reflect(position.xyz, normalize(gl_Normal));

    gl_TexCoord[0].stp = vec3(Reflection.x, Reflection.yz);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;


    //vec3 Normal = NormalMatrix * gl_Normal;
    //vec4 Position = ModelMatrix * gl_Vertex;
    //vec3 Reflection = reflect(Position.xyz - CameraPosition, normalize(Normal));

    //gl_TexCoord[0].stp = vec3(Reflection.x, -Reflection.yz);
    //gl_Position = gl_ModelViewProjectionMatrix * Position;
}
