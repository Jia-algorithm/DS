#include "iostream"
using namespace std;
struct offsets//ǰ�������ƫ��
{
	int x_move;//x������ƶ�
	int y_move;//y������ƶ�
};

static char Maze[20][20];//�Թ����Ϊ20*20
static int ox,oy;//��������

void build_maze(int a,int b)//�����Թ�
{
	int i,j;//��i��,��j��
	for(i=0;i<=a;i++)//ѭ�������Թ�ÿһ����,#Ϊǽ��,0Ϊͨ·
	{
		for(j=0;j<=b;j++)
			cin>>Maze[i][j];
	}
}

struct coordinate//����ṹ,����path������
{
	int x;
	int y;
};

class path//�����·
{
private:
	coordinate p[100];//����ṹ��������
	int top;//ջ��ָ��
public:
	path() { top = -1; }//���캯��,Ĭ��topΪ-1
	~path(){}//��������
	bool push(int, int);
	bool pop(int&, int&);
};
bool path::push(int a, int b)//��ջ
{
	if (top >= 99)//��ջ��������0
		return 0;
	top ++;//ջ����,ջ��ָ��+1
	p[top].x = a;//���������
	p[top].y = b;//����������
	return 1;
}
bool path::pop(int &a, int &b)//��ջ
{
	if (top == -1)//��ջ�ѿշ���0
		return 0;
	a=p[top].x;//���������
	b=p[top].y;//���������
	top--;//ջ��ָ��-1
	return 1;
}
path pa;//ȫ�ֱ���pa

bool seek_path(int x,int y)//Ѱ·����
{
	offsets move[4] = { {0,-1},{-1,0},{0,1},{1,0} };
	//���巽��,0���ϣ�1����2���£�3���ң�
	if(x==ox&&y==oy)//������Ϊ����,����1
	{return 1;}
	int i,sx,sy;//i���ڼ�¼��̽���ڼ�������,sx��syΪ��Ӧ������һ����
	for(i=0;i<4;i++)
	{
		sx=x+move[i].x_move;
		sy=y+move[i].y_move;
		if(Maze[sx][sy]=='0')//����һλ��Ϊ0,����Ѱ·
		{
			Maze[sx][sy]='1';//���1,�ѵ������λ��
			if(seek_path(sx,sy))//�ݹ������̽
			{
				if (!pa.push(sx, sy))//�����յ�,������ջ
					return 0;//���������
				Maze[sx][sy]='*';//���ĵ�ǰλ��Ϊ��ʾ·����*
				return 1;
			}
		}
	}
	return 0;//Ѱ·���ɹ�����0
}

void print_maze(int a, int b)//��ӡ�Թ�
{
	int i, j;//��i�е�j��
	cout << ' ' << '\t';
	for (j = 0;j <= b; j++)//�������ͷ
		cout << "��" << j << "��" << '\t';
	cout << endl;
	for (i = 0; i <= a; i++)//�������
	{
		cout<< "��" << i << "��" << '\t';
		for (j = 0; j <= b; j++)
		{
			if (Maze[i][j] == '1')//�����Ϊ1����������·����1�Ļ�0���
				cout << '0'<<'\t';
			else
				cout << Maze[i][j] << '\t';
		}
		cout << endl;
	}
}

void print_path(path pa)//���·��
{
	int x, y;
	while(pa.pop(x,y))//����ջ�ɹ�
		cout << "--->(" << x << "," << y << ")";//����������һλ�ÿ�ʼ������
	cout << endl;
}

int main()
{
	int a,b;
	cout<<"�����Թ�������"<<endl;
	cin>>a;
	cout<<"�����Թ�������"<<endl;
	cin>>b;
	cout << "�����Թ�:" << endl;
	build_maze(a,b);
	int x,y;
	cout<<"�����������x��y��"<<endl;
	cin>>x>>y;
	Maze[x][y] = '*';//�������Ϊ·��*
	cout<<"�����������x��y��"<<endl;
	cin >> ox >> oy;
	if (seek_path(x, y))//��Ѱ·�ɹ�
	{
		cout << "�Թ���ͼ��"<<endl;//��ӡ��ͼ
		print_maze(a, b);
		cout <<"�Թ�·���� "<<endl//��ӡ·��
			<<"(" << x << "," << y << ")";//�ȴ�ӡ�����
		print_path(pa);
	}
	else
		cout << "��·�����ڣ�";//Ѱ·���ɹ������·����ʾ
	system("pause");
	return 0;
}

