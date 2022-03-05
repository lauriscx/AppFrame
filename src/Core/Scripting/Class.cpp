#include "Class.h"

Class::Class(MonoImage * assemblyImage, const std::string& className, const std::string& assemblyName) {
	m_AssemblyImage = assemblyImage;
	m_Class = mono_class_from_name(assemblyImage, assemblyName.c_str(), className.c_str());
	m_ClassName = className;
}

void Class::LinkMethod(const std::string & name, const void* method) {
	mono_add_internal_call(name.c_str(), method);
}

Method * Class::GetMethod(const std::string & methodName) {
	if (m_Class) {
		m_Methods[methodName] = Method(m_Class, m_ClassName, methodName);
		return &m_Methods[methodName];
	}
	return nullptr;
}

Class::~Class() {

}