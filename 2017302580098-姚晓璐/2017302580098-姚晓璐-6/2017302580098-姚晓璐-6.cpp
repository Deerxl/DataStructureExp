#include<iostream>
using namespace std;
#include<stdlib.h>
#include <windows.h>
#include <WinBase.h>
#include <ctime>

typedef int KeyType;
typedef char InfoType;
struct Rectype
{
	KeyType key;    //关键字项
	InfoType data;  //其他数据项，类型为InfoType
};

//直接插入排序
/*
记录下 R[i] 处的值 为temp，再将前面的元素依次后挪，直到 temp的值比前面的大，最后再将temp的值插入到这个位置
时间复杂度 n²
*/
void InsertSort(Rectype R[], int n)
{
	Rectype temp;
	int j;
	for (int i = 1; i < n; i++)
	{
		temp = R[i];
		j = i - 1;
		while (R[j].key >temp.key && j >= 0)
		{
			R[j + 1] = R[j];
			j--;
		}
		R[j + 1] = temp;
	}
}

//折半插入排序
/*
R[i]位置的值，插入到有序区 0 - (i -1), 将区间折半，比较中间元素mid和 R[i]的值，
如果mid比R[i]大，high = mid
如果mid比R[i]小，low = mid;
只需要记录high的位置
找到位置后，后面的元素依次后挪
*/
void BinInsertSort(Rectype R[], int n)
{
	Rectype temp;
	int low, high, mid;
	int j;
	for (int i = 1; i < n; i++)
	{
		temp = R[i];
		low = 0;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (R[i].key > R[mid].key)
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
		for (j = i - 1; j > high; j--)
		{
			R[j + 1] = R[j];
		}
		R[j + 1] = temp;
	}
}

//希尔排序
/*
把元素分为 d = n / 2 组，把相隔 d 的元素放在同一个组里，进行直接插入排序
前一个 元素 j = j - d;
依此循环，直到 d = 0 
*/
void ShellSort(Rectype R[], int n)
{
	Rectype temp;
	int j;
	for (int d = n / 2; d > 0; d = d / 2)
	{
		for (int i = d; i < n; i++)
		{
			temp = R[i];
			j = i - d;  //同一组内前一个比较元素
			while (R[j].key > temp.key && j >= 0)
			{
				R[j + d] = R[j];
				j =  j - d;
			}
			R[j + d] = temp;
		}
	}
}

//冒泡排序
void BubbleSort(Rectype R[], int n)
{
	bool sort;
	for (int i = 0; i < n - 1; i++)
	{
		sort = false;
		for (int j = n - 1; j > i; j--)
		{
			if (R[i].key > R[j].key)
			{
				swap(R[i], R[j]);
				sort = true;
			}
		}
		if (!sort)
		{
			return;
		}
	}
}

//快速排序
/*
选择一个基准 i （一般都是第一个），把元素放入适当的位置，划分成两部分
再选取左边的部分，选i为基准，再次划分……
选取右边的部分，以i为基准，划分……
*/
int partition(Rectype R[], int s, int t)
{
	int i = s;
	int j = t;
	Rectype temp;
	temp = R[i];
	while (i < j)
	{
		//从右到左扫描，找到一个小于基准的元素R[j], 插到R[i]处
		while (R[j].key >= temp.key && i < j)
		{
			j--;
		}
		R[i] = R[j];
		//从左到右扫描，找到一个大于基准的元素R[i]，插到R[j]处
		while (R[i].key <= temp.key && i < j)
		{
			i++;
		}
		R[j] = R[i];
	}
	R[i] = temp;
	return i;

}
void QuickSort(Rectype R[], int s, int t)       //对 R[s...t]的元素进行排序
{
	int i;
	if (s < t)
	{
		i = partition(R, s, t);
		QuickSort(R, s, i - 1);
		QuickSort(R, i + 1, t);
	}
}

//简单选择排序
/*
把元素分为有序区和无序区
在无序区中找到最小的元素，和无序区第一个元素交换
*/
void SelectSort(Rectype R[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int j = i;
		for (int k = i + 1; k < n; k++)
		{
			
			if (R[k].key < R[j].key)
			{
				j = k;
			}
		}
		if (j != i)
		{
			swap(R[i], R[j]);
		}
	}
}

int main()
{
	int length1 = 100;
	Rectype R1[100];
	for (int i = 0; i < length1; i++) {
		R1[i].key = rand();
	}

	/*InsertSort(R1, length1);
	cout << "数据元素为100时，直接插入排序：\n";*/
	
	/*BinInsertSort(R1, length1);
	cout << "\n数据元素为100时，折半插入排序：\n";*/

	/*ShellSort(R1, length1);
	cout << "\n数据元素为100时，希尔排序：\n"; */

	/*BubbleSort(R1, length1);
	cout << "\n数据元素为100时，冒泡排序：\n";*/

	/*QuickSort(R1, 0, 99);
	cout << "\n数据元素为100时，快速排序：\n";*/

	/*SelectSort(R1, length1);
	cout << "\n数据元素为100时，简单选择排序：\n";
	for (int i = 0; i < length1; i++)
	{
		cout << R1[i].key << '\t';
	}*/

	int length = 10000;
	Rectype R2[10000];
	
	for (int i = 0; i < length; i++) {
		R2[i].key = rand();
	}

	Rectype *R3 = new Rectype[100000];
	for (int i = 0; i < length; i++) {
		R3[i].key = rand();
	}
	/*DWORD start_InsertSort = ::GetTickCount();
	InsertSort(R2, length);
	DWORD end_InsertSort = ::GetTickCount();
	ULONG InsertSort_10000 = end_InsertSort - start_InsertSort;
	cout << "排序数是10000时，直接插入排序时间：" << InsertSort_10000 << endl;*/

	DWORD start_BinInsertSort = ::GetTickCount();
	BinInsertSort(R2, length);
	DWORD end_BinInsertSort = ::GetTickCount();
	ULONG BinInsertSort_10000 = end_BinInsertSort - start_BinInsertSort;
	cout << "排序数是10000时，折半插入排序时间：" << BinInsertSort_10000 << endl;

	DWORD start_BinInsertSort_100000 = ::GetTickCount();
	BinInsertSort(R3, length);
	DWORD end_BinInsertSort_1000000 = ::GetTickCount();
	ULONG BinInsertSort_100000 = end_BinInsertSort_1000000 - start_BinInsertSort_100000;
	cout << "排序数是100000时，折半插入排序时间：" << BinInsertSort_100000 << endl;

	/*DWORD start_ShellSort = ::GetTickCount();
	ShellSort(R2, length);
	DWORD end_ShellSort = ::GetTickCount();
	ULONG ShellSort_10000 = end_ShellSort - start_ShellSort;
	cout << "排序数是10000时，希尔排序时间：" << ShellSort_10000 << endl;*/

	/*DWORD start_SelectSort = ::GetTickCount();
	SelectSort(R2, length);
	DWORD end_SelectSort = ::GetTickCount();
	ULONG SelectSort_10000 = end_SelectSort - start_SelectSort;
	cout << "排序数是10000时，简单选择排序时间：" << SelectSort_10000 << endl;*/   //109
	return 0;
}