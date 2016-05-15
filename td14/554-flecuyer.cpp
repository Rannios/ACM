#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

// 554 - Caesar Cypher


string caesar(string s, int offset)
{
	for(int i=0; i<s.size(); i++)
	{
		int c = 0;
		if(s[i] != ' ')
			c = s[i] - 'A' + 1;
		c = (c+offset) % 27;
		s[i] = (c == 0 ? ' ' : 'A' - 1 + c);
	}
	return s;
}

void print(string s)
{
	int cursor;
	stringstream ss(s);
	string word = "";
	do
	{
		cursor = 0;
		while(cursor + (cursor>0) + word.size() <= 60)
		{
			if(word.size())
			{
				if(cursor) cout << " ";
				cout << word;
				cursor += word.size() + 1;
			}
			if(!(ss >> word)) { cursor = -1; break; }
		}
		cout << endl;
	} while(cursor >= 0);
}

int main()
{
	map<string, bool> d;
	string word;
	while(getline(cin, word) && word[0] != '#')
		d[word] = true;

	string sentence;
	getline(cin, sentence);
	vector<int> score(27, 0);
	for(int offset=0; offset<27; offset++)
	{
		string s = caesar(sentence, offset);
		string cword;
		int i = 0;
		do
		{
			cword = "";
			while(i < s.size() && s[i] != ' ')
				cword += s[i++];
			if(d[cword])
				score[offset] ++;
		} while(++i < s.size());
	}

	int best_offset = 0;
	for(int offset=0; offset<27; offset++)
	{
		if(score[offset] > score[best_offset])
			best_offset = offset;
	}

	print(caesar(sentence, best_offset));

	return 0;
}