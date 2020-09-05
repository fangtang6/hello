#include<cstdio>
#include<Windows.h>
#include<conio.h>

//全局变量	
int high, width;				//	游戏界面尺寸
int bird_x, bird_y;				//	小鸟位置
int bird_vx, bird_vy;			//	小球速度
int bar_y, bar_xTop, bar_xDown; //  障碍物
int score;

void gotoxy(int x, int y)  //光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup() {	//数据初始化
	high = 15;
	width = 35;

	bird_x = 0;
	bird_y = 5;

	bird_vx = 1;
	bird_vy = 0;

	bar_y = width;
	bar_xTop = high / 4;
	bar_xDown = bar_xTop + 5;

	HideCursor();
}
void show() {				//显示界面
	gotoxy(0, 0);			//
	for (int i = 0; i <= high + 1; ++i) {
		for (int j = 0; j <= width + 1; ++j) {
			if ((i == bird_x) && (j == bird_y))
				printf("@");				//输出小鸟
			else if ((j == bar_y) && ((i <= bar_xTop) | (bar_xDown <= i )))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("得分: %d\n", score);
}
void updateWithoutInput() {		//与用户输入无关的更新 

	static int speed = 0;
	if (speed < 2)
		++speed;
	else {
		//根据速度更新小球位置
		bird_x += bird_vx;
		bird_y += bird_vy;

		//障碍物向左移动
		if (0 < bar_y) {
			bar_y--;
		}
		else {
			int rand_position = rand() % (high - 5);
			bar_xTop = rand_position;
			bar_xDown = bar_xTop + (5);
			bar_y = width;
		}
			
		if (bird_y == bar_y){
			if (bar_xTop <= bird_x && bird_x <= bar_xDown) {
				score++;
			}
			else {
				printf("Game Over!");
				system("pause");
				exit(0);
			}
		}
		

		speed = 0;
	}


}
void updateWithInput() {
	if (_kbhit() != 0) {
		switch (_getch())
		{
		case ' ':
			bird_x -= 2;
			break;
		case 'd':
			break;
		default:
			break;
		}
	}
}

int main()
{
	startup();
	while (1) {
		show();
		updateWithoutInput();
		updateWithInput();
	}
	return 0;
}