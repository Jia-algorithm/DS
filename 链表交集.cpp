#include "iostream"
using namespace std;

struct LinkNode{
	int data;//存储数据
	LinkNode *Link;//指向下一结点
};

class List{
private:
	LinkNode *first;//头指针
	LinkNode *current;//当前位置
	LinkNode *tail;//尾指针
public:
	int number;//记录链表中节点数目
	List();//构造函数
	~List(){}//析构函数
	void insert(int);//插入新结点
	int search(int);//从当前结点向后搜索数字,若搜索到返回该数字,若未搜索到则返回第一个比欲搜索数字大的数字
	int output_cur();//输出current结点data
	void next();//current指向下一个结点
	void input_data();//输入所有数字
	void print_all();//输出所有数据
	bool location();//current为NULL返回0
};
void inter(List&,List&,List&);

int main()
{
	List S1,S2;
	S1.input_data();
	S2.input_data();
	if(S1.number==0||S2.number==0)
		cout<<"NULL";
	else{
		List S3;
		S1.next();//current到达第一个结点
		S2.next();
		inter(S1,S2,S3);
		if(S3.number==0)
			cout<<"NULL";
		else
			S3.print_all();
	}
	system("pause");
	return 0;
}

void inter(List &S1,List &S2,List &S3){
	int num1,num2;//分别存放S1和S2结点数据
		while(S1.location()&&S2.location()){//当S1和S2都未遍历完时继续循环
			num1=S1.search(num2=S2.output_cur());//在S1中搜索S2当前数字
			if(num1==0)//若S1搜索完,结束
				break;
			if(num1>num2){//S1中不存在num2,得到比num2大的num1
				num2=S2.search(num1);//在S2中搜索num1
				if(num2==0)//若S2搜索完,结束
					break;
			}
			if(num1==num2){//匹配成功
				S3.insert(num1);//新建S3结点
				S1.next();//S1、S2分别向后移一个结点
				S2.next();
			}
		}
}


List::List(){
	first=new LinkNode;//建立头结点
	current=first;//当前结点指向头结点
	tail=first;//尾结点指向头结点
	number=0;
}
void List::insert(int n){
	LinkNode *newnode;
	newnode=new LinkNode;
	newnode->data=n;
	tail->Link=newnode;
	tail=newnode;
	tail->Link=NULL;
	number++;//结点数目+1
}
int List::search(int n){
	while(current!=NULL){
		if(current->data>=n)
			return current->data;//大于等于搜索数字返回当前结点数据
		next();
	}
	return 0;//搜索完链表依然没找到数据返回0
}
int List::output_cur(){
	return current->data;
}
void List::next(){
	current=current->Link;
}
void List::input_data(){
	int n;
	while(1){
		cin>>n;
		if(n==-1)break;//输入-1结束
		insert(n);
	}
	while(getchar()!='\n')//将换行符清除
		getchar();
}
bool List::location(){
	if(current==NULL)
		return 0;//若遍历完链表返回0
	else
		return 1;
}
void List::print_all(){
	current=first->Link;//current指向第一个结点
	while(current!=tail){
		cout<<current->data<<" ";
		next();
	}
	cout<<tail->data;//单独打印尾结点以免产生多余空格
}