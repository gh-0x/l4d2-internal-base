#include "../../std.h"

struct ui {
public:
	void run();
	void initialize(IDirect3DDevice9* device);
	void undo();
	void toggle();
private:
	bool               m_opened = {};
};

extern ui g_ui;
