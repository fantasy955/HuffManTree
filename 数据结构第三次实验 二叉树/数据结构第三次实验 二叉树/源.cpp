#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

#define FILE_ROOT "E:\\HuffManCode.txt"

class tTree
{
private:
	string str;
	string flag;
	struct node
	{
		node * leftChild;
		node * rightChild;
		int w;
		char c;
		bool flag;
	};
	node * base;
	int top;
	node * root;
public:
	tTree();
	~tTree();
	void WriteToFile();
	void toCode(node * n,string &str);
protected:
	void CreateTree();
	void Find(node * &n1, node * &n2);
};

tTree::tTree()
{
	cin >> str;
	top = 0;
	base = (node *)malloc(sizeof(node)*(2*str.length()-1));//若有个叶节点则总节点数数为2n-1，实际上字母会有重复，用不了这么多空间，此处只是为了方便
	for (int i = 0; i < str.length(); i++) {
		int temp = flag.find(str[i]);         
		if (temp>=0) {                 //该字母已经添加过
			base[temp].w++;            //权值加1
		}
		else {
			base[top].c = str[i];
			base[top].w=1;
			base[top].leftChild = NULL;
			base[top].flag = false;
			base[top].rightChild = NULL;
			flag.push_back(str[i]);   //把字母添加到string flag中
			top++;
		}
	}
	CreateTree();
}

tTree::~tTree()
{
	
}


void tTree::CreateTree() {
	node * temp1=NULL;  //temp1 temp2用于指向权值最小的两个节点
	node * temp2=NULL;
	for (int i = 0; i < flag.length() - 1; i++) {
		Find(temp1, temp2);
		if (temp1 == NULL || temp2 == NULL) {
			cout << "error" << endl;
			return;
		}
		base[top].leftChild = temp1;
		base[top].rightChild = temp2;
		base[top].w = temp1->w + temp2->w;
		base[top].flag = false;
		top++;
	}
	root = &base[top - 1];
}


void tTree::Find(node * &n1, node * &n2)   //找到权值最小的两个点
{
	bool flag = true;
	for (int i=0; i < top; i++) {
		if (!base[i].flag) {
			n1 = &base[i];
		}
	}
	for (int i =0; i < top; i++) {
		if (base[i].w < n1->w && !base[i].flag )
		{
			n1 = &base[i];
		}
	}
	n1->flag = true;                     //将找到的节点标记成已参与构造哈夫曼树
	for (int i = 0; i < top; i++) {
		if (!base[i].flag) {
			n2 = &base[i];
		}
	}
	for (int i = 0; i < top; i++) {
		if (base[i].w < n2->w && !base[i].flag)
		{
			n2 = &base[i];
		}
	}
	n2->flag = true;
}

void tTree::WriteToFile()
{
	string str;
	this->toCode(root, str);
}

void tTree::toCode(node * n,string & str)
{
	if (n->leftChild != NULL)
	{
		str.push_back('0');
		toCode(n->leftChild,str);
	}
	if (n->rightChild != NULL)
	{
		str.pop_back();
		str.push_back('1');
		toCode(n->rightChild, str);
	}
	if (n->rightChild == NULL) {
		ofstream o;
		o.open(FILE_ROOT, ios::app);
		o << str << ' ' << n->c << endl;
		o.close();
		return;
	}
}


int main() {
	ofstream o;
	o.open(FILE_ROOT, ios::trunc);
	o.close();
	tTree t1;
	t1.WriteToFile();
	ifstream i;
	i.open(FILE_ROOT, ios::in);
	string str;
	string code;
	char c;
	while (i>>c) {
		str.push_back(c);
	}
	cout << "please input code:";
	while (cin >> code)
	{
		int i = str.find(code);
		//判断输入的编码是否是对应一个字母
		if (i == string::npos || str[i+code.length()]<'a' || str[i+code.length()]>'z' || (i > 0 && (str[i - 1]<'a' || str[i - 1]>'z'))) {
			cout << "code error" << endl;
			cout << "please input code:";
			continue;
		}
		else {
			cout << str[i+code.length()]<<endl;
		}
		cout << "please input code:";
	}
	return 0;
}