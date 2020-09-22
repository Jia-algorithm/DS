#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath> 

using namespace std;
static int N;//total


struct lesson
{
	string code;
	string name;
	int hours=0;//studying hours one week
	int sem=0;//semister
	string pri_code[2]{"null","null"};
	int prior[2]{ -1,-1 };
};

void arrange_sem(int s, int n, lesson* l, int a[])//nunber of semister,quantity of lessons,the array of lessons
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		if (l[i].sem == s)
		{
			a[count] = i;
			count++;
		}
	}
	for (int i = 0; i < N; i++)
	{
		if (l[i].sem == 0)
		{
			if ((l[i].prior[0] == -1 || l[l[i].prior[0]].sem != 0) && (l[i].prior[1] == -1 || l[l[i].prior[1]].sem != 0))
			{
				a[count] = i;
				l[i].sem = s;
				count++;
			}
		}
		if (count == n)
			break;
	}
}



bool arrange_2(int num, int W[10][5], int& d, int day = 0)
{
	bool flag = 0;
	for (int i=day; i < 5; i++)
	{
		if (W[0][i] == -1)
		{
			W[0][i] = num;
			W[1][i] = num;
			d = i;
			flag = 1;
			break;
		}
		else if(W[5][i] == -1)
		{
			W[5][i] = num;
			W[6][i] = num;
			d = i;
			flag = 1;
			break;
		}
	}
	if(flag==0)
		for (int i = day; i < 5; i++)
		{
			if (W[2][i] == -1)
			{
				W[2][i] = num;
				W[3][i] = num;
				d = i;
				flag = 1;
				break;
			}
			else if (W[7][i] == -1)
			{
				W[7][i] = num;
				W[8][i] = num;
				d = i;
				flag = 1;
				break;
			}
		}
	return flag;
}
bool arrange_3(int num, int W[10][5], int &d,int day = 0)
{
	bool flag = 0;
	for (int i = day; i < 5; i++)
	{
		if (W[2][i] == -1)
		{
			W[2][i] = num;
			W[3][i] = num;
			W[4][i] = num;
			d = i;
			flag = 1;
			break;
		}
		else if (W[7][i] == -1)
		{
			W[7][i] = num;
			W[8][i] = num;
			W[9][i] = num;
			d = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		bool f=0;
		for (int i = day; i < 5; i++)
		{
			if (W[0][i] == -1)
			{
				W[0][i] = num;
				W[1][i] = num;
				f = 1;
				break;
			}
			else if (W[5][i] == -1)
			{
				W[5][i] = num;
				W[6][i] = num;
				f = 1;
				break;
			}
		}
		if(f==1)
			for (int i = day; i < 5; i++)
			{
				if (W[0][i] == -1)
				{
					W[0][i] = num;
					d = i;
					flag = 1;
					break;
				}
				else if (W[5][i] == -1)
				{
					W[5][i] = num;
					d = i;
					flag = 1;
					break;
				}
			}
	}
	return flag;
}

bool arrange_week(lesson* l, int W[10][5], int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		switch (l[a[i]].hours)
		{
			int day, day2;
		case 6:
			if (arrange_3(a[i], W, day))
			{
				if (arrange_3(a[i], W, day2, (day+2)%5))
					break;
			}
			else return 0;
		case 5:
			if (arrange_3(a[i], W, day))
				if (arrange_2(a[i], W, day2, (day + 2) % 5))
					break;
				else if(arrange_2(a[i], W, day2))
					break;
			return 0;
		case 4:
			if (arrange_2(a[i], W, day))
			{
				if (arrange_2(a[i], W, day2, (day + 2) % 5))
					break;
			}
			else return 0;
		case 3:
			if (arrange_3(a[i], W, day))
				break;
			else return 0;
		default: break;
		}
	}
	return 1;
}
#define x 30
void print(ofstream &of, int m[10][5],lesson *l)
{
	of  <<'\t'<< setw(x) <<"星期一" <<setw(x)<< "星期二" <<setw(x) << "星期三" << setw(x) << "星期四" << setw(x) << "星期五" << endl;
	for (int i = 0; i < 10; i++)
	{
		of << "第" << i + 1 << "节"<<'\t';
		for (int j = 0; j < 5; j++)
		{
			if (m[i][j] == -1)
				of << setw(x)<<"  ";
			else
				of << setw(x) << l[m[i][j]].name;
		}
		of << endl;
	}
}

int main()
{
	ifstream infile;
	string inf;
	cin >> inf;
	infile.open(inf);
	while (!infile.is_open())
	{
		cout << "wrong file name!input again!";
		cin >> inf;
		infile.open(inf);
	}
	int sem[8];
	N = 0;
	for (int i = 0; i < 8; i++)
	{
		infile >> sem[i];
		N += sem[i];
	}
	lesson* L = new lesson[N];
	for (int i = 0; i < N; i++)
	{
		if (infile.eof())
		{
			cout << "总课程数与各学期课程和不一致！";
			return 0;
		}
		infile>>L[i].code;
		infile >> L[i].name;
		infile >> L[i].hours;
		infile >> L[i].sem;
		char ch;
		for(int j=0;infile.get(ch), ch != '\n';j++)
		{
			infile.putback(ch);
			infile>>L[i].pri_code[j];
		}
	}
	if (!infile.eof())
	{
		cout << "总课程数与各学期课程和不一致！";
		return 0;
	}
	infile.close();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < N; k++)
			{
				if (L[i].pri_code[j] == "null")
					break;
				if (L[k].code == L[i].pri_code[j])
				{
					L[i].prior[j] = k;
					break;
				}
			}
		}
	}
	ofstream outfile;
	string outf;
	cin >> outf;
	outfile.open(outf);
	for (int i = 1; i < 9; i++)
	{
		int *a=new int[sem[i - 1]];
		arrange_sem(i, sem[i - 1], L, a);
		int week[10][5];
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 5; k++)
				week[j][k] = -1;
		if (!arrange_week(L, week, a, sem[i - 1]))
		{
			cout << "排课失败！";
			return 0;
		}
		outfile << "第" << i  << "学期" << endl;
		print(outfile, week, L);
		outfile << endl;
		delete[] a;
	}
	outfile.close();
	delete[] L;
	return 0;
}