#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <clocale>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>



using namespace std;
int i, j, m, n, v;
int** graph;
int counter;
bool sr = false;
int nachalo;
int k, p;
int res;

void nt(){
	printf("\n\n\n\t\t\tЗдраствуйте\n");
	printf("\t\t    Это курсовая работа\n\n");
	printf("Тема: Реализация алогритма поиска независимых множеств рёбр графа\n\n\n\n\n");
	printf("\t\t\t\t\   Выполнил студент группы 22ВВС1\n");
	printf("\t\t\t\t\   Разин Д.С\n\n\n\n");
	printf("\t\t\tПриступим\n\n\n");
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	nt();
	k = 1;
	while (k == 1) {
		
		printf("Создание матрицы смежности\n");
		printf("Введите с клавиатуры желаемое количество вершин в матрице:  ");


		do { //функция для запрета ввода букв
			res = scanf("%d", &m);
			while (getchar() != '\n');
			if (res == 1) printf("\n");
			else printf("%s", "Ошибка введите количество вершин: ");

		} while (res != 1);

		while (m == 0 || m < 0) {
			printf("\nОшибка!!!\n");
			printf("Введите с клавиатуры количество вершин в матрице (больше нуля):  ");

			do {
				res = scanf("%d", &m);
				while (getchar() != '\n');
				if (res == 1) printf("\n");
				else printf("%s", "Ошибка введите количество вершин: ");

			} while (res != 1);

		}

		n = m;
		graph = new int* [m];
		for (int i = 0; i < m; i++) {
			graph[i] = new int[m];
		}
		int t;
		printf("Выберите способ создания матрицы смежности:\n");
		printf("1 - Автоматическая генерация\n2 - Ручной ввод\n> ");

		do { //функция для запрета ввода букв
			res = scanf("%d", &t);
			while (getchar() != '\n');
			if (res == 1) printf("\n");
			else {
				printf("%s", "Ошибка\n");
				printf("Выберите способ создания матрицы смежности:\n");
				printf("1 - Автоматическая генерация\n2 - Ручной ввод\n> ");
			}

		} while (res != 1);
		while (t != 1 && t != 2) {
			printf("Ошибка!!! Выберите способ создания матрицы смежности:\n");
			printf("1 - Автоматическая генерация\n2 - Ручной ввод\n> ");
			do { //функция для запрета ввода букв
				res = scanf("%d", &t);

				while (getchar() != '\n');
				if (res == 1) printf("\n");
				else {
					printf("%s", "Ошибка\n");
					printf("Выберите способ создания матрицы смежности:\n");
					printf("1 - Автоматическая генерация\n2 - Ручной ввод\n> ");
				}

			} while (res != 1);
		}
		if (t == 1) {
			srand(time(NULL));
			for (i = 0; i < m; ++i) {
				for (j = i; j < m; ++j) {
					graph[i][j] = graph[j][i] = rand() % 2;
				}
				graph[i][i] = 0; //обнуление вершины
			}
		}
		else {
			printf("Вводите элементы матрицы (0 и 1):\n");
			for (i = 0; i < m; ++i) {
				for (j = i; j < m; ++j) {
					if (i != j) {
					ret:
						printf("a[%d][%d] = ", i, j);
						do {
							res = scanf("%d", &graph[i][j]);
							while (getchar() != '\n');
							if (res == 1) printf("");
							else printf("%s", "Некоректный ввод. Введите занова: ");
						} while (res != 1);
						if (graph[i][j] > 1 || graph[i][j] < 0) {
							printf("\nНекорректный ввод!\n");
							goto ret;
						}
					}
				}
				graph[i][i] = 0;
			}
		}
		for (i = 0; i < n; i++) //отзеркаливание матрицы
		{
			for (j = 0; j < n; j++)
			{
				graph[j][i] = graph[i][j];
			}
		}




		printf("Матрица смежности: \n");
		//нумерование столбцов
		printf("\n     ");
		for (int i = 0; i < n; i++) {
			printf("[%d] ", i + 1);
		}

		printf("\n");

		//нумерование строк
		for (i = 0; i < m; ++i)
		{
			printf("[%d] ", i + 1);
			for (j = 0; j < m; ++j) {
				if ((i + 1) < 10)
				{
					if (j < 10)
						printf("%3d ", graph[i][j]);
					else
						printf(" %3d ", graph[i][j]);

				}

				else if ((i + 1) < 100)
				{
					if (j == 0)
						printf(" %d", graph[i][j]);
					else if (j < 10)
						printf("   %d", graph[i][j]);
					else
						printf("    %d", graph[i][j]);

				}

			}
			printf("\n");
		}

		printf("\nМатрица инцидентности: \n");
		int reb = 0;
		int ch = 0;

		while (ch != n)
			for (int i = 0; i < n; i++)
			{
				for (int j = 0 + ch; j < n; j++)
					if (graph[i][j] != 0)
						reb++;
				ch++;
			}
		/////

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (graph[i][j] != 0)
					graph[j][i] = 0;

		int** inc;

		inc = (int**)malloc(n * sizeof(int*));
		for (int i = 0; i < n; i++)
		{
			inc[i] = (int*)malloc(reb * sizeof(int));
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < reb; j++)
				inc[i][j] = 0;

		int	ch1 = reb;
		reb = 0;
		for (int i = 0; i < n; i++)				//создание матрицы инцидентности
		{
			for (int j = 0; j < n; j++)
				if (graph[i][j] != 0)
				{
					inc[i][reb] = 1;				//начало
					inc[j][reb] = 1;				//конец
					reb++;
				}
		}

		printf("\n    ");
		for (int i = 0; i < ch1; i++) {
			printf("[%d] ", i + 1);
		}
		for (int i = 0; i < n; i++)
		{
			printf("\n[%d]", i + 1);

			for (int j = 0; j < reb; j++)
			{
				if ((i + 1) < 10)
				{
					if (j < 10)
						printf("%3d ", inc[i][j]);
					else
						printf(" %3d ", inc[i][j]);

				}

				else if ((i + 1) < 100)
				{
					if (j == 0)
						printf(" %d", inc[i][j]);
					else if (j < 10)
						printf("   %d", inc[i][j]);
					else
						printf("    %d", inc[i][j]);

				}

			}
		}
		printf("\n");
		printf("Независимые рёбра: ");
		counter = 1;
		for (int i = 0; i < reb; i++) {
			for (int j = i + 1; j < reb; j++) {
				sr = false;

				for (int k = 0; k < n; k++) {
					if (inc[k][i] == 1 && inc[k][j] == 1) {
						sr = true;
					}
				}
				if (sr == false) {
					counter = 0;
					printf("\n%d - %d\n", i + 1, j + 1);


				}
			}
		}
		if (counter == 1) {
			printf("таких рёбер не встретилось");
		}


		printf("\n \n \n");
		printf("Если хотите начать программу занова нажмите: 1, если хотите закончить программу нажмите: 0 \n");
		printf("Если хотите вывести приветствие введите: 3 \n");
		
		do {
			res = scanf("%d", &nachalo);
			while (getchar() != '\n');
			while (nachalo != 1 && nachalo != 3 && nachalo != 0) {
				printf("Если хотите начать программу занова нажмите: 1, если хотите закончить программу нажмите: 0 \n");
				printf("Если хотите вывести приветствие введите: 3 \n");
				res = scanf("%d", &nachalo);

				if (nachalo == 3) {
					nt();
					printf("Если хотите начать программу занова нажмите: 1, если хотите закончить программу нажмите: 0 \n");
					printf("Если хотите вывести приветствие введите: 3 \n");
					res = scanf("%d", &nachalo);

				}

				if (res == 1) {
						if (nachalo != 1 || nachalo == 0) return 0;
						nachalo = k;
						if (k == 1) {
							k = true;
							system("cls");
						}					
				}
				else {
					nachalo = 99999;
					printf("Некоректный ввод. Если хотите начать программу занова нажмите: 1, а если хотите закончить программу нажмите: 0\n");
					printf("Если хотите вывести приветствие введите: 3 \n");
				}
			}
		} while (res != 1);
		
		
	}

	return 0;
}
