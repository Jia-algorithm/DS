#include <iostream>
#include <string>
#include"Btree.h"
using namespace std;

bool input(const int& rN, list &rwood)//����ľͷ�γ���
{
	int length;//ÿ�γ���
	for (int i = 0; i < rN; i++)//ѭ������N��
	{
		cin >> length;//����ÿ�γ���
		if (length <= 0)//�����벻��������,����,�˳�����
		{
			rwood.clear_list();//���ú������list���
			fflush(stdin);//��ջ�����
			return 0;//����0ֵ
		}
		rwood.insert(length);//�����Ӧ���Ƚ��
	}
	return 1;
}

int main()
{
	list wood;//�洢ľͷ�γ��ȵ�����
	cout << "��������ľͷ������" << endl;
	int N;//ľͷ������N
	cin >> N;//����N
	while (N < 1 || N > 10000)//�����벻��С�ڵ���10000��������,��������
	{
		cout << "������С��10000����������" << endl;
		cin >> N;
	}
	cout << "�������ľͷ���ȣ�" << endl;
	while (!input(N, wood))//������γ���,������Ϊ����,��������
	{
		cout << "���Ȳ���Ϊ���������������룺" << endl;
	}
	cout << "��С�����ǣ�" << endl;
	wood.sum_cost();//���㲢�����С����
	system("pause");
	return 1;
}

bool list::clear_list()
{
	if (is_empty())
		return 0;
	Node* p = head->next;
	while (head != tail)
	{
		delete head;
		head = p;
		p = p->next;
	}
	head->next = NULL;
	return 1;
}
list::list()
{
	head = new Node;
	tail = head;
}
list::~list()
{
	Node* p = head->next;
	while (head != tail)
	{
		delete head;
		head = p;
		p = p->next;
	}
}
bool list::insert(int& n)
{
	Node* h = new Node{ n,NULL };
	if (is_empty())//������Ϊ��,ֱ�ӽ��½�����ͷָ���
	{
		tail->next = h;
		tail = h;
		return 1;
	}
	Node* p = head->next, * q = head;
	if (tail->value <= n)//��βָ����ֵ�����½���,ֱ�Ӳ���βָ���
	{
		tail->next = h;
		tail = h;
		return 1;
	}
	while (p->value < n)//��ͷ�������,�ҵ�ǡ�ô��ڵ����½��Ľ��
	{
		p = p->next;
		q = q->next;
	}
	h->next = p;//�����½��
	q ->next = h;
	return 1;
}
bool list::sum_cost()
{
	if (is_empty())//����Ϊ��,����0
		return 0;
	if (head->next == tail)//������һ�����,�����ֵ��Ϊ����,ֱ�����
	{
		cout << tail->value << endl;
		return 1;
	}
	int cost = 0;
	Node* left = head->next, * right = left->next;//�ɶ�ָ��
	while (right != tail)
	{
		int s = (right->value) + (left->value);
		insert(s);//��С���������,��������
		cost += s;//�����ȼ������ܻ���
		left = right->next;//��ָ�������λ
		right = left->next;
	}
	cost = cost + left->value + right->value;//������ڳ��ȼ������ܻ���
	cout << cost << endl;//�������
	return 1;
}