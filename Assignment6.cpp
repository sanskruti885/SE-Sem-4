#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Node{
    int data;
    Node *next;
public:
    Node(int d){
        data =d ;
        next = NULL;
    }
    Node (){
        data = -1;
        next = NULL;
    }
    friend class Graph;
};
class Graph{
    Node *G[20];
    int visited[20];
    int ver,src,des;
    Node *temp;
public:
// creating array of node and initialising it
    Graph(int v){
        ver = v;
        for(int i=0;i<v;i++){
            G[i] = new Node(i);
            visited[i] = 0;
        }
    }
    void insertNode(int edge){
        for(int i=0;i<edge;i++){
            cout<<"\nEnter source: ";
            cin>>src;
            cout<<"\nEnter destination: ";
            cin>>des;
            temp = G[src];
            while(temp->next!=NULL){   // attach source and destination
                temp = temp->next;
            }
            temp->next = new Node(des);  //store destination

            temp = G[des];
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = new Node(src);
            cout<<"\nNode inserted.";
        }
       

    }
    void BFS(int start){
        visited[start] = 1;
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            int v = q.front();
            cout<<v<<" ";
            q.pop();
            temp = G[v]->next;
            while(temp!=NULL){
                if(!visited[temp->data]){
                    q.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }

        }
    }
    void resetVisited(){
        for(int i=0;i<ver;i++){
            visited[i] = 0;
        }
    }
    void DFS(int start){
        stack<int> s;
        visited[start] = 1;
        s.push(start);
        
        while(!s.empty()){
            int v = s.top();
            cout<<v<<" ";
            s.pop();
            temp = G[v]->next;
            while(temp!=NULL){
                if(!visited[temp->data]){
                    s.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
    }
};
int main(){
    int ver, edges, start;
    cout << "Enter the number of vertices: ";
    cin >> ver;
    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph g(ver);
    g.insertNode(edges);

    cout << "\nEnter Starting Node for BFS: ";
    cin >> start;
    cout << "BFS Traversal: ";
    g.BFS(start);

    g.resetVisited();

    cout<<"\nEnter starting node for DFS: ";
    cin>>start;
    cout<<"DFS Traversal: ";
    g.DFS(start);

    return 0;
}

