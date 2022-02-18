#include "Camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


Camera::Camera()
{
	orth_per = true;

}

Camera::~Camera()
{

}

const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation;
}

const glm::mat4x4& Camera::GetViewTransformation() const
{
	return view_transformation;
}
void Camera::incremntal_calculate() {
	glm::mat4x4 translate_mat = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	rotatex += 5;
	translate_mat[3][0] = rotatex;
	translate_mat[3][1] = rotatey;
	translate_mat[3][2] = rotatez;
	inverse_mat = inverse_mat * glm::inverse(translate_mat);
}

void Camera::Set_orthorper_mat()
{

	if (orth_per) {
		inverse_mat = w_move * xw_rotate * yw_rotate * zw_rotate * move * x_rotate * y_rotate * z_rotate;
		orthographic_mat = glm::ortho(left_ortho, right_ortho, down_ortho, up_ortho);
	}
	else {
		double aspect = 1280.0 / 720.0;
		move[3][2] = movez - 600;
		inverse_mat = w_move * xw_rotate * yw_rotate * zw_rotate * move * x_rotate * y_rotate * z_rotate;
		move[3][2] = movez + 600;
		perspective_mat = glm::perspective(fovycam, aspect, nearcam, farcam);


		/*perspective_mat[0][0] = 2 * Near /  (right_per - left_per);
		perspective_mat[1][1] = 2*Near / (up_per-down_per);
		perspective_mat[2][1] = (up_per + down_per) / (up_per - down_per);
		perspective_mat[2][0] = (right_per + left_per) / (right_per - left_per);
		perspective_mat[2][2] = -(Far + Near) / (Far - Near);
		perspective_mat[3][2] = -(2*Far*Near)/(Far-Near);
		perspective_mat[2][3] = -1;*/

		/*float tanfovy = tan(float((3.14 * fovy) / 180) / 2.0f);
		perspective_mat[0][0] = 2 * Near /  (tanfovy*(right_per - left_per));
		perspective_mat[1][1] = Near / (tanfovy * (up_per - down_per));
		perspective_mat[2][0] = (right_per + left_per) / (right_per - left_per);
		perspective_mat[2][1] = (up_per + down_per) / (up_per - down_per);
		perspective_mat[2][2] = -(Far + Near) / (Far - Near);
		perspective_mat[2][3] = -1;
		perspective_mat[3][2] = -(2.0f * Far * Near) / (Far - Near);
		perspective_mat[3][3] = 1;*/
		/*std::cout << glm::to_string(perspective_mat) << std::endl;*/


		int x = 5;


		/*perspective_mat[0][0] = 2 * Near /  (right_per - left_per);
		perspective_mat[0][2] = (right_per+left_per) /  (right_per - left_per);
		perspective_mat[1][1] = 2*Near / (up_per-down_per);
		perspective_mat[1][2] = (up_per + down_per) / (up_per - down_per);
		perspective_mat[2][2] = -(Far + Near) / (Far - Near);
		perspective_mat[2][3] = -(2*Far*Near)/(Far-Near);
		perspective_mat[3][2] = -1;*/
	}
}

glm::mat4x4  Camera::get_orthoper() {
	if (orth_per)return orthographic_mat;
	else 	return perspective_mat;


}

glm::mat4x4 Camera::get_mat()
{

	return get_orthoper() * glm::lookAt(eye, glm::vec3{ 0,0,0 }, glm::vec3{ 0,1,0 }) * inverse_mat;
	//return w_move * xw_rotate * yw_rotate * zw_rotate * move * x_rotate * y_rotate * z_rotate;
	//return w_move  * xw_rotate * yw_rotate * zw_rotate * x_rotate * y_rotate * z_rotate * move;//move
}

void Camera::Seteye(double eye1, double eye2, double eye3)
{
	eye[0] = eye1;
	eye[1] = eye2;
	eye[2] = eye3;

}