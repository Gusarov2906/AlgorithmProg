#include <stdlib.h>
#include<stdio.h>
void Selection_sort(int mas[], int size) //Сортировка выбором
//Проходим по всему массиву, ищем минимальный элемент, меняем iым если они разные, сдвигаем i, идем дальше
{

	for (int i = 0; i < size-1; i++)
	{
		int min = i;
		for (int j = i+1; j < size; j++)
		{
			if (mas[j] < mas[min])
				min = j;
		}

		if (min != i)
		{
			int tmp = mas[i];
			mas[i] = mas[min];
			mas[min] = tmp;
			min = i;
		}
	}

}

void print_mas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", mas[i]);
	}
}

int main()
{
	int arr[10] = {2,1,8,4,5,6,9,10,3,7};
	Selection_sort(arr, 10);
	print_mas(arr, 10);
}