#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>


#include <stdio.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"


/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
//here we can change the start color of the background
glm::vec4 clear_color = glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);

//modle variables
//static double x_move = 0;
//static double y_move = 0;
//static double z_move = 0;
//static double xw_move = 0;
//static double yw_move = 0;
//static double zw_move = 0;
//static double x_scaling = 1;
//static double y_scaling = 1;
//static double z_scaling = 1;
//static double scale = 1;
//static double xw_scaling = 1;
//static double yw_scaling = 1;
//static double zw_scaling = 1;
//static double w_scale = 1;
//
//static double x_rotate = 0;
//static double y_rotate = 0;
//static double z_rotate = 0;
//static double xw_rotate = 0;
//static double yw_rotate = 0;
//static double zw_rotate = 0;
//
//
//static bool local = true;

//********

//cam variables
//
//static double x_move_cam = 0;
//static double y_move_cam = 0;
//static double z_move_cam = 0;
//static double xw_move_cam = 0;
//static double yw_move_cam = 0;
//static double zw_move_cam = 0;
//
//static double x_rotate_cam = 0;
//static double y_rotate_cam = 0;
//static double z_rotate_cam = 0;
//static double xw_rotate_cam = 0;
//static double yw_rotate_cam = 0;
//static double zw_rotate_cam = 0;
//
//static double left_orth_cam = -1;
//static double right_orth_cam = 1;
//static double up_orth_cam = 1;
//static double down_orth_cam = -1;
//
//static double left_per_cam = -500;
//static double right_per_cam = 500;
//static double up_per_cam = 200;
//static double down_per_cam = -200;
//
//static double near_cam = 3;
//static double far_cam = 200;
//static double fovy_cam = -0.000146;
//
//
//static double eye1 = 0;
//static double eye2 = 0;
//static double eye3 = 1;
//
//static int number_of_cameras=1;
//static bool iscam_trans = false;
//static bool local_cam = true;
int number_of_cameras = 1;
static bool iscam_trans = false;


GLFWwindow* window;

//*******



//***********
//window size
static double weidth_size = 1280;
static double hight_size = 720;

//axis buttons
static bool axis_model = false;
static bool axis_window = false;
static bool bounding_box = false;
static bool boxes_around_triangles = false;
static bool normal_face = false;
static bool normal_vertix = false;

static bool ambient = true, diffuse = false, specular = false,diffuse_flat=false,diffuse_gour=false,show_ref=false;
static bool flat = false, gour = false, phong = false;

char* windowTitle = "OpenGL Demo";


/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
ImGuiIO* imgui;
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);
void glfw_OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
void glfw_OnFramebufferSize(GLFWwindow* window, int width, int height);
bool Setup(int windowWidth, int windowHeight, const char* windowName);
ImGuiIO& SetupImgui(GLFWwindow* window);
/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

int main(int argc, char** argv)
{
	int windowWidth = 1280, windowHeight = 720;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;
	//if (!Setup(windowWidth, windowHeight, windowTitle))
	//{
	//	std::cerr << "Setup failed" << std::endl;
	//	return -1;
	//}
//

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glEnable(GL_DEPTH_TEST);
	Renderer renderer ;
	renderer.LoadShaders();
	renderer.LoadTextures();
	Scene scene = Scene();

	/*******************************my code start here**************************************************/


	/*cam*/
	shared_ptr <Camera> mycam = std::make_shared<Camera>();
	scene.AddCamera(mycam);
	scene.active_camera_index = 0;

	shared_ptr<Light> mylight = std::make_shared<Light>(glm::vec3(1, 1, 1), glm::vec3(1,1, 1));
	scene.AddLight(mylight);


	//shared_ptr<material> mymaterial = std::make_shared<material>(glm::vec3(1, 1, 1));
	//scene.Addmaterial(mymaterial);
	/**/




	//assignment 1.b s3ef 1
	scene.AddModel(Utils::LoadMeshModel("C:\\Users\\win10\\source\\repos\\computer-graphics-2022-coding-machines\\Data\\teapotT.obj"));
	//MeshModel my_mesh = scene.GetModel(0);
	//my_mesh.color = glm::vec3(1.f, 1.f, 1.f);
	//int dol_faces_count = my_mesh.GetFacesCount(), i;
	//int dol_vertices_count = my_mesh.GetVerticesCount();
	//int dol_normals_count = my_mesh.GetNormalsCount();


	/**************************************finish here**************************************************/
	//iscam_trans = true;
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		StartFrame();
		
		DrawImguiMenus(io, scene);
		ImGui::Render();
		
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderFrame(window, scene, renderer, io);
	}


	glfwTerminate();


	return 0;
}

//bool Setup(int windowWidth, int windowHeight, const char* windowName)
//{
//	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, windowName);
//	if (!window)
//	{
//		std::cerr << "Window setup failed" << std::endl;
//		return false;
//	}
//
//	imgui = &SetupImgui(window);
//
//	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
//	glEnable(GL_DEPTH_TEST);
//
//	return true;
//}
//ImGuiIO& SetupImgui(GLFWwindow* window)
//{
//	IMGUI_CHECKVERSION();
//	ImGui::CreateContext();
//	ImGuiIO& io = ImGui::GetIO();
//	(void)io;
//
//	ImGui_ImplGlfw_InitForOpenGL(window, true);
//	ImGui_ImplOpenGL3_Init();
//
//	// Setup style
//	ImGui::StyleColorsDark();
//
//	glfwSetScrollCallback(window, glfw_OnMouseScroll);
//
//	return io;
//}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	//scene.GetActiveCamera().Setper(fovy, near_cam, far_cam, up_cam, down_cam, right_cam, left_cam);
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		// TODO: Set new aspect ratio
		renderer.viewport_height = frameBufferHeight;
		renderer.viewport_width = frameBufferWidth;
	}

	MeshModel& active_model = scene.GetActiveModel();
	//active_model.color = glm::vec3(1.f, 1.f, 1.f);
	Camera& active_cam = scene.GetActiveCamera();

	if (!io.WantCaptureKeyboard)
	{

		// TODO: Handle keyboard events here

		if (io.KeysDown[88]) {
			if (iscam_trans)
			{
				active_cam.rotatex += 3;
				float alpha120 = glm::radians(active_cam.rotatex);
				active_cam.x_rotate[1][1] = cos(alpha120);
				active_cam.x_rotate[1][2] = sin(alpha120) * -1;
				active_cam.x_rotate[2][1] = sin(alpha120);
				active_cam.x_rotate[2][2] = cos(alpha120);

			}

		}
		if (io.KeysDown[89]) {
			if (iscam_trans)
			{
				active_cam.rotatey += 3;
				float alpha120 = glm::radians(active_cam.rotatey);
				active_cam.y_rotate[0][0] = cos(alpha120);
				active_cam.y_rotate[0][2] = sin(alpha120);
				active_cam.y_rotate[2][0] = sin(alpha120) * -1;
				active_cam.y_rotate[2][2] = cos(alpha120);

			}

		}
		if (io.KeysDown[90]) {
			if (iscam_trans)
			{
				active_cam.rotatez += 3;
				float alpha120 = glm::radians(active_cam.rotatez);
				active_cam.z_rotate[0][0] = cos(alpha120);
				active_cam.z_rotate[0][1] = sin(alpha120) * -1;
				active_cam.z_rotate[1][0] = sin(alpha120);
				active_cam.z_rotate[1][1] = cos(alpha120);

			}

		}
		if (io.KeysDown[65])
		{
			active_model.move[3][0] -= 5;
			active_model.movex -= 5;
			// A key is left
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
		if (io.KeysDown[68])

		{
			active_model.move[3][0] += 5;
			active_model.movex += 5;
			// D key is right
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
		if (io.KeysDown[87])
		{
			active_model.move[3][1] += 5;
			active_model.movey += 5;
			// W key is up
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
		if (io.KeysDown[83])
		{
			active_model.move[3][1] -= 5;
			active_model.movey -= 5;
			// S key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}

	}
	else {
		/*///////*/


		if (iscam_trans) {
			active_cam.move[3][0] = active_cam.movex;
			active_cam.move[3][1] = active_cam.movey;
			//-540 satir 333
			active_cam.move[3][2] = active_cam.movez;
			active_cam.w_move[3][0] = active_cam.movex_world;
			active_cam.w_move[3][1] = active_cam.movey_world;
			active_cam.w_move[3][2] = active_cam.movez_world;

			double alpha, alpha1, alpha2;

			alpha1 = glm::radians(active_cam.rotatex);
			active_cam.x_rotate[1][1] = cos(alpha1);
			active_cam.x_rotate[1][2] = sin(alpha1) * -1;
			active_cam.x_rotate[2][1] = sin(alpha1);
			active_cam.x_rotate[2][2] = cos(alpha1);
			alpha2 = glm::radians(active_cam.rotatey);
			active_cam.y_rotate[0][0] = cos(alpha2);
			active_cam.y_rotate[0][2] = sin(alpha2);
			active_cam.y_rotate[2][0] = sin(alpha2) * -1;
			active_cam.y_rotate[2][2] = cos(alpha2);
			alpha = glm::radians(active_cam.rotatez);
			active_cam.z_rotate[0][0] = cos(alpha);
			active_cam.z_rotate[0][1] = sin(alpha) * -1;
			active_cam.z_rotate[1][0] = sin(alpha);
			active_cam.z_rotate[1][1] = cos(alpha);
			/**/
			alpha = glm::radians(active_cam.rotatex_world);
			active_cam.xw_rotate[1][1] = cos(alpha);
			active_cam.xw_rotate[1][2] = sin(alpha) * -1;
			active_cam.xw_rotate[2][1] = sin(alpha);
			active_cam.xw_rotate[2][2] = cos(alpha);
			alpha = glm::radians(active_cam.rotatey_world);
			active_cam.yw_rotate[0][0] = cos(alpha);
			active_cam.yw_rotate[0][2] = sin(alpha);
			active_cam.yw_rotate[2][0] = sin(alpha) * -1;
			active_cam.yw_rotate[2][2] = cos(alpha);
			alpha = glm::radians(active_cam.rotatez_world);
			active_cam.zw_rotate[0][0] = cos(alpha);
			active_cam.zw_rotate[0][1] = sin(alpha) * -1;
			active_cam.zw_rotate[1][0] = sin(alpha);
			active_cam.zw_rotate[1][1] = cos(alpha);
			/*active_cam.x_alpha = x_rotate_cam;
			active_cam.y_alpha = y_rotate_cam;
			active_cam.z_alpha = z_rotate_cam;
			active_cam.xw_alpha = xw_rotate_cam;
			active_cam.yw_alpha = yw_rotate_cam;
			active_cam.zw_alpha = zw_rotate_cam;
			active_cam.up_ortho = up_orth_cam;
			active_cam.down_ortho = down_orth_cam;
			active_cam.left_ortho = left_orth_cam;
			active_cam.right_ortho = right_orth_cam;
			active_cam.right_per1 = right_per_cam;
			active_cam.left_per1 = left_per_cam;
			active_cam.down_per1 = down_per_cam;
			active_cam.up_per1 = up_per_cam;
			active_cam.far_per1 = far_cam;
			active_cam.near_per1 = near_cam;
			active_cam.fovy_per1 = fovy_cam;*/

			active_cam.Set_orthorper_mat();
			active_cam.Seteye(active_cam.eye1, active_cam.eye2, active_cam.eye3);
		}
		else {
			active_model.move[3][0] = active_model.movex;
			active_model.move[3][1] = active_model.movey;
			active_model.move[3][2] = active_model.movez;
			active_model.w_move[3][0] = active_model.movex_world;
			active_model.w_move[3][1] = active_model.movey_world;
			active_model.w_move[3][2] = active_model.movez_world;

			active_model.scale[0][0] = active_model.scalex + active_model.scalexyz;
			active_model.scale[1][1] = active_model.scaley + active_model.scalexyz;
			active_model.scale[2][2] = active_model.scalez + active_model.scalexyz;
			active_model.w_scale[0][0] = active_model.scalex_world;
			active_model.w_scale[1][1] = active_model.scaley_world;
			active_model.w_scale[2][2] = active_model.scalez_world;

			double alpha = glm::radians(active_model.rotatex);
			active_model.x_rotate[1][1] = cos(alpha);
			active_model.x_rotate[1][2] = sin(alpha) * -1;
			active_model.x_rotate[2][1] = sin(alpha);
			active_model.x_rotate[2][2] = cos(alpha);
			alpha = glm::radians(active_model.rotatey);
			active_model.y_rotate[0][0] = cos(alpha);
			active_model.y_rotate[0][2] = sin(alpha);
			active_model.y_rotate[2][0] = sin(alpha) * -1;
			active_model.y_rotate[2][2] = cos(alpha);
			alpha = glm::radians(active_model.rotatez);
			active_model.z_rotate[0][0] = cos(alpha);
			active_model.z_rotate[0][1] = sin(alpha) * -1;
			active_model.z_rotate[1][0] = sin(alpha);
			active_model.z_rotate[1][1] = cos(alpha);
			/**/
			alpha = glm::radians(active_model.rotatex_world);
			active_model.xw_rotate[1][1] = cos(alpha);
			active_model.xw_rotate[1][2] = sin(alpha) * -1;
			active_model.xw_rotate[2][1] = sin(alpha);
			active_model.xw_rotate[2][2] = cos(alpha);
			alpha = glm::radians(active_model.rotatey_world);
			active_model.yw_rotate[0][0] = cos(alpha);
			active_model.yw_rotate[0][2] = sin(alpha);
			active_model.yw_rotate[2][0] = sin(alpha) * -1;
			active_model.yw_rotate[2][2] = cos(alpha);
			alpha = glm::radians(active_model.rotatez_world);
			active_model.zw_rotate[0][0] = cos(alpha);
			active_model.zw_rotate[0][1] = sin(alpha) * -1;
			active_model.zw_rotate[1][0] = sin(alpha);
			active_model.zw_rotate[1][1] = cos(alpha);

			active_model.sc = active_model.scalexyz;
			active_model.w_sc = active_model.scalexyz_world;
			active_model.x_alpha = active_model.rotatex;
			active_model.y_alpha = active_model.rotatey;
			active_model.z_alpha = active_model.rotatez;
			active_model.xw_alpha = active_model.rotatex_world;
			active_model.yw_alpha = active_model.rotatey_world;
			active_model.zw_alpha = active_model.rotatez_world;
		}




		/*//////*/
	}

	if (!io.WantCaptureMouse)
	{

		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			if (!iscam_trans) {
				active_model.scale[0][0] += 1;
				active_model.scale[1][1] += 1;
				active_model.scale[2][2] += 1;
				active_model.scalexyz = active_model.scale[0][0];

			}
			if (iscam_trans)
				active_cam.incremntal_calculate();
			//	active_cam.move[3][0] += 5;
			// right mouse button is down
		}

		if (io.MouseDown[1])
		{
			if (!iscam_trans) {
				active_model.scale[0][0] -= 1;
				active_model.scale[1][1] -= 1;
				active_model.scale[2][2] -= 1;
				active_model.scalexyz = active_model.scale[0][0];

			}
			if (iscam_trans)
				active_cam.move[3][0] -= 5;
			// Left mouse button is down
		}
	}


	renderer.ClearColorBuffer(clear_color);
	renderer.Render(scene);
	renderer.SwapBuffers();


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}


void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	/**
	 * MeshViewer menu
	 */

	ImGui::Begin("MeshViewer Menu");
	
	MeshModel& active_model = scene.GetActiveModel();
	Camera& active_cam = scene.GetActiveCamera();

	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					/*active_model.movex = 0;
					active_model.movey = 0;
					active_model.movez = 0;
					active_model.movex_world = 0;
					active_model.movey_world = 0;
					active_model.movez_world = 0;
					active_model.scalex = 1;
					active_model.scaley = 1;
					active_model.scalez = 1;
					active_model.scalexyz = 1;
					active_model.scalex_world = 1;
					active_model.scaley_world = 1;
					active_model.scalez_world = 1;
					active_model.scalexyz_world = 1;
					active_model.rotatex = 0;
					active_model.rotatey = 0;
					active_model.rotatez = 0;
					active_model.rotatex_world = 0;
					active_model.rotatey_world = 0;
					active_model.rotatez_world = 0;*/

					scene.AddModel(Utils::LoadMeshModel(outPath));
					//active_model.color = glm::vec3(0.7f, 0.7f, 0.7f);
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
	// TODO: Add more controls as needed

	ImGui::End();

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */

	 // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();

	}
	if (scene.GetModelCount()) {
		ImGui::Begin("Buttons");

		if (iscam_trans) {
			ImGui::Text("Camera %d", scene.GetActiveCameraIndex() + 1);

			std::string local_world;
			if (active_cam.local_cam) {
				local_world = "local camera transformations";
			}
			else local_world = "world camera transformations";
			if (ImGui::Button(local_world.c_str()))
			{
				if (active_cam.local_cam) {
					active_cam.local_cam = false;
				}
				else active_cam.local_cam = true;
			}


			ImGui::Text("The last added camera is : %d", scene.GetCameraCount());
			if (active_cam.local_cam) {

				ImGui::InputDouble("move x", &active_cam.movex, 5, 5, (std::to_string(active_cam.movex)).c_str());
				ImGui::InputDouble("move y", &active_cam.movey, 5, 5, (std::to_string(active_cam.movey)).c_str());
				ImGui::InputDouble("move z", &active_cam.movez, 5, 5, (std::to_string(active_cam.movez)).c_str());
				ImGui::InputDouble("rotate x", &active_cam.rotatex, 3, 3, (std::to_string(active_cam.rotatex)).c_str(), 1);
				ImGui::InputDouble("rotate y", &active_cam.rotatey, 3, 3, (std::to_string(active_cam.rotatey)).c_str(), 1);
				ImGui::InputDouble("rotate z", &active_cam.rotatez, 3, 3, (std::to_string(active_cam.rotatez)).c_str(), 1);

			}

			else {
				//world trans
				ImGui::InputDouble("move x", &active_cam.movex_world, 5, 5, (std::to_string(active_cam.movex_world)).c_str());
				ImGui::InputDouble("move y", &active_cam.movey_world, 5, 5, (std::to_string(active_cam.movey_world)).c_str());
				ImGui::InputDouble("move z", &active_cam.movez_world, 5, 5, (std::to_string(active_cam.movez_world)).c_str());
				ImGui::InputDouble("rotate x", &active_cam.rotatex_world, 3, 3, (std::to_string(active_cam.rotatex_world)).c_str(), 1);
				ImGui::InputDouble("rotate y", &active_cam.rotatey_world, 3, 3, (std::to_string(active_cam.rotatey_world)).c_str(), 1);
				ImGui::InputDouble("rotate z", &active_cam.rotatez_world, 3, 3, (std::to_string(active_cam.rotatez_world)).c_str(), 1);
			}

			ImGui::InputDouble("eye 1", &active_cam.eye1, 0.1, 0.1, (std::to_string(active_cam.eye1)).c_str());
			ImGui::InputDouble("eye 2", &active_cam.eye2, 0.1, 0.1, (std::to_string(active_cam.eye2)).c_str());
			ImGui::InputDouble("eye 3", &active_cam.eye3, 0.1, 0.1, (std::to_string(active_cam.eye3)).c_str());

			if (active_cam.orth_per) {
				ImGui::InputDouble("left", &active_cam.left_ortho, 0.1, 0.1, (std::to_string(active_cam.left_ortho)).c_str());
				ImGui::InputDouble("right", &active_cam.right_ortho, 0.1, 0.1, (std::to_string(active_cam.right_ortho)).c_str());
				ImGui::InputDouble("up", &active_cam.up_ortho, 0.1, 0.1, (std::to_string(active_cam.up_ortho)).c_str());
				ImGui::InputDouble("down", &active_cam.down_ortho, 0.1, 0.1, (std::to_string(active_cam.down_ortho)).c_str());
			}
			else {
				ImGui::InputDouble("left", &active_cam.left_per, 0.1, 0.1, (std::to_string(active_cam.left_per)).c_str());
				ImGui::InputDouble("right", &active_cam.right_per, 0.1, 0.1, (std::to_string(active_cam.right_per)).c_str());
				ImGui::InputDouble("up", &active_cam.up_per, 0.1, 0.1, (std::to_string(active_cam.up_per)).c_str());
				ImGui::InputDouble("down", &active_cam.down_per, 0.1, 0.1, (std::to_string(active_cam.down_per)).c_str());
				ImGui::InputDouble("near", &active_cam.nearcam, 0.1, 0.1, (std::to_string(active_cam.nearcam)).c_str());
				ImGui::InputDouble("far", &active_cam.farcam, 0.1, 0.1, (std::to_string(active_cam.farcam)).c_str());
				ImGui::InputDouble("fovy", &active_cam.fovycam, 0.1, 0.1, (std::to_string(active_cam.fovycam)).c_str());

			}
			if (ImGui::Button("Add Camera")) {

				shared_ptr <Camera> mycam2 = std::make_shared<Camera>();
				scene.AddCamera(mycam2);
				iscam_trans = true;
				number_of_cameras++;
			}

			if (ImGui::Button("model trasformation")) {
				iscam_trans = false;
			}
			if (ImGui::Button("next Camera")) {

				scene.AddModel(Utils::LoadMeshModel("C:\\Users\\ACER\\source\\repos\\HaifaGraphicsCourses\\computer-graphics-2022-coding-machines\\Data\\camera.obj"));
				MeshModel& camera_model = scene.GetActiveModel();
				camera_model.scale = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);;
				camera_model.scalexyz = 1;
				camera_model.w_move = active_cam.w_move;
				camera_model.move = active_cam.move;
				camera_model.xw_rotate = active_cam.xw_rotate;
				camera_model.yw_rotate = active_cam.yw_rotate;
				camera_model.zw_rotate = active_cam.zw_rotate;
				camera_model.x_rotate = active_cam.x_rotate;
				camera_model.y_rotate = active_cam.y_rotate;
				camera_model.z_rotate = active_cam.z_rotate;
				camera_model.scale[0][0] += 50;
				camera_model.scale[1][1] += 50;
				camera_model.scale[2][2] += 50;

				scene.SetActiveCameraIndex((scene.GetActiveCameraIndex() + 1) % scene.GetCameraCount());

				//Camera& active_cam_tmp = scene.GetActiveCamera();
				//active_cam.movex= active_cam_tmp.move[3][0];
				//active_cam.movey= active_cam_tmp.move[3][1];
				////+540 satir 714
				//active_cam.movez= active_cam_tmp.move[3][2] ;
				//active_cam.movex_world = active_cam_tmp.w_move[3][0];
				//active_cam.movey_world = active_cam_tmp.w_move[3][1];
				//active_cam.movez_world = active_cam_tmp.w_move[3][2];
				//active_cam.rotatex = active_cam_tmp.rotatex;
				//active_cam.rotatey= active_cam_tmp.rotatey;
				//active_cam.rotatez = active_cam_tmp.rotatez;
				//active_cam.rotatex_world = active_cam_tmp.rotatex_world;
				//active_cam.rotatey_world = active_cam_tmp.rotatey_world;
				//active_cam.rotatez_world = active_cam_tmp.rotatez_world;
				//active_cam.left_ortho = active_cam_tmp.left_ortho;
				//active_cam.right_ortho = active_cam_tmp.right_ortho;
				//active_cam.up_ortho = active_cam_tmp.up_ortho;
				//active_cam.down_ortho = active_cam_tmp.down_ortho;
				//active_cam.left_per = active_cam_tmp.left_per;
				//active_cam.right_per = active_cam_tmp.right_per;
				//active_cam.up_per = active_cam_tmp.up_per;
				//active_cam.down_per = active_cam_tmp.down_per;
				//active_cam.nearcam = active_cam_tmp.nearcam;
				//active_cam.farcam = active_cam_tmp.farcam;
				//active_cam.fovycam = active_cam_tmp.fovycam;
				//active_cam.eye1 = 0;
				//active_cam.eye2 = 0;
				//active_cam.eye3 = 1;
				/*iscam_trans = true;
				active_cam.local_cam = true;*/

			}
			if (active_cam.orth_per == false) {
				if (ImGui::Button("ortho matrix")) {
					active_cam.orth_per = true;
					active_model.scale[0][0] = 1;
					active_model.scale[1][1] = 1;
					active_model.scale[2][2] = 1;
				}
			}
			else {
				if (ImGui::Button("per matrix")) {
					active_cam.orth_per = false;
					active_model.scale[0][0] = 1;
					active_model.scale[1][1] = 1;
					active_model.scale[2][2] = 1;
				}
			}

		}


		else {

			ImGui::Text(active_model.GetModelName().substr(0, active_model.GetModelName().size() - 4).c_str());
			std::string local_world;
			if (active_model.local) {
				local_world = "local  transformations";
			}
			else local_world = "world  transformations";
			if (ImGui::Button(local_world.c_str()))
			{
				if (active_model.local) {
					active_model.local = false;
				}
				else active_model.local = true;
			}

			if (active_model.local) {
				ImGui::InputDouble("move x", &active_model.movex, 5, 5, (std::to_string(active_model.movex)).c_str());
				ImGui::InputDouble("move y", &active_model.movey, 5, 5, (std::to_string(active_model.movey)).c_str());
				ImGui::InputDouble("move z", &active_model.movez, 5, 5, (std::to_string(active_model.movez)).c_str());
				ImGui::InputDouble("scale x", &active_model.scalex, 5, 5, (std::to_string(active_model.scalex)).c_str());
				ImGui::InputDouble("scale y", &active_model.scaley, 5, 5, (std::to_string(active_model.scaley)).c_str());
				ImGui::InputDouble("scale z", &active_model.scalez, 5, 5, (std::to_string(active_model.scalez)).c_str());
				ImGui::InputDouble("scale", &active_model.scalexyz, 0.5, 0.5, (std::to_string(active_model.scalexyz)).c_str(), 1);
				ImGui::InputDouble("rotate x", &active_model.rotatex, 3, 3, (std::to_string(active_model.rotatex)).c_str(), 1);
				ImGui::InputDouble("rotate y", &active_model.rotatey, 3, 3, (std::to_string(active_model.rotatey)).c_str(), 1);
				ImGui::InputDouble("rotate z", &active_model.rotatez, 3, 3, (std::to_string(active_model.rotatez)).c_str(), 1);

			}

			else {
				//world trans
				ImGui::InputDouble("move x", &active_model.movex_world, 5, 5, (std::to_string(active_model.movex_world)).c_str());
				ImGui::InputDouble("move y", &active_model.movey_world, 5, 5, (std::to_string(active_model.movey_world)).c_str());
				ImGui::InputDouble("move z", &active_model.movez_world, 5, 5, (std::to_string(active_model.movez_world)).c_str());
				ImGui::InputDouble("scale x", &active_model.scalex_world, 5, 5, (std::to_string(active_model.scalex_world)).c_str(), 1);
				ImGui::InputDouble("scale y", &active_model.scaley_world, 5, 5, (std::to_string(active_model.scaley_world)).c_str(), 1);
				ImGui::InputDouble("scale z", &active_model.scalez_world, 5, 5, (std::to_string(active_model.scalez_world)).c_str(), 1);
				ImGui::InputDouble("rotate x", &active_model.rotatex_world, 3, 3, (std::to_string(active_model.rotatex_world)).c_str(), 1);
				ImGui::InputDouble("rotate y", &active_model.rotatey_world, 3, 3, (std::to_string(active_model.rotatey_world)).c_str(), 1);
				ImGui::InputDouble("rotate z", &active_model.rotatez_world, 3, 3, (std::to_string(active_model.rotatez_world)).c_str(), 1);
			}
			if (ImGui::Button("next model")) {

				scene.SetActiveModelIndex((scene.GetActiveModelIndex() + 1) % scene.GetModelCount());

				/*
				x_move = active_model.move[3][0];
				y_move = active_model.move[3][1];
				z_move = active_model.move[3][2];
				xw_move = active_model.w_move[3][0];
				yw_move = active_model.w_move[3][1];
				zw_move = active_model.w_move[3][2];
				scale = active_model.sc;
				x_scaling = active_model.scale[0][0] - scale;
				y_scaling = active_model.scale[1][1] - scale;
				z_scaling = active_model.scale[2][2] - scale;
				xw_scaling = active_model.w_scale[0][0];
				yw_scaling = active_model.w_scale[1][1];
				zw_scaling = active_model.w_scale[2][2];
				w_scale = active_model.w_sc;
				x_rotate = active_model.x_alpha;
				y_rotate = active_model.y_alpha;
				z_rotate = active_model.z_alpha;
				xw_rotate = active_model.xw_alpha;
				yw_rotate = active_model.yw_alpha;
				zw_rotate = active_model.zw_alpha;*/


			}

			if (ImGui::Button("Camera Transformation")) {
				iscam_trans = true;
			}


		}
		if (ImGui::Checkbox("normal face", &normal_face)) {
			active_model.normal_face = !active_model.normal_face;
		}
		if (ImGui::Checkbox("normal vertix", &normal_vertix)) {
			active_model.normal_vertix = !active_model.normal_vertix;
		}
		if (ImGui::Checkbox("show axis model", &axis_model)) {
			active_model.axis = !active_model.axis;
		}
		if (ImGui::Checkbox("show axis window", &axis_window)) {
			active_cam.axis_wind = !active_cam.axis_wind;
		}


		if (ImGui::Checkbox("boundong box", &bounding_box)) {
			active_model.box = !active_model.box;
		}
		if (ImGui::Checkbox("boxes around triangles", &boxes_around_triangles)) {
			active_model.allboxes = !active_model.allboxes;
		}

		if (ImGui::Checkbox("show ref", &show_ref)) {
			if (diffuse == false && ambient == false && specular == false) {
				scene.GetLight(0).show_ref = !scene.GetLight(0).show_ref;
			}
			else show_ref = false;
		}
		ImGui::Text("\nLights Color ");



		if (ImGui::Checkbox("ambient", &ambient)) {
			if (diffuse == false && specular == false)
				scene.GetLight(0).ambient = !scene.GetLight(0).ambient;
			else ambient = false;
		}
		
			ImGui::ColorEdit3("ambient color", (float*)&scene.GetLight(0).ambient_color);
		

		if (ImGui::Checkbox("diffuse", &diffuse)) {
			if (ambient == false && specular == false) {
				scene.GetLight(0).diffuse = !scene.GetLight(0).diffuse;
			}
			else {
				diffuse = false;
			
			}
		}
		
			ImGui::ColorEdit3("Diffuse color", (float*)&scene.GetLight(0).diff_color);

		

		
		if (ImGui::Checkbox("specular", &specular)) {
			if (diffuse == false && ambient == false)
				scene.GetLight(0).specular = !scene.GetLight(0).specular;
			else specular = false;
		}
		
			ImGui::ColorEdit3("Specular color", (float*)&scene.GetLight(0).spec_color);

		
	
	
		ImGui::Text("\nmodels colors");
		ImGui::ColorEdit3("ambient light color", (float*)&active_model.ambient_color_model);
		ImGui::ColorEdit3("diffuse light color", (float*)&active_model.diff_color_model);
		ImGui::ColorEdit3("specular light color", (float*)&active_model.spec_color_model);

		ImGui::Text("\nshading");
		if (ImGui::Checkbox("flat", &flat)) {
			if (gour == false && phong == false)
				scene.GetLight(0).flat = !scene.GetLight(0).flat;
			else flat = false;
		}
		if (ImGui::Checkbox("gouraud", &gour)) {
			if (flat == false && phong == false)
				scene.GetLight(0).gour = !scene.GetLight(0).gour;
			else gour = false;
		}
		if (ImGui::Checkbox("phong", &phong)) {
			if (flat == false && gour == false)
				scene.GetLight(0).phong = !scene.GetLight(0).phong;
			else phong = false;
		}

		

		ImGui::Text("\nchange light position\n");
		ImGui::InputFloat("x pos", &scene.GetLight(0).position[0], 1, 1, (std::to_string(scene.GetLight(0).position[0])).c_str());
		ImGui::InputFloat("y pos", &scene.GetLight(0).position[1], 1, 1, (std::to_string(scene.GetLight(0).position[1])).c_str());
		ImGui::InputFloat("z pos", &scene.GetLight(0).position[2], 1, 1, (std::to_string(scene.GetLight(0).position[2])).c_str());

	/*	ImGui::Text("\nchange light color\n");
		ImGui::SliderFloat("x color", &scene.GetLight(0).color[0], 0.0f, 1.0f);
		ImGui::SliderFloat("y color", &scene.GetLight(0).color[1], 0.0f, 1.0f);
		ImGui::SliderFloat("z color", &scene.GetLight(0).color[2], 0.0f, 1.0f);

		ImGui::Text("\nchange material color\n");
		ImGui::SliderFloat("x material color", &active_model.color[0], 0.0f, 1.0f);
		ImGui::SliderFloat("y material color", &active_model.color[1], 0.0f, 1.0f);
		ImGui::SliderFloat("z material color", &active_model.color[2], 0.0f, 1.0f);*/


		ImGui::Text("\nchange width and hieght\n");
		ImGui::InputDouble("Weidth", &weidth_size, 5, 5, (std::to_string(weidth_size)).c_str(), 1);
		ImGui::InputDouble("Hieght", &hight_size, 5, 5, (std::to_string(hight_size)).c_str(), 1);





		ImGui::End();
	}




}