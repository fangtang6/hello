#include<cstdio>
#include<Windows.h>
#include<conio.h>

//ȫ�ֱ���	
int high, width;				//	��Ϸ����ߴ�
int bird_x, bird_y;				//	С��λ��
int bird_vx, bird_vy;			//	С���ٶ�
int bar_y, bar_xTop, bar_xDown; //  �ϰ���
int score;

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
void show() {				//��ʾ����
	gotoxy(0, 0);			//
	for (int i = 0; i <= high + 1; ++i) {
		for (int j = 0; j <= width + 1; ++j) {
			if ((i == bird_x) && (j == bird_y))
				printf("@");				//���С��
			else if ((j == bar_y) && ((i <= bar_xTop) | (bar_xDown <= i )))
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("�÷�: %d\n", score);
}
void updateWithoutInput() {		//���û������޹صĸ��� 

	static int speed = 0;
	if (speed < 2)
		++speed;
	else {
		//�����ٶȸ���С��λ��
		bird_x += bird_vx;
		bird_y += bird_vy;

		//�ϰ��������ƶ�
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