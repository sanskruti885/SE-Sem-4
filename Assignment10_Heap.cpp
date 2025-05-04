#include<iostream>
using namespace std;
#define MAX 20

class Heap{
    int arr[MAX];
    int n;
public:
    void getInput();
    void show();
    void max_heapify(int,int);
    void buildMaxHeap();
    void heapSort();
    void min_max();
};
void Heap :: getInput(){
    cout<<"\nEnter number of students: ";
    cin>>n;
    cout<<"\nEnter marks";
    for(int i=0;i<n;i++){
        cout<<"\nStudent "<<i+1<<": ";
        cin>>arr[i];
    }
}
void Heap :: show(){
    for(int j=0;j<n;j++){
        cout<<arr[j]<<"  ";
    }
}
void Heap :: max_heapify(int index,int size){
    int parent = index;
    int left = 2*index+1;      //LEFT child 
    int right = 2*index+2;     //RIGHT child

    if(left < size && arr[left]>arr[parent]){
        parent = left;
    }
    if(right < size && arr[right]>arr[parent]){
        parent = right;
    }
    // means parent has been updated
    if(parent!=index){
        swap(arr[index],arr[parent]);
        max_heapify(parent,size);
    }
}
void Heap :: buildMaxHeap(){
    for(int i=n/2-1;i>=0;i--){  //n/2-1 gives first internal node from bottom
        max_heapify(i,n);
    }
}
void Heap :: heapSort(){
    buildMaxHeap();
    for(int i=n-1;i>0;i--){     // by default swapping with 0, when 0 means last element
        swap(arr[0],arr[i]);    //swap 0 with last element
        max_heapify(0,i);
    }
    cout<<"\nElements sorted";
}
void Heap :: min_max(){
    cout<<"\nMin element: "<<arr[0];
    cout<<"\nMax element: "<<arr[n-1];
}
int main(){
    Heap h;
   char ch = 'y';
   int n;
   while(ch == 'y'){
    cout<<"\n1.Insert\n2.Sort\n3.Display\n4.Min Max element\n5.Exit";
    cout<<"\nEnter your choice: ";
    cin>>n;
    switch(n){
        case 1:
            h.getInput();
            break;
        case 2:
            h.heapSort();
            break;
        case 3:
            h.show();
            break;
        case 4:
            h.min_max();
            break;
        case 5:
            ch = 'n';
            break;
        default:
            cout<<"\nWrong Choice";
    }
   }

    return 0;
}