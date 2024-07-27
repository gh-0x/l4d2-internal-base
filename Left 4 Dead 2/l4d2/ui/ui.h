#include "../../std.h"

struct ui {
public:
	void run();
	void initialize(IDirect3DDevice9* device);
	void undo();
	void toggle();
private:
	bool               m_opened = {};
	IDirect3DTexture9* kb_icon = {};
};

extern ui g_ui;