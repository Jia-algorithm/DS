#include "iostream"
using namespace std;

struct Node//������
{
	int order;//�˿����
	Node *next;//ָ����һ���
};

class List//������
{
private:
	Node *head;//ͷ���
	Node *tail;//β���
	Node *current;//��ǰָ��
	int number;//�������
	
public:
	List();//���캯������������
	~List(){}
	int num();//����������
	void add(int);//����½��
	void clear();//������н��
	void next();//ָ��current���ƣ���current�ѵ���tail����0
	void print_cur();//��ӡָ��current��ָ��Ľ����ֵ
};
bool input_order(List &A,List &B,int N);

int main()
{
	int N;
	cin>>N;
	getchar();
	while(N<=0||N>1000)
		{fflush(stdin);cout<<"����������С�ڵ���1000��������N";cin>>N;getchar();}
	bool input=0;
	List A,B;
	while(!input)
		input=input_order(A,B,N);
	int i;//��������¼�ܹ�����˶���
	if(!A.num())//��A��,ֱ�����B
	{
		for(i=1;1<N;i++)
		{
			B.next();//ָ�����
			B.print_cur();//��ӡ
			cout<<" ";//����ո�
		}
		B.next();//���һ������,��ȷ����βû�ж���ո�
		B.print_cur();
	}
	else//A��Ϊ��
	{
		int flagA=1,flagB=0;//��¼A��B�ֱ������Ŀ
		A.next();//currentָ��A�е�һ���ڵ�
		A.print_cur();//������׽ڵ㣬��ʹ�ú���ո�����ƥ��
		if(N>1)
		{
			bool cir=0;//�ж�ѭ���Ƿ��Ѿ����й����״�ѭ��Aֻ���һ�����
			while((flagA<A.num())||(flagB<B.num()))//��A��Bδ�����,ѭ������
			{
				if(flagA<A.num())//��Aδ�����,�����һ��A
				{
					cout<<" ";
					A.next();
					A.print_cur();
					flagA++;//A������+1
				}
				if(cir&&flagA<A.num())//������ѭ��,�������ѭ���ڶ���A
				{
					cout<<" ";
					A.next();
					A.print_cur();
					flagA++;//A������+1
				}
				if(flagB<B.num())//B��A�����,��Bδ�����,�����һ��
				{
					cout<<" ";
					B.next();
					B.print_cur();
					flagB++;//B������+1
				}
				cir=1;//��һ��ѭ���ѽ��й�
			}
		}
	}
	system("pause");
	return 0;
}
List::List()//����������
{
	number=0;
	head=new Node;
	tail=head;
	tail->next=NULL;
	current=head;
}
void List::add(int n)//�����Ϊ��������½��
{
	Node *newnode=new Node;
	newnode->order=n;
	tail->next=newnode;
	tail=newnode;
	tail->next=NULL;
	number++;//�������+1
}
void List::next()//��currentָ�����һ�����
{
	current=current->next;
}
void List::print_cur()//��ӡ����
{
	cout<<current->order;
}
int List::num()
{
	return number;
}
void List::clear()//�����
{
	if(number!=0)
	{
	number=0;//�������������
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
	while(A.num()+B.num()<N)//������������N��������
	{
		int n;
		cin>>n;
		getchar();
		while(n<=0)
		{
			fflush(stdin);//�����벻����Ҫ��,��ջ�������������
			cout<<"�����Ϊ������������������";
			A.clear();B.clear();//���������������
			return 0;
		}//����δ�ɹ�����
		if(n%2)//�ж��������Ƿ�Ϊ����
			A.add(n);//������ӵ�A
		else
			B.add(n);//ż����ӵ�B
	}
	fflush(stdin);//��ջ�����
    return 1;//����ɹ�
}