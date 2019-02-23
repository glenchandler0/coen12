/*
 * File:	deque.h
 *
 *
 * Description:	May 31, 2016, Glen Chandler
 *
 * Summary: Includes createDeque, destroyDeque,
 * numItems, addFirst, addLast, removeFirst, removeLast,
 * getFirst, getLast to be used in maze.c and solve a maze.
 *
 */

class Deque {
    int count;
    
    class Node *head;
    
public:
    int size();
    
    void addFirst(int x);
    
    void addLast(int x);
    
    int removeFirst();
    
    int removeLast();
    
    int getFirst();
    
    int getLast();
    
    Deque();
    
    ~Deque();
};