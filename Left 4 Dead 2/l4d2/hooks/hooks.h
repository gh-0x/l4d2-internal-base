#pragma once

#define REINTERPRET_P reinterpret_cast<void*>
#define REINTERPRET_PP reinterpret_cast<void**>

struct hooks {
public:
	void initialize();
	void undo();
private:
	inline unsigned int get_virtual(void* _class, unsigned int index) {
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]);
	}
};

extern hooks g_hooks;