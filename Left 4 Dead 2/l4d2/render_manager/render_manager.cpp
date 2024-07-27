#include "render_manager.h"

#include "../../utils/utils.h"

render_manager g_render;
render_manager::fonts g_fonts;

void render_manager::initialize(IDirect3DDevice9* device)
{
	if (!m_device)
		m_device = device;

	create_objects();
}

void render_manager::undo()
{
	if (m_line) {
		m_line->Release();
		m_line = nullptr;
	}

	if (g_fonts.m_font) {
		g_fonts.m_font->Release();
		g_fonts.m_font = nullptr;
	}

	if (g_fonts.m_icons_font) {
		g_fonts.m_icons_font->Release();
		g_fonts.m_icons_font = nullptr;
	}

	if (m_block) {
		m_block->Release();
		m_block = nullptr;
	}
}

void render_manager::create_objects()
{
	if (FAILED(D3DXCreateLine(m_device, &m_line)))
		return;

	if (FAILED(D3DXCreateFontA(m_device, 12, 0, FW_DONTCARE, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, X_("Verdana"), &g_fonts.m_font)))
		return;

	if (FAILED(D3DXCreateFontA(m_device, 20, 0, FW_LIGHT, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, X_("left4dead_icons"), &g_fonts.m_icons_font)))
		return;

	if (FAILED(m_device->CreateStateBlock(D3DSBT_ALL, &m_block)))
		return;
}

void render_manager::begin_render_states(IDirect3DDevice9* device)
{
	if (!m_device)
		return;

	m_block->Capture();

	device->SetVertexShader(nullptr);
	device->SetPixelShader(nullptr);

	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_FOGENABLE, false);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	device->SetRenderState(D3DRS_STENCILENABLE, false);

	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);
	device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, true);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);

	device->SetTexture(0, nullptr);
	device->SetTexture(1, nullptr);
	device->SetTexture(2, nullptr);
	device->SetTexture(3, nullptr);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	device->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
}

void render_manager::end_render_states(IDirect3DDevice9* device)
{
	m_block->Apply();
}

void render_manager::draw_line(int x0, int y0, int x1, int y1, unsigned long color)
{
	D3DXVECTOR2 lines[2] = {
		D3DXVECTOR2(x0, y0), D3DXVECTOR2(x1, y1)
	};

	m_line->Begin();
	m_line->Draw(lines, 2, color);
	m_line->End();
}

void render_manager::draw_rect(int x, int y, int w, int h, unsigned long color)
{
	draw_line(x, y, x + w, y, color);
	draw_line(x, y, x, y + h, color);
	draw_line(x + w, y, x + w, y + h, color);
	draw_line(x, y + h, x + w + 1, y + h, color);
}

void render_manager::draw_filled_rect(int x, int y, int w, int h, unsigned long color)
{
	vertex v[4] = {
		{ float(x), float(y + h), 0.f, 1.f, color },
		{ float(x), float(y), 0.f, 1.f, color },
		{ float(x + w), float(y + h), 0.f, 1.f, color },
		{ float(x + w), float(y) , 0.f, 1.f, color }
	};

	m_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(vertex));
}

void render_manager::draw_outlined_rect(int x, int y, int w, int h, unsigned long color)
{
	draw_rect(x - 1, y - 1, w + 2, h + 2, D3DCOLOR_RGBA(1, 1, 1, 255));
	draw_rect(x + 1, y + 1, w - 2, h - 2, D3DCOLOR_RGBA(1, 1, 1, 255));

	draw_rect(x, y, w, h, color);
}

void render_manager::draw_text(const std::string& string, int x, int y, ID3DXFont* font, unsigned long color, bool center, bool outline)
{
	auto DrawTextA = [&](const std::string& _string, int _x, int _y, unsigned long _color) {
		RECT r{ _x, _y, _x, _y };
		font->DrawTextA(NULL, _string.c_str(), -1, &r, DT_NOCLIP, _color);
	};

	if (outline) {
		DrawTextA(string, x - 1, y, D3DCOLOR_RGBA(1, 1, 1, 255));
		DrawTextA(string, x + 1, y, D3DCOLOR_RGBA(1, 1, 1, 255));
		DrawTextA(string, x, y - 1, D3DCOLOR_RGBA(1, 1, 1, 255));
		DrawTextA(string, x, y + 1, D3DCOLOR_RGBA(1, 1, 1, 255));
	}

	DrawTextA(string, center ? x - get_text_width(string, font) / 2 : x, y, color);
}

unsigned long render_manager::create_col(float col[4])
{
	return D3DCOLOR_RGBA(g_utils.float_to_rgb(col[0]), g_utils.float_to_rgb(col[1]),
		g_utils.float_to_rgb(col[2]), g_utils.float_to_rgb(col[3]));
}

RECT render_manager::get_text_dimensions(const std::string& string, ID3DXFont* font)
{
	RECT r;
	font->DrawTextA(NULL, string.c_str(), -1, &r, DT_CALCRECT, 0xFFFFFFFF);
	return r;
}

int render_manager::get_text_width(const std::string& string, ID3DXFont* font)
{
	RECT r = get_text_dimensions(string, font);
	return r.right - r.left;
}

int render_manager::get_text_height(const std::string& string, ID3DXFont* font)
{
	RECT r = get_text_dimensions(string, font);
	return r.bottom - r.top;
}