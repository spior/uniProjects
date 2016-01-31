
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
	TYPE_ki,	// ���
	TYPE_qu,	// ������
	TYPE_ro,	// ���
	TYPE_bi,	// ������
	TYPE_kn,	// ���
	TYPE_pa		// �����
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
		cout << "�������� �� ���� ���������� �� � �� ����� �����." << endl;
		return;
	}

	if (board[row][col].team == 0)
	{
		cout << "���� ������ �� ���� ����������." << endl;
		return;
	}

	//	��� ���� ���������� ���� �����, ����������� ���� ���� ��� �� ���� � ����� ��� ����� ������.\
			����, ������ �� ������� �������� -- ����������, ������ �� ���� ��� ��� �� �������. ��� ����� �� �� ������� ����.
	if (board[row - 1][col - 1].team != team)
		cout << row - 1 << "," << col - 1;

	if (board[row - 1][col + 1].team != team)
		cout << row - 1 << "," << col + 1;
}

void moveFig(fig board[8][8], int team, int row, int col, int newRow, int newCol)
{
	if (board[row][col].team == 0)
	{
		cout << "���� ������ �� ���� ����������." << endl;
		return;
	}

	if (board[row][col].team != team)
	{
		cout << "�������� �� ���� ���������� �� � �� ����� �����." << endl;
		return;
	}

	// �����
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
		cout << "�������� �� ���� �� ���� ���������� �� ���� ����������." << endl;
		return;
	}
}

int main()
{
	fig board[8][8] = { 0 };

	int N = 0,	// N - white
		M = 0,	// M - black
		P = 0;	// P - requests

	cout << "�������� ���� �� �������� �� ����� 1: ";
	cin >> N;

	cout << "�������� ���� �� �������� �� ����� 2: ";
	cin >> M;

	cout << "�������� ���� �� ��������: ";
	cin >> P;

	if (N > 8 * 2 || N < 0 ||
		M > 8 * 2 || M < 0)
	{
		cout << "������ ��������. ��������� ����� ������." << endl;
		return 1;
	}

	// ������ �� �� ���� �� �� ������� �������, ��� ����� �� �� ������ �����������.
	for (int doThisTwiceLol = 0; doThisTwiceLol < 2; doThisTwiceLol++)
	{
		//					(							)  ���� ��� �� �����, ��������� if case. �� �� �������� ����� �� ������� �����������.
		for (int i = 0; i < (doThisTwiceLol == 0 ? N : M); i++)
		{
			char input[512] = { 0 };
			int row = 0, col = 0;

			cout << "�������� ������ �� ��������� ������: ";
			cin >> input;

			if (strlen(input) != 4 ||
				!isalpha(input[0]) || input[0] < 'a' || input[0] > 'h' ||	// ������� ������� ������ �� � ����� ����� �� 'a' �� 'h'
				!isdigit(input[1]) || isdigit(input[1]) > 8 ||				// ������� ������� ������ �� � ����� �� 1 �� 8
				!isalpha(input[2]) || input[2] < 'a' || input[2] > 'z' ||	// �������  
				!isalpha(input[3]) || input[3] < 'a' || input[3] > 'z')		//			� ���������� ������� ������ �� �� ����� �� 'a' do 'z'
			{
				cout << "������ �����. ����, �������� ����." << endl;
				i--;
				continue;
			}

			row = input[1] - '0' - 1;
			col = 8 - (input[0] - 'a');
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
				cout << "������ �����. ����, �������� ����." << endl;
				i--;
				continue;
				break;
			}
			board[row][col].team = doThisTwiceLol == 0 ? 1 : 2; // ��� ���� �� ���.
		}
	}

	for (int i = 0; i < P; i++)
	{
		cout << "������ 1: ������� ���������� �� ���� ������ ������. ����, �������� ����� �� ���� ������." << endl;

		while (1)
		{
			int team = 0,
				row = 0, col = 0;

			cout << "�������� �����: ";
			cin >> team;

			if (team > 1 || team < 0)
			{
				cout << "������ ��������. �������� �� 1 �� ���� � 2 �� �����. ����, �������� ���� �����." << endl;
				continue;
			}

			cout << "�������� ���: ";
			cin >> row;

			cout << "�������� ������: ";
			cin >> col;

			if (row > 8 || row < 0 ||
				col > 8 || col < 0)
			{
				cout << "������ ��������. ����� �������. ����, �������� ���� �����." << endl;
				continue;
			}

			isEndangered(board, team, row, col);
			break;
		}

		cout << "������ 2: ����������� �� ������. ����, �������� ����� �� ��������, ����� ������ �� ����������." << endl;

		while (1)
		{
			int team = 0,
				row = 0, col = 0,
				newRow = 0, newCol = 0;

			cout << "�������� �����: ";
			cin >> team;

			if (team > 1 || team < 0)
			{
				cout << "������ ��������. �������� �� 1 �� ���� � 2 �� �����. ����, �������� ���� �����." << endl;
				continue;
			}

			cout << "�������� ���: ";
			cin >> row;

			cout << "�������� ������: ";
			cin >> col;

			if (row > 8 || row < 0 ||
				col > 8 || col < 0)
			{
				cout << "������ ��������. ����� �������. ����, �������� ���� �����." << endl;
				continue;
			}

			cout << "�������� ��� ���: ";
			cin >> row;

			cout << "�������� ���� ������: ";
			cin >> col;

			if (row > 8 || row < 0 ||
				col > 8 || col < 0)
			{
				cout << "������ ��������. ����� �������. ����, �������� ���� �����." << endl;
				continue;
			}

			moveFig(board, team, row, col, newRow, newCol);
			break;
		}

	}

	system("pause");
	return 0;
}