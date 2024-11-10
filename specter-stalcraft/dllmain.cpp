#define CURL_STATICLIB
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>
#include "Stalcraft/Hooks/Hooks.h"
#include "Vmprotect/Vmprotect.h"
#include "Oxorany/Oxorany_include.h"
#include "Vmprotect/Vmprotect.h"
#include "Keyauth/Keyauth.h"
#include <iostream>

auto entry_point(char* key) -> void
{
    PROTECT_ULTRA("entry_point");
    
    //AllocConsole();
    //FILE* file{};
    //freopen_s(&file, "CONOUT$", "w+", stdout);
    //setlocale(LC_ALL, "RU");

    KeyAuth::api keyauth(_("Specter-stalcraft"), _("wX3TkacdAt"), _("ada30390df660aa9eaf3e64f9e808b3fc41681e737e6d10ff3cbaa94c86a269f"), _("1.0"), _("https://keyauth.win/api/1.2/"), _(""));
    keyauth.init();

    if (!keyauth.response.success) {
        MessageBox(0, keyauth.response.message.c_str(), _(oxorany("Error")), 0);
    }

    keyauth.license(key);
    VirtualFree(reinterpret_cast<LPVOID>(key), 0, MEM_RELEASE);
    if (!keyauth.response.success) {
        MessageBox(0, keyauth.response.message.c_str(), _(oxorany("Error")), 0);
    }
 

    Hooks* hooks = new Hooks();
    PROTECT_END();
}

auto APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     ) -> BOOL
{
    char* key = reinterpret_cast<char*>(lpReserved);
    PROTECT_ULTRA("DllMain");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        

        std::thread(entry_point, key).detach();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
    PROTECT_END();
}

