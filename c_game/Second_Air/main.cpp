#include<cstdio>
#include<Windows.h>
#include<conio.h>

//函数外全局变量定义
int position_x, position_y;	// 飞机位置
int high, width;			// 界面范围
int bullet_x, bullet_y;		// 子弹位置
int enemy_x, enemy_y;		// 敌机位置
int score;					// 游戏得分

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

void startup() {  //数据初始化
	high = 18;
	width = 30;
	position_x = high / 2;
	position_y = width / 2;
	
	bullet_x = -1;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = width / 2;

	score = 0;

	HideCursor();  //隐藏光标
}

void show() { //显示界面
	int i, j;
	//system("cls");
	gotoxy(0, 0);
	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++)
			if (i == position_x && j == position_y)
				printf("*");
			else if (i == bullet_x && j == bullet_y)
				printf("|");
			else if (i == enemy_x && j == enemy_y)
				printf("@");
			else
				printf(" ");
		printf("\n");
	}
	printf("得分：%d\n", score);
}
void updateWithoutInput() {  //与用户输入无关的输入

	if (bullet_x == enemy_x && bullet_y == enemy_y) {   //判断子弹是否击中
		score++;
		enemy_x = 0;
		enemy_y = rand() % width;
		bullet_x = -1;
	}

	if (bullet_x >= 0) bullet_x--;	//子弹向上发射
	static int speed = 0;
	if (speed < 10) {		
		speed++;
	} else {
		if (enemy_x > high) {
			enemy_x = 0;
			enemy_y = rand() % width;
		} else {
			enemy_x++;					//敌机向下运动
		}
		speed = 0;
	}
	
						

}
void updateWithInput() {  //与用户输入有关的输入
	if (_kbhit() != 0) {
		switch (_getch()) {
		case 'w': position_x--; break;       //向上移动
		case 's': position_x++; break;		 //向下移动
		case 'd': position_y++; break;		//向右移动
		case 'a': position_y--; break;		//向左移动
		case ' ': bullet_x = position_x - 1; //发射
			bullet_y = position_y;
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