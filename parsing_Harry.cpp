#include <algorithm> // эта библиотека нужна для функции transform
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

bool IsLetter(string l)
{
	if ((l >= "A" && l <= "Z") || (l >= "a" && l <= "z")
		|| (l >= "А" && l <= "Я")
		|| (l >= "а" && l <= "я")
		|| (l == "ё")
		|| (l == "Ё")
		|| (l == "\'"))
		return true;
	return false;
}

vector<string> multisplit(const string& str, const set<char>& delimiters = { ' ' })
{
	vector<string> result;
	string part;
	size_t startPos = 0;
	size_t pos = multifind(str, delimiters);
	while (pos != std::string::npos)
	{
		part = str.substr(startPos, pos - startPos);
		if (part.length() > 0)
			result.push_back(part);
		startPos = pos + 1;
		pos = multifind(str, delimiters, pos + 1);
	}
	part = str.substr(startPos, str.length() - startPos);
	if (part.length() > 0)
		result.push_back(part);
	return result;
}

size_t multifind(const string& str, const set<char>& delimiters, size_t startPos = 0)
{
	for (size_t i = startPos; i < str.length(); i++)
	{
		if (delimiters.count(str[i]) > 0)
			return i;
	}
	return std::string::npos;
}

vector<vector<string>> SentencesParser(string text)
{
	vector<vector<string>> result;

	

	return result;
}

void Print(vector<vector<string>> vvs)   //функция вывода координат
{
	for (int i = 0; i < vvs.size(); i ++)
	{
		
	}
}

int main()
{		
	setlocale(LC_ALL, "");
	ifstream f("..\\HarryPotterText.txt");
	string str, source;
	if (f)
	{
		while (f >> str)
			auto result1 = multisplit(str, set<char> {'!', '.', '?', ';', ':', '(', ')'});
	}
	else return -1;

	transform(source.begin(), source.end(), source.begin(), tolower);
}