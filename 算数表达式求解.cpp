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
bool calculate(char,Stack<char> &,Stack<double> &,char &);//进行计算
template<class T>
bool result(Stack<char> &,Stack<double> &);//将运算符计算成结果
template<class T>
bool run();//运行计算器


int main()
{
	bool flag;//标记运算是否成功
	while(1)
	{
		cout<<"输入表达式："<<endl;
		fflush(stdin);
		flag=run<bool>();
		if(!flag)
		{
			cout<<"无法计算！";//若flag为0,输出运算出错提示
		}
		fflush(stdin);
		cout<<"是否继续？（y/n）";//询问是否继续
	    string fb="a";
		cin>>fb;//用户输入
		while(fb!="y"&&fb!="n")//若输入不是y或n
		{
			cout<<"（y/n）";//提示正确输入
			fflush(stdin);
			cin>>fb;//重新输入
		}
		if(fb=="n")//输入n退出循环
			break;
	}
	system("pause");
	return 0;
}

template<class T>
bool run(){
	Stack<char> Ope;//运算符栈
	Stack<double> Num;//数字栈
	char ch,fore='0';//ch记录新读入字符,fore记录前一字符
	double n;
	while(cin>>ch)//输入字符
	{
		if(priority(ch)==6)//非数字非运算符
		{
			cout<<"无法识别运算符！";
			return 0;
		}
		if(priority(ch))//合法运算符
		{
			if (!calculate<bool>(ch, Ope, Num, fore))
				return 0;
			if(ch=='=')//遇到等号不计算
				break;
			fore = ch;//更新fore
			continue;
		}
		cin.putback(ch);//输入为数字,退回输入流
		cin>>n;//重新输出double
		Num.push(n);//数字入栈
		fore = ch;//更新fore
	}
	if(Ope.is_empty()){//计算结束时运算符栈空
		if(Num.pop(n)){//得数出栈
			if(Num.is_empty()){//数字栈空
				cout<<n<<endl;//输出结果
				return 1;
			}
		}
	}
	return 0;
}

template<class T>
bool result(Stack<char> &Ope,Stack<double> &Num){
	char op;
	Ope.pop(op);//取出运算符
	double x,y;
	Num.pop(y);//数字出栈
	if(Num.is_empty())//判断数字栈是否为空
	{
		if(priority(op)==3)//数字栈空且运算符为+-,进行单目运算
		{
			Num.push(unary(op,y));
			return 1;
		}
		cout<<"运算符"<<op<<"不适用于单目运算！";//输入错误
		return 0;
	}
	Num.pop(x);//数字栈不空,栈顶出栈
	switch (op)//进行运算
	{
	case'+':Num.push(x+y);return 1;
	case'-':Num.push(x-y);return 1;
	case'*':Num.push(x*y);return 1;
	case'/':
		if(y==0)
		{
				cout<<"0不能作为被除数！";//被除数为0提示
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
	if (Ope.is_empty()||op=='(')//(直接入栈,若运算符栈为空当前运算符直接入栈
	{
		Ope.push(op);
		return 1;
	}
	if (fore == '(')//若前一字符为(,检测是否为单目运算
	{
		if (priority(op)==3)//若当前运算符为+-,进行单目运算
		{
			double x;
			cin >> x;
			unary(op, x);
			Num.push(x);//结果入栈
			fore = char(x);//更新fore
			return 1;
		}
		else
		{
			cout<<'op'<<"不适于单目运算！";//运算符输入错误提示
			return 0;
		}
	}
	char top_op;
	Ope.get_top(top_op);
	if ((op == ')') && (top_op == '('))//数字前后分别对应(),(出栈,)不入栈
	{
		Ope.pop(top_op);
		return 1;
	}
	if (!(op == ')') && (top_op == '('))//数字前为(,后非),运算符入栈不计算
	{
		Ope.push(op);
		return 1;
	}
	while(!Ope.is_empty()&&priority(op)<=priority(top_op))//当运算符栈非空,当前运算符优先级小于等于栈顶运算符,对栈顶运算符做运算
	{
		if ((op == ')') && (top_op == '('))//数字前后分别对应(),(出栈,)不入栈
		{
			Ope.pop(top_op);
			return 1;
		}
		if (!(op == ')') && (top_op == '('))//数字前为(,后非),运算符入栈不计算
		{
			Ope.push(op);
			return 1;
		}
		if(!result<bool>(Ope,Num))
			return 0;
		Ope.get_top(top_op);//运算完后更新栈顶运算符
	}
	if(!(op==')')&&op!='=')
		Ope.push(op);//所有运算完成,当前运算符入栈
	return 1;
}

double unary(char op,double num){
	if(op=='+')//+将负数变相反数
		if(num<0)num=-num;
		else;
	else//-将正数变相反数
		if(num>0)num=-num;
	return num;
}

int priority(char op){
	if(op>='0'&&op<='9')
		return 0;//数字返回0
	switch (op)//按优先级排列
	{
	case '=':return 1;break;
	case '(':case')':return 2;break;
	case '+':case '-':return 3;break;
	case '*':case '/':case'%':return 4;break;
	case'^':return 5;break;
	}
	return 6;//不合法运算符返回6
}

template<class T>
struct LinkNode{
	T data;
	LinkNode *link;
};

template<class T>
class Stack{
private:
	LinkNode<T> *top;//栈顶指针
public:
	Stack(){top=NULL;}//构造函数
	~Stack(){}//析构函数
	void push(const T&);//进栈
	bool pop(T&);//退栈
	bool get_top(T&)const;//获取栈顶元素
	bool is_empty()const{return(top==NULL)?true:false;}//确定栈是否为空
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

