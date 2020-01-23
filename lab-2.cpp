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
        root->data = in_succ->data;
        if (par->left == in_succ) par->left = in_succ->right;
        else par->right = in_succ->right;
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
    cout << "1. Create a BST" << endl;
    cout << "2. Insert an element" << endl;
    cout << "3. Search an element" << endl;
    cout << "4. Delete an element" << endl;
    cout << "5. Preorder traversal" << endl;
    cout << "6. Inorder traversal" << endl;
    cout << "7. Postorder traversal" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice : ";
    int op, n, a;
    cin >> op;
    while (op != 8) {
        switch(op) {
            case 1:
                cout << "Enter the number of elements to insert : ";
                cin >> n;
                cout << "Enter the elements : " << endl;
                cin >> a;
                root = bst.insert(a, root);
                for (int i = 0; i < n - 1; i++)
                {
                    int a;
                    cin >> a;
                    bst.insert(a, root);
                }
                cout << "Elements inserted successfully" << endl;
                break;
            case 2:
                cout << "Enter the element to insert : ";
                cin >> a;
                if (root == NULL) root = bst.insert(a, root);
                else bst.insert(a, root);
                cout << a << " inserted successfully." << endl;
                break;
            case 3:
                cout << "Enter the element to search : ";
                cin >> a;
                if (bst.find(a, root)) cout << a << " found" << endl;
                else cout << a << " not found" << endl;
                break;
            case 4:
                cout << "Enter the element to delete : ";
                cin >> a;
                root = bst.remove(a, root);
                cout << a << " deleted" << endl;
                break;
            case 5:
                cout << "Preorder traversal : ";
                bst.preorder(root); cout << endl;
                break;
            case 6:
                cout << "Inorder traversal : ";
                bst.inorder(root); cout << endl;
                break;
            case 7:
                cout << "Postorder traversal : ";
                bst.postorder(root); cout << endl;
                break;
            default:
                break;
        }
        cout << "\nEnter your choice : ";
        cin >> op;
    }
}