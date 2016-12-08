#pragma once
class Color
{
private:
	int var;
public:
	explicit Color(int c = 0) : var(c) {}
	inline const int getColorNum() const { return var; }
	
	static Color Black() { return Color(0); }
	static Color Blue() { return Color(1); }
	static Color Green() { return Color(2); }
	static Color Jade() { return Color(3); }
	static Color Red() { return Color(4); }
	static Color ReddishPurple() { return Color(5); }
	static Color Yellow() { return Color(6); }
	static Color White() { return Color(7); }
	static Color Gray() { return Color(8); }
	static Color SoftBlue() { return Color(9); }
	static Color SoftGreen() { return Color(10); }
	static Color SoftJade() { return Color(11); }
	static Color SoftRed() { return Color(12); }
	static Color SoftReddishPurple() { return Color(13); }
	static Color SoftYellow() { return Color(14); }
	static Color DeepWhite() { return Color(15); }
};