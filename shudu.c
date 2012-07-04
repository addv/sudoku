/****************************************************************************
 * FileName   : shudu.c
 * ProjectType: Win32 Console Application
 * Platform   : Microsoft Visual C++ 6.0
 * Version    : 1.0
 * Author     : AddV
 * Date       : 2012.7.2
 * Description: solve a Sudoku question from web, said a finlander provide
 * Usage      : enter number to array and then compile and run
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <memory.h>

int check_no_conflict(const char* const arr);
int test(char arr[], char* r);
void print_start(char const arr[][9]);
void print_result(const char arrS[][9], const char arrR[][9]);

int show1only;

int main(int argc, char* argv[])
{
	char arrShu[9][9] = {
		8, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 3, 6, 0, 0, 0, 0, 0, 
		0, 7, 0, 0, 9, 0, 2, 0, 0, 
		0, 5, 0, 0, 0, 7, 0, 0, 0, 
		0, 0, 0, 0, 4, 5, 7, 0, 0, 
		0, 0, 0, 1, 0, 0, 0, 3, 0, 
		0, 0, 1, 0, 0, 0, 0, 6, 8, 
		0, 0, 8, 5, 0, 0, 0, 1, 0, 
		0, 9, 0, 0, 0, 0, 4, 0, 0
	};
	char arrR[9][9] = {0};
	show1only = (_getch() == 'y' | 'Y')?1:0;

	print_start(arrShu);
	printf("Start!\n");
	getch();

//	test((char *)arrShu, (char *)arrShu);
	test((char *)arrShu, (char *)arrR);
	
	print_result(arrShu, arrR);
	printf("End!\n");

	return 0;
}

int test(char arr[], char* r)
{
	int result;
	// 1: found answer
	// 0: conflict or no found
	char* p;
	char* p0;
	char num;
	int next;

	p = (char *)malloc(81);
	memcpy(p, arr, 81);

	// find out whether it has been filled
	p0 = (char *)memchr(p, 0, 81);
	if (p0)
	{
		result = 0;// did not find at the beginning
		for (num = 1; num <= 9; num++)
		{
			*p0 = num;
			// fill in the number before testing
			if (check_no_conflict(p))
			{// There is no conflict
				next = test(p, r);// Recursive
				if (next == 0)
				{// Not found, try next number
					continue;
				}
				else// if (next == 1)
				{// Found, to come out
					result = 1;// illustrate found in this branch
					break;
				}
			}
			else
			{
				// There is a conflict, try the next number
				continue;
			}
		}
		// Complete all attempts
	}
	else
	{// fill to full
		if (check_no_conflict(p))
		{
			memcpy(r, p, 81);
			result = 1;
		}
		else
		{
			result = 0;
		}
	}

	free(p);
	return result;
}

int check_no_conflict(const char* const arr)
{
	int result;
	int exist;
	int num;
	int i, j;

	result = 1;
	// from 1 to 9, according to three orders, check reiteration
	for (num = 1; num <=9; num++)
	{
		// rows
		for (i = 0; i < 9; i++)
		{
			exist = 0;
			for (j = 0; j < 9; j++)
			{
				if (arr[i * 9 + j] == num)//i->9i,j->j
				{
					if (exist++)
					{
						result = 0;
						break;
					}
				}
			}
			if (!result) break;
		}
		if (!result) break;
		// columns
		for (i = 0; i < 9; i++)
		{
			exist = 0;
			for (j = 0; j < 9; j++)
			{
				if (arr[i + j * 9] == num)//i->i,j->9j
				{
					if (exist++)
					{
						result = 0;
						break;
					}
				}
			}
			if (!result) break;
		}
		if (!result) break;
		// blocks
		for (i = 0; i < 9; i++)
		{
			exist = 0;
			for (j = 0; j < 9; j++)
			{
				if (arr[i / 3 * 27 + i % 3 * 3 + j / 3 * 9 + j % 3] == num)
					//i->i/3*27+i%3*3,j->j/3*9+j%3
				{
					if (exist++)
					{
						result = 0;
						break;
					}
				}
			}
			if (!result) break;
		}
		if (!result) break;
	}
	return result;
}

void print_start(const char arr[][9])
{
	int i, j;
	char c;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			c = arr[i][j];
			if (c)
			{
				printf("[%d]", c);
			}
			else
			{
				printf(" . ");
			}
		}
		printf("\n");
	}
}

void print_result(const char arrS[][9], const char arrR[][9])
{
	int i, j;
	// having space not be fill in numbers means traverse is end
	if (memchr(arrR, 0, 81))
	{
		printf("There is no result yet.\n");
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (arrS[i][j] == arrR[i][j])
				{
					printf("(%d)", arrR[i][j]);
				}
				else
				{
					printf(" %d ", arrR[i][j]);
				}
			}
			printf("\n");
		}
	}
}

