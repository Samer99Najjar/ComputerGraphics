# Assignment 3 Report


Part 1:

first of all the function create a texture and vertex array and then it creats a buffer afterwards we  identify a bufffer and

make it the buffer we use after it we allocate memory on the gpu of the size of the vertexes and texture 

afterwards we copy the vertexes and the texture to the correct place in the buffer after that we load and compile the shaders and 

set the program  then we set the program where to look in the texture and vertex position  and then we pass the texture to the program

and it draw it on the screen 

Part 3: vertex shader:
```
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(model * vec4(pos, 1.0f));
	fragNormal = mat3(model) * normal;

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	fragTexCoords = texCoords;

	// This is an internal OpenGL variable, we must set a value to this variable
	gl_Position =   view *  model * vec4(pos, 1.0f);
}

```

Part 4: Note: this is the code after adding phong shading 
```
#version 330 core

struct Material
{
	sampler2D textureMap;
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
	
	 vec3 diffusecol= difcol* (dot( normalize(textureColor),normalize(light_pos)))*difcol_mat;
	// calculate spec

	vec3 V= normalize(cam_pos);
	vec3 R= normalize(light_pos)-2* dot(normalize(light_pos),normalize(textureColor))*normalize(textureColor);

	vec3 specularlight=specol* dot(V,R)*specol_mat;


	
	frag_color = vec4(1,0,0,1);
}
```
Part 5:

```
void Renderer::Render(const Scene& scene)
{

	Scene scene_cam = scene;

	Camera& cam = scene_cam.GetActiveCamera();
	int dol_vertices_count, size_model_faces;
	
	for (int i_model = 0; i_model < scene.GetModelCount(); i_model++) {
		MeshModel my_model = scene.GetModel(i_model);

		colorShader.use();
		colorShader.setUniform("model", my_model.get_mat());
		colorShader.setUniform("view", cam.get_mat());
		colorShader.setUniform("projection", cam.get_orthoper());

		colorShader.setUniform("ambcol", glm::vec3(scene.GetLight(0).ambient_color));
		colorShader.setUniform("difcol", glm::vec3(scene.GetLight(0).diff_color));
		colorShader.setUniform("specol", glm::vec3(scene.GetLight(0).spec_color));
		colorShader.setUniform("ambcol_mat", glm::vec3(my_model.ambient_color_model));
		colorShader.setUniform("difcol_mat", glm::vec3(my_model.diff_color_model));
		colorShader.setUniform("specol_mat", glm::vec3(my_model.spec_color_model));
		colorShader.setUniform("light_pos", (scene.GetLight(0).position));
		colorShader.setUniform("cam_pos", glm::vec3{ 0,0,1 });


		colorShader.setUniform("material.textureMap", 0);

		texture1.bind(0);

		// Drag our model's faces (triangles) in fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(my_model.GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, my_model.GetModelVertices().size());
		glBindVertexArray(0);

		// Unset 'texture1' as the active texture at slot #0
		texture1.unbind(0);

		colorShader.setUniform("color", glm::vec3(0, 0, 0));

		// Drag our model's faces (triangles) in line mode (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(my_model.GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, my_model.GetModelVertices().size());
		glBindVertexArray(0);




	}
	//guassian_blur();

}
```
Part 6:


![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/phong1.PNG)

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/phong22.PNG)

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/phong3.PNG)

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/phong4.PNG)

Part7:

texture:

![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/texture.PNG)
here i implemented texture planar and got this result 
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/texturePlanar.PNG)

Part8:

here i did toon shading and here is the result of it
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-coding-machines/blob/master/Assignment3Report/toonshading.PNG)