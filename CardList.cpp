# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include "CardListHeader.h"

CardList::CardList()
{
	head = NULL;
	tail = NULL;
}
bool CardList::isEmpty()
{
	if (head == NULL)
	{
		return true;
	}
	return false;
}

/* Begin: code taken from 3rd Week slides and updated  */ 
void CardList::insertCard(string creditCardNo, int month, int year)
{
	// pre: list is sorted
	// post: add newkey to list, keep list sorted
	{
		expirationNode *  ptr = head;   // loop variable for doublelinklist
		// if new node should be first, handle this case  
		// in this case, we return address of new node since it is new head  
		if (head == NULL)
		{
			// en bastaki nodeu olustrumak icin:
			head = new expirationNode;
			head->month = month;
			head->year = year;
			head->next = NULL;
			head->prev = NULL; 
			head ->cHead = new creditCardNode;
			head->cHead->creditCardNo = creditCardNo;
			head->cHead->next = NULL;
			tail = head;
			cout << creditCardNo << " " <<month<< " "<< year <<": added to a new expiration date node" << endl;
			return;
		}
		bool isBelowWhileFound = false;
		while (ptr != NULL && isBelowWhileFound == false)     
		{   
			if ((year > ptr->year)) // year bigger   // head same
			{
			}
			else if (year == ptr->year) // year equals
			{
				if (month > ptr->month) // h bigger    // head same
				{
				}
				else if (month == ptr->month)
				{
					isBelowWhileFound = true;
					creditCardNode * iterator = ptr->cHead;
					bool isUnique = true;
					while (iterator != NULL && isUnique == true)
					{
						if ( iterator->creditCardNo == creditCardNo)
						{
							isUnique = false;
							cout << creditCardNo << " " << month << " " << year << ": this card was already inserted " << endl;
						}
						else
						{
							iterator = iterator->next;
						}
					}

					if (isUnique == true)
					{
						cout << creditCardNo << " " << month << " " << year << ":  inserted to an existing expiration date node " << endl;
						creditCardNode * temp = ptr->cHead;
						creditCardNode * prev = NULL;
						bool isFound = false;
						while (temp != NULL && isFound == false)
						{
							if (temp->creditCardNo > creditCardNo)
							{
								if (prev == NULL) //add to beginning
								{
									creditCardNode * toInsert = new creditCardNode;
									toInsert->creditCardNo = creditCardNo;
									toInsert->next = ptr->cHead;
									ptr->cHead = toInsert;
									isFound = true;
								}
								else //add to middle
								{
									creditCardNode * toInsert = new creditCardNode;
									toInsert->creditCardNo = creditCardNo;
									toInsert->next = temp;
									prev->next = toInsert;
									isFound = true;
								}
							}
							prev = temp;
							temp = temp->next;
						} 
						// isfound still false then add to end
						if (isFound == false)
						{
							prev->next = new creditCardNode;
							prev->next->creditCardNo = creditCardNo;
							prev->next->next = NULL;
						}
					}
				}
				else // month smaller   // temp shoulg be the new head // insert in middle
				{
					isBelowWhileFound = true;
					if (ptr->prev == NULL) //if added becomes the head (edge case)
					{
						expirationNode * temp = new expirationNode;
						temp->next = ptr;
						temp->month = month;
						temp->year = year;
						temp->prev = NULL;
						ptr->prev = temp;
						head = temp;
						cout << creditCardNo << " " <<month<< " "<< year <<": added to a new expiration date node " << endl;
						head ->cHead = new creditCardNode;
						temp->cHead->creditCardNo = creditCardNo;
						temp->cHead->next = NULL;
					}
					else
					{
						expirationNode * temp = new expirationNode;
						temp->month = month;
						temp->year = year;
						temp->next =ptr;
						temp->prev =ptr->prev;
						ptr->prev = temp;
						temp->prev->next = temp;
						cout << creditCardNo << " " <<month<< " "<< year <<": added to a new expiration date node " << endl;
						temp ->cHead = new creditCardNode;
						temp->cHead->creditCardNo = creditCardNo;
						temp->cHead->next = NULL;
					}	
				}
			}
			else // year smaller     
			{
				isBelowWhileFound = true;
				if (ptr->prev == NULL) //if added becomes the head (edge case)
				{
					expirationNode * temp = new expirationNode;
					temp->month = month;
					temp->year = year;
					temp->next = ptr;
					temp->prev = NULL;
					ptr->prev = temp;
					head = temp;
					cout << creditCardNo << " " <<month<< " "<< year <<": added to a new expiration date node " << endl;
					head ->cHead = new creditCardNode;
					temp->cHead->creditCardNo = creditCardNo;
					temp->cHead->next = NULL;
				}
				else
				{
					expirationNode * temp = new expirationNode;
					temp->month = month;
					temp->year = year;
					temp->next =ptr;
					temp->prev =ptr->prev;
					ptr->prev = temp;
					temp->prev->next = temp;
					cout << creditCardNo << " " <<month<< " "<< year <<": added to a new expiration date node " << endl;
					temp ->cHead = new creditCardNode;
					temp->cHead->creditCardNo = creditCardNo;
					temp->cHead->next = NULL;
				}	
			}
			
			ptr = ptr->next; 
		}
		// check node one ahead so we don't pass!
		if (isBelowWhileFound == false) // add to end 
		{    
			expirationNode * temp = new expirationNode;
			temp->month = month;
			temp->year = year;
			temp->next = NULL;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
			temp->cHead = new creditCardNode;
			temp->cHead->creditCardNo = creditCardNo;
			temp->cHead->next = NULL;
			cout << creditCardNo << " " <<month<< " "<< year <<": added to a new expiration date node" << endl;
		} // postcondition: new node to be inserted just after the node ptr points
	}
	/* End: code taken from 3rd week lecture slides and updated*/
} 

void CardList::displayListChronological() //option2
{
	expirationNode* ptr;
	ptr = head;
	expirationNode* checkPoint = head;
	if (ptr == tail)
	{
		cout << "List is empty! "<< endl;
		return;
	}
	else
	{
		while(checkPoint !=NULL)
		{
			cout << "Expiration Date: " << checkPoint->month << " " << checkPoint->year <<endl;

			creditCardNode* traverse = checkPoint->cHead;
			int i = 1;
			while (traverse != NULL)
			{
				cout << i << ") " << traverse->creditCardNo << endl;
				traverse = traverse->next;
				i++;
			}
			cout << "------------------- " << endl;
			checkPoint = checkPoint->next;
		}
	}
}
int i = 1;
void reverse(creditCardNode* head)
{
	if(head==NULL)
		return;

	reverse(head->next);
	cout << i <<") "<< head->creditCardNo << endl;
	i++;
}


void CardList::displayListReverseChronological() //option3
{
	expirationNode* ptr;
	ptr = tail;
	expirationNode* checkPoint = tail;
	if (ptr == head)
	{
		cout << "List is empty! "<< endl;
		return;
	}
	else
	{
		while(checkPoint !=NULL)
		{
			cout << "Expiration Date: " << checkPoint->month << " " << checkPoint->year <<endl;
			i = 1;
			creditCardNode* traverse = checkPoint->cHead;
			reverse(traverse);
			cout << "------------------- " << endl;
			checkPoint = checkPoint->prev;
		}
	}
}

void CardList::cardSearch (string creditCardNo) // option4
{
	bool isFound = false;
	expirationNode* ptr;
	creditCardNode* iterator;
	ptr = head;

	if (ptr == NULL)
	{
		cout << "There is no credit card with given credit card number: "<< creditCardNo << endl;
		return;
	}

	iterator = ptr->cHead;

	while (ptr !=  tail->next ) //null degilken
	{
		bool isTemp = false;
		iterator = ptr->cHead;
		while (iterator != NULL && isTemp != true )
		{
			if ((iterator->creditCardNo == creditCardNo))
			{
				isFound = true;
				isTemp = true;
				cout << "There exists a credit card given number "<< creditCardNo << " with expiration date: " << ptr->month << " " << ptr->year << endl;
				
			}
			else
			{
				iterator = iterator-> next;
			}

		}

		ptr = ptr->next;
	}
	if (isFound == false)
	{
		cout << "There is no credit card with given credit card number: " << creditCardNo << endl;
	}


}

void CardList::bulkDelete (int month, int year) // option5
{ 
	expirationNode* ptr;
	expirationNode* tempD;
	creditCardNode* iterator;
	creditCardNode* tempS;
	ptr = head;
	if (ptr == NULL)
	{
		cout << "List is empty! " << endl;
		return;
	}
	while (ptr != NULL)
	{
		iterator = ptr->cHead;
		if (((ptr->year <= year) || (ptr->month <= month && ptr->year == year)))
		{ 
			int i =1;
			cout << "Node with expiration date" << ptr->month << " " << ptr->year << " and the following credit cards have been deleted!" << endl;
			while ((iterator!=NULL))
			{
				tempS = iterator;
				iterator = iterator->next;
				cout << i << ") " << tempS->creditCardNo << endl;
				i++;
				delete tempS;
			}
			tempD = ptr;
			ptr = ptr->next;
			delete tempD;
		}
		else
		{
			head = ptr;
			head->prev = NULL;
			return;
		}
	}
	head = NULL;
	tail = NULL;
}

void CardList::deleteAll () // option6
{
	expirationNode* ptr;
	expirationNode* tempD;
	creditCardNode* iterator;
	creditCardNode* temp;

	ptr = head;

	if (ptr == NULL)
	{
		// list is already empty and I terminate the program here:
		return;
	}

	while (ptr != NULL )
	{
		iterator = ptr->cHead;
		while (iterator != NULL)
		{
			temp = iterator;
			iterator = iterator->next;
			delete temp;
		}
		tempD = ptr;
		ptr = ptr->next;
		delete tempD;
	}
}