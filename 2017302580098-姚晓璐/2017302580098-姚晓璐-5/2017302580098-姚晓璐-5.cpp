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
���������ţ���ʼ�������� k=0�� ��ǰһ������ջ
�������ţ���ʼ�����Һ��� k=1
���������ţ�������ϣ���ջ
��������������ַ����ж������㻹���ҽ�� ��k��¼
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
����������ȸ�����������
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
�ǵݹ��㷨
��ջ���д洢
��ջ���յ�����£��Ƚ��Һ��ӽ�ջ���ٽ����ӽ�ջ
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
	//�ж�ջ�Ƿ����
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
	cout << "����������ݹ飺" << endl;
	PreOrder_1(p);
	cout << '\n' << "����������ǵݹ飺" << endl;
	PreOrder_2(p);
}