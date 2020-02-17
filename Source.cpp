#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<stdio.h>
#include <time.h>


void print_mas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", mas[i]);
	}
	printf("\n");
}

int* Generate_mas(int size)
{ 
	int* mas = (int*)malloc(size*sizeof(int));
	for (int i = 0; i < size; i++)
	{
		int r = rand() % 100;
		mas[i] = r;
	}
	return mas;
}

void Selection_sort(int mas[], int size) //���������� �������
//�������� �� ����� �������, ���� ����������� �������, ������ i�� ���� ��� ������, �������� i, ���� ������
{

	for (int i = 0; i < size-1; i++)
	{
		int min = i; 
		for (int j = i+1; j < size; j++) //���� ���������� ������� ���� �� �� i��
		{
			if (mas[j] < mas[min])
				min = j;
		}

		if (min != i) //� ������ ���� �� �� i�� ������ ��� � i�� �������
		{
			int tmp = mas[i];
			mas[i] = mas[min];
			mas[min] = tmp;
			min = i;
		}
	}

}

void Insertion_sort(int mas[], int size) //���������� ��������
// �������� �� ������� ���� ����������� �� �������, ���� �� �������� ������� �������� ���������
// �������� ��� �������� ������� ������, ����� ������� ����������� ��� ������� �����(��-�� ������ ����� ���
// �� ������ ������
// ��������� ���� �� 1 �� ������ ���������� ���������
{
	for (int i = 1; i < size; i++)
	{
		int key = mas[i]; //���� i�� �������, ����������� � ������ �������� �����
		int j = i - 1; // j ���� �� i �� ����
		while (j >= 0 and mas[j] > key) //���� ����� ���� �������� ����
		{
			mas[j + 1] = mas[j]; //����� ���� ���������
			j = j - 1;
		}
		mas[j + 1] = key; //��������� ���� �� �������������� �����(��������� ������)
	}
}

void Binary_insertion_sort(int mas[], int size) //���������� �������� ��������
{

	for (int i = 1; i < size; i++)
	{
		int key = mas[i];//����, ������� ������������
		int l = 0; //������ ������� �������
		int h = i - 1; //������� ������� �������
		int m = 0; //������
		while (l < h)
		{
			if (key >= mas[m]) //���� ������ �������� ��� �������
				l = m + 1;
			else
				h = m;
			m = l + (h - l) / 2;
		}
		if (mas[i] > mas[m])
			m += 1;
		int result = mas[i]; //��������� ������ ��������
		for (int k = i; k > m; k--) //�������� ��� �������� ����� ������� ������
		{
			mas[k] = mas[k - 1];
		}
		mas[m] = result; //���������� ����������� �������� � ������(��������� ������) �����
	}
}

int* Merge_sort(int* u, int* d, int l, int r)
/*
* ��������� ������, ��������� ����������� ���������� ��������
* u(up) - ��������� �� ������, ������� ����� �����������
* d(down) - ��������� �� ������ �, ��� �������, ����� �� �������� ��� � 'u', ������������ ��� �����
* l(left) - ����� ������� �������, ��������� 0, ����� ����������� ������ � ������
* r(right) - ������ ������� �������, ��������� ����� ������� - 1, ����� ����������� ������ �� ���������� ��������
* ����������: ��������� �� ��������������� ������. ��-�� ������������ ������ ������ ����������
* ��������������� ������ ������� ����� ��������� ���� � 'u', ���� � 'd'
*/
{
	if (l == r)
	{
		d[l] = u[l];
		return d;
	}
	int m = (l + r) / 2;
	// ���������� � ����������
	int* l_buff = Merge_sort(u, d, l, m);
	int* r_buff = Merge_sort(u, d, m + 1, r);
	// ������� ���� ��������������� �������
	int* target = l_buff == u ? d : u;
	int l_cur = l, r_cur = m + 1;
	for (int i = l; i <= r; i++)
	{
		if (l_cur <= m && r_cur <= r)
		{
			if (l_buff[l_cur] < r_buff[r_cur])
			{
				target[i] = l_buff[l_cur];
				l_cur++;
			}
			else
			{
				target[i] = r_buff[r_cur];
				r_cur++;
			}
		}
		else if (l_cur <= m)
		{
			target[i] = l_buff[l_cur];
			l_cur++;
		}
		else
		{
			target[i] = r_buff[r_cur];
			r_cur++;
		}
	}
	return target;
}


int main()
{
	srand(time(NULL));
	/*const int size_arr = 10;
	int arr[size_arr] = {2,1,8,4,5,6,9,10,3,7};
	Selection_sort(arr, size_arr);
	print_mas(arr, size_arr);
	int arr1[size_arr] = { 2,1,8,4,5,6,9,10,3,7 };
	Insertion_sort(arr1, size_arr);
	print_mas(arr1, size_arr);
	int arr2[size_arr] = { 2,1,8,4,5,6,9,10,3,7 };
	Binary_insertion_sort(arr2, size_arr);
	print_mas(arr2, size_arr);
	*/
	/*
	const int size_arr = 10;
	int* mas = Generate_mas(size_arr);
	int buff[size_arr] = {};
	printf("\n");
	printf("Unsorted array: ");
	print_mas(mas, size_arr);
	Selection_sort(mas, size_arr);
	printf("Sorted array:   ");
	print_mas(mas, size_arr);
	mas = Generate_mas(size_arr);
	printf("\n");
	printf("Unsorted array: ");
	print_mas(mas, size_arr);
	Insertion_sort(mas, size_arr);
	printf("Sorted array:   ");
	print_mas(mas, size_arr);
	printf("\n");
	mas = Generate_mas(size_arr);
	printf("Unsorted array: ");
	print_mas(mas, size_arr);
	mas = Merge_sort(mas,buff,0,size_arr-1);
	printf("Sorted array:   ");
	print_mas(mas, size_arr);
	printf("\n");
	*/
	printf("***************************\nPROGRAM FOR LAB1 ALGORITHMS\n***************************\n");
	int n=0, tmp_size=0;
	int* mas = {};
	const int* size_arr;
	size_arr = 0;
	int* buff = {};
	bool exit_f = false;
	while (1)
	{
		if (exit_f)
		{
			break;
		}
		printf("1: Generate new array\n");
		printf("2: Sort array\n");
		printf("0: Exit\n");
		printf("\nCmd: ");
		scanf("%d", &n);
		switch (n)
		{
			case 1:
			{
				printf("\nWrite size of array: ");
				scanf("%d", &tmp_size);

				size_arr = &tmp_size;
				mas = Generate_mas(*size_arr);
				buff = (int*)malloc(*size_arr * sizeof(int));
				printf("\nUnsorted array: ");
				print_mas(mas, *size_arr);
				printf("\n");
				break;
			}

			case 2:
			{
				if (!mas)
				{
					printf("\nNot generated array!\n\n");
					break;
				}
				printf("\n1:Selection sort\n");
				printf("2:Insertion sort\n");
				printf("3:Binary insertion sort\n"); 
				printf("4:Merge sort\n\n");
				printf("Cmd: ");
				int cmd = 0;
				scanf("%d", &cmd);
				switch (cmd)
				{
				case 1:
				{
					
					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					Selection_sort(mas, *size_arr);
					printf("Sorted array:   ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 2:
				{
					
					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					Insertion_sort(mas, *size_arr);
					printf("\n");
					printf("Sorted array:   ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 3:
				{
					
					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					Binary_insertion_sort(mas, *size_arr);
					printf("\n");
					printf("Sorted array:   ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 4:
				{
					
					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					mas = Merge_sort(mas, buff, 0, *size_arr - 1);
					printf("\n");
					printf("Sorted array:   ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				default:
					break;
				}
				break;
			}
		case 0:
			exit_f = true;

		default:
			break;
		}
	}

}