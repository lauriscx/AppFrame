#pragma once
#include "Core/Asserts.h"
#include <future>

namespace Engine {

	/*enum ExecutionFlag {
		Async = std::launch::async,
		Deffered = std::launch::deferred
	};*/

	template<typename T>
	class Task {
	public:
		Task() : m_ExecutionFlag((int)std::launch::async/*ExecutionFlag::Async*/) {}

		//inline void SetExecutionFlag(ExecutionFlag flag) { m_ExecutionFlag = flag; };

		template<typename... Args, typename F>
		inline void CreateAsyncTask(const F& function, Args&&... args) {
			m_Results = std::async((std::launch)m_ExecutionFlag, function, std::forward<Args>(args)...);
			m_Retrieved = false;
		}
		inline bool IsCompleted()	{ return m_Results._Is_ready(); }
		inline bool IsRetrieved()	{ return m_Retrieved; }
		inline bool IsAccessible()	{ return !m_Retrieved && m_Results._Is_ready(); }
		inline T	GetResults()	{ ASSERT(!m_Retrieved); m_Retrieved = true;	return m_Results._Get_value(); }

		virtual ~Task() {}
	private:
		int m_ExecutionFlag;
		bool m_Retrieved;
		std::future<T> m_Results;
	};
}