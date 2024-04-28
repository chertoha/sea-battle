/* Морской бой  LAST 11.05.15 18-05*/

#include  <iostream>
#include <conio.h> //_getch()
#include <math.h>
#include <time.h>
#include <windows.h>
//#include <string.h>
//#include <stdio.h>
//#include <errno.h>
//#include <stdlib.h>


using namespace std;

// Global Var	
const int _size = 10;
int xGlobal = 5, yGlobal = 5;
int totalDecksPC = 20, totalDecksHuman = 20;


// Structures
struct ships {
	int deckNum;// decks number
	int amount; // ships quantity 
};


// Procedure & Function Prototypes
void arrPrint(int arr[][_size]); // Any array print
void fieldHumanCreate(int arrHum[][_size]); // Filling Human Field
bool interferentionCheck(int arr1[][_size], int** arr2, int size2);// Check arrays interferention 
void fieldPCCreate(int arrPC[][_size]); // Filling PC Field
bool shipPossibleCheck(int** arr, int deckSize);// Return true if it is possible to create a ship
void GameHum(int arrPC[][_size], int arrHum[][_size], int arrMask[][_size]);//  GamePlay Human
void destruction(int arrMask[][_size], int arrPC[][_size], int y, int x); // Ship Destruction by Human
void GamePC(int arrPC[][_size], int arrHum[][_size], int arrMask[][_size]);//  GamePlay PC
int DecksCheck(int arrHum[][_size]); // Check Decks presence at battlefield
void destructionByPC(int arrHum[][_size], int y, int x);// Ship Destruction by PC

void main() {

	srand(time(NULL));

	// Create battle fields arrays
	int fieldHum[_size][_size];
	int fieldPC[_size][_size];


	cout << "\t-Sea Battle-" << endl << endl;

	//cout << "PC ships" << endl;

	fieldPCCreate(fieldPC);
	//fieldPCCreate(fieldHum); // Temporary
	//arrPrint(fieldPC);

	//cout << endl;
	system("pause");

	cout << "Arrange your ships!" << endl << endl;
	system("pause");
	fieldHumanCreate(fieldHum);
	system("cls");

	arrPrint(fieldHum);


	int arrMask[_size][_size];// Special array to show PC's open cells  to a Human 
	//int shotsNum = 0;

	while (totalDecksHuman != 0 || totalDecksPC != 0) {
		system("cls");
		GameHum(fieldPC, fieldHum, arrMask);
		Beep(700, 100);
		//system("pause");
		system("cls");


		GamePC(fieldPC, fieldHum, arrMask);

		if (totalDecksHuman == 0 || totalDecksPC == 0)
			break;

		//shotsNum++;
		//cout << "Number of shots: " << shotsNum << endl;
	}// end while


	if (totalDecksHuman == 0)
		cout << "PC IS THE WINNERRRR!!!!" << endl;
	else if (totalDecksPC == 0)
		cout << "YOU ARE THE WINNERRRR!!!!" << endl;
	else
		cout << "HERE IS DEAD HEAT!!!";

	system("pause");
}//main


//  GamePlay PC
void GamePC(int arrPC[][_size], int arrHum[][_size], int arrMask[][_size]) {

	//int totalDecksPC = 20;
	int y = 0, x = 0;
	bool moveSwitch = true;// True - Human move, False - PC move


	while (totalDecksHuman != 0 || totalDecksPC != 0) {
		system("cls");


		// Check for brocken decks
		int xBrokenDeck = -1, yBrockenDeck = -1;
		int tempI = -1;
		bool horizont = true;
		int countBrokenDekcs = 0;

		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (arrHum[i][j] > 1000) {

					if (tempI == -1) {// Horizontal or vertical
						tempI = i;
					}
					else {
						if (tempI == i) {
							horizont = true;
						}
						else
							horizont = false;
					}

					countBrokenDekcs++;
					yBrockenDeck = i;
					xBrokenDeck = j;
				}// end if 
			}
		}//end for i


		// Search for non broken decks
		if (countBrokenDekcs == 1) {
			int directX;
			int direct;

			while (1) {
				directX = rand() % 2;
				direct = rand() % 2;

				if (directX == 0) {
					if (direct == 0) {
						y = yBrockenDeck - 1;
						x = xBrokenDeck;
					}
					else {
						y = yBrockenDeck + 1;
						x = xBrokenDeck;
					}
				}//end if
				else {
					if (direct == 0) {
						y = yBrockenDeck;
						x = xBrokenDeck - 1;
					}
					else {
						y = yBrockenDeck;
						x = xBrokenDeck + 1;
					}

				}// end else


				if (arrHum[y][x] != 6 && arrHum[y][x] != 10 && arrHum[y][x] < 1000 && x >= 0 && y >= 0 && x < _size && y < _size)
					break;


			}// end while
		}// end if


		if (countBrokenDekcs > 1) {

			if (!horizont) {
				if (arrHum[yBrockenDeck + 1][xBrokenDeck] != 6 && arrHum[yBrockenDeck + 1][xBrokenDeck] != 10
					&& arrHum[yBrockenDeck + 1][xBrokenDeck] < 1000 && yBrockenDeck - 1 >= 0 && yBrockenDeck + 1 < _size) {

					x = xBrokenDeck;
					y = yBrockenDeck + 1;
				}
				else {
					x = xBrokenDeck;
					y = yBrockenDeck - countBrokenDekcs;
				}
			}// end if horizont true
			else {
				if (arrHum[yBrockenDeck][xBrokenDeck + 1] != 6 && arrHum[yBrockenDeck][xBrokenDeck + 1] != 10
					&& arrHum[yBrockenDeck][xBrokenDeck + 1] < 1000 && xBrokenDeck - 1 >= 0 && xBrokenDeck + 1 < _size) {

					x = xBrokenDeck + 1;
					y = yBrockenDeck;
				}
				else {
					x = xBrokenDeck - countBrokenDekcs;
					y = yBrockenDeck;
				}
			}// end else horizont


		}// end if



		// If shoot for the first time
		if (countBrokenDekcs == 0) {

			while (1) {
				y = rand() % 10;
				x = rand() % 10;

				if (arrHum[y][x] != 6 && arrHum[y][x] != 10 && arrHum[y][x] < 1000)
					break;

			}// end while
		}// end if

		if (totalDecksHuman == 0 || totalDecksPC == 0)
			break;

		// Work with Y and X
		if (arrHum[y][x] >= 100) {
			destructionByPC(arrHum, y, x);
			totalDecksHuman--;
			moveSwitch = true;
			//helpIndex1stShoot = false;
		}
		else {
			arrHum[y][x] = 6;
			moveSwitch = false;

			break;
		}

		if (totalDecksHuman == 0 || totalDecksPC == 0)
			break;


		// Print part
		arrPrint(arrMask);
		cout << "PC decks left: " << totalDecksPC;
		cout << endl << endl;

		cout << "\tYOUR FIELD" << endl;
		arrPrint(arrHum);
		cout << "Your decks left: " << totalDecksHuman << endl;

		for (int i = 0, beep = 100; i < 5; i++, beep += 100) {
			Beep(beep, 300);
		}
	}// end global while

}// end procedure GamePC


// Ship Destruction by  PC
void destructionByPC(int arrHum[][_size], int y, int x) {

	int countDecks = 0;
	int countDecksBroken = 0;

	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (arrHum[i][j] == arrHum[y][x] || arrHum[i][j] / 10 == arrHum[y][x]) {
				countDecks++;
				if (arrHum[i][j] >= 1000)
					countDecksBroken++;
			}
		}
	}// end for i
	//cout << "TOTAL DECKS: " << countDecks << endl << "BROKEN DECKS: " << countDecksBroken <<"NUM: "<<arrHum[y][x]<< endl;


	int numYX = arrHum[y][x];
	if (countDecksBroken + 1 == countDecks) {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (arrHum[i][j] == numYX * 10 || arrHum[i][j] == numYX) {
					//cout << arrHum[i][j]<< " ";
					//system("pause");
					arrHum[i][j] = 10;
				}
			}
		}
	}// end if
	else if (countDecks > 1) {
		arrHum[y][x] *= 10;

	}



	// Write 6 ('#') to the field------------------------
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (arrHum[i][j] == 10) {
				for (int n = i - 1; n <= i + 1; n++) {
					for (int k = j - 1; k <= j + 1; k++) {
						if (arrHum[n][k] != 10 && n >= 0 && k >= 0 && n < _size && k < _size)
							arrHum[n][k] = 6;
					}
				}
			}//end of

		}// end for j
	}//end for i----------------------------------------------


}// end procedure destructionByPC


// Check Ship Decks presence    
int DecksCheck(int arrHum[][_size]) {
	int count = 0;

	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (arrHum[i][j] > 1000)
				count++;
		}
	}

	return count;

}// end function


//  GamePlay Human
void GameHum(int arrPC[][_size], int arrHum[][_size], int arrMask[][_size]) {



	int inpt = 0;
	int x = xGlobal, y = yGlobal, xPC = 0, yPC = 0;
	//int totalDeckSize = 20;
	bool moveSwitch = true;

	// Global while
	while (inpt != 27 || totalDecksHuman != 0 || totalDecksPC != 0) {

		system("cls");

		// Movement Direction
		if (inpt == 77 && x < _size - 1)// move right	
			x++;
		if (inpt == 75 && x > 0)// move left
			x--;
		if (inpt == 80 && y < _size - 1)// move down
			y++;
		if (inpt == 72 && y > 0)// move up
			y--;

		xGlobal = x;
		yGlobal = y;


		cout << "\tPC FIELD" << endl;



		// Missle Movement
		for (int i = 0; i < _size; i++) {

			for (int j = 0; j < _size; j++) {

				if (arrMask[i][j] != 1 && arrMask[i][j] != 6 && arrMask[i][j] != 10 && arrMask[i][j] != 1000)
					arrMask[i][j] = 0;

			}// end for j

		}// end for i -----------------------------------------------------------



		// Markers at battle field
		if (arrMask[y][x] != 1 && arrMask[y][x] != 6 && arrMask[y][x] != 10 && arrMask[y][x] != 1000)
			arrMask[y][x] = 5;
		if (inpt == 13 && arrPC[y][x] < 100 && arrMask[y][x] != 6 && arrMask[y][x] != 10 && arrMask[y][x] != 1000) {
			arrMask[y][x] = 6; // '#'
			moveSwitch = false;
			inpt = 27; // to make next move by PC
		}

		if (inpt == 13 && arrPC[y][x] >= 100 && arrMask[y][x] != 6 && arrMask[y][x] != 10 && arrMask[y][x] != 1000) {

			destruction(arrMask, arrPC, y, x);
			totalDecksPC--;
			moveSwitch = true;
		}


		// Write 6 ('#') to the field------------------------
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (arrMask[i][j] == 10) {
					for (int n = i - 1; n <= i + 1; n++) {
						for (int k = j - 1; k <= j + 1; k++) {
							if (arrMask[n][k] != 10 && n >= 0 && k >= 0 && n < _size && k < _size)
								arrMask[n][k] = 6;
						}
					}
				}//end of

			}// end for j
		}//end for i----------------------------------------------


		arrPrint(arrMask);
		cout << "PC decks left: " << totalDecksPC;
		cout << endl << endl;

		cout << "\tYOUR FIELD" << endl;
		arrPrint(arrHum);
		cout << "Your decks left: " << totalDecksHuman << endl;

		if (totalDecksHuman == 0 || totalDecksPC == 0)
			break;

		if (inpt == 27)
			break;

		// Get button
		inpt = 224;
		while (inpt == 224) {
			inpt = _getch();
		}





	}// end global while



}// end procedure


// Ship Destruction
void destruction(int arrMask[][_size], int arrPC[][_size], int y, int x) {

	int countDecks = 0;
	int countDecksBroken = 0;

	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (arrPC[i][j] == arrPC[y][x]) {
				countDecks++;
				if (arrMask[i][j] == 1000)
					countDecksBroken++;
			}
		}
	}// end for i


	if (countDecksBroken + 1 == countDecks) {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (arrPC[i][j] == arrPC[y][x]) {
					arrMask[i][j] = 10;
				}
			}
		}
	}// end if
	else if (countDecks > 1) {
		arrMask[y][x] = 1000;
	}






}// end procedure


// Filling PC Field
void fieldPCCreate(int arrPC[][_size]) {

	//int arrMask[size][size];
	int x = 0, y = 0;
	int shipsNUM = 10;
	int deckSize = 4;




	// Create PC Ships

	int marker = 0;

	while (shipsNUM > 0) {

		// Ships amount
		if (shipsNUM == 10)
			deckSize = 4;
		else if (shipsNUM <= 9 && shipsNUM >= 8)
			deckSize = 3;
		else if (shipsNUM <= 7 && shipsNUM >= 5)
			deckSize = 2;
		else
			deckSize = 1;


		// Temporary array for checking interferention
		int** arrTemp = new int* [2];
		for (int i = 0; i < 2; i++) {
			arrTemp[i] = new int[deckSize];
		}// -------------------------------------------


		x = rand() % 10;
		y = rand() % 10;

		int directX = rand() % 2;// 0 or 1
		int direct = rand() % 2;// 0 or 1 
		//cout << "directX= " << directX << "  directY= " << directY << endl;


		// Random Create PC Battle Field
		for (int i = 0; i < deckSize; i++) {//-------------------

			if (directX == 0)
				if (direct == 0) {
					//arrMask[y - i][x] = 1;
					arrTemp[0][i] = y - i;
					arrTemp[1][i] = x;
				}
				else {
					//arrMask[y + i][x] = 1;
					arrTemp[0][i] = y + i;
					arrTemp[1][i] = x;
				}
			else
				if (direct == 0) {
					//arrMask[y][x - i] = 1;
					arrTemp[0][i] = y;
					arrTemp[1][i] = x - i;
				}
				else {
					//arrMask[y][x + i] = 1;
					arrTemp[0][i] = y;
					arrTemp[1][i] = x + i;
				}
		}// end for i-------------------------------------------



		// If ship position is not wrong-----------------
		if (shipPossibleCheck(arrTemp, deckSize) && interferentionCheck(arrPC, arrTemp, deckSize)) {
			marker++;
			// Write ship to array
			for (int i = 0; i < deckSize; i++) {
				arrPC[arrTemp[0][i]][arrTemp[1][i]] = (deckSize * 100) + marker;// 400, 300, 200 ,100
			}


			// Write -1 ('-') to the field------------------------
			for (int i = 0; i < _size; i++) {
				for (int j = 0; j < _size; j++) {
					if (arrPC[i][j] >= 100) {
						for (int n = i - 1; n <= i + 1; n++) {
							for (int k = j - 1; k <= j + 1; k++) {
								if (arrPC[n][k] < 100 && n >= 0 && k >= 0 && n < _size && k < _size)
									arrPC[n][k] = -1;
							}
						}
					}//end of

				}// end for j
			}//end for i----------------------------------------------


			//arrPrint(arrPC);
			shipsNUM--;
			//system("pause");

			// Clear memory of temporary array
			for (int i = 0; i < 2; i++) {
				delete arrTemp[i];
			}
			delete[] arrTemp;


			//break;

		}// end if ---------------------------------------------------


	}// end while

	//arrPrint(arrPC);


}// end of procedure


// Check place for ship. Return true if it is possible to create a ship
bool shipPossibleCheck(int** arr, int deckSize) {

	for (int i = 0; i < deckSize; i++) {
		if (arr[0][i] < 0 || arr[1][i] < 0 || arr[0][i] > _size - 1 || arr[1][i] > _size - 1) // Check going out of border
			return false;

	}
	return true;
}


// Filling Human Field
void fieldHumanCreate(int arrHum[][_size]) {

	int arrMask[_size][_size];// Special array to create Human Battle field	


	int inpt = 0;
	int x = 5, y = 5;
	int rotate = 2;
	int shipsNUM = 10;
	int deckSize = 4;
	int marker = 1;

	// Global While
	while (shipsNUM > 0) {

		system("cls");

		// Ships amount
		if (shipsNUM == 10)
			deckSize = 4;
		else if (shipsNUM <= 9 && shipsNUM >= 8)
			deckSize = 3;
		else if (shipsNUM <= 7 && shipsNUM >= 5)
			deckSize = 2;
		else
			deckSize = 1;


		// Movement Direction
		if (inpt == 32) {// rotate ship			
			if (x + deckSize <= _size && y + deckSize <= _size)
				rotate++;
		}
		if (inpt == 77) {// move right			
			if (rotate % 2 != 0 && x + deckSize < _size)
				x++;
			else if (rotate % 2 == 0 && x < _size - 1)
				x++;
		}
		if (inpt == 75 && x > 0)// move left
			x--;
		if (inpt == 80) {// move down
			if (rotate % 2 != 0 && y < _size - 1)
				y++;
			else if (rotate % 2 == 0 && y + deckSize < _size)
				y++;
		}
		if (inpt == 72 && y > 0)// move up
			y--;


		// Temporary array for checking interferention
		int** arrTemp = new int* [2];
		for (int i = 0; i < 2; i++) {
			arrTemp[i] = new int[deckSize];
		}// -------------------------------------------


		// Create array for Human field CYCLE

		for (int i = 0; i < _size; i++) {

			for (int j = 0; j < _size; j++) {

				arrMask[i][j] = arrHum[i][j];

				// Create decks
				for (int nDeck = 0; nDeck < deckSize; nDeck++) {
					if (rotate % 2 == 0) {
						arrMask[y + nDeck][x] = (deckSize * 100) + marker;
						arrTemp[0][nDeck] = y + nDeck;
						arrTemp[1][nDeck] = x;
					}
					else {
						arrMask[y][x + nDeck] = (deckSize * 100) + marker;
						arrTemp[0][nDeck] = y;
						arrTemp[1][nDeck] = x + nDeck;
					}
				}// end for nDeck



			}// end for j

		}// end for i -----------------------------------------------------------

		// Print fields
		arrPrint(arrMask);
		//cout <<"REAL FIELD"<<endl;
		//arrPrint(arrHum);

		// Get button
		inpt = 224;
		while (inpt == 224) {
			inpt = _getch();
		}
		if (inpt == 27)
			break;

		// Copy Ship position to Human field
		bool funcRes = interferentionCheck(arrHum, arrTemp, deckSize);
		if (inpt == 13 && funcRes) {
			marker++;
			for (int i = 0; i < _size; i++) {
				for (int j = 0; j < _size; j++) {

					if (arrHum[i][j] != 1)
						arrHum[i][j] = arrMask[i][j];
				}
			}

			shipsNUM--;
		}// end if 
		if (!funcRes && inpt == 13)
			Beep(800, 500);
		//----------------------------------------------------


		// Write -1 ('-') to the field------------------------
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (arrHum[i][j] >= 100) {
					for (int n = i - 1; n <= i + 1; n++) {
						for (int k = j - 1; k <= j + 1; k++) {
							if (arrHum[n][k] < 100 && n >= 0 && k >= 0 && n < _size && k < _size)
								arrHum[n][k] = -1;
						}
					}
				}//end of

			}// end for j
		}//end for i----------------------------------------------


		// Clear memory of temporary array
		for (int i = 0; i < 2; i++) {
			delete arrTemp[i];
		}
		delete[] arrTemp;


	}// end Global While

}// End procedure 


// Return false , when there is shipDecks interferention
bool interferentionCheck(int arr1[][_size], int** arr2, int size2) {

	for (int i = 0; i < size2; i++) {
		if (arr1[arr2[0][i]][arr2[1][i]] >= 100 || arr1[arr2[0][i]][arr2[1][i]] == -1)
			return false;
	}
	return true;
}


// Any array print
void arrPrint(int arr[][_size]) {

	//cout << "   a b c d e f g h i j" << endl;

	cout << "   ";
	for (int i = 1; i <= xGlobal; i++) cout << "  ";
	cout << "*" << endl;
	// top border
	cout << "  ";
	for (int i = 0; i < 21; i++) {
		cout << char(220);
	}
	cout << endl;

	// left and right borders
	for (int i = 0; i < _size; i++) {



		/*	if (i + 1 <= 9)
				cout << " ";*/
		cout << "  " <</*i + 1 <<*/ char(221);

		for (int j = 0; j < _size; j++) {

			if (arr[i][j] >= 100 && arr[i][j] < 1000)
				cout << char(4)/*arr[i][j]*/ << " ";
			else if (arr[i][j] >= 1000)
				cout << "?"  /*arr[i][j]*/ << " ";
			//else if (arr[i][j] == -1)
				//cout << "-" << " ";
			else if (arr[i][j] == 5)
				cout << char(1) << " ";
			else if (arr[i][j] == 6)
				cout << /*'#'*/ char(15) << " ";
			else if (arr[i][j] == 10)
				cout << 'x'/*arr[i][j]*/ << " ";
			else
				cout << char(249) << " ";

		}

		if (yGlobal == i) {
			cout << "\b" << char(222);
			cout << "*" << endl;
		}
		else
			cout << "\b" << char(222) << endl;


	}// end for i------------- end side borders



	// Bottom border
	cout << "  ";
	for (int i = 0; i < 21; i++) {
		cout << char(223);
	}
	cout << endl;
}