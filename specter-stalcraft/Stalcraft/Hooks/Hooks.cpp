#include "Hooks.h"
#include <MinHook.h>
#include "wglSwapBuffers/wglSwapBuffers.h"
#include "glScalef/glScalef.h"
#include "wglSwapBuffers/Esp/Esp.h"
#include "glDrawElements/glDrawElements.h"
#include <string>
#include <Windows.h>
#include "gl/GLU.h"
#include "glUniformMatrix4fv/glUniformMatrix4fv.h"
#include "glGetFloatv/glGetFloatv.h"
#include "../../Vmprotect/Vmprotect.h"
#include "../../Oxorany/Oxorany_include.h"
Hooks::Hooks()
{
	try
	{		
		if (MH_Initialize() != MH_STATUS::MH_OK)
			throw _(oxorany("Failed to init minhook"));
		
		MH_CreateHookApi(oxorany(L"opengl32.dll"), _(oxorany("wglSwapBuffers")), wglSwapBuffers::hk_wglSwapBuffers, reinterpret_cast<LPVOID*>(&wglSwapBuffers::original_wglSwapBuffers));

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_STATUS::MH_OK)
			throw _(oxorany("Failed to enable all hooks"));

	}
	catch (const char* message)
	{
		MessageBoxA(0, message, _(oxorany("Error")), 0);
	}
	catch (...)
	{
		MessageBoxA(0,_(oxorany("Some error in hooks class")), _(oxorany("Error")), 0);
	}
}

auto Hooks::init_context_hooks() -> void
{
	try
	{
		MH_CreateHookApi(oxorany(L"opengl32.dll"), _(oxorany("glScalef")), glScalef::hk_glScalef, reinterpret_cast<LPVOID*>(&glScalef::original_glScalef));
		MH_CreateHookApi(oxorany(L"opengl32.dll"), _(oxorany("glGetFloatv")), glGetFloatv::hk_glGetFloatv, reinterpret_cast<LPVOID*>(&glGetFloatv::original_glGetFloatv));
		
		auto glUniformMatrix4fv_addr = wglGetProcAddress(_(oxorany("glUniformMatrix4fv")));
		MH_CreateHook(glUniformMatrix4fv_addr, glUniformMatrix4fv::hk_glUniformMatrix4fv, reinterpret_cast<LPVOID*>(&glUniformMatrix4fv::original_glUniformMatrix4fv));

		auto glDrawElements_addr = wglGetProcAddress(_(oxorany("glDrawElements")));
		MH_CreateHook(glDrawElements_addr, glDrawElements::hk_glDrawElements, reinterpret_cast<LPVOID*>(&glDrawElements::original_glDrawElements));

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_STATUS::MH_OK)
			throw _(oxorany("Failed to enable all hooks"));

	}
	catch (const char* message)
	{
		MessageBoxA(0, message, _(oxorany("Error")), 0);
	}
	catch (...)
	{
		MessageBoxA(0, _(oxorany("Some error in hooks class")), _(oxorany("Error")), 0);
	}

}

Hooks::~Hooks()
{
	try
	{
		if (MH_DisableHook(MH_ALL_HOOKS) != MH_STATUS::MH_OK)
			throw _(oxorany("Failed to disable all hooks"));
	}
	catch (const char* message)
	{
		MessageBoxA(0, message, _(oxorany("Error")), 0);
	}
	catch (...)
	{
		MessageBoxA(0, _(oxorany("Some error in ~hooks class")), _(oxorany("Error")), 0);
	}
}
