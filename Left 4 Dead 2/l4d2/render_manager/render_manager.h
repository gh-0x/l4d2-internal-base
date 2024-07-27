#pragma once

#include "../../std.h"

#include <d3d9.h>
#include <d3dx9.h>

struct vertex {
	float x, y, z, rhw;
	unsigned long color;
};

struct render_manager {
public:
	IDirect3DDevice9*                        m_device = {};
	ID3DXLine*                               m_line = {};
	D3DVIEWPORT9                             m_viewport = {};
	IDirect3DStateBlock9*	                 m_block = {};

	struct fonts {
	public:
		ID3DXFont*                           m_font = {};
		ID3DXFont*                           m_icons_font = {};
	};
public:
	void initialize(IDirect3DDevice9* device);
	void undo();

	void begin_render_states(IDirect3DDevice9* device);
	void end_render_states(IDirect3DDevice9* device);

	void create_objects();

	void draw_line(int x0, int y0, int x1, int y1, unsigned long color);
	void draw_rect(int x, int y, int w, int h, unsigned long color);
	void draw_filled_rect(int x, int y, int w, int h, unsigned long color);
	void draw_outlined_rect(int x, int y, int w, int h, unsigned long color);
	void draw_text(const std::string& string, int x, int y, ID3DXFont* font, unsigned long color, bool center, bool outline);

	unsigned long create_col(float col[4]);

	RECT get_text_dimensions(const std::string& string, ID3DXFont* font);
	int get_text_width(const std::string& string, ID3DXFont* font);
	int get_text_height(const std::string& string, ID3DXFont* font);
};

extern render_manager g_render;
extern render_manager::fonts g_fonts;