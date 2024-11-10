#pragma once
#define WIN32_LEAN_AND_MEAN
#include <glfw3.h>
#include <cstdint>
#include <windows.h>
#include "../../Libs/Imgui/imgui.h"
class Menu
{
public:
	static auto draw() -> void;
	static inline bool items_esp = true;
	static inline ImVec4 items_esp_color = {1,1,1,0.3f};

	static inline bool players_chams = true;
	static inline ImVec4 players_chams_color = { 1,1,1,0.3f };
	static inline int players_toggle_key;
};