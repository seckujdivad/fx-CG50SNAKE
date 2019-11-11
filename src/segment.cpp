#include "segment.hpp"

Segment::Segment()
{
	this->Initialise();
}

Segment::~Segment()
{

}

void Segment::Initialise()
{
	this->m_colour_fill = COLOR_BLACK;
	this->m_colour_outline = COLOR_RED;

	this->m_size_x = 10;
	this->m_size_y = 10;

	this->x = 0;
	this->y = 0;
}

void Segment::Draw()
{
	this->Draw(this->m_colour_fill, this->m_colour_outline);
}

void Segment::Draw(color_t fill, color_t outline)
{
	int start_x = this->x - (this->m_size_x / 2);
	int end_x = this->x + (this->m_size_x / 2);
	int start_y = this->y - (this->m_size_y / 2);
	int end_y = this->y + (this->m_size_y / 2);

	if (start_x < 0)
	{
		start_x = 0;
	}

	if (start_y < 0)
	{
		start_y = 0;
	}

	if (end_x > LCD_WIDTH_PX)
	{
		end_x = LCD_WIDTH_PX;
	}

	if (end_y > LCD_HEIGHT_PX)
	{
		end_y = LCD_HEIGHT_PX;
	}

	if (!((start_x > LCD_WIDTH_PX) || (start_y > LCD_HEIGHT_PX) || (end_x < 0) || (end_y < 0)))
	{
		for (int x = start_x; x < end_x; x++)
		{
			for (int y = start_y; y < end_y; y++)
			{
				if ((x == start_x) || (x == end_x) || (y == start_y) || (y == end_y))
				{
					Bdisp_SetPoint_VRAM(x, y, this->m_colour_outline);
				}
				else
				{
					Bdisp_SetPoint_VRAM(x, y, this->m_colour_fill);
				}
			}
		}
	}
}