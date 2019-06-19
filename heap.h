#ifndef HEAP_H

#define HEAP_H


typedef struct s_heap
{
    void    *arr;
    int     count;
    int     capacity;
    int     heap_type;
}              t_heap;

t_heap *CreateHeap(int capacity,int heap_type);
void insert(t_heap *h, int key);
void print(t_heap *h);
void heapify_bottom_top(t_heap *h,int index);
void heapify_top_bottom(t_heap *h, int parent_node);
int pop(t_heap *h);

#endif