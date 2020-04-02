//Mastermind game
//Benjamin Downey

#include<iostream>
#include <array>
#include <string>
#include <algorithm>
#include<ctime>

using namespace std;

void rules();
int fixcode(array<int, 8> &a5, int,int,int);
int correctguess(array<char, 6> &a1, array<char, 6> &a2);
int correctcolor(array<char, 6> &a1, array<char, 6> &a2);
void arrayofguesses(array<array<char, 8>, 15> &a2, array<char, 6> &a3, int, int, int, int);
//void printArray(char array[][15]);

int tries{0};


//function main begins execution
int main()
{
	//initializing variables
	string name{};
	int level{0};
	char rule{};
	char guess{};
	char guess2{};
	char guess3{};
	char guess4{};
	char guess5{};
	char guess6{};
	char picklevel{'y'};
	int playagain{0};
	int turns{0};
	int color{0};
	int number{0};
	int cplace{0};
	int ccolor{0};
	int win{0};
	int lose{0};
	//array of all the previous guesses
	array<array<char, 8>, 15>arrayofguesses1;
	//random generator
	srand(static_cast<unsigned int>(time(0)));
	//some random array helps not create doubles in mastercode
	array<int, 8> numberguessarray{9,9,9,9,9,9,9,9};
	
	//gives an array of all the color choices
	array<char, 8> colorchoice{'R', 'O', 'Y', 'G', 'B', 'P', 'T', 'S'};
	//create correctarray the master code move to beginning
	array<char, 6> correctarray;
	//innitalizes an array to copy correctarray to.
	array<char, 6>correctarray2;
	//creates guess array
	array<char, 6> guessarray;
	//creates a copy of guess array
	array<char, 6> guessarray2;
	
	//welcome message
	cout<<"Welcome to this game of mastermind.";
	cout<<"\n What is your name? ";
	cin>>name;
	cout<<name<<", would you like to know the rules? (y or n)";
	cin>>rule;
	if (rule=='y') {
		rules();
	}
	else{
		cout<<"Good luck "<<name<<"\n";
	}
	
	//while lets them pick a new level if they want too when playing again
	while (playagain==0){
		
		
		if (picklevel=='y'){
		//pick a level
		cout<<"Which level would you like to play?(1, 2, or 3) ";
		cin>>level;
		
		switch (level) {
			case 1:
				cout<<name<<", you chose the easy level. \n";
				cout<<"You get 4 colors, 4 guesses, and 10 turns.\n";
				color=4;
				number=4;
				turns=10;
				break;
				
			case 2:
				cout<<name<<", you chose the medium level. \n";
				cout<<"You get 6 colors, 4 guesses, and 12 turns. \n";
				color=6;
				number=4;
				turns=12;
				break;
				
			case 3:
				cout<<name<<", you chose the hard level. \n";
				cout<<"You get 8 colors, 6 guesses and 15 turns. \n";
				color=8;
				number=6;
				turns=15;
				break;
				
			default:
				cout<<name<<", you did not choose a level so you get easy. \n";
				cout<<"You get 4 colors, 4 guesses, and 10 turns. \n";
				color=4;
				number=4;
				turns=10;
				break;
		}
		}
		
		
		//while stement here lets them keep playing
		//while (playagain==0){
		
		
		for(int j=0; j<6; j++) {
			correctarray[j]='A';
		}
		
		//renitializes numberguessarray
		for(int l=0; l<6; l++) {
			numberguessarray[l]=9;
		}
		
		for(int k=0; k<number; k++){
			correctarray[k]=colorchoice[fixcode(numberguessarray, color, number, k)];
			//correctarray[k]=colorchoice[Mastercode1.fixcode()];
		}
		
		cout<<"the mastercode has been created \n";
		//prints out mastercode
		for(int l=0; l<number; l++) {
			cout<<correctarray[l]<<"  ";
		}
		
		
		for(int k=0; k<6; k++){
			correctarray2[k]='A';
		}
		
		
		//gives an array for each guess
		//sets variable in guess array to something
		for(int j=0; j<6; j++) {
			guessarray[j]='Z';
		}
		//sets variables in guess array2 to something
		for(int k=0; k<number; k++){
			guessarray2[k]='Z';
		}
		
		
		cplace=0;
		tries=0;
		//gives them a certain number of tries
		while (tries<turns && cplace != number){
			//for (int i=0; i<number; i++) {
					cout<<"What color would you like to guess? (";
					for (int j=0; j<color; j++) {
							cout<<colorchoice[j]<<", ";
						}
						cout<<") ";

						if(number==4){
							cin>>guess>>guess2>>guess3>>guess4;
							guessarray[0]=guess;
							guessarray[1]=guess2;
							guessarray[2]=guess3;
							guessarray[3]=guess4;
						}
						else{
							cin>>guess>>guess2>>guess3>>guess4>>guess5>>guess6;
							guessarray[0]=guess;
							guessarray[1]=guess2;
							guessarray[2]=guess3;
							guessarray[3]=guess4;
							guessarray[4]=guess5;
							guessarray[5]=guess6;
						}
		
			
			
			
			//sets guessarray2 equal to guessarray
			for(int k=0; k<6; k++){
				guessarray2[k]=guessarray[k];
			}
			
			//sets correctarray2 equal to correctarray
			for(int k=0; k<6; k++){
				correctarray2[k]=correctarray[k];
			}
			//adds up tries
			tries=tries+1;
			
			//gives correct place and color guess
			cplace=correctguess(correctarray2, guessarray2);
			//cout<<cplace<<" blacks \n";
			
			
			//gives correct color but not correct place
			ccolor=correctcolor(correctarray2, guessarray2);
			//cout<<ccolor<< " whites \n";
			
			//prints out all previous guesses
			arrayofguesses(arrayofguesses1, guessarray, cplace, ccolor, tries, number);
			cout<<"You have tried "<<tries<<" out of "<<turns<<" tries \n\n";
		}
		if (cplace==4){
			cout<<"\a \a"<<"Congratulations, "<<name<<", you won!!!!\n";
			win=win+1;
		}
		else {
			cout<<"\a"<<"Sorry, "<<name<<",you lost. :( \n";
			cout<<"The mastercode was";
			for(int l=0; l<number; l++) {
				cout<<correctarray[l]<<"  ";
			}
			lose=lose+1;
		}
		
		cout<<"your win to lose ratio is "<<win<<" to "<<lose<<"\n";
		cout<<name<<", enter 0 if you want to play again? ";
		cin>>playagain;
		if (playagain==0){
			cout<<name<<", would you like to change levels?(y or n)";
			cin>>picklevel;
		}
	}
		
		cout<<"Thanks for playing";
		return 0;
		
		
};


//end main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//functions
	//prints out rules
	void rules() {
			cout<<"Your job is to guess the code. \n";
			cout<<"Each guess is made by entering a your guess of colors when propmted.\n";
			cout<<"Once placed, the computer will provide feedback by giving a certain  \n";
			cout<<"number of colored pegs. A white peg is for correct color and a \n";
			cout<<"black key peg is placed for each guessed color from the guess which is \n";
			cout<<"correct in both color and position. \n";
	}
	
	//gives a number for the mastercode
	int fixcode(array<int, 8> &numberguessarray, int color, int number, int k) {
			int guess{0};
			int i{0};
			srand(static_cast<unsigned int>(time(0)));
			guess=rand() % color;
			while(i<k) {
				if (numberguessarray[i]==guess){
					guess=rand() % color;
					i=0;
				}
				else{
					i++;
				}
			}
			numberguessarray[k]=guess;
			return guess;
		}
		
		
	//number correct color and correct place
	int correctguess(array<char, 6> &correctarray2, array<char, 6> &guessarray2){
		int black{0};
		for(int i=0; i<6; i++) {
			if (guessarray2[i]==correctarray2[i]) {
				black=black+1;
				guessarray2[i]='Z';
				correctarray2[i]='A';
			}
		}
			return black;
	}
	
		
	//returns number of correct color incorrect place
	int correctcolor(array<char, 6> &correctarray2, array<char, 6> &guessarray2){
			int white{0};
			sort(correctarray2.begin(), correctarray2.end());
			sort(guessarray2.begin(), guessarray2.end());
			bool found{false};
			
			for (int j=0; j<6; j++) {
				found=binary_search(guessarray2.begin(),guessarray2.end(),correctarray2[j]);
				if (found==true) {
					white=white +1;
				}
				else {
					white =white;
				}
			}
			return white;
		}
			
	//prints out all the previous guesses
	void arrayofguesses(array<array<char, 8>, 15> &arrayofguesses1, array<char, 6> &guessarray,int correctguess,int correctcolor,int tries, int number) {
		//sets original guess array and includes black and white
		array<char, 8> answerarray;
		for (int i=0; i<number; i++) {
			answerarray[i]=guessarray[i];
		}
		switch (correctcolor){
			case 4:
			answerarray[number+1]='4';
			break;
			case 3:
			answerarray[number+1]='3';
			break;
			case 2:
			answerarray[number+1]='2';
			break;
			case 1:
			answerarray[number+1] = '1';
			break;
			default:
			answerarray[number+1]='0';
			break;
		}
			
		switch (correctguess){
			case 4:
			answerarray[number]='4';
			break;
			case 3:
			answerarray[number]='3';
			break;
			case 2:
			answerarray[number]='2';
			break;
			case 1:
			answerarray[number] = '1';
			break;
			default:
			answerarray[number]='0';
			break;
		}
		
		
		//arrayofguesses[tries]=answerarray;
		for( int l=0; l<8; l++){
			arrayofguesses1[tries-1][l]=answerarray[l];
		}
		
		cout<<"\n \n Your guesses are \n";
		for(int k=0; k<number;k++){
			cout<<"peg "<<k+1<<"  ";
		}
		
		cout<<"blacks whites\n";
		
		
		for (int i{0}; i<tries; i++){
				for(int j{0}; j<number+2; j++){
					cout<<arrayofguesses1[i][j]<<"      ";
				}
				cout<<"\n";
		}
		
	}