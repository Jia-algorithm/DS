#include "iostream"
#include "string"
#include "iomanip"
using namespace std;
static int N=0;//��¼ϵͳ��ѧ������

class Student
{
private:
	string number;//ѧ��
	string name;//����
	string sex;//�Ա�
	int age;//����
	string subject;//���
public:
	void chg_number();//chg��change����ʾ�޸Ķ�Ӧ��Ա
	void chg_name();
	void chg_sex();
	void chg_age();
	void chg_subject();
	string show_num();
	void get_inf();//��������ȫ����Ϣ
	void show_stu();//��ʾ��Ӧѧ��ȫ����Ϣ
	Student();
	~Student();
};

struct node//��������
{
Student inf;
node* next;
};

void build(node*);//������Ϣϵͳ
void show_all(node*);
void delete_node(node *);
void insert(node*);
void search(node*);
void change(node*);

int main()
{
	cout<<"�����뽨��������Ϣϵͳ"<<endl;
	node* head;
	head=new node;
	build(head);
	show_all(head);
	int op=0;
	cout<<"��ѡ����Ҫ���еĲ�����1���룬2ɾ����3���ң�4�޸ģ�5ͳ�ƣ�0�˳���������";
	cin>>op;
	while(op)
		{
			switch(op)
			{
			case 1:insert(head);break;
			case 2:delete_node(head);break;
			case 3:search(head);break;
			case 4:change(head);break;
			case 5:show_all(head);break;
			default:cout<<"����������0~5";
			}
		    cout<<"��ѡ����Ҫ���еĲ�����1���룬2ɾ����3���ң�4�޸ģ�5ͳ�ƣ�0�˳���������"<<endl;
			cin>>op;
		}
	cout<<"�������˳�����ʾ��Ϣϵͳ�������ݣ�"<<endl;
	show_all(head);
	system("pause");
	return 0;
}

Student::Student()
{
	number="00";
	name="��";
	sex="��";
	age=0;
	subject="��";
}
Student::~Student()
{
}
void Student::get_inf()
{
	chg_number();
	chg_name();
	chg_sex();
	chg_age();
	chg_subject();
}
void Student::show_stu()
{
	cout<<left<<setw(10)<<number;
	cout<<setw(10)<<name;
	cout<<setw(10)<<sex;
	cout<<setw(10)<<age;
	cout<<setw(10)<<subject;
	cout<<endl;
}
void Student::chg_number(){cin>>number;getchar();}
void Student::chg_name(){cin>>name;getchar();}
void Student::chg_sex(){cin>>sex;while(sex!="��"&&sex!="Ů"){cout<<"�������Ա�Ϊ���С���Ů��";cin>>sex;};getchar();}
void Student::chg_age(){cin>>age;while(age>=100||age<=0){cout<<"��������ȷ������";cin>>age;}getchar();}
void Student::chg_subject(){cin>>subject;getchar();}
string Student::show_num(){return number;}

void build(node *p)
{
		int n;
		cout<<"�����뿼��������";
		cin>>n;
		if(n<=0)
		{cout<<"��������Ӧ����Ϊ1�����������룺";cin>>n;}
		N=n;
		cout<<"���������뿼���Ŀ��ţ��������Ա����估�������"<<endl;
		node *newnode,*tail;
		newnode=new node;
		p->next=newnode;
		tail=newnode;
		tail->next=NULL;
		newnode->inf.get_inf();
		n--;
		while(n)
		{
			newnode=new node;
			tail->next=newnode;
			newnode->inf.get_inf();
			n--;
			tail=newnode;
			tail->next=NULL;
		}
}


void show_all(node *head)
{
	cout<<endl<<left<<setw(10)<<"����"<<setw(10)<<"����"<<setw(10)<<"�Ա�"<<setw(10)<<"����"<<setw(10)<<"�������"<<endl;
	node *p;
	p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		p->inf.show_stu();
	}
	cout<<"����"<<N<<endl;
}

void delete_node(node *head)
{
	string del;
	cout<<"��������Ҫɾ���Ŀ��ţ�";
	cin>>del;
	bool flag=0;
	node *p=head->next;
	node *q=head;
	while(p!=NULL)
	{
      if((p->inf.show_num())==del)
		{flag=1;break;}
	  q=p;
      p=p->next;
	}
	if(flag==0)
		cout<<"��Ҫɾ���Ŀ�����Ϣ������"<<endl;
	else
	{
		q->next=p->next;
		cout<<"��Ҫɾ���Ŀ�����Ϣ�ǣ�"<<endl;
		p->inf.show_stu();
		delete p;
		N--;
	}
}

void insert(node *head)
{
	int n,i(1);
	bool flag=1;
	cout<<"��������Ҫ�����λ�ã�";
	cin>>n;
	while(n>N)
	{
		cout<<"��Ҫ�����λ�ò����ڣ�����������";
		cin>>n;
	}
	node *p=head;
	while(i<n)
	{
		p=p->next;
		i++;
	}
        cout<<"������Ҫ���뿼���Ŀ��ţ��������Ա����估�������"<<endl;
		node *newnode;
		newnode=new node;
		newnode->inf.get_inf();
		newnode->next=p->next;
		p->next=newnode;
		cout<<"������Ŀ�����Ϣ�ǣ�"<<endl;
		newnode->inf.show_stu();
		N++;
}

void search(node *head)
{
	string n;
	cout<<"��������Ҫ���ҵĿ��ţ�";
	cin>>n;
	bool flag=0;
	node *p=head->next;
	while(p!=NULL)
	{
      if((p->inf.show_num())==n)
		{flag=1;break;}
      p=p->next;
	}
	if(flag==0)
		cout<<"��Ҫ���ҵĿ�����Ϣ������"<<endl;
	else
	{
		cout<<"��Ҫ���ҵĿ�����Ϣ�ǣ�"<<endl;
		p->inf.show_stu();
	}
}

void change(node *head)
{
	string n;
	cout<<"��������Ҫ�޸ĵĿ��ţ�";
	cin>>n;
	bool flag=0;
	node *p=head->next;
	while(p!=NULL)
	{
      if((p->inf.show_num())==n)
		{flag=1;break;}
      p=p->next;
	}
	if(flag==0)
		cout<<"��Ҫ�޸ĵĿ�����Ϣ������"<<endl;
	else
	{
		cout<<"��ѡ����Ҫ�޸ĵĿ�����Ϣ��1���ţ�2������3�Ա�4���䣬5�������0�˳��޸ģ���"<<endl;
		int x;
		cin>>x;
		while(x)
		{
			switch(x)
			{
			case 1:cout<<"�������޸ĵĿ��ţ�";p->inf.chg_number();break;
			case 2:cout<<"�������޸ĵ�������";p->inf.chg_name();break;
			case 3:cout<<"�������޸ĵ��Ա�";p->inf.chg_sex();break;
			case 4:cout<<"�������޸ĵ����䣻";p->inf.chg_age();break;
			case 5:cout<<"�������޸ĵı������";p->inf.chg_subject();break;
			default:cout<<"����������0~5";
			}
		    cout<<"��ѡ����Ҫ�޸ĵĿ�����Ϣ��1���ţ�2������3�Ա�4���䣬5�������0�˳��޸ģ���"<<endl;
			cin>>x;
		}
		cout<<"���޸ĵĿ�����Ϣ�ǣ�"<<endl;
		p->inf.show_stu();
	}
}