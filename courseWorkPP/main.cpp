/*
 * 12/05/2016
 *
 *         ������� ����������, ������, ��1, 2259
 *		������� ������ �� "���������� ������������"
 * -----------------------------------------------------
 *
 * ���� � ����� ������������� �� ������ ��� �������, ������ � �����.
 * ������ �� ���� �����, ���� � ���� � ������ �� ������� ������ � ���.
 * ������� �� ���� �� ������� ���� ���� � ��� ���� ������� ��������.
 * �� ����� �� ������� ������� ���� � ������, ���� ������ ���� � �����.
 */

#include <iostream>
using namespace std;

// ���������� ������������ ������ �����
typedef enum
{
	CABBAGE,
	GOAT,
	WOLF
} type;

typedef struct
{
	type t;
	bool crossed;
} purchase;

int main()
{
	// ���������� ���� � ��������� �� �������
	purchase purchases[3] =
	{
		{ CABBAGE,	false },
		{ GOAT,		false },
		{ WOLF,		false }
	};

	bool boatCrossed = false; // ���� ���� ���������� ��������� �� ��� ������ �� ������ �� ������ �������
	bool completed = false; // ���� ��� ������ ������

	// �������� �����
	while (1)
	{
		// ����������� ������� �� �������� ������ �� ���������������
		cout << "You are currently " << (boatCrossed ? "on the other side" : "on the initial side") << " of the river." << endl;
		cout << "Current status of purchases: " << endl;
		for (int i = 0; i < 3; i++, completed = purchases[0].crossed && purchases[1].crossed && purchases[2].crossed)
			cout << i + 1 << ". " << (purchases[i].t == CABBAGE ? "Cabbage: " : purchases[i].t == GOAT ? "Goat:    " : purchases[i].t == WOLF ? "Wolf:    " : "ayy") << (purchases[i].crossed ? "crossed" : "not crossed") << endl;

		// ��� ��� ������ ������, �������� �� ������
		if (completed)
			break;

		// ������ ���� �� ������� �� ��� ������� �� ������
		enterval:
		cout << "Enter which one to place on boat (0 for none): ";

		int id = 0;
		cin >> id;

		if (id > 0 && id > 3)
		{ // ������ ����
			cout << "Wront id. ";
			goto enterval;
		}
		else if (id > 0 && id - 1 != CABBAGE && id - 1 != GOAT && purchases[CABBAGE].crossed == purchases[GOAT].crossed)
		{ // �������� ���� �������� ������� ���� � ������
			cout << "Can't leave cabbage alone with goat." << endl;
			goto enterval;
		}
		else if (id > 0 && id - 1 != GOAT && id - 1 != WOLF && purchases[GOAT].crossed == purchases[WOLF].crossed)
		{ // �������� ���� �������� ������ ���� � �����
			cout << "Can't leave goat alone with wolf." << endl;
			goto enterval;
		}
		else if (id > 0 && purchases[id - 1].crossed != boatCrossed)
		{ // �������� ���� �������� ������� � �� ������ ������, �� ����� ��� ���
			cout << "This id is on the other side of the river. You can't move it from this side." << endl;
			goto enterval;
		}

		purchases[id - 1].crossed = !purchases[id - 1].crossed; // ������� ������� �� ��������� �������
		boatCrossed = !boatCrossed; // ������� ������� �� �������
		cout << endl;
	}

	// ��� ��� ������� �� ������, ����������� �������, �� � ����� ������ :)
	cout << "Congratulations! You completed the puzzle!" << endl;
	system("pause");
}