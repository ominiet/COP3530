//
//  Assignment1.cpp
//  
//
//  Created by Oscar Alex Miniet on 2/2/17.
//
//


#include <iostream>
#include <stdio.h>

template <class T>//template allows more than one data type
class Node{//Holds some type of data and a pointer to next node
    public:
    T data;
    Node<T>* next;
    
    Node(const T& dat) : data(dat), next(NULL) {};
    };

template <class T> class LList{
public:
    Node<T>* head;//head and tail pointer for easier insertion
    Node<T>* tail;
    
    void append(T& val);//adds new node to the end of list
    void print();//prints list for final output
    LList();//constructor
    void del(int start, int end, int step);//for deletion stage of problem
    
};
template <class T>
LList<T>::LList(){
    
}
template <class T>
void LList<T>::append(T& data){
    Node<T> * insert = new Node<T>(data);//creates node to add to list
    
    if (head == NULL){//if list is empty, head and tail both point to node
        head = insert;
        tail = insert;
    }
    
    else{//else it points the tail to the new node and updates tail
        tail->next = insert;
        tail = tail->next;
        tail->next = head;//Essentially makes a circularly linked list
        }
}

template <class T>
void LList<T>::print(){//simply prtints each node in list
     Node<T>* pn = head; //pn for print now
    if (pn != nullptr){
        do {
            std::cout << pn->data << " ";
            pn = pn->next;
        } while (pn!= head);
    }
   }

template <class T>
void LList<T>::del(int start, int end, int step){//takes 3 parameters start, end, and step size
    Node<T>* begin = tail;//used to find first occurence ofthe start value
    int run = true;
    int headChecked = 0;
    for(; begin->next->data != start; begin = begin->next){//sets begin pointer to node before start value
        if (begin == tail && headChecked > 0){//breaks loop and prevents deletion loop if not found in list
            run = false;
            break;//prevents infinite loop
        }
        if(begin == tail){
            headChecked++;
        }

    }
    //std::cout << begin;
    Node<T>* last = begin->next->next;         //end must first occurence after begin->next (actual start value)
    for(; last->data != end; last = last->next){//finds end value and prevents infinite loop
            if(last == begin){
            run = false;
            break;
        }
    }
    int tempStep = step;
    Node<T>* temp;//start begin and temp on the same node
    
    while (run == true){
        tempStep = step;//use tempstep in case multiple deletions are needed
        temp = begin;//temp and begin are both at begin at start
        while (tempStep > 0){
            begin = temp; //bring begin to same node as temp
            temp = temp->next;//increment temp
            if (last == temp){
                //std::cout << "TRUE\n";
                run = false;
                
            }
            if (last == temp && step != 1){
                break;
            }
            tempStep--;
            
            if(tempStep == 0){//statement taken on last iteration
                begin->next = temp->next;//if temp needs to be deleted update pointer of previous node
                if (head == temp){//accounts for case of head being removed
                    head = temp->next;
                }
                if (tail == temp){//accounts for tail being removed
                    tail = begin;
                }
                if (begin == temp){
                    head = nullptr;
                }
            }
        }
    }
}


int main(){
    
    LList<int> list;    //list instantiation
    int size;
    std::cin >> size;   //takes size of list (N)
    int x;
    
    while (size > 0){   //loop to create full list
        std::cin >> x;
        list.append(x);
        size --;
    }
    
    int delSeq = 1;
    int start = 0;
    int end = 0;
    int step = 0;
    std::cin >> delSeq;
    while (delSeq > 0){ //loop for deltion part of problem
        std::cin >> start;
        std::cin >> end;
        std::cin >> step;
        list.del(start, end, step);
        delSeq--;
    }
    list.print();       //final print
    return 0;
}
