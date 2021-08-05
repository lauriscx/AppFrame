#include "AppContext.h"

void AppContext::SetWindowWidth(float width) {
	m_Width = width;
}

void AppContext::SetWindowHeight(float height) {
	m_Height = height;
}

void AppContext::SetApplicationName(const char * name) {
	m_Name = name;
}

void AppContext::SetFPSLimit(int fps) {
	m_FPS = fps;
}

void AppContext::SetMemoryUsage(float memory) {
	m_MemoryUsage = memory;
}