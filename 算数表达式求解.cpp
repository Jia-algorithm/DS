#include "iostream"
using namespace std;
#include "string"


template<class T>
struct LinkNode;
template<class T>
class Stack;

int priority(char);
double unary(char,double);
template<class T>
bool calculate(char,Stack<char> &,Stack<double> &,char &);//���м���
template<class T>
bool result(Stack<char> &,Stack<double> &);//�����������ɽ��
template<class T>
bool run();//���м�����


int main()
{
	bool flag;//��������Ƿ�ɹ�
	while(1)
	{
		cout<<"������ʽ��"<<endl;
		fflush(stdin);
		flag=run<bool>();
		if(!flag)
		{
			cout<<"�޷����㣡";//��flagΪ0,������������ʾ
		}
		fflush(stdin);
		cout<<"�Ƿ��������y/n��";//ѯ���Ƿ����
	    string fb="a";
		cin>>fb;//�û�����
		while(fb!="y"&&fb!="n")//�����벻��y��n
		{
			cout<<"��y/n��";//��ʾ��ȷ����
			fflush(stdin);
			cin>>fb;//��������
		}
		if(fb=="n")//����n�˳�ѭ��
			break;
	}
	system("pause");
	return 0;
}

template<class T>
bool run(){
	Stack<char> Ope;//�����ջ
	Stack<double> Num;//����ջ
	char ch,fore='0';//ch��¼�¶����ַ�,fore��¼ǰһ�ַ�
	double n;
	while(cin>>ch)//�����ַ�
	{
		if(priority(ch)==6)//�����ַ������
		{
			cout<<"�޷�ʶ���������";
			return 0;
		}
		if(priority(ch))//�Ϸ������
		{
			if (!calculate<bool>(ch, Ope, Num, fore))
				return 0;
			if(ch=='=')//�����ȺŲ�����
				break;
			fore = ch;//����fore
			continue;
		}
		cin.putback(ch);//����Ϊ����,�˻�������
		cin>>n;//�������double
		Num.push(n);//������ջ
		fore = ch;//����fore
	}
	if(Ope.is_empty()){//�������ʱ�����ջ��
		if(Num.pop(n)){//������ջ
			if(Num.is_empty()){//����ջ��
				cout<<n<<endl;//������
				return 1;
			}
		}
	}
	return 0;
}

template<class T>
bool result(Stack<char> &Ope,Stack<double> &Num){
	char op;
	Ope.pop(op);//ȡ�������
	double x,y;
	Num.pop(y);//���ֳ�ջ
	if(Num.is_empty())//�ж�����ջ�Ƿ�Ϊ��
	{
		if(priority(op)==3)//����ջ���������Ϊ+-,���е�Ŀ����
		{
			Num.push(unary(op,y));
			return 1;
		}
		cout<<"�����"<<op<<"�������ڵ�Ŀ���㣡";//�������
		return 0;
	}
	Num.pop(x);//����ջ����,ջ����ջ
	switch (op)//��������
	{
	case'+':Num.push(x+y);return 1;
	case'-':Num.push(x-y);return 1;
	case'*':Num.push(x*y);return 1;
	case'/':
		if(y==0)
		{
				cout<<"0������Ϊ��������";//������Ϊ0��ʾ
				return 0;
		}
		Num.push(x/y);return 1;
	case'%':
		Num.push(double(int(x)%int(y)));return 1;
	case'^':
		int i,re=1;
		for(i=0;i<y;i++)
			re*=x;
		Num.push(double(re));
		return 1;
	}
	return 0;
}

template<class T>
bool calculate(char op,Stack<char> &Ope,Stack<double> &Num,char &fore){
	if (Ope.is_empty()||op=='(')//(ֱ����ջ,�������ջΪ�յ�ǰ�����ֱ����ջ
	{
		Ope.push(op);
		return 1;
	}
	if (fore == '(')//��ǰһ�ַ�Ϊ(,����Ƿ�Ϊ��Ŀ����
	{
		if (priority(op)==3)//����ǰ�����Ϊ+-,���е�Ŀ����
		{
			double x;
			cin >> x;
			unary(op, x);
			Num.push(x);//�����ջ
			fore = char(x);//����fore
			return 1;
		}
		else
		{
			cout<<'op'<<"�����ڵ�Ŀ���㣡";//��������������ʾ
			return 0;
		}
	}
	char top_op;
	Ope.get_top(top_op);
	if ((op == ')') && (top_op == '('))//����ǰ��ֱ��Ӧ(),(��ջ,)����ջ
	{
		Ope.pop(top_op);
		return 1;
	}
	if (!(op == ')') && (top_op == '('))//����ǰΪ(,���),�������ջ������
	{
		Ope.push(op);
		return 1;
	}
	while(!Ope.is_empty()&&priority(op)<=priority(top_op))//�������ջ�ǿ�,��ǰ��������ȼ�С�ڵ���ջ�������,��ջ�������������
	{
		if ((op == ')') && (top_op == '('))//����ǰ��ֱ��Ӧ(),(��ջ,)����ջ
		{
			Ope.pop(top_op);
			return 1;
		}
		if (!(op == ')') && (top_op == '('))//����ǰΪ(,���),�������ջ������
		{
			Ope.push(op);
			return 1;
		}
		if(!result<bool>(Ope,Num))
			return 0;
		Ope.get_top(top_op);//����������ջ�������
	}
	if(!(op==')')&&op!='=')
		Ope.push(op);//�����������,��ǰ�������ջ
	return 1;
}

double unary(char op,double num){
	if(op=='+')//+���������෴��
		if(num<0)num=-num;
		else;
	else//-���������෴��
		if(num>0)num=-num;
	return num;
}

int priority(char op){
	if(op>='0'&&op<='9')
		return 0;//���ַ���0
	switch (op)//�����ȼ�����
	{
	case '=':return 1;break;
	case '(':case')':return 2;break;
	case '+':case '-':return 3;break;
	case '*':case '/':case'%':return 4;break;
	case'^':return 5;break;
	}
	return 6;//���Ϸ����������6
}

template<class T>
struct LinkNode{
	T data;
	LinkNode *link;
};

template<class T>
class Stack{
private:
	LinkNode<T> *top;//ջ��ָ��
public:
	Stack(){top=NULL;}//���캯��
	~Stack(){}//��������
	void push(const T&);//��ջ
	bool pop(T&);//��ջ
	bool get_top(T&)const;//��ȡջ��Ԫ��
	bool is_empty()const{return(top==NULL)?true:false;}//ȷ��ջ�Ƿ�Ϊ��
};

template<class T>
void Stack<T>::push(const T& x){
	LinkNode<T> *p;
	p=new LinkNode<T>;
	p->data=x;
	p->link=top;
	top=p;
}
template<class T>
bool Stack<T>::pop(T& x){
	if(is_empty())
		return 0;
	LinkNode<T>*p=top;
	top=top->link;
	x=p->data;
	delete p;
	return 1;
}
template<class T>
bool Stack<T>::get_top(T& x)const{
	if(is_empty())
		return 0;
	x=top->data;
	return 1;
}

