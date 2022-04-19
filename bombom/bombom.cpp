using namespace std;
#include <iostream>
#include <Windows.h>
#define SIZE 10

bool setCheck(int field[SIZE][SIZE], int shipSize, int x, int y, int dir)
{
    bool isPossible = 1;

    for (int i = 0; i < shipSize; i++)
    {
        if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
        {
            isPossible = 0;
            break;
        }

        if (field[x][y] >= 1 ||
            field[x][y + 1] == 1 ||
            field[x][y - 1] == 1 ||
            field[x + 1][y] == 1 ||
            field[x + 1][y + 1] == 1 ||
            field[x + 1][y - 1] == 1 ||
            field[x - 1][y] == 1 ||
            field[x - 1][y + 1] == 1 ||
            field[x - 1][y - 1] == 1)
        {
            isPossible = 0;
            break;
        }

        switch (dir)
        {
        case 0:
            x++;
            break;
        case 1:
            y++;
            break;
        case 2:
            x--;
            break;
        case 3:
            y--;
            break;
        }
    }

    return isPossible;
}

bool checkBorder(int field[SIZE][SIZE], int x, int y)
{
    bool check;
    if (x >= 0 && y >= 0 && x < SIZE && y < SIZE)
        check = 1;
    else
        check = 0;
    return check;
}

struct Ships
{
    int length;
    int x1, y1, x2, y2, dir;
    int hp;
    void setShipsRandom(int field[SIZE][SIZE], int& i)
    {
        if (i == 0)
            length = 4;
        else if (i >= 1 && i <= 2)
            length = 3;
        else if (i >= 3 && i <= 5)
            length = 2;
        else if (i >= 6 && i <= 9)
            length = 1;

        hp = length;

        x1 = rand() % SIZE;
        y1 = rand() % SIZE;

        int tempX = x1;
        int tempY = y1;

        dir = rand() % 4;

        if (setCheck(field, length, tempX, tempY, dir))
        {
            for (int j = 0; j < length; j++)
            {
                field[tempX][tempY] = 1;
                switch (dir)
                {
                case 0:
                    tempX++;
                    break;
                case 1:
                    tempY++;
                    break;
                case 2:
                    tempX--;
                    break;
                case 3:
                    tempY--;
                    break;
                }
            }
            switch (dir)
            {
            case 0:
                x2 = tempX - 1;
                y2 = tempY;
                break;
            case 1:
                x2 = tempX;
                y2 = tempY - 1;
                break;
            case 2:
                x2 = tempX + 1;
                y2 = tempY;
                break;
            case 3:
                x2 = tempX;
                y2 = tempY + 1;
            }
            i++;
        }
    }
};

void showField(int field[SIZE][SIZE])
{
    cout << '@';
    for (int i = 0; i < SIZE; i++)
        printf("%c%d", ' ', i);
    cout << endl;

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d%c", i, ' ');

        for (int j = 0; j < SIZE; j++)
        {
            if (field[j][i] == 0)
                cout << "~ ";
            else if (field[j][i] == 1)
                cout << "# ";
            else if (field[j][i] == 2)
                cout << "X ";
            else if (field[j][i] == 3)
                cout << "* ";
        }
        cout << endl;
    }
}

int selectShip(Ships* ship, int size, int x, int y)
{
    for (int i = 0; i < size; i++)
    {
        if (((x >= ship[i].x1 && x <= ship[i].x2) || (x <= ship[i].x1 && x >= ship[i].x2)) && ((y >= ship[i].y1 && y <= ship[i].y2) || (y <= ship[i].y1 && y >= ship[i].y2)))
            return i;
    }
}

void defineDestroy(int field[SIZE][SIZE], Ships* ship, int i)
{
    int tempX, tempY;
    tempX = ship[i].x1;
    tempY = ship[i].y1;

    switch (ship[i].dir)
    {
    case 0:
        for (int j = 0; j < ship[i].length; j++)
        {
            field[tempX][ship[i].y1] = 3;
            tempX++;
        }
        for (int j = ship[i].x1 - 1; j <= ship[i].x2 + 1; j++)
        {
            for (int k = ship[i].y1 - 1; k <= ship[i].y2 + 1; k++)
            {
                if (field[j][k] != 3 && checkBorder(field, j, k))
                    field[j][k] = 2;
            }
        }
        break;
    case 1:
        for (int j = 0; j < ship[i].length; j++)
        {
            field[ship[i].x1][tempY] = 3;
            tempY++;

        }
        for (int j = ship[i].x1 - 1; j <= ship[i].x2 + 1; j++)
        {
            for (int k = ship[i].y1 - 1; k <= ship[i].y2 + 1; k++)
            {
                if (field[j][k] != 3 && checkBorder(field, j, k))
                    field[j][k] = 2;
            }
        }
        break;
    case 2:
        for (int j = 0; j < ship[i].length; j++)
        {
            field[tempX][ship[i].y1] = 3;
            tempX--;
        }
        for (int j = ship[i].x2 - 1; j <= ship[i].x1 + 1; j++)
        {
            for (int k = ship[i].y1 - 1; k <= ship[i].y2 + 1; k++)
            {
                if (field[j][k] != 3 && checkBorder(field, j, k))
                    field[j][k] = 2;
            }
        }
        break;
    case 3:
        for (int j = 0; j < ship[i].length; j++)
        {
            field[ship[i].x1][tempY] = 3;
            tempY--;
        }
        for (int j = ship[i].x1 - 1; j <= ship[i].x2 + 1; j++)
        {
            for (int k = ship[i].y2 - 1; k <= ship[i].y1 + 1; k++)
            {
                if (field[j][k] != 3 && checkBorder(field, j, k))
                    field[j][k] = 2;
            }
        }
        break;
    }
}

int shot(int field[SIZE][SIZE], int fieldMask[SIZE][SIZE], Ships* ship, int x, int y, int& numberOfShip, int size)
{
    int shotResult;

    if (field[x][y] == 1)
    {
        fieldMask[x][y] = 1;
        field[x][y] = 3;

        numberOfShip = selectShip(ship, size, x, y);
        ship[numberOfShip].hp--;
        if (ship[numberOfShip].hp == 0)
        {
            shotResult = 2;
            defineDestroy(fieldMask, ship, numberOfShip);
        }
        else
        {
            shotResult = 1;
        }
    }
    else
    {
        shotResult = 0;
        fieldMask[x][y] = 2;
        field[x][y] = 2;
    }

    return shotResult;
}

int smartPCTurn(int field[SIZE][SIZE], int fieldMask[SIZE][SIZE], Ships* ship, bool& mode, bool& randomDir, int& x1, int& y1, int& firstX, int& firstY, int& dir, int numOfShips)
{
    int shotResult;
    int numberOfShip;
    bool border;
    bool rightHit;

	if (mode == 0)
	{
		rightHit = 0;

		while (rightHit == 0)
		{
			x1 = rand() % 10;
			y1 = rand() % 10;

			if (field[x1][y1] == 1 || field[x1][y1] == 0)
				rightHit = 1;
		}

		shotResult = shot(field, fieldMask, ship, x1, y1, numberOfShip, numOfShips);

		if (shotResult == 1)
		{
			mode = 1;
			firstX = x1;
			firstY = y1;
		}
		else if (shotResult == 2)
		{
			defineDestroy(field, ship, numberOfShip);
		}
	}
	else if (mode == 1)
	{
		while (true)
		{
			if (randomDir == 1)
			{
				dir = rand() % 4;
			}
			if (dir == 0 && (field[x1 + 1][y1] == 1 || field[x1 + 1][y1] == 0))
			{
				break;
			}
			else if (dir == 1 && (field[x1][y1 + 1] == 1 || field[x1][y1 + 1] == 0))
			{
				break;
			}
			else if (dir == 2 && (field[x1 - 1][y1] == 1 || field[x1 - 1][y1] == 0))
			{
				break;
			}
			else if (dir == 3 && (field[x1][y1 - 1] == 1 || field[x1][y1 - 1] == 0))
			{
				break;
			}
			else
			{
				randomDir = 1;
			}
		}
		while (true)
		{
			switch (dir)
			{
			case 0:
				x1++;
				break;
			case 1:
				y1++;
				break;
			case 2:
				x1--;
				break;
			case 3:
				y1--;
				break;
			}

			border = checkBorder(field, x1, y1);

			if (border == 1)
			{
				shotResult = shot(field, fieldMask, ship, x1, y1, numberOfShip, numOfShips);
				if (shotResult == 2)
				{
					mode = 0;
					defineDestroy(field, ship, numberOfShip);
					randomDir = 1;
					break;
				}
				else if (shotResult == 0)
				{
					x1 = firstX;
					y1 = firstY;
					if (randomDir == 0)
					{
						if (dir == 0)
							dir = 2;
						if (dir == 1)
							dir = 3;
						if (dir == 2)
							dir = 0;
						if (dir == 3)
							dir = 1;
					}
					break;
				}
				else
				{
					randomDir = 0;
					break;
				}
			}
			else if (border == 0)
			{
				shotResult = 3;
				x1 = firstX;
				y1 = firstY;
				if (randomDir == 0)
				{
					if (dir == 0)
						dir = 2;
					if (dir == 1)
						dir = 3;
					if (dir == 2)
						dir = 0;
					if (dir == 3)
						dir = 1;
				}
				break;
			}
		}
	}
	return shotResult;
}

int main()
{
    int field[SIZE][SIZE] = { 0 };
    int fieldMask[SIZE][SIZE] = { 0 };

    int enemyField[SIZE][SIZE] = { 0 };
    int enemyFieldMask[SIZE][SIZE] = { 0 };

    const int numOfShips = 10;

    Ships ship[numOfShips];
    Ships enemyShip[numOfShips];

    int x, y, x1, y1;

    int numberOfShip;
    int shotResult;
    int dir, dir1;
    int firstX, firstY, firstX1, firstY1;
    int winCount = 0, enemyWinCount = 0;
    bool turn = 1;
    bool mode = 0, mode1 = 0;
    bool randomDir = 1, randomDir1 = 1;

    for (int i = 0; i < numOfShips;)
    {
        ship[i].setShipsRandom(field, i);
    }

    for (int i = 0; i < numOfShips;)
    {
        enemyShip[i].setShipsRandom(enemyField, i);
    }

    cout << "\tWELCOME TO BATTLESHIP!\n\n";
    cout << "Choose game mode:\n1| Player vs PC\n2| PC vs PC\n#";
    int choice;
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        cout << "Choose game difficulty:\n1| Easy\n2| Hard\n#";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1: //игрок против пк легкий уровень
            while(true)
            {
                do
                {
                    system("cls");
                    showField(field);
                    cout << endl;
                    showField(enemyFieldMask);

                    if (turn == 1)
                    {
                        cout << "Enter goal:\n";
                        cin >> x >> y;
                        cin.ignore();

                        shotResult = shot(enemyField, enemyFieldMask, enemyShip, x, y, numberOfShip, numOfShips);

                        if (shotResult == 2)
                        {
                            cout << "Ship destroyed!" << endl;
                            winCount++;
                        }
                    }
                    else
                    {
                        cout << "PC turn:\n";
                        Sleep(1000);
                        x = rand() % 10;
                        y = rand() % 10;

                        shotResult = shot(field, fieldMask, ship, x, y, numberOfShip, numOfShips);

                        if (shotResult == 2)
                        {
                            cout << "Ship destroyed!" << endl;
                            enemyWinCount++;
                        }
                    }

                    if (shotResult == 0)
                    {
                        cout << "Miss" << endl;
                    }
                    else if (shotResult == 1)
                    {
                        cout << "Hit!" << endl;
                    }
                    getchar();

                    if (winCount == 10 || enemyWinCount == 10)
                        break;

                } while (shotResult != 0);

                turn = !turn;

                if (winCount == 10 || enemyWinCount == 10)
                    break;
            }
            break;
        case 2: //игрок против пк сложный уровень
            while (true)
            {
                do
                {
                    system("cls");
                    showField(field);
                    cout << endl;
                    showField(enemyFieldMask);

                    if (turn == 1)
                    {
                        cout << "Enter goal:\n";
                        cin >> x >> y;
                        cin.ignore();

                        shotResult = shot(enemyField, enemyFieldMask, enemyShip, x, y, numberOfShip, numOfShips);
                        if (shotResult == 2)
                        {
                            cout << "Ship destroyed!" << endl;
                            winCount++;
                        }
                    }
                    else
                    {
                        cout << "PC turn:\n";
                        Sleep(1000);
                        shotResult = smartPCTurn(field, fieldMask, ship, mode, randomDir, x1, y1, firstX, firstY, dir, numOfShips);
                        if (shotResult == 2)
                        {
                            cout << "Ship destroyed!" << endl;
                            enemyWinCount++;
                        }
                    }

                    if (shotResult == 0)
                    {
                        cout << "Miss" << endl;
                        getchar();
                    }
                    else if (shotResult == 1)
                    {
                        cout << "Hit!" << endl;
                        getchar();
                    }

                    if (winCount == 10 || enemyWinCount == 10)
                        break;

                } while (shotResult != 0);

                turn = !turn;

                if (winCount == 10 || enemyWinCount == 10)
                    break;

            }
            break;
        }

        system("cls");
        showField(fieldMask);
        cout << endl;
        showField(enemyFieldMask);

        if (winCount > enemyWinCount)
            cout << "You Won!";
        else
            cout << "PC Won!";
        break;

    case 2: //пк против пк
        while (true)
        {
            do
            {
                system("cls");
                showField(fieldMask);
                cout << endl;
                showField(enemyFieldMask);

                if (turn == 1)
                {
                    cout << "PC1 turn:\n";
                    Sleep(1000);
                    shotResult = smartPCTurn(enemyField, enemyFieldMask, enemyShip, mode, randomDir, x, y, firstX, firstY, dir, numOfShips);
                    if (shotResult == 2)
                    {
                        cout << "Ship destroyed!" << endl;
                        winCount++;
                        getchar();
                    }
                }
                else
                {
                    cout << "PC2 turn:\n";

                    Sleep(1000);
                    shotResult = smartPCTurn(field, fieldMask, ship, mode1, randomDir1, x1, y1, firstX1, firstY1, dir1, numOfShips);
                    if (shotResult == 2)
                    {
                        cout << "Ship destroyed!" << endl;
                        enemyWinCount++;
                        getchar();
                    }
                }

                if (shotResult == 0)
                {
                    cout << "Miss" << endl;
                    getchar();
                }
                else if (shotResult == 1)
                {
                    cout << "Hit!" << endl;
                    getchar();
                }

                if (winCount == 10 || enemyWinCount == 10)
                    break;

            } while (shotResult != 0);

            turn = !turn;

            if (winCount == 10 || enemyWinCount == 10)
                break;
        }

        system("cls");
        showField(fieldMask);
        cout << endl;
        showField(enemyFieldMask);

        if (winCount > enemyWinCount)
            cout << "PC1 Won!";
        else
            cout << "PC2 Won!";
        break;
    }
}
