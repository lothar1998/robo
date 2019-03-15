#include <iostream>
#include <fstream>
#include "path.h"


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

    cout<<endl;
    cout<<endl;


    path sciezka(64, 32, wsk, 9);

    coordinates start(14, 1);
    coordinates stop(20, 31);

    vector<coordinates> optimum = sciezka.find_optimal_path(start, stop);




    for (unsigned int i = 0; i < optimum.size(); i++)
        wsk[optimum.at(i).get_x()][optimum.at(i).get_y()] = 0;

    wsk[14][1] = 5;
    wsk[20][31] = 3;

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 64; j++)
            cout << wsk[j][i];

        cout << endl;
    }

    for (int i = 0; i < 64; i++)
        delete wsk[i];

    delete[] wsk;


    return 0;
}