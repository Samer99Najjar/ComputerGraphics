#version 330 core

struct Material
{
	sampler2D textureMap;
	sampler2D normalMap;
	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
};

// We set this field's properties from the C++ code
uniform Material material;
uniform vec3 ambcol;
uniform vec3 difcol;
uniform vec3 specol;
uniform vec3 ambcol_mat;
uniform vec3 difcol_mat;
uniform vec3 specol_mat;
uniform vec3 light_pos;
uniform vec3 cam_pos;


// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;


// The final color of the fragment (pixel)
out vec4 frag_color;

void main()
{
 	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	
	//calculate amb color
	  vec3 ambientcol= ambcol *ambcol_mat;
	// calculate diffuse color
	
	float shadinglevel;
	vec4 color;
	shadinglevel = dot(light_pos,fragNormal);
	shadinglevel= floor(shadinglevel*100)/100 ;

	 vec3 diffusecol= difcol* (shadinglevel)*difcol_mat;
	// calculate spec

	vec3 V= normalize(cam_pos);

	vec3 R= normalize(light_pos)-2* dot(normalize(light_pos),normalize(textureColor))*normalize(textureColor);
	shadinglevel = dot(light_pos,R);
	shadinglevel= floor(shadinglevel*100)/100 ;
	vec3 specularlight=specol* shadinglevel*specol_mat;


		frag_color = vec4(textureColor,1);
	
//	frag_color = vec4(ambientcol+diffusecol+specularlight,1);

}
