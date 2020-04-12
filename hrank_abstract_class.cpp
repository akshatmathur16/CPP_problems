#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
struct Node *A =NULL;

//          key
//p--------------------q
//|  prev | num| next  |
//p--------------------q

class LRUCache: public Cache
{
    public:
    int cap;
    map<int, Node*> :: iterator itr; 
    map<int, Node*>::reverse_iterator rev_itr;
    
    void InsertNode(int key, int num)
    {
        Node *temp = new Node(key, num);
        temp ->value = num;
        temp ->next = A;
        if(A == NULL)
            A= temp;
        else 
            A->prev = temp;
        temp ->prev = NULL;
        A = temp;

    }
    void DeleteNode(Node *ptr_to_del)
    {
        Node *temp = ptr_to_del;
        if(temp == A) // first node
        {
            if(temp->next != 0)
            {
               Node *temp1=temp->next;
               temp1->prev = NULL;
               delete(temp);
               A = temp1;
               temp = NULL;
               temp1 =NULL;
            }
            else //if its the only Node
            {
                delete(temp);
                A =NULL;
                temp =NULL;
            }
        }
        else if(temp->next == 0) // last node
        {
            temp->prev->next = NULL;
            delete(temp);
            temp = NULL;
        }
        else
        {
            Node *temp1 = temp->prev;
            temp1->next = temp->next;
            Node *temp2 = temp->next;
            temp2->prev = temp->prev;
            delete(temp);
            temp = NULL;
            temp1= NULL;
        }
    }

    LRUCache(int capacity) //constructor 
    {
        cap = capacity;
    }

     void set(int key, int value)
    { 
        int flag = 0;
        Node * temp = A; // temp Node for traversal
        Node * ptr_to_del;
        Node * last_node = A;
        int key_found = 0;

        //traversal logic
        while(temp != NULL)
        {
            if(key == temp->key) // TODO not sure how temp->key is working
            {
                key_found = 1;
                break;
            }
            else 
            {
                key_found =0;
            }
            temp =temp->next;
        }

        if(key_found)  // replacement condition
        {
            DeleteNode(temp);
            InsertNode(key, value);
            //temp->value = value;
            key_found = 0;
        }
        else
        {
        if(mp.size() == cap)
        {
           Node *last_node = A;
            while(last_node->next != 0)
            {
                last_node = last_node->next;
            }
            DeleteNode(last_node);
            mp.erase(last_node->key);
            InsertNode(key, value);
        }
        else
            InsertNode(key, value);
        }

        mp.insert(pair<int, Node*>(key, A));
    }

    int get(int key)
    {
        int val;
        int key_found = 0;   //  to check if key exists
        Node * temp = A; // temp Node for traversal

        while(temp != NULL) {
          if(key == temp->key) {
             val = temp -> value;
             key_found = 1;
             break;
          }
          else
          {
              key_found =0;
          }
          temp = temp -> next;
        } 

        if(key_found)
        {   
            // key found
            DeleteNode(temp);
            InsertNode(key, val);
            key_found =0;
            mp.insert(pair<int, Node*>(key, A));
            return val;
        }
        else
        {
            if(mp.size() == cap)
            {
                Node *last_node = A;
                while(last_node->next != 0)
                {
                    last_node = last_node->next;
                }
                DeleteNode(last_node);
                mp.erase(last_node->key);
                InsertNode(key, val);
            }
            else
            {
                val = -1;
                InsertNode(key,val);
            }
          mp.insert(pair<int, Node*>(key, A));
          return -1;
        }

    }
};



int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
