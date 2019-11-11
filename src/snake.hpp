#pragma once

#include <fxcg/heap.h>
#include <fxcg/display.h>

#include "segment.hpp"

class Snake
{
private:
	int m_segments_length_max;
	int m_segments_length;
	Segment** m_segments;

	color_t m_background_colour;

	color_t m_head_fill;
	color_t m_head_outline;
	color_t m_body_fill;
	color_t m_body_outline;

	int m_segment_size;

	int m_prev_direction;
	int m_direction;

	int m_start_x;
	int m_start_y;

	void ExtendSegmentsArray();

public:
	Snake();
	void Initialise();
	~Snake();

	void NewSegment(bool is_head);

	void SetDirection(int direction);
	void MoveForward();
};