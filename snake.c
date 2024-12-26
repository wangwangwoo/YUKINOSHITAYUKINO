#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<time.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//链表节点声明 
typedef struct _snake_t
{
	int x;
	int y;
	struct _snake_t *next;
}snake_t;
typedef struct inf{
    char name[30];
    int score;
}inf;

typedef struct list{
    inf data;
    struct list* next;
}list;

list*L;
FILE*fp;
int number=0;
int score = 0;
int add = 1;
int direction = RIGHT;
int sleepTime = 350;
int endStatus = 0;


snake_t *head = NULL;
snake_t *foodNode = NULL;
snake_t *save = NULL;

//函数声明 
int Setcolor(int c); 
int printsnake(void);
int WelcomeGame(void);
int aboutGame(void);
int RunningGame(void);
int printMap(void);
int showScoreTips(void);
int readFile(void);
int initSnake(void);
int randFood(void);
int moveSnake(void);
int moveKeyControl(void);
int speedUp(void);
int speedDown(void);
int isHitWall(void);
int isHitSelf(void);
void printFailed(void);
int endGame(void);
int writeFile(int score);
int desSnake(void);


//设置颜色 
int Setcolor(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}
//定位坐标 
int Setcursor(int x,int y){

	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}
//欢迎界面蛇的绘画 
int printsnake(void)
{
	//清屏 
	system("cls");
	

	Setcursor(35,1);
	Setcolor(6);
	printf("/^\\/^\\");
	
	Setcursor(34,2);
	printf("|__|  0|");
	
	Setcursor(33,2);
	Setcolor(2);
	printf("_");
	
	Setcursor(25,3);
	Setcolor(12);
	printf("\\/");
	
	Setcursor(31,3);
	Setcolor(2);
	printf("/");
	
	Setcursor(37,3);
	Setcolor(6);
	printf("\\_/");
	
	Setcursor(41,3);
	Setcolor(10);
	printf("\\");
	
	Setcursor(26,4);
	Setcolor(12);
	printf("\\______");
	
	Setcursor(32,4);
	printf("___________/");
	
	Setcursor(31,4);
	Setcolor(2);
	printf("|");
	
	Setcursor(43,4);
	Setcolor(10);
	printf("\\");
	
	Setcursor(32,5);
	Setcolor(12);
	printf("\\________");
	
	Setcursor(44,5);
	Setcolor(10);
	printf("\\");
	
	Setcursor(39,6);
	Setcolor(12);
	printf("/       /                    \\");
	
	Setcursor(38,7);
	printf("/       /                     \\");
	
	Setcursor(37,8);
	printf("/       /                      \\ \\");
	
	Setcursor(35,9);
	printf("/      /                         \\ \\");
	
	Setcursor(34,10);
	printf("/      /                           \\ \\");
	
	Setcursor(33,11);
	printf("/      /              _===_          \\ \\");
	
	Setcursor(32,12);
	printf("/      /           _=-     -=_         |  |");
	
	Setcursor(31,13);
	printf("(      (         _=-    _==_   -=_    _/    |");
	
	Setcursor(32,14);
	printf("\\     -=____=-    _-=   =-_    =-_-=      /");
	
	Setcursor(33,15);
	printf("=-_           _-=         =-_        _-=");
	
	Setcursor(35,16);
	printf("=--________-=               =-____-=");
	
	return 0;

}
//欢迎界面 
int WelcomeGame(void)
{
	printsnake();
	Setcolor(11);
	Setcursor(45,18);
	printf("贪吃蛇");/*printf代替*/
	Setcolor(14);
	int i,j;
	int n=0;
	for(i = 20; i <= 26; i++)
	{
		for(j = 27; j <= 74; j++)
		{
			if(i == 20 || i == 26)
			{
				Setcursor(j,i);
				printf("-");
			}
			else if(j == 27 || j==74)
			{
				Setcursor(j,i);
				printf("|");
			}
		}
	}
	Setcolor(13);
	

	Setcursor(35,22);
	printf("1, 游戏开始");
	
	Setcursor(55,22);
	printf("2, 游戏说明");
	
	Setcursor(35,24);
	printf("3, 退出游戏");
	
	Setcursor(55,24);
	printf("4, 成绩查询");
	
	Setcolor(15);
	Setcursor(27,27);
	printf("请选择:1,2,3,4:  ");
	
	scanf("%d",&n);
	getchar();
	return n;

}
//游戏说明 
int aboutGame(void)
{
	int i,j;
	system("cls");
	Setcolor(11);
	for(i=6;i<=22;i++)
	{
	for(j=20;j<=90;j++)
		{
			if(i==6||i==22)
			{
				Setcursor(j,i);
				printf("=");
				

			}
			else if(j==20||j==90)
			{
				Setcursor(j,i);
				printf("|");
			}
	
		}
	}
	
	Setcolor(3);
	Setcursor(30,8);
	printf("1,不能撞到墙和你自己");
	
	Setcolor(5);
	Setcursor(30,11);
	printf("2,按Shift加速,按Ctrl减速");
	
	Setcolor(11);
	Setcursor(30,14);
	printf("3,按下空格键暂停游戏或继续游戏");
	
	Setcolor(13);
	Setcursor(30,17);
	printf("4,用方向键控制移动方向");
	
	Setcolor(14);
	Setcursor(30,20);
	printf("5,按下ESC退出游戏");
	
	Setcolor(12);
	Setcursor(20,24);
	printf("按下Enter返回");
	
	return 0;

}
//成绩查询 
int aboutgrade()
{
	int i,j;
	system("cls");
	Setcolor(11);
	for(i=6;i<=22;i++)
	{
	for(j=20;j<=90;j++)
		{
			if(i==6||i==22)
			{
				Setcursor(j,i);
				printf("=");
				
			}
			else if(j==20||j==90)
			{
				Setcursor(j,i);
				printf("|");
			}

		}
	}
	Setcursor(38,5);
	printf("查询历史成绩（分数按照从高到低排序）\n");
	Setcursor(21,7);
	return 0;	
}
/*初始化并读取已有的记录,返回值是用来检测是否成功*/
int innert(list*L){  

inf p;
list*new_node,*last=NULL;
L=(list*)malloc(sizeof(list));
L->next=NULL;
last=L;


fp=fopen("rank.txt","r");
if(fp==NULL){
    printf("未能正常打开文件！\n");
    return 0;
}
else{
    fgetc(fp);
    if(!feof(fp)){
        while(!feof(fp)){
            fseek(fp,-1,SEEK_CUR); 
            fscanf(fp,"%s",p.name);
            fscanf(fp,"\t%d\n",&p.score);
            new_node=(list*)malloc(sizeof(list));
            new_node->data=p;
            last->next=new_node;
            last=new_node;
            number++;
            fgetc(fp);

            }
    
        }
    }

fclose(fp);
last->next=NULL;
last=L;
printf("成绩记录链表已建立，共有%d条记录。\n",number);
    return 1;
}
/*手动加入新纪录*/
void add_newscore(list*L){
   fp=fopen("rank.txt","w+");
    list*p=L,*pre=NULL;
    inf new_inf;
	while(p!=NULL){
        p=p->next;
    }
    p=(list*)malloc(sizeof(list));
    Setcursor(38,20);
    printf("请输入该次挑战者的名称:");
    scanf("%s",new_inf.name);
    Setcursor(38,21);
    printf("请输入您所得的分数:");
    scanf("%d",&new_inf.score);
    
    pre=p;
    pre->next=NULL;
    pre->data=new_inf;
    number++;
    p=L;
    
    
	while(p!=NULL)
	{
        fprintf(fp,"%s\t",p->data.name);
        fprintf(fp,"%d\n",p->data.score);
        p=p->next;
    }
    fclose(fp);
    
    
}
/*这是寻找记录但我发现最开始好像把所有记录都打出来了，不过好像也没关系，就当省略自己看来找的时间*/
list* search(list*L,char*name){/*这个地方偷个懒没写输入名字的函数就用形参*/
	list*p=L;
    while(p!=NULL){
        if(!strcmp(p->data.name,name)){
            printf("挑战者%s的得分为%d",name,p->data.score);
            return p;
        }
        p=p->next;
    }
    return NULL;
}
/*冒泡排序*/
void bubble_sort(list*L) {
    list *p;
    inf temp;
	fp=fopen("rank.txt","w+");
    int n = number;
    int i, j;
    
    if (L == NULL || L->next == NULL)
    Setcursor(21,9);
        printf("当前链表中没有记录\n");
    for (j = 1; j < n; ++j) {
        p = L->next;
        for (i = 0; i < n - j; ++i) {
            if (p->data.score > p->next->data.score) {
                 temp=p->data;
                p->data=p->next->data;
                p->next->data=temp;
            }
            p = p->next;
        }
    }
    	p=L;
		while(p!=NULL){
        
		fprintf(fp,"%s\t",p->data.name);
        fprintf(fp,"%d\n",p->data.score);
        p=p->next;
    }
   	p=L;
    while(p!=NULL){
	Setcursor(21,8);
    printf("挑战者%s的得分为%d\n",p->data.name,p->data.score);
	p=p->next;
}
	fclose(fp);

    
}

//划定边框（暂时无用）
int RunningGame(void) 
{
	system("cls");
	Setcolor(12);
	int i,j;
	for(i=0;i<=28;i++)
	{
	for(j=0;j<=80;j++)
		{
			if(i==0||i==28)
			{
				Setcursor(j,i);
				printf("-");
				

			}
			else if(j==0||j==80)
			{
				Setcursor(j,i);
				printf("|");
			}
	
		}
	}
	return 0;

}
//代替上个函数   绘制地图 
int printMap(void)
{
	int i=0;
	int j=0;
	system("cls");
	

	for(i=0;i<=26;i++)
	{
		for(j=0;j<=56;j=j+2)
		{
			Setcursor(j,i);
			if(0==i || 26==i || 0==j || 56==j)
			{
				Setcolor(12);
				printf("□");
			}
			else
			{
				Setcolor(7);
				printf("■");
			}
		}
	}
	//四角设定 
	Setcolor(11);
		Setcursor(0,0);
		printf("■");
		
		Setcursor(56,0);
		printf("■");
		
		Setcursor(0,26);
		printf("■");
		
		Setcursor(56,26);
		printf("■");

}
//游戏内注释 
int showScoreTips(void)
{	
	int highScore=0;
	

	highScore=readFile();
	
	Setcolor(3);
	Setcursor(64,4);
	printf("**最高得分记录: %d",highScore);
	
	Setcolor(7); 
	Setcursor(64,8);
	printf("得分: %d",score);
	
	Setcolor(12);
	Setcursor(72,11);
	printf("温 馨 提 示");
	
	Setcolor(13);
	Setcursor(64,14);
	printf("*吃掉每个食物得分：%d分",add);
	 
	Setcursor(64,16);
	printf("*不能撞到墙壁，不能咬到自己");
	
	Setcursor(64,18);
	printf("*Shift加速前进，Ctrl减速前进");
	
	Setcursor(64,20);
	printf("*使用空格键暂停游戏和继续游戏");
	
	Setcursor(64,22);
	printf("*使用↑↓←→控制前进的方向");
	
	Setcursor(64,24);
	printf("*按下ESC键退出游戏"); 
	
	Setcursor(64,26);
    printf("请在游戏结束后输入玩家名和成绩以进行排名");
}
//读取文件（最高分） 
int readFile()
{
	int ret=-1;
	FILE *fp=NULL;
	char buf[32];
	

	fp=fopen("save.txt","r");
	if(NULL==fp)
	{
		printf("fopen failed.\n");
		return 0;
	}
	//清零方式 
	memset(buf,0,sizeof(buf));
	ret=fread(buf,sizeof(char),sizeof(buf),fp);
	if(ret<=0)
	{
		printf("fread failed.\n");
		return 0;
	}
	
	fclose(fp);
	
	return atoi(buf);

}
//插入文件（最高分） 
int writeFile(int score)
{
	FILE *fp=NULL;
	

	fp=fopen("save.txt","w+");
	if(fp==NULL)
	{
		printf("File opening failed.\n");
		return -1;
	}
	
	fprintf(fp,"%d",score);
	
	fclose(fp);
	
	return 0;

}
//蛇的初始化 
int initSnake(void)
{
	int i=0;
	

	snake_t *hed =NULL;
	snake_t *tmp =NULL;
	
	for(i=0;i<4;i++)
	{
		hed = (snake_t*)malloc(sizeof(snake_t));
		if(NULL==hed)
		{
			printf("malloc initSnake failed.\n");
			return -1;
		}
		memset(hed,0,sizeof(snake_t));
		//蛇的初始位置确定 
		hed->x=24+(i*2);
		hed->y=5;
		
		hed->next=head;
		head=hed;
	}
	
	tmp=head;
	
	while(NULL != tmp)
	{
		Setcolor(14);
		Setcursor(tmp->x,tmp->y);
		//画蛇 
		if(head==tmp)
		{
			printf("O");
		}
		else
		{
		printf("o");
		}
		tmp = tmp->next;
	}

}
//随机生成食物 
int randFood(void)
{
	snake_t *tmp=NULL;
	foodNode=(snake_t*)malloc(sizeof(snake_t));
	if(NULL==foodNode)
	{
		Setcursor(1,28);
		printf("malloc failed.\n");
		return -1;
	}
	memset(foodNode,0,sizeof(snake_t));
	

	while(1)
	{


	
		while(1)
		{
			foodNode->x=rand() % 53 + 2 ;
			
			if(0==foodNode->x % 2)
			{
				break;
			}
	 	}
			foodNode->y=rand() % 25 + 1 ;
		
			tmp=head;
			while(NULL!=tmp)
			{
				if((foodNode->x==tmp->x) && (foodNode->y==tmp->y))
				{
					break;
				}
				tmp=tmp->next;
			}
			if(NULL==tmp)
			{
				Setcursor(foodNode->x,foodNode->y);
				Setcolor(13);
				printf("@");
				break;
			}
			else
			{
				continue;
			}
	}

}
//蛇的移动 
int moveSnake(void)
{
	snake_t *hed=NULL;
	snake_t *tmp=NULL;
	

	hed=(snake_t*)malloc(sizeof(snake_t));
	if(NULL==hed)
	{
		printf("malloc failed.\n");
		return -1;
	}
	memset(hed,0,sizeof(snake_t));
	//蛇的方向 
	if(UP==direction)
	{
		hed->x=head->x;
		hed->y=head->y-1;
	}
	if(DOWN==direction)
	{
		hed->x=head->x;
		hed->y=head->y+1;
	}
	if(LEFT==direction)
	{
		hed->x=head->x-2;
		hed->y=head->y;
	}
	if(RIGHT==direction)
	{
		hed->x=head->x+2;
		hed->y=head->y;
	}
	
	hed->next=head;
	head=hed;
	
	tmp=head;
	Setcolor(14);
	
	if((hed->x==foodNode->x) && (hed->y==foodNode->y))
	{
		while(NULL!=tmp)
		{
			Setcursor(tmp->x,tmp->y);
			if(head==tmp)
			{
				printf("O");
			}
			else
			{
				printf("o");
			}
			
			tmp=tmp->next;
		}
		//吃食物加分 
		score=score+add;
		
		randFood();
	}
	else
	{
		while(NULL!=tmp->next)
		{
			save=tmp->next;
			Setcursor(tmp->x,tmp->y);
			if(head==tmp)
			{
				printf("O");
			}
			else
			{
				printf("o");
			}
			save=tmp;
			tmp=tmp->next;
		}
		//将蛇尾替换为 ■
		Setcursor(tmp->x,tmp->y);
		Setcolor(7);
		printf("■");
		
		save->next=NULL;
		
		free(tmp);
	}

}
//按键操作 
int moveKeyControl(void)
{		
	//初始方向向右 
	direction=RIGHT;
	while(1)
	{
		showScoreTips();
		

		//读入按键函数 ：GetAsyncKeyState(VK_  ） 
		if(GetAsyncKeyState(VK_UP) && direction != DOWN)
		{
			direction=UP;
		}
		if(GetAsyncKeyState(VK_DOWN) && direction != UP)
		{
			direction=DOWN;
		}
		if(GetAsyncKeyState(VK_LEFT) && direction != RIGHT)
		{
			direction=LEFT;
		}
		if(GetAsyncKeyState(VK_RIGHT) && direction != LEFT)
		{
			direction=RIGHT;
		}
		
		if(GetAsyncKeyState(VK_SPACE))
		{
			while(1)
			{
				Sleep(300);
				if(GetAsyncKeyState(VK_SPACE))
				{
					break;
				}
			}
		}
		
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			endStatus=3;
			endGame();
			break;
		}
		//加速 
		if(GetAsyncKeyState(VK_SHIFT))
		{
			speedUp();
		}
		//减速 
		if(GetAsyncKeyState(VK_CONTROL))
		{
			speedDown();
		}
		
		Sleep(sleepTime);
		
		moveSnake();
		
		//撞墙 
		if(isHitWall())
		{
			endStatus = 1;
			endGame();
			break;
		}
		//咬到自己 
		if(isHitSelf())
		{
			endStatus = 2;
			endGame();
			break;
		}
	}

}
//加速 （上限为50ms） 
int speedUp(void)
{
	if(sleepTime>50)
	{
		sleepTime=sleepTime-20;
		add=add+2;
	}
}
//减速 （下限为350ms） 
int speedDown(void)
{
	if(sleepTime<350)
	{
		sleepTime=sleepTime+20;
		add=add-2;
	}
	if(add<=0)
	{
		add=1;
	}
}
//判断是否撞墙 
int isHitWall(void)
{	
	int q;
	if(head->x==0 || head->x==56|| head->y==0 || head->y==26)
	{
		q=1;
	}
	else 
	{
		q=0;
	}
	return q;
}
//判断是否咬到自己 
int isHitSelf(void)
{
	snake_t *tmp = NULL;
	tmp=head->next;
	

	while(NULL!=tmp)
	{
		if((head->x==tmp->x)&&(head->y==tmp->y))
		{
			return 1;
		}
		
		else tmp=tmp->next;
	}
	return 0;

}
//失败界面 
void printFailed(void)
{	
	int i=0;
	system("cls");
	Setcolor(15);
	Setcursor(44,3);
	printf("游 戏 结 束 ！");
	

	Setcolor(11);
	Setcursor(17,5);
	printf("+----------------------------------------------------------------+");
	
	Setcursor(17,20);
	printf("+----------------------------------------------------------------+");
	
	for(i=6;i<20;i++)
	{
		Setcursor(17,i);
		printf("|");
		
		Setcursor(82,i);
		printf("|");
	}

}
//结束游戏方式 
int endGame(void)
{
	int highScore=0;
	int choice=0;
	

	while(1)
	{
	
		printFailed();
		switch(endStatus)
		{
			case 1://撞墙 
				{
					Setcursor(38,9);
					Setcolor(14);
					printf("小蛇撞到墙哩！");
					break;
				}
			case 2://咬到自己 
				{
					Setcursor(38,9);
					Setcolor(14);
					printf("不能贪吃到吃自己口牙！");
					break;
				}
			case 3://ESC退出 
				{
					Setcursor(38,9);
					Setcolor(14);
					printf("你怎么退了？！");
					break;
				}
			default:
				;
		}
		Setcolor(13);
		Setcursor(38,12);
		printf("得分: %d",score);
		
		Setcolor(10);
		highScore=readFile();
		if(score>highScore)
		{
			Setcursor(38,16);
			printf("你破了记录耶！");
			writeFile(score);
		}
		else
		{
			Setcursor(38,16);
			printf("你不够努力，还差 %d 到最高分!好菜QAQ",highScore-score);
		}
	    innert(L);  
		add_newscore(L);
		Setcursor(25,23);
		Setcolor(13);
		printf("再玩一局吧! : 1");
		
		Setcursor(53,23);
		printf("残忍拒绝 : 2");
		
		Setcursor(40,25);
		Setcolor(15);
		printf("做出你的选择 : ");
		
		scanf("%d",&choice);
		getchar();
		
		if(choice==1)
		{
			score=0;
			sleepTime=350;
			add=1;
			desSnake();
			break;
		}
		else if(choice==2)
		{
			exit(0);
		}
		else
		{
			Setcursor(30,27);
			Setcolor(12);
			printf("你输的啥！？再输一次！");
			getchar();
		}
	}
	
	return 0;

}
//销毁蛇 
int desSnake(void)
{
	snake_t *tmp=NULL;
	snake_t *save=NULL;
	

	tmp=head;
	while(tmp!=NULL)
	{
		save=tmp->next;
		free(tmp);
		tmp=save;
	}
	head=NULL;
	
	return 0;

}
//主函数 
int main()
{
	int choice=0;
	system("mode con cols=100 lines=30");
	srand(time(NULL));
	Setcolor(13);
	Setcursor(44,3);
	printf("游戏说明");
	int i,j;
	char name[1024];
	list*p;

	while(1)
	{
		choice=WelcomeGame();
		
		switch(choice)
		{
			case 1:
			//打印地图 
			printMap();	
			//展示提示 
			showScoreTips();
			//初始化蛇 
			initSnake();
			//随机生成食物 
			randFood();
			//按键操作 
			moveKeyControl();
			break;
			
			case 2:
			//关于游戏 
			aboutGame();
			break;
			
			case 3:
			//退出 
			exit(0);
			break;
			
			case 4:
			//成绩查询
			aboutgrade();
			innert(L);
			bubble_sort(L);
			printf("请输入挑战者名称：");
			scanf("%s",name);
			p=search (L,name);
			if(p!=NULL){
				printf("挑战者%s的得分为%d.",name,p->data.score);
			}
			else{
				printf("输入的名字错误，请重新输入！") ;
			}
			break; 
			
			default:
		    Setcolor(12);
		    Setcursor(45,28);
		    
			printf("不合法，请重新选择!");
		}
		
		getchar();
	}
	
	return 0;

}
