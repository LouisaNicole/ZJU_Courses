#pragma once

#include "head.h"

class BinoNode
{
    public:
        int vertex;             // Vertex value
        int distance;           // Distance value
        int degree;             // Degree of the node
        BinoNode *parent;       // Pointer to the parent node
        BinoNode *leftChild;    // Pointer to the leftmost child node
        BinoNode *nextSibling;  // Pointer to the next sibling node

    BinoNode() : vertex(0), distance(0), degree(0), parent(nullptr), leftChild(nullptr), nextSibling(nullptr) {}
};

typedef struct Bheap
{
    BinoNode *head;
} *BinoHeap;

class BinomialHeap : public Heap
{
    private:
        BinoHeap h;             // Pointer to the binomial heap
        BinoNode newNode;       // New node for insertion

    public:
        BinomialHeap()
        {
            h = BulidHeap();      // Build a new heap
            newNode = BinoNode(); // Create a new node
        }
        void initial()
        {
            free(h);            // Free the heap
            h = BulidHeap();    // Build a new heap
        }
        void push(int vertex, int distance)
        {
            BinoNode *x = (BinoNode *)malloc(sizeof(BinoNode));
            x->vertex = vertex;
            x->distance = distance;
            x->degree = 0;
            x->parent = nullptr;
            x->leftChild = nullptr;
            x->nextSibling = nullptr;
            // Insert the new node into the heap
            InsertHeap(&h, x);
        }
        void pop()
        {
            ExtractMin(&h);
        }
        pair<int, int> top()
        {
            BinoNode *tmp = FindMin(h);
            return GNode(tmp->vertex, tmp->distance);
        }
        bool empty()
        {
            return h->head == NULL;
        }

    private:
        BinoHeap BulidHeap();                       // Build a new heap
        void LinkHeap(BinoNode *y, BinoNode *z);    // Link two heaps
        BinoNode *FindMin(BinoHeap h);              // Find the minimum node in the heap
        void InsertHeap(BinoHeap *h, BinoNode *x); // Insert a node into the heap
        BinoNode *ExtractMin(BinoHeap *h);          // Extract the minimum node from the heap
        BinoNode *MergeHeap(BinoHeap h1, BinoHeap h2);  // Merge two heaps
        BinoHeap UnionHeap(BinoHeap *h1, BinoHeap *h2); // Union of two heaps
};

BinoHeap BinomialHeap::BulidHeap()
{
    BinoHeap H = new Bheap();
    H->head = nullptr;
    return H;
}

BinoNode* BinomialHeap::FindMin(BinoHeap h)
{
    BinoNode *minNode = nullptr; // Node with the minimum distance value
    BinoNode *currentNode = h->head; // Start from the head of the heap
    if (currentNode)
    {
        int minDistance = currentNode->distance; // Initialize minDistance with the distance of the current node
        minNode = currentNode;
        currentNode = currentNode->nextSibling; // Move to the next sibling
        while (currentNode)
        {
            // If the distance of the current node is less than the minimum distance found so far, update minDistance and minNode
            if (currentNode->distance < minDistance)
            {
                minDistance = currentNode->distance;
                minNode = currentNode;
            }
            currentNode = currentNode->nextSibling; // Move to the next sibling
        }
    }
    return minNode; // Return the node with the minimum distance value
}

void BinomialHeap::LinkHeap(BinoNode *childNode, BinoNode *parentNode)
{
    childNode->parent = parentNode; // Set the parent
    childNode->nextSibling = parentNode->leftChild; // Set the next sibling as the current leftmost child
    parentNode->leftChild = childNode; // Set the new leftmost child
    parentNode->degree += 1; // Increase the degree
}


BinoNode* BinomialHeap::MergeHeap(BinoHeap heap1, BinoHeap heap2)
{
    BinoNode *firstNode = nullptr;
    BinoNode *currentNode = nullptr;
    BinoNode *node1 = heap1->head, *node2 = heap2->head;
    // If either heap is empty, return the other heap
    if (node1 == nullptr || node2 == nullptr)
    {
        if (node1 == nullptr) firstNode = node2;
        else firstNode = node1;
        return firstNode;
    }
    // Determine the first node of the merged heap
    if (node1->degree < node2->degree)
    {
        firstNode = node1;
        currentNode = node1;
        node1 = node1->nextSibling;
    }
    else
    {
        firstNode = node2;
        currentNode = node2;
        node2 = node2->nextSibling;
    }
    // Merge nodes from both heaps into a single sorted list
    while (node1 && node2)
    {
        if (node1->degree < node2->degree)
        {
            currentNode->nextSibling = node1;
            currentNode = node1;
            node1 = node1->nextSibling;
        }
        else
        {
            currentNode->nextSibling = node2;
            currentNode = node2;
            node2 = node2->nextSibling;
        }
    }
    // Append any remaining nodes from heap1 or heap2
    if (node1) currentNode->nextSibling = node1;
    else currentNode->nextSibling = node2;
    return firstNode;
}


BinoHeap BinomialHeap::UnionHeap(BinoHeap *heap1, BinoHeap *heap2)
{
    BinoHeap mergedHeap = BulidHeap();
    mergedHeap->head = MergeHeap(*heap1, *heap2);
    free(*heap1);
    *heap1 = nullptr;
    free(*heap2);
    *heap2 = nullptr;
    // If the merged heap is empty, return it
    if (mergedHeap->head == nullptr)
        return mergedHeap;

    BinoNode *previous = nullptr;
    BinoNode *currentNode = mergedHeap->head;
    BinoNode *nextNode = currentNode->nextSibling;
    // Traverse the merged heap to consolidate trees of equal degree
    while (nextNode)
    {
        // If the degrees of the current and next node are different or if the next node's degree is equal to the degree of its next sibling, move to the next nodes
        if (currentNode->degree != nextNode->degree || (nextNode->nextSibling && nextNode->degree == nextNode->nextSibling->degree))
        {
            previous = currentNode;
            currentNode = nextNode;
        }
        // If the distance of the current node is less than or equal to the distance of the next node, remove the next node from the merged heap and link it as a child of the current node
        else if (currentNode->distance <= nextNode->distance)
        {
            currentNode->nextSibling = nextNode->nextSibling;
            LinkHeap(nextNode, currentNode);
        }
        // If the distance of the current node is greater than the distance of the next node, remove the current node from the merged heap and link it as a child of the next node
        else
        {
            if (previous == nullptr)
                mergedHeap->head = nextNode;
            else
                previous->nextSibling = nextNode;
            LinkHeap(currentNode, nextNode);
            currentNode = nextNode;
        }
        nextNode = currentNode->nextSibling;
    }
    return mergedHeap;
}


void BinomialHeap::InsertHeap(BinoHeap *heap, BinoNode *node)
{
    BinoHeap newHeap = BulidHeap();
    newHeap->head = node;
    // Union the new heap h1 with the existing heap h
    *heap = UnionHeap(heap, &newHeap);
}


BinoNode* BinomialHeap::ExtractMin(BinoHeap *heap)
{
    BinoNode *current = (*heap)->head;
    BinoNode *minNode = nullptr, *prevMinNode = nullptr, *prev = nullptr;
    int minDistance;
    if (current == nullptr)
    {
        return current;
    }
    // Find the node with the minimum distance value
    minNode = current;
    minDistance = current->distance;
    prevMinNode = prev = current;
    current = current->nextSibling;
    while (current)
    {
        if (current->distance < minDistance)
        {
            minNode = current;
            minDistance = current->distance;
            prevMinNode = prev;
        }
        prev = current;
        current = current->nextSibling;
    }
    // Remove the minimum node from the heap
    if (minNode == (*heap)->head)
    {
        (*heap)->head = minNode->nextSibling;
    }
    else if (minNode->nextSibling == nullptr)
    {
        prevMinNode->nextSibling = nullptr;
    }
    else
    {
        prevMinNode->nextSibling = minNode->nextSibling;
    }
    // Reverse the children of the minimum node and add them to a new heap h1
    BinoNode *childNode = minNode->leftChild;
    if (childNode)
    {
        BinoHeap newHeap = BulidHeap();
        childNode->parent = nullptr;
        newHeap->head = childNode;
        current = childNode->nextSibling;
        childNode->nextSibling = nullptr;
        while (current)
        {
            prev = current;
            current = current->nextSibling;
            prev->nextSibling = newHeap->head;
            newHeap->head = prev;
            prev->parent = nullptr;
        }
        // Union the new heap h1 with the original heap
        *heap = UnionHeap(heap, &newHeap);
    }
    return minNode;
}

