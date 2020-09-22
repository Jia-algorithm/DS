#include "iostream"
#include "string"
#include "iomanip"
using namespace std;



void start()//屏幕初始化
{
	cout << "##" << setw(10) << ' ' << "家谱管理系统" << setw(14) << ' ' << "##" << endl
		<< "========================================" << endl
		<< "##" << setw(10) << ' ' << "请选择要执行的操作：" << setw(6) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "A——完善家谱" << setw(13) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "B——添加家庭成员" << setw(9) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "C——解散局部家庭" << setw(9) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "D——更改家庭成员姓名" << setw(5) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "E——退出程序" << setw(13) << ' ' << "##" << endl
		<<"========================================"<< endl
		<< endl;
}

struct member//成员结构
{
    string name;//姓名
	member* first_child;//长子
	member* next_sibling;//兄弟
public:
	member()//构造函数
	{
		first_child = NULL;//默认指针为NULL
		next_sibling = NULL;
	}
};

class family//家谱类
{
private:
	member* ancestor;//祖先
public:
	family();
	~family() {}
	bool add_child();//添加家庭成员
	void add_sibling(member*,string);
	member* search(member* ,string);
	member* search_all(string);//在整个族谱中搜索成员
	void print_child(member*);//打印第一代子孙
	bool change();//更改家庭成员姓名
	bool set_sub();//完善家谱
	bool del_sub();//解散局部家庭
	bool delete_child(member* p, member* P[]);//删除当前成员所有子代
};


int main()
{
	start();//初始化屏幕
	family F;//创建家谱类
	char ch = 'Z';//记录用户输入操作
	while (ch != 'E')//E退出操作
	{
		cout << "请选择要执行的操作：" << endl;
		cin >> ch;
		switch (ch)
		{
		case'A':F.set_sub(); break;//A对应完善家谱
		case'B':F.add_child(); break;//B对应添加孩子
		case'C':F.del_sub(); break;//C对应解散局部家庭
		case'D':F.change(); break;//D对应改名
		case'E':break;
		default:cout << "不存在此操作！" << endl;//输入规定选项以外的选项报错
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

family::family()//构造函数
{
	cout << "首先建立一个家谱！" << endl << "请输入祖先的姓名："<<endl;
	ancestor = new member;
	cin >> ancestor->name;//将祖先姓名赋值
	cout << "此家谱的祖先是：" << ancestor->name << endl<<endl;
}

member* family::search(member* p,string n)
{
	if (p != NULL)//当指针不为空,继续递归
	{
		if (p->name == n)//姓名为制定字符串
			return p;//递归结束
		for (p = p->first_child; p != NULL; p = p->next_sibling)//按顺序对兄弟逐个搜索
		{
			member *pn= search(p, n);//递归
			if(pn!=NULL)
				return pn;//将当前指针返回
		}
	}
	return NULL;
}
member* family::search_all(string n)
{
	member* p = ancestor;//从祖先开始搜索
	p = search(p, n);
	if (p!=NULL)//搜索成功
		return p;//返回搜索到的指针
	return NULL;//未搜索到,返回空指针
}
bool family::add_child()
{
	string prt;
	cout << "请输入要添加儿女的人的姓名：" << endl;
	cin >> prt;
	member* parent = search_all(prt);//搜索对应姓名的家庭成员
	if (parent == NULL)//未搜索到
	{
		cout << prt << "尚不在此家谱中！" << endl;
		return 0;//退出函数
	}
	string ch_name;
	cout << "请输入" << prt << "新添加的儿女的姓名：" << endl;
	cin >> ch_name;
	if (parent->first_child == NULL)//若当前成员还没有子代,添加长子
	{
		member* newchild = new member;//为子代分配空间
		newchild->name = ch_name;//给姓名赋值
		parent->first_child = newchild;
	}
	else
		add_sibling(parent->first_child, ch_name);//已有长子,添加子代兄弟
	print_child(parent);//打印子代
	return 1;
}

void family::add_sibling(member* me, string sib_name)//添加兄弟
{
	member* newsib = new member;//分配空间
	newsib->name = sib_name;//给姓名赋值
	member* p = me;
	while (p->next_sibling != NULL)
		p = p->next_sibling;//找到最小兄弟
	p->next_sibling = newsib;//将新兄弟添加在兄弟链结尾
}
void family::print_child(member* prt)
{
	if (prt->first_child == NULL)//长子为空,没有子孙
		cout << prt->name << "没有子孙！" << endl;
	else
	{
		member* p = prt->first_child;
		cout << prt->name << "的第一代子孙是：";
		do
		{
			cout << p->name << '\t';
			p = p->next_sibling;
		} while (p != NULL);//指针不为空时以此打印兄弟链表
		cout << endl;
	}
}
bool family::change()
{
	cout << "请输入要更改姓名的人的姓名：" << endl;
	string old_name;
	cin >> old_name;
	member* p = search_all(old_name);//查找旧姓名
	if (p == NULL)//遍历完未找到
	{
		cout << old_name << "尚不在此家谱中！" << endl;
		return 0;
	}
	cout << "请输入更改后的姓名：" << endl;
	string new_name;
	cin >> new_name;
	p->name = new_name;//更改姓名
	cout << old_name << "已更名为" << p->name << endl;
	return 0;
}
bool family::set_sub()
{
	cout << "请输入要建立家庭的人的姓名：" << endl;
	string prt;
	cin >> prt;
	member* p = search_all(prt);//遍历查找
	if (p == NULL)
	{
		cout << prt << "尚不在此家谱中！"<<endl;//未找到
		return 0;
	}
	int n,i;
	cout << "请输入" << prt << "的儿女人数：" << endl;
	cin >> n;
	while (n <= 0)
	{
		cout<<"请输入正数！"<<endl;
		cin >> n;
	}
	cout << "请依次输入" << prt << "的儿女的姓名：" << endl;
	string ch;
	for (i = 0; i < n; i++)//循环输入对应子代名字
	{
		cin >> ch;
		if (p->first_child == NULL)//若当前成员还没有子代,添加长子
		{
			member* newchild = new member;
			newchild->name = ch;
			p->first_child = newchild;
		}
		else
			add_sibling(p->first_child, ch);//已有长子,添加子代兄弟;
	}
	print_child(p);
	return 1;
}

static int count_P;//记录遍历得到的局部家庭人数
bool family::delete_child(member* p,member *P[])
{
	if (p != NULL)//指针不为空继续递归
	{
		for (p = p->first_child; p != NULL; p = p->next_sibling)
		{
			if (delete_child(p, P))//递归
			{
				P[count_P] = p;//将成员地址记录在数组
				count_P++;//总数++
			}
		}
		return 1;
	}
	return 0;
}

bool family::del_sub()
{
	cout << "请输入要解散家庭的人的姓名：" << endl;
	string prt;
	cin >> prt;
	member* p = search_all(prt);
	if (p == NULL)
	{
		cout << prt << "尚不在此家谱中！" << endl;
		return 0;
	}
	member *P[100];
    count_P=0;
	cout << "要解散家庭的人是：" << prt << endl;
	print_child(p);
	count_P = 0;//计数器清零
	delete_child(p,P);//搜索所有子代地址,记入数组
	int i;
	for (i = 0; i < count_P; i++)
	{
		if (P[i] != NULL)//将数组中存储的指针依次释放
			delete P[i];
	}
	p->first_child = NULL;//将长子指针指向NULL
	return 1;
}

