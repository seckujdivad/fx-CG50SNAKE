#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/heap.h>
#include "fxcg/rtc.h"

#include "snake.hpp"
#include "segment.hpp"

void SetRandomFoodPos(Segment* food, Snake* snake)
{
	//while (snake->CollidesWith(food, true, true))
	//{
		food->x = 15 * (RTC_GetTicks() % ((LCD_WIDTH_PX / 15) - 2)) + 30;
		food->y = 15 * (RTC_GetTicks() % ((LCD_HEIGHT_PX / 15) - 2)) + 30;
	//}

	food->Draw();
}

void SetBackground(color_t colour)
{
	for (int i = 0; i < LCD_WIDTH_PX; i++)
	{
		for (int j = 0; j < LCD_HEIGHT_PX; j++)
		{
			Bdisp_SetPoint_VRAM(i, j, colour);
		}
	}
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

	int state = 0; // 0: menu, 1: playing, 2: death screen

	Snake* snake;
	Segment* food;

	while (true)
	{
		if ((RTC_GetTicks() - last_refresh) > 20)
		{
			DisplayStatusArea();

			if (state == 0)
			{

				PrintXY(1, 1, "--SNAKE", TEXT_MODE_NORMAL, COLOR_BLACK);
				PrintXY(1, 2, "--F1: start", TEXT_MODE_NORMAL, COLOR_BLACK);

				Bdisp_PutDisp_DD();
			}
			else if (state == 1)
			{
				snake->MoveForward();

				Bdisp_PutDisp_DD();

				last_refresh = RTC_GetTicks();

				snake->GetHeadPos(&snake_head_x, &snake_head_y);
				if ((snake_head_x == food->x) && (snake_head_y == food->y))
				{
					snake->NewSegment(false);
					SetRandomFoodPos(food, snake);
				}

				if (snake->CollidesWith(snake->GetHeadSegment(), true, false))
				{
					state = 2;

					snake->~Snake();
					sys_free(snake);

					food->~Segment();
					sys_free(food);
				}
			}
			else if (state == 2)
			{
				PrintXY(1, 1, "--Game Over", TEXT_MODE_NORMAL, COLOR_BLACK);
				PrintXY(1, 2, "--F2: menu", TEXT_MODE_NORMAL, COLOR_BLACK);

				Bdisp_PutDisp_DD();
			}
		}

		keypress_type = GetKeyWait_OS(&column, &row, KEYWAIT_HALTOFF_TIMEROFF, 1, 1, &key);

		if (keypress_type == KEYREP_KEYEVENT)
		{
			if ((column == 0x04) && (row == 0x09)) //pressing menu sends keypresses to the calculator. they can then press menu again
			{
				SetBackground(COLOR_WHITE);

				PrintXY(1, 1, "--Menu: exit to main", TEXT_MODE_NORMAL, COLOR_BLACK);
				state = 0;
				
				GetKey(&getkey);

				SetBackground(COLOR_WHITE);
			}

			if (state == 0)
			{
				if ((column == 0x07) && (row == 0x0A))
				{
					SetBackground(COLOR_WHITE);

					snake = (Snake*)sys_malloc(sizeof(Snake));
					snake->Initialise();

					food = (Segment*)sys_malloc(sizeof(Segment));
					food->Initialise(15, COLOR_RED, COLOR_BLUE);
					SetRandomFoodPos(food, snake);

					state = 1;
				}
			}
			else if (state == 1)
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
			}
			else if (state == 2)
			{
				if ((column == 0x06) && (row == 0x0A))
				{
					state = 0;

					SetBackground(COLOR_WHITE);
				}
			}
		}
	}

	snake->~Snake();
	sys_free(snake);
    return 0;
}