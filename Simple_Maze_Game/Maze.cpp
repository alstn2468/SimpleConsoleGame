#include <iostream>
#include <conio.h>

using namespace std;

/*
	0 : 벽
	1 : 길
	2 : 시작점
	3 : 도착점
	4 : 폭탄
	5 : 파워 아이템
	6 : 벽 밀기 아이템
	7 : 투명 아이템
	8 : 웜홀
*/

typedef struct _tagPoint
{
	int x;
	int y;
}POINT;

typedef POINT * PPOINT;

typedef struct _tagPlayer
{
	_tagPoint tPos;
	bool bWallPush;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;

/* 미로를 설정해주는 함수 */
void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy(Maze[0],  "21100000000000000000");
	strcpy(Maze[1],  "00111111110000000000");
	strcpy(Maze[2],  "00100100011111111100");
	strcpy(Maze[3],  "01100100000000000100");
	strcpy(Maze[4],  "01000100000000000100");
	strcpy(Maze[5],  "01000111100001111100");
	strcpy(Maze[6],  "01110000001111000000");
	strcpy(Maze[7],  "00011000001000000000");
	strcpy(Maze[8],  "00010000001000000000");
	strcpy(Maze[9],  "00010000001111110000");
	strcpy(Maze[10], "00011100000000010000");
	strcpy(Maze[11], "00010000000000010000");
	strcpy(Maze[12], "00011100000000011110");
	strcpy(Maze[13], "00000000000000010000");
	strcpy(Maze[14], "00001111111000010000");
	strcpy(Maze[15], "00000000001111110000");
	strcpy(Maze[16], "00011100001000010000");
	strcpy(Maze[17], "00110111111000011100");
	strcpy(Maze[18], "01110001000000000100");
	strcpy(Maze[19], "01011001000000000113");
}

/* 미로를 출력해주는 함수 */
void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '4')
				cout << "♨";

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
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

	cout << "폭탄 파워 : " << pPlayer->iBombPower << endl;
	cout << "벽 통과 : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "벽 밀기 : ";
	if (pPlayer->bWallPush)
		cout << "ON\t" << endl;
	else
		cout << "OFF\t" << endl;
}

/* 아이템 획득 함수 */
bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		++pPlayer->iBombPower;
		return true;
	}

	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		return true;
	}

	else if (cItemType == '7')
	{
		pPlayer->bTransparency = true;
		return true;
	}

	return false;
}

/* 위로 움직이는 함수 */
void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{

		/* 벽인지 체크 */
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}
		/* 유령화 일 경우 */
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

/* 아래로 움직이는 함수 */
void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		/* 벽인지 체크 */
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}
	}
}

/* 오른쪽으로 움직이는 함수 */
void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		/* 벽인지 체크 */
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}
	}
}

/* 왼쪽으로 움직이는 함수 */
void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 < 20)
	{
		/* 벽인지 체크 */
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}
	}
}

/* 입력값에 따라 사용자를 움직이는 함수 */
void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cinput)
{
	switch (cinput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

/* 폭탄을 만드는 함수 */
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int *pBombCount)
{
	if (*pBombCount == 5)
		return;

	for (int i = 0; i < *pBombCount; i++)
	{
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

/* 폭탄을 터뜨리는 함수 */
void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int *pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		if (pBombArr[i].y - 1 >= 0) // 위
		{
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';

			/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
			if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - 1)
			{
				pPlayer->tPos.x = 0;
				pPlayer->tPos.y = 0;
			}
		}

		if (pBombArr[i].y + 1 < 20) // 아래
		{
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';

			/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
			if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + 1)
			{
				pPlayer->tPos.x = 0;
				pPlayer->tPos.y = 0;
			}
		}

		if (pBombArr[i].x- 1 >= 0) // 왼쪽
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';

			/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
			if (pPlayer->tPos.x == pBombArr[i].x - 1 && pPlayer->tPos.y == pBombArr[i].y)
			{
				pPlayer->tPos.x = 0;
				pPlayer->tPos.y = 0;
			}
		}

		if (pBombArr[i].x + 1 < 20) // 오른쪽
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';

			/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
			if (pPlayer->tPos.x == pBombArr[i].x + 1 && pPlayer->tPos.y == pBombArr[i].y)
			{
				pPlayer->tPos.x = 0;
				pPlayer->tPos.y = 0;
			}
		}
	}

	*pBombCount = 0;
}

int main()
{
	/* 20 X 20 미로 생성 */
	char strMaze[21][21] = { 0 };

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];

	/* 미로를 설정 */
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");

		/* 미로를 출력 */
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "t : 폭탄설치 | u : 폭탄 터뜨리기 | i : 벽 밀기" << endl;
		cout << "w : 위 | s : 아래 | a : 왼쪽 | d : 오른쪽 | q : 종료";

		char cinput = _getch();

		if (cinput == 'q' || cinput == 'Q')
			break;

		else if (cinput == 't' || cinput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cinput == 'u' || cinput == 'U')
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);

		else
			MovePlayer(strMaze, &tPlayer, cinput);
	}

	return 0;
}
