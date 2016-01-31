
/*

21/01/2016

Prints an inverted pyramid made out of numbers based on an inputted number, which is less than 40.

So if you input 4 it will print:

4           4
4 3       3 4
4 3 2   2 3 4
4 3 2 1 2 3 4

*/

#include <iostream>
using namespace std;

/*
n = inputted number, we start from here
i = the current number
l = line number
*/

void print(int n, int i, int l)
{
	if (l == n)
		return;
	if (i<-n)
	{
		cout << endl;
		print(n, i = n, ++l);
	}
	else
	{ // lmao
		if (
			(i > 0 && n - i > l) ||
			(i < 0 && n - (i*-1) > l)
			) cout << "  ";
		else cout << (i > 0 ? i : -i) << " ";
		print(n, i - 1 == 0 ? i - 3 : --i, l);
	}

}

int main()
{
	int n = 0, i;

	cout << "Enter number: ";
	cin >> n;

	if (n > 40)
		cout << "Invalid number." << endl;
	else
		print(n, i = n, 0);

	system("pause");
}