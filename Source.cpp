﻿#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int pow(int val, int n)
{
	int res = 1;
	for (int i = 0; i < n; i++)
		res *= val;
		return res;
}

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

int* Rand_mid_square_method(int size, int n, int x)
{
	int* mas = (int*)malloc(size * sizeof(int));
	mas[0] = x;
	int y;
	for (int i = 1; i < size; i++)
	{
		y = x*x;
		x = (y / pow(10,n/2)) % pow(10,n);
		mas[i] = x;
	}
	print_mas(mas, size);
	return mas;
}

void Rand_linear_congruential_method(int size,int b, int x, int k, int m)
{
	double* mas = (double*)malloc(size * sizeof(double));
	int tmp = (b * x + k) % m ;
	mas[0] = (float)tmp / m;
	for (int i = 1; i < size; i++)
	{
		tmp = (b * tmp + k) % m;
		mas[i] = (float)tmp / m;
	}
	for (int i = 0; i < size; i++)
	{
		printf("%lf ", mas[i]);
	}
}

void Polar_method(int size)
{
	srand(time(NULL));
	double* mas = (double*)malloc((size+1) * sizeof(double));
	double u1, u2, v1, v2, s = 1;
	int j = 0;
	for (int i = 0; i < (size+1)/2; i++)
	{
		while (s >= 1)
		{
			u1 = double(rand()) / RAND_MAX;
			u2 = double(rand()) / RAND_MAX;
			v1 = 2 * u1 - 1;
			v2 = 2 * u2 - 1;
			s = v1 * v1 + v2 * v2;
		}
		double n = sqrt((-2 * log(s)) / s);
//		printf("%lf  %lf",v1* n ,v2 * n );
		mas[j] = v1 * n;
		mas[j + 1] = v2 * n;
		j += 2;
		s = 1;
	}
	for (int i = 0; i < size;i++)
	{
		printf("%lf  ", mas[i]);
	}
}


int* Copy_mas(int* mas, int size)
{
	int* new_mas = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		new_mas[i] = mas[i];
	}
	return new_mas;
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

/*
algorithm partition(A, low, high) is
	pivot := A[(low + high) / 2]
	i := low - 1
	j := high + 1
	loop forever
		do
			i := i + 1
		while A[i] < pivot

		do
			j := j - 1
		while A[j] > pivot

		if i >= j then
			return j

		swap A[i] with A[j]*/


void Quick_sort(int mas[], int l, int h)
{
	int index = (l + h) / 2;
	int pivot = mas[index];
	int tmp;
	int i = l;
	int j = h;
	do {
		while (mas[i] < pivot)
			i++;
		while (mas[j] > pivot)
			j--;

		if (i <= j)
		{
			if (i < j)
			{
				tmp = mas[i];
				mas[i] = mas[j];
				mas[j] = tmp;
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < h)
		Quick_sort(mas, i, h);
	if (l < j)
		Quick_sort(mas, l, j);
	}


/*
int* Sort(int* A, int size) {

	int* tree = new int[size * 2];
	int i;

	int k, j = 0;

	while (j < N) {
		tree[size + j] = A[j];
		++j;
	}

	j = size;
	while (j < 2 * size)
	{
		if (tree[j] >= tree[j + 1])  tree[j / 2] = j;
		else  tree[j / 2] = j + 1;
		j += 2;
	}

	k = size / 2;
	while (k >= 1)
	{
		j = k;
		while (j < 2 * k)
		{
			if (tree[tree[j]] >= tree[tree[j + 1]])
				tree[j / 2] = tree[j];
			else  tree[j / 2] = tree[j + 1];
			j += 2;
		}
		k /= 2;
	}

	for (k = N; k >= 2; --k)
	{
		i = tree[1];
		A[k - 1] = tree[i];
		tree[i] = -MAXINT;


		if (i % 2)  tree[i / 2] = i - 1;
		else  tree[i / 2] = i + 1;

		i /= 2;

		while (i > 1)
		{ //j - ápàò i.
			if (i % 2)  j = i - 1;
			else  j = i + 1;
			if (tree[tree[i]] > tree[tree[j]])  tree[i / 2] = tree[i];
			else  tree[i / 2] = tree[j];
			i /= 2;
		}
	}
	A[0] = tree[tree[1]];
	return A;
}
*/

int Sequential_search(int mas[], int size, int val)
{
	for (int i = 0; i < size; i++)
	{
		if (mas[i] == val)
		{
			printf("Successful! Num is %d number (starts from 0) in array.\n", i);
			return i;
		}
	}
	printf("There is no match in array\n");
	return NULL;
}

int Binary_search(int mas[], int size, int val)
{
	int l = 0;
	int r = size;
	int m = 0;
	while (l < r)
	{
		m = l + (r - l) / 2;
		if (mas[m] == val)
		{
			printf("Successful! Num is %d number (starts from 0) in array.\n", m);
			return m;
		}
		if (mas[m] > val)
			r = m;
		else
			l = m + 1;
	}
	printf("There is no key in array\n");
	return NULL;
}

int fibonacchi(int n) {
	if (n == 0) return 0;

	if (n == 1) return 1;
	return fibonacchi(n - 2) + fibonacchi(n - 1);
}

int Fibonachi_search(int mas[], int l,int r, int val)
{
	int k = 1;
	int i = 0;

	while (true)
	{
		i = l + fibonacchi(k)-1;

		if (mas[i] == val)
		{
			printf("Successful! Num is %d number (starts from 0) in array.\n", i);
			return i;
		}
		if (i == r)
		{
			printf("There is no key in array\n");
			return NULL;
		}
		if ((mas[i] < val))
		{
			if (i < r)
			k++;
			else
				return Fibonachi_search(mas,l+ fibonacchi(k - 1), r, val);

		}
		else
		{
			return Fibonachi_search(mas,l+ fibonacchi(k - 1), i, val);
		}
	}
}

int Interpolation_search(int mas[], int size, int val)
{
	int l = 0;
	int r = size;
	int m;
	while ((mas[l] < val) && (val < mas[r]))
	{
		m = l + (val - mas[l]) * (r - l) / (mas[r] - mas[l]);
		if (mas[m] < val)
			l = m + 1;
		else if (mas[m] > val)
			r = m - 1;
		else
		{
			printf("Successful! Num is %d number (starts from 0) in array.\n", m);
			return m;
		}
	}
	if (mas[l] == val)
	{
		printf("Successful! Num is %d number (starts from 0) in array.\n", l);
		return l;
	}
	else if (mas[r] == val)
	{
		printf("Successful! Num is %d number (starts from 0) in array.\n", r);
		return r;
	}
	else
	{
		printf("There is no key in array\n");
		return NULL;
	}
}

struct Node
{
	float data;
	Node* left;
	Node* right;
};

Node* tree;

void add(Node* r, float d)
{
	Node* tmp;
	if (r == NULL)
	{
		tree = new Node;
		tree->data = d;
		tree->left = NULL;
		tree->right = NULL;
		return;
	}
	if (d <= r->data)
	{
		// left
		if (r->left != NULL)
			add(r->left, d);
		else
		{
			tmp = new Node;
			tmp->data = d;
			tmp->left = NULL;
			tmp->right = NULL;
			r->left = tmp;
		}
	}
	else
	{
		//right
		if (r->right)
			add(r->right, d);
		else
		{
			tmp = new Node;
			tmp->data = d;
			tmp->left = NULL;
			tmp->right = NULL;
			r->right = tmp;
		}
	}
}

void print(Node* s, int level, int l, int r)
{
	if (s == NULL)
	{
		printf("Tree is empty!!!\n");
		return;
	}
	int c = (l + r) / 2;
	if (s->left)
		print(s->left, level + 1, l, c);
	if (s->right)
		print(s->right, level + 1, c, r);

	return;
}

int Binary_tree_search(Node* r, float d)
{
	if (r == NULL)
	{
		printf("Not found!\n");
		return 0;

	}
	if (r->data == d)
	{
		printf("Successful!\n");
		return 1;
	}

	if (d <= r->data)
	{
		// left
		if (r->left != NULL)
			return Binary_tree_search(r->left, d);
		else
		{
			printf("Not found!\n");
			return 0;

		}
	}
	else
	{
		//right
		if (r->right)
			return Binary_tree_search(r->right, d);
		else
		{
			printf("Not found!\n");
			return 0;

		}
	}
}

/*
bool Hashing_search(int* mas,int size, int val)
{
	bool answer = false;
	int max_key = 0;
	for (int i = 0; i < size; i++)
		if (mas[i] > max_key) max_key = mas[i];
	int m = max_key / 2;

	int** matrix = (int**)malloc(m*sizeof(int));
	for (int i = 0; i < m; i++)
	{
		matrix[i] = (int*)malloc(1* sizeof(int));
		matrix[i][0] = 1;
	}


	int key_hash = val % m;
	for (int i = 1; i < matrix[key_hash][0]; i++)
	{
		if (matrix[key_hash][i] == val) answer = true;
	}

	for (int i = 0; i < m; i++)
		delete matrix[i];

	return answer;
}
*/
bool Is_sorted(int mas[], int size)
{
	for (int i = 0; i < size - 1; i++)
		if (!(mas[i] <= mas[i + 1]))
			return false;
	return true;
}

bool Protection_for_sorted_array(int mas[], int size)
{
	if (!Is_sorted(mas, size))
	{
		printf("\nArray not sorted, please sort array before this search!\n");
		return false;
	}
	else
		return true;
}


void Selection_sort_case(int* mas, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	Selection_sort(mas, size);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");

}

void Insertion_sort_case(int* mas, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	Insertion_sort(mas, size);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");

}

void Binary_insertion_sort_case(int* mas, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	Binary_insertion_sort(mas, size);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");

}

int* Merge_sort_case(int* mas, int* buff, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	mas = Merge_sort(mas, buff, 0, size-1);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
	return mas;
}

void Bubble_sort_case(int* mas, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	Bubble_sort(mas, size);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");

}

void Shaker_sort_case(int* mas, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	Shaker_sort(mas, size);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");

}

void Shell_sort_case(int* mas, int size, clock_t time)
{
	//	printf("\nUnsorted array: ");
			//	print_mas(mas, *size_arr);
	time = clock();
	Shell_sort(mas, size);
	time = clock() - time;
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
	
}

void Quick_sort_case(int* mas, int size, clock_t time)
{
	time = clock();
	Quick_sort(mas, 0, size - 1);
	time = clock() - time;
	printf("\n");
	//	printf("Sorted array:   ");
	//	print_mas(mas, *size_arr);
	printf("\n");
	printf("Time of sort %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
}

void Sequential_search_case(int* mas,int size, clock_t time, int val)
{
	time = clock();
	Sequential_search(mas, size, val);
	time = clock() - time;
	printf("\n");
	printf("Time of search %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
}

void Binary_search_case(int* mas, int size, clock_t time, int val)
{
	time = clock();
	Binary_search(mas, size, val);
	time = clock() - time;
	printf("\n");
	printf("Time of search %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
}

void Fibonachi_search_case(int* mas, int size, clock_t time, int val)
{
	time = clock();
	Fibonachi_search(mas,0, size-1, val);
	time = clock() - time;
	printf("\n");
	printf("Time of search %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
}

void Interpolation_search_case(int* mas, int size, clock_t time, int val)
{
	time = clock();
	Interpolation_search(mas, size-1, val);
	time = clock() - time;
	printf("\n");
	printf("Time of search %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
}

void Binary_tree_search_case(int* mas, int size, clock_t time, int val)
{
	time = clock();
	for (int i = 0; i < size; i++)
	{
		add(tree, float(mas[i]));
	}
	Binary_tree_search(tree, float(val));
	time = clock() - time;
	printf("\n");
	printf("Time of search %f seconds", double(time) / CLOCKS_PER_SEC);
	//printf("%f", double(time) / CLOCKS_PER_SEC);
	printf("\n");
}

void Sort_test_case(int* mas, int* buff, int size, clock_t time)
{
	printf("\nSort test for array with %d numbers.\n", size);
	printf("\nSelection sort:");
	int* tmp = Copy_mas(mas, size);
	Selection_sort_case(tmp, size, time);
	printf("\nInsertion sort:");
	tmp = Copy_mas(mas, size);
	Insertion_sort_case(tmp, size, time);
	printf("\nBinary insertion sort:");
	tmp = Copy_mas(mas, size);
	Binary_insertion_sort_case(tmp, size, time);
	printf("\nMerge sort:");
	tmp = Copy_mas(mas, size);
	tmp = Merge_sort_case(tmp, buff, size, time);
	printf("\nBubble sort:");
	tmp = Copy_mas(mas, size);
	Bubble_sort_case(tmp, size, time);
	printf("\nShaker sort:");
	tmp = Copy_mas(mas, size);
	Shaker_sort_case(tmp, size, time);
	printf("\nShell sort:");
	tmp = Copy_mas(mas, size);
	Shell_sort_case(tmp, size, time);
	printf("\nQuick sort:");
	tmp = Copy_mas(mas, size);
	Quick_sort_case(tmp, size, time);
}

void Search_test_case(int* mas, int size, clock_t time, int val)
{
	printf("\nSequential search:\n");
	Sequential_search_case(mas, size, time, val);
	printf("\nBinary search:\n");
	Binary_search_case(mas, size, time, val);
	printf("\nFibonachi search:\n");
	Fibonachi_search_case(mas, size, time, val);
	printf("\nInterpolation search:\n");
	Interpolation_search_case(mas, size, time, val);
	printf("\nInterpolation search:\n");
	Binary_tree_search_case(mas, size, time, val);

}
int main()
{
	srand(time(NULL));
	clock_t time = 0;
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
		printf("\n1: Generate new array\n");
		printf("2: Show array\n");
		printf("3: Sort array\n");
		printf("4: Find in array\n");
		printf("5: Tests\n");
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
				printf("4: Choose method of random generation\n");
				printf("0: Cancel\n");
				printf("\nCmd: ");
				scanf("%d", &c);
				switch (c)
				{
				case 1:
					{
						printf("\nWrite size of array: ");
						scanf("%d", &tmp_size);
						size_arr = &tmp_size;
						printf("\nWrite custom array with %d numbers.\nArray: ",tmp_size);
					//	start = clock();
						mas = Generate_custom_mas(*size_arr);
					//	stop = clock();
						buff = (int*)malloc(*size_arr * sizeof(int));
						printf("\nUnsorted array: ");
					//	print_mas(mas, *size_arr);
						printf("\n");
					//	printf("Time to create %f seconds", (stop - start) / CLK_TCK);
						break;
					}
				case 2:
				{
					printf("\nWrite size of array: ");
					scanf("%d", &tmp_size);
					printf("\nWrite range of numbers in array\n");
					printf("\nMin: ");
					int min, max;
					scanf("%d", &min);
					printf("\nMax: ");
					scanf("%d", &max);
					size_arr = &tmp_size;
					printf("\n");
					mas = Generate_mas(*size_arr,min,max);
					buff = (int*)malloc(*size_arr * sizeof(int));
					//printf("\nUnsorted array: ");
					//print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 3:
				{
					printf("\nWrite size of array: ");
					scanf("%d", &tmp_size);
					size_arr = &tmp_size;
					mas = Generate_mas(*size_arr, 1, 10);
					buff = (int*)malloc(*size_arr * sizeof(int));
					//printf("\nUnsorted array: ");
					//print_mas(mas, *size_arr);
					printf("\n");
					break;
				}
				case 4:
				{
					printf("\n1: Middle-square method\n");
					printf("2: Linear congruential method\n");
					printf("3: Polar method\n");
					printf("0: Cancel\n");
					printf("\nCmd: ");
					int cmd = 0;
					scanf("%d", &cmd);
					switch (cmd)
					{
					case 1:
					{

						printf("\nWrite size of array: ");
						scanf("%d", &tmp_size);
						size_arr = &tmp_size;
						printf("\nWrite parametrs of rande generation\n");
						printf("\nn: ");
						int x0;
						scanf("%d", &n);
						printf("\nx0: ");
						scanf("%d", &x0);
						mas = Rand_mid_square_method(*size_arr, n, x0);
						buff = (int*)malloc(*size_arr * sizeof(int));
						break;
					}
					case 2:
					{

						printf("\nWrite size of array: ");
						scanf("%d", &tmp_size);
						size_arr = &tmp_size;
						printf("\nWrite parametrs of rande generation\n");
						printf("\nb: ");
						int b, x, k, m;
						scanf("%d", &b);
						printf("\nx: ");
						scanf("%d", &x);
						printf("\nk: ");
						scanf("%d", &k);
						printf("\nm: ");
						scanf("%d", &m);
						Rand_linear_congruential_method(*size_arr, b, x, k, m);
						buff = (int*)malloc(*size_arr * sizeof(int));
						break;
					}
					case 3:
					{
						printf("\nWrite size of array: ");
						scanf("%d", &tmp_size);
						size_arr = &tmp_size;
						Polar_method(*size_arr);
						printf("\n");
						break;
					}

					default:
						break;
					}
				}
				default:
					break;
				}
				break;
			}
			case 2: {
				if (!mas)
				{
					printf("\nNot generated array!\n\n");
					break;
				}
				printf("\nCurrent array:\n");
				print_mas(mas, *size_arr);
				break;
			}
			case 3:
			{
				if (!mas)
				{
					printf("\nNot generated array!\n\n");
					break;
				}
				printf("\n1: Selection sort\n");
				printf("2: Insertion sort\n");
				printf("3: Binary insertion sort\n"); 
				printf("4: Merge sort\n");
				printf("5: Bubble sort\n");
				printf("6: Shaker sort\n");
				printf("7: Shell sort\n");
				printf("8: Quick sort\n");
				printf("0: Cancel\n");
				printf("\nCmd: ");
				int cmd = 0;
				scanf("%d", &cmd);
				switch (cmd)
				{
				case 1:
				{
					
					Selection_sort_case(mas, *size_arr, time);
					break;
				}
				case 2:
				{
					Insertion_sort_case(mas, *size_arr, time);
					break;
				}
				case 3:
				{
					
				Binary_insertion_sort_case(mas, *size_arr, time);
					break;
				}
				case 4:
				{
					
					mas = Merge_sort_case(mas, buff, *size_arr, time);
					break;
				}
				case 5:
				{

					Bubble_sort_case(mas, *size_arr, time);
					break;
				}
				case 6:
				{

					Shaker_sort_case(mas, *size_arr, time);
					break;
				}
				case 7:
				{
					Shell_sort_case(mas, *size_arr, time);
					break;
				}
				case 8:
				{

				Quick_sort_case(mas, *size_arr, time);
					break;
				}
				default:
					break;
				}
				break;
			}
		case 4:
		{
			if (!mas)
			{
				printf("\nNot generated array!\n\n");
				break;
			}
			printf("\n1: Sequential search\n");
			printf("2: Binary search\n");
			printf("3: Fibonachi search\n");
			printf("4: Interpolation search\n");
			printf("5: Binary tree search\n");
			printf("0: Cancel\n");
			printf("\nCmd: ");
			int cmd = 0;
			scanf("%d", &cmd);
			switch (cmd)
			{
			case 1:
			{
				if (!Protection_for_sorted_array(mas, *size_arr))
					break;
				printf("\nWrite key to search: ");
				int val;
				scanf("%d", &val);
				Sequential_search_case(mas, *size_arr, time, val);
				break;
			}
			case 2:
			{
				if (!Protection_for_sorted_array(mas, *size_arr))
					break;
				printf("\nWrite key to search: ");
				int val;
				scanf("%d", &val);
				Binary_search_case(mas, *size_arr, time, val);
				break;
			}
			case 3:
			{
				if (!Protection_for_sorted_array(mas, *size_arr))
					break;
				printf("\nWrite key to search: ");
				int val;
				scanf("%d", &val);
				Fibonachi_search_case(mas, *size_arr, time,val);
				break;
			}
			case 4:
			{
				if (!Protection_for_sorted_array(mas, *size_arr))
					break;
				printf("\nWrite key to search: ");
				int val;
				scanf("%d", &val);
				Interpolation_search_case(mas, *size_arr, time,val);
				break;
			}
			case 5:
			{
				if (!Protection_for_sorted_array(mas, *size_arr))
					break;
				printf("\nWrite key to search: ");
				int val;
				scanf("%d", &val);
				Binary_tree_search_case(mas, *size_arr, time, val);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 5:
		{
		
			printf("1: Sort test\n");
			printf("2: Search test\n");
			printf("0: Cancel\n");
			printf("\nCmd: ");
			int cmd = 0;
			scanf("%d", &cmd);
			switch (cmd)
			{
			case 1:
			{
				if (!mas)
				{
					printf("\nNot generated array!\n\n");
					break;
				}
				Sort_test_case(mas, buff, *size_arr, time);
				break;
			}
			case 2:
			{
				if (!mas)
				{
					printf("\nNot generated array!\n\n");
					break;
				}
				if (!Protection_for_sorted_array(mas, *size_arr))
					break;
				printf("\nSearch test for array with %d numbers.\n", *size_arr);
				printf("\nWrite key to search: ");
				int val;
				scanf("%d", &val);
				Search_test_case(mas, *size_arr, time, val);
				break;
			}
			case 3:
			{
				for (int n = 5000; n < 30000; n += 5000)
				{
					mas = Generate_mas(n, 1, 100);
					buff = (int*)malloc(n * sizeof(int));
					Sort_test_case(mas, buff, n, time);
				}

				for (int n = 10000; n < 200000; n += 10000)
				{
					mas = Generate_mas(n, 1, 100);
					buff = (int*)malloc(n * sizeof(int));
					Quick_sort(mas, 0, n - 1);
					printf("\nSearch test for array with %d numbers.\n", n);
					Search_test_case(mas, n, time, 58);
				}
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