#include <iostream>
using namespace std;

typedef int ElemType;

struct LNode
{
	ElemType data;
    LNode *next;
};


void CreatList(LNode *&p, ElemType arr[], int n) {
	LNode *q;
	p = new LNode;
	p->next = NULL;
	for (int i = 0; i < n; i++)
	{
		q = new LNode;
		q->data = arr[i];
		q->next = p->next;
		p->next = q;
	}
}

void sort(LNode *&L)
{
	LNode *pre, *p, *q;
	p = L->next->next;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && pre->next->data < p->data)
			pre = pre->next;
		p->next = pre->next;
		pre->next = p;
		p = q;

	}
}

void UnionList(LNode *LA, LNode *LB, LNode *LC) 
{
	LNode *pa = LA->next;
	LNode *pb = LB->next;
	LNode *pc = LC;
	LNode *q;
	while (pa != NULL && pb != NULL) 
	{
		if (pa->data <= pb->data)
		{
			q = new LNode;
			q->data = pa->data;
			pc->next = q;
			pc = q;
			pa = pa->next;
		}
		else
		{
			q = new LNode;
			q->data = pb->data;
			pc->next = q;
			pc = q;
			pb = pb->next;
		}
	}
	while (pa != NULL) {
		q = new LNode;
		q->data = pa->data;
		pc->next = q;
		pc = q;
		pa = pa->next;
	}
	while (pb != NULL) 
	{
		q = new LNode;
		q->data = pb->data;
		pc->next = q;
		pc = q;
		pb = pb->next;
	}
	pc->next = NULL;
}

void DispList(LNode *p) {
	LNode *q = p->next;
	while (q != NULL) {
		cout << q->data << '\t';
		q = q->next;
	}
}

int main() {
	ElemType arrA[] = { 21, 21, 32, 43, 5, 3543, 453, 34 };
	ElemType arrB[] = { 32, 533, 54, 54, 64, 3, 4, 21, 3 };

	LNode *LA = new LNode;
	LNode *LB = new LNode;
	LNode *LC = new LNode;
	CreatList(LA, arrA, sizeof(arrA)/sizeof(arrA[0]));
	CreatList(LB, arrB, sizeof(arrB)/sizeof(arrB[0]));
	sort(LA);
	sort(LB);
	UnionList(LA, LB, LC);
	DispList(LC);

	return 0;
}