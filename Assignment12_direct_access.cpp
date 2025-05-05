#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student
{
    public:
        int rollno;
        char name[20];  //use char array instead of string
};

class DirectAccess
{
    public:
        int getPos(int roll)
        {
            return (roll-1)*sizeof(Student);
        }
        
        void insertRecord()
        {
            Student student;
            cout<<"\nEnter Roll no.:";
            cin>>student.rollno;
            cout<<"\nEnter Name: ";
            cin>>student.name;
            fstream file;
            file.open("test",ios::in|ios::out|ios::binary);
            cout<<"\nOpened";

            if(!file)
            {
                cout<<"\nFailed to create or open file";
                return;
            }

            file.seekp(getPos(student.rollno));
            file.write((char*)&student,sizeof(Student));
            cout<<"\nWritten";

            file.close();
            cout<<"\nRecord inserted successfully !";
        }

        void deleteRecord()
        {
            fstream file("test",ios::in|ios::out|ios::binary);
            if(!file)
            {
                cout<<"\nFile not found !";
                return;
            }

            int rollno;
            cout<<"\nEnter Roll no. to delete:";
            cin>>rollno;

            Student stud;
            file.seekg(getPos(rollno));
            file.read((char*)&stud,sizeof(Student));

            if(stud.rollno!=rollno || stud.rollno==-1)
            {
                cout<<"\nRecord not found";
            }
            else{ stud.rollno=-1;
                file.seekp(getPos(rollno));
                file.write((char*)&stud,sizeof(Student));

                cout<<"\nRecord deleted";
            }

            file.close();
        }

        void displayRecord()
        {
            fstream file;
            file.open("test",ios::in|ios::binary);

            if(!file)
            {
                // file.open("StudentDirect",ios::in | ios::binary);
                cout<<"\nError opening the file";
                return;
            }

            int rno;
            cout<<"\nEnter the roll no to read:";
            cin>>rno;
            
            Student student;
            file.seekg(getPos(rno),ios::beg);
            file.read((char*)&student,sizeof(Student));

            if(student.rollno!=rno)
            {
                cout<<"\nRoll no. not found !";
            }
            else{
                cout << "Roll: " << student.rollno << "\nName: " << student.name << endl;
            }
        }
};
int main()
{
    Student st;
    cout<<sizeof(st);
    cout<<endl<<sizeof(st.rollno);
    cout<<endl<<sizeof(st.name);
    // cout<<endl<<sizeof(st.deleted);

    DirectAccess DFile;

    cout<<"\n\n\t\t\tDirect Access FIle";

    int choice;
    do
    {
        cout<<"\n1. Insert Record\n2. Delete Record\n3. Display Record\n4. Exit\nEnter your choice:";
        cin>>choice;

        switch (choice)
        {
        case 1:
            DFile.insertRecord();
            break;

        case 2:
            DFile.deleteRecord();
            break;

        case 3:
            DFile.displayRecord();
            break;
        
        default:
            break;
        }
    } while (choice!=4);
    

return 0;
}