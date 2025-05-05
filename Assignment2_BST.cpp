#include <iostream>
#include <string>
#include<cstring>
#include <vector>
using namespace std;

class Node{
	string key,value;
	Node *left,*right;
public:
	Node(): key(""), value(""),left(nullptr),right(nullptr){}
	Node(string k,string v): key(k), value(v),left(nullptr),right(nullptr){}
	friend class BST;
};
class Stack{
	int top;
	vector<Node*> data;
public:
	Stack():top(-1){}
	void push(Node* n);
	bool isEmpty();
	Node* pop();

};
bool Stack::isEmpty(){
	return top == -1;
}
void Stack::push(Node *node){
	data.push_back(node);
	top++;
}
Node* Stack::pop(){
	if(isEmpty()){
		cout<<"Stack Empty";
		return nullptr;
	}
	Node *topEle = data[top];
	data.pop_back();
	top--;
	return topEle;
}
class BST{
	Node *root;
public:
	BST():root(nullptr){}

	void create(string k, string v);
	Node* insert(Node *temp, string k, string v);
	void userinput();
	void helper_inorder();
	void inorder(Node *root); //ascending
	void descending(); //descending
	int search();
	void update();
	void delete_node();
	pair<Node*, Node*> search(string key);
	pair<Node*,Node*> leftmost(Node* n);
};

void BST :: create(string k, string v){
	if(root == nullptr){
				Node *newNode = new Node(k,v);
				root = newNode;
			}
			else{
				root = insert(root,k,v);
			}
}
Node*  BST :: insert(Node *temp, string k, string v){
	Node *p;
	if(temp == nullptr){
		p = new Node(k,v);
		return p;
	}
	else{
		if(k <= temp->key){
			temp->left = insert(temp->left,k,v);
		}
		else{
			temp->right = insert(temp->right,k,v);
		}
	}
	return temp;
}
void BST :: userinput(){
	string u_key,u_value;
	cout<<"\nEnter key: ";
	cin>>u_key;
	cout<<"\nEnter value: ";
	cin>>u_value;
	create(u_key,u_value);
}

void BST:: inorder(Node * root){
	if(root!=NULL){
		inorder(root->left);
		cout<<root->key<<":"<<root->value<<"\n";
		inorder(root->right);
	}
}
void BST:: helper_inorder(){
	cout<<"\nAscending order: ";
	inorder(root);
}
void BST :: descending(){
	Node *cur = root;
	Stack st;
	while(cur!=nullptr || !st.isEmpty()){
		while(cur!=nullptr){
			st.push(cur);
			cur = cur->right;
		}
		cur = st.pop();
		cout<<cur->key<<": "<<cur->value<<"\n";
		cur = cur->left;
	}
}
int BST :: search(){
	string key;
	int f=0;
	cout<<"\nEnter key to search: ";
	cin>>key;
	int comp=0;
	Node *temp = root;
	while(temp!=nullptr){
		if(key == temp->key){
			comp++;
			f=1;
			return comp;
		}
		else if(key<=temp->key){
			temp =temp->left;
			comp++;
		}
		else{
			temp = temp->right;
			comp++;
		}
	}
	if(f==0)
		cout<<"\nElement not found";
	return comp;
}
void BST :: update(){
	string key,new_value;
	cout<<"\nEnter the key to update: ";
	cin>>key;
	cout<<"\nEnter new value: ";
	cin>>new_value;
	Node * temp = root;
	while(temp!=nullptr){
		if(key == temp->key){
			temp->value = new_value;
			cout<<"\nRecord updated";
			return;
		}
		else if(key <= temp->key){
			temp = temp->left;
		}
		else{
			temp = temp->right;
		}
	}

}
// returnig parent and child after finding them
pair<Node*,Node*> BST :: search(string key){
	Node *temp = root;
	Node *parent,*child;
	string *str[2];
	parent = root;
	while(temp!=nullptr){
		if(key == temp->key){
			child = temp;
			return{parent,temp};
		}
		else if(key<temp->key){
			parent = temp;
			temp = temp->left;
		}
		else{
			parent = temp;
			temp = temp->right;
		}
	}
	return {nullptr,nullptr};
}
pair<Node*, Node*> BST :: leftmost(Node *temp){
	Node *parent;
	while(temp!=nullptr){
		parent = temp;
		temp = temp->left;
	}
	return {parent,temp};
}
void BST :: delete_node(){
	string key;
	cout<<"\nEnter key to delete: ";
	cin>>key;
	pair<Node*,Node*> res = search(key);
	Node *parent = res.first;
	Node *child = res.second;
	cout<<parent->key<<": "<<child->key;
	
	// leaf node 
	if(child->left == nullptr && child->right == nullptr){
		if(child!=root){
			if(parent->left == child){
				parent->left = nullptr;
			}
			else{
				parent->right = nullptr;
			}
		}
		else{
			root = nullptr;
		}
		delete child;
	} 
	// if both chid present find sucessor
	else if(child->left && child->right){
		pair<Node*,Node*> res = leftmost(child->right);
		Node *succ_par = res.first;
		Node *succ = res.second;
		string key = succ->key;
		string value = succ->value;
		child->key = key;
		child->value = value;
		if(succ_par->left == succ){
			succ_par->left = nullptr;
		}
		else{
			succ_par->right = nullptr;
		}
		delete(succ);
	}
	// if one of the child is present then connect parent and child ka child
	else{
		Node *c_child = child->left ?child->left:child->right;

		if(child!=root){
			if(child == parent->left){
				parent->left = c_child;
			}
			else{
				parent->right = c_child;
			}
		}
		else{
			root = c_child;
			delete child;
		}
	}
}

void BST :: delete_node(){
	int data;
	cout<<"Enter node to delete: ";
	cin>>data;
	pair<Node*,Node*> res = search(data);
	Node * par = res.first;
	Node *child = res.second;

	if(child->left == NULL && child->right = NULL){
		if(child!=root){
			if(par->left == child) par->left = NULL;
			else if(par->right == child) par->right = NULL;
			delete child;
		}
		else root = NULL;
	}
	else if(child->left && child->right){
		pair<Node*,Node*> suc = leftmost(child->right);
		Node * suc_par = suc.first;
		Node *suc_child = suc.second;
		child->key = suc->key;
		child->value = suc->value;

		if(suc_par->left == suc) suc_par->left = NULL;
		else if(suc_par->right == suc) suc_par->right = NULL;
		delete suc;
	}
	else{
		Node *c_child = child->left?child->left : child->right;
		if(child!=root){
			if(par->left == child){
			par->left = c_child;
			delete child;
		}
		else if(par->right == child){
			par->right = c_child;
			delete child;
		}
		}
		else{
			root = c_child;
			delete child;
		}
		
	}
}

int main() {
	BST t1;
	char ch = 'y';
	int n;
	while(ch == 'y'){
		cout<<"\n1. Create";
		cout<<"\n2. Ascending order";
		cout<<"\n3. Descending order";
		cout<<"\n4. Search with No. of comparison";
		cout<<"\n5. Update record";
		cout<<"\n6. Delete";
		cout<<"\n7. Exit";
		cout<<"\nEnter choice: ";
		cin>>n;
		switch(n){
			case 1: t1.userinput();
					break;
			case 2: t1.helper_inorder();
					break;
			case 3: t1.descending();
					break;
			case 4: cout<<t1.search();
					break;
			case 5: t1.update();
					break;
			case 6: t1.delete_node();
					break;
			case 7: ch ='n';
					break;
			default: cout<<"wrong choice";
		}
	}
	return 0;
}
