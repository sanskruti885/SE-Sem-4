#include<iostream>
using namespace std;

#define table_size 10
class Client{
    long phone;
    bool present;

public:
    Client(){
        phone = -1;
        present = false; 
    }

    long getphone(){ 
        return phone; 
    }

    void setphone(long p){
        phone = p;
        present = true;
    }

    bool isPresent(){
        return present;
    }
    friend class Telephone;
};

class Telephone{
    Client table[table_size];
    int hash_function(long phone){
        return phone % table_size;
    }

public:
    // without replacement
    void without_replacement(long phone){
        int index = hash_function(phone);
        int original = index;

        // find empty bucket
        while(table[index].isPresent()){ //place occupied move to next
            index = (index+1) % table_size;
            // back to its position
            if(index == original){
                cout<<"\nTable is full!!!!!!!!!!!!!!";
            }
        }
        table[index].setphone(phone);
    }

    // with replacement
    void with_replacement(long phone){
       int index = hash_function(phone);
       int original = index;
       
       // check occupied position and replce if require
       if(table[index].isPresent()){
        // if existing value is not mapped according to key and using linear probe replace
        // doesnot match with current index swap
        if(hash_function(table[index].getphone()) != index){
            // get old number
            long old_value = table[index].getphone();

            // set new number
            table[index].setphone(phone);

            // find positing for old value
            if (old_value != phone) {
                with_replacement(old_value);
            }
            
            // with_replacement(old_value);
            return;
        }
       }

       // find next position
    //    while(table[index].isPresent()){
    //       index = (index+1) % table_size; 
    //    }
    //    table[index].setphone(phone);
    }

    // search 
    int search(long phone) {
    int index = hash_function(phone);
    int original = index;
    int comparisons = 1;

    // Search until an empty slot is found
    while (table[index].isPresent()) {  // 
        // Check if current slot contains the phone number
        if (table[index].getphone() == phone) {
            return comparisons;  // 
        }

        index = (index + 1) % table_size; 
        comparisons++;

        // If we return to the original index, it means we traversed the entire table
        if (index == original) {
            return -1;  // 
        }
    }
    return -1;  
}


    void display(){
        cout<<"\nPhone  numbers: \n";
        for (int i = 0; i < table_size; i++) {
            cout << i << "\t";
            if (table[i].isPresent()) cout << table[i].getphone();
            else cout << "--";
            cout << endl;
        }
    }
};

int main() {
    Telephone tb;
    int choice;
    long phone;
    bool useReplacement;
    
    cout << "Use replacement method? (1 for Yes, 0 for No): ";
    cin >> useReplacement;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a Phone Number\n";
        cout << "2. Search for a Phone Number\n";
        cout << "3. Display Hash Table\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter phone number to insert: ";
                cin >> phone;
                if (useReplacement)
                    tb.with_replacement(phone);
                else
                    tb.with_replacement(phone);
                break;
            case 2:
                cout << "Enter phone number to search: ";
                cin >> phone;
                {
                    int comparisons = tb.search(phone);
                    if (comparisons == -1)
                        cout << "Phone number not found!\n";
                    else
                        cout << "Phone number found with " << comparisons << " comparisons.\n";
                }
                break;
            case 3:
                tb.display();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}