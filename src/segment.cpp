#include "segment.hpp"

Segment::Segment()
{
	this->Initialise(10, COLOR_WHITE, COLOR_BLACK);
}

Segment::~Segment()
{

}

void Segment::Initialise(int size, color_t fill, color_t outline)
{
	this->SetColours(fill, outline);

	this->m_size_x = size;
	this->m_size_y = size;

	this->x = 0;
	this->y = 0;

	this->m_outline_width = 2;
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
				if ((x < start_x + this->m_outline_width) || (x > end_x - this->m_outline_width - 1) || (y < start_y + this->m_outline_width) || (y > end_y - this->m_outline_width - 1))
				{
					Bdisp_SetPoint_VRAM(x, y, outline);
				}
				else
				{
					Bdisp_SetPoint_VRAM(x, y, fill);
				}
			}
		}
	}
}

void Segment::SetColours(color_t fill, color_t outline)
{
	this->m_colour_fill = fill;
	this->m_colour_outline = outline;
}