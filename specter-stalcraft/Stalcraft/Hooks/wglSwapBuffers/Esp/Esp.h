#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>
#include "../Libs/Imgui/imgui.h"
#include "../../../Structs/Structs.h"
#include <vector>
#include <mutex>
struct drawables
{
	drawables(GLfloat* projection_matrix_, GLfloat* modelview_matrix_)
	{
		std::memcpy(projection_matrix, projection_matrix_, sizeof(projection_matrix));
		std::memcpy(modelview_matrix, modelview_matrix_, sizeof(modelview_matrix));
	}
	GLfloat projection_matrix[16];
	GLfloat modelview_matrix[16];
};


class Esp
{
public:
	static inline std::vector<drawables> items;
	static inline std::vector<drawables> players;
	static auto draw() -> void;
	static auto add_drawing_model(std::vector<drawables>& models, Vector3 offset) -> void;
	static auto draw_model(const GLfloat projection_matrix[16], const GLfloat modelview_matrix[16], const ImVec4& color, const Vector3& box_size) -> void;
	static inline GLfloat last_modelview_matrix[16];
	static inline GLfloat last_projection_matrix[16];
};