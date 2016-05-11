/*
 * 12/05/2016
 *
 *         Николай Костадинов, УНИБИТ, ИТ1, 2259
 *		Курсова работа по "Процедурно програмиране"
 * -----------------------------------------------------
 *
 * Това е моята имплементация на пъзела със зелката, козата и вълка.
 * Фермер си купл зелка, коза и вълк и трябва да прекоси реката с тях.
 * Лодката му може да пренася само него и още една покупка наведнъж.
 * Не можем да оставим зелката сама с козата, нито козата сама с вълка.
 */

#include <iostream>
using namespace std;

// Дефинираме необходимите типове данни
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
	// Дефинираме низа с покупкуте на фермера
	purchase purchases[3] =
	{
		{ CABBAGE,	false },
		{ GOAT,		false },
		{ WOLF,		false }
	};

	bool boatCrossed = false; // Чрез тази променлива разбираме на коя страна на реката се намира лодката
	bool completed = false; // Дали сме решили пъзела

	// Главният цикъл
	while (1)
	{
		// Информираме клиента за сегашния статус на обсотятелствата
		cout << "You are currently " << (boatCrossed ? "on the other side" : "on the initial side") << " of the river." << endl;
		cout << "Current status of purchases: " << endl;
		for (int i = 0; i < 3; i++, completed = purchases[0].crossed && purchases[1].crossed && purchases[2].crossed)
			cout << i + 1 << ". " << (purchases[i].t == CABBAGE ? "Cabbage: " : purchases[i].t == GOAT ? "Goat:    " : purchases[i].t == WOLF ? "Wolf:    " : "ayy") << (purchases[i].crossed ? "crossed" : "not crossed") << endl;

		// Ако сме решили пъзела, излизаме от цикъла
		if (completed)
			break;

		// Чакаме вход от клиента за коя покупка ще местим
		enterval:
		cout << "Enter which one to place on boat (0 for none): ";

		int id = 0;
		cin >> id;

		if (id > 0 && id > 3)
		{ // Грешен вход
			cout << "Wront id. ";
			goto enterval;
		}
		else if (id > 0 && id - 1 != CABBAGE && id - 1 != GOAT && purchases[CABBAGE].crossed == purchases[GOAT].crossed)
		{ // Проверка дали оставяме зелката сама с козата
			cout << "Can't leave cabbage alone with goat." << endl;
			goto enterval;
		}
		else if (id > 0 && id - 1 != GOAT && id - 1 != WOLF && purchases[GOAT].crossed == purchases[WOLF].crossed)
		{ // Проверка дали оставяме козата сама с вълка
			cout << "Can't leave goat alone with wolf." << endl;
			goto enterval;
		}
		else if (id > 0 && purchases[id - 1].crossed != boatCrossed)
		{ // Проверка дали избрания продукт е на същата страна, на която сме ние
			cout << "This id is on the other side of the river. You can't move it from this side." << endl;
			goto enterval;
		}

		purchases[id - 1].crossed = !purchases[id - 1].crossed; // Сменяме статута на избраната покупка
		boatCrossed = !boatCrossed; // Сменяме статута на лодката
		cout << endl;
	}

	// Щом сме излязли от цикъла, информираме клиента, че е решил пъзела :)
	cout << "Congratulations! You completed the puzzle!" << endl;
	system("pause");
}