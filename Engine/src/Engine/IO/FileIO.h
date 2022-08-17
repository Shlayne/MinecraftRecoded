#pragma once

#include "Engine/Core/Int.h"
#include <string_view>
#include <vector>

namespace eng::io
{
	std::string ReadFile(std::string_view filepath);
	std::vector<uint8> ReadBinaryFile(std::string_view filepath);
	bool WriteFile(std::string_view filepath, std::string_view contents);
	bool WriteBinaryFile(std::string_view filepath, const std::vector<uint8>& crContents);
	bool WriteBinaryFile(std::string_view filepath, const void* cpContents, size_t size);
}
