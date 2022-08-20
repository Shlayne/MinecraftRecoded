#include "Engine/pch.h"
#include "ScriptEngine.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include "Engine/IO/FileIO.h"

namespace eng
{
	struct ScriptEngineData
	{
		MonoDomain* rootDomain = nullptr;
		MonoDomain* appDomain = nullptr;

		MonoAssembly* coreAssembly = nullptr;
	};

	static ScriptEngineData* s_ScriptEngineData = nullptr;

	// Forward Declarations
	void InitMono();
	void ShutdownMono();
	MonoAssembly* LoadAssembly(std::string_view filepath);
	void PrintAssemblyTypes(MonoAssembly* assembly);

	void ScriptEngine::Init()
	{
		CORE_ASSERT(s_ScriptEngineData == nullptr, "Tried to reinitialize the script engine.");
		s_ScriptEngineData = new ScriptEngineData();

		InitMono();
	}

	void ScriptEngine::Shutdown()
	{
		CORE_ASSERT(s_ScriptEngineData != nullptr, "Tried to reshutdown the script engine.");

		ShutdownMono();

		delete s_ScriptEngineData;
		s_ScriptEngineData = nullptr;
	}

	void InitMono()
	{
		auto& data = *s_ScriptEngineData;

		mono_set_assemblies_path("mono/lib");

		data.rootDomain = mono_jit_init("JitRuntime");
		ASSERT(data.rootDomain != nullptr, "Failed to load C# runtime.");

		data.appDomain = mono_domain_create_appdomain(const_cast<char*>("ScriptRuntime"), nullptr);
		ASSERT(data.appDomain != nullptr, "Failed to create C# app domain.");
		UNUSED(mono_domain_set(data.appDomain, true));

		data.coreAssembly = LoadAssembly(SCRIPT_CORE_ASSEMBLY_FILEPATH);
		ASSERT(data.coreAssembly != nullptr, "Failed to load script core assembly.");
		PrintAssemblyTypes(data.coreAssembly);

		//MonoImage* monoImage = mono_assembly_get_image(data.coreAssembly);
		//MonoClass* monoClass = mono_class_from_name(monoImage, "eng", "Main");
		//MonoObject* monoObject = mono_object_new(data.appDomain, monoClass);
		//mono_runtime_object_init(monoObject);
		//MonoMethod* printCustomMessageFunc = mono_class_get_method_from_name(monoClass, "PrintCustomMessage", 1);

		//MonoString* string = mono_string_new(data.appDomain, "asdaklsjdfhliu dfg");

		//int a = 5;
		//void* params[]{ string };
		//mono_runtime_invoke(printCustomMessageFunc, monoObject, params, nullptr);
	}

	void ShutdownMono()
	{
		auto& data = *s_ScriptEngineData;

		// Bad mono, very uncool.

		//mono_domain_unload(data.appDomain);
		data.appDomain = nullptr;
		//mono_jit_cleanup(data.rootDomain);
		data.rootDomain = nullptr;
	}

	MonoAssembly* LoadAssembly(std::string_view filepath)
	{
		std::vector<uint8> file = io::ReadBinaryFile(filepath);
		ASSERT(!file.empty(), "C# assembly file=\"{0}\" did not exist.", filepath);

		MonoImageOpenStatus status;
		MonoImage* monoImage = mono_image_open_from_data_full((char*)file.data(), static_cast<uint32>(file.size()), TRUE, &status, FALSE);
		ASSERT(status == MONO_IMAGE_OK, "Failed to load mono image: {0}", mono_image_strerror(status));

		MonoAssembly* monoAssembly = mono_assembly_load_from_full(monoImage, filepath.data(), &status, FALSE);
		ASSERT(monoAssembly != nullptr, "Assembly from file=\"{0}\" failed to load.", filepath);

		mono_image_close(monoImage);
		return monoAssembly;
	}

	void PrintAssemblyTypes(MonoAssembly* assembly)
	{
		MonoImage* monoImage = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(monoImage, MONO_TABLE_TYPEDEF);
		sint32 typeCount = mono_table_info_get_rows(typeDefinitionsTable);

		for (sint32 i = 0; i < typeCount; i++)
		{
			uint32 columns[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, columns, MONO_TYPEDEF_SIZE);

			const char* monoNamespace = mono_metadata_string_heap(monoImage, columns[MONO_TYPEDEF_NAMESPACE]);
			const char* monoName = mono_metadata_string_heap(monoImage, columns[MONO_TYPEDEF_NAME]);

			LOG_CORE_INFO("{0}.{1}", monoNamespace, monoName);
		}
	}
}
