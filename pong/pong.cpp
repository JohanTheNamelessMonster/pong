#include <iostream>
#include <vector>
#include <Windows.h>

const int height = 25;
const int width = 100;
int vertical_Length = 5;
int game = true;
char ball = 'O';
std::string hbound = "";
int directionalVector[2] = { 0,0 };
int ball_Position[2];
char map[height][width];
int line_Ends[2][2] = 
{	{(height - vertical_Length) / 2,(height + vertical_Length) / 2 },
	{(height - vertical_Length) / 2,(height + vertical_Length) / 2 } 
};
bool killGame = false;
int players[2] = {0,0};
enum keyAction {pressed,released};
std::string space;

void initialiseGame()
{

	hbound = "";

	for (int i = 0; i < width; i++)
	{
		hbound += '+';
	}

	srand(time(0));
	ball_Position[0] = rand() % width;
	ball_Position[1] = rand() % height;

	while ((ball_Position[0] == 0 || ball_Position[1] == width-1) || (ball_Position[0] == 1 || ball_Position[1] == width -2) || ball_Position[0] == width / 2)
	{
		ball_Position[0] = rand() % width;
		ball_Position[1] = rand() % height;
	}


	if (ball_Position[0] < round(width / 2))
	{
		directionalVector[0] = -1;
	}
	else
	{
		directionalVector[0] = 1;
	}

	if (ball_Position[1] < round(height/2))
	{
		directionalVector[1] = 1;
	}
	else
	{
		directionalVector[1] = -1;
	}

	space = "";
	for (int i = 0; i < (width - 50); i++)
	{
		space += " ";
	}

	Sleep(1000);

	return;

}

void draw()
{

	system("cls");

	std::cout << hbound << std::endl;

	for (int i = 0; i < height; i++)
	{
		std::string line = "";
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				map[i][j] = '+';
			}
			else if (((j + 1) == width / 2) && (ball_Position[0] != j || ball_Position[1] != i))
			{
				map[i][j] = '|';
			}
			else if (((i > line_Ends[0][0] && i <= line_Ends[0][1]) && j == 1) || ((i > line_Ends[1][0] && i <= line_Ends[1][1]) && j == width - 2))
			{
				map[i][j] = '|';
			}
			else if (j == ball_Position[0] && i == ball_Position[1])
			{
				map[i][j] = ball;
			}
			else
			{
				map[i][j] = ' ';
			}

			line += map[i][j];

		}

		std::cout << line << std::endl;

	}

	std::cout << hbound << std::endl;

	std::cout << "Player 1: " << players[0] << space << "Player 2: " << players[1] << std::endl;
}

void logic()
{

	for (int i = 0; i < (vertical_Length); i++)
	{
		map[line_Ends[0][0] + i + 1][1] = ' ';
		map[line_Ends[1][0] + i + 1][width - 2] = ' ';
	}


	if (GetAsyncKeyState('W'))
	{
		if (!(line_Ends[0][0] == -1))
		{
			line_Ends[0][0] -= 1;
			line_Ends[0][1] -= 1;
		}
	}
	else if(GetAsyncKeyState('S'))
	{
		if (!(line_Ends[0][1] == height - 1))
		{
			line_Ends[0][0] += 1;
			line_Ends[0][1] += 1;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (!(line_Ends[1][0] == -1))
		{
			line_Ends[1][0] -= 1;
			line_Ends[1][1] -= 1;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (!(line_Ends[1][1] == height - 1))
		{
			line_Ends[1][0] += 1;
			line_Ends[1][1] += 1;
		}
	}

	map[ball_Position[1]][ball_Position[0]] = ' ';

	for (int i = 0; i < (vertical_Length); i++)
	{
		map[line_Ends[0][0] + i + 1][1] = '|';
		map[line_Ends[1][0] + i + 1][width - 2] = '|';
	}

	ball_Position[0] += directionalVector[0];
	ball_Position[1] += directionalVector[1];

	if (((ball_Position[0] == 1) || ball_Position[0] == width - 2) && map[ball_Position[1]][ball_Position[0]] == '|')
	{
		directionalVector[0] *= -1;
	}

	if ((ball_Position[0] == 0) || (ball_Position[0]  == width - 1))
	{

		if (ball_Position[0] == 0)
		{
			players[1] += 1;
		}
		else {
			players[0] += 1;
		}

		initialiseGame();

		return;
	}
	
	if (((ball_Position[1] == 0) || ((ball_Position[1] ) == height - 1)))
	{
		directionalVector[1] *= -1;
	}

	map[ball_Position[1]][ball_Position[0]] = ball;

	return;
}

int main() 
{
	initialiseGame();

	while (!GetAsyncKeyState('S') && !GetAsyncKeyState('T'))
	{
		std::cout << "Hit S to start or T to terminate" << std::endl;

		Sleep(1000);
		system("cls");
	}

	if (GetKeyState('T') & 0x001)
	{
		killGame = true;
	}

	if (!killGame)
	{
		while (!GetAsyncKeyState('T'))
		{
			draw();
			logic();
			if (players[0] == 10 || players[1] == 10)
			{
				break;
			};
			Sleep(10);
		}

		system("cls");
		std::cout << "Game Over!!" << std::endl;
		if (players[0] > players[1])
		{
			std::cout << "Player 1 beat Player 2" << std::endl;
		}
		else if (players[0] == players[1])
		{
			std::cout << "Stand proud warriors. For both of y'all are champions" << std::endl;
		}
		else
		{
			std::cout << "Player 2 beat Player 1" << std::endl;
		}

	}
	else {
		system("cls");
		std::cout << "Game Terminated!" << std::endl;
	}

	return 0;
}
