#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define COL         GetStdHandle(STD_OUTPUT_HANDLE)
#define BAE         SetConsoleTextAttribute(COL, 0x0008);
#define BAISE       SetConsoleTextAttribute(COL, 0x0007);
#define BLUE_1      SetConsoleTextAttribute(COL, 0x0009);
#define GREEN_2     SetConsoleTextAttribute(COL, 0x000a);
#define RED_3       SetConsoleTextAttribute(COL, 0x000c);
#define PURPLE_4    SetConsoleTextAttribute(COL, 0x000d);
#define SU_5        SetConsoleTextAttribute(COL, 0x000b);
#define SU_6        SetConsoleTextAttribute(COL, 0x0002);
#define SU_7        SetConsoleTextAttribute(COL, 0x0004);
#define SU_8        SetConsoleTextAttribute(COL, 0x0007);
#define SU_9        SetConsoleTextAttribute(COL, 0x000e);

INPUT_RECORD rec;
DWORD dwNOER;

HANDLE CIN = 0; //콘솔 입력장치
HANDLE COUT = 0;    // 콘솔 출력 장치

int map[31][31];
int ga, se, gae;

int loading() {
	int n;
	printf("몇 칸의 게임판을 할 것인가요?(n*n칸) n : \n");
	while (1) {
		scanf("%d", &n);
		if (1 <= n && n <= 30)
			break;
		printf("1이상 30이하로 입력해주세요 :");
	}
	ga = n;
	se = n;

	return n;
}

void mapcreate() {
	int i, j;
	int gatsu;

	for (i = 0; i < se; i++) { //배열 초기화
		for (j = 0; j < ga; j++) {
			map[i][j] = 0;
		}
	}

	gatsu = ga;

	for (i = 0; i < gatsu; i++) {  //꽝생성
		for (j = 0; j < gatsu; j++)
		{
			map[i][j] = rand() % ga + 2;  //1일때 선택되고 2일때 꽝으로 설정되게
		}
	}
}

void gotoxy(int x, int y) {  //커서를 x, y로 이동시킨다

	COORD coord = { 0,0 };
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gameendf() {

	printf("\n\n");
	printf("    ###           ###   \n");
	printf("    # #           # #    \n");
	printf("  ##  #           #  ##  \n");
	printf(" #     !#########!    #  \n");
	printf("  ###  #.       .#  ###  \n");
	printf("     :#~         ~#:     \n");
	printf("     #.           .#     \n");
	printf("     #             #     \n");
	printf("     #  ##     ##  #    \n");
	printf("     # ~# #   # #~ #  \n");
	printf("     # ~###   ###~ #     \n");
	printf("     # ~###   ###~ #    \n");
	printf("     #  ##  #  ##  #     \n");
	printf("     $     ###     $  \n");
	printf("      #    ###    #      \n");
	printf("     :~#         # ~:   \n");
	printf("  ###  ~.# # # #.~  ###  \n");
	printf("  #      $ # # $      #  \n");
	printf("  ##  #  $#####$  #  ##  \n");
	printf("    # #           # #    \n");
	printf("    ###           ###  \n");
	printf("\n        Game over\n");
}

void clearcon() {
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw); // 콘솔창 화면을 지운다.
}

void CheckMouse(int* yy, int* xx, int* lr, int* mse, int* mga) {
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임.

	if (rec.EventType == MOUSE_EVENT) {// 마우스 이벤트일 경우

		if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌측 버튼이 클릭되었을 경우

			int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X값 받아옴
			int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y값 받아옴

			if (mouse_x < ga * 2 && mouse_y < se + 1) {
				*xx = mouse_x;
				*yy = mouse_y;
				*lr = 1;
				*mse = mouse_y;
				*mga = mouse_x;
				//printf("%d, %d\n", mouse_x, mouse_y); // 좌표를 출력한다.
			}
		}

		else {
			int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X값 받아옴
			int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y값 받아옴

			if (mouse_x < ga * 2 && 0 < mouse_y && mouse_y < se + 1) {
				*mga = mouse_x;
				*mse = mouse_y;
				*lr = 3;
			}

			else {
				*mga = 200;
				*mse = 100;
				*lr = 10;
			}
		}
	}

	Sleep(10);
}

int main() {
	int mode = 0;
	int i, j;
	int lga = 0, lse = 0, lr = 0;
	int a = 0;
	int end = 0, endf = 0, mi = 0, s = 0, gaec = 0, keygam = 0;
	int mse = 31, mga = 31;
	srand((unsigned int)time(NULL));

	CONSOLE_CURSOR_INFO cursorInfo = { 0, }; // 커서 지우기
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	mode = loading();

	CIN = GetStdHandle(STD_INPUT_HANDLE);
	// 마우스 활성화
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);

	clearcon();
	mapcreate();

	while (1) {
		if (a != 0) {
			CheckMouse(&lse, &lga, &lr, &mse, &mga);
			lse = lse - 1;
			lga = lga / 2;
			mse = mse - 1;
			mga = mga / 2;

			if (lr == 1 && map[lse][lga] != 1 && map[lse][lga] != 2)
			{
				map[lse][lga] = 1;
			}
			if (lr == 1 && map[lse][lga] == 2)
			{
				endf++;
			}
		}

		if (a == 0) a++;

		gaec = 0;
		gotoxy(0, 0);
		printf("해적게임시작\n");

		for (i = 0; i < se; i++) { //틀만들기 
			for (j = 0; j < ga; j++) {

				if (map[i][j] == 1)
					printf("■"); //선택된 칸 표시
				else if (map[i][j] == 2)//꽝인 경우
				{
					printf("□");
				}

				else
				{
					printf("□"); //선택 가능한 칸 표시

				}
			}
			printf("\n");
		}

		if (endf != 0) {

			clearcon();
			gameendf();
			break;
		}
	}

	return 0;
}