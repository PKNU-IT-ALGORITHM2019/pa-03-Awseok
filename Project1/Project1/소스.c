#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define data_size1 1000
#define data_size2 10000
#define data_size3 100000

int data1[data_size1];
int data2[data_size2];
int data3[data_size3];
int temp[data_size3];
int data1_cmp[data_size1];
int data2_cmp[data_size2];
int data3_cmp[data_size3];
int check_qNum;
double result[9][6];
clock_t clock_a;

void copy_arr();
void random_arr();
void reverse_arr();
double Bubble(int data[], int size);
double Selection(int data[], int size);
double Insertion(int data[], int size);
double MergeSort(int data[], int p, int r);
void Merge(int data[], int p, int q, int r);
double QuickSort(int data[], int p, int r, int check_qNum);
int Partition1(int data[], int p, int r);
int Partition2(int data[], int p, int r);
int Partition3(int data[], int p, int r);
int rand_pivot(int p, int r);
int medianofthree(int data[], int p, int mid, int r);
void swap(int data[], int i, int j);
void build_max_heap(int data[], int size);
void max_heapify(int data[], int ind, int size);
double heap_sort(int data[], int size);
int cmp_fun(const void *p, const void *q);
double qsorting(void *arr, int size);
void print(int data[], int size);
void print_result();
void sort();

int main()
{
	system("mode con cols=120 lines=50");

	sort();

	print_result();

	return 0;
}

void copy_arr()
{
	int i;

	for (i = 0; i < data_size1; i++)
		data1_cmp[i] = data1[i];

	for (i = 0; i < data_size2; i++)
		data2_cmp[i] = data2[i];

	for (i = 0; i < data_size3; i++)
		data3_cmp[i] = data3[i];
}

void random_arr()
{
	int i;
	srand((unsigned)time(NULL));
	
	for (i = 0; i < data_size1; i++)
		data1[i] = rand() + 1;

	for (i = 0; i < data_size2; i++)
		data2[i] = rand() + 1;

	for (i = 0; i < data_size3; i++)
		data3[i] = rand() + 1;
}

void reverse_arr()
{
	int i;

	for (i = 0; i <data_size1; i++)
		data1[i] = data_size1 - i;

	for (i = 0; i < data_size2; i++)
		data2[i] = data_size2 - i;

	for (i = 0; i < data_size3; i++)
		data3[i] = data_size3 - i;
}


double Bubble(int data[], int size)
{
	int i, j, cnt = size;
	
	clock_a = clock();

	for (i = 0; i < size; i++)
	{
		for (j = 1; j < cnt; j++)
			if (data[j] < data[j - 1])
				swap(data, j, j - 1);
		cnt--;
	}

	return (double)(clock() - clock_a) / 1000;
}

double Insertion(int data[], int size)
{
	int i, j;

	clock_a = clock();

	for (i = 1; i < size; i++)
		for (j = 0; j < i; j++)
			if (data[i] < data[j])
				swap(data, i, j);

	return (double)(clock() - clock_a) / 1000;
}

double Selection(int data[], int size)
{
	int i, j, temp, temp_i;

	clock_a = clock();

	for (i = size - 1; i > 0; i--)
	{
		temp = 0;

		for (j = i; j >= 0; j--)
		{
			if (temp < data[j])
			{
				temp = data[j];
				temp_i = j;
			}
		}
		swap(data, temp_i, i);
	}

	return (double)(clock() - clock_a) / 1000;
}

double MergeSort(int data[], int p, int r)
{
	int q;

	clock_a = clock();

	if (p < r)
	{
		q = (p + r) / 2;
		MergeSort(data, p, q);
		MergeSort(data, q + 1, r);
		Merge(data, p, q, r);
	}

	return (double)(clock() - clock_a) / 1000;
}

void Merge(int data[], int p, int q, int r)
{
	int i = p, j = q + 1, k = p;
	
	while (i <= q && j <= r)
	{
		if (data[i] <= data[j])
			temp[k++] = data[i++];
		else
			temp[k++] = data[j++];
	}
	while (i <= q)
		temp[k++] = data[i++];
	while (j <= r)
		temp[k++] = data[j++];
	for (int i = p; i <= r; i++)
		data[i] = temp[i];
}

double QuickSort(int data[], int p, int r, int check_qNum)
{
	int q;

	clock_a = clock();

	if (p < r && check_qNum == 0)
	{
		q = Partition1(data, p, r);
		QuickSort(data, p, q - 1, check_qNum);
		QuickSort(data, q + 1, r, check_qNum);
	}
	else if (p < r && check_qNum == 1)
	{
		q = Partition2(data, p, r);
		QuickSort(data, p, q - 1, check_qNum);
		QuickSort(data, q + 1, r, check_qNum);
	}
	else if (p < r && check_qNum == 2)
	{
		q = Partition3(data, p, r);
		QuickSort(data, p, q - 1, check_qNum);
		QuickSort(data, q + 1, r, check_qNum);
	}

	return (double)(clock() - clock_a) / 1000;
}

int Partition1(int data[], int p, int r)
{

	int i = p - 1, j = p;

	for (j; j < r; j++) // pivot이 끝값일때 100,000개
	{
		if (data[j] >= data[r]);
		else
		{
			i += 1;
			swap(data, i, j);
		}
	}
	swap(data, i + 1, r);

	return i + 1;
}

int Partition2(int data[], int p, int r) // median of three
{

	int i = p - 1, j = p, mid = 0; 

	mid = (p + r) / 2;
	mid = medianofthree(data, p, mid, r);

	swap(data, mid, r);

	for (j; j < r; j++)
	{
		if (data[j] >= data[r]);
		else
		{
			i += 1;
			swap(data, i, j);
		}
	}
	swap(data, i + 1, r);

	return i + 1;
}

int Partition3(int data[], int p, int r) // random
{
	int i = p - 1, j = p, pivot = 0;

	pivot = rand_pivot(p, r);

	swap(data, pivot, r);

	for (j; j < r; j++)
	{
		if (data[j] >= data[r]);
		else
		{
			i += 1;
			swap(data, i, j);
		}
	}
	swap(data, i + 1, r);

	return i + 1;
	
}


int rand_pivot(int p, int r)
{
	srand((unsigned)time(NULL));
	return rand() % (r - p + 1) + p;
}

int medianofthree(int data[], int p, int mid, int r)
{
	if (data[p] > data[mid])
		swap(data, p, mid);
	else if (data[p] > data[r])
		swap(data, p, r);
	else if (data[mid] > data[r])
		swap(data, mid, r);

	return mid;
}

void swap(int data[], int i, int j)
{
	int temp;

	temp = data[j];
	data[j] = data[i];
	data[i] = temp;
}

void max_heapify(int data[], int ind, int size)
{
	int k = 2 * ind;

	if (k > size)
		return;

	if (k + 1 <= size)
		if (data[k] < data[k + 1])
			k++;

	if (data[ind] >= data[k])
		return;

	swap(data, ind, k);

	max_heapify(data, k, size);
}

void build_max_heap(int data[], int size)
{
	int i;

	for (i = size / 2; i >= 0; i--)
		max_heapify(data, i, size);
}

double heap_sort(int data[], int size)
{
	int i;

	clock_a = clock();
	build_max_heap(data, size);

	for (i = size; i > 0; i--)
	{
		swap(data, 0, i);
		max_heapify(data, 0, i - 1);
	}

	return (double)(clock() - clock_a) / 1000;
}

int cmp_fun(const void *p, const void *q)
{
	if (*(int*)p < *(int*)q)
		return -1;
	else if (*(int *)p == *(int *)q)
		return 0;
	else
		return 1;
}

double qsorting(void *arr, int size)
{
	clock_a = clock();
	qsort(arr, size, sizeof(arr), cmp_fun);
	return (double)(clock() - clock_a) / 1000;
}

void print(int data[], int size)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%d ", data[i]);
}

void print_result()
{
	int i, j;

	printf("\t  Random1000\tReverse1000\tRandom10000\tReverse10000");
	printf("\tRandom100000\tReverse100000\n");

	for (i = 0; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			printf("Bubble    ");
			break;
		case 1:
			printf("Selection ");
			break;
		case 2:
			printf("Insertion ");
			break;
		case 3:
			printf("Merge     ");
			break;
		case 4:
			printf("Quick1    ");
			break;
		case 5:
			printf("Quick2    ");
			break;
		case 6:
			printf("Quick3    ");
			break;
		case 7:
			printf("Heap      ");
			break;
		case 8:
			printf("Library   ");
			break;
		default:
			printf("Index error");
			exit(1);
		}

		for (j = 0; j < 6; j++)
		{
			printf("%10lf\t", result[i][j]);
		}

		printf("\n");
	}
}

void sort()
{
	int size, *arr, i, j,ind;

	for (i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			random_arr();
			arr = data1_cmp;
			size = data_size1;
			break;
		case 1:
			arr = data2_cmp;
			size = data_size2;
			break;
		case 2:
			arr = data3_cmp;
			size = data_size3;
			break;
		case 3:
			reverse_arr();
			arr = data1_cmp;
			size = data_size1;
			break;
		case 4:
			arr = data2_cmp;
			size = data_size2;
			break;
		case 5:
			arr = data3_cmp;
			size = data_size3;
			break;
		}

		for (j = 0; j < 10; j++)
		{
			ind = 0;

			copy_arr();
			result[ind++][(i + 2) % 6] += Bubble(arr, size);
			copy_arr();
			result[ind++][(i + 2) % 6] += Selection(arr, size);
			copy_arr();
			result[ind++][(i + 2) % 6] += Insertion(arr, size);
			copy_arr();
			result[ind++][(i + 2) % 6] += MergeSort(arr, 0, size - 1);
			copy_arr();
			result[ind++][(i + 2) % 6] += QuickSort(arr, 0, size - 1, 0);
			copy_arr();
			result[ind++][(i + 2) % 6] += QuickSort(arr, 0, size - 1, 1);
			copy_arr();
			result[ind++][(i + 2) % 6] += QuickSort(arr, 0, size - 1, 2);
			copy_arr();
			result[ind++][(i + 2) % 6] += heap_sort(arr, size - 1);
			copy_arr();
			result[ind][(i + 2) % 6] += qsorting(arr, size);
		}
	}

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 6; j++)
			result[i][j] /= 10;
	}
}
