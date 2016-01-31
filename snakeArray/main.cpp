
/*

10/12/2015

Prints out an array like a snake.
Look at how the below array is sorted, I can't explain it any clearer than that.

*/

#include <iostream>
using namespace std;

typedef enum
{
	DOWN,
	LEFT,
	UP,
	RIGHT,
} dist_t;

int main()
{
	int arr[5][5] = {
		{ 1,	2,		3,		4,		5 },
		{ 16,	17,		18,		19,		6 },
		{ 15,	24,		25,		20,		7 },
		{ 14,	23,		22,		21,		8 },
		{ 13,	12,		11,		10,		9 },
	};

	int i = 0, j = -1, // j is -1 because we do ++j in the array print in the while()
		start = 0, end = 5,
		dir = RIGHT;

	while (1)
	{
		if (dir == UP) start++;
		if (dir == RIGHT) end--;

		if (dir == DOWN)
			for (int v = i; v < end; v++)
				cout << arr[++i][j] << " ";
		else if (dir == LEFT)
			for (int v = j; v > start; v--)
				cout << arr[i][--j] << " ";
		else if (dir == UP)
			for (int v = i; v > start; v--)
				cout << arr[--i][j] << " ";
		else if (dir == RIGHT)
			for (int v = j; v < end; v++)
				cout << arr[i][++j] << " ";

		dir = dir == RIGHT ? DOWN : dir + 1;
		if (start == end) break;
	}

	system("pause");
	return 0;
}

