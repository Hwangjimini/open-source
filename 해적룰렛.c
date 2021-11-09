#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

char LJW(); //함수원형
void Gameover();
void CheckMouse(int* yy, int* xx, int* lr);
INPUT_RECORD rec;
DWORD        dwNOER;

int main()
{
    int n;//n*n이 게임칸의 갯수
    printf("몇 칸의 게임판을 할 것인가요?(n*n칸) n : ");
    scanf("%d", &n);
    int** arr;
    arr = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {

        arr[i] = (int*)malloc(sizeof(int) * n);
    }



    //n*n 게임판을 표시하기 위한 2차원 배열
    int i, j;   //i는 행, j는 열
    char c;      
    srand(time(NULL));   //난수함수의 무작위성 확대

    for (i = 0; i < n; i++)   //무작위로 입력
    {
        for (j = 0; j < n; j++)  //무작위로 입력
        {
            arr[i][j] = rand() % n+2; //난수입력
        }
    }
    while (1)     //무한반복
    {
        printf("게임판 : 총 %d 칸\n\n", n * n);
        printf(" ");
        for (i = 0; i < n; i++)
            printf(" %d", i + 1); //행번호
        printf("\n");

        for (i = 0; i < n; i++)   //행 만들기
        {
            printf(" %d", i + 1);  //열번호
            for (j = 0; j < n; j++)  //열 만들기
            {
                if (arr[i][j] == 1)
                    printf("■"); //선택된 칸 표시
                else if (arr[i][j] == 2)//꽝인 경우
                {
                    printf("□");
                }
                else
                {
                    printf("□"); //선택 가능한 칸 표시
                    
                }
            }
            printf("\n");   //줄바꿈
        }
        
        
    ONE:
        printf("행을 선택하시오 : ");
        scanf("%d", &i);     //행 번호 입력
        if (i <= 0)       //0 이하인 수를 입력할때
            return 0;      //프로그램 종료
        if (i > n)       //n보다 큰수를 입력할때
        {
            printf("*주의! %d행이 넘는 경우는 없습니다. 다시 입력하세요.\n\n", n);
            goto ONE;      //ONE으로 돌아간다.
        }
    TWO:
        printf("열을 선택하시오 : ");
        scanf("%d", &j);     //열 번호 입력
        if (j <= 0)       //0 이하인 수를 입력할때
            return 0;      //프로그램 종료
        if (j > n)       // 열 갯수보다 큰수를 입력할때
        {
            printf("*주의! %d열을 넘는 경우는 없습니다. 다시 입력하세요.\n\n", n);
            goto TWO;      //TWO으로 돌아간다.
        }
        if (arr[i - 1][j - 1] == 1)     //예약된 자리가 있을 경우
        {
            printf("이미 선택한 칸입니다. 다른 칸을 선택하시오\n");
            goto ONE;      //ONE으로 돌아간다.
        }
        else if (arr[i - 1][j - 1] == 2)
        {
            Gameover();
            break;
        }

        else
        {
            arr[i - 1][j - 1] = 1;    //선택한다.
            printf("\n해당 위치는 꽝이 아닙니다. \n%d행 %d열 선택됐습니다.\n\n", i, j);
          
        }


    THREE:
        printf("계속 진행하시려면 'y', 끝내시려면 'n'를 누르시오.\n");
        LJW();        //함수호출
        c = LJW();       //함수값을 c에다 입력
        if (c == 121)       //y를 입력했을 경우
            system("cls");     //화면 지우기
        else if (c == 110)      //n을 입력했을 경우
            return 0;      //프로그램 종료
        else
        {
            printf("\n'y'또는'n'을 입력하세요\n\n");
            goto THREE;
        }
    }
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);


}

char LJW()    //함수 정의
{
    char a;    //a값(실행 여부)를 입력 받음
    scanf("%c", &a); //값을 입력
    return a;   //a값을 반환
}

void Gameover()
{
    COORD Coor = { 0, 0 };
    DWORD dw;
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw); // 콘솔창 화면을 지운다.

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

