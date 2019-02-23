/*
 * File:	deque.cpp
 *
 *
 * Description: May 31, 2016 Glen Chandler
 * Summary: Includes createDeque, destroyDeque,
 * numItems, addFirst, addLast, removeFirst, removeLast,
 * getFirst, getLast to be used in maze.c and solve a maze.
 */

#include <cassert>

#include "deque.h"

//Create a struct Node which hold its own data similar
//to the way the Deque class does
//Node is really just a fully public class
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

//Constructor defined for the Deque class.
//'::' defines that this function is being defined for Deque
//O(1)
Deque::Deque()
{
    //Set the private variable of Deque to 0
    //No declared variables are needed because 'count' is referring to member of Deque
    count = 0;
    
    //Create the dummy node for later algorithms
    head = new Node;
    
    //Set next and prev of head back to itself to complete the circular linkedlist
    head->next = head;
    head->prev = head;
}

//Destructor will delete all the nodes present in Deque
//O(n)
Deque::~Deque()
{
    //np will refer to the current pointer
    //next will refer to the pointer after np, so that it can delete memory at location
    Node * np;
    Node * next;
    
    //Set np to head to begin
    np = head;
    //To begin, set next equal to np->next (head->next) to be freed, this way head is preserved
    //Keep doing this until the current (np) is pointing to the head, so the entire Deque is deleted
    do
    {
        next = np->next;
        delete next;
        np = next;
    } while(np != head);
}

//Adds a node with data x to the beginning of the Deque (after head)
//O(1)
void Deque::addFirst(int x)
{
    //Create the node to be added to the beginning, then set the data to x
    Node * np = new Node;
    np->data = x;
    count++;
    
    //The new node will point to head, and head's next, to anchor the pointer
    np->prev = head;
    np->next = head->next;
    
    //Then make the pointers np is pointing to, to point back to np
    np->next->prev = np;
    np->prev->next = np;
}

//Adds a node with data x to the end of the Deque (before head)
//O(1)
void Deque::addLast(int x)
{
    //Create the node to be added ot the end, then set the data to x
    Node * np = new Node;
    np->data = x;
    count++;
    
    //The new node will point to head, and head's prev, to anchor the pointer
    np->next = head;
    np->prev = head->prev;
    
    //Then make the pointers np is pointing to, to point back to np
    np->next->prev = np;
    np->prev->next = np;
}

//Remove the first node in the circular linked list (after head)
//O(1)
int Deque::removeFirst()
{
    //Assert that the count is greater than 0, so head itself is not deleted
    assert(count > 0);
    
    //Create pointer to save the address of the pointer to be deleted
    //while other pointers rearrange themselves
    Node * np;
    
    //Set np to the first pointer in the Deque
    np = head->next;
    
    //Set head->next pointer to the displaced pointer
    //Then set the displaced pointer's prev back to head to close gap
    head->next = np->next;
    head->next->prev = head;
    
    //Save the data of the to be deleted pointer before deleting it
    int x = np->data;
    
    //Delete pointer, decrement count, then return the relevent data
    delete np;
    count--;
    return x;
}

//Remove the last node in the circular linked list (before head)
//O(1)
int Deque::removeLast()
{
    //Asser that the count is greater than 0, so head itself is not deleted
    assert(count > 0);
    
    //Create pointer to save the address of the pointer to be deleted
    //while the other pointers rearrange themselves
    Node * np;
    
    //Set np to the first pointer in the Deque
    np = head->prev;
    
    //Set head->prev pointer to the displaced pointer
    //Then set the displaced pointer's next back to head to close gap
    head->prev = np->prev;
    head->prev->next = head;
    
    //Save the data of the to be deleted pointer before deleting it
    int x = np->data;
    
    //Delete pointer, decrement count, then return the relevent data
    delete np;
    count--;
    return x;
}

//Simply return the first node in Deque, which is the node after head
//O(1)
int Deque::getFirst()
{
    return head->next->data;
}

//Simply return the last node in Deque, which is the node before head
//O(1)
int Deque::getLast()
{
    return head->prev->data;
}

//Simply return the size of the Deque, which is a member of the class
int Deque::size()
{
    return count;
}