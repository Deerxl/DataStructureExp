#include<iostream>
using namespace std;

typedef int ElemType;
#define MaxSize 50
struct BTNode
{
	ElemType data;
    BTNode* lchild;
    BTNode* rchild;
};
/*
A(B(D(, G)), C(E, F))
遇到左括号，开始处理左孩子 k=0， 将前一个结点进栈
遇到逗号，开始处理右孩子 k=1
遇到右括号，处理完毕，退栈
遇到其他情况，字符，判断是左结点还是右结点 用k记录
*/
void CreateBTree(BTNode *&b, string str)
{
	BTNode *Stack[MaxSize];
	BTNode *p = NULL;
	b = NULL;

	int j = 0;
	int k = 0;
	int top = -1;
	while (str[j] != '\0')
	{
		switch (str[j])
		{
		case '(':
			Stack[++top] = p;
			k = 0;
			break;
		case ')':
			top -= 1;
			break;
		case ',':
			k = 1;
			break;
		default:
			p = new BTNode;
			p->data = str[j];
			p->lchild = p->rchild = NULL;
			if (b == NULL)
			{
				b = p;
			}
			else
			{
				switch (k)
				{
				case 0:
					Stack[top]->lchild = p;
					//b->lchild = p;
					break;
				case 1:
					Stack[top]->rchild = p;
					//b->rchild = p;
					break;
				}
			}
			
			break;
		}
		j++;
	}

}

/*
先序遍历，先根，后左，再右
*/
void PreOrder_1(BTNode *b)
{
	if (b != NULL)
	{
		cout << b->data << '\t';
		PreOrder_1(b->lchild);
		PreOrder_1(b->rchild);
	}
}
/*
非递归算法
用栈进行存储
在栈不空的情况下，先将右孩子进栈，再将左孩子进栈
*/
struct SqStack
{
	BTNode *data[MaxSize];
	int top;
};

void InitStack(SqStack *&p)
{
	p = new SqStack;
	p->top = -1;
}

bool PushStack(SqStack *&p, BTNode *e)
{
	//判断栈是否溢出
	if (p->top == MaxSize - 1)
		return false;
	p->top++;
	p->data[p->top] = e;
	return true;
}
bool PopStack(SqStack *&p, BTNode*& e)
{
	if (p->top == -1)
		return false;
	e = p->data[p->top];
	p->top--;
	return true;
}
bool IsStackEmpty(SqStack *p) {
	return (p->top == -1);
}

void DestoryStack(SqStack *p) {
	free(p);
}

void PreOrder_2(BTNode *b)
{
	SqStack *q = NULL;
	InitStack(q);
	
	BTNode *p;
	if (b != NULL)
	{
		PushStack(q, b);
		while (!IsStackEmpty(q))
		{
			PopStack(q, p);
			cout << p->data << '\t';
			if (p->rchild != NULL)
			{
				PushStack(q, p->rchild);
			}
			if (p->lchild != NULL)
			{
				PushStack(q, p->lchild);
			}
		}
	}
}


int main()
{
	string str = "A(B(D(,G)),C(E,F))";
	BTNode *p = new BTNode;
	CreateBTree(p, str);
	cout << "先序遍历，递归：" << endl;
	PreOrder_1(p);
	cout << '\n' << "先序遍历，非递归：" << endl;
	PreOrder_2(p);
}