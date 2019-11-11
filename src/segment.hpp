#pragma once
#include <fxcg/display.h>

class Segment
{
private:
	color_t m_colour_fill;
	color_t m_colour_outline;

	int m_size_x;
	int m_size_y;
	
public:
	int x;
	int y;

	Segment();
	void Initialise();
	~Segment();

	void Draw();
	void Draw(color_t fill, color_t outline);
};