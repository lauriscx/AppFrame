#pragma once
#include "Core/Scripting/Method.h"
#include <map>
#include <mono/jit/jit.h>
#include <mono/metadata/debug-helpers.h>

class Class {
public:
	Class() = default;
	Class(MonoImage* assemblyImage, const std::string& className, const std::string& assemblyName);

	void LinkMethod(const std::string& name, const void* method);

	Method* GetMethod(const std::string& methodName);

	~Class();
private:
	std::map<std::string, Method> m_Methods;
	std::string m_ClassName;

	//MONO
private:
	MonoImage* m_AssemblyImage = nullptr;
	MonoClass* m_Class = nullptr;
};