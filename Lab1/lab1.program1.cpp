/* Lucas Voron
 * COEN 79
 * Lab 1
 * Program 1 */

#include <iostream>
#include <string>
using namespace std;

int main() {
	int nonalpha=0;
	int alpha=0;
	string input;

	cout << "Type a string: \n";
	getline(cin, input);

	for(int i=0; i<input.length(); i++) //loop itterates through the string of characters
	{
		if(input[i] == ' ')
			nonalpha--;
		if(isalnum(input[i])) //function checks if a character is alphanumeric
			alpha++;
		else
			nonalpha++;
	}

	cout << "Number of non-alphanumeric characters: " << nonalpha << endl;
	cout << "Number of alphanumeric characters: " << alpha << endl;
}

