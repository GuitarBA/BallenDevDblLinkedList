#include "BallenDevDblLinkedList.h"

BallenDevDblLinkedList::BallenDevDblLinkedList()
{
	head = NULL;
	tail = NULL;
}
		
/*Insert a node in it's correct location based on an ascension algorithm*/
void BallenDevDblLinkedList::insert(int key)
{
	Node* currentNode = NULL;
	Node* nodeToInsert = new Node;
	nodeToInsert->key = key;
	nodeToInsert->next = NULL;
	nodeToInsert->prev = NULL;
	
	//Insert the first node if their are not yet any nodes in the list
	if(!head)
	{
		head = nodeToInsert;
		tail = nodeToInsert;
	}
	else
	{
		//Start at the beginning of the list
		currentNode = head;
		
		//Traverse the list and find the location for the node to be inserted
		while(currentNode && currentNode->key < key) //
			currentNode = currentNode->next;
		
		//Inserting at the beginning of the list
		if(currentNode == head) 
		{
			nodeToInsert->next = currentNode;
			currentNode->prev = nodeToInsert;
			head = nodeToInsert;
		}
		//Inserting somewhere within the list
		else if(currentNode)
		{			
			currentNode->prev->next = nodeToInsert;
			nodeToInsert->prev = currentNode->prev;
			currentNode->prev = nodeToInsert;
			nodeToInsert->next = currentNode;			
		}
		//Inserting at the end of the list
		else 
		{
			currentNode = nodeToInsert;
			currentNode->prev = tail;
			tail->next = currentNode;
			tail = currentNode;
		}				
	}
}

/*Delete a node from the list*/
void BallenDevDblLinkedList::dispose(int key)
{
	Node* nodeToDelete = NULL;
	
	if(head)
	{
		//Deleting the head node
		if(key == head->key)
		{
			nodeToDelete = head;
			head = head->next;
			head->prev = NULL;
			delete nodeToDelete;
		}
		//Deleting the tail node
		else if(tail && key == tail->key)
		{
			nodeToDelete = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete nodeToDelete;
		}
		//Traverse the list and find the node to delete
		else
		{
			nodeToDelete = head;
			
			while(nodeToDelete && nodeToDelete->key != key)			
				nodeToDelete = nodeToDelete->next;
			
			//Delete the node and preserve the links if found
			if(nodeToDelete)
			{
				nodeToDelete->prev->next = nodeToDelete->next;
				nodeToDelete->next->prev = nodeToDelete->prev;
				delete nodeToDelete;
			}
			else
				std::cout << "ERROR: key value " << key << " does not exist in the list.\n\n";
		}
	}
	else
		std::cout << "There are no nodes to be deleted.\n\n";
}

/*Get the memory address of the beginning of the list*/
BallenDevDblLinkedList::Node* BallenDevDblLinkedList::getHead() const
{
	return head;
}

/*Get the memory address of the end of the list*/
BallenDevDblLinkedList::Node* BallenDevDblLinkedList::getTail() const
{
	return tail;
}

/*Display the list in ascending order*/
void BallenDevDblLinkedList::displayAscending()
{
	Node* currentNode = NULL;
	
	if(head)
	{
		currentNode = head;
	
		std::cout << "Ascending Order: ";
	
		while(currentNode)
		{
			std::cout << currentNode->key << "\t";
			currentNode = currentNode->next;
		}			
		
		std::cout << "\n";
	}
	else
		std::cout << "No nodes available to display\n\n";
}

/*Display the ist in descending order*/
void BallenDevDblLinkedList::displayDescending()
{
	Node* currentNode = NULL;
	
	if(tail)
	{
		currentNode = tail;
		
		std::cout << "Descending Order: ";
		
		while(currentNode)
		{
			std::cout << currentNode->key << "\t";
			currentNode = currentNode->prev;
		}
		
		std::cout << "\n";
	}
	else
		std::cout << "No nodes available to display\n\n";
}

BallenDevDblLinkedList::~BallenDevDblLinkedList()
{
	Node* currentNode = NULL;
	Node* nextNode = NULL;
	
	int numDeleted = 0;
	
	if(head)
	{
		currentNode = head;
		
		while(currentNode)
		{
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
			
			numDeleted++;
		}
		
		std::cout << numDeleted << " nodes deleted. Memory released.\n";
	}
	else
		std::cout << "No nodes to delete.\n";
}