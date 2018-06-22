#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

char web[28][50];
bool web_nwse[4][28][50];
int web_way[28][50];
vector <int> x;
vector <int> y;

void out_web()
{
	system("cls");
	
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			cout << web[i][j];
		}
		cout << "" << endl;
	}
}

void erase_way(int x,int y)
{
	if (x != 27)
	{
		web_nwse[2][x + 1][y] = 0;
	}
	if (x != 0)
	{
		web_nwse[0][x - 1][y] = 0;
	}
	if (y != 49)
	{
		web_nwse[1][x][y+1] = 0;
	}
	if (y != 0)
	{
		web_nwse[3][x][y-1] = 0;
	}
}

void make_barier(int x_barier, int y_barier)
{
	web[x_barier][y_barier]='b';
	erase_way(x_barier,y_barier);
	out_web();
}

void make_start(int x_start, int y_start)
{
	web[x_start][y_start] = 's';

	out_web();
	
}

void make_end(int x_end, int y_end)
{
	web[x_end][y_end] = 'e';
	out_web();
}

void way()
{
	while (web_way[x[0]][y[0]] != -1)
	{
		if (web_way[x[0]][y[0]] == 0)
		{
			x[0] += 1;
		}
		else if (web_way[x[0]][y[0]] == 1)
		{
			y[0] -= 1;
		}
		else if (web_way[x[0]][y[0]] == 2)
		{
			x[0] -= 1;
		}
		else if (web_way[x[0]][y[0]] == 3)
		{
			y[0] += 1;
		}
		web[x[0]][y[0]] = '@';
		out_web();
	}
	web[x[0]][y[0]] = 's';
	out_web();
	cout << "WAY FOUND" << endl;
}

void find_way(int x_e, int y_e)
{
	while (x.size() != 0)
	{
		if (web_nwse[0][x[0]][y[0]] == 1)
		{
			web_way[x[0] + 1][y[0]]=2;
			if ((x[0] + 1 == x_e) && (y[0] == y_e))
			{
				x[0] = x_e;
				break;
			}
			x.push_back(x[0] + 1);
			y.push_back(y[0]);
			erase_way(x[0] + 1, y[0]);
			web[x[0] + 1][y[0]] = '*';
			out_web();
		}
		if (web_nwse[1][x[0]][y[0]] == 1)
		{
			web_way[x[0] ][y[0]-1] = 3;
			if ((x[0] == x_e) && (y[0]-1 == y_e))
			{
				y[0] = y_e;
				break;
			}
			x.push_back(x[0]);
			y.push_back(y[0]-1);
			erase_way(x[0], y[0]-1);
			web[x[0] ][y[0]-1] = '*';
			out_web();
		}
		if (web_nwse[2][x[0]][y[0]] == 1)
		{
			web_way[x[0] - 1][y[0]] = 0;
			if ((x[0] - 1 == x_e) && (y[0] == y_e))
			{
				x[0] = x_e;
				break;
			}
			x.push_back(x[0] - 1);
			y.push_back(y[0]);
			erase_way(x[0] - 1, y[0]);
			web[x[0] - 1][y[0]] = '*';
			out_web();
		}
		if (web_nwse[3][x[0]][y[0]] == 1)
		{
			web_way[x[0]][y[0]+1] = 1;
			if ((x[0]  == x_e) && (y[0]+1 == y_e))
			{
				y[0] = y_e;
				break;
			}
			x.push_back(x[0]);
			y.push_back(y[0]+1);
			erase_way(x[0], y[0]+1);
			web[x[0]][y[0]+1] = '*';
			out_web();
		}
		x.erase(x.begin());
		y.erase(y.begin());
	}
	if (x.size() == 0)
	{
		cout << "NO WAYS" << endl;
	}
	else
	{
		way();
	}
}

int main()
{
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			web_way[i][j] = -1;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			for (int k = 0; k < 50; k++)
			{
				web_nwse[i][j][k] = 1;
			}
		}
	}
	for (int i = 0; i < 28;i++)
	{
		web_nwse[1][i][0] = 0;
		web_nwse[3][i][49] = 0;
	}
	for (int i = 0; i < 50; i++)
	{
		web_nwse[2][0][i] = 0;
		web_nwse[0][27][i] = 0;
	}
	int x_start = 0, y_start = 0, x_end = 27, y_end = 49;
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			web[i][j] = '.';
		}
	}
	out_web();
	
	string a;
	while (cin >> a)
	{
		if (a=="barier")
		{
			int x, y;
				cin >> x >> y;
				make_barier(x, y);
		}
		else if (a == "make_start")
		{
			cin >> x_start >> y_start;
			make_start(x_start, y_start);

		}
		else if (a == "make_end")
		{
			cin >> x_end >> y_end;
			make_end(x_end, y_end);
		}
		else if (a == "start")
		{
			x.push_back(x_start);
			y.push_back(y_start);
			erase_way(x_start, y_start);
			find_way(x_end,y_end);
		}
		else if (a == "exit")
		{
			break;
		}
		else
		{
			out_web();
			cout << "error" << endl;
		}
	} //
    return 0;
}

