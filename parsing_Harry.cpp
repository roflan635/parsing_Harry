#include <algorithm> // эта библиотека нужна для функции transform
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

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

vector<string> multisplit(const string& str, const set<char>& delimiters)
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
	set<char> delimiters{ '.','!','?',';',':','(', ')'};
	set<char> delimiters1{ '.','!','?',';',':','(', ')', ',', '"'};
	size_t pos = multifind(text, delimiters1);
	size_t startPos = 0;
	string sentence;
	while (pos != std::string::npos)
	{
		sentence = text.substr(startPos, pos - startPos);
		if (sentence.length() > 0)
		{
			for (size_t i = 0; i < sentence.length(); i++)
				while (delimiters1.count(sentence[i]) > 0 || sentence[i] == '”' || sentence[i] == '“')
					sentence.erase(i, 1);
			words = multisplit(sentence, delimiters);
			result.push_back(words);
		}
			startPos = pos + 1;
			pos = multifind(text, delimiters, pos + 1);
	}
	return result;
}

void Print(const vector<vector<string>>& vvs)   //функция вывода координат
{
	setlocale(LC_ALL, "");
	for (int i = 0; i < vvs.size(); i++)
	{
		cout << i + 1 << " sentence:" << endl;
		for (int j = 0; j < vvs[i].size(); j++)
			cout << vvs[i][j] << endl;
	}
}

int main()
{		
	ifstream f("HarryPotterText.txt");
	string str, source;
	if (f)
	{
		while (f >> str)
			source += str + ' ';
		f.close();
	}
	else return -1;
	transform(source.begin(), source.end(), source.begin(), tolower);
	Print(SentencesParser(source));
}
