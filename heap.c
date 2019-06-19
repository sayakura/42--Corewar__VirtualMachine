#include<stdio.h>
#include<stdlib.h>
#include "heap.h"

t_heap *CreateHeap(int capacity,int heap_type, size_t size)
{
    t_heap *h;
    
    h = (t_heap * ) malloc(sizeof(t_heap));
    if(!h)
        return NULL;
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->arr = malloc(capacity * size);
    if (!h->arr)
        return NULL;
    return h;
}

void insert(t_heap *h, int key)
{
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(t_heap *h,int index){
    int temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node] > h->arr[index])
    {
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(h,parent_node);
    }
}

void heapify_top_bottom(t_heap *h, int parent_node)
{
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    int temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;
    if(left != -1 && h->arr[left] < h->arr[parent_node])
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right] < h->arr[min])
        min = right;
    if(min != parent_node)
    {
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;
        heapify_top_bottom(h, min);
    }
}

int pop(t_heap *h)
{
    int     pop;

    if (h->count==0)
    {
        return -1;
    }
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

void print(t_heap *h)
{
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %d ",h->arr[i]);
    }
    printf("->__/\\__\n");
}

int main(){
    int i;
    t_heap *heap = CreateHeap(20, 0); //Min t_heap
    if( heap == NULL ){
        printf("__Memory Issue____\n");
        return -1;
    }

    for(i =9;i>0;i--)
        insert(heap, i);

    print(heap);

    for(i=9;i>=0;i--){
        printf(" Pop Minima : %d\n", pop(heap));
        print(heap);
    }
    return 0;
}