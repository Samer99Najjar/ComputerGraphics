#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

#include "Renderer.h"
#include "InitShader.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>


#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))


Renderer::Renderer() :
	viewport_width(1280),
	viewport_height(720)
{
	InitOpenglRendering();
	
	CreateBuffers(viewport_width, viewport_height);
}

Renderer::~Renderer()
{
	delete[] color_buffer;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width) return;
	if (j < 0) return; if (j >= viewport_height) return;


	color_buffer[INDEX(viewport_width, i, j, 0)] = color.x;
	color_buffer[INDEX(viewport_width, i, j, 1)] = color.y;
	color_buffer[INDEX(viewport_width, i, j, 2)] = color.z;
}

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{

	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	// p1 = first point 
	//p2 = second point
	int my_p1_x = p1.x;
	int my_p1_y = p1.y;
	int my_p2_x = p2.x;
	int my_p2_y = p2.y;
	int x = p1.x;
	int y = p1.y;

	int flag = 0;
	if (p1.x > p2.x) {
		x = p2.x;
		y = p2.y;
		my_p2_x = p1.x;
		my_p2_y = p1.y;
	}

	float delta_x = my_p2_x - x;
	float delta_y = my_p2_y - y;

	float a;

	if (delta_x == 0) {
		flag = 1;
		if (delta_y < 0)
			delta_y = delta_y * (-1);
		while (delta_y != 0) {
			if (y >= my_p2_y) {
				PutPixel(x, y, color);
				y--;

			}
			if (y <= my_p2_y) {
				PutPixel(x, y, color);
				y++;

			}
			delta_y--;
		}


	}
	if (flag == 0) {
		a = delta_y / delta_x;
	}



	if (delta_x < 0)
		delta_x = delta_x * (-1);
	if (delta_y < 0)
		delta_y = delta_y * (-1);
	//int  c = p1.y - delta_x * p1.x;


	if (flag == 0 && a >= 0 && a <= 1) {
		int e = -(delta_x);
		while (x < my_p2_x) {
			if (e >= 0) {
				y = y + 1;
				e = e - 2 * (delta_x);
			}
			PutPixel(x, y, color);
			x = x + 1;
			e = e + 2 * (delta_y);
		}
	}

	if (flag == 0 && a > -1 && a < 0) {
		int  e = -(delta_y);
		while (x <= my_p2_x) {

			if (e >= 0) {
				y = y - 1;
				e = e - 2 * (delta_x);
			}
			PutPixel(x, y, color);
			x = x + 1;
			e = e + 2 * (delta_y);
		}
	}

	if (flag == 0 && a > 1) {

		int e = -(delta_y);
		while (y <= my_p2_y) {

			if (e >= 0) {
				x = x + 1;
				e = e - 2 * (delta_y);
			}
			PutPixel(x, y, color);
			y = y + 1;
			e = e + 2 * (delta_x);
		}
	}



	if (flag == 0 && a <= -1) {
		int  e = (delta_y);
		while (y >= my_p2_y) {

			if (e >= 0) {
				x = x + 1;
				e = e - 2 * (delta_y);
			}
			PutPixel(x, y, color);
			y = y - 1;
			e = e + 2 * (delta_x);
		}
	}


	// TODO: Implement bresenham algorithm

	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenglBuffer(); //Do not remove this line.
	color_buffer = new float[3 * w * h];

	ClearColorBuffer(glm::vec3(0, 0, 0));
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenglRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[] = {
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1 };

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc) + sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(vtc));

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}

void Renderer::CreateOpenglBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width, viewport_height, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewport_width, viewport_height);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width, viewport_height, GL_RGB, GL_FLOAT, color_buffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewport_width; i++)
	{
		for (int j = 0; j < viewport_height; j++)
		{
			PutPixel(i, j, color);
		}
	}

}

void Renderer::ColorObject(const glm::ivec3& p1, const glm::ivec3& const p2, const glm::ivec3& p3, const Scene& scene, const glm::vec3& color, int index) {
	float color1, color2, color3;
	float C, A, B, D, Z;
	glm::vec3 ambientcol = { 0.0,0.0,0.0 }, diffusecol = { 0.0,0.0,0.0 }, speccol = { 0.0,0.0,0.0 };
	color1 = (float)(rand()) / (RAND_MAX);
	color2 = (float)(rand()) / (RAND_MAX);
	color3 = (float)(rand()) / (RAND_MAX);
	int max_x, max_y, min_x, min_y;
	max_x = max(max(p1.x, p2.x), p3.x);
	max_y = max(max(p1.y, p2.y), p3.y);
	min_x = min(min(p1.x, p2.x), p3.x);
	min_y = min(min(p1.y, p2.y), p3.y);
	glm::vec3 face_avg = (p1 + p2 + p3) / 3;
	Scene scene_cam = scene;
	//glm::vec3 lightcolordiffuse, lightspecularcol, lightambientcol;
	Camera& cam = scene_cam.GetActiveCamera();
	Light light = scene.GetLight(0);
	glm::vec3 lightcolor_ambient = glm::vec3(light.ambient_color);
	glm::vec3 lightcolor_diff = glm::vec3(light.diff_color);
	glm::vec3 lightcolor_spec = glm::vec3(light.spec_color);


	if (scene.GetModel(0).allboxes) {
		DrawLine(glm::ivec2(min_x, min_y), glm::ivec2(min_x, max_y), glm::vec3(color1, color2, color3));
		DrawLine(glm::ivec2(min_x, min_y), glm::ivec2(max_x, min_y), glm::vec3(color1, color2, color3));
		DrawLine(glm::ivec2(min_x, max_y), glm::ivec2(max_x, max_y), glm::vec3(color1, color2, color3));
		DrawLine(glm::ivec2(max_x, min_y), glm::ivec2(max_x, max_y), glm::vec3(color1, color2, color3));
	}
	else {
		float zmax = -1 * INFINITY, zmin = INFINITY;
		for (int i = min_x; i <= max_x; i++) {
			for (int j = min_y; j <= max_y; j++) {
				if (test_edge(p1, p2, p3, glm::ivec2(i, j)) == 1) {

					Z = cal_depth(p1, p2, p3, i, j);
					if (zmax < Z)zmax = Z;
					if (zmin > Z)zmin = Z;
				}
			}
		}
		glm::vec3 mynewnormal = glm::vec3{ 0.0,0.0,0.0 };
		glm::vec3 mynewcolor = glm::vec3(0.0, 0.0, 0.0);
		glm::vec3 mynewcolor1 = glm::vec3(0.0, 0.0, 0.0);
		glm::vec3 mynewcolor2 = glm::vec3(0.0, 0.0, 0.0);
		glm::vec3 mynewcolor3 = glm::vec3(0.0, 0.0, 0.0);
		glm::vec4 myvec = { 0,0,0,0 };
		glm::vec3 l = { 0,0,0 };
		float div = 1, teta = 1;
		//color of model =material color;
		glm::vec3 materialcol = color;
		glm::vec3 lightcol = scene.GetLight(0).color;
		glm::vec3 position = scene.GetLight(0).getpos();
		glm::vec3 face_normal = scene.GetActiveModel().face_normal[index];
		face_normal = glm::normalize(face_normal);
		Face tmp = scene.GetActiveModel().GetFace(index);
		glm::vec3 ver1, ver2, ver3;
		glm::vec3 vertrix1_normal = scene.GetActiveModel().ver_normal[tmp.GetVertexIndex(0) - 1];
		glm::vec3 vertrix2_normal = scene.GetActiveModel().ver_normal[tmp.GetVertexIndex(1) - 1];
		glm::vec3 vertrix3_normal = scene.GetActiveModel().ver_normal[tmp.GetVertexIndex(2) - 1];
		myvec = glm::vec4(position.x, position.y, position.z, 1) * scene.GetActiveModel().get_mat();
		myvec /= myvec[3];
		l = glm::normalize(myvec);
		if (scene.GetLight(0).flat) {
			myvec = glm::vec4(position.x, position.y, position.z, 1) * scene.GetActiveModel().get_mat();
			myvec /= myvec[3];
			l = glm::normalize(myvec);
			div = sqrt(l[0] * l[0] + l[1] * l[1] + l[2] * l[2]) * sqrt(face_normal[0] * face_normal[0] + face_normal[1] * face_normal[1] + face_normal[2] * face_normal[2]);
			teta = glm::dot(l, face_normal) / div;
			mynewcolor = glm::vec3(glm::vec3(scene.GetActiveModel().diff_color_model)[0] * lightcolor_diff[0] * teta, glm::vec3(scene.GetActiveModel().diff_color_model)[1] * lightcolor_diff[1] * teta, glm::vec3(scene.GetActiveModel().diff_color_model)[2] * lightcolor_diff[2] * teta);
		}


		if (scene.GetLight(0).specular || scene.GetLight(0).gour) {

			myvec = glm::vec4(position.x, position.y, position.z, 1) * scene.GetActiveModel().get_mat();
			myvec /= myvec[3];
			glm::vec3 l1 = glm::normalize(myvec);
			float div1 = sqrt(l1[0] * l1[0] + l1[1] * l1[1] + l1[2] * l1[2]) * sqrt(vertrix1_normal[0] * vertrix1_normal[0] + vertrix1_normal[1] * vertrix1_normal[1] + vertrix1_normal[2] * vertrix1_normal[2]);
			float teta1 = glm::dot(l1, vertrix1_normal) / div1;
			teta1 = glm::clamp(teta1, (float)0.0, (float)1.0);

			glm::vec3 l2 = glm::normalize(myvec);
			float div2 = sqrt(l2[0] * l2[0] + l2[1] * l2[1] + l2[2] * l2[2]) * sqrt(vertrix2_normal[0] * vertrix2_normal[0] + vertrix2_normal[1] * vertrix2_normal[1] + vertrix2_normal[2] * vertrix2_normal[2]);
			float teta2 = glm::dot(l2, vertrix2_normal) / div2;
			teta2 = glm::clamp(teta2, (float)0.0, (float)1.0);

			glm::vec3 l3 = glm::normalize(myvec);
			float div3 = sqrt(l3[0] * l3[0] + l3[1] * l3[1] + l3[2] * l3[2]) * sqrt(vertrix3_normal[0] * vertrix3_normal[0] + vertrix3_normal[1] * vertrix3_normal[1] + vertrix3_normal[2] * vertrix3_normal[2]);
			float teta3 = glm::dot(l3, vertrix3_normal) / div3;
			teta3 = glm::clamp(teta3, (float)0.0, (float)1.0);

			mynewcolor1 = glm::vec3(glm::vec3(scene.GetActiveModel().diff_color_model)[0] * lightcolor_diff[0] * teta1, glm::vec3(scene.GetActiveModel().diff_color_model)[1] * lightcolor_diff[1] * teta1, glm::vec3(scene.GetActiveModel().diff_color_model)[2] * lightcolor_diff[2] * teta1);
			mynewcolor2 = glm::vec3(glm::vec3(scene.GetActiveModel().diff_color_model)[0] * lightcolor_diff[0] * teta2, glm::vec3(scene.GetActiveModel().diff_color_model)[1] * lightcolor_diff[1] * teta2, glm::vec3(scene.GetActiveModel().diff_color_model)[2] * lightcolor_diff[2] * teta2);
			mynewcolor3 = glm::vec3(glm::vec3(scene.GetActiveModel().diff_color_model)[0] * lightcolor_diff[0] * teta3, glm::vec3(scene.GetActiveModel().diff_color_model)[1] * lightcolor_diff[1] * teta3, glm::vec3(scene.GetActiveModel().diff_color_model)[2] * lightcolor_diff[2] * teta3);
			//cout << "hi";
		}



		ambientcol = glm::vec3(scene.GetActiveModel().ambient_color_model) * lightcolor_ambient;

		glm::vec3 normalp1 = { 0,0,0 }, normalp2 = { 0,0,0 }, normalp3 = { 0,0,0 }, p1v2 = p1, p2v2 = p2, p3v2 = p3;
		glm::vec3 l1 = { 0,0,0 };
		glm::vec3 cam_pos = cam.eye;
		if (scene.GetLight(0).specular) {
			glm::vec4 test = glm::vec4{ vertrix1_normal,1 };
			test = test * scene.GetActiveModel().get_mat();
			test = test / test[3];
			glm::vec4 test1 = glm::vec4{ vertrix2_normal,1 };
			test1 = test1 * scene.GetActiveModel().get_mat();
			test1 = test1 / test1[3];
			glm::vec4 test2 = glm::vec4{ vertrix3_normal,1 };
			test2 = test2 * scene.GetActiveModel().get_mat();
			test2 = test2 / test2[3];
			vertrix1_normal = test;
			vertrix2_normal = test1;
			vertrix3_normal = test2;
			vertrix1_normal.x = vertrix1_normal.x + 1 * (viewport_width / 2);
			vertrix1_normal.y = vertrix1_normal.y + 1 * (viewport_height / 2);
			vertrix2_normal.x = vertrix2_normal.x + 1 * (viewport_width / 2);
			vertrix2_normal.y = vertrix2_normal.y + 1 * (viewport_height / 2);
			vertrix3_normal.x = vertrix3_normal.x + 1 * (viewport_width / 2);
			vertrix3_normal.y = vertrix3_normal.y + 1 * (viewport_height / 2);
			normalp1 = vertrix1_normal + p1v2;
			normalp2 = vertrix2_normal + p2v2;
			normalp3 = vertrix3_normal + p3v2;
			myvec = glm::vec4(position.x, position.y, position.z, 1) * scene.GetActiveModel().get_mat();
			myvec /= myvec[3];
			l1 = glm::normalize(myvec);
			//	 cout << l1[0] << "         " <<l1[1] << "           " << l1[2] << endl;

		}
		for (int i = min_x; i <= max_x; i++) {
			for (int j = min_y; j <= max_y; j++) {
				if (test_edge(p1, p2, p3, glm::ivec2(i, j)) == 1) {

					if (i > min_x + 3 && j > min_y + 3) {

					}
					Z = cal_depth(p1, p2, p3, i, j);

					if (Z > Z_buffer[Z_INDEX(viewport_width, i, j)]) {

						if (i < 0) return; if (i >= viewport_width) return;
						if (j < 0) return; if (j >= viewport_height) return;
						float a = 1 - (200 - Z) / (300), a1 = color[0] * Z / 100, a2 = color[1] * Z / 100, a3 = color[2] * Z / 100;
						Z_buffer[Z_INDEX(viewport_width, i, j)] = Z;
						;
						if (scene.GetLight(0).ambient) {

							PutPixel(i, j, ambientcol);
						}
						if (scene.GetLight(0).diffuse) {
							if (scene.GetLight(0).flat) {
								//	cout << "hhi";
								float fog_end = 1000;
								float fog_start = -10000;
								float f = (fog_end - Z) / (fog_end - fog_start);
								PutPixel(i, j, (1 - f) * glm::vec3{ 0.5,0.5,0.5 } + f * (mynewcolor + ambientcol));

							}
							if (scene.GetLight(0).gour) {
								mynewcolor = color_gro(p1, p2, p3, i, j, mynewcolor1, mynewcolor2, mynewcolor3);
								PutPixel(i, j, mynewcolor + ambientcol);
							}
							if (scene.GetLight(0).phong) {}
						}
						if (scene.GetLight(0).specular) {
							if (scene.GetLight(0).flat) {}
							if (scene.GetLight(0).gour) {}
							if (scene.GetLight(0).phong) {
								mynewnormal = color_gro(p1v2, p2v2, p3v2, i, j, normalp1, normalp2, normalp3);
								mynewnormal = glm::normalize(mynewnormal);

								float div1 = sqrt(l1[0] * l1[0] + l1[1] * l1[1] + l1[2] * l1[2]) * sqrt(mynewnormal[0] * mynewnormal[0] + mynewnormal[1] * mynewnormal[1] + mynewnormal[2] * mynewnormal[2]);
								float teta1 = (l1[0] * mynewnormal[0] + l1[1] * mynewnormal[1] + l1[2] * mynewnormal[2]) / div1;
								teta1 = glm::clamp(teta1, (float)0.0, (float)1.0);
								//	mynewcolor1 = color_gro(p1, p2, p3, i, j, mynewcolor1, mynewcolor2, mynewcolor3);
								mynewcolor1 = lightcolor_diff * teta1 * glm::vec3(scene.GetActiveModel().diff_color_model);
								mynewcolor1 = abs(mynewcolor1);
								glm::vec3 v = cam.eye;
								v = glm::normalize(v);
								//glm::vec3 i_spec = -l + glm::vec3(i, j, Z);
								l = glm::normalize(l);
								glm::vec3 r = -l + 2 * (glm::dot(l, mynewnormal)) * mynewnormal;
								r = glm::normalize(r);
								float div_spec = sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
								teta = (r[0] + r[1] + r[2]) / div_spec;
								teta = glm::clamp(teta, (float)0.0, (float)1.0);
								//	teta = abs(teta);5
						//		cout << teta << endl;
					//		cout << r[0] << "         " << r[1] << "           " << r[2] << endl;
								mynewcolor = lightcolor_spec * teta * glm::vec3(scene.GetActiveModel().spec_color_model);
								//  mynewcolor = abs(mynewcolor);
							   //   cout << mynewcolor[0] << "         " << mynewcolor[1] << "           " << mynewcolor[2] << endl;

								PutPixel(i, j, (mynewcolor + ambientcol + mynewcolor1));
								// cout << mynewcolor[0]+ ambientcol[0]+mynewcolor1[0] << "         " << mynewcolor[1] + ambientcol[1] + mynewcolor1[1] << "           " << mynewcolor[2] + ambientcol[2] + mynewcolor1[2] << endl;
							}
						}
						if (scene.GetLight(0).show_ref) {

							glm::vec3 r = l - 2 * (glm::dot(l, face_normal)) * face_normal;
							r = glm::normalize(r);
							r = glm::vec3(10, 10, 10) * r + glm::vec3(face_avg);
							r = r / div;
							DrawLine(glm::ivec2(face_avg.x, face_avg.y), glm::ivec2(r.x, r.y), glm::vec3(0.0f, 0.0f, 0.0f));
						}

						/*color_buffer[INDEX(viewport_width, i, j, 0)] = color[0];
						color_buffer[INDEX(viewport_width, i, j, 1)] = color[1];
						color_buffer[INDEX(viewport_width, i, j, 2)] = color[2];*/


					}
				}
			}
		}
	}



}

float Renderer::cal_depth(const glm::ivec3& p1, const glm::ivec3& const p2, const glm::ivec3& p3, float i, float j) {

	float Z = 0, A, A1, A2, A3, z1, z2, z3;
	z1 = p1.z;
	z2 = p2.z;
	z3 = p3.z;
	A1 = 0.5 * abs(float(i) * (p2.y - p3.y) + p2.x * (p3.y - float(j)) + p3.x * (float(j) - p2.y));
	A3 = 0.5 * abs(i * (p1.y - p3.y) + p1.x * (p3.y - j) + p3.x * (j - p1.y));
	A2 = 0.5 * abs(i * (p1.y - p2.y) + p2.x * (j - p1.y) + p1.x * (p2.y - j));
	A = 0.5 * abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
	Z = (A1 / A) * z1 + (A2 / A) * z2 + (A3 / A) * z3;
	return Z;

}
glm::vec3 Renderer::color_gro(const glm::vec3& p1, const glm::vec3& const p2, const glm::vec3& p3, float i, float j, const glm::vec3& color1, const glm::vec3& color2, const glm::vec3& color3) {
	glm::vec3 Z, col1, col2, col3;
	col1 = color1;
	col2 = color2;
	col3 = color3;
	float  A, A1, A2, A3, z1, z2, z3;
	z1 = p1.z;
	z2 = p2.z;
	z3 = p3.z;
	A1 = 0.5 * abs(float(i) * (p2.y - p3.y) + p2.x * (p3.y - float(j)) + p3.x * (float(j) - p2.y));
	A3 = 0.5 * abs(i * (p1.y - p3.y) + p1.x * (p3.y - j) + p3.x * (j - p1.y));
	A2 = 0.5 * abs(i * (p1.y - p2.y) + p2.x * (j - p1.y) + p1.x * (p2.y - j));
	A = A1 + A2 + A3;
	//cout << color1[0] << "      " << color1[1] << "        " << color1[2] << endl;
	Z[0] = (A1 / A) * (float)col1[0] + (A2 / A) * (float)col2[0] + (A3 / A) * (float)col3[0];
	Z[1] = (A1 / A) * (float)col1[1] + (A2 / A) * (float)col2[1] + (A3 / A) * (float)col3[1];
	Z[2] = (A1 / A) * (float)col1[2] + (A2 / A) * (float)col2[2] + (A3 / A) * (float)col3[2];
	return Z;

}

int Renderer::test_edge(const glm::ivec2& vert1_4, const glm::ivec2& vert2_4, const glm::ivec2& vert3_4, const glm::ivec2& current) {
	/*if (((vert1_4.x - vert2_4.x) * (current.y - vert1_4.y) - (vert1_4.y - vert2_4.y) * (current.x - vert1_4.x) >= 0)
		&& ((vert2_4.x - vert3_4.x) * (current.y - vert2_4.y) - (vert2_4.y - vert3_4.y) * (current.x - vert2_4.x) >= 0)
		&& ((vert3_4.x - vert1_4.x) * (current.y - vert3_4.y) - (vert3_4.y - vert1_4.y) * (current.x - vert3_4.x) >= 0))
		return 1;*/
	if (((vert1_4.y - vert2_4.y) * (current.x - vert1_4.x) - (vert1_4.x - vert2_4.x) * (current.y - vert1_4.y) >= 0)
		&& ((vert2_4.y - vert3_4.y) * (current.x - vert2_4.x) - (vert2_4.x - vert3_4.x) * (current.y - vert2_4.y) >= 0)
		&& ((vert3_4.y - vert1_4.y) * (current.x - vert3_4.x) - (vert3_4.x - vert1_4.x) * (current.y - vert3_4.y) >= 0))
		return 1;
	return 0;
}

void Renderer::guassian_blur() {
	for (int i = 100; i < viewport_width - 3; i++) {
		for (int j = 100; j < viewport_height - 3; j++) {
			float x1, x2, x3, x4, x5, x6, x7, x8, x9;
			float y1, y2, y3, y4, y5, y6, y7, y8, y9;
			float z1, z2, z3, z4, z5, z6, z7, z8, z9;

			x1 = color_buffer[INDEX(viewport_width, i - 1, j - 1, 0)];
			x2 = color_buffer[INDEX(viewport_width, i - 1, j, 0)];
			x3 = color_buffer[INDEX(viewport_width, i - 1, j + 1, 0)];
			x4 = color_buffer[INDEX(viewport_width, i, j - 1, 0)];
			x5 = color_buffer[INDEX(viewport_width, i, j, 0)];
			x6 = color_buffer[INDEX(viewport_width, i, j + 1, 0)];
			x7 = color_buffer[INDEX(viewport_width, i + 1, j - 1, 0)];
			x8 = color_buffer[INDEX(viewport_width, i + 1, j, 0)];
			x9 = color_buffer[INDEX(viewport_width, i + 1, j + 1, 0)];
			y1 = color_buffer[INDEX(viewport_width, i - 1, j - 1, 1)];
			y2 = color_buffer[INDEX(viewport_width, i - 1, j, 1)];
			y3 = color_buffer[INDEX(viewport_width, i - 1, j + 1, 1)];
			y4 = color_buffer[INDEX(viewport_width, i, j - 1, 1)];
			y5 = color_buffer[INDEX(viewport_width, i, j, 1)];
			y6 = color_buffer[INDEX(viewport_width, i, j + 1, 1)];
			y7 = color_buffer[INDEX(viewport_width, i + 1, j - 1, 1)];
			y8 = color_buffer[INDEX(viewport_width, i + 1, j, 1)];
			y9 = color_buffer[INDEX(viewport_width, i + 1, j + 1, 1)];
			z1 = color_buffer[INDEX(viewport_width, i - 1, j - 1, 2)];
			z2 = color_buffer[INDEX(viewport_width, i - 1, j, 2)];
			z3 = color_buffer[INDEX(viewport_width, i - 1, j + 1, 2)];
			z4 = color_buffer[INDEX(viewport_width, i, j - 1, 2)];
			z5 = color_buffer[INDEX(viewport_width, i, j, 2)];
			z6 = color_buffer[INDEX(viewport_width, i, j + 1, 2)];
			z7 = color_buffer[INDEX(viewport_width, i + 1, j - 1, 2)];
			z8 = color_buffer[INDEX(viewport_width, i + 1, j, 2)];
			z9 = color_buffer[INDEX(viewport_width, i + 1, j + 1, 2)];

			color_buffer[INDEX(viewport_width, i, j, 0)] = 1 / 16 * x1 + 1 / 8 * x2 + 1 / 16 * x3 + 1 / 8 * x4 + 8 / 4 * x5 + 1 / 8 * x6 + 1 / 16 * x7 + 1 / 8 * x8 + 1 / 16 * x9;
			color_buffer[INDEX(viewport_width, i, j, 1)] = 1 / 16 * y1 + 1 / 8 * y2 + 1 / 16 * y3 + 1 / 8 * y4 + 8 / 4 * y5 + 1 / 8 * y6 + 1 / 16 * y7 + 1 / 8 * y8 + 1 / 16 * y9;
			color_buffer[INDEX(viewport_width, i, j, 2)] = 1 / 16 * z1 + 1 / 8 * z2 + 1 / 16 * z3 + 1 / 8 * z4 + 8 / 4 * z5 + 1 / 8 * z6 + 1 / 16 * z7 + 1 / 8 * z8 + 1 / 16 * z9;
		}
	}

}



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


int Renderer::GetViewportWidth() const
{
	return viewport_width;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height;
}

void Renderer::LoadShaders()
{
	colorShader.loadShaders("vshader.glsl", "fshader.glsl");
}

void Renderer::LoadTextures()
{
	if (!texture1.loadTexture("bin\\Debug\\chess.jpg", true))
	{
		texture1.loadTexture("bin\\Release\\crate.jpg", true);
	}
}