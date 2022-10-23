/**
   Project: Implementation of a Queue in C++.
   Programmer: Karim Naqvi
   Course: enel452
   Modified by: Greg Sveinbjornson
   Description: Assignement 4 for ENSE 452,
   implements a queue based on a linked list.
   My assignment was to implement a function insert that
   takes a data element and an integer, and inserts the data
   into the queue at the position specified by the integer.

*/

#include "queue.h"
#include <iostream> 
#include <cstdlib>              // for exit

using namespace std;

Queue::Queue()
{
    head = 0;
    tail = 0;
    nelements = 0;
    verbose = false;

}

Queue::~Queue()
{
    for (QElement* qe = head; qe != 0;)
    {
	QElement* temp = qe;
	qe = qe->next;
	delete(temp);
    }
}

void Queue::remove(Data* d)
{
    if (size() > 0)
    {
        QElement* qe = head;
        head = head->next;
        nelements--;
        *d = qe->data;
	delete qe;
    }
    else
    {
        cerr << "Error: Queue is empty.\n";
        exit(1);
    }
}

void Queue::insert(Data d)
{
    if (verbose) std::cout << "insert(d)\n";
    QElement* el = new QElement(d);
    if (size() > 0)
    {
        tail->next = el;
    }
    else
    {
        head = el;
    }
    tail = el;
    nelements++;
}
/*
    MY CODE
    Insert a new element into the queue at a given position.
    @param d The element to insert.
    @param pos The position to insert the element at.

*/
void Queue::insert(Data d, unsigned position)
{
    if (verbose) std::cout << "insert(d, position)\n";
    QElement* el = new QElement(d);
    if (size() > 0)
    {
        QElement* qe = head;
        for (int i = 0; i < position - 1; i++)
        {
            qe = qe->next;
        }
        el->next = qe->next;
        qe->next = el;
    }
    else
    {
        head = el;
    }
    nelements++;

}

bool Queue::search(Data otherData) const
{
    QElement* insideEl = head;
    for (int i = 0; i < nelements; i++)
    {
        if (insideEl->data.equals(otherData))
            return true;
        insideEl = insideEl->next;
    }
    return false;
}

void Queue::print() const
{
    QElement* qe = head;
    if (size() > 0)
    {
        for (unsigned i = 0; i < size(); i++)
        {
            cout << i << ":(" << qe->data.x << "," << qe->data.y << ") ";
            qe = qe->next;
        }
    }
    cout << "\n";
}

unsigned Queue::size() const
{
    return nelements;
}
