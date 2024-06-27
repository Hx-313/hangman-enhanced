#include <iostream>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include<vector>
#include <Windows.h>
#include<fstream>
#include<iomanip>
#include <cctype> /// for cases
#include<bits/stdc++.h>///include standard remplate library
#define esc 27


/// left =35
/// right = 78 
using namespace std;
enum color{ //enumeration is a user-defined data type
	NONE,
	DARK_BLUE,
	GREEN,
	DARK_CYAN,
	DARK_RED,
	PURPLE,
	DARK_YELLOW,
	NORMAL,
	GRAY,
	BLUE,
	LIME,
	CYAN,
	RED,
	PINK,
	YELLOW,
	WHITE
};
void gotoXY(int , int);
void setcolor   (color newColor);
void timer();
int PrintHeaderFooter(int ,int , int  , int   );
void DrawHangman(int errors=0);
void hanger();
int  PrintBody(int  , int , int );
void Layout();
int triesLeft(string , string );
bool PrintAndCheckWin(string ,string );
void firstscreen();
void ebod();
void finalScreen();
void info();
void showTabular();
void write_data();
void class_result();
//// Global Variables
//int doo;
int myarr= 0;  ///// for writing and getting data from file 
int AskDifficulty=0;
double maxtime=45;
string word;
/////Filing variables////
string name;//// from User
	int errors; /// inside get data functon///
	string mode; /////insode getdata function
	string Win = " Lose ";    //// from control function
	/////////
class BasicFunctionality
{
	
	public:
		void PrintLetters(string , char , char);
		void AvailableLetters(string);
		string LoadRandomWord( int);
		int triesLeft ( string , string);
		int Difficulty();
};

class hangingman : public BasicFunctionality
{
	
	public:
		void DrawHangman(int );
	
};
class Game: public BasicFunctionality
{
	int tries ;
	string   Guessed;
	bool win;
	
	public:
		Game()
		{
			tries = 0;
			Guessed="";
			win = false;
			
		}
		bool PrintandCheckWin(string , string );
		void Control();
		bool returnResult();
		int retunTries()
		{
			return tries;
		}
		
	
};

class User : public BasicFunctionality 
{
	string Username;
	string comm;
	int moves;
	int Mode; /// 1. Rokie 2. Veteran 3.Expert 4.Against Friend
	public:
		User()
		{
			Username = "";
			moves = 0;
		}
		void getdata();
		void Result(int , bool);
		string Comment(bool);
		string returnUsername()
		{
			return Username;
		}
		string returnMode()
		{
			if (Mode == 4)
			return " VsHuman";
		if ( Mode == 3)
		return "Expert";
		if (Mode == 2)
		return "Veteran";
		if ( Mode == 1)
		return "Rookie";
	}
};

int main ()
{
	
	firstscreen();
	
	 return 0;
	
}

////console control///
void gotoXY(int x, int y) 	//function to decide location of the screem
{
	//A "handle" is a generic identifier (typically a pointer) used to represent something
	//Retrieves a handle to the specified standard device (standard input, standard output).
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
	COORD CursorPosition; 
	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	//Sets the cursor position in the specified console screen buffer.
	//A COORD structure that specifies the new cursor position, in characters. The coordinates are 
	//the column and row of a screen buffer character cell. The coordinates must be within the 
	//boundaries of the console screen buffer.
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}
 ////  for header and footer

/////Color chnage of console
void setcolor   (color newColor) 
{
	//A "handle" is a generic identifier (typically a pointer) used to represent something.
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), (newColor ) );
}
 int PrintHeaderFooter(int iterator=0 ,int y = 4, int R= 78 , int L =35)
{ 
setcolor(DARK_CYAN);
gotoXY(L,y);
	  	cout<<"*------------------------------------------*";
	
      for (int i=0;i<iterator;i++)
      {
	  	gotoXY(L,++y);
		cout<<"|";
		gotoXY(R,y);
		cout<<"|";
	}
		gotoXY(L,++y);
	  	cout<<"*------------------------------------------*";
		return ++y;
}

//// for basic boundaries///
int  PrintBody(int y=0 , int R= 78 , int L = 35)
{
	int i= y;
	  	while ( y<= i+13)
	  	{
	  		gotoXY(L,y);
	  		cout<<"|";
	  		gotoXY(R,y);
	  		cout<<"|";
	  		y++;
		  }
		  return y++;
		 
		  
}

/////  To call both to Assemble LAyout

void Layout()
{
		int line=0;

line = PrintHeaderFooter(3);
line = PrintBody(line);
line = PrintHeaderFooter(1 ,line);
line = PrintHeaderFooter(3 ,line);
line = PrintHeaderFooter(3 ,line);
 hanger();
}

/////Hanger /////
void hanger()
{
	
	gotoXY(46,6);
	setcolor(DARK_YELLOW);
	cout<<" Let's Hang The Man";
	setcolor(DARK_RED);
	gotoXY(50, 9);
	cout<<"============";
	for (int i=0;i<=12;i++)
	if (i<2)
	{
		gotoXY(61,i+10);
		cout<<"||";
		gotoXY(50,i+10);
		cout<<"| ";
	}
	else 
	{
		gotoXY(61,i+10);
		cout<<"||";
	}
	gotoXY(50, 22);
	cout<<"=======================";
}



///// printing available letters here////
void  BasicFunctionality::PrintLetters(string input, char from ,char to)
{    string s;
	for( char i=from; i<=to;i++)
	{
		if (input.find(i)==string::npos) // find will check if string contain characyer in "i"//
		{
			s += i;
			s+="  ";
		}
		else 
		{
			s += " _ ";
		}	
	}
	
		cout<<s;
}
 ////it wil call and print letters in game page////
void BasicFunctionality :: AvailableLetters(string taken)
{   gotoXY(48,24);
setcolor(DARK_YELLOW);
    cout<<"AVAILABLE LETTERS";
    gotoXY(41,27);
	PrintLetters(taken,'A','J');
	gotoXY(40,28);
	PrintLetters(taken,'K','U');
	gotoXY(48,29);
	PrintLetters(taken,'V','Z');
	
}

//// loading word///
string  BasicFunctionality:: LoadRandomWord ( int AskDiff)
{
	string word ; 
	string path ;      ///word that is loaded from the file///
	vector<string> v;   ///  special type of an array that resize dynamically according to rquirement///it is an array of strings
    if ( AskDiff == 1)
    path="EASY.txt";
    if ( AskDiff == 2)
    path ="MEDIUM.txt";
    if(AskDiff == 3)
    path =  "HARD.txt";
	
	ifstream reader(path.c_str());     ////path is variable name to get word from file variable name as input///
    if ( reader.is_open())
    {
     	while (getline(reader,word)) ////first argument is from where to get the line 
     	    v.push_back(word);                                 ////second is where to store the line we get from first argument
                                                           	/*push_back function is used to push element into  a vector from the back 
     	                                                    the new value is inserted into the vector at the end when container size increase by one
     	                                                    as [i]=i++; sort of increase */
	    srand(time(0));                      
	   
	   int randomLine=rand()% v.size();                      // rand() is used to to generate random number./// 
	   	     word=v.at(randomLine);                  ///it says that word we will deal with is at randomline (1 or 2 or 3) may be //                                               
				 	
		  reader.close();		 	
	}		
	return word;
}


//// how many tries left///
int BasicFunctionality :: triesLeft(string word , string  guessed)
{
	
		int errors=0 ;
		for (int i=0 ; i<guessed.length();i++)
		{
			if(word.find(guessed[i])==string::npos)  ///means does not contain
		    	errors++;
		}
		return errors;
	
}

///fifficulty check///
int BasicFunctionality ::Difficulty()
{
	
 } 


////Hangman////
void hangingman::DrawHangman(int errors=0)
{
	if (errors >= 1)
	{
		gotoXY(50,12);
		cout<<"O";
		cout<<"\a\a\a";	
	}
	 if (errors >= 2)
	{
		gotoXY(50,13);
			cout<<"|";
	}
	 if (errors == 3)
	{
		gotoXY(49,14);
			cout<<"/ ";
	}
	 else if (errors >= 4)
	{
		gotoXY(49,14);
			cout<<"/ \\";
	}
	 if (errors >= 5)
	{
		gotoXY(50,15);
			cout<<"|";
	}
	 if (errors == 6)
	{
		gotoXY(49,16);
			cout<<"/ ";
	}
	 else if (errors == 7)
	{
		gotoXY(49,16);
	 		cout<<"/ \\";
	}
}

bool Game :: PrintandCheckWin(string wordG , string guessed)
{
  bool won=true;
  string s;
  	for (int i=0;i<wordG.length();i++)////spots will be equal to word we enter by ".length " function///
  	{
  		if(guessed.find(wordG[i])== string::npos)//it will find guessed character in given string if return false then/// 
  		{
  			won=false;
  		
  			s+=" _";
		  }
		else 
		{
			s+=wordG[i];  //if it will find guessed character in given string then it will print that guessed character//
			s+=" ";
			won = true;
		  } 
	  }
	  gotoXY(50 , 32);
	  cout<<" GUESSED WORDS";
	  int length = wordG.length();
	  int x = ( 21 - ( length / 2 ) +30 )  ; ////to center allign text 
	  gotoXY(x, 34); 
		 cout<<s;
		  return won;
}
void ebod()
{
 			
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY(x,4);	
			cout<<char(205);
			}
			for(int x = 20; x < 103; x++){
			setcolor(PURPLE);
			gotoXY(x,12);	
			cout<<char(205);
			}

			for(int x = 5; x < 12; x++){
			setcolor(CYAN);
			gotoXY(20,x);	
			cout<<char(186);
			}
			for(int x = 5; x < 12; x++){
			setcolor(CYAN);
			gotoXY(103,x);	
			cout<<char(186);
			}
			setcolor(CYAN);

			gotoXY(20,4);	
			cout<<char(201);
			gotoXY(103,4);	
			cout<<char(187);
			gotoXY(103,12);	
			cout<<char(188);
			gotoXY(20,12);	
			cout<<char(200);
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY(20,x);	
			cout<<char(186);
			}
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY(x,16);	
			cout<<char(205);
			}
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY(103,x);	
			cout<<char(186);
			}


			setcolor(CYAN);
			gotoXY(103,16);	
			cout<<char(188);
			gotoXY(20,16);	
			cout<<char(200);

}
void Game:: Control()
		{
				std::clock_t start;
                start = std::clock();
			hangingman hg;
			Layout();
			do
			{
				
				hg.DrawHangman(tries);
				hg.AvailableLetters(Guessed);
			    win = PrintandCheckWin(word, Guessed);
			    
			    char x;
			    gotoXY( 35 , 36 );
	            cout<<">";x=getch(); 
	            if(x > 'a' && x<'z')
				   x= toupper(x);
				 cout<<x;
	            if (Guessed.find(x)==string::npos)//check wheter guesses contain it or not if not it will add x to guesses if already contained it willl leave         
	              {
	              	Guessed += x; 
				  }
	            
	            tries= BasicFunctionality:: triesLeft(word,Guessed);
	            if (win)
	            {
	            	system("pause");
	            	Win = " Win ";
	            	break;
				}
	            
	            
		}while(tries <7);
	}
	bool Game::returnResult()
	{
		return win;
	}
	/////if user selects new game the control will come here from first scren//
	void User :: getdata()
		{
			ebod();
			gotoXY(21 , 5);
			setcolor(GRAY);
			cout<<"Enter Your Username...";
			cin.ignore();
			getline(cin, Username);
			name = Username;
			
			int doo;
			doo:
			system("cls");
			ebod();
			gotoXY(24, 6);
			cout<<"Hi! "<<Username<<" Which game mode you want to select?";
			gotoXY(55, 8);
			cout<<"1---> Human Vs Human";
			gotoXY(55,9);
			cout<<"2---> Human Vs AI";
			int x=0;
			cin>>x;
			if(x == 1)
			{
				system("cls");
				ebod();
				Mode = 4;
				gotoXY(24, 6);
				cout<<"Hmmm! Seems Got a challenging friend....";
				gotoXY(24,7);
				cout<<" Lets Challenge Your Friend...";
				gotoXY(24,8);
				cout<<"Enter the word to Guess...";
				cin.ignore();
				getline(cin, word);
				 transform(word.begin(), word.end(), word.begin(), ::toupper);
				gotoXY(22, 13);
				cout<<"---> Mode you selected is playing against a Friend...";
				gotoXY(22, 14);
				cout<<"---> You challenged your friend with word...";
				gotoXY(55, 15);
				cout<<"\""<<word<<"\"";
				gotoXY(22,17);
				cout<<"press esc to reselect...";
				
				gotoXY(22,18);
				cout<<"Press any key to continue...";
				char ch= getch();
				if (ch==27)
				goto doo;
				system("cls");
			}
			else if (x == 2)
			{
				
					system("cls");
					ebod();
				gotoXY(24, 6);
				cout<<" Hmmm!! Looks Promising...";
				gotoXY(24 , 7);
				cout<<" Select difficulty Level...";
				gotoXY(55, 8);
				cout<<"1--> Rookie";
				gotoXY(55, 9);
				cout<<"2---> Veteran";
				gotoXY(55, 10);
				cout<<"3---> Expert";
				int X;
				gotoXY(55,11);
				cin>>X;
				AskDifficulty = X;
				Mode = X;
				word =LoadRandomWord(X);
					gotoXY(22, 13);
					cout<<"---> So you Challenging me...";
					string Mode;
					if (AskDifficulty == 1)
					Mode = "\"Rookie\"";
					if (AskDifficulty ==  2)
					Mode = "\"Veteran\"";
					if(AskDifficulty == 3)
					Mode = "Expert";
					gotoXY(22, 14);
				cout<<"---> Mode You Selected is ...";
				gotoXY(55, 15);
				cout<<Mode;
				gotoXY(22,17);
				cout<<"press esc to reselect...";
				
				gotoXY(22,18);
				cout<<"Press any key to continue...";
				char ch= getch();
				if (ch==27)
				goto doo;
				system("cls");
			}
			Game g ;
	Layout();
	g.Control();
	system("cls");
	errors = g.retunTries();
	mode = returnMode();
	Result(g.retunTries() , g.returnResult() );
	 finalScreen();
			
	}
	/////Make Comments///
	string  User :: Comment(bool won)
	{
		string comm;
		if (won == false)
		{
			comm= "You will guess it next time (< o) ";
		}
		else if (Mode == 4  && won)
		comm= " It's Your turn to challenge now!!!";
		else if ( Mode == 3 && won)
		comm = "You'r a true Expert";
		else if (Mode == 2 && won)
		comm = "Future expert is in Progress...  ";
		else if ( Mode == 1)
		comm = " Not a Rookie Anymore";
		  
		  return comm;
	}
		/////to display game result////
		
void User :: Result(int Try , bool Won)
	{
			int f=30;
	setcolor(RED);
	gotoXY(0,3);
	cout<<"  _____                 _ _   "<<endl;
	gotoXY(0,4);
	cout<<" |  __ \\               | | |  "<<endl;
	gotoXY(0,5);
	cout<<" | |__) |___  ___ _   _| | |_ "<<endl;
	gotoXY(0,6);
	cout<<" |  _  // _ \\/ __| | | | | __|"<<endl;
	gotoXY(0,7);
	cout<<" | | \\ \\  __/\\__ \\ |_| | | |_ "<<endl;
	gotoXY(0,8);
	cout<<" |_|  \\_\\___||___/\\__,_|_|\\__|"<<endl;
	
	setcolor(YELLOW);
gotoXY(f,1);
cout<<"                     ,---.           ,---.   "<<endl;
gotoXY(f,2);
cout<<"                    / /^`.\\.--''''-./,'^\\ \\	"<<endl;
gotoXY(f,3);
cout<<"                    \\ \\    _       _    / /	"<<endl;
gotoXY(f,4);
cout<<"                     `./  / __   __ \\  \\,'	"<<endl;
gotoXY(f,5);
cout<<"                      /    /_O)_(_O\\    \\	"<<endl;
gotoXY(f,6);
cout<<"                      |  .-'  ___  `-.  |	"<<endl;
gotoXY(f,7);
cout<<"                   .--|       \\_/       |--.	"<<endl;
gotoXY(f,8);
cout<<"                 ,'    \\   \\   |   /   /    `."<<endl;
gotoXY(f,9);
cout<<"                /       `.  `--^--'  ,'       \\"<<endl;
gotoXY(f,10);
cout<<"             .-^^^^^-.    `--.___.--'     .-^^^^^-."<<endl;
gotoXY(f,11);
cout<<".-----------/         \\------------------/         \\--------------."<<endl;
gotoXY(f,12);
cout<<"| .---------\\         /----------------- \\         /------------. |"<<endl;
gotoXY(f,13);
cout<<"| |          `-`--`--'                    `--'--'-'             | |"<<endl;
gotoXY(f,14);
cout<<"| |                                                             | |"<<endl;
gotoXY(f,15);
cout<<"| |                                                             | |"<<endl;
gotoXY(f,16);
cout<<"| |                                                             | |"<<endl;
gotoXY(f,17);
cout<<"| |                                                             | |"<<endl;
gotoXY(f,18);
cout<<"| |_____________________________________________________________| |"<<endl;
gotoXY(f,19);
cout<<"|_________________________________________________________________|"<<endl;
gotoXY(f,20);
cout<<"                   )__________|__|__________("<<endl;
gotoXY(f,21);
cout<<"                  |            ||            |"<<endl;
gotoXY(f,22);
cout<<"                  |____________||____________|"<<endl;
gotoXY(f,23);
cout<<"                    ),-----.(      ),-----.("<<endl;
gotoXY(f,24);
cout<<"                  ,'   ==.   \\    /  .==    `."<<endl;
gotoXY(f,25);
cout<<"                 /            )  (            \\"<<endl;
gotoXY(f,26);
cout<<"                 `==========='    `==========='  "<<endl;
	setcolor(CYAN);
	gotoXY(45,14);
	if (Won )
	cout<<"Congratulations You have won...:) ";
	else 
	cout<<"Better Luck Next time!... ";
	setcolor(CYAN);
	gotoXY(35,15);
	cout<<"Name ==>"<<Username;
	setcolor(CYAN);
	gotoXY(35,15);
	cout<<"Word to Guess was ==> "<<word;
	gotoXY(70,15);
	cout<<"Total tries  ==> 7";
	setcolor(CYAN);
	gotoXY(35,16);
	cout<<"You guessed in (tries) ==> "<<Try;
	gotoXY(70,16);
	//cout<<"your Rank ==> "<<rank;
	setcolor(CYAN);
	gotoXY(35,17);
	comm = Comment(Won);
	cout<<"Comments==> "<<comm;
getch();
//write_data();
	
}
//// instruction page///
void info()
{
	setcolor(RED);
	gotoXY(56,4);	
		cout<<"Instruction"<<endl;
	setcolor(GREEN);
	gotoXY(50,5);	
		cout<<"Press Enter to Home Menu"<<endl;
	
		setcolor(LIME);
		gotoXY(38,6);	
		cout<<"   ________________________________________"<<endl;
		gotoXY(38,7);
		cout<<" / \\                             	         \\."<<endl;
		gotoXY(38,8);
		cout<<"|   |                                      |."<<endl;
		gotoXY(38,9);
		cout<<" \\_ | Select==>                            |."<<endl;
		gotoXY(38,10);
		cout<<"    | All the alphabets Valid  (a,b,c,d)   |."<<endl;
		gotoXY(38,11);
		cout<<"    | You have 7 seven tries if all        |."<<endl;
		gotoXY(38,12);
		cout<<"    | exhauted you will lose               |."<<endl;
		gotoXY(38,13);
		cout<<"    |                            	   	 |."<<endl;
		gotoXY(38,14);
		cout<<"    | Modes==>                             |."<<endl;
		gotoXY(38,15);
		cout<<"    | Human vs Human                       |."<<endl;
		gotoXY(38,16);
		cout<<"    | Human vsAI ( Rookie,Veteran ,Expertd)|."<<endl;
		gotoXY(38,17);
		cout<<"    | Rule==>                              |."<<endl;
		gotoXY(38,18);
		cout<<"    | For every wrong guess The one body   |."<<endl;
		gotoXY(38,19);
		cout<<"    | one body part of man built.          |."<<endl;
		gotoXY(38,20);
		cout<<"    | There are 7 body parts once all done |."<<endl;
		gotoXY(38,21);
		cout<<"    | you wil lose                         |."<<endl;
		gotoXY(38,22);
		cout<<"    | Team will be given 60 seconds for    |."<<endl;
		gotoXY(38,23);
		cout<<"    | each Guess                           |."<<endl;
		gotoXY(38,24);
		cout<<"    |                            	         |."<<endl;
		gotoXY(38,25);
		cout<<"    | Identification==>                    |."<<endl;
		gotoXY(38,26);
		cout<<"    | Enter  UserName for Recod            |."<<endl;
		gotoXY(38,27);
		cout<<"    | save                          	 |."<<endl;
		gotoXY(38,28);
		cout<<"    |   ___________________________________|___"<<endl;
		gotoXY(38,29);
		cout<<"    |  /                                      /."<<endl;
		gotoXY(38,30);
		cout<<"    \\_/______________________________________/."<<endl;
	
}
			

//simply desgin screen
void firstscreen()		
{

	doo :
	system("CLS");		
						setcolor(NORMAL);
			cout<<"\n\n\n\t\t\t\t   __      __   ___  | |   ___    ___    _ __ ___     ___  "<<endl;
			cout<<"\t\t\t\t   \\ \\ /\\ / /  / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\ "<<endl;
			cout<<"\t\t\t\t    \\ V  V /  |  __/ | | | (__  | (_) | | | | | | | |  __/ "<<endl;
			cout<<"\t\t\t\t     \\_/\\_/    \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___| "<<endl;
	setcolor(GREEN);
	gotoXY(50,20);
	cout<<" >>";
	gotoXY(74,20);
	cout<<" >>";
	gotoXY(54,20);
	setcolor(WHITE);
	cout<<"Press Enter Continue";
	Beep(500, 100);
	gotoXY(45,10);
	cout<<"======Select Following Option ======";
	gotoXY(50,12);
	cout<<"1-->  New Game";
	gotoXY(50,13);
	cout<<"2-->  Instructions";
	gotoXY(50,14);
	cout<<"3-->  Result Record";  
	gotoXY(42,16);
	cout<<"Select : ";    
	Beep(500, 100);
	go:                                     
	int type;
	gotoXY(51,16);
	cin>>type;	
	switch(type)
	{
		case 1:
			{
						system("CLS");
			
		
			User u ;
			u.getdata();	
			break;
			}
	case 2:
			{
			system("CLS");
	
			info();
			getch();
			goto doo;
			break;
			}
			case 3:
			{
			system("CLS");		
				setcolor(GREEN);
			class_result();
			
			system("CLS");
			goto doo;
			break;
			}

		 default:
			{
			cout<<"/n INVALID CHOICE";
			goto go;
		}
	}
	//system("CLS");
		
}
void finalScreen()
{
	char ch;
	write_data();
	system("cls");
	system("COLOR 8F");
	gotoXY(55,15);
	cout<<"===>Do you want to pla again....";
	gotoXY(60, 16);
	cout<<"press A";
	gotoXY(55,17);
	cout<<"===> Press any key to exit";
	
	gotoXY(55,18);
	ch = getch();
	ch = toupper(ch);
	if(ch == 'A'){
	system("cls");
	firstscreen();
}
	else 
	{
		system("cls");
		system("COLOR 8F");
		gotoXY(55,15);
		cout<<"GOOD BYE!!!";
	 } 
}
void showTabular()
		{
			cout<<name<<setw(15)<<mode<<setw(10)<<word<<setw(10)<<errors<<setw(15)<<Win<<endl;
	     myarr++;
		}
/////writing data/////
void write_data()
{
	
	ofstream outFile;
	outFile.open("Hangman.txt",ios::app);
	outFile<<name<<setw(8)<<mode<<setw(8)<<word<<setw(8)<<errors<<setw(8)<<Win<<endl;
	outFile.close();
   
}
//***************************************************************
//    	function to display all students grade report
//****************************************************************

void class_result()
{
	ifstream inFile;

	inFile.open("Hangman.txt");
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		
	}

	cout<<"\n\n\t\tALL Users RESULT \n";
	cout<<"\n\t\tPress Enter to Go Back Home Screen\n";
	cout<<"==========================================================\n";
	cout<<"Name              Mode      GuessWord     erros       win     "<<endl;
	cout<<"==========================================================\n";
	while(inFile>>name>>mode>>word>>errors>>Win)
	{
showTabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
