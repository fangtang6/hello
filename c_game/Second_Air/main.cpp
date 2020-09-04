#include<cstdio>
#include<Windows.h>
#include<conio.h>

//������ȫ�ֱ�������
int position_x, position_y;	// �ɻ�λ��
int high, width;			// ���淶Χ
int bullet_x, bullet_y;		// �ӵ�λ��
int enemy_x, enemy_y;		// �л�λ��
int score;					// ��Ϸ�÷�

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

void startup() {  //���ݳ�ʼ��
	high = 18;
	width = 30;
	position_x = high / 2;
	position_y = width / 2;
	
	bullet_x = -1;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = width / 2;

	score = 0;

	HideCursor();  //���ع��
}

void show() { //��ʾ����
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
	printf("�÷֣�%d\n", score);
}
void updateWithoutInput() {  //���û������޹ص�����

	if (bullet_x == enemy_x && bullet_y == enemy_y) {   //�ж��ӵ��Ƿ����
		score++;
		enemy_x = 0;
		enemy_y = rand() % width;
		bullet_x = -1;
	}

	if (bullet_x >= 0) bullet_x--;	//�ӵ����Ϸ���
	static int speed = 0;
	if (speed < 10) {		
		speed++;
	} else {
		if (enemy_x > high) {
			enemy_x = 0;
			enemy_y = rand() % width;
		} else {
			enemy_x++;					//�л������˶�
		}
		speed = 0;
	}
	
						

}
void updateWithInput() {  //���û������йص�����
	if (_kbhit() != 0) {
		switch (_getch()) {
		case 'w': position_x--; break;       //�����ƶ�
		case 's': position_x++; break;		 //�����ƶ�
		case 'd': position_y++; break;		//�����ƶ�
		case 'a': position_y--; break;		//�����ƶ�
		case ' ': bullet_x = position_x - 1; //����
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