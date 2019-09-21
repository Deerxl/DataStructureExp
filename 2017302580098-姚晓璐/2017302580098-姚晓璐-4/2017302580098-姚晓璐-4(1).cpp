#include <iostream>
using namespace std;

//��������
struct HTNode
{
	char data;   //���ֵ
	double weight; //Ȩ��
	int parent;  //˫�׽��
	int lchild;  //���ӽ��
	int rchild;  //�Һ��ӽ��
};

/*
�����������
�Ȱ����н��� parent, lchild, rchild ��Ϊ -1��
*/
void CreateHT(HTNode ht[], int n0) //n0��Ҷ�ӽ��ĸ���
{
	double min1, min2;
	int lnode, rnode;
	int i;
	
	for (i = 0; i < 2 * n0 - 1; i++)
	{
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
	}
	
	for (int j = n0; j < 2 * n0 - 2; j++)
	{
		min1 = min2 = 32767;
		lnode = rnode = -1;
		for (int k = 0; k <= j - 1; k++)
		{
			if (ht[k].parent == -1)
			{
				if (ht[k].weight < min1)
				{
					min2 = min1;
					rnode = lnode;
					min1 = ht[k].weight;
					lnode = k;
				}
				else if (ht[k].weight < min2)
				{
					min2 = ht[k].weight;
					rnode = k;
				}
			}
		}
		ht[j].weight = ht[lnode].weight + ht[rnode].weight;
		ht[j].lchild = lnode;
		ht[j].rchild = rnode;
		ht[lnode].parent = j;
		ht[rnode].parent = j;
	}
}

//����������
struct HCode
{
	char cd[50];  //��ŵ�ǰ���Ĺ�������
	int start;   //��ʾcd[start..n0]�ǹ�������
};

void CreateHCode(HTNode ht[], HCode hcd[], int n0)
{
	int i, f, c;
	HCode hc;
	for (i = 0; i < n0; i++)
	{
		hc.start = n0;
		c = i;
		f = ht[i].parent;
		while (f != -1)
		{
			if (ht[f].lchild == c)
			{
				hc.cd[hc.start--] = '0';
			}
			else
			{
				hc.cd[hc.start--] = '1';
			}
			c = f;
			f = ht[f].parent;
		}
		hc.start++;
		hcd[i] = hc;
	}
}

void DispHcode(HTNode ht[], HCode hcd[], int n0)
{
	cout << "����������" << endl;
	int i = 0;
	while(ht[i].data != '\0')
	{
		cout << ht[i].data << '\t';
		for (int k = hcd[i].start; k <= n0; k++)
		{
			cout << hcd[i].cd[k];
		}
		cout << endl;
		i++;
	}
}

int main()
{
	/*const int n = 20;
	int *arr = new int[n];

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand()%100;
	}
	
	HTNode *ht = new HTNode[2 * n];
	HCode *hcd = new HCode[2 * n];*/

	int array[] = { 12, 1, 23, 35, 21, 60, 90, 60, 10, 15, 25, 56};
	int n = sizeof(array) / sizeof(array[0]);

	HTNode ht[50];
	HCode hcd[50];

	
	
	for (int i = 0; i < n; i++)
	{
		ht[i].data = array[i];
		ht[i].weight = array[i];
	}

	CreateHT(ht, n);
	CreateHCode(ht, hcd, n);

	cout << "���������룺";
	for (int i = 0; i < n; i++)
	{
		cout << '\n' << array[i] << '\t';
		for (int k = hcd[i].start; k <= n; k++)
		{
			cout << hcd[i].cd[k];
		}
	}

	//DispHcode(ht, hcd, n);
	return 0;
}