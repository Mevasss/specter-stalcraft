#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <TlHelp32.h>
#include <stdio.h>
#include <string>
#include "nt.h"


class HijackHandle
{
public:
	static auto get_handle(std::uint32_t pid, HANDLE& handle) -> bool;
};