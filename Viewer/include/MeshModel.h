#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include "Face.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

class MeshModel
{
public:
	//MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,const std::string& model_name);
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, const std::string& model_name);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	const std::string& GetModelName() const;
	glm::vec3 MeshModel::GetVertice(int index) const;
	int MeshModel::GetVerticesCount() const;
	glm::vec3 MeshModel::GetNormal(int index) const;
	int MeshModel::GetNormalsCount() const;
	bool MeshModel::setVertices(double min, double max);
	glm::vec4 MeshModel::setVertice(glm::vec4 vec);

	glm::mat4x4 MeshModel::get_mat();

	glm::mat4x4 move = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 w_move = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 scale = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 w_scale = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 x_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 y_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 z_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 xw_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 yw_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 zw_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	double sc = 1, w_sc = 1;
	double x_alpha = 0;
	double y_alpha = 0;
	double z_alpha = 0;
	double xw_alpha = 0;
	double yw_alpha = 0;
	double zw_alpha = 0;
	

	std::vector<glm::vec3> face_normal;
	std::vector<int> ver_faces_count;
	std::vector<glm::vec3> ver_normal;
	void calculate_faces_norma();
	void calculate_vertices_norma();
	std::vector<glm::vec2> textureCoords;
	std::vector<Vertex> modelVertices;
	//norma variables
	bool normal_face = false;
	bool normal_vertix = false;

	//min and max
	double min_x, max_x, min_y, max_y, min_z, max_z;
	void find_min_max();


	//axis 
	bool axis = false;
	bool box = false;
	bool allboxes = false;
	glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);

	//variabels model
	double movex = 0;
	double movey = 0;
	double movez = 1;
	double movex_world = 0;
	double movey_world = 0;
	double movez_world = 0;

	double scalex = 1;
	double scaley = 1;
	double scalez = 1;
	double scalexyz = -0.5;
	double scalex_world = 1;
	double scaley_world = 1;
	double scalez_world = 1;
	double scalexyz_world = 1;

	double rotatex = 0;
	double rotatey = 0;
	double rotatez = 0;
	double rotatex_world = 0;
	double rotatey_world = 0;
	double rotatez_world = 0;


	bool local = true;
	bool world = false;
	glm::vec4 ambient_color_model = glm::vec4(1, 1, 1, 1.00f);
	glm::vec4 spec_color_model = glm::vec4(1, 1, 1, 1.00f);
	glm::vec4 diff_color_model = glm::vec4(1, 1, 1, 1.00f);
	GLuint GetVAO() const;
	GLuint vbo;
	GLuint vao;

	const std::vector<Vertex>& GetModelVertices();
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string model_name;

};