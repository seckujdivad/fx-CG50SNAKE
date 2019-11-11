#include "snake.hpp"

Snake::Snake()
{

}

Snake::~Snake()
{
	for (int i = 0; i < this->m_segments_length; i++)
	{
		this->m_segments[i]->Draw(this->m_background_colour, this->m_background_colour);

		this->m_segments[i]->~Segment();
		sys_free(this->m_segments[i]);
	}

	sys_free(this->m_segments);
}

void Snake::Initialise()
{
	this->m_segments_length = 0;
	this->m_segments_length_max = 2;

	this->m_background_colour = COLOR_WHITE;

	this->m_head_fill = COLOR_RED;
	this->m_head_outline = COLOR_BLACK;
	this->m_body_fill = COLOR_GREEN;
	this->m_body_outline = COLOR_GREENYELLOW;

	this->m_segment_size = 15;

	this->m_start_x = 15 * 10;
	this->m_start_y = 15 * 10;

	this->m_segments = (Segment**)sys_malloc(sizeof(Segment*) * this->m_segments_length_max);

	this->m_direction = 0;
	this->m_prev_direction = -1;

	this->NewSegment(true);
	this->NewSegment(false);
}

void Snake::NewSegment(bool is_head)
{
	if (this->m_segments_length >= this->m_segments_length_max)
	{
		this->ExtendSegmentsArray();
	}

	this->m_segments[this->m_segments_length] = (Segment*)sys_malloc(sizeof(Segment));

	if (is_head)
	{
		this->m_segments[this->m_segments_length]->Initialise(this->m_segment_size, this->m_head_fill, this->m_head_outline);

		this->m_segments[this->m_segments_length]->x = this->m_start_x;
		this->m_segments[this->m_segments_length]->y = this->m_start_y;
	}
	else
	{
		this->m_segments[this->m_segments_length]->Initialise(this->m_segment_size, this->m_body_fill, this->m_body_outline);
		
		this->m_segments[this->m_segments_length]->x = this->m_segments[this->m_segments_length - 1]->x;
		this->m_segments[this->m_segments_length]->y = this->m_segments[this->m_segments_length - 1]->y;
	}

	this->m_segments[this->m_segments_length]->Draw();
	
	this->m_segments_length++;
}

void Snake::ExtendSegmentsArray()
{
	this->m_segments_length_max = this->m_segments_length_max * 2;

	Segment** new_array = (Segment**)sys_malloc(sizeof(Segment*) * this->m_segments_length_max);

	for (int i = 0; i < this->m_segments_length; i++)
	{
		new_array[i] = this->m_segments[i];
	}

	sys_free(this->m_segments);
	this->m_segments = new_array;
}

void Snake::SetDirection(int direction)
{
	if (direction != this->m_prev_direction)
	{
		this->m_direction = direction;
	}
}

void Snake::MoveForward()
{
	this->m_prev_direction = this->m_direction;

	this->m_segments[this->m_segments_length - 1]->Draw(this->m_background_colour, this->m_background_colour);

	bool bunch_found = false;
	for (int i = 1; i < this->m_segments_length; i++)
	{
		if ((this->m_segments[i]->x == this->m_segments[i + 1]->x) && (this->m_segments[i]->y == this->m_segments[i + 1]->y))
		{
			bunch_found = true;
		}
		else if (!bunch_found)
		{
			this->m_segments[i]->x = this->m_segments[i - 1]->x;
			this->m_segments[i]->y = this->m_segments[i - 1]->y;
		}
	}
	
	this->m_segments[1]->Draw();

	if (this->m_direction == 0)
	{
		this->m_segments[0]->y = this->m_segments[0]->y - this->m_segment_size;
	}
	else if (this->m_direction == 1)
	{
		this->m_segments[0]->x = this->m_segments[0]->x + this->m_segment_size;
	}
	else if (this->m_direction == 2)
	{
		this->m_segments[0]->y = this->m_segments[0]->y + this->m_segment_size;
	}
	else if (this->m_direction == 3)
	{
		this->m_segments[0]->x = this->m_segments[0]->x - this->m_segment_size;
	}

	this->m_segments[0]->Draw();
}

void Snake::GetHeadPos(int* x, int* y)
{
	*x = this->m_segments[0]->x;
	*y = this->m_segments[0]->y;
}