#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/debug-helpers.h>
#include <map>
#include "Core/Scripting/Class.h"
#include "mono/metadata/assembly.h"

class ScriptAssembly {
public:
	ScriptAssembly(const std::string& Name, const std::string& AssemblyName);

	Class* GetClass(std::string className);

	~ScriptAssembly();
private:
	std::map<std::string, Class> m_Classes;
	std::string m_AssemblyName;

private://MONO
	MonoDomain* m_PtrMonoDomain = nullptr;//Script container in which we load script assembly(probably).
	MonoAssembly* m_PtrAssembly = nullptr;//Script assembly can be loaded directi from file or implemented use VFS.
	MonoImage* m_PtrAssemblyImage = nullptr;//Assembly image in this object is mapped classes(probably).
};