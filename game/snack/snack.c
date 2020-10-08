/**
 *  author WenJuing
 * 
 *     by 2020.9.29
 */
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<stdbool.h>
#include<string.h>
#define random(a, b) (rand()%(b-a+1)+a)
#define black 0
#define blue 1
#define green 2
#define lakeblue 3
#define red 4
#define purple 5
#define yellow 6
#define white 7
#define grey 8
#define lightblue 9
#define lightgreen 0xA
#define lightlightgreen 0xB
#define lightred 0xC
#define lightpurple 0xD
#define lightyellow 0xE
#define lightwhite 0xF

/** 结构体 */
typedef struct node         //定义链表结构
{
    int x;
    int y;
    struct node * pNext;
} NODE, * PNODE;

typedef struct food         //定义食物的结构
{
    int x;
    int y;
} FOOD;
typedef struct player       // 定义玩家信息
{
    char name[20];          // 玩家姓名
    float score;            // 得分
    int rank;               // 排名
} PLAYER;


/** 全局变量 */
PNODE pHead;                // 定义蛇头指针
PNODE pTail;                // 定义蛇尾指针
PNODE pToxic;               // 定义毒食物头指针
PNODE pToxicTail;           // 定义毒食物尾指针
FOOD food;                  // 定义食物
PLAYER player;              // 定义玩家 
// 定义可供选择的颜色
char click = 'd';           // 输入值
int speed = 300;            // 移动速度


const char * difficulty[6] = {"very easy", "easy     ", "normal   ", "difficult", "very difficult", "hell          "};

int MIN_X = 0;        // 边界各边最值（可根据得分改变）
int MAX_X = 70;
int MIN_Y = 0;
int MAX_Y = 28;

/** 方法 */
PNODE initSnack();              // 初始化蛇头
PNODE initToxic();              // 初始化毒物
void welcome();                 // 开始界面
void game();                    // 游戏运行主体
void gotoxy(int x, int y);      // 定位
void moving();                  // 移动
void printBoundary();           // 打印边界
void printBody();               // 打印身体
void printTipAndJudge();                // 打印附加信息及判断（包括得分、难度）
void createFood();              // 生成食物
void getNewToxicXAndY();        // 得到新毒物随机坐标
void appendToxicBody(int x, int y);     // 追加毒物
void appendBody(int oldX, int oldY);    // 追加身体
void changeBody(int NewX, int NewY);    // 身体变换
bool eating();                  // 吃食物
void deleteFood(int x, int y);  // 删除食物
void deleteBody(int x, int y);  // 删除身体（其实是在最后一个节点的位置打印空白）
void printAll();                // 打印各节点详情
bool isOver();                  // 判断游戏是否结束
void gameOver();                // 结束界面
void writeGrade();              // 写入成绩，以便下次打开界面可看排名
void getGrade();                // 读入成绩

int main(void)
{
    system("color 03");
    
    pHead = initSnack();
    pToxic = initToxic();
    srand((unsigned)time(NULL));
    welcome();
    printBoundary();
    createFood();
    game();
    return 0;
}
void game()
{
    while (isOver() != true) {
    int oldX, oldY;
    oldX = pTail->x;
    oldY = pTail->y;
    printTipAndJudge();
    printBody();    // 打印身体
    Sleep(speed);   // 延时
    moving();
    if (eating()) {
            if (player.score >= 150) {          // hell
        player.score += 8;
        getNewToxicXAndY();
        getNewToxicXAndY();
        getNewToxicXAndY();
        getNewToxicXAndY();
        getNewToxicXAndY();
    } else if (player.score >= 100) {   // very difficult
        player.score += 5;
        getNewToxicXAndY();
        getNewToxicXAndY();
        getNewToxicXAndY();
        getNewToxicXAndY();
    } else if (player.score >= 50) {    // difficult
        player.score += 4;
        getNewToxicXAndY();
        getNewToxicXAndY();
        getNewToxicXAndY();
    } else if (player.score >= 20) {    // normal
        player.score += 3;
        getNewToxicXAndY();
        getNewToxicXAndY();
    } else if (player.score >= 5) {    // easy
        player.score += 2;
        getNewToxicXAndY();
    } else {                            // very easy
        (player.score)++;
    }
        deleteFood(food.x, food.y);
        createFood();
        appendBody(oldX, oldY);
        moving();
    }
    deleteBody(oldX, oldY);     // 末尾位置打印空
    }
    gameOver();
}
void getNewToxicXAndY()
{
    int x, y;
    PNODE p = pHead;
    boolean flag = false;
    while (flag == false) {
    x = random(MIN_X+2, MAX_X-4);
    y = random(MIN_Y+1, MAX_Y-3);
    if (x % 2 != 0) {
        x -= 1;
        }
        while (p->pNext != NULL) {
            // 若生成毒物的位置和蛇身及食物重合，则从新生成
            if (x == p->pNext->x && y == p->pNext->y || x == food.x && x == food.y) {   
                flag = false;
                break;
            } else {
                flag = true;
            }
            p = p->pNext;
        }
    }
    appendToxicBody(x, y);
}
void appendToxicBody(int x, int y)
{
    PNODE pT = pToxic;
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->x = x;
    pNew->y = y;
    while (pT->pNext != NULL) {
        pT = pT->pNext;
    }
    pT->pNext = pNew;
    pNew->pNext = NULL;
    pToxicTail = pNew;
}
void appendBody(int oldX, int oldY)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    pNew->x = oldX;
    pNew->y = oldY;
    pTail->pNext = pNew;
    pNew->pNext = NULL;
    pTail = pNew;
    
}
PNODE initToxic()
{
    pToxic = (PNODE)malloc(sizeof(NODE));
    pToxic->pNext = NULL;
    pToxicTail = pToxic;
    return pToxic;
}
PNODE initSnack()
{
    pHead = (PNODE)malloc(sizeof(NODE));
    // 蛇头的初始位置
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    PNODE pNew2 = (PNODE)malloc(sizeof(NODE));
    pNew->x = 20;
    pNew->y = 10;
    pNew2->x = 22;
    pNew2->y = 10;
    pHead->pNext = pNew;    // pHead -> pNew -> pNew2 = pTail
    pNew->pNext = pNew2;
    pNew2->pNext = NULL;
    pTail = pNew2;
    return pHead;
}
void getGrade()
{
    int ch;
    FILE * fp = fopen("game/snack/rank.txt", "r");
    while ((ch = getc(fp)) != EOF) {
        putchar(ch);
    }
    if (fclose(fp) != 0) printf("Error for get grade from \"rank.txt\"!");
}
void writeGrade()
{
    int ch;
    int i = 0;
    char all[100];    // 排名 玩家名字 分数
    int rank = 1;       // 排名
    char arr[20];   // 过渡字符，提取分数
    char arr2[20];   // 过渡字符，提取排名
    FILE * fpout = fopen("game/snack/rank.txt", "a+");
    // 把排名加上
    strcat(all, "   ");
    itoa(rank, arr2, 10);
    strcat(all, arr2);
    // 把分数加上
    memset(arr, '\0', sizeof(arr));
    sprintf(arr, "%.2f", player.score);
    strcat(all, "        ");
    strcat(all, arr);
    // 把名字加上
    strcat(all, "      ");
    strcat(all, player.name);
    while ((ch = all[i++])) {   // 载入成绩到 rank.txt
        putc(ch, fpout);
    }
    if (fclose(fpout) != 0) printf("Error for writing grade into \"rank.txt\"!");
}
void welcome()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n");
    SetConsoleTextAttribute(hConsole, lightyellow);
    printf("This game was written by WenJuing.\n");
    printf("\n");
    printf("      ________      _________      ______        ________      ___  ___   \n");
    printf("     /  _____/|    /  ___   /|    /  _   |      /  _____/|    /  / /  /|  \n");
    printf("    /  /|___|/    /  /| /  / /   /  /_|  |     /  /|____|/   /  /_/  / /  \n");
    printf("   /____   /|    /  / //  / /   /   __   |    /  / /        /  /__  / /   \n");
    printf("  _|___/  / /   /  / //  / /   /  /|__|  |   /  /_/___     /  / ||  |/    \n");
    printf(" /_______/ /   /__/ //__/ /   /__/ /  |__|  /_______/ |   /__/ / |__|     \n");
    printf(" |_______|/    |__|/ |__|/    |__|/   |__|  |_______|/    |__|/  |__|     \n");
    printf("\n");
    printf("\n");
    // SetConsoleTextAttribute(hConsole, lightred);   // 淡红色
    printf("\n");
    // getGrade();     // 载入成绩排行
    printf("\n");
    SetConsoleTextAttribute(hConsole, lakeblue);
    printf("控制：上移w，下移s，左移a，右移d。\n");
    printf("\n");
    printf("规则：蛇头碰到墙壁，或者反向移动，或按其他键，或碰到障碍物，则游戏结束。每吃到一个食物，则加分。\n");
    printf("\n");
    printf("请输入你的姓名（按回车确认）：");
    SetConsoleTextAttribute(hConsole, lightyellow);
    fgets(player.name, 20, stdin);      // 自带回车
    SetConsoleTextAttribute(hConsole, lakeblue);
    printf("\n");
    printf("Prease press any where to begin the game...\n");
    getch();
    system("CLS");
}
void printAll()
{
    int i = 1;
    NODE p = *pHead;
    while (p.pNext != NULL)
    {
        gotoxy(70, i+2);
        printf("第%d个节点：x=%d，y=%d\n", i, p.pNext->x, p.pNext->y);
        i++;
        p.pNext = p.pNext->pNext;
    }
}
void createFood()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    food.x = 0;
    food.y = 0;
    PNODE p = pHead;
    boolean flag = false;
    while (flag == false) {
    srand((unsigned)time(NULL));
    food.x = random(MIN_X+2, MAX_X-6);
    food.y = random(MIN_Y+1, MAX_Y-3);
    if (food.x%2 != 0) {
        food.x -= 1;
        }
        while (p->pNext != NULL) {
            if (food.x == p->pNext->x && food.y == p->pNext->y) {   // 若生成食物的位置和蛇身重合，则从新生成
                flag = false;
                break;
            } else {
                flag = true;
            }
            p = p->pNext;
        }
    }
    gotoxy(food.x, food.y);
    SetConsoleTextAttribute(hConsole, lightgreen);
    printf("⊙");
    SetConsoleTextAttribute(hConsole, lakeblue);
}
void printTipAndJudge()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int r;
    int i = 0;
    PNODE pT = pToxic;
    if (player.score >= 150) {          // hell
        r = 5;
        speed = 100;
    } else if (player.score >= 100) {   // very difficult
        r = 4;
        speed = 120;
    } else if (player.score >= 50) {    // difficult
        r = 3;
        speed = 150;
    } else if (player.score >= 20) {    // normal
        r = 2;
        speed = 180;
    } else if (player.score >= 5) {    // easy
        r = 1;
        speed = 250;
    } else {                           // very easy
        r = 0;
    }
    // 获得障碍物个数
    while (pT->pNext != NULL) {
        i++;
        pT = pT->pNext;
    }
    gotoxy(76, 3);
    printf("This is your score: ");
    SetConsoleTextAttribute(hConsole, lightyellow);
    printf("%.2f", player.score);
    SetConsoleTextAttribute(hConsole, lakeblue);
    gotoxy(76, 5);
    printf("difficulty: ");
    SetConsoleTextAttribute(hConsole, red);
    printf("%s", difficulty[r]);
    SetConsoleTextAttribute(hConsole, lakeblue);
    gotoxy(76, 7);
    printf("障碍物个数: ");
    SetConsoleTextAttribute(hConsole, red);
    printf("%d", i);
    SetConsoleTextAttribute(hConsole, lakeblue);
    gotoxy(76, 11);
    SetConsoleTextAttribute(hConsole, lightlightgreen);
    printf("玩的愉快~ |o'-'o) *");
    SetConsoleTextAttribute(hConsole, lakeblue);
}
void printBody()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    NODE p = *pHead;
    while (p.pNext != NULL) {
        gotoxy(p.pNext->x, p.pNext->y);
        SetConsoleTextAttribute(hConsole, lightyellow);
        printf("□");
        SetConsoleTextAttribute(hConsole, lakeblue);
        p.pNext = p.pNext->pNext;
    }
    p = *pToxic;
    while (p.pNext != NULL) {
        gotoxy(p.pNext->x, p.pNext->y);
        SetConsoleTextAttribute(hConsole, red);
        printf("×");
        SetConsoleTextAttribute(hConsole, lakeblue);
        p.pNext = p.pNext->pNext;
    }
}
void printBoundary()
{
    for (int i=MIN_X; i<=MAX_X; i+=2) {     // 打印上下边
        gotoxy(i, MIN_Y);
        printf("■");
        gotoxy(i, MAX_Y);
        printf("■");
    }
    for (int i=MIN_Y; i<=MAX_Y; i++) {     // 打印左右边
        gotoxy(MIN_X, i);
        printf("■");
        gotoxy(MAX_X, i);
        printf("■");
    }
}
void deleteBody(int x, int y)
{
    gotoxy(x, y);
    printf("  ");
}
void deleteFood(int x, int y)
{
    gotoxy(x, y);
    printf("  ");
}
void moving()
{
    // 记录移动后头的位置，初始值为头位置
    int NewX = pHead->pNext->x;
    int NewY = pHead->pNext->y;

        if (kbhit()) click = getch();   //若有输入，则获取
        switch (click)
        {
        case 'w':
                NewY -= 1;
            break;
        case 's':
                NewY += 1;
            break;
        case 'a':
                NewX -= 2;
            break;
        case 'd':
                NewX += 2;
            break;
        default:
            break;
        }
        changeBody(NewX, NewY);
}
void changeBody(int NewX, int NewY)     // 头部位置改变后，将第二节位置赋值头位置，第三节位置赋值第二节位置...以此类推
{
    // 新增头节点，连接旧蛇头
    PNODE new_first = (PNODE)malloc(sizeof(NODE));
    new_first->x = NewX;
    new_first->y = NewY;
    new_first->pNext = pHead->pNext;
    pHead->pNext = new_first;
    // 删除尾节点
    PNODE p = pHead;
    while (p->pNext->pNext != NULL)
    {
        p = p->pNext;
    }
    PNODE r = p->pNext;
    free(r);
    r = NULL;
    p->pNext = NULL;
    pTail = p;
}
bool eating() 
{
    return (pHead->pNext->x==food.x && pHead->pNext->y==food.y);  //若头位置等于食物位置，返回true 
}
bool isOver()
{
    PNODE p = pHead->pNext;
    PNODE pT = pToxic;
    int headX = p->x;
    int headY = p->y;

    // 若蛇头撞到边界，则游戏结束
    for (int i=MIN_X; i<=MAX_X; i+=2) {     // 蛇头等于上下边界任一坐标
        if (headX == i && headY == MIN_Y) return true;
        if (headX == i && headY == MAX_Y) return true;
    }
    for (int i=MIN_Y; i<=MAX_Y; i++) {     // 蛇头等于左右边界任一坐标
        if (headY == i && headX == MIN_X) return true;
        if (headY == i && headX == MAX_X) return true;
    }
    // 若蛇头撞到自己，则游戏结束
    while (p->pNext != NULL) {
        if (headX == p->pNext->x && headY == p->pNext->y) return true;
        p = p->pNext;
    }
    // 若蛇头撞到毒物，则游戏结束
    while (pT->pNext != NULL) {
        if (headX == pT->pNext->x && headY == pT->pNext->y) return true;
        pT = pT->pNext;
    }
    return false;

}
void gameOver()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 清除蛇链表
    PNODE p = pHead;
    PNODE q;
    while (p->pNext != NULL) {
        q = p->pNext;
        free(p);
        p = NULL;
        p = q;
    }
    // 清除毒物链表
    PNODE pT = pToxic;
    PNODE qT;
    while (pT->pNext != NULL) {
        qT = pT->pNext;
        free(pT);
        pT = NULL;
        pT = qT;
    }
    // 写入成绩
    writeGrade();
    gotoxy(26, 4);
    SetConsoleTextAttribute(hConsole, lightyellow);
    printf("____________________");
    gotoxy(28, 6);
    printf("  GAME OVER！\n");
    gotoxy(28, 8);
    printf("Your score is %.2f\n", player.score);
    gotoxy(26, 10);
    printf("____________________");
    SetConsoleTextAttribute(hConsole, lakeblue);
    getch();
    gotoxy(26, 12);
    printf("按任意键结束游戏");
    getch();
}
void gotoxy(int x, int y)
{
    // 更新光标位置 
    COORD pos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOutput, pos);
    // 隐藏光标 
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
}