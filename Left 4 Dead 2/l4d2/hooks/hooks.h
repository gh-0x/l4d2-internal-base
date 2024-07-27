#pragma once

#define REINTERPRET_P reinterpret_cast<void*>
#define REINTERPRET_PP reinterpret_cast<void**>

struct hooks {
public:
	void initialize();
	void undo();
};

extern hooks g_hooks;