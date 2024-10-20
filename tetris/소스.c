// 색 추가.ver

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <stdbool.h>

clock_t startDropT, endT, startGroundT;
int x = 8, y = 0;
RECT blockSize;
int blockForm;
int blockRotation = 0;
int key;
int score = 0;
float dropSpeed = 800.0; // 초기 드롭 속도 (밀리초)

HANDLE hConsole;

int block[7][4][4][4] = {
	{ // T모양 블럭
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // 번개 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 번개 블럭 반대
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형 블럭
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭 반대
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 네모 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};
// 블럭 노가다 개귀찮네 -_-
int space[15 + 1][10 + 2] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)칸  
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};
void Init();
void gotoxy(int x, int y);
void CreateRandomForm();
bool CheckCrash(int x, int y);
void DropBlock();
void BlockToGround();
void RemoveLine();
void DrawMap();
void DrawBlock();
void InputKey();
void GameOver();
void PauseGame();
void StartScreen();

int main() {
    Init();
    StartScreen();
    startDropT = clock();
    CreateRandomForm();

    while (true) {
        DrawMap();
        DrawBlock();
        DropBlock();
        BlockToGround();
        RemoveLine();
        InputKey();
    }
    return 0;
}
//GPT 도움
void Init() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    srand(time(NULL));
    system("cls");
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
// GPT 도움
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// 구글 도움
void CreateRandomForm() {
    blockForm = rand() % 7;
    blockRotation = 0;
}
// GPT 도움
bool CheckCrash(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[blockForm][blockRotation][i][j] == 1) {
                int t = space[i + y][j + x / 2];
                if (t == 1 || t == 2) { // 벽일 때, 블럭일 때
                    return true;
                }
            }
        }
    }
    return false;
}
void DropBlock() {
    endT = clock();
    if ((float)(endT - startDropT) >= dropSpeed) {
        if (CheckCrash(x, y + 1) == true) {
            startGroundT = clock();
            return;
        }
        y++;
        startDropT = clock();
        startGroundT = clock();
        system("cls");
    }
}

// 구글 도움
void BlockToGround() {
    if (CheckCrash(x, y + 1) == true) {
        if ((float)(endT - startGroundT) > 500) { // 지면에 닿은 후 딜레이
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (block[blockForm][blockRotation][i][j] == 1) {
                        space[i + y][j + x / 2] = 2;
                    }
                }
            }
            x = 8;
            y = 0;
            CreateRandomForm();
            if (CheckCrash(x, y)) {
                GameOver();
            }
        }
    }
}
// GPT 도움
void RemoveLine() {
    for (int i = 15; i >= 0; i--) { // 벽라인 제외한 값
        int cnt = 0;
        for (int j = 1; j < 11; j++) {
            if (space[i][j] == 2) {
                cnt++;
            }
        }
        if (cnt >= 10) { // 벽돌이 다 차있다면
            score += 100; // 점수 증가
            dropSpeed *= 0.95; // 속도 증가
            for (int j = 0; i - j >= 0; j++) {
                for (int x = 1; x < 11; x++) {
                    if (i - j - 1 >= 0)
                        space[i - j][x] = space[i - j - 1][x];
                    else      // 천장이면 0저장
                        space[i - j][x] = 0;
                }
            }
            i++; // 라인 제거 후 다시 검사
        }
    }
}

void DrawMap() {
    gotoxy(0, 0);
    printf("Score: %d\n", score);
    SetConsoleTextAttribute(hConsole, 7); // 흰색으로 벽 그리기
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 12; j++) {
            if (space[i][j] == 1) {
                gotoxy(j * 2, i + 1);
                printf("□");
            }
            else if (space[i][j] == 2) {
                gotoxy(j * 2, i + 1);
                printf("■");
            }
        }
    }
}

void DrawBlock() {
    // 각 블록마다 고유한 색상 설정
    int color;
    switch (blockForm) {
    case 0: color = 5; break; // T 블록 - 자주색
    case 1: color = 6; break; // 번개 블록 - 노란색
    case 2: color = 2; break; // 반대 번개 블록 - 초록색
    case 3: color = 1; break; // 1자형 블록 - 파란색
    case 4: color = 4; break; // L자형 블록 - 빨간색
    case 5: color = 3; break; // 반대 L자형 블록 - 청록색
    case 6: color = 14; break; // 네모 블록 - 밝은 노란색
    default: color = 7; break;
    }
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[blockForm][blockRotation][i][j] == 1) {
                gotoxy(x + j * 2, y + i + 1);
                printf("■");
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 7); // 기본 색상(흰색)으로 되돌리기
}


void InputKey() {
    if (_kbhit()) {
        key = _getch();
        switch (key) {
        case 32: // space - 블록 회전
            blockRotation = (blockRotation + 1) % 4;
            if (CheckCrash(x, y)) {
                blockRotation = (blockRotation + 3) % 4; // 회전 불가 시 원상복구
            }
            break;
        case 75: // 왼쪽
            if (!CheckCrash(x - 2, y)) {
                x -= 2;
            }
            break;
        case 77: // 오른쪽
            if (!CheckCrash(x + 2, y)) {
                x += 2;
            }
            break;
        case 80: // 아래
            if (!CheckCrash(x, y + 1)) {
                y++;
            }
            break;
        case 'p': // 일시정지
            PauseGame();
            break;
        }
        system("cls");
    }
}
void GameOver() {
    system("cls");
    gotoxy(5, 7);
    printf("Game Over! 최종점수: %d\n", score);
    exit(0);
}
void PauseGame() {
    gotoxy(5, 7);
    printf("일시정지. 다시 시작하려면 아무 키나 누르세요...");
    _getch();
    system("cls");
}
void StartScreen() {
    system("cls");
    gotoxy(5, 5);
    printf("TETRIS\n");
    gotoxy(3, 7);
    printf("시작하려면 아무 키나 누르세요...");
    _getch();
    system("cls");
}
