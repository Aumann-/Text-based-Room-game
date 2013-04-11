/*
Current Status: Compiles, runs with no bugs

Complete: 	Intro: Will be altered later
			Room 1: More or less complete as it is only a syntax tutorial.
			Room 2: Gets guess amount and correctly calls base function

Current work: Room 2 (hide and seek (item))

Notes: 	Need to decide on themes for each room before continuing. 
		Current possible list as follows:
		Number guessing (easy to do, not very interesting)
			
		20 questions (very difficult, will wait til later room for this. 
			Would be easier to have computer ask questions. Assign tags to objects, allow user to enter object name and tag for unknown.
			Have to use txt file for that.
			May consider limiting possible answers to a certain type of object.)
			
		Chatbot (Use for final room, objective unsure. Very difficult to integrate properly.)
		
		Hide and seek (hide an item in the room, player gets certain amount of guesses to find it.) *USED IN ROOM 2*
		
		Rock, Paper, Scissors (very easy, player must win certain amount of games to proceed) *Probably won't use*
		
		Need more.
		
TO DO:
		Add kill message function that displays a random message should player die.
		Rewrite room descriptions.
		Add 'help' command message for room 2.
		Write action check function for room 2.
		Create location variables for room 2.
		May need to use substrings to check for partial commands (ex. search door (outputs based on the word 'search' instead of just a plain error)
		Write new errors for invalid commands.
		
BUGS: 	1/10/13 - 	Room1_correct variable not changing to true when correct action entered *FIXED - Variable change was placed after return statement*
					Room 1 not calling correct action functions and setting flags. *FIXED - Function call for ActionCheck1 was missing, not sure why*
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <ctype.h>

//#include "Database.h"
using namespace std;

const int SIZE = 5;

//additional flags
bool Room1_correct = false; //flag for room 1 correct action. (prevents error from showing if valid, but incorrect action is performed)



//loading function to set room descriptions
void setDesc(string (&Desc)[SIZE]);

//function for invalid commands(commands not in any array)
int Invalid(int);

int Intro(void); //function that displays introductory message/gameplay question (used to limit buildup in main)

//function to convert user action to all lower case
void ConvertLower (string &action);
	
//valid actions function for each room
bool ActionCheck1(string); //checks for valid actions within room 1
bool BaseAction(string, string, int); //checks for generic actions prior to room actions

//room functions
int Room1(string);
int Room2(string);
int Room3(string);
int Room4(string);
int Room5(string);

int random;

int main()
{
	//Intro(); //display intro
	srand (time(NULL)); //seed random number function with current time
	string Description[SIZE]; //set room descriptions
	setDesc(Description);
	//Room1(Description[0]); //start room 1
	Room2(Description[1]);
	//Room3(Description[2]);
	//Room4(Description[3]);
	//Room5(Description[4]);
	
	cout << "You will return." << endl;
	return 0;
}

//function to set room descriptions at game load, used simply to keep main tidy.
void setDesc(string (&Description)[SIZE])
{
	Description[0] = "This is room 1. This room will act as a simple syntax tutorial. There is a stone table. Stand on it.";
	Description[1] = "After walking the short distance from the previous room, you are surprised by the the stark contrast this new room presents.\n"
						"Unlike the very empty first room, this room is tastefully decorated with a variety of furniture.\n"
						"You see a comfy looking sofa, a wooden coffee table, a simple desk, a healthly potted fern, and a soft looking rug.\n";
	Description[2] = "This is room 3.";
	Description[3] = "This is room 4.";
	Description[4] = "This is room 5.";
}


//room 1 overall function (syntax tutorial)
//Simple room, player is told to do a certain thing, must do so to proceed.
int Room1(string Desc)
{
	const int Room_Num = 1;
	string action;
	bool valid = false;
	bool base = false;
	cout << Desc << endl;
	
	while (!valid)
	{
		base = false;
		getline(cin, action); //get player command
		
		ConvertLower (action);
		
		//check for generic command first
		base = BaseAction(action, Desc, Room_Num);
		
		//if not a generic command, check for room-specific command
		if (base == false)
		{
			valid = ActionCheck1(action);
			//checks for valid action and checks room1 correct flag
			if (valid == true && Room1_correct == true)
			{
				cout << "Good. You have proven you have the intelligence of a rodent at least." << endl << endl;
				cout << "You walk through the now open door into the next room." << endl << endl;
				return 0;
			}
			
			else if (valid == true && Room1_correct == false)
			{
				valid = false;
			}
			
			else //if command not valid from either set, display random insult *****************(needs expanding)
			{
				Invalid(Room_Num);
			} //close else
		} //close if (base is false)
	} //close while
} //close function

//room 2 overall function (hide and seek)
//description of room is given with various objects within the room (text identifier only). Player must search room for a unique item.
	//Item is placed using a random number, with locations having a code-based numerical value.
	//Second random number is generated to determine how many guesses the player is given before a kill-script is executed. (May move kill script to separate function)
	//***Consider implementing third random number, executed using dice roll each time player searches. If certain value is rolled, do something***
int Room2(string Desc)
{
	cout << Desc << endl << endl;
	
	const int Room_Num = 2;
	int item_random = rand();
	//randomizes amount of guesses, just for variety
	int guesses = ((rand() % 3) + 2);
	string action;
	bool base = false;
	bool valid = false;
	cout << " \"Welcome to your next trial, try not to drool on anything while you are here.\" \n"
			<< " \"We are going to play a simple game of hide and seek. I have hidden an item somewhere in this room, you have to find it.\n"
			<< "\"To look for it, just type 'search (location)'. Even you should be able to manage that.\" \n\n";
	cout << "\"You have " << guesses << " tries until I release the surprise I have for you. Though I haven't actually decided what that surprise will be.\"" << endl;
	
	getline (cin, action);
	
	base = BaseAction(action, Desc, Room_Num);
	
	if (base == false)
	{
		
	}
	
	return 0;
}

//room 3 overall function
int Room3(string Desc)
{
	cout << Desc << endl;
	return 0;
}

//room 4 overall function
int Room4(string Desc)
{
	cout << Desc << endl;
	return 0;
}

//room 5 overall function
int Room5(string Desc)
{
	cout << Desc << endl;
	return 0;
}

//function to check for valid actions in room 1
bool ActionCheck1(string Action)
{
	string PossibleActions[] = { 	 "flip table",
									 "stand on table",
									 "break table",
									 "kick table",
									 "sleep on table",
									
									};
	
	if (Action == PossibleActions[0]) //check for 'flip table' command
	{
		cout << "The table is too heavy for your pathetic limbs." << endl;
		return true;
	}
	
	else if (Action == PossibleActions[1]) //check for valid action, 'stand on table'
	{
		Room1_correct = true;
		return true;
	}
	
	else if (Action == PossibleActions[2]) //check for 'break table' command
	{
		cout << "You pound on the table to no avail. You are a failure." << endl;
		return true;
	}
	
	else if (Action == PossibleActions[3]) //check for 'kick table' command
	{
		cout << "You injured your foot attempting such a foolish action." << endl;
		return true;
	}
	
	else if (Action == PossibleActions[4]) //check for 'sleep on table' command
	{
		cout << "You lay down on the table in an attempt to fall asleep. A short creak later, a small stone slab falls from the cieling and crushes your head." << endl;
		exit(0);
	}
	
	//if action not in table
	else
	{
		return false;
	}
}


//function for actions that work in any room
bool BaseAction(string action, string Desc, int Room_num)
{
	//list of possible generic commands
	string PossibleActions[] = { 	"look",
									"inventory",
									"dance",
									"cry",
									"run",
									"help",
									"leave",
									"quit",
									"exit",
									"swordfish"
								};
	
	if (action == PossibleActions[0]) //check for look command
	{
		cout << Desc << endl;
		return true;
	}
	
	else if (action == PossibleActions[1]) //check for inventory command
	{
		cout << "You do not have an inventory. How did you not notice?" << endl;
		return true;
	}
	
	else if (action == PossibleActions[2]) //check for dance command
	{
		cout << "You dance like a brainless baboon." << endl;
		return true;
	}
	
	else if (action == PossibleActions[3]) //check for 'cry' command
	{
		cout << "You look pathetic. I almost hope you drown from all your blubbering." << endl;
		return true;
	}
	
	else if (action == PossibleActions[4]) //check for 'run' command, insults player
	{
		cout << "Run where? At the wall? I think you are getting stupider." << endl;
		return true;
	}
	
	else if (action == PossibleActions[5]) //check for help command. checks room number to display proper message
	{
		if (Room_num == 1)
		{
			cout << "This room is just a basic tutorial for the user to see how commands should be entered and what sort of commands are accepted." << endl;
		}
		
		else if (Room_num == 2)
		{
			cout << "This is simply a random number generator test. A number is generated that matches a location in the room. The player must guess where it is." << endl;
		}
		return true;
	}
	
	else if (action == PossibleActions[6]) //check for 'leave' command
	{
		cout << "You can't leave until I let you, but nice try." << endl;
		return true;
	}
	
	else if (action == PossibleActions[7]) //check for 'quit' command
	{
		cout << "Nope, that won't work." << endl;
		return true;
	}
	
	else if (action == PossibleActions[8]) //check for 'exit' command
	{
		cout << "There is no exit, unless your trying to exit your life. Might I suggest running head first into the wall a few times?" << endl;
		return true;
	}
	
	else if (action == PossibleActions[9]) //check for 'swordfish' command
	{
		cout << "OVERRIDE COMMAND FOUND: EXITING." << endl;
		exit(0);
	}
	
	
	else
		return false;
}


int Intro(void)
{
	string choice;
	
	//odd bug if choice is declared as a char. runs fine but upon entering room 1, immediately outputs message as if invalid action was entered. 
	//Changing to string fixes the problem
	
	//introduction message about program, verifies player wants to start. (Will be edited)
	cout << "Welcome to my test area for basic AI development. The basic premise is text-based game divided into separate rooms."
	<< endl << "Each room contains a different type of AI. For each room, enter commands and the narrator AI will give a response." 
	<< endl << "Each room has certain commands that will only work there, while general commands may be used in any room."
	<< endl << "When entering commands, be as specific as possible. If you want to open a door, type 'open door', not just 'open'."
	<< endl << "You may quit at anytime by entering the word 'swordfish'."
	<< endl << "If you want a description of each room, type help in that room."
	<< endl << "Good luck." << endl << endl;;
		
		cout << "Are you ready? Y/N" << endl;
		getline (cin, choice);
	
	while (choice != "Y" || choice != "y" || choice != "N" || choice != "n") //checks for valid choice *may change to accept words 'yes'/'no' as well*
	{
		if (choice == "n" || choice == "N") //if negative, quits program
		{
			cout << "So be it." << endl;
			exit(0);
		}
		
		else if (choice == "Y" || choice == "y") //if positive, display game intro message
		{
			cout << "After another night of being a wasteful human lump, you wake to find yourself in a plain room."
			<< endl << "The only thing you see is a speaker on the ceiling and a closed door on the far wall."
			<< endl << " 'Welcome to my little maze. Past the door in this room is a series of areas, each with a simple test.' "
			<< endl << " 'Pass my tests and I will release you, fail and you shall die. Simple, no?' "
			<< endl << " Considering your lack of options and your low intelligence, you decide to take your chances and enter the now open door. " << endl << endl;
			
			return 0;
		}

		else //if not yes or no character deritive, insults player
		{
			cout << "Are you really having trouble already? There are only two choices, now work that cavernous space you call a skull and enter either a Y or a N." << endl;
			cin >> choice;
		}
	}
}


int Invalid(int Room_num)
{
	random = rand() % 3;
	
	if (Room_num == 1)
	{
			if (random == 0)
				cout << "Follow my instructions." << endl;
		
			else if (random == 1)
				cout << "Obey." << endl;
		
			else if (random == 2)
				cout << "You are a failure." << endl;
	}
	
	return 0;
}

void ConvertLower (string &action) {
//convert command to all lowercase (simpler to check against table)
		for (int i = 0; i < action.length(); i++)
		{
			action[i] = tolower(action[i]);
		}
}

