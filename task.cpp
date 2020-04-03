#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
»спользу€ генератор случайных чисел, смоделировать процесс
парковки автомобилей коммерческой фирмы у тротуара. 
ƒлина тротуара D, длина автомобил€ N
*/

void print_mas(int mas[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", mas[i]);
	}
	printf("\n");
}

int main()
{
	double D = 0, N = 0;
	int n = 0;
	srand(time(NULL));
	int* arr = (int*)malloc(1 * sizeof(int));
	printf("Andrey Gusarov PIN-24 LAB1 \nTASK:\nUsing a random number generator, simulate a process\nparking of cars of a commercial company at the sidewalk.\nSidewalk length D, car length N \n#Programm working in cycle, if u want to stop write 0 in dimensions.\n");
	while (true)
	{
		printf("\nWrite length of sidewalk(D): ");
		scanf("%lf", &D);
		printf("Write length of car(N): ");
		scanf("%lf", &N);
		if (D == 0 || N == 0)
			break;
		n = D / N;
		arr = (int*)realloc(arr, n * sizeof(int));
		for (int i = 0; i < n; i++)
			arr[i] = 0;
		printf("\nNumbers of parking spaces: %d \n", n);
		if (n >= 1)
		{
			int j = 0;
			for (int i = 1; i <= n; i++)
			{
				while (true)
				{
					j = rand() % n;
					if (arr[j] == 0)
					{
						arr[j] = i;
						break;
					}
				}
			}
			printf("Sidewalk: ");
			print_mas(arr, n);

		}
	}
}