#include<cstdio>
#include<Windows.h>
#include<conio.h>

//全局变量	
#define HIGH 30				
#define WIDTH 100		//	游戏界面尺寸
int cell[HIGH][WIDTH];  //  细胞数组
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
	for (int i = 0; i < HIGH; ++i)
		for (int j = 0; j < WIDTH; ++j)
			cell[i][j] = rand() % 2;

	HideCursor();
}
void show() {				//显示界面
	gotoxy(0, 0);			//
	for (int i = 0; i < HIGH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (cell[i][j] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}
void updateWithoutInput() {		//与用户输入无关的更新 
	int cell_copy[HIGH][WIDTH];
	for (int i = 0; i < HIGH; ++i)
		for (int j = 0; j < WIDTH; ++j)
			cell_copy[i][j] = cell[i][j];
	for(int i = 1; i < HIGH - 1; ++i)
		for (int j = 1; j < WIDTH - 1; ++j) {
			int sum = 0;
			sum += cell[i - 1][j - 1] + cell[i - 1][j] + cell[i - 1][j + 1] +
				cell[i][j - 1] + cell[i][j] + cell[i][j + 1] +
				cell[i + 1][j - 1] + cell[i + 1][j] + cell[i + 1][j + 1];
			if (sum < 2 || sum > 3)
				cell_copy[i][j] = 0;
			else if (sum == 3)
				cell_copy[i][j] = 1;

		}
	for (int i = 0; i < HIGH; ++i)
		for (int j = 0; j < WIDTH; ++j)
			cell[i][j] = cell_copy[i][j];
}
void updateWithInput() {

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