//есть структура, кот хранит фамилию сотрудника и его номер телефона
//необоходимо создать trie - дерево по номерам телефонов
//(в trie - дереве будут хранится не фамилии а номера телефонов, массив ссылок цифры от 0 до 9)
//(eow - признак конца слова, булевский флаг(фио) - меня если фамилия то пустая то номер телефона еще не заполнен)
//Далее нужно распечатать фамилии всех сотрудников, чьи номера начинаются на(введенные 3 цифры)


#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

struct Node 
{
	Node* ptrs[10]; //0..9
	string eow; //fio
};
typedef Node* TrieTree;

void init(TrieTree t)
{
	t = nullptr;
}

bool empty(TrieTree t)
{
	return t == nullptr;
}

void add(TrieTree &t, const string number, string surname, const int i = 0) 
{
	if (t == nullptr) 
	{
		t = new Node;
		t->eow = ""; //fio если пустое, то номер еще не собран

		for (int j = 0; j < 10; j++) 
		{
			t->ptrs[j] = nullptr;
		}
	}

	if (number.length() - 1 < i)
		t->eow = surname;
	else
		add(t->ptrs[number[i] - '0'], number, surname, i + 1);
}

bool all_prts_empty(TrieTree t) 
{
	bool result = true;
	int i = 0;
	while (i < 10 && result)
	{
		if (!t->ptrs[i])
			i++;
		else
			result = false;
	}
	return result;
}

void Delete(TrieTree &t, const string number, const int i = 0)
{
	if (t != nullptr)
	{
		if (i <= number.length() - 1)
			Delete(t->ptrs[number[i] - '0'], number, i + 1);
		else
		{
			t->eow = ""; 
			if (all_prts_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
	}
}

void print(TrieTree t, string number = "")
{
	if (t->eow != "")
	{
		cout << number << " " << t->eow << endl;
	}

	for (int i = 0; i < 10; i++) 
	{
		if (t->ptrs[i])
			print(t->ptrs[i], number + char(i + '0'));
	}
}

void clear(TrieTree &t)
{
	for (int i = 0; i < 10; i++)
	{
		if (t->ptrs[i])
			clear(t->ptrs[i]);
	}
	delete t;
	t = nullptr;
}

void Task1(TrieTree t, string threedig, int i = 0, string number = "")
{
	if (i != 3) 
	{
		if (t->ptrs[threedig[i] - '0'] != nullptr)
			Task1(t->ptrs[threedig[i] - '0'], threedig, i + 1, number + char(i + '0')); 
		//поочередно идем по ветвям дерева имеющих данные цифры (проверяем первую цифру, есть ли от неё вторая, далее третья)
		else
			cout << "Пусто!" << endl; //если таковых нет
	}
	else
	{
		print(t, threedig); //если все трехзначное число нашлось в дереве, то печатаем все номера (3 цифры + номера)
	}
}

int main() {
	setlocale(LC_ALL, "ru");

	string path = "inp.txt";
	ifstream fin(path);

	if (fin.is_open())
	{
		TrieTree Tree = nullptr;
		string tmp_number, tmp_surname;
		while (!fin.eof())
		{
			fin >> tmp_number;
			fin >> tmp_surname;
			add(Tree, tmp_number, tmp_surname);
		}
		cout << "Считано:" << endl;
		print(Tree);
		cout << "Введите трехзначное число" << endl;
		string threedig;
		cin >> threedig;
		cout << "Фамилии сотрудников с номерами с 3-х заданых цифр:" << endl;
		Task1(Tree, threedig); //передаем трехзначное число
	}
	else 
	{
		cout << "Opening file ERROR" << endl;
	}

	system("pause");
	return 0;
}