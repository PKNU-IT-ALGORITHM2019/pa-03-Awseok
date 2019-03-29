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
int Bubble(int data[], int size);
int Selection(int data[], int size);
int Insertion(int data[], int size);
int MergeSort(int data[], int p, int r);
void Merge(int data[], int p, int q, int r);
int QuickSort(int data[], int p, int r);
int Partition1(int data[], int p, int r);
int Partition2(int data[], int p, int r);
int Partition3(int data[], int p, int r);
int rand_pivot(int p, int r);
int medianofthree(int data[], int p, int mid, int r);
void swap(int data[], int i, int j);
void print(int data[], int size);
void print_result();
void get_Bubble(int ind);
void get_Selection(int ind);
void get_Insertion(int ind);
void get_Merge(int ind);
void get_Quick(int ind);

int main()
{
	system("mode con cols=120 lines=50");

	random_arr();

	copy_arr();
	
	get_Bubble(0);

	get_Selection(0);

	get_Insertion(0);

	get_Merge(0);

	get_Quick(0);

	reverse_arr();

	copy_arr();

	get_Bubble(1);

	get_Selection(1);

	get_Insertion(1);

	get_Merge(1);

	get_Quick(1);

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


int Bubble(int data[], int size)
{
	int i, j, cnt = size;
	
	for (i = 0; i < size; i++)
	{
		for (j = 1; j < cnt; j++)
			if (data[j] < data[j - 1])
				swap(data, j, j - 1);
		cnt--;
	}

	return clock() - clock_a;
}

int Insertion(int data[], int size)
{
	int i, j;

	for (i = 1; i < size; i++)
		for (j = 0; j < i; j++)
			if (data[i] < data[j])
				swap(data, i, j);

	return clock() - clock_a;
}

int Selection(int data[], int size)
{
	int i, j, temp, temp_i;

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

	return clock() - clock_a;
}

int MergeSort(int data[], int p, int r)
{
	int q;

	if (p < r)
	{
		q = (p + r) / 2;
		MergeSort(data, p, q);
		MergeSort(data, q + 1, r);
		Merge(data, p, q, r);
	}

	return clock() - clock_a;
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

int QuickSort(int data[], int p, int r)
{
	int q;

	if (p < r && check_qNum == 0)
	{
		q = Partition1(data, p, r);
		QuickSort(data, p, q - 1);
		QuickSort(data, q + 1, r);
	}
	else if (p < r && check_qNum == 1)
	{
		q = Partition2(data, p, r);
		QuickSort(data, p, q - 1);
		QuickSort(data, q + 1, r);
	}
	else if (p < r && check_qNum == 2)
	{
		q = Partition3(data, p, r);
		QuickSort(data, p, q - 1);
		QuickSort(data, q + 1, r);
	}

	return clock() - clock_a;
}

int Partition1(int data[], int p, int r)
{

	int i = p - 1, j = p;

	for (j; j < r; j++) // pivot이 끝값일때 100,000개가 넘어가면 스택 오버플로우
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

int Partition2(int data[], int p, int r)
{

	int i = p - 1, j = p, mid = 0; // median of three

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

int Partition3(int data[], int p, int r)
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

void get_Bubble(int ind)
{
	int res, i;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Bubble(data1_cmp, data_size1);
	}
	result[0][ind] = (double)res / (1000 * 10);

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Bubble(data2_cmp, data_size2);
	}
	result[0][2 + ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Bubble(data3_cmp, data_size3);
	}
	result[0][2 + ind] = (double)res / 10000;
}

void get_Selection(int ind)
{
	int res, i;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Selection(data1_cmp, data_size1);
	}
	result[1][ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Selection(data2_cmp, data_size2);
	}
	result[1][2 + ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Selection(data3_cmp, data_size3);
	}
	result[1][4 + ind] = (double)res / 10000;
}

void get_Insertion(int ind)
{
	int res, i;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Insertion(data1_cmp, data_size1);
	}
	result[2][ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Insertion(data2_cmp, data_size2);
	}
	result[2][2 + ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += Insertion(data3_cmp, data_size3);
	}
	result[2][4 + ind] = (double)res / 10000;
}

void get_Merge(int ind)
{
	int i, res;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += MergeSort(data1_cmp, 0, data_size1 - 1);
	}
	result[3][0 + ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += MergeSort(data2_cmp, 0, data_size2 - 1);
	}
	result[3][2 + ind] = (double)res / 10000;

	for (i = 0, res = 0; i < 10; i++)
	{
		clock_a = clock();
		res += MergeSort(data3_cmp, 0, data_size3 - 1);
	}
	result[3][4 + ind] = (double)res / 10000;
}

void get_Quick(int ind)
{
	int i, j, res;

	for (j = 0; j < 3; j++)
	{
		for (i = 0, res = 0; i < 10; i++)
		{
			clock_a = clock();
			res += QuickSort(data1_cmp, 0, data_size1 - 1);
		}
		result[4 + j][0 + ind] = (double)res / 10000;

		check_qNum = 1;
		for (i = 0, res = 0; i < 10; i++)
		{
			clock_a = clock();
			res += QuickSort(data2_cmp, 0, data_size2 - 1);
		}
		result[4 + j][2 + ind] = (double)res / 10000;

		check_qNum = 2;
		for (i = 0, res = 0; i < 10; i++)
		{
			clock_a = clock();
			res += QuickSort(data3_cmp, 0, data_size3 - 1);
		}
		result[4 + j][4 + ind] = (double)res / 10000;
	}
}