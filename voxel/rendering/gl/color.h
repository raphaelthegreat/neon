#pragma once

class Color {
public:
	Color(float r, float g, float b, float a = 1.0f);

	void set_color(float r, float g, float b);
	void set_alpha(float a);

	float red() const { return _r; }
	float green() const { return _g; }
	float blue() const { return _b; }
	float alpha() const { return _a; }

protected:
	float _r = 0;
	float _g = 0;
	float _b = 0;
	float _a = 1;
};

#define RED Color(1.0f, 0.0f, 0.0f)
#define GREEN Color(0.0f, 1.0f, 0.0f)
#define BLUE Color(0.0f, 0.0f, 1.0f)
#define PURPLE Color(1.0f, 0.0f, 1.0f)
#define YELLOW Color(1.0f, 1.0f, 0.0f)
#define CYAN Color(0.0f, 1.0f, 1.0f)
#define BLACK Color(0.0f, 0.0f, 0.0f)
#define WHITE Color(1.0f, 1.0f, 1.0f)

void clear_display();
void clear_display(float r, float g, float b, float a);
void clear_display(Color color);
