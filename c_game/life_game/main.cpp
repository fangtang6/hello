#include<cstdio>
#include<Windows.h>
#include<conio.h>

//ȫ�ֱ���	
#define HIGH 30				
#define WIDTH 100		//	��Ϸ����ߴ�
int cell[HIGH][WIDTH];  //  ϸ������
void gotoxy(int x, int y)  //����ƶ���(x,y)λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor() // �������ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup() {	//���ݳ�ʼ��
	for (int i = 0; i < HIGH; ++i)
		for (int j = 0; j < WIDTH; ++j)
			cell[i][j] = rand() % 2;

	HideCursor();
}
void show() {				//��ʾ����
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
void updateWithoutInput() {		//���û������޹صĸ��� 
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