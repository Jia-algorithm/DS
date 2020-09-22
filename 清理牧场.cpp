#include <iostream>
#include <string>
#include"Btree.h"
using namespace std;

bool input(const int& rN, list &rwood)//输入木头段长度
{
	int length;//每段长度
	for (int i = 0; i < rN; i++)//循环输入N次
	{
		cin >> length;//输入每段长度
		if (length <= 0)//若输入不是正整数,报错,退出函数
		{
			rwood.clear_list();//调用函数清除list结点
			fflush(stdin);//清空缓存区
			return 0;//返回0值
		}
		rwood.insert(length);//插入对应长度结点
	}
	return 1;
}

int main()
{
	list wood;//存储木头段长度的链表
	cout << "输入所需木头段数：" << endl;
	int N;//木头段总数N
	cin >> N;//输入N
	while (N < 1 || N > 10000)//若输入不是小于等于10000的正整数,重新输入
	{
		cout << "请输入小于10000的正整数：" << endl;
		cin >> N;
	}
	cout << "输入各段木头长度：" << endl;
	while (!input(N, wood))//输入各段长度,若输入为负数,重新输入
	{
		cout << "长度不能为负数，请重新输入：" << endl;
	}
	cout << "最小花销是：" << endl;
	wood.sum_cost();//计算并输出最小花销
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
	if (is_empty())//若链表为空,直接将新结点接在头指针后
	{
		tail->next = h;
		tail = h;
		return 1;
	}
	Node* p = head->next, * q = head;
	if (tail->value <= n)//若尾指针数值不比新结点大,直接插在尾指针后
	{
		tail->next = h;
		tail = h;
		return 1;
	}
	while (p->value < n)//从头遍历结点,找到恰好大于等于新结点的结点
	{
		p = p->next;
		q = q->next;
	}
	h->next = p;//插入新结点
	q ->next = h;
	return 1;
}
bool list::sum_cost()
{
	if (is_empty())//链表为空,返回0
		return 0;
	if (head->next == tail)//若仅有一个结点,结点数值即为所求,直接输出
	{
		cout << tail->value << endl;
		return 1;
	}
	int cost = 0;
	Node* left = head->next, * right = left->next;//成对指针
	while (right != tail)
	{
		int s = (right->value) + (left->value);
		insert(s);//最小两长度相加,插入链表
		cost += s;//两长度计算入总花销
		left = right->next;//两指针后移两位
		right = left->next;
	}
	cost = cost + left->value + right->value;//最后两节长度计算入总花销
	cout << cost << endl;//输出花销
	return 1;
}