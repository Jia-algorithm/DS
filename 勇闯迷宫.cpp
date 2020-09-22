#include "iostream"
using namespace std;
struct offsets//前进方向的偏移
{
	int x_move;//x方向的移动
	int y_move;//y方向的移动
};

static char Maze[20][20];//迷宫最大为20*20
static int ox,oy;//出口坐标

void build_maze(int a,int b)//建立迷宫
{
	int i,j;//第i列,第j行
	for(i=0;i<=a;i++)//循环输入迷宫每一坐标,#为墙壁,0为通路
	{
		for(j=0;j<=b;j++)
			cin>>Maze[i][j];
	}
}

struct coordinate//坐标结构,用于path类数组
{
	int x;
	int y;
};

class path//储存道路
{
private:
	coordinate p[100];//数组结构储存坐标
	int top;//栈顶指针
public:
	path() { top = -1; }//构造函数,默认top为-1
	~path(){}//析构函数
	bool push(int, int);
	bool pop(int&, int&);
};
bool path::push(int a, int b)//入栈
{
	if (top >= 99)//若栈已满返回0
		return 0;
	top ++;//栈不满,栈顶指针+1
	p[top].x = a;//输入横坐标
	p[top].y = b;//输入纵坐标
	return 1;
}
bool path::pop(int &a, int &b)//出栈
{
	if (top == -1)//若栈已空返回0
		return 0;
	a=p[top].x;//输出横坐标
	b=p[top].y;//输出纵坐标
	top--;//栈顶指针-1
	return 1;
}
path pa;//全局变量pa

bool seek_path(int x,int y)//寻路函数
{
	offsets move[4] = { {0,-1},{-1,0},{0,1},{1,0} };
	//定义方向,0：上；1：左；2：下；3：右；
	if(x==ox&&y==oy)//当坐标为出口,返回1
	{return 1;}
	int i,sx,sy;//i用于记录试探到第几个方向,sx和sy为对应方向下一坐标
	for(i=0;i<4;i++)
	{
		sx=x+move[i].x_move;
		sy=y+move[i].y_move;
		if(Maze[sx][sy]=='0')//若下一位置为0,继续寻路
		{
			Maze[sx][sy]='1';//标记1,已到达过此位置
			if(seek_path(sx,sy))//递归继续试探
			{
				if (!pa.push(sx, sy))//到达终点,坐标入栈
					return 0;//坐标入队列
				Maze[sx][sy]='*';//更改当前位置为表示路径的*
				return 1;
			}
		}
	}
	return 0;//寻路不成功返回0
}

void print_maze(int a, int b)//打印迷宫
{
	int i, j;//第i行第j列
	cout << ' ' << '\t';
	for (j = 0;j <= b; j++)//先输出表头
		cout << "第" << j << "列" << '\t';
	cout << endl;
	for (i = 0; i <= a; i++)//逐行输出
	{
		cout<< "第" << i << "行" << '\t';
		for (j = 0; j <= b; j++)
		{
			if (Maze[i][j] == '1')//将标记为1而不是最终路径的1改回0输出
				cout << '0'<<'\t';
			else
				cout << Maze[i][j] << '\t';
		}
		cout << endl;
	}
}

void print_path(path pa)//输出路径
{
	int x, y;
	while(pa.pop(x,y))//当退栈成功
		cout << "--->(" << x << "," << y << ")";//输出从起点下一位置开始的坐标
	cout << endl;
}

int main()
{
	int a,b;
	cout<<"输入迷宫行数："<<endl;
	cin>>a;
	cout<<"输入迷宫列数："<<endl;
	cin>>b;
	cout << "输入迷宫:" << endl;
	build_maze(a,b);
	int x,y;
	cout<<"输入入口坐标x、y："<<endl;
	cin>>x>>y;
	Maze[x][y] = '*';//将起点标记为路径*
	cout<<"输入出口坐标x、y："<<endl;
	cin >> ox >> oy;
	if (seek_path(x, y))//若寻路成功
	{
		cout << "迷宫地图："<<endl;//打印地图
		print_maze(a, b);
		cout <<"迷宫路径： "<<endl//打印路径
			<<"(" << x << "," << y << ")";//先打印出起点
		print_path(pa);
	}
	else
		cout << "道路不存在！";//寻路不成功输出无路径提示
	system("pause");
	return 0;
}

