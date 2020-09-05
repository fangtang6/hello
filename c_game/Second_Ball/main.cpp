#include<cstdio>
#include<Windows.h>
#include<conio.h>

//ȫ�ֱ���
int high, width;			//	��Ϸ����ߴ�
int ball_x, ball_y;			//	С��λ��
int ball_vx, ball_vy;		//	С���ٶ�
int position_x, position_y; //  ���������λ��
int radius;					//  ����İ뾶
int left, right;			//  ��������Ұ뾶
int ball_number;			//  С�򷴵���
int brick_x, brick_y;		//  ש��λ��
int score;					//	�÷�
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
				printf("O");				//�����
			else if (j == width + 1)
				printf("|");				//����ұ߽�
			else if (i == high + 1)
				printf("-");				//����±߽�
			else if ((i == high) && (left <= j) && (j <= right))
				printf("*");				//�������
			else if ((i == brick_x) && (j == brick_y))
				printf("B");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("����С����:%d \n", ball_number);
	printf("�÷�:%d \n", score);
}
void updateWithoutInput() {		//���û������޹صĸ��� 
	
	static int speed = 0;
	if (speed < 5)
		++speed;
	else {
		//�����ٶȸ���С��λ��
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

		//�߽���ײ�жϣ����ķ���
		if ((ball_x == 0) || (ball_x == high - 1))
			ball_vx *= -1;
		if ((ball_y == 0) || (ball_y == width - 1))
			ball_vy *= -1;

		//�����ж�
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