#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/heap.h>

#include "segment.hpp"

int main()
{
	Segment* segment = (Segment*)sys_malloc(sizeof(Segment));
	segment->Initialise();

	int row;
	int column;
	unsigned short key;

	segment->x = 50;
	segment->y = 50;

	while (true)
	{
		segment->Draw();
		Bdisp_PutDisp_DD();

		PrintXY(1, 1, "--Drew triangle", TEXT_MODE_NORMAL, COLOR_BLACK);

		GetKeyWait_OS(&column, &row, KEYWAIT_HALTON_TIMEROFF, 1, 1, &key);

		PrintXY(1, 2, "--Key pressed", TEXT_MODE_NORMAL, COLOR_BLACK);

		if ((column == 0x05) && (row == 0x04))
		{
			segment->x = segment->x + 10;
		}
		else if ((column == 0x07) && (row == 0x04))
		{
			segment->x = segment->x - 10;
		}
		else if ((column == 0x06) && (row == 0x03))
		{
			segment->y = segment->y + 10;
		}
		else if ((column == 0x06) && (row == 0x05))
		{
			segment->y = segment->y - 10;
		}
	}

	segment->~Segment();
	sys_free(segment);

    return 0;
}