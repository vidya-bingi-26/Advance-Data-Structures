#include<iostream>
#include<stack>
using namespace std;
//AVL Tree
class node{
    public:
    int data,height;
    node* left;
    node* right;
    node(int value){
        data=value;
        left=right=nullptr;
        height=1;
    }
};
//to get height of subtrees for calculating balance factor
int getHeight(node* n){
if(n==nullptr){
    return 0;
}
return n->height;
}
//function to get balance factor
int getBalance(node* n){
    return  getHeight(n->left)-getHeight(n->right);
}
//func for right rotation
node* rightRotate(node* root) {
    node* child=root->left;
    
    node* t3=child->right;
    
    child->right=root;
    root->left=t3;

    //update height 
    root->height=1+max(getHeight(root->left),getHeight(root->right));
    child->height=1+max(getHeight(child->left),getHeight(child->right));
    return child;
}
//func for left rotation
node* leftRotate(node* root){
    node* child=root->right;
    
    node* t3=child->left;
    
    child->left=root;
    root->right=t3;

    //update height
    root->height=1+max(getHeight(root->left),getHeight(root->right));
    child->height=1+max(getHeight(child->left),getHeight(child->right));
    return child;
}
//func to insert node
node* insert(node* root,int value){
        if(!root){
            //create new node as a root if tree is empty
            return  new node(value);
        }

        //if value is smaller than root
        if(value<root->data){
            root->left=insert(root->left,value);
        }
        //if value is greater
        else if(value>root->data){
            root->right=insert(root->right,value);
        }
        //if is same as root(same values are not allowed in avl tree)
        else{
            return root;
        }
        //update height after inserting
        root->height=max(getHeight(root->left),getHeight(root->right))+1;

        //calculate balance factor
        int  balanceFact = getBalance(root);
        //left left case
        if(balanceFact>1 && root->left->data>value){
            return rightRotate(root);
        }
        //right right case
        else if(balanceFact<-1 && value>root->right->data){
            return leftRotate(root);
        }
        //left right case
        else if(balanceFact>1 && value>root->left->data){
            root->left=leftRotate(root->left);
            return rightRotate(root);
        }
        //right left case
        else if(balanceFact<-1 && root->right->data>value){
            root->right=rightRotate(root->right);
            return leftRotate(root);
        }
        //no unbalancing
        
            return root;
        

    }

    //recursive Inorder Traversal
    void inorder(node* root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    //recursive  Preorder Traversal
    void preorder(node *root) {
        if(root==nullptr){
            return;
        }
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }

    //recursive postorder Traversal
    void postorder(node *root) {
        if(root==nullptr){
            return ;
        }
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<" ";
    }

    //Non-Recursive Preorder Traversal
    void nonRecPreorder(node* root){
        stack<node*> s;
            s.push(root);
        while(!s.empty()){
            node *curr=s.top();
            s.pop();
            cout<<curr->data<<" ";
            if(curr->right!=nullptr){
                s.push(curr->right);
            }
            if(curr->left!=nullptr){
                s.push(curr->left);
            }
        }
    }
//non recursive inorder traversal
void nonRecInorder(node* root) {
    if (root == nullptr) return;
    
    stack<node*> st;
    while (!st.empty() || root != nullptr) {
        while (root != nullptr) {
            st.push(root);
            root = root->left;
        }
        node* temp = st.top();
        st.pop();
        cout << temp->data << " ";
        root = temp->right;
    }
}

    //non recursive postorder traversal
    void nonRecPostorder(node* root){
    if (root == nullptr)
        return;

    stack<node*> stk;
    node* current = root;
    node* lastVisited = nullptr;

    while (current || !stk.empty()) {
        // Traverse left subtree and push nodes to stack
        while (current) {
            stk.push(current);
            current = current->left;
        }

        current = stk.top();
        
        // If right child exists and traversing right child is not done
        if (current->right && current->right != lastVisited) {
            current = current->right;
        } else {
            // Print data of the current node
            cout << current->data << " ";
            stk.pop();
            lastVisited = current;
            current = nullptr; // Reset current pointer
        }
    }
    }
int main(){
    node *root=nullptr;
    int value;
    char ch;
    do{
        cout<<"enter value to insert:";
        cin>>value;
        root=insert(root,value);
        cout<<"do you want to continue?[y/n] :   ";
        cin>>ch;

    }while(ch!='n');
    int choice;
    char c;
    do{
    cout<<"select a operation :"<<endl;
    cout<<"1.Recursive Inorder Traversal"<<endl;
    cout<<"2.Recursive Preorder Traversal"<<endl;
    cout<<"3.Recursive Postorder Traversal"<<endl;
    cout<<"4.Non-Recursive Inorder Traversal"<<endl;
    cout<<"5.Non-Recursive Preorder Traversal"<<endl;
    cout<<"6.Non-Recursive Postorder Traversal"<<endl;
    cin>>choice;
    
    switch (choice)
    {
    case 1:
    cout<<"inorder traversal is:";
    inorder(root);
        break;
    case 2:
    cout<<"Preorder traversal is:";
    preorder(root);
    break;
    case 3:
    cout<<"Postorder traversal is:";
    postorder(root);
    break;
    case 4:
    cout<<"Inorder traversal is:";
    nonRecInorder(root);
    break;
    case 5:
    cout<<"Preorder traversal is:";
    nonRecPreorder(root);
    break;
    case 6:
    cout<<"Postorder traversal is:";
    nonRecPostorder(root);
    break;
    default:
    cout<<"Invalid Choice"<<endl;
        break;
    }
cout<<"\nwant to continue? :  ";
cin>>c;
    }while(c!='n');
    
    
    return 0;

}
/*
output:
PS C:\Users\Dell\OneDrive\Desktop\sem-2-SY\ads> cd "c:\Users\Dell\OneDrive\Desktop\sem-2-SY\ads\" ; if ($?) { g++ practical3.cpp -o practical3 } ; if ($?) { .\practical3 }
enter value to insert:10
do you want to continue?[y/n] :   y
enter value to insert:20
do you want to continue?[y/n] :   y
enter value to insert:5
do you want to continue?[y/n] :   y
enter value to insert:50
do you want to continue?[y/n] :   y
enter value to insert:30
do you want to continue?[y/n] :   y
enter value to insert:95
do you want to continue?[y/n] :   y
enter value to insert:70
do you want to continue?[y/n] :   y
enter value to insert:100
do you want to continue?[y/n] :   n
select a operation :
1.Recursive Inorder Traversal
2.Recursive Preorder Traversal
3.Recursive Postorder Traversal
4.Non-Recursive Inorder Traversal
5.Non-Recursive Preorder Traversal
6.Non-Recursive Postorder Traversal
1
inorder traversal is:5 10 20 30 50 70 95 100 
want to continue? :  y
select a operation :
1.Recursive Inorder Traversal
2.Recursive Preorder Traversal
3.Recursive Postorder Traversal
4.Non-Recursive Inorder Traversal
5.Non-Recursive Preorder Traversal
6.Non-Recursive Postorder Traversal
2
Preorder traversal is:30 10 5 20 70 50 95 100 
want to continue? :  y
select a operation :
1.Recursive Inorder Traversal
2.Recursive Preorder Traversal
3.Recursive Postorder Traversal
4.Non-Recursive Inorder Traversal
5.Non-Recursive Preorder Traversal
6.Non-Recursive Postorder Traversal
3
Postorder traversal is:5 20 10 50 100 95 70 30 
want to continue? :  y
select a operation :
1.Recursive Inorder Traversal
2.Recursive Preorder Traversal
3.Recursive Postorder Traversal
4.Non-Recursive Inorder Traversal
5.Non-Recursive Preorder Traversal
6.Non-Recursive Postorder Traversal
4
Inorder traversal is:5 10 20 30 50 70 95 100
want to continue? :   y
select a operation :
1.Recursive Inorder Traversal
2.Recursive Preorder Traversal
3.Recursive Postorder Traversal
4.Non-Recursive Inorder Traversal
5.Non-Recursive Preorder Traversal
6.Non-Recursive Postorder Traversal
5
Preorder traversal is:20 10 5 50 30 95 70 100 
want to continue? :  y
select a operation :
1.Recursive Inorder Traversal
2.Recursive Preorder Traversal
3.Recursive Postorder Traversal
4.Non-Recursive Inorder Traversal
5.Non-Recursive Preorder Traversal
6.Non-Recursive Postorder Traversal
6
Postorder traversal is:5 10 30 70 100 95 50 20 
want to continue? :  n
*/