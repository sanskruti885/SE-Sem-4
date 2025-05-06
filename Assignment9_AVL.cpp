#include<iostream>
using namespace std;

class Node{
    int key,height;
    Node *left,*right;
    friend class AVL;
public:
    Node(int k){
        key = k;
        left = NULL;
        right = NULL;
        height = 1;
    }
};
class AVL{
    Node *root;
public:
    AVL(){
        root = nullptr;
    }
// required to calculate balanace factor
    int getHeight(Node *n){
        if(n ==  NULL)
            return 0;
        return n->height;
    }

    Node *createNode(int k){
        Node *newNode = new Node(k);
        return newNode;
    }

    // balanace factor = height of left tree - height of right tree
    int getBalanceFactor(Node *n){
        if(n == NULL) return 0;
        return getHeight(n->left)-getHeight(n->right);
    }

// remember tree structure root y, y->left = x, x->left = t1, x->right = t2
    Node *rightRotate(Node *y){
        Node *x =y->left;
        Node *t2 = x->right;

        // rotate
        x->right = y;
        y->left = t2;

        //height changed of x,y
        x->height = max(getHeight(x->left),getHeight(x->right)) + 1; // its own height also
        y->height = max(getHeight(y->left),getHeight(y->right)) + 1;

        return x; //new root
    }

    Node *leftRotate(Node *x){
        Node *y = x->right;
        Node *t2 = y->left;

        // rotate
        y->left = x;
        x->right = t2;

        x->height = max(getHeight(x->left),getHeight(x->right))+1;
        y->height = max(getHeight(y->left),getHeight(y->right))+1;

        return y; // new root
    }

// bst logic
    Node *insert(Node *node,int k){
        if(node == NULL){
           return createNode(k);
        }
        else if(k<node->key){
            node->left = insert(node->left,k);
        }
        else{
            node->right = insert(node->right,k);
        }
        // return node; //recursion called at end

        node->height = max(getHeight(node->left),getHeight(node->right)) + 1;
        int bf = getBalanceFactor(node);

        // left left case
        if(bf>1 && k<node->left->key){
           return rightRotate(node);
        }
        // case right right
        if(bf<-1 && k>node->right->key){
           return leftRotate(node);
        }
        // case left right
        if(bf>1 && k>node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // case right left
        if(bf<-1 && k<node->right->key){
            node->right = rightRotate(node->right);
           return  leftRotate(node);
        }
        return node;
    }
    void helper_insert(int k){
       root =  insert(root,k);
    }

    void preorder(Node*n){
        if(n!=NULL){
            cout<<n->key<< " ";
            preorder(n->left);
            preorder(n->right);
        }
    }

    void helper_preorder(){
        preorder(root);
    }
    void search(int k){
        Node *temp = root;
        int comp = 0;
        while(temp!=NULL){
            if(temp->key == k){
                comp++;
                cout<<"\nFound\nComparison:  "<<comp;
                return;
            }
            else if(k<temp->key){
                comp++;
                temp = temp->left;
            }
            else{
                comp++;
                temp = temp->right;
            }
        }
        cout<<"\nElement not found";
    }

};
int main(){
    AVL a;
    int choice,k;
    char ch = 'y';
    while(ch == 'y'){
        cout<<"\n1. Insert\n2. Display\n3. Search\n4. Exit";
        cout<<"\nEnter choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"\nEnter key: ";
                cin>>k;
                a.helper_insert(k);
                break;
            case 2:
                a.helper_preorder();
                break;
            case 3:
                cout<<"\nEnter key to search: ";
                cin>>k;
                a.search(k);
            default :
                ch = 'n';
        }
    }
    return 0;
}