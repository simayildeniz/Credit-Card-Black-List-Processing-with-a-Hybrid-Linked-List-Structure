# include <iostream>
# include <string>
using namespace std;


struct creditCardNode  //singlelinklist
{  
	string creditCardNo;  
	creditCardNode * next;    
};

struct expirationNode  // doublelinklist
{  
	int month, year;  
	creditCardNode * cHead;  
	expirationNode * next;  
	expirationNode * prev; 
}; 

class CardList  
{ 
	private:
		//head and tail
		
		expirationNode *head;
		expirationNode *tail;

	public:  

		CardList(); //default constructor that creates an empty list  

		void insertCard (string creditCardNo, int month, int year); //inserts a new card to the structure in sorted fashion  
		void displayListChronological ();  //displays entire structure in chronological order  
		void displayListReverseChronological ();  //displays entire structure in reverse chronological order  
		void cardSearch (string creditCardNo);  //displays all of the occurrences of the given card number  
		void bulkDelete (int month, int year);  //deletes all nodes up to and including given expiration date  
		void deleteAll (); //deletes the entire structure private:  expirationNode * head;  expirationNode * tail; 
		
		// any helper functions you see necessary 
		bool isEmpty();
}; 