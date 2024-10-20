// �� �߰�.ver

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
float dropSpeed = 800.0; // �ʱ� ��� �ӵ� (�и���)

HANDLE hConsole;

int block[7][4][4][4] = {
	{ // T��� ��
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
	{    // ���� ��
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
	{   // ���� �� �ݴ�
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
	{   // 1���� ��
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
	{   // L���� ��
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
	{   // L���� �� �ݴ�
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
	{   // �׸� ��
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
// �� �밡�� �������� -_-
int space[15 + 1][10 + 2] = {  // ���� 15+1(�Ʒ���)ĭ, ���� 10+2(���� ��)ĭ  
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
//GPT ����
void Init() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    srand(time(NULL));
    system("cls");
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
// GPT ����
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// ���� ����
void CreateRandomForm() {
    blockForm = rand() % 7;
    blockRotation = 0;
}
// GPT ����
bool CheckCrash(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[blockForm][blockRotation][i][j] == 1) {
                int t = space[i + y][j + x / 2];
                if (t == 1 || t == 2) { // ���� ��, ���� ��
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

// ���� ����
void BlockToGround() {
    if (CheckCrash(x, y + 1) == true) {
        if ((float)(endT - startGroundT) > 500) { // ���鿡 ���� �� ������
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
// GPT ����
void RemoveLine() {
    for (int i = 15; i >= 0; i--) { // ������ ������ ��
        int cnt = 0;
        for (int j = 1; j < 11; j++) {
            if (space[i][j] == 2) {
                cnt++;
            }
        }
        if (cnt >= 10) { // ������ �� ���ִٸ�
            score += 100; // ���� ����
            dropSpeed *= 0.95; // �ӵ� ����
            for (int j = 0; i - j >= 0; j++) {
                for (int x = 1; x < 11; x++) {
                    if (i - j - 1 >= 0)
                        space[i - j][x] = space[i - j - 1][x];
                    else      // õ���̸� 0����
                        space[i - j][x] = 0;
                }
            }
            i++; // ���� ���� �� �ٽ� �˻�
        }
    }
}

void DrawMap() {
    gotoxy(0, 0);
    printf("Score: %d\n", score);
    SetConsoleTextAttribute(hConsole, 7); // ������� �� �׸���
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 12; j++) {
            if (space[i][j] == 1) {
                gotoxy(j * 2, i + 1);
                printf("��");
            }
            else if (space[i][j] == 2) {
                gotoxy(j * 2, i + 1);
                printf("��");
            }
        }
    }
}

void DrawBlock() {
    // �� ��ϸ��� ������ ���� ����
    int color;
    switch (blockForm) {
    case 0: color = 5; break; // T ��� - ���ֻ�
    case 1: color = 6; break; // ���� ��� - �����
    case 2: color = 2; break; // �ݴ� ���� ��� - �ʷϻ�
    case 3: color = 1; break; // 1���� ��� - �Ķ���
    case 4: color = 4; break; // L���� ��� - ������
    case 5: color = 3; break; // �ݴ� L���� ��� - û�ϻ�
    case 6: color = 14; break; // �׸� ��� - ���� �����
    default: color = 7; break;
    }
    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[blockForm][blockRotation][i][j] == 1) {
                gotoxy(x + j * 2, y + i + 1);
                printf("��");
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 7); // �⺻ ����(���)���� �ǵ�����
}


void InputKey() {
    if (_kbhit()) {
        key = _getch();
        switch (key) {
        case 32: // space - ��� ȸ��
            blockRotation = (blockRotation + 1) % 4;
            if (CheckCrash(x, y)) {
                blockRotation = (blockRotation + 3) % 4; // ȸ�� �Ұ� �� ���󺹱�
            }
            break;
        case 75: // ����
            if (!CheckCrash(x - 2, y)) {
                x -= 2;
            }
            break;
        case 77: // ������
            if (!CheckCrash(x + 2, y)) {
                x += 2;
            }
            break;
        case 80: // �Ʒ�
            if (!CheckCrash(x, y + 1)) {
                y++;
            }
            break;
        case 'p': // �Ͻ�����
            PauseGame();
            break;
        }
        system("cls");
    }
}
void GameOver() {
    system("cls");
    gotoxy(5, 7);
    printf("Game Over! ��������: %d\n", score);
    exit(0);
}
void PauseGame() {
    gotoxy(5, 7);
    printf("�Ͻ�����. �ٽ� �����Ϸ��� �ƹ� Ű�� ��������...");
    _getch();
    system("cls");
}
void StartScreen() {
    system("cls");
    gotoxy(5, 5);
    printf("TETRIS\n");
    gotoxy(3, 7);
    printf("�����Ϸ��� �ƹ� Ű�� ��������...");
    _getch();
    system("cls");
}
