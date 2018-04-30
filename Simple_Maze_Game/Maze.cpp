#include <iostream>
#include <conio.h>

using namespace std;

/*
	0 : 벽
	1 : 길
	2 : 시작점
	3 : 도착점
*/

typedef struct _tagPoint
{
	int x;
	int y;
}POINT;

typedef POINT * PPOINT;

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*pPlayerPos = *pStartPos;

	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111110000000000");
	strcpy_s(Maze[2],  "00100100011111111100");
	strcpy_s(Maze[3],  "01100100000000000100");
	strcpy_s(Maze[4],  "01000100000000000100");
	strcpy_s(Maze[5],  "01000111100001111100");
	strcpy_s(Maze[6],  "01110000001111000000");
	strcpy_s(Maze[7],  "00011000001000000000");
	strcpy_s(Maze[8],  "00010000001000000000");
	strcpy_s(Maze[9],  "00010000001111110000");
	strcpy_s(Maze[10], "00011100000000010000");
	strcpy_s(Maze[11], "00010000000000010000");
	strcpy_s(Maze[12], "00011100000000011110");
	strcpy_s(Maze[13], "00000000000000010000");
	strcpy_s(Maze[14], "00001111111000010000");
	strcpy_s(Maze[15], "00000000001111110000");
	strcpy_s(Maze[16], "00011100001000010000");
	strcpy_s(Maze[17], "00110111111000011100");
	strcpy_s(Maze[18], "01110001000000000100");
	strcpy_s(Maze[19], "01011001000000000113");
}

void Output(char Maze[21][21], PPOINT pPlayerPos)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (pPlayerPos->x == j && pPlayerPos->y == i)
				cout << "☆";
			else if (Maze[i][j] == '0')
				cout << "■";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "★";
			else if (Maze[i][j] == '3')
				cout << "◎";
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerpos)
{
	if (pPlayerpos->y - 1 >= 0)
	{
		// 벽인지 체크
		if (Maze[pPlayerpos->y - 1][pPlayerpos->x] != '0')
		{
			--pPlayerpos->y;
		}
	}
}

void MoveDown(char Maze[21][21], PPOINT pPlayerpos)
{
	if (pPlayerpos->y + 1 < 20)
	{
		// 벽인지 체크
		if (Maze[pPlayerpos->y + 1][pPlayerpos->x] != '0')
		{
			++pPlayerpos->y;
		}
	}
}

void MoveRight(char Maze[21][21], PPOINT pPlayerpos)
{
	if (pPlayerpos->x + 1 < 20)
	{
		// 벽인지 체크
		if (Maze[pPlayerpos->y][pPlayerpos->x + 1] != '0')
		{
			++pPlayerpos->x;
		}
	}
}

void MoveLeft(char Maze[21][21], PPOINT pPlayerpos)
{
	if (pPlayerpos->x - 1 < 20)
	{
		// 벽인지 체크
		if (Maze[pPlayerpos->y][pPlayerpos->x - 1] != '0')
		{
			--pPlayerpos->x;
		}
	}
}

void MovePlayer(char Maze[21][21], PPOINT pPlayerPos, char cinput)
{
	switch (cinput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayerPos);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayerPos);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayerPos);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayerPos);
		break;
	}
}

int main()
{
	// 20 X 20 미로를 만들어준다.
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	// 미로를 설정한다.
	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");

		// 미로를 출력한다.
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "w : 위 | s : 아래 | a : 왼쪽 | d : 오른쪽 | q : 종료";

		char cinput = _getch();

		if (cinput == 'q' || cinput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cinput);
	}

	return 0;
}
