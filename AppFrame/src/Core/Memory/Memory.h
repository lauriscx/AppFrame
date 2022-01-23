#pragma once
#include <iostream>

namespace AppFrame {
	namespace Memory {

		/*
		 * Deleting object then created Scope object
		 * goes out of scope or is assigned to other value.
		 * You can't copy Scope or have 2 pointers
		 * pointing to the same memory address.
		*/
		template<typename T>
		using Scope = std::unique_ptr<T>;

		/*
		 * Create a Scope.
		 * Uses constexpr to determent data type in
		 * compile time. This function return created
		 * Scope with prefered data.
		*/
		template<typename T, typename ... Args>
		constexpr Scope<T> CreateScope(Args&& ... args) {
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		/*
		 * Counting reference. If reference
		 * count is zero the delete(release memory).
		*/
		template<typename T>
		using Reference = std::shared_ptr<T>;

		/*
		 * Create a reference.
		 * Uses constexpr to determent data type in
		 * compile time. This function return created
		 * Reference with prefered data.
		*/
		template<typename T, typename ... Args>
		constexpr Reference<T> CreateReference(Args&& ... args) {
			return std::make_shared<T>(std::forward<Args>(args)...);
		}

		/*
		 * This type is used to pass Reference pointer
		 * to other function without increasing
		 * reference count.
		*/
		template<typename T>
		using PassReference = std::weak_ptr<T>;

		/*
		 * Then is used define DEBUG and MEORY_LEAK
		 * together you can see in console printing
		 * meory alocation and releasion operations.
		*/
	};
};

#if defined(_DEBUG)//Only for VS
/*
static __int64 m_MemoryAllocated = 0;
static __int64 m_MemoryRelease = 0;
static __int64 m_MemoryCurrentMemory = 0;

void * operator new(size_t size) {
	//std::cout << "Allocated memory " << size << std::endl;
	//void * p = ::operator new(size);
	void * p = malloc(size); //will also work fine
	m_MemoryAllocated += size;
	m_MemoryCurrentMemory += size;

	return p;
}

void operator delete(void * p, std::size_t size) {
	//std::cout << "Releasing memory " << size << std::endl;

	
	//Big red warnning!!! If you start suddently get memory leak error probably
	//you alocate memory in one module and release in another.
	
#ifdef NO_MEMORY_BUG
	if (m_MemoryCurrentMemory >= (m_MemoryCurrentMemory - size)) {
		m_MemoryCurrentMemory -= size;
		m_MemoryRelease += size;
	} else {
		m_MemoryCurrentMemory = 0;
		m_MemoryRelease = m_MemoryAllocated;
	}
#else
	m_MemoryCurrentMemory -= size;
	m_MemoryRelease += size;
#endif
	free(p);
}
*/
#endif // DEBUG