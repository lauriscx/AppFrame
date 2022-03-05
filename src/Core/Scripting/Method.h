#pragma once
#include <map>
#include <mono/jit/jit.h>
#include <mono/metadata/debug-helpers.h>
#include <vector>
#include <any>

class Method {
public:
	Method() = default;
	Method(MonoClass* _class, const std::string& className, const std::string& name);

	MonoObject* InvokeStatic();
	MonoObject* InvokeVirtual();
	MonoObject* Invoke();
	template <class ...Args>
	MonoObject* Invoke(const Args&... args);


	~Method();
private:
	std::map<std::string, Method> m_Methods;
	std::string m_ClassName;

	//MONO
private:
	MonoMethodDesc* m_MethodDesc = nullptr;
	MonoMethod* m_Method = nullptr;
	MonoMethod* m_MethodVirtual = nullptr;
	MonoObject* m_return = nullptr;
	MonoClass* m_Class = nullptr;
};

template<class ...Args>
inline MonoObject * Method::Invoke(const Args & ...args) {
	std::vector<std::any> _args = { args... };

	void** __args = new void*[_args.size()];

	for (uint32_t i = 0; i < _args.size(); i++) {
		__args[i] = (void*)&_args[i];
	}

	m_return = nullptr;
	mono_runtime_invoke(m_Method, m_Class, __args, &m_return);
	delete __args;
	return m_return;
}
