#include "iostream"
#include "string"
#include "iomanip"
using namespace std;



void start()//��Ļ��ʼ��
{
	cout << "##" << setw(10) << ' ' << "���׹���ϵͳ" << setw(14) << ' ' << "##" << endl
		<< "========================================" << endl
		<< "##" << setw(10) << ' ' << "��ѡ��Ҫִ�еĲ�����" << setw(6) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "A�������Ƽ���" << setw(13) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "B������Ӽ�ͥ��Ա" << setw(9) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "C������ɢ�ֲ���ͥ" << setw(9) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "D�������ļ�ͥ��Ա����" << setw(5) << ' ' << "##" << endl
		<< "##" << setw(10) << ' ' << "E�����˳�����" << setw(13) << ' ' << "##" << endl
		<<"========================================"<< endl
		<< endl;
}

struct member//��Ա�ṹ
{
    string name;//����
	member* first_child;//����
	member* next_sibling;//�ֵ�
public:
	member()//���캯��
	{
		first_child = NULL;//Ĭ��ָ��ΪNULL
		next_sibling = NULL;
	}
};

class family//������
{
private:
	member* ancestor;//����
public:
	family();
	~family() {}
	bool add_child();//��Ӽ�ͥ��Ա
	void add_sibling(member*,string);
	member* search(member* ,string);
	member* search_all(string);//������������������Ա
	void print_child(member*);//��ӡ��һ������
	bool change();//���ļ�ͥ��Ա����
	bool set_sub();//���Ƽ���
	bool del_sub();//��ɢ�ֲ���ͥ
	bool delete_child(member* p, member* P[]);//ɾ����ǰ��Ա�����Ӵ�
};


int main()
{
	start();//��ʼ����Ļ
	family F;//����������
	char ch = 'Z';//��¼�û��������
	while (ch != 'E')//E�˳�����
	{
		cout << "��ѡ��Ҫִ�еĲ�����" << endl;
		cin >> ch;
		switch (ch)
		{
		case'A':F.set_sub(); break;//A��Ӧ���Ƽ���
		case'B':F.add_child(); break;//B��Ӧ��Ӻ���
		case'C':F.del_sub(); break;//C��Ӧ��ɢ�ֲ���ͥ
		case'D':F.change(); break;//D��Ӧ����
		case'E':break;
		default:cout << "�����ڴ˲�����" << endl;//����涨ѡ�������ѡ���
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

family::family()//���캯��
{
	cout << "���Ƚ���һ�����ף�" << endl << "���������ȵ�������"<<endl;
	ancestor = new member;
	cin >> ancestor->name;//������������ֵ
	cout << "�˼��׵������ǣ�" << ancestor->name << endl<<endl;
}

member* family::search(member* p,string n)
{
	if (p != NULL)//��ָ�벻Ϊ��,�����ݹ�
	{
		if (p->name == n)//����Ϊ�ƶ��ַ���
			return p;//�ݹ����
		for (p = p->first_child; p != NULL; p = p->next_sibling)//��˳����ֵ��������
		{
			member *pn= search(p, n);//�ݹ�
			if(pn!=NULL)
				return pn;//����ǰָ�뷵��
		}
	}
	return NULL;
}
member* family::search_all(string n)
{
	member* p = ancestor;//�����ȿ�ʼ����
	p = search(p, n);
	if (p!=NULL)//�����ɹ�
		return p;//������������ָ��
	return NULL;//δ������,���ؿ�ָ��
}
bool family::add_child()
{
	string prt;
	cout << "������Ҫ��Ӷ�Ů���˵�������" << endl;
	cin >> prt;
	member* parent = search_all(prt);//������Ӧ�����ļ�ͥ��Ա
	if (parent == NULL)//δ������
	{
		cout << prt << "�в��ڴ˼����У�" << endl;
		return 0;//�˳�����
	}
	string ch_name;
	cout << "������" << prt << "����ӵĶ�Ů��������" << endl;
	cin >> ch_name;
	if (parent->first_child == NULL)//����ǰ��Ա��û���Ӵ�,��ӳ���
	{
		member* newchild = new member;//Ϊ�Ӵ�����ռ�
		newchild->name = ch_name;//��������ֵ
		parent->first_child = newchild;
	}
	else
		add_sibling(parent->first_child, ch_name);//���г���,����Ӵ��ֵ�
	print_child(parent);//��ӡ�Ӵ�
	return 1;
}

void family::add_sibling(member* me, string sib_name)//����ֵ�
{
	member* newsib = new member;//����ռ�
	newsib->name = sib_name;//��������ֵ
	member* p = me;
	while (p->next_sibling != NULL)
		p = p->next_sibling;//�ҵ���С�ֵ�
	p->next_sibling = newsib;//�����ֵ�������ֵ�����β
}
void family::print_child(member* prt)
{
	if (prt->first_child == NULL)//����Ϊ��,û������
		cout << prt->name << "û�����" << endl;
	else
	{
		member* p = prt->first_child;
		cout << prt->name << "�ĵ�һ�������ǣ�";
		do
		{
			cout << p->name << '\t';
			p = p->next_sibling;
		} while (p != NULL);//ָ�벻Ϊ��ʱ�Դ˴�ӡ�ֵ�����
		cout << endl;
	}
}
bool family::change()
{
	cout << "������Ҫ�����������˵�������" << endl;
	string old_name;
	cin >> old_name;
	member* p = search_all(old_name);//���Ҿ�����
	if (p == NULL)//������δ�ҵ�
	{
		cout << old_name << "�в��ڴ˼����У�" << endl;
		return 0;
	}
	cout << "��������ĺ��������" << endl;
	string new_name;
	cin >> new_name;
	p->name = new_name;//��������
	cout << old_name << "�Ѹ���Ϊ" << p->name << endl;
	return 0;
}
bool family::set_sub()
{
	cout << "������Ҫ������ͥ���˵�������" << endl;
	string prt;
	cin >> prt;
	member* p = search_all(prt);//��������
	if (p == NULL)
	{
		cout << prt << "�в��ڴ˼����У�"<<endl;//δ�ҵ�
		return 0;
	}
	int n,i;
	cout << "������" << prt << "�Ķ�Ů������" << endl;
	cin >> n;
	while (n <= 0)
	{
		cout<<"������������"<<endl;
		cin >> n;
	}
	cout << "����������" << prt << "�Ķ�Ů��������" << endl;
	string ch;
	for (i = 0; i < n; i++)//ѭ�������Ӧ�Ӵ�����
	{
		cin >> ch;
		if (p->first_child == NULL)//����ǰ��Ա��û���Ӵ�,��ӳ���
		{
			member* newchild = new member;
			newchild->name = ch;
			p->first_child = newchild;
		}
		else
			add_sibling(p->first_child, ch);//���г���,����Ӵ��ֵ�;
	}
	print_child(p);
	return 1;
}

static int count_P;//��¼�����õ��ľֲ���ͥ����
bool family::delete_child(member* p,member *P[])
{
	if (p != NULL)//ָ�벻Ϊ�ռ����ݹ�
	{
		for (p = p->first_child; p != NULL; p = p->next_sibling)
		{
			if (delete_child(p, P))//�ݹ�
			{
				P[count_P] = p;//����Ա��ַ��¼������
				count_P++;//����++
			}
		}
		return 1;
	}
	return 0;
}

bool family::del_sub()
{
	cout << "������Ҫ��ɢ��ͥ���˵�������" << endl;
	string prt;
	cin >> prt;
	member* p = search_all(prt);
	if (p == NULL)
	{
		cout << prt << "�в��ڴ˼����У�" << endl;
		return 0;
	}
	member *P[100];
    count_P=0;
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << prt << endl;
	print_child(p);
	count_P = 0;//����������
	delete_child(p,P);//���������Ӵ���ַ,��������
	int i;
	for (i = 0; i < count_P; i++)
	{
		if (P[i] != NULL)//�������д洢��ָ�������ͷ�
			delete P[i];
	}
	p->first_child = NULL;//������ָ��ָ��NULL
	return 1;
}

