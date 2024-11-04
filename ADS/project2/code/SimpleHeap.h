#pragma once

#include "head.h"

typedef struct node
{
    int vertex;
    int distance;
    bool operator<(const node &node) const
    {
        return node.distance < distance;
    }
} SimpNode;

class SimpleHeap : public Heap
{
private:
    priority_queue<SimpNode> q;
    SimpNode newNode;

public:
    SimpleHeap()
    {
        q = priority_queue<SimpNode>();
        newNode = SimpNode();
    };
    void initial()
    {
        q = priority_queue<SimpNode>();
    }
    void push(int vertex, int distance)
    {
        newNode.vertex = vertex;
        newNode.distance = distance;
        q.push(newNode);
    }
    void pop()
    {
        q.pop();
    }
    pair<int, int> top()
    {
        newNode = q.top();
        return GNode(newNode.vertex, newNode.distance);
    }
    bool empty()
    {
        return q.empty();
    }
};