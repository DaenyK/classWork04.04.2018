#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

unsigned short int q;

struct dob
{
	int year;
	int month;
	int day;
};



void main()

{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int bckr, t;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));


	srand(time(NULL));

	unsigned short int nz;

	do
	{
		cout << "введите номер задания: ";
		cin >> nz;
		cin.get();



		switch (nz)
		{
		case 1:
		{
			char s[80];
			int t;
			FILE *fp = NULL;

			if ((fp = fopen("test.txt", "w")) == NULL)
			{
				printf("error\n");
				exit(1);
			}
			else
			{
				//читать с клавиатуры
				printf("введите строку и число: ");
				fscanf(stdin, "%s - %d", s, &t);

				//писать в файл
				fprintf(fp, "# %d. %s", t, s);

				fclose(fp);

				if ((fp = fopen("test.txt", "r")) == NULL)
					exit(1);

				char name[80];
				int i = 0;
				fscanf(fp, "#%d. %s", &i, name);
				fprintf(stdout, "#%d. %s\n", i, name);
			}
		}break;

		case 2:
		{
			FILE *file;
			char words[40];
			if ((file = fopen("file.txt", "a+")) == NULL)
			{
				fprintf(stdout, "не удалось открыть файл\n");
				exit(1);
			}
			else
			{
				//аналог cout и printf
				puts("введите слова. нажмите enter");
				puts("в начале строки для завершения программы");

				//cin.getline
				while (gets_s(words) != NULL && words[0] != '\0')
				{
					fprintf(file, "%s", words);
				}

				puts("содержимое файла: ");
				//вернет указатель в анчало файла
				rewind(file);

				while (fscanf(file, "%s", words) == 1)
				{
					puts(words);
				}

				if (fclose(file) != 0)
					fprintf(stderr, "ошибка при закрытии файла\n");
			}
		}break;

		case 3:
		{
			FILE *pf;

			//КОГДА НЕ ЗНАЕШЬ ДЛИНЫ СТРОКИ В ФАЙЛЕ

			char buffer[10];
			char*input = NULL;
			size_t curLen = 0;

			int t = 0;

			while (fgets(buffer, sizeof(buffer), stdin) != 0)
			{
				size_t  bufLen = strlen(buffer);
				char *extra = (char*)realloc(input, bufLen + curLen + 1);

				if (extra == NULL)
					break;

				input = extra;
				strcpy(input + curLen, buffer);
				curLen += bufLen;
				t++;
				if (t > 3)
					break;
			}

			printf("%s [%d]", input, (int)strlen(input));
			free(input);
		}break;

		case 4:
		{
			FILE * file;

			double  d = 12.23, newD;
			int i = 101, newI;
			long l = 123023L, newL;

			if ((file = fopen("fReadFile", "wb+")) == NULL)
			{
				printf("error");
				exit(1);
			}
			else
			{
				fwrite(&d, sizeof(double), 1, file);
				fwrite(&i, sizeof(int), 1, file);
				fwrite(&l, sizeof(long), 1, file);

				//переход в начало
				rewind(file);

				fread(&newD, sizeof(double), 1, file);
				fread(&newI, sizeof(int), 1, file);
				fread(&newL, sizeof(long), 1, file);

				printf("%lf - %ld - %d", newD, newL, newI);

				fclose(file);
			}
		}break;

		case 11:
		{
			//1.	Дан файл, содержащий различные даты.Каждая дата - это число, месяц и год.Найти самую раннюю дату.
			FILE * DOB;
			int minY = 2018, minM = 12, minD = 30;
			int indexD;

			if ((DOB = fopen("dates.txt", "w")) == NULL)
			{
				printf("error");
				exit(1);
			}
			else
			{
				int a = 5 + rand() % 10;

				dob * YMD = NULL;
				YMD = (dob*)malloc(a * sizeof(dob));

				for (int i = 0; i < a; i++)
				{
					if (YMD == NULL)
					{
						printf("error\n");
						EXIT_FAILURE;
					}
					else
					{
						(YMD + i)->year = 2014 + rand() % 4;
						(YMD + i)->month = 1 + rand() % 12;
						(YMD + i)->day = 1 + rand() % 30;

						fprintf(DOB, "#%d \t %d.%d.%d\n", i + 1, (YMD + i)->day, (YMD + i)->month, (YMD + i)->year);
						//	printf("#%d \t %d.%d.%d\n", i + 1, (YMD + i)->day, (YMD + i)->month, (YMD + i)->year);

						fscanf(DOB, "#%d \t %d.%d.%d\n", i + 1, (YMD + i)->day, (YMD + i)->month, (YMD + i)->year);
						fprintf(stdout, "#%d \t %d.%d.%d\n", i + 1, (YMD + i)->day, (YMD + i)->month, (YMD + i)->year);

						if ((YMD + i)->year < minY)
						{
							minY = (YMD + i)->year;

							if ((YMD + i)->month < minM)
							{
								minM = (YMD + i)->month;
								if ((YMD + i)->day < minD)
								{
									minD = (YMD + i)->day;
									indexD = i;
								}
							}
						}
					}
				}
				printf("\nсамая ранняя дата: %d.%d.%d \n", (YMD + indexD)->day, (YMD + indexD)->month, (YMD + indexD)->year);
			}
			fclose(DOB);
		}break;


		}

		cout << "хотите продолжить 1/0?";
		cin >> q;

		switch (q)
		{
		case 1:
			system("cls");
			break;
		default:
			cout << "ошибка" << endl;
		}
	} while (nz > 0);


}