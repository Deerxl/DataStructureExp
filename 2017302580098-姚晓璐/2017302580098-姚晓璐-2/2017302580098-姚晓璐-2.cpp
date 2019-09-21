#include <iostream>
using namespace std;

typedef char ElemType;

struct LNode
{
	ElemType data;
	LNode* next;
};

void Init(LNode *&p) 
{
	p = new LNode;
	p->next = NULL;
}

void Push(LNode *&p, ElemType e)
{
	LNode*q = new LNode;
	q->data = e;
	q->next = p->next;
	p->next = q;	
}

bool Pop(LNode *&p, ElemType& e)
{
	if (p->next == NULL)
		return false;
	LNode*q = new LNode;
	q = p->next;
	e = q->data;
	p->next = q->next;
	
	free(q);	
	return true;
}

bool GetTop(LNode *p, ElemType &e) {
	if (p->next == NULL)
		return false;
	e = p->next->data; //È¡Õ»¶¥ÔªËØ
	return true;
}

void Destroy(LNode*&p) 
{
	LNode*pre = p;
	LNode*q = p->next;
	while (q != NULL)
	{
		free(pre);
		pre = q;
		q = pre->next;
	}
	free(pre);
}

bool match(char exp[], int n) {
	
	bool match = true;
	LNode* p;
	Init(p);
    char e;
	int i = 0;
	int a(0), b(0);
	while (i < n && match == true) 
	{
		if (exp[i] == '(') {
			Push(p, exp[i]);
			a++;
		}
		else if (exp[i] == ')')
		{
			if (GetTop(p, e))
			{
				if (e == '(')
				{
					Pop(p, e);
					b++;
				}
				else
					match = false;
			}
			else
				match = false;
		}
		i++;
	}
	if (a != b || a == 0 && b == 0) 
		return false;

	Destroy(p);
	return match;

}

int main() {
	ElemType exp1[] = "()(*******)";

	bool n = match(exp1, sizeof(exp1));
	cout << n;
}