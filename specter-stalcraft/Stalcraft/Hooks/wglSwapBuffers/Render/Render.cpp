#include "Render.h"
#include "../Libs/Imgui/imgui.h"
#include "../Libs/Imgui/imgui_impl_win32.h"
#include "../Libs/Imgui/imgui_impl_opengl2.h"
#include "Menu/Menu.h"
#include <string>
#include "../../Hooks.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK h_WndProc(
	const HWND	hWnd,
	UINT		uMsg,
	WPARAM		wParam,
	LPARAM		lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_COMMAND:

		break;
	case WM_LBUTTONDOWN:
		if (Render::menu_opened)
			return 0;
		break;
	case WM_LBUTTONUP:
		if (Render::menu_opened)
			return 0;
		break;
	default:
		break;
	}

	return CallWindowProc(Render::original_wndproc, hWnd, uMsg, wParam, lParam);
}

auto Render::render(HDC hDc) -> void
{
	if (!inited) {

		Hooks::init_context_hooks();

		hwnd = WindowFromDC(hDc);
		original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(h_WndProc)));
		h_wgl_context = wglCreateContext(hDc);
		
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		window_width = window_rect.right - window_rect.left;
		window_height = window_rect.bottom - window_rect.top;
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplOpenGL2_Init();

		inited = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
		Render::menu_opened = !Render::menu_opened;

	if (GetAsyncKeyState(Menu::players_toggle_key) & 1)
		Menu::players_chams = !Menu::players_chams;

	auto original_wgl_context = wglGetCurrentContext();

	
	wglMakeCurrent(hDc, h_wgl_context);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto& io = ImGui::GetIO();
	if (menu_opened) {
		io.MouseDrawCursor = true;
		Menu::draw();
	}
	else {
		io.MouseDrawCursor = false; 
	}
	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(hDc, original_wgl_context);

}
