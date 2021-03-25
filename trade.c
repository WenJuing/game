#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "trader.h"


int main(int argc, char const *argv[])
{
    // system("mode con cols=150 lines=38");
    welcome();
    game();
    gameOver();
    system("pause");
    return 0;
}
void welcome()
{
    printf("游戏名：");
    printf("《关于为了家族存亡我不得不背上行囊带货这回事》   ");
    printf("发行日期：2020-9-4   版本：1.0\n");
    printf("\n");
    printf("【故事背景】\n");
    printf("\n");
    printf("哇——哇————，着一声清亮的哭声，打破了这偏远山村的宁静。\n");
    getch();
    printf("\n");
    printf("绵延苍山，小溪流边，山村一处小木屋子里突然爆发一道紫光，直冲云霄！\n");
    getch();
    printf("\n");
    printf("祥云萦绕，九龙盘腾，天地异变，万物竞生！\n");
    getch();
    printf("\n");
    printf("你出生了...\n");
    getch();
    printf("\n");
    printf("十八年后\n");
    getch();
    printf("\n");
    printf("一天。儿子！家族有难了，四十天后家族再没有收入，家族就倒闭了！。\n");
    getch();
    printf("\n");
    printf("。。。你就带着这4000块去小镇上看看有没有什么生意做吧，家族就全靠你了\n");
    getch();
    printf("\n");
    printf("最好赚够50万回来，不然杯水车薪。。。\n");
    getch();
    printf("\n");
    printf("你无奈苦笑，行吧！”\n");
    getch();
    printf("\n");
    printf("你双手抱拳，慢慢退了下去...\n");
    getch();
    printf("\n");
    printf("浪迹天涯，背负家族存亡的历练开始了！\n");
    getch();
    printf("\n");
    printf("请输入你的姓名：");
    scanf("%s", leimu.name);
    system("CLS");
}
void game()
{
    int opt;
    while( *pDay!=1 ) {
    (*pDay)--;    //推出商店，减一天
    opt = 0;
    locality();
    Arr arr;                    //储存当轮商店里的商品编号
    selectItem(&arr);           //创建数量范围为[4,10]的随机商品编号
    delete_same_value(&arr);    //删除的重复编号
    create_all_market_price();  //给商品赋予市场价格
    while( opt!=-2) {
    store(&arr);
    possession();
    gotoxy(0,9);
    opt = transaction(&arr);
        }
        system("CLS");
    }
}
bool locality()
{
    int opt = 0;
    while (opt!=1 || opt!=2 ||opt!=3 || opt!=4 || opt!=5 || opt!=6 || opt!=7 || opt!=8 || opt!=9 ) {
    printf("1.清华路     2.长安街     3.莲花畔\n");
    printf("\n");
    printf("4.步行街     5.杏花村     6.垂露亭\n");
    printf("\n");
    printf("7.商业街     8.中关村     9.雨露町\n");
    printf("\n");
    printf("你要去哪？\n");
    scanf("%d", &opt);
    if (opt==1 || opt==2 ||opt==3 || opt==4 || opt==5 || opt==6 || opt==7 || opt==8 || opt==9) {
        system("CLS");
        break;
    } else {
        printf("没这地儿啊~\n");
        system("CLS");
        }
    }
    return true;
}

void store(Arr * arr)
{
    int i;
    printf("【第%d天】\n", 41-*pDay);
    gotoxy(30,1);
    printf("【商店】\n");
    printf("编号|       物品        |    价格    |    数量    |\n");
    for ( i=0; i<arr->cnt; i++) {
        int id = arr->a[i];
        printf("%4d|%-19s|%12.2f|%12d|\n", goods[id-1].id, goods[id-1].name, goods[id-1].market_value, (goods+id-1)->quantity);
    }
    printf("%4d|退出商店", -2);
}
void create_all_market_price()
{
    int i;
    for( i=0; i<maxId; i++ ) {
        one(&goods[i]);
    }
}
void one(Item * goods)
{
    goods->market_value = marketPrice(*goods);
}
float marketPrice(Item goods)
{
    int i;
    float res;
    float rand_price[10];
    srand((unsigned)time(NULL));
    for ( i=0; i<10; i++ ) {
        rand_price[i] = ((goods.value)+(int)(goods.value_up*rand()/RAND_MAX + 1.0));
    }
    res = rand_price[1+(int)(8*rand()/RAND_MAX+1.0)];
    return res;
}
void selectItem(Arr * arr)
{
    int i;
    arr->cnt = 0;
    arr->len = 10;
    srand((unsigned)time(NULL));
    int kinds = 4+(int)(4*rand()/RAND_MAX+1.0);
    for ( i=0; i<kinds; i++ ) {
        arr->a[i] = 1+(int)((maxId-1)*rand()/RAND_MAX+1.0);
        arr->cnt++;
    }
}
void delete_same_value(Arr * arr)
{
    int i, j, k;
    for ( i=0; i<arr->cnt; i++) {
        for ( j=i+1; j<arr->cnt; j++) {
            if ( arr->a[i] == arr->a[j] ) {
                arr->a[i] = 0;
                int begin = i;
                for ( k=begin; k<=arr->cnt; k++) {
                    arr->a[k] = arr->a[k+1];
                }
                arr->cnt--;
            }
        }
    }
}
int transaction(Arr * arr)
{
    int id, opt, num, have = 0;    //id商品编号，id-1商品下标
    while ( have!=1 )
    {
        printf("\n");
        printf("\n");
        printf("\n");
        printf("请选择商品编号：\n");
        scanf("%d", &id);
        for( int i=0; i<arr->cnt; i++ ) {   //判断选中的编号是否在编号数组中
        if( id==arr->a[i] ) {
            have = 1;
            }
        }
    if( id==-2) return id;
        if( have == 0) {
        printf("这家店没有你要的商品哦~\n");
        getch();
        }
    }
    printf("1.购买\n");
    printf("2.售卖\n");
    scanf("%d", &opt);
    if ( opt==1 ) {
        int afford_max = *pMoney / goods[id-1].market_value;
        printf("你购买的是%s，你要买多少呢？(最大可购买数为%d)：", goods[id-1].name, afford_max);
        scanf("%d", &num);
        if ( *pMoney-num*goods[id-1].market_value<0 ) {    //判断是否拥有足够的钱
        gotoxy(0,20);
        printf("你是在开玩笑吗？\n");
        getch();
        system("CLS");
        return 0;
    } else {
        addPos(&leimu, &goods[id-1], num);
        system("CLS");
    }
    } else if ( opt==2 ) {
        printf("你售卖的是%s，你要卖多少呢？：", goods[id-1].name);
        scanf("%d", &num);
        int i;
        for ( i=0; i<leimu.kinds; i++ ) {
            if ( leimu.own[i].id == goods[id-1].id ) {  //判断是否拥有该商品
                if ( leimu.own[i].quantity < num ) {
                    gotoxy(0,20);
                    printf("你没有这么多商品哦~\n");
                    getch();
                    system("CLS");
                    return 0;
                } else {
                    sellPos(&leimu, &goods[id-1], num, i);
                    system("CLS");
                    return 0;
                }
            }
        }
        gotoxy(0,20);
        printf("你没有该商品。\n");
        getch();
        system("CLS");
    } else {
        gotoxy(0,20);
        printf("操作不存在。\n");
        getch();
        system("CLS");
    }
}
bool sellPos(Player * leimu, Item *goods, int num, int index)
{
    int i;
    if ( leimu->own[index].quantity == num ) {  //情况一、售卖数量等于拥有数量
        *pMoney += goods->market_value * num;
        leimu->cnt -= num;
        deleteOwnItem(&leimu,index);   //删除拥有该商品的全部信息
    } else {    //情况二、售卖数量小于拥有数量
        *pMoney += goods->market_value * num;
        leimu->cnt -= num;
        leimu->own[index].quantity -= num;
    }
    goods->quantity += num;
    return true;
}
bool addPos(Player * leimu, Item *goods, int num)
{
    int i;
    if( leimu->cnt>=leimu->len ) {
        printf("超出最大容量！（%d）\n", leimu->len);
        getch();
        return false;
    }
        *pMoney -= num*goods->market_value;
        goods->quantity -= num;
    for ( i=0; i<leimu->kinds; i++ ) {
        if ( leimu->own[i].id == goods->id) { //判断是否已拥有同类商品
            int oldcount = leimu->own[i].quantity;  //原总数
            int oldsum = leimu->own[i].quantity * leimu->own[i].market_value;  //原总价
            leimu->own[i].quantity += num;
            leimu->cnt += num;
            leimu->own[i].market_value = (oldsum + goods->market_value * num) / (oldcount + num); //该商品新价格（旧+新的平均值 ）
        }
    }
    for ( i=0; i<leimu->kinds; i++ ) {
        if ( leimu->own[i].id == goods->id ) return false;  //若已拥有该商品，则返货false
    }
        //暂未拥有该商品
        strcpy(leimu->own[leimu->kinds].name,goods->name);
        leimu->own[leimu->kinds].id = goods->id;
        leimu->own[leimu->kinds].quantity = num;
        leimu->own[leimu->kinds].market_value = goods->market_value;
        leimu->cnt += num;
        (leimu->kinds)++;
    return true;
}
bool deleteOwnItem(Player ** leimu, int index)
{
    int i;
    memset(&((*leimu)->own[index]), 0, sizeof((*leimu)->own[index]));   //清空该商品信息
    for ( i=index; i<=(*leimu)->cnt-1; i++ ) {
        (*leimu)->own[i] = (*leimu)->own[i+1];
    }
    ((*leimu)->kinds)--;
    return true;

}
void possession()
{
    int i;
    float amount = 0.00;   //总额
    for ( i=0; i<leimu.kinds; i++) {  //判断拥有哪些物品
        if( leimu.own[i].market_value > 0 ) {
            gotoxy(60,1+i);
            printf("你有%d件%s，单价为%.2f，总价值为%.2f元；\n", leimu.own[i].quantity, leimu.own[i].name, leimu.own[i].market_value, leimu.own[i].quantity*leimu.own[i].market_value);
            amount += leimu.own[i].market_value * leimu.own[i].quantity;
        }
    }
    if( amount == 0 ) {
        gotoxy(60,1);
        printf("你的仓库为空。\n");
    }
    gotoxy(60,12);
    printf("你的余额为%.2f\n", *pMoney);
}
void gameOver()
{
    if( *pMoney>=10000000 ) {    //一千万
        printf("%s，你现在一共有%.2f元！漂泊结束！\n", leimu.name, *pMoney);
        getch();
        printf("\n");
        printf("你腰缠万贯富甲一方，风风火火回家族了，你的父亲非常高兴。\n");
        getch();
        printf("\n");
        printf("族里看重你的能力，把你提拔为新一任的族长，多年后，在你的带领下家族威震八方~~~\n");
    } else if ( *pMoney>=1000000) { //一百万
        printf("%s，你现在一共有%.2f元！漂泊结束！\n", leimu.name, *pMoney);
        getch();
        printf("\n");
        printf("你身穿西服脚踏皮革，风风火火回家族了，你的父亲很高兴。\n");
        getch();
        printf("\n");
        printf("族里看重你的能力，把你提拔为家族的财务主管，多年后，家族名声显赫~~~\n");
    } else if ( *pMoney>=500000) {  //五十万
        printf("%s，你现在一共有%.2f元！漂泊结束！\n", leimu.name, *pMoney);
        getch();
        printf("\n");
        printf("你达成目标一身轻，开开心心回家族了，你的父亲很满意。\n");
        getch();
        printf("\n");
        printf("家族因为你带来的资金，重新度过了又一轮的危机~~~\n");
    } else if ( *pMoney>=0) {
        printf("%s，你现在一共有%.2f元！漂泊结束！\n", leimu.name, *pMoney);
        getch();
        printf("\n");
        printf("你没完成目标，悄悄地回家族了，你的父亲很生气。\n");
        getch();
        printf("\n");
        printf("家门不幸，家门不幸啊~~~\n");
        getch();
        printf("\n");
        printf("为了渡过这次经济危机，父亲只能指派你去和隔壁家族的翠花通婚~~~\n");
        getch();
        printf("\n");
        printf("不，不要啊~~~\n");
        printf("\n");
    }
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




