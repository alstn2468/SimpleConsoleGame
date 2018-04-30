#include <iostream>
#include <conio.h>
#include <time.h>

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
	bool bPushOnOff;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;

/* 미로를 설정해주는 함수 */
void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	// MazeList.txt 파일을 읽어와 미로 목록 생성
	FILE * pFile = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");

	char **pMazeList = NULL;

	if (pFile)
	{
		char cCount;

		fread(&cCount, 1, 1, pFile);

		int iMazeCount = atoi(&cCount);

		fread(&cCount, 1, 1, pFile);

		/* char  *배열을 미로 개수만큼 할당 */
		pMazeList = new char *[iMazeCount];

		for (int i = 0; i < iMazeCount; ++i)
		{
			int iNameCount = 0;

			/* 현재 미로의 파일 이름을 저장할 배열 할당 */
			pMazeList[i] = new char[256];

			while (true)
			{
				fread(&cCount, 1, 1, pFile);

				if (cCount != '\n')
				{
					pMazeList[i][iNameCount] = cCount;
					++iNameCount;
				}
				else
					break;
			}

			/* 파일 이름을 모두 읽었다면 문자열의 끝을 설정 */
			pMazeList[i][iNameCount] = 0;
		}

		fclose(pFile);

		/* 읽을 파일 목록 생성 완료 파일 중 하나 선택 */
		for (int i = 0; i < iMazeCount; ++i)
			cout << i + 1 << ". " << pMazeList[i] << endl;

		cout << "미로를 선택하세요 : ";
		int iSelect;
		cin >> iSelect;

		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile)
		{
			/* 미로의 세로 줄 수 만큼 반복 */
			for (int i = 0; i < 20; ++i)
			{
				fread(Maze[i], 1, 20, pFile);

				/* 현재 줄의 미로를 검사 */
				for (int j = 0; j < 20; ++j)
				{
					if (Maze[i][j] == '2')
					{
						pStartPos->x = j;
						pStartPos->y = i;

						pPlayer->tPos = *pStartPos;
					}

					else if (Maze[i][j] == '3')
					{
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}

				/* 개행 문자 읽기 */
				fread(&cCount, 1, 1, pFile);
			}
			fclose(pFile);
		}
	}

	/*pStartPos->x = 0;
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
	strcpy(Maze[19], "01011001000000000113");*/
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

			else if (Maze[i][j] == '5')
				cout << "ⓟ";

			else if (Maze[i][j] == '6')
				cout << "⇔";

			else if (Maze[i][j] == '7')
				cout << "▷";
		}
		cout << endl;
	}

	cout << "[폭탄 파워] : " << pPlayer->iBombPower << endl;
	cout << "[벽 통과] : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "[벽 밀기] : ";
	if (pPlayer->bWallPush)
	{
		cout << "가능 \\ ";

		if (pPlayer->bPushOnOff)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}
	else
		cout << "불가능 \\ OFF" << endl;
}

/* 아이템 획득 함수 */
bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		if (pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;

		return true;
	}

	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
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

		/* 벽 밀기가 가능할 때*/
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0')
		{
			/* 벽 밀기가 ON 상태인 경우 */
			if (pPlayer->bPushOnOff)
			{
				/* 위 위 칸이 0보다 크거나 같은 경우는 인덱스가 존재 */
				if (pPlayer->tPos.y - 2 >= 0)
				{
					/* 위 칸이 벽일 경우 */
					if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							--pPlayer->tPos.y;
					}

					/* 길일 경우 벽을 밀어낸다 */
					else if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1')
					{
						/* 위 위 칸을 벽으로 한다 */
						Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						/* 벽이였던 위 칸을 길로 만듬 */
						Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						/* 플레이어 이동 */
						--pPlayer->tPos.y;
					}
				}

				else if (pPlayer->bTransparency)
					--pPlayer->tPos.y;
			}

			/* 벽 밀기 OFF 상태일 경우 */
			else if (pPlayer->bTransparency)
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

		/* 벽 밀기가 가능할 때*/
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0')
		{
			/* 벽 밀기가 ON 상태인 경우 */
			if (pPlayer->bPushOnOff)
			{
				/* 아래 아래 칸이 20보다 작은 경우는 인덱스가 존재 */
				if (pPlayer->tPos.y + 2 < 20)
				{
					/* 아래 칸이 벽일 경우 */
					if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							++pPlayer->tPos.y;
					}

					/* 길일 경우 벽을 밀어낸다 */
					else if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '1')
					{
						/* 아래 아래 칸을 벽으로 한다 */
						Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						/* 벽이였던 아래 칸을 길로 만듬 */
						Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						/* 플레이어 이동 */
						++pPlayer->tPos.y;
					}
				}

				else if (pPlayer->bTransparency)
					++pPlayer->tPos.y;
			}

			/* 벽 밀기 OFF 상태일 경우 */
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.y;
		}
		/* 유령화 일 경우 */
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
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

		/* 벽 밀기가 가능할 때*/
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			/* 벽 밀기가 ON 상태인 경우 */
			if (pPlayer->bPushOnOff)
			{
				/* 오른쪽 오른쪽 칸이 0보다 크거나 같은 경우는 인덱스가 존재 */
				if (pPlayer->tPos.x + 2 < 20)
				{
					/* 오른쪽 칸이 벽일 경우 */
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '0')
					{
						if (pPlayer->bTransparency)
							++pPlayer->tPos.x;
					}

					/* 길일 경우 벽을 밀어낸다 */
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '1')
					{
						/* 오른쪽 오른쪽 칸을 벽으로 한다 */
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] = '0';
						/* 벽이였던 오른쪽 칸을 길로 만듬 */
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
						/* 플레이어 이동 */
						++pPlayer->tPos.x;
					}
				}

				else if (pPlayer->bTransparency)
					++pPlayer->tPos.x;
			}

			/* 벽 밀기 OFF 상태일 경우 */
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.x;
		}
		/* 유령화 일 경우 */
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

/* 왼쪽으로 움직이는 함수 */
void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		/* 벽인지 체크 */
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}

		/* 벽 밀기가 가능할 때*/
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
			/* 벽 밀기가 ON 상태인 경우 */
			if (pPlayer->bPushOnOff)
			{
				/* 왼쪽 왼쪽 칸이 0보다 크거나 같은 경우는 인덱스가 존재 */
				if (pPlayer->tPos.x - 2 >= 0)
				{
					/* 왼쪽 칸이 벽일 경우 */
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '0')
					{
						if (pPlayer->bTransparency)
							--pPlayer->tPos.x;
					}

					/* 길일 경우 벽을 밀어낸다 */
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '1')
					{
						/* 왼쪽 왼쪽 칸을 벽으로 한다 */
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						/* 벽이였던 왼쪽 칸을 길로 만듬 */
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						/* 플레이어 이동 */
						--pPlayer->tPos.x;
					}
				}

				else if (pPlayer->bTransparency)
					--pPlayer->tPos.x;
			}

			/* 벽 밀기 OFF 상태일 경우 */
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.x;
		}
		/* 유령화 일 경우 */
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
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

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
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

		for (int j = 1; j <= pPlayer->iBombPower; j++)
		{
			if (pBombArr[i].y - j >= 0) // 위
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					/* 아이템 드랍 확률을 구한다. */
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (rand() % 100 < 40)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';

						else if(iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';

						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}
				/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y + j < 20) // 아래
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					/* 아이템 드랍 확률을 구한다. */
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (rand() % 100 < 40)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';

						else if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';

						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}
				/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x - j >= 0) // 왼쪽
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					/* 아이템 드랍 확률을 구한다. */
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (rand() % 100 < 40)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';

						else if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x - j] = '6';

						else
							Maze[pBombArr[i].y - j][pBombArr[i].x - j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}
				/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + j < 20) // 오른쪽
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					/* 아이템 드랍 확률을 구한다. */
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (rand() % 100 < 40)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';

						else if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';

						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}
				/* 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다. */
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	*pBombCount = 0;
}

int main()
{
	/* 20 X 20 미로 생성 */
	char strMaze[21][21] = { 0 };

	srand((unsigned)time(NULL));

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
			cout << "출구에 도착했습니다." << endl;
			break;
		}

		cout << "[폭탄설치 : t] [폭탄 터뜨리기 : u] [벽밀기 ON/OFF : i]" << endl;
		cout << "[위 : w] [아래 : s] [왼쪽 : a] [오른쪽 : d] [종료 : q]" << endl;

		char cinput = _getch();

		if (cinput == 'q' || cinput == 'Q')
			break;

		else if (cinput == 't' || cinput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cinput == 'u' || cinput == 'U')
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cinput == 'i' || cinput == 'I')
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}

		else
			MovePlayer(strMaze, &tPlayer, cinput);
	}

	return 0;
}
