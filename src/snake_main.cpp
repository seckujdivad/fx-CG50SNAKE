#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/heap.h>
#include "fxcg/rtc.h"

#include "snake.hpp"

int main()
{
	int row;
	int column;
	unsigned short key;
	int getkey;
	int keypress_type;

	int last_refresh = RTC_GetTicks() - 10000;

	bool run_main = true;

	Snake* snake = (Snake*)sys_malloc(sizeof(Snake));
	snake->Initialise();

	while (run_main)
	{
		if ((RTC_GetTicks() - last_refresh) > 50)
		{
			snake->MoveForward();
			Bdisp_PutDisp_DD();
			last_refresh = RTC_GetTicks();
		}

		keypress_type = GetKeyWait_OS(&column, &row, KEYWAIT_HALTOFF_TIMEROFF, 1, 1, &key);

		if (keypress_type == KEYREP_KEYEVENT)
		{
			if ((column == 0x05) && (row == 0x04))
			{
				snake->SetDirection(1);
			}
			else if ((column == 0x07) && (row == 0x04))
			{
				snake->SetDirection(3);
			}
			else if ((column == 0x06) && (row == 0x03))
			{
				snake->SetDirection(2);
			}
			else if ((column == 0x06) && (row == 0x05))
			{
				snake->SetDirection(0);
			}
			else if ((column == 0x04) && (row == 0x09))
			{
				GetKey(&getkey);
			}
		}
	}

	snake->~Snake();
	sys_free(snake);
    return 0;
}