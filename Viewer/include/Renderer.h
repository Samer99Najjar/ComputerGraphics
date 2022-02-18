#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
class Renderer
{
public:
	ShaderProgram lightShader;
	ShaderProgram colorShader;
	Texture2D texture1;
	Renderer();
	//Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	int viewport_width;
	int viewport_height;
	void ColorObject(const glm::ivec3& vert1_4, const glm::ivec3& const vert2_4, const glm::ivec3& vert3_4, const Scene& scene, const glm::vec3& color, int index);
	float cal_depth(const glm::ivec3& p1, const glm::ivec3& const p2, const glm::ivec3& p3, float i, float j);
	int test_edge(const glm::ivec2& vert1_4, const  glm::ivec2& vert2_4, const glm::ivec2& vert3_4, const glm::ivec2& current);

	void Renderer::Draw_BoundingRectangle(const glm::ivec3& ver1, const glm::ivec3& const ver2, const glm::ivec3& ver3);
	glm::vec3 Renderer::color_gro(const glm::vec3& p1, const glm::vec3& const p2, const glm::vec3& p3, float i, float j, const glm::vec3& color1, const glm::vec3& color2, const glm::vec3& color3);
	void guassian_blur();
	void LoadShaders();
	void LoadTextures();
private:
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);

	void CreateBuffers(int w, int h);
	void CreateOpenglBuffer();
	void InitOpenglRendering();

	float* color_buffer;
	float* Z_buffer;

	GLuint gl_screen_tex;
	GLuint gl_screen_vtc;
};