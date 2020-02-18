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

int* Generate_mas(int size, int min, int max)
{ 
	int* mas = (int*)malloc(size*sizeof(int));
	for (int i = 0; i < size; i++)
	{
		int r = min + rand() % (max-min+1);
		mas[i] = r;
	}
	return mas;
}

int* Generate_custom_mas(int size)
{
	int* mas = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		int r = 0;
		scanf("%d", &r);
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

int* Merge_sort(int* u, int* d, int l, int r)
/*
* Сортирует массив, используя рекурсивную сортировку слиянием
* u(up) - указатель на массив, который нужно сортировать
* d(down) - указатель на массив с, как минимум, таким же размером как у 'u', используется как буфер
* l(left) - левая граница массива, передайте 0, чтобы сортировать массив с начала
* r(right) - правая граница массива, передайте длину массива - 1, чтобы сортировать массив до последнего элемента
* возвращает: указатель на отсортированный массив. Из-за особенностей работы данной реализации
* отсортированная версия массива может оказаться либо в 'u', либо в 'd'
*/
{
	if (l == r)
	{
		d[l] = u[l];
		return d;
	}
	int m = (l + r) / 2;
	// разделение и сортировка
	int* l_buff = Merge_sort(u, d, l, m);
	int* r_buff = Merge_sort(u, d, m + 1, r);
	// слияние двух отсортированных половин
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

//сортировка обменом, проходим по массиву, меняем соселние элементы местами если один больше другого
// соотвественно на первой итерации на верх всплывает максимум и граница цикла уменьшается на один
void Bubble_sort(int mas[], int size)
{
	bool condition = false;
	for (int i = 0; i < size-1; i++)
	{
		condition = true;
		for (int j = 0; j < size - i -1;j++) // на каждой итерациии всплывает максимум
		{
			if (mas[j] > mas[j + 1]) //обмен между соседними если предыдущий больше последующего
			{
				int tmp = mas[j];
				mas[j] = mas[j + 1];
				mas[j+1] = tmp;
				condition = false; //Условие Айверсона пока не соблюдается
			}
		}
		if (condition)//выходим по условию если не было перестановок
			break;
	}
}

//Шейкерная сортировка, проходим по массиву обменом сначала в одну,потом в другую сторону и так чередуем
void Shaker_sort(int mas[], int size)
{
	bool condition = false;
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		bool condition = true;
		for (int i = left; i < right; i++) //Пузырьковая на максимум
		{
			if (mas[i] > mas[i + 1]) 
			{
				int tmp = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = tmp;
				condition = false; //Условие Айверсона пока не соблюдается
			}
		}
		right--;
		for (int i = right; i > left; i--) //Пузырьковая на минимум
		{
			if (mas[i-1] > mas[i]) 
			{
				int tmp = mas[i];
				mas[i] = mas[i - 1];
				mas[i - 1] = tmp;
				condition = false; //Условие Айверсона пока не соблюдается
			}
		}
		left++;
		if (condition)//выходим по условию если не было перестановок
			break;
	}
}

//Сортировка Шелла
void Shell_sort(int mas[], int size)
{
	bool condition = false;
	int d = size / 2; //шаг изначально в пол массива
	while(true)
	{
		condition = true;
		for (int j = 0; j < size - d; j++) 
		{
			if (mas[j] > mas[j + d]) //обмен между соседними по шагу d если предыдущий больше последующего
			{
				int tmp = mas[j];
				mas[j] = mas[j + d];
				mas[j + d] = tmp;
				condition = false; //Условие Айверсона пока не соблюдается
			}
		}
		if (d>1) //целочисленно делим шаг попалам, пока не станет 1 и сортировка не превратиться в пузырьковую
			d = d / 2;
		if (condition && d ==1)//выходим по условию если не было перестановок
			break;
	}
}

int main()
{
	srand(time(NULL));
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
				int c = 0;
				printf("\n1: Custom array from keyboard\n");
				printf("2: Random array with range\n");
				printf("3: Random array with default generation\n");
				printf("\nCmd: ");
				scanf("%d", &c);
				switch (c)
				{
				case 1:
					{
						printf("\nWrite size of array: ");
						scanf("%d", &tmp_size);
						size_arr = &tmp_size;
						mas = Generate_custom_mas(*size_arr);
						buff = (int*)malloc(*size_arr * sizeof(int));
						printf("\nUnsorted array: ");
						print_mas(mas, *size_arr);
						printf("\n");
						break;
					}
				case 2:
				{
					printf("\nWrite size of array: ");
					scanf("%d", &tmp_size);
					printf("\nWrite range of numbers in array");
					printf("\nMin: ");
					int min, max;
					scanf("%d", &min);
					printf("\nMax: ");
					scanf("%d", &max);
					size_arr = &tmp_size;
					mas = Generate_mas(*size_arr,min,max);
					buff = (int*)malloc(*size_arr * sizeof(int));
					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 3:
				{
					printf("\nWrite size of array: ");
					scanf("%d", &tmp_size);
					size_arr = &tmp_size;
					mas = Generate_mas(*size_arr, 0, 10);
					buff = (int*)malloc(*size_arr * sizeof(int));
					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				default:
					break;
				}
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
				printf("4:Merge sort\n");
				printf("5:Bubble sort\n");
				printf("6:Shaker sort\n");
				printf("7:Shell sort\n");
				printf("0:Cancel\n");
				printf("\nCmd: ");
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
				case 5:
				{

					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					Bubble_sort(mas, *size_arr);
					printf("\n");
					printf("Sorted array:   ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 6:
				{

					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					Shaker_sort(mas, *size_arr);
					printf("\n");
					printf("Sorted array:   ");
					print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 7:
				{

					printf("\nUnsorted array: ");
					print_mas(mas, *size_arr);
					Shell_sort(mas, *size_arr);
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