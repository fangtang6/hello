// sinple_air.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include <random>
using namespace std;
int main()
{
	int x = 5, y = 10;
	int ny;
	default_random_engine e;
	uniform_int_distribution<unsigned> u(2, 8);
	int isFired = 0;
	int isShoted = 0;
	ny = u(e);
	while (1) {
		system("cls");
		if (!isShoted) {
			for (int i = 0; i < ny; i++)
				cout << " ";
			cout << '-' << endl;
		} else {
			isShoted = 0;
			ny = u(e);
			for (int i = 0; i < ny; i++)
				cout << " ";
			cout << '-' << endl;
			
		}

		if (isFired) {
			for (int i = 0; i < x; i++) {
				for (int i = 0; i < y; i++)
					cout << " ";
				cout << "  |\n";
				if (y + 2 == ny)
					isShoted = 1;
			}
			isFired = 0;
		}
		else {
			for (int i = 0; i < x; i++)
				cout << endl;
		}
		for (int i = 0; i < y; i++)
			cout << " ";
		cout << "  *" << endl;	

		for (int i = 0; i < y; i++)
			cout << " ";
		cout << "*****" << endl;

		for (int i = 0; i < y; i++)
			cout << " ";
		cout << " * * " << endl;
		switch (_getch())
		{
		case 'w': x--; break;
		case 's': x++; break;
		case 'd': y++; break;
		case 'a': y--; break;
		default:
			break;
		}
		if (_getch() == ' ')
			isFired = 1;
	}
    return 0;
}

