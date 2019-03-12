#include <iostream>
#include <fstream>
#include "path.h"
#include <Windows.h>

using namespace std;

int main()
{
	
	fstream file;
	file.open("map.txt", ios::in);

	char temp;

	int **wsk = new int *[64];

	for (int i = 0; i < 64; i++)
		wsk[i] = new int[32];

	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 64; j++)
		{
			file >> temp;
			wsk[j][i] = (int)temp-48;
		}

	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 64; j++)
			cout << wsk[j][i];

		cout << endl;
	}

	path sciezka(64, 32, wsk, 9);

	//sciezka.find_path();

	for (int i = 0; i < 64; i++)
		delete wsk[i];

	delete[] wsk;

	system("pause");

	return 0;
}