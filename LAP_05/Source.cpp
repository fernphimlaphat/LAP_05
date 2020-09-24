#include<stdio.h>
#include<windows.h>
#include<conio.h>

void draw(int x, int y) {

	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf(" <-0-> ");
}

void drawAmmo(int x, int y)
{
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf("O");

}
void deleteXY(int x, int y) {
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf("       ");

}

void deleteX(int x, int y) {
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf(" ");

}
void setcolor(int bg, int fg) {
	//bg background , fg foreground สีตัวอักษร
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //color = output
	SetConsoleTextAttribute(color, bg * 16 + fg); //(output ,เป็นอะไร)
}
void deletecolor(int bg, int fg) {
	bg = 0, fg = 0;
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, bg * 16 + fg);
}
void setcursor(bool visible) {
	//cusur หายไป
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Ipcursur;
	Ipcursur.bVisible = visible;
	Ipcursur.dwSize = 20;
	SetConsoleCursorInfo(console, &Ipcursur);

}

void auto_left(int x, int y)
{
	setcolor(6, 4);
	draw(x, y);
	Sleep(100);
	deletecolor(0, 0);
	deleteXY(x, y);
}

void auto_right(int x, int y)
{

	setcolor(6, 4);
	draw(x, y);

	deletecolor(0, 0);
	deleteXY(x + 8, y);

	Sleep(100);

	deletecolor(0, 0);
	deleteXY(x, y);
}

void Ammo(int x, int i)
{
	setcolor(5, 3);

	drawAmmo(x, i);
	deletecolor(0, 0);
	deleteX(x, i + 1);
}

void MoveAmmo(int x, int y, int i)
{

	for (i = y - 2; i >= 0; i--)
	{
		auto_left(x, y);

		Ammo(x + 3, i - 12);

		deleteXY(x + 2, y);

		Ammo(x + 3, i - 9);
		deleteXY(x + 4, y);

		Ammo(x + 3, i - 6);
		deleteXY(x + 6, y);

		Ammo(x + 3, i - 3);
		deleteXY(x + 8, y);

		Ammo(x + 3, i);
		deleteXY(x + 10, y);

		Sleep(1);



		deletecolor(0, 0);



		if (i == 0)
		{

			deleteX(x + 3, 0);
		}



	}
}

void Ship()
{

	setcursor(0);
	int x = 20, y = 20, i = y;
	setcolor(6, 4);
	draw(x, y);

	char m = ' ';


	do
	{
		if (_kbhit)
		{
			m = _getch();
			if (m == 'a') {


				for (x; x >= 0; x--)
				{

					auto_left(x, y);

					if (x == 0)
					{
						setcolor(6, 4);
						draw(x, y);
					}

					if (_kbhit())
					{
						m = _getch();
						if (m == 's') { setcolor(6, 4); draw(x, y);  break; }
						else if (m == ' ')
						{
							MoveAmmo(x, y, i);

							if (x == 0)
							{
								setcolor(6, 4);
								draw(x, y);
							}
						}

					}
				}


			}

			else if (m == 'd')
			{
				for (x; x <= 80; x++)
				{
					auto_right(x, y);
					if (x == 80)
					{
						setcolor(6, 4);
						draw(x + 1, y);
					}

					if (_kbhit())
					{
						m = _getch();
						if (m == 's')
						{
							setcolor(6, 4); draw(x, y); break;
						}

						else if (m == ' ')
						{
							MoveAmmo(x, y, i);

							if (x == 80)
							{
								setcolor(6, 4);
								draw(x, y);
							}
						}



					}

				}
			}

			else if (m == ' ')
			{
				MoveAmmo(x, y, i);
				setcolor(6, 4);
				draw(x, y);
			}



		}

	} while (m != 'x');



}


int main() {
	
	Ship();
	


}