/* Lucas Voron
 * COEN 79
 * Lab 1
 * Program 2 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
	string input;
	string oginput;
	int k = 15;

	cout << "Type in a string of 10 digits (no spaces): \n";
	cin >> input;

	oginput = input;

	if(input.length() != 10)
	{
		cout << "String is incorrect length \n";
		return 0;
	}
	for(int i=0; i<10; i++)
	{
		if(input[i]<'0'|| input[i]>'9')
		{	
			cout << "String contains non-digit characters \n";
			return 0;
		}
	}
	for(int j=0; j<5; j++)
	{
		cout << setw(k);
		cout << oginput << setw(10);

		for(int i = input.length()-1; i>=0; i--)
		{
			cout << input[i];
		}
		cout << endl;
		k+=2;
	}
}
