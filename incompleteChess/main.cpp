
/*

30/01/2016

A chess program that makes you input N and M number of pieces on the board then input their type and position.
After that, it check if they can take any of the other pieces, or if they can be moved.

Incomplete though, only added pawn logic because it was very short notice.
And some other things because I am not sure how they do it in their course.

Completely untested because Visual Studio's consoles can't print cyrilic properly and I was too lazy to convert all of those messages to latin.
But I'm pretty sure it works.

*/

#include <iostream>
using namespace std;

enum fig_type {
	TYPE_NONE,
	TYPE_ki,	// Цар
	TYPE_qu,	// Царица
	TYPE_ro,	// Топ
	TYPE_bi,	// Офицер
	TYPE_kn,	// Кон
	TYPE_pa		// Пешка
};

struct fig
{
	int team;
	fig_type type;
};

void isEndangered(fig board[8][8], int team, int row, int col)
{
	if (board[row][col].team != team)
	{
		cout << "Figurata na tezi koordinati ne e ot Vashiq otbor." << endl;
		return;
	}

	if (board[row][col].team == 0)
	{
		cout << "Nqma figura na tezi koordinati." << endl;
		return;
	}

	//	Тъй като поддържаме само пешки, проверяваме дали пред нас от ляво и дясно има друга фигура.\
			Също, вместо да връщаме стойност -- принтираме, защото не знам вие как го правите. Ако искаш си го направи така.
	if (row > 0 && board[row - 1][col - 1].team != team)
		cout << row - 1 << "," << col - 1;

	if (row > 0 && board[row - 1][col + 1].team != team)
		cout << row - 1 << "," << col + 1;
}

void moveFig(fig board[8][8], int team, int row, int col, int newRow, int newCol)
{
	if (board[row][col].team == 0)
	{
		cout << "Nqma figura na tezi koordinati." << endl;
		return;
	}

	if (board[row][col].team != team)
	{
		cout << "Figurata na tezi koordinati ne e ot Vashiq otbor." << endl;
		return;
	}

	// Пешка
	if ((team == 1 && newRow == row - 1) ||
		(team == 2 && newRow == row + 1))
	{
		board[newRow][newCol].team = board[row][col].team;
		board[newRow][newCol].type = board[row][col].type;

		board[row][col].team = 0;
		board[row][col].type = TYPE_NONE;
	}
	else
	{
		cout << "Figurata ne moje da bude premestena na tezi koordinati." << endl;
		return;
	}
}

int main()
{
	fig board[8][8] = { 0 };

	int N = 0,	// N - white
		M = 0,	// M - black
		P = 0;	// P - requests

	cout << "Vavedete broq na figurite na igrach 1: ";
	cin >> N;

	cout << "Vavedete broq na figurite na igrach 2: ";
	cin >> M;

	cout << "Vavedete broq na zaqvkite: ";
	cin >> P;

	if (N > 8 * 2 || N < 0 ||
		M > 8 * 2 || M < 0)
	{
		cout << "Greshen interval. Prekaleno mnogo figuri." << endl;
		return 1;
	}

	// Искаше ми се това да го направя функция, ама викаш да не вдигам очакванията.
	for (int doThisTwiceLol = 0; doThisTwiceLol < 2; doThisTwiceLol++)
	{
		//					(							)  Това сте го учили, едноредов if case. Не би трябвало много да направи впечатление.
		for (int i = 0; i < (doThisTwiceLol == 0 ? N : M); i++)
		{
			char input[512] = { 0 };
			int row = 0, col = 0;

			cout << "Vavedete figura po zadadeniq format: ";
			cin >> input;

			if (strlen(input) != 4 ||
				!isalpha(input[0]) || input[0] < 'a' || input[0] > 'h' ||	// Първият елемент трябва да е малка буква от 'a' до 'h'
				!isdigit(input[1]) || isdigit(input[1]) > 8 ||				// Вторият елемент трябва да е цифра от 1 до 8
				!isalpha(input[2]) || input[2] < 'a' || input[2] > 'z' ||	// Третият  
				!isalpha(input[3]) || input[3] < 'a' || input[3] > 'z')		//			и четвъртият елемент трябва да са букви от 'a' do 'z'
			{
				cout << "Greshni danni. Molq, vavedete novi." << endl;
				i--;
				continue;
			}

			row = input[1] - '0' - 1;
			col = 8 - (input[0] - 'a');

			if(board[row][col].team > 0)
			{
				cout << "Greshni danni. Na tova mqsto veche ima figura. Molq, vavedete novi." << endl;
				i--;
				continue;
			}

			switch (input[2])
			{
			case 'k':
				if (input[3] == 'i')
					board[row][col].type = TYPE_ki;
				else if (input[3] == 'n')
					board[row][col].type = TYPE_kn;
				break;
			case 'q':
				board[row][col].type = TYPE_qu;
				break;
			case 'r':
				board[row][col].type = TYPE_ro;
				break;
			case 'b':
				board[row][col].type = TYPE_bi;
				break;
			case 'p':
				board[row][col].type = TYPE_pa;
				break;
			default:
				cout << "Greshni danni. Molq, vavedete novi." << endl;
				i--;
				continue;
				break;
			}
			board[row][col].team = doThisTwiceLol == 0 ? 1 : 2; // Тук също го има.
		}
	}

	for (int i = 0; i < P; i++)
	{
		cout << "Zaqvka 1: Izvejda zastresheni ot Vasha figura figuri. Molq, vavedete danni za Vasha figura." << endl;

		while (1)
		{
			int team = 0,
				row = 0, col = 0;

			cout << "Vavedete otbor: ";
			cin >> team;

			if (team > 1 || team < 0)
			{
				cout << "Greshen interval. Otborite sa 1 za beli i 2 za cherni. Molq, vavedete nowi danni." << endl;
				continue;
			}

			char input[512] = { 0 };
			cout << "Vavedete koordinati: ";
			cin >> input;

			if (strlen(input) != 4 ||
				!isalpha(input[0]) || input[0] < 'a' || input[0] > 'h' ||
				!isdigit(input[1]) || isdigit(input[1]) > 8)
			{
				cout << "Greshni danni. Molq, vavedete novi." << endl;
				i--;
				continue;
			}

			row = input[1] - '0' - 1;
			col = 8 - (input[0] - 'a');

			isEndangered(board, team, row, col);
			break;
		}

		cout << "Zaqvka 2: Premestvane na figura. Molq, vavedete danni za figurata, koqto iskate da premestite." << endl;

		while (1)
		{
			int team = 0,
				row = 0, col = 0,
				newRow = 0, newCol = 0;

			cout << "Vavedete otbor: ";
			cin >> team;

			if (team > 1 || team < 0)
			{
				cout << "Greshen interval. Otborite sa 1 za beli i 2 za cherni. Molq, vavedete novi danni." << endl;
				continue;
			}

			char input[512] = { 0 };
			cout << "Vavedete koordinati: ";
			cin >> input;			
			
			if (strlen(input) != 4 ||
				!isalpha(input[0]) || input[0] < 'a' || input[0] > 'h' ||
				!isdigit(input[1]) || isdigit(input[1]) > 8 )
			{
				cout << "Greshni danni. Molq, vavedete novi." << endl;
				i--;
				continue;
			}

			row = input[1] - '0' - 1;
			col = 8 - (input[0] - 'a');

			cout << "Vavedete novi koordinati: ";
			cin >> input;

			if (strlen(input) != 4 ||
				!isalpha(input[0]) || input[0] < 'a' || input[0] > 'h' ||
				!isdigit(input[1]) || isdigit(input[1]) > 8)
			{
				cout << "Greshni danni. Molq, vavedete novi." << endl;
				i--;
				continue;
			}

			newRow = input[1] - '0' - 1;
			newCol = 8 - (input[0] - 'a');
			moveFig(board, team, row, col, newRow, newCol);
			break;
		}

	}

	system("pause");
	return 0;
}