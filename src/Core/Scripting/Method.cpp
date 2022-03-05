#include "Method.h"

Method::Method(MonoClass * _class, const std::string& className, const std::string & name) {
	m_Class = _class;
	m_ClassName = className;
	if (_class) {
		std::string MethodDescriptionName = ".";
		MethodDescriptionName += className;
		MethodDescriptionName += ":";
		MethodDescriptionName += name;
		m_MethodDesc = mono_method_desc_new(MethodDescriptionName.c_str(), false);
		if (m_MethodDesc) {
			m_Method = mono_method_desc_search_in_class(m_MethodDesc, m_Class);
		}

		/*if (m_MethodDesc) {
			MonoMethod* virtualMethod = mono_method_desc_search_in_class(m_MethodDesc, m_Class);
			//Instead of nullptr here need class which inheret this function and overrides it.
			m_MethodVirtual = mono_object_get_virtual_method(nullptr, virtualMethod);
		}*/
	}
}

MonoObject * Method::InvokeStatic() {
	m_return = nullptr;
	mono_runtime_invoke(m_Method, nullptr, nullptr, &m_return);
	return m_return;
}

MonoObject * Method::InvokeVirtual() {
	m_return = nullptr;
	if (m_MethodVirtual) {
		mono_runtime_invoke(m_MethodVirtual, m_Class, nullptr, &m_return);
	}
	return m_return;
}

MonoObject * Method::Invoke() {
	m_return = nullptr;
	mono_runtime_invoke(m_Method, m_Class, nullptr, &m_return);
	return m_return;
}

Method::~Method() {
	if (m_MethodDesc) {
		mono_method_desc_free(m_MethodDesc);
	}
}