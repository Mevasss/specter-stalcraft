#define CURL_STATICLIB
#include <iostream>
#include "Keyauth/Keyauth.h"
#include "Vmprotect/Vmprotect.h"
#include "Injector/Injector.h"
#include "LazyImporter/LazyImporter.h"
#include "Oxorany/Oxorany_include.h"
#include <thread>
#include "HijackHandle/HijackHandle.h"

__forceinline uint32_t GetProcessIdByName(const char* name) {
    PROCESSENTRY32 entry;
    entry.dwSize = oxorany(static_cast<DWORD>(sizeof(PROCESSENTRY32)));

    HANDLE snapshot = LI_FN(CreateToolhelp32Snapshot)(oxorany(TH32CS_SNAPPROCESS), oxorany(NULL));

    if (LI_FN(Process32First)(snapshot, &entry) == oxorany(TRUE)) {
        while (LI_FN(Process32Next)(snapshot, &entry) == oxorany(TRUE)) {
            if (LI_FN(strcmp)(entry.szExeFile, name) == oxorany(0)) {
                LI_FN(CloseHandle)(snapshot);
                return entry.th32ProcessID;
            }
        }
    }

    LI_FN(CloseHandle)(snapshot);
    return oxorany(0);
}


int main()
{
    PROTECT_ULTRA("main");

    LI_FN(SetConsoleTitle)(_(oxorany("Specter - SC")));
    HANDLE hConsole = LI_FN(GetStdHandle)(oxorany(STD_OUTPUT_HANDLE));
    LI_FN(SetConsoleTextAttribute)(hConsole, oxorany(13));


    std::thread([]() {
        while (true) {
            if (!VMProtectIsProtected() || VMProtectIsDebuggerPresent(true) || VMProtectIsVirtualMachinePresent() || !VMProtectIsValidImageCRC()) {
                LI_FN(abort)();
            }
            LI_FN(Sleep)(oxorany(100));
        }
        }).detach();

    KeyAuth::api keyauth(_("Specter-stalcraft"), _("wX3TkacdAt"), _("ada30390df660aa9eaf3e64f9e808b3fc41681e737e6d10ff3cbaa94c86a269f"), _("1.0"), _("https://keyauth.win/api/1.2/"), _(""));

    keyauth.init();
    if (!keyauth.response.success) {
        std::cout << _(oxorany("[!!] Failed to init auth system")) << std::endl;
        LI_FN(system)(_(oxorany("pause")));
        return oxorany(0);
    }

    std::cout << _(oxorany("Enter key: "));
    char key[50];
    std::cin >> key;
    std::cout << std::endl;

    keyauth.license(key);
    if (!keyauth.response.success) {
        std::cout << keyauth.response.message << std::endl;
        LI_FN(system)(_(oxorany("pause")));
        return oxorany(0);
    }
    LI_FN(system)(_(oxorany("cls")));
    std::cout << _(oxorany("[~] Authentificated! Loading...")) << std::endl;

   

    auto stalcraft_pid = GetProcessIdByName(_(oxorany("stalcraft.exe")));

    if (!stalcraft_pid) {
        stalcraft_pid = GetProcessIdByName(_(oxorany("stalcraftw.exe")));
        if (!stalcraft_pid) {
            std::cout << _(oxorany("[!] Failed to find stalcraft process")) << std::endl;
            system(_("pause"));
            return oxorany(0);
        }
    }
    std::cout << _(oxorany("[~] Finded pid...")) << std::endl;

    HANDLE stalcraft_handle = nullptr;
    if (!HijackHandle::get_handle(stalcraft_pid, stalcraft_handle) || !stalcraft_handle) {
        std::cout << _(oxorany("[!!] Failed to get handle!")) << std::endl;
        LI_FN(system)(_(oxorany("pause")));
        return oxorany(0);
    }
    std::cout << _(oxorany("[~] Finded handle...")) << std::endl;

    std::cout << _(oxorany("[~] Downloading cheat...")) << std::endl;
    auto dll_bytes = keyauth.download(_(oxorany("512437")));
    std::cout << _(oxorany("[~] Cheat downloaded...")) << std::endl;

    auto key_address = LI_FN(VirtualAllocEx)(stalcraft_handle, nullptr, sizeof(key), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!key_address) {
        CloseHandle(stalcraft_handle);
        std::cout << _(oxorany("[!!] Failed to allocate memory!")) << std::endl;
        LI_FN(system)(_(oxorany("pause")));
        return oxorany(0);
    }

    WriteProcessMemory(stalcraft_handle, key_address, key, sizeof(key), nullptr);

    if (!ManualMapDll(stalcraft_handle, dll_bytes.data(), dll_bytes.size(),true,true,true,true,1UL,key_address))
    {
        CloseHandle(stalcraft_handle);
        std::cout << _(oxorany("[!!] Failed to inject!")) << std::endl;
        LI_FN(system)(_(oxorany("pause")));
        return oxorany(0);
    }

    CloseHandle(stalcraft_handle);
    std::cout << _(oxorany("[~] Injected!")) << std::endl;
    LI_FN(Sleep)(oxorany(5000));
    return oxorany(0);

    PROTECT_END();
}
