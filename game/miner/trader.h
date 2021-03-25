#ifndef _NODE_H_
#define _NODE_H_

typedef struct item      //商品信息
{
    int id;              //商品编号
    char name[100];      //名称
    float value;         //价值
    float value_up;      //价值增长潜能
    float market_value;  //市场价值
    int quantity;        //数量
} Item;
typedef struct player
{
    char name[50];        //保存人物姓名
    float money;          //保存人物金额
    Item own[10];         //你目前拥有的商品
    int len;              //仓库最大容量（拥有商品总数）
    int cnt;              //货物所占容量
    int kinds;            //多少种货物
} Player;
typedef struct arr        //可能用到的结构体
{
    int a[10];
    int cnt;
    int len;
} Arr;

Player leimu = {"Default", 2000.00, {}, 100, 0, 0};
float *pMoney = &leimu.money;      //定义金钱指针
int gameDay = 41;                  //游戏周期，实际40
int * pDay = &gameDay;

void welcome();                 //欢迎界面
void game();                    //游戏主体
void store(Arr * arr);          //商店界面
void gameOver();                //结束界面
void possession();              //玩家拥有物
void gotoxy(int x, int y);      //定位
int transaction(Arr * arr);              //交易
void selectItem(Arr * arr);             //随机抽取随机个数的商品的id
bool locality();                //地点
bool addPos(Player * leimu, Item *goods, int num);              //购买商品
bool sellPos(Player * leimu, Item *goods, int num, int ownId);  //销售商品
bool deleteOwnItem(Player ** leimu, int index);                 //注销商品
float marketPrice(Item goods);                                  //随机变动的商品价格
void delete_same_value(Arr * arr);      //删除重复值
void one(Item * goods);                 //给传入的单个商品赋值市场价值
void create_all_market_price();         //给所有商品赋值市场价值

const int maxId = 18;    //商品最大编号
Item goods[maxId] = {
    /*编号|商品名字|价格|价格增长潜能|市场价值|库存*/
    //图书类
    {1, "离散数学（二手）", 10.00, 150, 0, 50,},
    {2, "西方经济学（二手）", 10.00, 200, 0, 50},
    {3, "论修养之道", 20.00, 180, 0, 30},
    {4, "知音漫客", 10.00, 200, 0, 50},
    {5, "三体（共三册）", 100.00, 700, 0, 100},
    //生活用品类
    {6, "清风手冲纸", 5.00, 80, 0, 80},
    {7, "高档化妆品", 100.00, 1000, 0, 80},
    {8, "青花瓷碗", 150.00, 1200, 0, 50},
    //手办类
    {9, "雷姆手办（和服）", 300.00, 2000, 0, 100},
    {10, "Saber邪神手办", 700.00, 2000, 0, 50},
    {11, "初音未来（深海）", 200.00, 800, 0, 100},
    {12, "泳装白", 100.00, 600, 0, 100},
    {13, "萌神史莱姆", 300.00, 800, 0, 200},
    //奢饰品类
    {14, "小米pro10", 1000.00, 8000, 0, 100},
    {15, "冰箱", 2000.00, 10000, 0, 100},
    {16, "2080电脑", 4000.00, 20000, 0, 100},
    {17, "黄金", 20000.00, 150000, 0, 80},
    {18, "汽车", 50000.00, 400000, 0, 50},
    
};

#endif