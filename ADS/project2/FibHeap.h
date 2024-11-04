#pragma once

#include "head.h"

class FibNode
{
    public:
        GNode val;       
        int degree;      
        FibNode *left;    
        FibNode *right;   
        FibNode *child;   
        FibNode *parent;   
        bool marked;      

    FibNode(int vertex, int distance):degree(0), marked(false)
    {
        val.first = vertex;
        val.second = distance;
        left = this;
        right = this;
        child = nullptr;
        parent = nullptr;
    }
};

class FibHeap: public Heap
{
    private:
        int node_num;         // The total number of nodes in the heap
        FibNode *min_node;    // minimum

    public:
        FibHeap():node_num(0)
        {
            min_node = nullptr;
        };
        ~FibHeap(){};

        void initial(){}
        void push(int vertex, int distance)
        {
            insert_key(vertex, distance);
        }
        void pop()
        {
            remove_min_node();
        }
        pair<int, int> top()
        {
            return min_node->val;
        }
        bool empty()
        {
            return min_node == nullptr;
        }
        void print();    
        void destroy(); 
        void merge(FibHeap *newheap); // Merges the new heap into the current heap     

    private:
        void insert_key(int vertex, int distance);   // Create a new node with val and insert it into the Fibonacci heap
        void remove_min_node();                      // Remove the minimum node from the Fibonacci heap and return the minimum value
        void remove_node(FibNode *node);             // Remove a node from the doubly linked list
        void add_node(FibNode *node, FibNode *&root);// Add a node to the root node before the root node in the circular linked list
        void merge_list(FibNode *a, FibNode *b);     // Merge the doubly linked list b to the end of the doubly linked list a
        FibNode* retrieve_min_node();                // Remove the "minimum node of the heap" from the root list
        void link_subnode(FibNode *node, FibNode *root); // Link the node to the root node
        void consolidate();                          // Combine trees in the root list of the Fibonacci heap with the same degree
        void destroy_node(FibNode *node);            // Recursively delete nodes
        void print(FibNode *node, FibNode *prev); 
};

void FibHeap::remove_node(FibNode *node)
{
    node->right->left = node->left;
    node->left->right = node->right;
}

void FibHeap::add_node(FibNode *node, FibNode *&root)
{
    // If the root is null, make the new node the root
    if (root == nullptr)
    {
        root = node;
        root->left = root->right = root;
    }
    else
    {   // Insert the new node into the root list
        FibNode *r = root;
        node->left = r->left;
        node->right = r;
        r->left->right = node;
        r->left = node;
    }
}

void FibHeap::insert_key(int vertex, int distance)
{
    // Create a new node with the given vertex and distance
    FibNode *node = new FibNode(vertex, distance);
    // If the heap is empty, set the new node as the minimum node
    if (node_num == 0)
        min_node = node;
    else
    {   // Insert the new node into the root list
        add_node(node, min_node);
        // Update the minimum node if necessary
        if (node->val < min_node->val)
            min_node = node;
    }

    node_num++;
}

void FibHeap::merge_list(FibNode *a, FibNode *b)
{
    // Merge the doubly linked list b to the end of the doubly linked list a
    if (a == NULL)
        a = b;
    else
    {
        FibNode *t = a->left;
        a->left->right = b;
        b->left->right = a;
        a->left = b->left;
        b->left = t;
    }
}

void FibHeap::merge(FibHeap *newheap)
{
    // Merge the root lists of the two heaps
    if (newheap->min_node == NULL) return;
    merge_list(min_node, newheap->min_node);
    // Update the minimum node if necessary
    if (this->min_node->val > newheap->min_node->val)
        this->min_node = newheap->min_node;
    this->node_num += newheap->node_num;
}

FibNode* FibHeap::retrieve_min_node()
{
    FibNode *p = min_node;  // Save the current minimum node
    // If the minimum node is the only node in the heap, set min_node to NULL
    if (p == p->right)
        min_node = NULL;
    else
    {
        // Remove the minimum node from the root list and update min_node to the right sibling of the current minimum node
        remove_node(min_node);
        min_node = p->right;
    }
    p->left = p->right = p;  // Reset the left and right pointers of the current minimum node to itself
    return p;
}

void FibHeap::link_subnode(FibNode* node, FibNode* root)
{
    remove_node(node);  
    add_node(node, root->child); 
    node->parent = root;    // Update the parent pointer of the node to point to the root node
    (root->degree)++;       // Increase the degree
    node->marked = false;   // Reset the marked flag
}

void FibHeap::consolidate()
{
    // Initialize an array to hold the roots of trees in the heap
    vector<FibNode *> cons(log2(node_num) + 1, nullptr);
    FibNode *x, *y, *tmp; int t;
    while (min_node != nullptr)
    {
        // Remove the minimum node from the heap and store it in x
        x = retrieve_min_node();
        t = x->degree;
        // Merge nodes with the same degree until no nodes with the same degree exist
        while (cons[t] != nullptr)
        {
            y = cons[t];
            if (x->val > y->val) swap(x, y);  // X has the smaller value among the two nodes
            link_subnode(y, x);  // Link y as a child of x
            cons[t] = nullptr;
            t++;
        }
        cons[t] = x;
    }
    min_node = nullptr;  // Reset the min_node pointer
    // Reconstruct the root list from the consolidated nodes array
    for (int i = 0; i < cons.size(); i++)
    {
        if (cons[i] != nullptr)
        {
            add_node(cons[i], min_node);  // Add the node to the root list
            // Update the min_node pointer if necessary
            if (cons[i]->val < min_node->val) min_node = cons[i];
        }
    }
}

void FibHeap::remove_min_node()
{
    if (min_node == nullptr) return;
    FibNode *p = min_node, *kid = nullptr;  // Variables to track the current node and its child
    while (p->child != nullptr)  // Remove children of the minimum node and add them to the root list
    {
        kid = p->child;
        remove_node(kid);
        p->child = (kid->right == kid) ? nullptr : kid->right;  // Update the child pointer of the parent node
        add_node(kid, min_node);
        kid->parent = nullptr;
    }
    remove_node(p);
    // Update the min_node pointer based on the remaining nodes in the root list
    if (min_node->right == min_node)
        min_node = nullptr;
    else
    {
        min_node = p->right;
        consolidate();
    }
    node_num--;
    p = kid = nullptr;
}


void FibHeap::destroy()
{
    destroy_node(min_node);
}

void FibHeap::destroy_node(FibNode *node)
{
    if(node == nullptr) return;
    while(node != nullptr)
    {
        destroy_node(node->child);
        node = node->right;
        delete node;
    }
}

void FibHeap::print(FibNode *node, FibNode *prev)
{
    FibNode *start=node, *root=node;

    if (node==NULL)
        {return ;}
    do
    {
        if(start->right == node) cout << "(" << start->val.first << ", " << start->val.second << ") " << "(" << start->degree << ")" << endl;
        else cout << "(" << start->val.first << ", " << start->val.second << ") " << "(" << start->degree << ") -> ";
        start = start->right;
    } while(start != node);

    do
    {
        if(root->child != nullptr)
        {
            cout << "(" << root->val.first << ", " << root->val.second << ") " << "(" << start->degree << ")'s child:" << endl;
            print(root->child, node);
        }
        else cout << "(" << root->val.first << ", " << root->val.second << ") " << " has no child." << endl;
        root = root->right;
    } while(root != node);
}

void FibHeap::print()
{
    int root_num=0;
    FibNode *p;

    if (min_node == nullptr) return;

    cout << "== info ==" << endl;
    p = min_node;
    do {
        root_num++;
        cout << "第" << root_num << "棵树：" << endl;
        cout << setw(4) << "(" << p->val.first << ", " << p->val.second << ") " << "(" << p->degree << ") is root" << endl;

        print(p->child, p);
        p = p->right;
    } while (p != min_node);
    cout << endl;
}