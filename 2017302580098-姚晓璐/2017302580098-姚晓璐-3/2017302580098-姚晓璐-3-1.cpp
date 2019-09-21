#include<iostream>
using namespace std;

//ջ
#define MaxSize 50

int mg[10][10] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

struct Box
{
	int x;
	int y;
	int di;      //��λ
};

struct SqStack
{
	Box data[MaxSize];
	int top;
};

void InitStack(SqStack *&p)
{
	p = new SqStack;
	p->top = -1;
}

bool PushStack(SqStack *&p, Box e)
{
	//�ж�ջ�Ƿ����
	if (p->top == MaxSize - 1)
		return false;
	p->top++;
	p->data[p->top] = e;
	return true;
}
bool PopStack(SqStack *&p, Box& e)
{
	if (p->top == -1)
		return false;
	e = p->data[p->top];
	p->top--;
	return true;
}

bool GetTop(SqStack *p, Box& e)
{
	if (p->top == -1)
		return false;
	e = p->data[p->top];
	return true;
}

bool IsStackEmpty(SqStack *p) {
	return (p->top == -1);
}

void DestoryStack(SqStack *p) {
	free(p);
}

//˳��ջ
/*
��ջ��Ϊ�յ�����£�
ȡջ��Ԫ�أ�
����ǳ��ڣ������ջ������Ԫ��
�������ǣ����ҵ���һ�����ڿ��߷��飬��ջ��
		  û���ҵ����ڿ��߷��飬���ջ
		  ��ջԪ��di��ֵ���Ա�������ͬ·��
*/
bool MgPath_stack(int xi, int yi, int xe, int ye)  // (xi,yi)->(xe,ye)
{
	Box p;
	Box path[MaxSize];
	int i(0), j(0);
	p.x = xi, p.y = yi, p.di = -1;      //�߹�����Ϊ-1

	SqStack * q = new SqStack;
	InitStack(q);

	PushStack(q, p); //�ѳ�ʼλ�ý�ջ

	bool find = false;
	int x, y, di(-1);
	while (!IsStackEmpty(q)) {
		GetTop(q, p);
		x = p.x, y = p.y, di = p.di;

		//�ǳ���
		find = false;
		if (x == xe && y == ye)
		{
			find = true;
			int j = 0;
			while (!IsStackEmpty(q)) {
				PopStack(q, p);
				path[j] = p;
				//cout <<"("<< path[j].x<<","<<path[j].y<<")\t";  //���
				j++;
			}
			cout << "��ջ�����Թ���" << endl;
			while (j > 0) {
				j--;
				cout << "(" << path[j].x << "," << path[j].y << ")\t";
			}
			cout << endl;
			DestoryStack(q);
			return true;
		}

		//���ǳ��ڣ��ҵ����ڿ��߷���		
		while (di < 4 && find == false) {
			di++;
			switch (di)
			{
			case 0:
				i = x; j = y + 1;
				break;
			case 1:
				i = x + 1; j = y;
				break;
			case 2:
				i = x; j = y - 1;
				break;
			case 3:
				i = x - 1; j = y;
				break;
			}
			if (mg[i][j] == 0)
			{
				find = true;
				q->data[q->top].di = di;
				p.x = i, p.y = j, p.di = -1;
				PushStack(q, p);
				mg[x][y] = -1;
			}
		}
		if (find == false) {
			PopStack(q, p);
			mg[p.x][p.y] = 0;  ///��ջ�󣬱����-1��Ϊ0
		}
	}
	return find;
}
