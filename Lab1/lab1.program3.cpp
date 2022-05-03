/* Lucas Voron
 * COEN 79
 * Lab 1
 * Program 3 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	ifstream program3(argv[1]); //creates the text file

	string program3output; //used to store output of the text file

	while(program3 && program3.peek() != EOF) {
		program3 >> program3output;
		if(program3output.length() >= 10) {
			for(int i=0; i<program3output.length(); i++)
			{
				if(program3output[i]>='a' && program3output[i]<='z') //check if lowercase, then uppercase
					program3output[i] -= 32;
			
				if((program3output[i]>'0' || program3output[i]<'9') && (program3output[i]<'A' || program3output[i]>'Z')) //if alphanumeric, delete current character
				{
					program3output.erase(i,1); //deletes spaces and non-alphanumeric numbers
					i--;
				}
			}
			cout << program3output << endl;
		}
	}
	program3.close(); //closes text file
}
