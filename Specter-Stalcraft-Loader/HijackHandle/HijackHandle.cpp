#include "HijackHandle.h"


auto HijackHandle::get_handle(std::uint32_t pid, HANDLE& handle) -> bool
{
    try
    {
        static auto nt_dll = GetModuleHandle("ntdll.dll");
        if (!nt_dll)
            throw "Failed to get ntdll";

        static auto NtQuerySystemInformation = (lpNtQuerySystemInformation)GetProcAddress(nt_dll, "NtQuerySystemInformation");
        if (!NtQuerySystemInformation)
            throw "Failed to get NtQuerySystemInformation";

        static auto NtDuplicateObject = (lpNtDuplicateObject)GetProcAddress(nt_dll, "NtDuplicateObject");
        if (!NtDuplicateObject)
            throw "Failed to get NtDuplicateObject";

        NTSTATUS status = 0; 
        ULONG handle_info_size = 0x10000; 
        PSYSTEM_HANDLE_INFORMATION handle_info = nullptr;

        handle_info = reinterpret_cast<PSYSTEM_HANDLE_INFORMATION>(std::malloc(handle_info_size)); 
        if (!handle_info)
            throw "Failed to allocate memory";

        RtlZeroMemory(handle_info, handle_info_size);

        while ((status = NtQuerySystemInformation(SystemHandleInformation, handle_info, handle_info_size, NULL)) == STATUS_INFO_LENGTH_MISMATCH)
        {
            handle_info_size *= 2;
            handle_info = (PSYSTEM_HANDLE_INFORMATION)realloc(handle_info, handle_info_size);
            if (!handle_info)
                throw "Failed to allocate memory";
        }

        if (!NT_SUCCESS(status))
            throw "Failed to iterate all processes";

        for (ULONG i = 0; i < handle_info->HandleCount; ++i)
        {
            auto current_handle = handle_info->Handles[i];

            if (current_handle.ObjectTypeNumber != 0x5 && current_handle.ObjectTypeNumber != 0x7)
                continue;

            auto process_handle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, current_handle.ProcessId);
            if (!process_handle || process_handle == INVALID_HANDLE_VALUE) {
                continue;
            }

            HANDLE duplicate_handle = nullptr;
            status = NtDuplicateObject(process_handle, (HANDLE)current_handle.Handle, NtCurrentProcess, &duplicate_handle, PROCESS_ALL_ACCESS, 0, 0);
            if (!NT_SUCCESS(status))
            {
                CloseHandle(process_handle);
                continue;
            }

            if (GetProcessId(duplicate_handle) != pid) {
                CloseHandle(duplicate_handle);
                CloseHandle(process_handle);
                continue;
            }

            if (duplicate_handle) {
                handle = duplicate_handle;
                CloseHandle(process_handle);
                std::free(handle_info);
                return true;
            }
        }
    }
    catch (const char* message)
    {
        std::cout << "[!!] " << message << std::endl;
        return false;
    }
    catch (...)
    {
        std::cout << "[!!] Some error in hijacking handle" << std::endl;
        return false;
    }
    return false;
}
