#include "stdafx.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::right;
#include<iomanip>
using std::setw;
#include <string>
using std::string;

//VARIBALS
const int memorySize = 1000;//size of memory
int memory[memorySize]; //memory of computer
int accumulator;
int instructionCounter = 0; //адрес следующей команды
int operatorCode;  // левые цифры код операции
int operand; //правые цифры ячейка операциии в памяти
int instructionRegistr;//хранение исполняемой команды
string _string = "";//строковый массив

					   //FUNCTIONS
void loadComputer();//function of computer loading
void showMemory(); //function of memory showing

int main()
{
	setlocale(0, "");
	cout << "*** Вас приветствует СимлТрон ***\n*** Введите программу ***\n\n";
	//showMemory();

	cout.fill('0');
	int memoryCin = NULL;//перемнная для проверки вводва данных
	do {
		do{		
			cout << setw(3) << instructionCounter << "? ";
			cin >> memoryCin;
		} while (memoryCin > 99999 || memoryCin < -99999);

		memory[instructionCounter] = memoryCin;
		instructionCounter++;
	} while (memory[instructionCounter - 1] != -99999);

	bool endprog = 0;

	instructionCounter = 0;

	cout << "\nStart programm: \n";

	do {
		instructionRegistr = memory[instructionCounter];
		operatorCode = instructionRegistr / 1000;
		operand = instructionRegistr - (operatorCode * 1000);
		instructionCounter++;

		switch (operatorCode)
		{
		case 10:                                    //10 - операция ввода в память
			cout << "-> ";
			cin >> memory[operand];
			break;
		case 11:                                    //11 -операция вывода
			cout << "<- ";
			cout << memory[operand];
			break;
		case 12:                                    //12 -операция вывода строки
			cout << "-> ";
			cin >> _string;
			
			for (int i = 0; i < _string.size(); i++)
			{
				 memory[operand + i] = char( _string[i]) ;
			}
			memory[operand + _string.size()] = 0;
			break;
		case 13:                                    //13 -операция вывода строки
			cout << "<- ";
			_string = "";
			do
			{
				_string += memory[operand++];
			} 
			while (memory[operand] != 0);
			cout << _string; //memory[operand];
			break;
		case 20:									//20 - операция помещения в аккомулятор
			accumulator = memory[operand];
			break;
		case 21:									//21 - операция выгрузки из аккомулятора
			memory[operand] = accumulator;
			break;
		case 30:									//30 - операция сложения с числом в аккомуляторе
			accumulator += memory[operand];
			break;
		case 31:									//31 - операция вычитания с числом в аккомуляторе			
			accumulator -= memory[operand];
			break;
		case 32:									//32 - операция деления с числом в аккомуляторе
			accumulator /= memory[operand];
			break;
		case 33:									//31 - операция умножения с числом в аккомуляторе
			accumulator *= memory[operand];
			break;
		case 40:									//40 - переход к указаному адресу памяти
			instructionCounter = operand;
			break;
		case 41:									//41 - переход к указаному адресу памяти если в аккамуляторе отрицательное число
		{
			if (accumulator < 0)
			{
				instructionCounter = operand;
			}
			break;
		}
		case 42:									//42 - переход к указаному адресу памяти если в аккамуляторе ноль
		{
			if (accumulator == 0)
			{
				instructionCounter = operand;
			}
			break;
		}
		case 43:									//43 - останов
		{
			endprog = 1;
		}
		}

	} while (!endprog);

	showMemory();
	system("pause");
	return 0;
}

void loadComputer()
{
	for (int i = 0; i < memorySize; i++)
	{

		memory[i] = 0;

	}
}

void showMemory()
{
	cout << "\n*****************************************\n\nРЕГИСТРЫ:\n";

	cout << "accumulator\t" << accumulator
		<< "\ninstructionCounter\t" << instructionCounter
		<< "\noperatorCode\t" << operatorCode
		<< "\noperand\t" << operand
		<< "\ninstructionRegistr\t" << instructionRegistr << "\n\n\n";
	
	cout.fill('0');
	for (int i = 1; i <= memorySize; i++)
	{
		if (memory[i - 1] >= 0)
			cout << "+";

		cout << setw(5) << right << memory[i - 1];

		if ((i % 10) == 0)
			cout << endl;

	}
	cout << "\n*****************************************\n\n";
}