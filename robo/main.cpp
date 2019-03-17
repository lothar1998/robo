#include <iostream>
#include <fstream>
#include "path.h"
#define _DIM_X 64
#define _DIM_Y 32

using namespace std;

int main()
{
    fstream file;
    file.open("map.txt", ios::in);

    char temp;

    auto **wsk = new int *[_DIM_X];

    for (int i = 0; i < _DIM_X; i++)
        wsk[i] = new int[_DIM_Y];

    for (int i = 0; i < _DIM_Y; i++)
        for (int j = 0; j < _DIM_X; j++)
        {
            file >> temp;
            if((int)temp-48==9)
                wsk[j][i]=_DIM_X*_DIM_Y;
            else
                wsk[j][i] =(int)temp-48;
        }

    for (int i = 0; i < _DIM_Y; i++)
    {
        for (int j = 0; j < _DIM_X; j++)
            if(wsk[j][i]==_DIM_X*_DIM_Y)
                cout << "*";
            else
                cout << wsk[j][i];

        cout << endl;
    }

    file.close();
    cout<<endl;
    cout<<endl;


    path sciezka(_DIM_X, _DIM_Y, wsk, _DIM_X*_DIM_Y);

    coordinates start(14, 0);//14 1
    coordinates stop(20, 31);//20 31

    vector<coordinates> optimum = sciezka.find_path(start, stop);

    cout<<"length of path"<<optimum.size()<<endl;
    cout<<endl;


    for (auto i:optimum)
        wsk[i.get_x()][i.get_y()] = 0;

    //wsk[14][1] = 5;
    //wsk[20][31] = 3;

    for (int i = 0; i < _DIM_Y; i++)
    {
        for (int j = 0; j < _DIM_X; j++)
            if(wsk[j][i]==_DIM_X*_DIM_Y)
                cout << "*";
            else
                cout << wsk[j][i];

        cout << endl;
    }

    for (int i = 0; i < _DIM_X; i++)
        delete wsk[i];

    delete[] wsk;


    return 0;
}