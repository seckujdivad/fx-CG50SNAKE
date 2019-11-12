#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/heap.h>
#include "fxcg/rtc.h"

#include "snake.hpp"
#include "segment.hpp"

void SetRandomFoodPos(Segment* food)
{
	food->x = 15 * (RTC_GetTicks() % ((LCD_WIDTH_PX / 15) - 2)) + 30;
	food->y = 15 * (RTC_GetTicks() % ((LCD_HEIGHT_PX / 15) - 2)) + 30;

	food->Draw();
}

int main()
{
	int row;
	int column;
	unsigned short key;
	int getkey;
	int keypress_type;

	int snake_head_x;
	int snake_head_y;

	int last_refresh = RTC_GetTicks() - 10000;

	bool run_main = true;

	Snake* snake = (Snake*)sys_malloc(sizeof(Snake));
	snake->Initialise();

	Segment* food = (Segment*)sys_malloc(sizeof(Segment));
	food->Initialise(15, COLOR_RED, COLOR_BLUE);
	SetRandomFoodPos(food);

	while (run_main)
	{
		if ((RTC_GetTicks() - last_refresh) > 20)
		{
			snake->MoveForward();
			Bdisp_PutDisp_DD();
			last_refresh = RTC_GetTicks();

			snake->GetHeadPos(&snake_head_x, &snake_head_y);
			if ((snake_head_x == food->x) && (snake_head_y == food->y))
			{
				snake->NewSegment(false);
				SetRandomFoodPos(food);
			}
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