#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

struct wordPair {
	string word;
	int occurrences = 0;
};


void sanitizeText(string &text) {
	string newText;

	for (unsigned long long int i = 0; i < text.size() - 1; i++) {
		if (isalpha(text[i])) {
			text[i] = tolower(text[i]);
			newText += text[i];
		}
		else {
			if (text[i] == '\n' || text[i] == '-') {
				text[i] = ' ';
			}
			if (text[i] == ' ' && text[i + 1] != ' ') {
				newText += text[i];
			}
		}
	}
	text = newText;
}

vector<string> turnToWords(string& text) {
	vector<string> retVal;
	string word;
	for (unsigned long long int i = 0; i < text.size(); i++) {
		if (isalpha(text[i])) {
			word += text[i];
		}
		else {
			if (text[i] == ' ') {
				if (word != "") {
					retVal.push_back(word);
				}
				word = "";
			}
		}
	}
	return retVal;
}

vector<wordPair> returnPairs(vector<string>& words) {
	vector<wordPair> wordPairs;
	wordPair p1;
	p1.word = words[0];
	p1.occurrences = 0;
	wordPairs.push_back(p1);

	for (unsigned long long int i = 0; i < words.size(); i++) {
	start:

		for (unsigned long long int j = 0; j < wordPairs.size(); j++) {
			if (words[i] == wordPairs[j].word) {
				wordPairs[j].occurrences += 1;
				i++;
				goto start;
			}
		}
		p1.word = words[i];
		p1.occurrences = 1;
		wordPairs.push_back(p1);
	}

	return wordPairs;
}

void sortPairs(vector<wordPair> &wp) {
	for (unsigned long long int i = 0; i < wp.size(); i++) {
		for (unsigned long long int j = 0; j < wp.size(); j++) {
			if (wp[i].occurrences > wp[j].occurrences) {
				wordPair temp = wp[i];
				wp[i] = wp[j];
				wp[j] = temp;
			}
		}
	}
}



vector<wordPair> eliminateShortWords(vector<wordPair> &wp) {
	vector<wordPair> retVal;
	for (unsigned long long int i = 0; i < wp.size(); i++) {
		if (wp[i].word.size() > 5) {
			retVal.push_back(wp[i]);
		}
	}

	return retVal;
}

vector<string> randomSentences(vector<wordPair> &wp2, int sentenceAmount) {
	vector<string> lookupTable;

	for (unsigned long long int i = 0; i < wp2.size(); i++) {
		for (int j = 0; j < wp2[i].occurrences; j++) {
			lookupTable.push_back(wp2[i].word);
		}
	}

	vector<string> sentences;
	
	for (unsigned long long int i = 0; i < sentenceAmount; i++) {
		string sentence = "";
		int sentenceLength = (rand() % 11 + 1) - (rand() % 4 + 1) + 7;
		for (int j = 0; j < sentenceLength; j++) {
			sentence += lookupTable[rand() % lookupTable.size()] + ' ';
		}
		sentence[0] = toupper(sentence[0]);
		sentence[sentence.size() - 1] = '.';
		sentences.push_back(sentence);
	}

	return sentences;
}

int main()
{
	srand(time(NULL));

	string text;
	string line;
	ifstream file("zarathustra.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			text += line + ' ';
		}
	}
	file.close();

	sanitizeText(text);
	vector<string> words(turnToWords(text));
	vector<wordPair> wp(returnPairs(words));
	sortPairs(wp);
	//program ends here, rest is just for fun

	vector<wordPair> wp2(eliminateShortWords(wp));
	vector<string> sentences(randomSentences(wp2, 100));
	
	for (int i = 0; i < sentences.size(); i++) {
		cout << sentences[i] << endl;
	}
	return 0;
}
