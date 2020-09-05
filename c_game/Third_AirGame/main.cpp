#include<cstdio>
#include<Windows.h>
#include<conio.h>

//全局变量	
#define HIGH 25				
#define WIDTH 50					//	游戏界面尺寸
#define ENUM 10					//  敌机数量
int canvas[HIGH][WIDTH] = { 0 };    //  屏幕数组  
int position_x, position_y;			//	飞机位置
int enemy_x[ENUM], enemy_y[ENUM];	//  敌机位置
int bullet_width;					//	子弹宽度
int score;							//	得分
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
	position_x = HIGH - 1;
	position_y = WIDTH / 2;
	canvas[position_x][position_y] = 1;

	for (int i = 0; i < ENUM; ++i) {
		enemy_x[i] = rand() % 3;
		enemy_y[i] = rand() % WIDTH;
		canvas[enemy_x[i]][enemy_y[i]] = 3;
	}
	bullet_width = 5;
	score = 0;
	HideCursor();
}
void show() {				//显示界面
	gotoxy(0, 0);			//
	for (int i = 0; i < HIGH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (canvas[i][j] == 0)			//值为0,输出空格
				printf(" ");
			else if (canvas[i][j] == 1)		//值为1，输出飞机*
				printf("*");
			else if (canvas[i][j] == 2)		//值为2,输出子弹|
				printf("|");
			else if (canvas[i][j] == 3)		//值为2,输出敌机@
				printf("@");
		}
		printf("\n");
	}
	printf("得分：%d\n", score);
}
void updateWithoutInput() {		//与用户输入无关的更新 
	for (int i = 0; i < HIGH; ++i) 
	{
		for (int j = 0; j < WIDTH; ++j) 
		{	
			
			if (canvas[i][j] == 2)								//处理子弹
			{
				canvas[i][j] = 0;
				if (i > 0)
					canvas[i - 1][j] = 2;
				for (int k = 0; k < ENUM; k++)
				{
					if (i == enemy_x[k] && j == enemy_y[k]) {  //子弹击中敌机  
						score++;
						canvas[enemy_x[k]][enemy_y[k]] = 0;	   //敌机消失
						enemy_x[k] = rand() % 3;
						enemy_y[k] = rand() % WIDTH;
						canvas[enemy_x[k]][enemy_y[k]] = 3;
					}
				}
				
			}
		}
	}
	static int speed = 0;
	if (speed < 5)
		speed++;
	else {
		for (int i = 0; i < ENUM; ++i) {
			if (enemy_x[i] == position_x && enemy_y[i] == position_y)	//敌机碰到我方飞机,游戏结束
			{
				printf("Game Over!!\n");
				system("pause");
				exit(0);
			}
			else if (enemy_x[i] >= HIGH - 1) {				//敌机落到底部
				canvas[enemy_x[i]][enemy_y[i]] = 0;		
				enemy_x[i] = rand() % 3;
				enemy_y[i] = rand() % WIDTH;
				canvas[enemy_x[i]][enemy_y[i]] = 3;
				score--;	
			}
			else {
				canvas[enemy_x[i]][enemy_y[i]] = 0;
				enemy_x[i]++;
				canvas[enemy_x[i]][enemy_y[i]] = 3;
			}
		}
		speed = 0;
	}
}
void updateWithInput() {
	char Input;
	if (_kbhit()) {
		Input = _getch();
		if (Input == 'a' && 0 < position_y ) {
			canvas[position_x][position_y] = 0;
			position_y--;
			canvas[position_x][position_y] = 1;
		} else if (Input == 'd' && position_y < WIDTH - 1) {
			canvas[position_x][position_y] = 0;
			position_y++;
			canvas[position_x][position_y] = 1;
		} else if (Input == 'w' && 0 < position_x  ) {
			canvas[position_x][position_y] = 0;
			position_x--;
			canvas[position_x][position_y] = 1;
		}
		else if (Input == 's' && position_x  < HIGH - 1) {
			canvas[position_x][position_y] = 0;
			position_x++;
			canvas[position_x][position_y] = 1;
		}
		else if (Input == ' ') {
			int left = position_y - bullet_width;
			int right = position_y + bullet_width;
			if (left < 0)
				left = 0;
			if (right > WIDTH - 1)
				right = WIDTH - 1;
			for(int i = left; i <= right; ++i)
				canvas[position_x - 1][i] = 2;
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