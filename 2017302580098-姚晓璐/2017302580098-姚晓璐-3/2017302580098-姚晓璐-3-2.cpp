#include<iostream>
using namespace std;

#define MaxSize 50

int mg_2[10][10] =
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

struct Box {
	int x, y;
	int pre;     //��·����һ�������ڶ����е��±�
};

struct SqQueue {
	Box data[MaxSize];
	int front, rear;
};

void InitQueue(SqQueue *&q) {
	q = new SqQueue;
	q->front = q->rear = 1;
}

bool EnQueue(SqQueue *&q, Box e) {
	if (q->rear == MaxSize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool DeQueue(SqQueue *&q, Box& e) {
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

bool IsQueueEmpty(SqQueue *q) {
	return(q->front == q->rear);
}

void DetroyQueue(SqQueue *&q) {
	free(q);
}


/*
��������Թ�
���в�Ϊ�յ�����£�
����һ��Ԫ�أ�����ǳ��ڣ������
			  ������ǣ����ҵ��������ڿ��߷��飬����
*/
bool MgPath_queue(int xi, int yi, int xe, int ye) {
	Box p;

	SqQueue * q = new SqQueue;
	InitQueue(q);

	p.x = xi, p.y = yi, p.pre = 0;
	EnQueue(q, p);
	mg_2[xi][yi] = -1;

	int x, y;
	int i, j;
	while (!IsQueueEmpty(q))
	{
		DeQueue(q, p);
		x = p.x, y = p.y;

		if (x == xe && y == ye) //������յ㣬������
		{
			//���
			int m = q->front;
			int k;
			while(m!= 0)
			{
				k = m;
				m = q->data[m].pre;
				q->data[k].pre = -1;
			}
			int n = 0;
			cout << "��������Թ���" << endl;
			while (n < MaxSize) {
				if (q->data[n].pre == -1)
					cout << "(" << q->data[n].x << "," << q->data[n].y << ")\t";
				n++;
			}
			return true;
		}

		for (int di = 0; di < 4; di++)
		{
			switch (di)
			{
			case 0:
				i = x;
				j = y + 1;  //����ʹ�� ++ --
				break;
			case 1:
				i = x + 1;
				j = y;
				break;
			case 2:
				i = x; 
				j = y - 1;
				break;
			case 3:
				i = x - 1; 
				j = y;
				break;
			}
			if (mg_2[i][j] == 0)
			{
				p.x = i;
				p.y = j;
				p.pre = q->front; //�Ѷ�ͷָ��������pre������¼����ǰһ�����飨���Ӻ�front���ƣ�ָ��ľ��ǳ��ӵķ��飩
				EnQueue(q, p);
				mg_2[i][j] = -1;
			}
		}
	}
	return false;
}