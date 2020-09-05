#include<cstdio>
#include<Windows.h>
#include<conio.h>

//全局变量
int high, width;			//	游戏界面尺寸
int ball_x, ball_y;			//	小球位置
int ball_vx, ball_vy;		//	小球速度
int position_x, position_y; //  挡板的中心位置
int radius;					//  挡板的半径
int left, right;			//  挡板的左右半径
int ball_number;			//  小球反弹数
int brick_x, brick_y;		//  砖块位置
int score;					//	得分
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
	width = 25;

	ball_number = 0;
	score = 0;

	ball_x = 1;
	ball_y = width / 2;

	ball_vx = 1;
	ball_vy = 1;

	position_x = high;
	position_y = width / 2;
	radius = 5;
	left = position_y - radius;
	right = position_y + radius;

	brick_x = 0;
	brick_y = rand() % width;

	HideCursor();
}
void show() {
	gotoxy(0, 0);
	for (int i = 0; i <= high + 1; ++i) {
		for (int j = 0; j <= width + 1; ++j) {
			if ((i == ball_x) && (j == ball_y))
				printf("O");				//输出球
			else if (j == width + 1)
				printf("|");				//输出右边界
			else if (i == high + 1)
				printf("-");				//输出下边界
			else if ((i == high) && (left <= j) && (j <= right))
				printf("*");				//输出挡板
			else if ((i == brick_x) && (j == brick_y))
				printf("B");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("反弹小球数:%d \n", ball_number);
	printf("得分:%d \n", score);
}
void updateWithoutInput() {		//与用户输入无关的更新 
	
	static int speed = 0;
	if (speed < 5)
		++speed;
	else {
		//根据速度更新小球位置
		ball_x += ball_vx;
		ball_y += ball_vy;

		if (ball_x == high - 1) {
			if ((left <= ball_y) && (ball_y <= right)) {
				ball_number++;
				//ball_y = ball_y + rand() % 4 - 2;
			}
			else {
				printf("Game Over!\n");
				system("pause");
				exit(0);
			}
		}

		//边界碰撞判断，更改方向
		if ((ball_x == 0) || (ball_x == high - 1))
			ball_vx *= -1;
		if ((ball_y == 0) || (ball_y == width - 1))
			ball_vy *= -1;

		//击中判断
		if ((ball_x == brick_x) && (ball_y == brick_y)) {
			score++;
			brick_y = rand() % width;
		}
			
		speed = 0;
	}
	
	
}
void updateWithInput() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			position_y--;
			left = position_y - radius;
			right = position_y + radius;
			break;
		case 'd':
			position_y++;
			left = position_y - radius;
			right = position_y + radius;
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