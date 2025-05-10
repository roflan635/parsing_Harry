#include <algorithm> // эта библиотека нужна для функции transform
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

// функция нахождения разделителей
size_t multifind(const string& str, const set<char>& delimiters, size_t startPos = 0)
{
	if (startPos == std::string::npos) return string::npos;
	for (size_t i = startPos; i < str.length(); i++)
	{
		if (delimiters.count(str[i]) > 0)
			return i;
	}
	return string::npos;
}

//фунцкия удаляет пробели и возвращает массив из полученных слов
vector<string> multisplit(const string& str)
{
	vector<string> result;
	string part;
	size_t startPos = 0;
	size_t pos = str.find(' ');
	if (!str.empty())
	{
		while (pos != std::string::npos)
		{
			part = str.substr(startPos, pos - startPos);
			if (part.length() > 0)
				result.push_back(part);
			startPos = pos + 1;
			pos = str.find(' ', pos + 1);
		}
		part = str.substr(startPos, str.length() - startPos);
		if (part.length() > 0)
			result.push_back(part);
	}
	return result;
}

vector<vector<string>> SentencesParser(const string& text)
{
	vector<vector<string>> result;
	vector<string> words;
	set<char> delimiters{ '.','!','?',';',':','(',')' }; //разделители для обозначения конца предложения
	set<char> delimiters1{ '.','!','?',';',':','(', ')', ',', '"'}; //разделители, которые будут удаляться, чтобы не создавать лишних слов
	size_t pos = multifind(text, delimiters1);	//позиция первого разделителя
	size_t startPos = 0;	//начало предложения
	string sentence;	//создание подстроки
	while (pos != std::string::npos)
	{
		sentence = text.substr(startPos, pos - startPos);
		if (sentence.length() > 0)
		{
			for (int i = 0; i < sentence.length(); i++)
				while (delimiters1.count(sentence[i]) > 0 || sentence[i] == '”' || sentence[i] == '“') //цикл удаления знаков препинания из подстроки
					sentence.erase(i, 1);

			words = multisplit(sentence);
			result.push_back(words);
		}
			startPos = pos;	//переход к следующему предложению
			pos = multifind(text, delimiters, pos + 1); // поиск следующего разделителя
	}
	return result;
}

void Print(const vector<vector<string>>& vvs)   //функция вывода координат
{
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < vvs.size(); i++)
	{
		cout << i + 1 << " предложение:" << endl;
		for (int j = 0; j < vvs[i].size(); j++)
			cout << vvs[i][j] << endl;
		cout << endl;
	}
}

int main()
{		
	ifstream f("HarryPotterText.txt");
	string str, source;
	if (f)	//считывание текста 
	{
		while (f >> str)
			source += str + ' '; //создание пробелов, т.к. при считывании текста этим способом пробелы убираются
		f.close();
	}
	else return -1;
	transform(source.begin(), source.end(), source.begin(), tolower);	//трансформация всех букв в нижний регистр
	Print(SentencesParser(source));
}
