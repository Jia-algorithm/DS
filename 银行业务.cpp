#include "iostream"
using namespace std;

struct Node//链表结点
{
	int order;//顾客序号
	Node *next;//指向下一结点
};

class List//链表类
{
private:
	Node *head;//头结点
	Node *tail;//尾结点
	Node *current;//当前指针
	int number;//结点总数
	
public:
	List();//构造函数创建空链表
	~List(){}
	int num();//输出结点总数
	void add(int);//添加新结点
	void clear();//清除所有结点
	void next();//指针current后移，若current已到达tail返回0
	void print_cur();//打印指针current所指向的结点数值
};
bool input_order(List &A,List &B,int N);

int main()
{
	int N;
	cin>>N;
	getchar();
	while(N<=0||N>1000)
		{fflush(stdin);cout<<"请重新输入小于等于1000的正整数N";cin>>N;getchar();}
	bool input=0;
	List A,B;
	while(!input)
		input=input_order(A,B,N);
	int i;//计数器记录总共输出了多少
	if(!A.num())//若A空,直接输出B
	{
		for(i=1;1<N;i++)
		{
			B.next();//指针后移
			B.print_cur();//打印
			cout<<" ";//输出空格
		}
		B.next();//最后一项单独输出,以确保结尾没有多余空格
		B.print_cur();
	}
	else//A不为空
	{
		int flagA=1,flagB=0;//记录A和B分别输出数目
		A.next();//current指向A中第一个节点
		A.print_cur();//先输出首节点，以使得后面空格和序号匹配
		if(N>1)
		{
			bool cir=0;//判断循环是否已经进行过，首次循环A只输出一个结点
			while((flagA<A.num())||(flagB<B.num()))//若A或B未输出完,循环进行
			{
				if(flagA<A.num())//若A未输出完,输出下一项A
				{
					cout<<" ";
					A.next();
					A.print_cur();
					flagA++;//A计数器+1
				}
				if(cir&&flagA<A.num())//并非首循环,输出本次循环第二项A
				{
					cout<<" ";
					A.next();
					A.print_cur();
					flagA++;//A计数器+1
				}
				if(flagB<B.num())//B在A后输出,若B未输出完,输出下一项
				{
					cout<<" ";
					B.next();
					B.print_cur();
					flagB++;//B计数器+1
				}
				cir=1;//第一次循环已进行过
			}
		}
	}
	system("pause");
	return 0;
}
List::List()//创建空链表
{
	number=0;
	head=new Node;
	tail=head;
	tail->next=NULL;
	current=head;
}
void List::add(int n)//以序号为参数添加新结点
{
	Node *newnode=new Node;
	newnode->order=n;
	tail->next=newnode;
	tail=newnode;
	tail->next=NULL;
	number++;//结点总数+1
}
void List::next()//将current指针后移一个结点
{
	current=current->next;
}
void List::print_cur()//打印数据
{
	cout<<current->order;
}
int List::num()
{
	return number;
}
void List::clear()//清空类
{
	if(number!=0)
	{
	number=0;//将结点总数清零
	next();
	Node *p=current;
	while(current!=tail)
	{
		next();
		delete p;
		p=current;
	}
	delete tail;
	tail=head;
	current=head;
	}
}

bool input_order(List &A,List &B,int N)
{
	while(A.num()+B.num()<N)//当总人数少于N继续输入
	{
		int n;
		cin>>n;
		getchar();
		while(n<=0)
		{
			fflush(stdin);//若输入不满足要求,清空缓冲区重新输入
			cout<<"序号需为正整数，请重新输入";
			A.clear();B.clear();//将已输入数据清除
			return 0;
		}//返回未成功输入
		if(n%2)//判断输入编号是否为奇数
			A.add(n);//奇数添加到A
		else
			B.add(n);//偶数添加到B
	}
	fflush(stdin);//清空缓冲区
    return 1;//输入成功
}