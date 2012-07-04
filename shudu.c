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

int check_no_conflict(const char* const arr, const char* const off, char num);
int test(char arr[]);
void print_start(char const arr[][9]);
void print_result(const char arrS[][9], const char arrR[][9]);

int showNum, currNum = 0;
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
};// Placed outside in order to can be invoked when more than one answer.
char arrR[9][9] = {0};

int main(int argc, char* argv[])
{
	char tempchar;
	
	print_start(arrShu);
	printf("How many answers do you want? (1-9)");
	tempchar = _getch();
	if (tempchar >= '1' && tempchar <= '9')
	{
		_putch(tempchar);
		showNum = tempchar - '0';
	}
	else
	{
		_putch('1');
		showNum = 1;
	}
	printf("\nStart!\n");
	
	test((char *)arrShu);
	
	if (showNum == 1)
	{
		print_result(arrShu, arrR);
	}
	else if(showNum > currNum)
	{
		printf("There is no more yet!\n");
	}
	printf("End!\n");
	
	return 0;
}

int test(char arr[])
{
	int result;
	// 1: found answer
	// 0: conflict or no found
	char* p;
	char* p0;
	char num;
	int next;
	
	p = malloc(81);
	memcpy(p, arr, 81);
	
	// find out whether it has been filled
	p0 = memchr(p, 0, 81);
	if (p0)
	{
		result = 0;// did not find at the beginning
		for (num = 1; num <= 9; num++)
		{
			// test the number be fill in
			if (check_no_conflict(p, p0, num))
			{// There is no conflict
				*p0 = num;
				
				next = test(p);// Recursive
				if (next == 0)
				{// Not found, try next number
					continue;
				}
				else// if (next == 1)
				{// Found, to come out
					result = 1;// illustrate found in this branch
					if (showNum != 1 && currNum < showNum) {continue;}
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
		memcpy(arrR, p, 81);// Can be written back to arr
		result = 1;
		if (showNum != 1)
		{
			printf("%d.\n", ++currNum);
			print_result(arrShu, arrR);
		}
	}
	
	free(p);
	return result;
}

int check_no_conflict(const char* const arr, const char* const off, char num)
{
	int row = (off - arr) / 9;
	int col = (off - arr) % 9;
	int blk = row / 3 * 3 + col / 3;
	int i;
	int r;
	
	r = 1;
	
	for (i = 0; i < 9; i++)
	{
		if ((arr[row * 9 + i] == num) || 
		    (arr[col + i * 9] == num) || 
		    (arr[blk / 3 * 27 + blk % 3 * 3 + i / 3 * 9 + i % 3] == num))
		{
			r = 0;
			break;
		}
	}
	
	return r;
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

