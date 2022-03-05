#include "ScriptAssembly.h"

ScriptAssembly::ScriptAssembly(const std::string& Name, const std::string& AssemblyName) {
	//Examples https://cpp.hotexamples.com/examples/-/-/mono_add_internal_call/cpp-mono_add_internal_call-function-examples.html
	mono_set_dirs(".", ".");//Set where to search for assembly file.(Location is project file whihc is has kind application or console application(exe)).
	m_AssemblyName = AssemblyName;
	m_PtrMonoDomain = mono_jit_init(Name.c_str());//Unknow why here we neeed provide this string.
	if (m_PtrMonoDomain) {
		//Information which is usefull to implement load dll from VFS https://stackoverflow.com/questions/36094802/embeded-mono-load-assemblies-from-memory
		m_PtrAssembly = mono_domain_assembly_open(m_PtrMonoDomain, (AssemblyName + std::string(".dll")).c_str());//In feature need change to us VFS 
		if (m_PtrAssembly) {
			m_PtrAssemblyImage = mono_assembly_get_image(m_PtrAssembly);
		}
	}
}

Class * ScriptAssembly::GetClass(std::string className) {
	if (m_PtrAssemblyImage) {
		m_Classes[className] = Class(m_PtrAssemblyImage, className, m_AssemblyName);
		return &m_Classes[className];
	}
	return nullptr;
}

ScriptAssembly::~ScriptAssembly() {
	if (m_PtrMonoDomain) {
		mono_jit_cleanup(m_PtrMonoDomain);//if used mono_jit_init need use mono_jit_clean (probably).
	}
}
