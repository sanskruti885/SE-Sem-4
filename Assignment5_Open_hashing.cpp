#include<iostream>
using namespace std;
#define table_size 10

class Node{
    int key;
    string value;
    Node *next;
public:
    Node(){
        key = -1;
        value = "";
        next = NULL;
    }
    Node(int k,string val){
        key = k;
        value = val;
        next = NULL;
    }
    friend class Dictionary;
};
class Dictionary{
    Node *table[table_size];
    Node *temp;
    int hash_func(int k){
        return k%table_size;
    }
public:
    Dictionary(){
        for(int i=0;i<table_size;i++){
            table[i] = NULL;
        }
    }
    void insertNode(int k,string val){
        int index = hash_func(k);
        temp = table[index];
        Node *newNode = new Node(k,val);

        if(table[index] == NULL){
            table[index] = newNode;
            return;
        }
        while(temp->next!=NULL){
            if(temp->key == k){
                temp->value = val;
                cout<<"\nUpdated value";
                return;
            }
            temp = temp->next;
        }
        temp->next = newNode;
    }
    void display(){
        for(int i=0;i<table_size;i++){
           temp = table[i];
           while(temp!=NULL){
            if(temp!=NULL){
                 cout<<"["<<temp->key<<":"<<temp->value<<"]";
                 temp = temp->next;
            }
           }
           cout<<"NULL"<<endl;
        }
    }
    void search(int k){
        int index = hash_func(k);
        temp = table[index];

        while(temp!=NULL){
            if(temp->key == k){
                cout<<"\nFound";
                cout<<"\nKey: "<<temp->key<<"\nValue: "<<temp->value;
                return;
            }
            temp = temp->next;
        }
        cout<<"\nNot Found";
    }
    void delete_key(int k){
        int index = hash_func(k);
        temp = table[index];
        Node *prev;
        while(temp!=NULL && temp->key!=k){
            prev = temp;
            temp = temp->next;
        }
        if(temp == nullptr){
            cout<<"\nNot found.";
            return;
        }
        else if(prev == NULL){
            table[index] = temp->next; 
        }
        else{
            prev->next = temp->next;
        }
        cout<<"\nDelete Node";
    }
};
int main(){
    Dictionary dict;
    int choice, key;
    string value;
    char c ='y';
    while(c == 'y'){
        cout<<"\n1.Insert\n2.Display\n3.Search\n4.Delete\n5.Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
            cout<<"\nKey: ";
                cin>>key;
                cout<<"\nValue: ";
                cin>>value;
                dict.insertNode(key,value);
                break;
            case 2:
                dict.display();
                break;
            case 3:
                cout<<"\nEnter the key to search: ";
                cin>>key;
                dict.search(key);
                break;
            case 4:
                cout<<"\nENter key to delete: ";
                cin>>key;
                dict.delete_key(key);
                break;
            default:
                c = 'n';
        }
    }
    return 0;
}