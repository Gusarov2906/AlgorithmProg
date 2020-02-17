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
	const int size_arr = 10;
	int* mas = Generate_mas(size_arr);
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
	Binary_insertion_sort(mas, size_arr);
	printf("Sorted array:   ");
	print_mas(mas, size_arr);
	printf("\n");

}