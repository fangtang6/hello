#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;
int main()
{	
	int button = 0, top = 10;
	int left = 0, right = 15;
	int x = 0, y = 5;
	int volecity_x = 1, volecity_y = 1;
	while (1) {
		system("cls");
		x += volecity_x;
		y += volecity_y;
		for (int i = 0; i < x; ++i)
			cout << endl;
		for (int i = 0; i < y; ++i)
			cout << " ";
		cout << "O" << endl;
		if (x == button || x == top) {
			volecity_x *= -1;
			//cout << "\a";
		}
		if (y == left || y == right) {
			volecity_y *= -1;
			//cout << "\a";
		}
			
	}
	return 0;
}