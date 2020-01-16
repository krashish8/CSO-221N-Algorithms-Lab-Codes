#include <iostream>
#include <stack>
using namespace std;

struct node {
    int data;
    node *left, *right;
};

node *get_node(int val) {
    node *newnode = new node;
    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}

class BST {
    private:
        node *root;
        bool search(node*&, node*&, int, node*);
    public:
        bool find(int, node*);
        node* insert(int, node*);
        node* remove(int, node*);
        void preorder(node*);
        void inorder(node*);
        void postorder(node*);
        BST() {root = NULL;}
};

bool BST::find(int x, node *root) {
    while (root != NULL) {
        if (root->data == x) return true;
        else if (root->data > x) root = root->left;
        else root = root->right;
    }
    return false;
}

bool BST::search(node* &n, node* &parent, int x, node* root) {
    parent = NULL;
    while (root != NULL) {
        if (root->data == x) {
            n = root;
            return true;
        }
        else if (root->data > x) {
            parent = root;
            root = root->left;
        }
        else {
            parent = root;
            root = root->right;
        }
    }
    return false;
}

node *BST::insert(int x, node *root) {
    node *parent = root;
    if (root == NULL) return get_node(x);
    while (root != NULL) {
        parent = root;
        if (root->data > x) root = root->left;
        else root = root->right;
    }
    if (parent->data > x) parent->left = get_node(x);
    else parent->right = get_node(x);
    return root;
}

node *BST::remove(int x, node* root) {
    node *n, *parent;
    bool found = search(n, parent, x, root);
    if (!found) return root;
    // No Child
    if (n->left == NULL && n->right == NULL) {
        if (parent != NULL) {
            if (parent->left == n) parent->left = NULL;
            else parent->right = NULL;
        }
        else root = NULL;
        free(n);
    }
    // Only right child
    else if (n->left == NULL && n->right != NULL) {
        if (parent != NULL) {
            if (parent->left == n) parent->left = n->right;
            else parent->right = n->right;
        }
        else root = n->right;
        free(n);
    }
    // Only left child
    else if (n->left != NULL && n->right == NULL) {
        if (parent != NULL) {
            if (parent->left == n) parent->left = n->left;
            else parent->right = n->left;
        }
        else root = n->left;
        free(n);
    }
    // Two children
    else if (n->left != NULL && n->right != NULL) {
        node *par = n;
        node *in_succ = n->right;
        while (in_succ->left != NULL) {
            par = in_succ;
            in_succ = in_succ->left;
        }
        in_succ->left = n->left;
        in_succ->right = n->right;
        if (par->left == in_succ) par->left = NULL;
        else par->right = NULL;
        if (parent != NULL) {
            if (parent->left == n) parent->left = in_succ;
            else parent->right = in_succ;
        }
        else {
            root = in_succ;
        }
        free(n);
    }
    return root;
}

void BST::preorder(node *root) {
    stack<node*> st;
    st.push(NULL);
    node* ptr = root;
    while (ptr != NULL) {
        cout << ptr->data << " ";
        if (ptr->right != NULL) st.push(ptr->right);
        if (ptr->left != NULL) {
            ptr = ptr->left;
        }
        else {
            ptr = st.top();
            st.pop();
        }
    }
}

void BST::inorder(node *root) {
    stack<node*> st;
    st.push(NULL);
    node* ptr = root;
    while (ptr != NULL || st.top() != NULL) {
        while (ptr != NULL) {
            st.push(ptr);
            ptr = ptr->left;
        }
        ptr = st.top();
        st.pop();
        cout << ptr->data << " ";
        ptr = ptr->right;
    }
}

void BST::postorder(node *root) {
    stack<node*> st;
    node *ptr = root, *last_pop = root;
    st.push(ptr);
    while (!st.empty()) {
        ptr = st.top();
        if (ptr->left != NULL && ptr->left != last_pop && ptr->right != last_pop) {
            st.push(ptr->left);
        }
        else if (ptr->right != NULL && ptr->right != last_pop) {
            st.push(ptr->right);
        }
        else {
            st.pop();
            cout << ptr->data << " ";
            last_pop = ptr;
        }
    }
}

int main() {
    BST bst;
    node *root = NULL;
    root = bst.insert(35, root);
    bst.insert(20, root);
    bst.insert(50, root);
    bst.insert(30, root);
    bst.insert(10, root);
    cout << "Preorder : "; bst.preorder(root); cout << endl;
    cout << "Inorder : "; bst.inorder(root); cout << endl;
    cout << "Postorder : "; bst.postorder(root); cout << endl;
}