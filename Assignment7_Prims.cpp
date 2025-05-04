//============================================================================
// Name        : Prims_kruskal.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<limits.h>
using namespace std;
#define max_size 30

class MST{
	int ver;
	int adj[max_size][max_size];
	int v_array[max_size];
	int mst[max_size][max_size];
public:
	MST(int v){
		ver = v;
		for(int i=0;i<v;i++){
			for(int j=0;j<v;j++){
				adj[i][j] = 0; // store 0 while checking min put condition if(G[i][j]) means go in if non zero value
				mst[i][j] = 0;
			}
			v_array[i] = 0;    //visted value 0
		}
	}
	void create();
	void display();
	void prism();
};
void MST :: create(){
	int src,des,edges,cost;
	cout<<"\nEnter Edges: ";
	cin>>edges;
		for(int i=0;i<edges;i++){
		cout<<"\nEnter source: ";
		cin>>src;
		cout<<"\nEnter destination: ";
		cin>>des;
		cout<<"\nEnter cost: ";
		cin>>cost;
		adj[src][des] = cost;
		cout<<adj[src][des]<<endl;    //undirectional therefore value of [0][1] also come [1][0]
		adj[des][src] = cost;
	}
	
}
void MST :: display(){
	cout<<"Row"<<"  "<<"column"<<"  "<<"Cost\n";
	int total =0;
	for(int i=0;i<ver;i++){
		for(int j=i+1;j<ver;j++){
			if(mst[i][j]){
			cout<<i<<"-"<<j<<":"<<mst[i][j]<<" ";
			total+= mst[i][j];
			}
		}
		cout<<endl;
	}
	cout<<"Total: "<<total;
}
void MST :: prism(){
	
	v_array[0] = 1; // at start assign it visisted to begin visted
	int edges = 0;
	// by defination edges=ver-1
	while(edges<ver-1){
		int min = INT_MAX;
		int r = -1, c = -1;
	 
		for(int i=0;i<ver;i++){
		// only if visited column is pushed then search in that row
		// if arr[0][4] = min v_array[4] = 1 then check further 
		  if(v_array[i]){
			for(int j=0;j<ver;j++){
					// we puch column therefore check j
					// adj[i][j] if not zero
					if(min > adj[i][j] && !v_array[j] && adj[i][j]){
						min = adj[i][j];
						r = i;
						c = j;	
					}
				}
			}	
		 }
		 // after for of i this is executed 
		if(r!=-1 && c!=-1){
			v_array[c] = 1;         // pushing column to visited set 1
			mst[r][c] = adj[r][c];  //push min cost in array
			mst[c][r] = adj[c][r];  // undirected
			edges++;
		}
		
	}
	
}
int main() {
	int ver;
	cout<<"\nEnter Vertices\n";
	cin>>ver;
	MST m(ver);
	m.create();
	// m.display();
	m.prism();
	m.display();
	return 0;
}
