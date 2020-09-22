#include <iostream>
using namespace std;
#include<time.h>
#define max 1000000;

long sort1(int r[], int n)//ð������
{
	long count=0;
	for(int i=1;i<n;i++)
		for(int j=n-1;j>=i;j--)
			if (r[j - i] > r[j])
			{
				int t = r[j - 1];
				r[j - 1] = r[j];
				r[j] = t;
				count++;
			}
	return count;
}
long sort2(int r[], int n)//ѡ������
{
	long count = 0;
	for (int i = 0; i < n-1; i++)
	{
		int k = i;
		for (int j = i + 1; j <= n - 1; j++)
			if (r[j] < r[k])
			{
				k = j;
				count++;
			}
		if (k != i)
		{
			int t = r[k];
			r[k] = r[i];
			r[i] = t;
			count++;
		}
	}
	return count;
}
double sort3(int r[], int n)//ֱ�Ӳ�������
{
	int t;
	double count = 0;
	int* rp = new int[n];
	for(int i=1;i<=n-1;i++)
		if (r[i] < r[i - 1])
		{
			t = r[i];
			int j = i - 1;
			do
			{
				r[j + 1] = r[j];
				count++;
				j--;
			} while (j >= 0 && t < r[j]);
			r[j + 1] = t;
			count++;
		}
	delete[] rp;
	return count;
}
int sort4(int r[], int n)//ϣ������
{
	int i, j,t, gap = n+1,count=0;
	do
	{
		gap = gap / 3 + 1;
		for(i=0+gap;i<n;i++)
			if (r[i] < r[i - gap])
			{
				t = r[i];
				j = i - gap;
				do {
					r[j + gap] = r[j];
					j = j - gap;
					count++;
				} while (j >= 0 && t < r[j]);
				r[j + gap] = t;
				count++;
			}
	} while (gap > 1);
	return count;
}
int partition(int r[],const int low,const int high,int &rc)
{
	int pivotpos = low, pivot = r[low];
	for(int i=low+1;i<=high;i++)
		if (r[i] < pivot)
		{
			pivotpos++;
			if (pivotpos != i)
			{
				int t = r[pivotpos];
				r[pivotpos] = r[i];
				r[i] = r[pivotpos];
				rc++;
			}
		}
	r[low] = r[pivotpos];
	r[pivotpos] = pivot;
	rc++;
	return pivotpos;
}
void quicksort(int r[], const int left, const int right, int &rc)
{
	if (left < right)
	{
		int pivotpos = partition(r, left, right, rc);
		quicksort(r, left, pivotpos - 1, rc);
		quicksort(r, pivotpos + 1, right, rc);
	}
}
int sort5(int r[],int n)//��������
{
	int count=0;
	quicksort(r, 0, n - 1, count);
	return count;
}
void siftdown(int r[], const int start, const int m, int& rc)
{
	int i = start, j = 2 * i + 1;
	int t = r[i];
	while (j <= m)
	{
		if (j < m && r[i] < r[j + 1])
			j++;
		if (t >= r[j])
			break;
		else
		{
			r[i] = r[j];
			i = j;
			j = 2 * j + 1;
			rc++;
		}
	}
	r[i] = t;
}
int sort6(int r[], int n)//������
{
	int count = 0;
	for (int i = (n - 2) / 2; i >= 0; i--)
		siftdown(r, i, n - 1, count);
	for (int i = n - 1; i >= 0; i--)
	{
		int t = r[i];
		r[i] = r[0];
		r[0] = t;
		count++;
		siftdown(r, 0, i - 1, count);
	}
	return count;
}
void merge(int r[], int r1[],const int left, const int mid, const int right, int& rc)
{
	
	for (int k = left; k < right; k++)
	{
		r1[k] = r[k];
		rc++;
	}
	int s1 = left, s2 = mid + 1, t = left;
	while (s1 <= mid && s2 <= right)
	{
		if (r1[s1] <= r[s2])
			r[t++] = r1[s1++];
		else
			r[t++] = r1[s2++];
		rc++;
	}
	while (s1 < mid)
	{
		r[t++] = r1[s1++];
		rc++;
	}
	while (s2 < right)
	{
		r[t++] = r1[s2++];
		rc++;
	}
}
void mergesort(int r[],int r1[],int left, int right,int &rc)
{
	if (left >= right)
		return;
	int mid=(right+left)/2;
	mergesort(r, r1,left, mid,rc);
	mergesort(r, r1,mid + 1, right,rc);
	merge(r, r1,left, mid, right, rc);
}
int sort7(int r[], int n)//�鲢����
{
	int count = 0;
	int *r1 = new int[n];
	mergesort(r, r1,0, n - 1, count);
	return count;
}
int maxbit(int data[], int n) //���������������ݵ����λ��
{
	int d = 1; //��������λ��
	int p = 10;
	for (int i = 0; i < n; ++i)
	{
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}
int sort8(int data[], int n) //��������
{
	int d = maxbit(data, n);
	int* tmp = new int[n];
	int* count = new int[10];
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) 
	{
		for (j = 0; j < 10; j++)
			count[j] = 0;
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10;
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];
		for (j = n - 1; j >= 0; j--) 
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++)
			data[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
	return 0;
}


void screen_initial()
{
	cout << "**            �����㷨�Ƚ�                **" << endl
		<< "============================================" << endl
		<< "**            1---ð������                **" << endl
		<< "**            2---ѡ������                **" << endl
		<< "**            3---ֱ�Ӳ�������            **" << endl
		<< "**            4---ϣ������                **" << endl
		<< "**            5---��������                **" << endl
		<< "**            6---������                  **" << endl
		<< "**            7---�鲢����                **" << endl
		<< "**            8---��������                **" << endl
		<< "**            9---�˳�����                **" << endl
		<< "============================================" << endl;
}
int main()
{
	screen_initial();
	srand((unsigned)time(NULL));
	clock_t start, end;
	int n,op=0;
	cout << "������Ҫ������������ĸ�����" << endl;
	cin >> n;
	while (1)
	{
		cout <<endl<< "��ѡ�������㷨��" << '\t';
		cin >> op;
		if (op == 9)
			break;
		if (op < 1)
			continue;
		int* r = new int[n];
		for (int i = 0; i < n; i++)
			r[i] = rand() % max;
		int count;
		switch (op)
		{
		case 1:
			start = clock();
			count = sort1(r, n);
			end = clock();
			cout << "ð����������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "ð�����򽻻�������" << '\t' << count;
			break;
		case 2:
			start = clock();
			count = sort2(r, n);
			end = clock();
			cout << "ѡ����������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "ѡ�����򽻻�������" << '\t' << count;
			break;
		case 3:
			start = clock();
			count = sort3(r, n);
			end = clock();
			cout << "ֱ�Ӳ�����������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "ֱ�Ӳ������򽻻�������" << '\t' << count;
			break;
		case 4:
			start = clock();
			count = sort4(r, n);
			end = clock();
			cout << "ϣ����������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "ϣ�����򽻻�������" << '\t' << count;
			break;
		case 5:
			start = clock();
			count = sort5(r, n);
			end = clock();
			cout << "������������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "�������򽻻�������" << '\t' << count;
			break;
		case 6:
			start = clock();
			count = sort6(r, n);
			end = clock();
			cout << "����������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "�����򽻻�������" << '\t' << count;
			break;
		case 7:
			start = clock();
			count = sort7(r, n);
			end = clock();
			cout << "�鲢��������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "�鲢���򽻻�������" << '\t' << count;
			break;
		case 8:
			start = clock();
			count = sort8(r, n);
			end = clock();
			cout << "������������ʱ�䣺" << '\t'
				<< ((double)end - (double)start) / CLK_TCK << endl
				<< "�������򽻻�������" << '\t' << count;
			break;
		default:
			break;
		}
		delete[] r;
	}
	return 0;
}