#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <fstream>
#include <cstring>
#include <vector>
#include <utility>      // std::pair
#include <unordered_map>
#include <random>

using namespace std;

const int MAX_CHARS_PER_LINE = 2048;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ,.-\n";

string ToLower(char *word) {
	for (; *word; word++) {
		*word = tolower(*word);
	}
	return string(word);
}

std::vector<string> tokenizeFile() {
	ifstream fin;
	vector<string> v;
	fin.open("data.txt"); // open a file
	if (!fin.good()) {
		exit(1);// exit if file not found
	}

	// read each line of the file
	while (!fin.eof())
	{
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		fin.getline(buf, MAX_CHARS_PER_LINE);

		char* word = strtok(buf, DELIMITER);
		while (word != NULL) {

			// need to clean word, for example convert to lower case
			ToLower(word);
			v.push_back(word);

			// continue split
			word = strtok (NULL, DELIMITER);
		}

	}
	return v;
}

unordered_map<string , vector<string>> buildFrequencyTable(std::vector<string> v) {

	// create a file-reading object

	unordered_map<string , vector<string>> mymap;
	unordered_map<string , vector<string>>::iterator mapIt;
	unordered_map<string , vector<string>>::const_iterator got;



	for (int i = 0; i < v.size() - 1; i++ ) {
		// make key of map
		// string key = v[i] + v[i + 1];	// choose to look at previous 2 words
		// string value = v[i + 2];
		string key = v[i] ;
		string value = v[i + 1];

		vector<string> temp;

		// insert key
		got = mymap.find(key);      // find if map already has this key
		if (got == mymap.end()) {	// if map does not  have this key
			mymap.insert(pair<string, std::vector<string> >(key, std::vector<string> {value}));
		}
		else {
			mymap.at(key).push_back(value);
		}


	}
	return mymap;
}

// print frequency table
void printFrequencyTable(unordered_map<string , vector<string>> frequencyTable) {
	for ( auto iter : frequencyTable) {
		// cout << iter.first  << "\t";
		std::vector<string> v = iter.second;
		for (string s : v) {
			// cout << s << ", ";
		}
		// cout << endl;
	}
}

int randomInt(int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, max - 1); // guaranteed unbiased
	return uni(rng);
}
// pick a random start point for Markov tweet
string getStartWord(unordered_map<string , vector<string>> frequencyTable) {
	//pick a random start point
	// get a random number between 0 and size of table
	int random_integer = randomInt(frequencyTable.size());

	string startWord = "";

	int i = 0;
	for (auto iter : frequencyTable) {
		if (i == random_integer) {
			startWord = iter.first;
			break;
		}
		else {
			i++ ;
		}
	}
	return startWord;
}

void printVector(std::vector<string> v) {
	for (string s : v) {
		// cout << s << "\t" << endl;
	}
	// cout << endl;
}

string generate(unordered_map<string , vector<string>> frequencyTable) {
	int random_integer = 0;
	int length = 140;
	int size = 0;
	string tweet = "";
	string startWord = getStartWord(frequencyTable);
	// cout << startWord << endl;

	for (int i = 0; i < length; i ++) {
		// find values of that word
		for (auto iter : frequencyTable) {
			if (iter.first == startWord) {
				// randomly pick word
				std::vector<string> values = iter.second;
				random_integer = randomInt(values.size());
				tweet = tweet + values[random_integer] + " ";
				int len = tweet.length();
				// cout << len << endl;
				if(len >= 140){
					
					return tweet;
				}
				startWord = values[random_integer];
				
				break;
			}
		}
	}
	return tweet;
}


int main()
{
	/*
	in this case, i only look at 1 previous word. 
	*/

	// tokenize input file, extract each word out
	vector<string> wordList = tokenizeFile();
	printVector(wordList);
	
	// build frequency table from word list
	unordered_map<string , vector<string>> frequencyTable = buildFrequencyTable(wordList);
	// pick a random start point, and generte Markov tweet
	string MarkovianTweet = generate(frequencyTable);

	cout << "Final Markovian-tweet is: "<< endl;
	cout << MarkovianTweet << endl;
	// printFrequencyTable(frequencyTable);



	return 1;
}