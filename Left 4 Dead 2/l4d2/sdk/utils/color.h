#pragma once

class Color {
public:
	inline Color()
	{
		*((int *)this) = 0;
	}
	inline Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 0);
	}
	inline Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 0);

	void GetColor(int &_r, int &_g, int &_b, int &_a) const;

	inline void SetRawColor(int color32)
	{
		*((int *)this) = color32;
	}

	inline int GetRawColor() const
	{
		return *((int *)this);
	}

	inline void getFloatArray(float *arr) const;

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	inline unsigned char &operator[](int index)
	{
		return _color[index];
	}

	inline const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	inline bool operator==(const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	inline bool operator!=(const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	inline Color &operator=(const Color &rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	float* Base();

	float Hue() const;

	float Saturation() const;

	float Brightness() const;

	Color FromHSB(float hue, float saturation, float brightness);

	static Color Red() { return Color(255, 0, 0); }
	static Color Green() { return Color(70, 255, 70); }
	static Color Blue() { return Color(0, 0, 255); }
	static Color LightBlue() { return Color(50, 160, 255); }
	static Color Grey() { return Color(128, 128, 128); }
	static Color DarkGrey() { return Color(45, 45, 45); }
	static Color Black() { return Color(0, 0, 0); }
	static Color White() { return Color(255, 255, 255); }
	static Color Purple() { return Color(220, 0, 220); }

private:
	unsigned char _color[4];
};
