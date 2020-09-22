#include <iostream>
using namespace std;
#include <string>
#define Max 1000000

struct edge
{
	int dest=-1;//another node
	double cost = Max;//cost of the edge
	edge* link=NULL;//next edge
};
struct vertex
{
	string name="null";//name of the city
	edge* adj=NULL;//head link of edges
};
class graph
{
private:
	vertex *NodeTable;//head link
	int num;//quantity of cities
public:
	graph(int);//using the quantity of cities to build the graph
	~graph();
	int get_pos(const string);//find the position in the node table
	double get_cost(int&, int&);//get the cost between two nodes
	bool insert_edge(int&, int&, double&);//insert an edge
	int get_first(int&);//get the first neighbor of the node
	int get_next(int&, int&);//get the next neighbor of a neighbor of the node
	int get_num() { return num; }//get the quantity of cities
	void output(int n) { cout << NodeTable[n].name; }//print the name of specified node
	void build();//build the edges
};
struct ednode
{
	int head=-1;//inside the tree
	int tail=-1;//outside the tree
	ednode* link=NULL;
	double cost=Max;//cost of the edge
};
class pile
{
private:
	ednode* front;//the front pointer,doesn't include data
	ednode* rear;//points to the last node
public:
	pile();//constructor
	~pile();//destructor
	bool insert(ednode*);//insert a new node in an increasing order
	bool pop(ednode*&);//if empty,return 0,else remove the smallest node
	bool is_empty() { return front == rear; }//to judge whether the pile is empty
	void print(graph &G);//print all the node with the node names in graph G
	void clear();
};

pile::pile()
{
	front = new ednode;
	rear = front;
}
pile::~pile()
{
	ednode* p = front;
	while (front != rear)
	{
		p = front->link;
		delete front;
		front = p;
	}
	delete rear;
}
void pile::clear()
{
	ednode* p = front;
	while (front != rear)
	{
		p = front->link;
		delete front;
		front = p;
	}
}
bool pile::insert(ednode* ed)
{
	if (front == rear)//if the pile is blank, insert at the front
	{
		front->link = ed;
		rear = ed;
		rear->link = NULL;
		return 1;
	}
	ednode *after=front->link,*before=front;
	while (after != NULL&&ed->cost > after->cost)
	{
		after = after->link;
		before = before->link;
	}
	if (after == NULL)
	{
		rear->link = ed;
		rear = ed;
		rear->link = NULL;
		return 1;
	}
	before->link = ed;
	ed->link = after;
	return 1;
}
bool pile::pop(ednode* &ed)
{
	if (front == rear)
		return 0;
	ed = front->link;
	if (ed == rear)
	{
		rear = front;
		return 1;
	}
	front->link = ed->link;
	return 1;
}
void pile::print(graph &G)
{
	ednode* p=front->link;
	while (p != NULL)
	{
		G.output(p->head);
		cout << "-" << '(' << p->cost << ')' << "->";
		G.output(p->tail);
		cout << '\t';
		p = p->link;
	}
}


graph::graph(int n)
{
	num = n;
	NodeTable = new vertex[num];
}
graph::~graph()
{
	for (int i = 0; i < num; i++)
	{
		edge* p = NodeTable[i].adj;
		while (p != NULL)
		{
			edge* q = p->link;
			delete p;
			p = q;
		}
	}
	delete[] NodeTable;
}
int graph::get_pos(const string s)
{
	int n = -1;
	for (int i = 0; i < num; i++)
	{
		if (NodeTable[i].name == s)
		{
			n = i;
			break;
		}
	}
	return n;
}
double graph::get_cost(int& u, int& v)
{
	double c = Max;
	edge* p=NodeTable[u].adj;
	while (p != NULL)
	{
		if (p->dest == v)
		{
			c = p->cost;
			break;
		}
		p = p->link;
	}
	return c;
}
bool graph::insert_edge(int& u, int& v, double& c)
{
	if (u == v || u >= num || v >= num)
		return 0;
	edge* p = new edge{ v,c,NodeTable[u].adj };
	NodeTable[u].adj = p;
	p = new edge{ u,c,NodeTable[v].adj };
	NodeTable[v].adj = p;
	return 1;
}
int graph::get_first(int& dest)
{
	if (dest >= num)
		return -1;
	return NodeTable[dest].adj->dest;
}
int graph::get_next(int& dest, int& current)
{
	if (dest >= num||current>=num)
		return -1;
	edge* p = NodeTable[dest].adj;
	while (p->dest != current && p != NULL)
		p = p->link;
	if (p != NULL && p->link != NULL)
		return p->link->dest;
	return -1;
}
void graph::build()
{
	string s;
	for (int i = 0; i < num; i++)
	{
		cin >> s;
		NodeTable[i].name = s;
	}
}

bool Prim(graph &G,const int u0,pile &MST)//using Prim to build the mininum spanning tree
{
	int n = G.get_num();//quantity of nodes
	pile H;//Auxiliary list containing alternative edges
	bool *Vmst = new bool[n];//auxiliary array,to mark whether a node is in the MST
	for (int i = 0; i < n; i++)
		Vmst[i] = 0;
	Vmst[u0] = 1;//the starting node is inside the tree
	int u=u0,count = 1;//u is the newly inserted node to the MST,count marks the quantity of nodes already in the MST
	do
	{
		int v = G.get_first(u);
		while (v != -1)//put each edge between the unmarked nodes and the current node into H
		{
			if (Vmst[v] == 0)
			{
				ednode* ed = new ednode;
				ed->head = u;
				ed->tail = v;
				ed->cost = G.get_cost(u, v);
				H.insert(ed);
			}
			v = G.get_next(u, v);
		}
		if (H.is_empty() && count < n)
			return 0;
		while (!H.is_empty() && count < n)
		{
			ednode* ed=NULL;
			H.pop(ed);
			if (Vmst[ed->tail] == 0)
			{
				MST.insert(ed);
				Vmst[ed->tail]=1;
				u = ed->tail;
				count++;
				break;
			}
		}
	}
	while (count < n);
	return 1;
}
void start()
{
	cout << "**        �������ģ��ϵͳ          **" << endl;
	cout << "======================================" << endl;
	cout << "**        A---�����������          **" << endl;
	cout << "**        B---��ӵ����ı�          **" << endl;
	cout << "**        C---������С������        **" << endl;
	cout << "**        D---��ʾ��С������        **" << endl;
	cout << "**        E---�˳�����              **" << endl;
	cout << "======================================" << endl << endl;
}

int main()
{
	start();
	char op;
	cout << "��ѡ�������";
	cin >> op;
	while (op != 'A')
	{
		cout << "���ȴ�����㣺";
		cin >> op;
	}
	int n;
	cout << "�����붥��ĸ�����";
	cin >> n;
	while (n <= 1)
	{
		cout << "������������Ϊ2�����������룺" << endl;
		cin >> n;
	}
	graph G(n);
	cout << "�������������������ƣ�"<<endl;
	G.build();
	pile H,MST;
	bool flag=0;//build MST
	cout << endl<<"��ѡ�������";
	while (cin >> op, op != 'E')
	{
		string ustart;
		int u0;
		switch (op)
		{
		case'A':
			cout << "���㽨������ɣ�" << endl;
			break;
		case'B':
			while (1)
			{
				cout << "�������������㼰�ߣ�";
				string su, sv;
				cin >> su >> sv;
				double co;
				cin >> co;
				if (co == 0)
					break;
				int u = G.get_pos(su), v = G.get_pos(sv);
				if (u == -1 || v == -1)
				{
					cout << "�����������" << endl;
					continue;
				}
				G.insert_edge(u, v, co);
			}
			break;
		case'C':
			cout << "��������ʼ���㣺";
			cin >> ustart;
			u0=G.get_pos(ustart);
			if (u0 == -1)
			{
				cout << "���㲻���ڣ�";
				break;
			}
			if (Prim(G, u0, MST))
			{
				cout << "����Prim��С��������" << endl;
				flag = 1;
			}
			else
			{
				cout << "����������������Prim��С������,����ӱߣ�" << endl;
				MST.clear();
			}
			break;
		case'D':
			if (!flag)
			{
				cout << "��������Prim��С��������" << endl;
				break;
			}
			cout << "��С�������Ķ��㼰��Ϊ��" << endl;
			MST.print(G);
			break;
		default:
			cout << "����Ĳ�����" << endl;
			break;
		}
		cout <<endl<< "��ѡ�������";
	}
	return 0;
}