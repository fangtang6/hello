#include<cstdio>
#include<Windows.h>
#include<conio.h>

//ȫ�ֱ���	
#define HIGH 25				
#define WIDTH 50					//	��Ϸ����ߴ�
#define ENUM 10					//  �л�����
int canvas[HIGH][WIDTH] = { 0 };    //  ��Ļ����  
int position_x, position_y;			//	�ɻ�λ��
int enemy_x[ENUM], enemy_y[ENUM];	//  �л�λ��
int bullet_width;					//	�ӵ����
int score;							//	�÷�
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
void show() {				//��ʾ����
	gotoxy(0, 0);			//
	for (int i = 0; i < HIGH; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (canvas[i][j] == 0)			//ֵΪ0,����ո�
				printf(" ");
			else if (canvas[i][j] == 1)		//ֵΪ1������ɻ�*
				printf("*");
			else if (canvas[i][j] == 2)		//ֵΪ2,����ӵ�|
				printf("|");
			else if (canvas[i][j] == 3)		//ֵΪ2,����л�@
				printf("@");
		}
		printf("\n");
	}
	printf("�÷֣�%d\n", score);
}
void updateWithoutInput() {		//���û������޹صĸ��� 
	for (int i = 0; i < HIGH; ++i) 
	{
		for (int j = 0; j < WIDTH; ++j) 
		{	
			
			if (canvas[i][j] == 2)								//�����ӵ�
			{
				canvas[i][j] = 0;
				if (i > 0)
					canvas[i - 1][j] = 2;
				for (int k = 0; k < ENUM; k++)
				{
					if (i == enemy_x[k] && j == enemy_y[k]) {  //�ӵ����ел�  
						score++;
						canvas[enemy_x[k]][enemy_y[k]] = 0;	   //�л���ʧ
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
			if (enemy_x[i] == position_x && enemy_y[i] == position_y)	//�л������ҷ��ɻ�,��Ϸ����
			{
				printf("Game Over!!\n");
				system("pause");
				exit(0);
			}
			else if (enemy_x[i] >= HIGH - 1) {				//�л��䵽�ײ�
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