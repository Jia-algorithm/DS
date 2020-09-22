#include "iostream"
#include "string"
#include "iomanip"
using namespace std;
static int N=0;//记录系统中学生数量

class Student
{
private:
	string number;//学号
	string name;//姓名
	string sex;//性别
	int age;//年龄
	string subject;//类别
public:
	void chg_number();//chg即change，表示修改对应成员
	void chg_name();
	void chg_sex();
	void chg_age();
	void chg_subject();
	string show_num();
	void get_inf();//用于输入全部信息
	void show_stu();//显示对应学生全部信息
	Student();
	~Student();
};

struct node//建立链表
{
Student inf;
node* next;
};

void build(node*);//创建信息系统
void show_all(node*);
void delete_node(node *);
void insert(node*);
void search(node*);
void change(node*);

int main()
{
	cout<<"首先请建立考生信息系统"<<endl;
	node* head;
	head=new node;
	build(head);
	show_all(head);
	int op=0;
	cout<<"请选择您要进行的操作（1插入，2删除，3查找，4修改，5统计，0退出操作）：";
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
			default:cout<<"请重新输入0~5";
			}
		    cout<<"请选择您要进行的操作（1插入，2删除，3查找，4修改，5统计，0退出操作）："<<endl;
			cin>>op;
		}
	cout<<"操作已退出，显示信息系统最终数据："<<endl;
	show_all(head);
	system("pause");
	return 0;
}

Student::Student()
{
	number="00";
	name="空";
	sex="空";
	age=0;
	subject="空";
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
void Student::chg_sex(){cin>>sex;while(sex!="男"&&sex!="女"){cout<<"请输入性别为“男”或“女”";cin>>sex;};getchar();}
void Student::chg_age(){cin>>age;while(age>=100||age<=0){cout<<"请输入正确的年龄";cin>>age;}getchar();}
void Student::chg_subject(){cin>>subject;getchar();}
string Student::show_num(){return number;}

void build(node *p)
{
		int n;
		cout<<"请输入考生人数：";
		cin>>n;
		if(n<=0)
		{cout<<"考生人数应至少为1，请重新输入：";cin>>n;}
		N=n;
		cout<<"请依次输入考生的考号，姓名，性别，年龄及报考类别："<<endl;
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
	cout<<endl<<left<<setw(10)<<"考号"<<setw(10)<<"姓名"<<setw(10)<<"性别"<<setw(10)<<"年龄"<<setw(10)<<"报考类别"<<endl;
	node *p;
	p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		p->inf.show_stu();
	}
	cout<<"总数"<<N<<endl;
}

void delete_node(node *head)
{
	string del;
	cout<<"请输入您要删除的考号：";
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
		cout<<"您要删除的考生信息不存在"<<endl;
	else
	{
		q->next=p->next;
		cout<<"您要删除的考生信息是："<<endl;
		p->inf.show_stu();
		delete p;
		N--;
	}
}

void insert(node *head)
{
	int n,i(1);
	bool flag=1;
	cout<<"请输入您要插入的位置：";
	cin>>n;
	while(n>N)
	{
		cout<<"您要插入的位置不存在，请重新输入";
		cin>>n;
	}
	node *p=head;
	while(i<n)
	{
		p=p->next;
		i++;
	}
        cout<<"请输入要插入考生的考号，姓名，性别，年龄及报考类别："<<endl;
		node *newnode;
		newnode=new node;
		newnode->inf.get_inf();
		newnode->next=p->next;
		p->next=newnode;
		cout<<"您插入的考生信息是："<<endl;
		newnode->inf.show_stu();
		N++;
}

void search(node *head)
{
	string n;
	cout<<"请输入您要查找的考号：";
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
		cout<<"您要查找的考生信息不存在"<<endl;
	else
	{
		cout<<"您要查找的考生信息是："<<endl;
		p->inf.show_stu();
	}
}

void change(node *head)
{
	string n;
	cout<<"请输入您要修改的考号：";
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
		cout<<"您要修改的考生信息不存在"<<endl;
	else
	{
		cout<<"请选择您要修改的考生信息（1考号，2姓名，3性别，4年龄，5报考类别，0退出修改）："<<endl;
		int x;
		cin>>x;
		while(x)
		{
			switch(x)
			{
			case 1:cout<<"请输入修改的考号；";p->inf.chg_number();break;
			case 2:cout<<"请输入修改的姓名；";p->inf.chg_name();break;
			case 3:cout<<"请输入修改的性别；";p->inf.chg_sex();break;
			case 4:cout<<"请输入修改的年龄；";p->inf.chg_age();break;
			case 5:cout<<"请输入修改的报考类别；";p->inf.chg_subject();break;
			default:cout<<"请重新输入0~5";
			}
		    cout<<"请选择您要修改的考生信息（1考号，2姓名，3性别，4年龄，5报考类别，0退出修改）："<<endl;
			cin>>x;
		}
		cout<<"您修改的考生信息是："<<endl;
		p->inf.show_stu();
	}
}