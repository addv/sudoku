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
#include <memory.h>

int check_no_conflict(char arr[]);
int test(char arr[], char* r);

int main(int argc, char* argv[])
{
	int i, j;
	char arrShu[9][9] = {
		1, 2, 3, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d ", arrShu[i][j]);
		}
		printf("\n");
	}
	printf("Start!\n");

	test((char *)arrShu, (char *)arrShu);
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d ", arrShu[i][j]);
		}
		printf("\n");
	}
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
	{
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

int check_no_conflict(char arr[])
{
	int result;
	int exist;
	int num;
	int i, j;

	if (arr[9] == 4)
		i = 0;
	// from 1 to 9, according to three orders, check reiteration
	result = 1;
	for (num = 1; num <=9; num++)
	{
		// rows
		exist = 0;
		for (i = 0; i < 9; i++)
		{
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
		exist = 0;
		for (i = 0; i < 9; i++)
		{
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
		exist = 0;
		for (i = 0; i < 9; i++)
		{
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
