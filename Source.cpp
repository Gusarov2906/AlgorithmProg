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

void Selection_sort(int mas[], int size) //Сортировка выбором
//Проходим по всему массиву, ищем минимальный элемент, меняем iым если они разные, сдвигаем i, идем дальше
{

	for (int i = 0; i < size-1; i++)
	{
		int min = i; 
		for (int j = i+1; j < size; j++) //ищем минмальный элемент если он не iый
		{
			if (mas[j] < mas[min])
				min = j;
		}

		if (min != i) //в случае если он не iый меняем его с iым местами
		{
			int tmp = mas[i];
			mas[i] = mas[min];
			mas[min] = tmp;
			min = i;
		}
	}

}

void Insertion_sort(int mas[], int size) //Сортировка вставкой
// Начинаем со второго шага проходиться по массиву, пока не найдется элемент большего ключевого
// сдвигаем все элементы массива вправо, когда нашелся присваиваем ему текущее место(из-за сдвига перед ним
// не теряем данные
// Повторяем цикл от 1 до номера количества элементов
{
	for (int i = 1; i < size; i++)
	{
		int key = mas[i]; //ключ iый элемент, обновляется в каждой итерации цикла
		int j = i - 1; // j двиг от i на один
		while (j >= 0 and mas[j] > key) //ищем место куда вставить ключ
		{
			mas[j + 1] = mas[j]; //сдвиг всех элементов
			j = j - 1;
		}
		mas[j + 1] = key; //вставляем ключ на освободившееся место(логически пустое)
	}
}

void Binary_insertion_sort(int mas[], int size) //Сортировка бинарной вставкой
{

	for (int i = 1; i < size; i++)
	{
		int key = mas[i];//ключ, который сравнивается
		int l = 0; //нижняя граница области
		int h = i - 1; //верхняя граница облпсти
		int m = 0; //маркер
		while (l < h)
		{
			if (key >= mas[m]) //ищем нужное значение для маркера
				l = m + 1;
			else
				h = m;
			m = l + (h - l) / 2;
		}
		if (mas[i] > mas[m])
			m += 1;
		int result = mas[i]; //сохраняем нужное значение
		for (int k = i; k > m; k--) //сдвигаем все значения после маркера вправо
		{
			mas[k] = mas[k - 1];
		}
		mas[m] = result; //записываем сохраненное значение в пустое(логически пустое) место
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