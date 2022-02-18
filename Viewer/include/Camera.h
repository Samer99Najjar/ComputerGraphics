#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
class Camera
{
public:
	Camera();
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;

	void Set_orthorper_mat();
	glm::mat4x4 Camera::get_mat();
	glm::mat4x4  get_orthoper();

	glm::vec3& eye = glm::vec3(0, 0, 1);
	void Seteye(double eye1, double eye2, double eye3);
	void incremntal_calculate();
	glm::mat4x4 move = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 w_move = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 x_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 y_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 z_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 xw_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 yw_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 zw_rotate = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 orthographic_mat = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 perspective_mat = glm::mat4x4(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glm::mat4x4 inverse_mat = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4x4 incremantal_mat;

	bool orth_per;
	bool axis_wind = false;

	/*double x_alpha = 0;
	double y_alpha = 0;
	double z_alpha = 0;
	double xw_alpha = 0;
	double yw_alpha = 0;
	double zw_alpha = 0;*/

	double left_ortho = -1;
	double right_ortho = 1;
	double up_ortho = 1;
	double down_ortho = -1;

	int is_inc_on = 0;


	double movex = 0;
	double movey = 0;
	double movez = 0;
	double movex_world = 0;
	double movey_world = 0;
	double movez_world = 0;

	double rotatex = 0;
	double rotatey = 0;
	double rotatez = 0;
	double rotatex_world = 0;
	double rotatey_world = 0;
	double rotatez_world = 0;

	double left_per = -500;
	double right_per = 500;
	double up_per = 200;
	double down_per = -200;

	double nearcam = 3;
	double farcam = 200;
	double fovycam = -0.000146;

	double eye1 = 0;
	double eye2 = 0;
	double eye3 = 1;

	bool iscam_trans = false;
	bool local_cam = true;



private:
	glm::mat4x4 view_transformation;
	glm::mat4x4 projection_transformation;
};