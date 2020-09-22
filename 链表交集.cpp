#include "iostream"
using namespace std;

struct LinkNode{
	int data;//�洢����
	LinkNode *Link;//ָ����һ���
};

class List{
private:
	LinkNode *first;//ͷָ��
	LinkNode *current;//��ǰλ��
	LinkNode *tail;//βָ��
public:
	int number;//��¼�����нڵ���Ŀ
	List();//���캯��
	~List(){}//��������
	void insert(int);//�����½��
	int search(int);//�ӵ�ǰ��������������,�����������ظ�����,��δ�������򷵻ص�һ�������������ִ������
	int output_cur();//���current���data
	void next();//currentָ����һ�����
	void input_data();//������������
	void print_all();//�����������
	bool location();//currentΪNULL����0
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
		S1.next();//current�����һ�����
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
	int num1,num2;//�ֱ���S1��S2�������
		while(S1.location()&&S2.location()){//��S1��S2��δ������ʱ����ѭ��
			num1=S1.search(num2=S2.output_cur());//��S1������S2��ǰ����
			if(num1==0)//��S1������,����
				break;
			if(num1>num2){//S1�в�����num2,�õ���num2���num1
				num2=S2.search(num1);//��S2������num1
				if(num2==0)//��S2������,����
					break;
			}
			if(num1==num2){//ƥ��ɹ�
				S3.insert(num1);//�½�S3���
				S1.next();//S1��S2�ֱ������һ�����
				S2.next();
			}
		}
}


List::List(){
	first=new LinkNode;//����ͷ���
	current=first;//��ǰ���ָ��ͷ���
	tail=first;//β���ָ��ͷ���
	number=0;
}
void List::insert(int n){
	LinkNode *newnode;
	newnode=new LinkNode;
	newnode->data=n;
	tail->Link=newnode;
	tail=newnode;
	tail->Link=NULL;
	number++;//�����Ŀ+1
}
int List::search(int n){
	while(current!=NULL){
		if(current->data>=n)
			return current->data;//���ڵ����������ַ��ص�ǰ�������
		next();
	}
	return 0;//������������Ȼû�ҵ����ݷ���0
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
		if(n==-1)break;//����-1����
		insert(n);
	}
	while(getchar()!='\n')//�����з����
		getchar();
}
bool List::location(){
	if(current==NULL)
		return 0;//��������������0
	else
		return 1;
}
void List::print_all(){
	current=first->Link;//currentָ���һ�����
	while(current!=tail){
		cout<<current->data<<" ";
		next();
	}
	cout<<tail->data;//������ӡβ��������������ո�
}