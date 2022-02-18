#include "MeshModel.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <glm/gtc/matrix_transform.hpp>


//MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
//	faces(faces),
//	vertices(vertices),
//	normals(normals),
//	model_name(model_name),
//	color(0, 0, 0)
//
//{
//
//	calculate_faces_norma();
//	calculate_vertices_norma();
//	find_min_max();
//
//	/*float color1, color2, color3;
//	color1 = (float)(rand()) / (RAND_MAX);
//	color2 = (float)(rand()) / (RAND_MAX);
//	color3 = (float)(rand()) / (RAND_MAX);
//	color = glm::vec3(color1, color2, color3);*/
//	std::random_device rd;
//	std::mt19937 mt(rd());
//	std::uniform_real_distribution<double> dist(0, 1);
//	color = glm::vec3(dist(mt), dist(mt), dist(mt));
//
//	modelVertices.reserve(3 * faces.size());
//	for (int i = 0; i < faces.size(); i++)
//	{
//		Face currentFace = faces.at(i);
//		for (int j = 0; j < 3; j++)
//		{
//			int vertexIndex = currentFace.GetVertexIndex(j) - 1;
//
//			Vertex vertex;
//			vertex.position = vertices[vertexIndex];
//			vertex.normal = normals[vertexIndex];
//
//			if (textureCoords.size() > 0)
//			{
//				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
//				vertex.textureCoords = textureCoords[textureCoordsIndex];
//				
//			}
//
//			modelVertices.push_back(vertex);
//		}
//	}
//	glGenVertexArrays(1, &vao);
//	glGenBuffers(1, &vbo);
//
//	glBindVertexArray(vao);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(Vertex), &modelVertices[0], GL_STATIC_DRAW);
//
//	// Vertex Positions
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	// Normals attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	// Vertex Texture Coords
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	// unbind to make sure other code does not change it somewhere else
//	glBindVertexArray(0);
//	
//
//}
MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, const std::string& model_name) :
	faces(faces),
	vertices(vertices),
	normals(normals),
	model_name(model_name),
	color(0, 0, 0)

{

	calculate_faces_norma();
	calculate_vertices_norma();
	find_min_max();

	/*float color1, color2, color3;
	color1 = (float)(rand()) / (RAND_MAX);
	color2 = (float)(rand()) / (RAND_MAX);
	color3 = (float)(rand()) / (RAND_MAX);
	color = glm::vec3(color1, color2, color3);*/
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, 1);
	color = glm::vec3(dist(mt), dist(mt), dist(mt));

	modelVertices.reserve(3 * faces.size());
	for (int i = 0; i < faces.size(); i++)
	{
		Face currentFace = faces.at(i);
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = currentFace.GetVertexIndex(j) - 1;

			Vertex vertex;
			vertex.position = vertices[vertexIndex];
			vertex.normal = normals[vertexIndex];

			if (textureCoords.size() > 0)
			{
			
				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
				vertex.textureCoords = textureCoords[textureCoordsIndex];
			
				//float theta = (atan2(vertex.position.z, vertex.position.x)) +3.14;
				vertex.textureCoords.x = vertex.position.x;
				vertex.textureCoords.y = vertex.position.y;
			}

			modelVertices.push_back(vertex);
		}
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(Vertex), &modelVertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);


}

MeshModel::~MeshModel()
{
}

const Face& MeshModel::GetFace(int index) const
{
	return faces[index];
}

int MeshModel::GetFacesCount() const
{
	return faces.size();
}

glm::vec3 MeshModel::GetVertice(int index) const
{
	return vertices[index];
}


bool MeshModel::setVertices(double min, double max) {
	int size = GetVerticesCount(), i;
	min = abs(min);
	double ratio = (max + min) * 1.7 / 1000;
	for (i = 0; i < size; i++) {
		/*vertices[i][0] = (((vertices[i][0] + min) * ratio) + 500);
		vertices[i][1] = (((vertices[i][1] + min) * ratio)+100);
		vertices[i][2] = ((vertices[i][2] + min) * ratio)+200;*/
		vertices[i][0] += 700;
		vertices[i][1] += 300;
		vertices[i][2] += 300;

	}
	return true;

}
glm::vec4 MeshModel::setVertice(glm::vec4 vec) {
	vec[0] += 700;
	vec[1] += 300;
	vec[2] += 300;
	return vec;

}

int MeshModel::GetVerticesCount() const
{
	return vertices.size();
}

glm::vec3 MeshModel::GetNormal(int index) const
{
	return normals[index];
}

int MeshModel::GetNormalsCount() const
{
	return normals.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name;
}
glm::mat4x4 MeshModel::get_mat() {

	return w_move * w_scale * xw_rotate * yw_rotate * zw_rotate * move * x_rotate * y_rotate * z_rotate * scale;
	//return w_move * w_scale * xw_rotate * yw_rotate * zw_rotate * x_rotate * y_rotate * z_rotate * move* scale;//move
}
void MeshModel::calculate_vertices_norma() {
	for (int i = 0; i < vertices.size(); i++)
	{
		ver_normal[i] /= ver_faces_count[i];
	}
}

void MeshModel::calculate_faces_norma()
{
	ver_faces_count = std::vector<int>(vertices.size(), 0);
	ver_normal = std::vector<glm::vec3>(vertices.size(), glm::vec3(0, 0, 0));

	int size = faces.size();

	for (int i = 0; i < size; i++)
	{
		Face face = faces[i];
		int face_index0 = face.GetVertexIndex(0) - 1, face_index1 = face.GetVertexIndex(1) - 1, face_index2 = face.GetVertexIndex(2) - 1;

		glm::vec4 face_vec = glm::vec4(face_index0, face_index1, face_index2, 1);
		face_vec = face_vec * w_move * w_scale * xw_rotate * yw_rotate * zw_rotate * move * x_rotate * y_rotate * z_rotate * scale;
		//face_index0 = face_vec[0]/face_vec[3];
		//face_index1 = face_vec[1];
		//face_index2 = face_vec[2];

		glm::vec3 vec21 = vertices[face_index1] - vertices[face_index0];//vec-vec1
		glm::vec3 vec31 = vertices[face_index2] - vertices[face_index0];//vec3-vec1

		glm::vec3 normal = glm::vec3(vec21[1] * vec31[2] - vec21[2] * vec31[1], vec21[2] * vec31[0] - vec21[0] * vec31[2], vec21[0] * vec31[1] - vec21[1] * vec31[0]);

		float norma = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
		normal /= norma;

		face_normal.push_back(normal);

		ver_faces_count[face_index0]++;
		ver_faces_count[face_index1]++;
		ver_faces_count[face_index2]++;

		ver_normal[face_index0] += normal;
		ver_normal[face_index1] += normal;
		ver_normal[face_index2] += normal;
	}



}

void MeshModel::find_min_max() {
	glm::vec3 first_p = vertices[0];
	min_x = first_p[0], max_x = first_p[0], min_y = first_p[1], max_y = first_p[1], min_z = first_p[2], max_z = first_p[2];
	int size = faces.size();
	for (int i = 0; i < size; i++) {
		Face tmp = faces[i];
		for (int j = 0; j < 3; j++) {
			glm::vec3 ver = vertices[faces[i].GetVertexIndex(j) - 1];
			min_x = min_x < ver[0] ? min_x : ver[0];
			max_x = max_x > ver[0] ? max_x : ver[0];
			min_y = min_y < ver[1] ? min_y : ver[1];
			max_y = max_y > ver[1] ? max_y : ver[1];
			min_z = min_z < ver[2] ? min_z : ver[2];
			max_z = max_z > ver[2] ? max_z : ver[2];
		}
	}
}

GLuint MeshModel::GetVAO() const
{
	return vao;
}
const std::vector<Vertex>& MeshModel::GetModelVertices()
{
	return modelVertices;
}