/* Lucas Voron
 * COEN 79
 * Lab 1
 * Program 4 */

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main() {
	string input;

	cout << "Think of a number between 1 and 20 \n";
	
	int array[20];
	for(int i=0; i<20; i++)
		array[i]=0;
	int number=0;
	for(int i=0; i<20; i++)
	{
		int random = rand() % 20 + 1;
		string input2;

		if(array[random-1]==0)//check if that spot in the array is empty, if yes, continue, if full, return to loop
		{
			array[random-1] = random;
			cout << "Is the number " << random << "?" << endl;
			number++;
			cin >> input2;
			if(input2 == "Y" || input2 == "y" || input2 == "yes")//if next input is Y, stop
			{
				cout << "I found the number in " << number << " steps!" << endl;
				break;
			}
			else if(input2 != "N" && input2 != "n" && input2 != "no")//if next input is not Y or N, give warning
				cout << "The input must be Y or N!" << endl;
		}
		else
			i--;
	}
}
