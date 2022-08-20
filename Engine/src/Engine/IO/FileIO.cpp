#include "Engine/pch.h"
#include "Engine/IO/FileIO.h"

namespace eng::io
{
	std::string ReadFile(std::string_view filepath)
	{
		std::ifstream file(filepath.data());
		if (file.is_open())
		{
			std::stringstream contents;
			contents << file.rdbuf();
			file.close();
			return contents.str();
		}
		return {};
	}

	std::vector<uint8> ReadBinaryFile(std::string_view filepath)
	{
		std::ifstream file(filepath.data(), std::ios::binary);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			file.seekg(0, std::ios::beg);

			std::vector<uint8> contents(size, 0);
			file.read((char*)contents.data(), size);
			file.close();
			return contents;
		}
		return {};
	}

	bool WriteFile(std::string_view filepath, std::string_view contents)
	{
		std::ofstream file(filepath.data());
		if (file.is_open())
		{
			file << contents;
			file.close();
			return file.good();
		}
		return false;
	}

	bool WriteBinaryFile(std::string_view filepath, const std::vector<uint8_t>& contents)
	{
		return WriteBinaryFile(filepath, contents.data(), contents.size());
	}

	bool WriteBinaryFile(std::string_view filepath, const void* contents, size_t size)
	{
		std::ofstream file(filepath.data(), std::ios::binary);
		if (file.is_open())
		{
			file.write((const char*)contents, size);
			file.close();
			return file.good();
		}
		return false;
	}
}
