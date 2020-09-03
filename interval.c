#include <stdio.h>
#include <stdlib.h>
#include "interval.h"

/***  Mesh  ***/

void meshInit(struct Mesh *m)
{
    size_t size = 4;
    m->totalSize = size;
    m->N = 0;
    m->heap = (struct Interval *)malloc(size * sizeof(struct Interval));
}

void meshFree(struct Mesh *m)
{
    m->totalSize = 0;
    m->N = 0;
    free(m->heap);
    m->heap = NULL;
}

void meshInsert(struct Mesh *m, struct Interval i)
{
    // Resize if necessary
    while(m->N >= m->totalSize)
    {
        m->totalSize *= 2;
        m->heap = (struct Interval *)realloc(m->heap,
                                    m->totalSize * sizeof(struct Interval));
    }
    // Add interval to end of heap
    m->heap[m->N] = i;
    (m->N)++;

    // Restore ordering
    meshHeapifyUp(m);
}

struct Interval meshExtract(struct Mesh *m)
{
    struct Interval worst = m->heap[0];

    m->heap[0] = m->heap[m->N-1];
    (m->N)--;

    meshHeapifyDown(m);

    return worst;
}

double meshTotalIntegral(struct Mesh *m)
{
    double I = 0.0;

    int i = 0;
    for(i=0; i<m->N; i++)
        I += m->heap[i].I;
    
    return I;
}

double meshTotalError(struct Mesh *m)
{
    double err = 0.0;

    int i = 0;
    for(i=0; i<m->N; i++)
        err += m->heap[i].err;
    
    return err;
}

void meshHeapifyUp(struct Mesh *m)
{
    int c = m->N-1;
    int p = (c-1)/2;

    while(c != 0 && m->heap[p].err < m->heap[c].err)
    {
        struct Interval tempP = m->heap[p];
        m->heap[p] = m->heap[c];
        m->heap[c] = tempP;
        c = p;
        p = (c-1)/2;
    }
}

void meshHeapifyDown(struct Mesh *m)
{
    int p = 0;
    int c1 = 2*p + 1;
    int c2 = c1 + 1;


    while(c1 < m->N)
    {
        //Find the child with largest error
        int c = c1;
        double e = m->heap[c1].err;

        if(c2 < m->N && m->heap[c2].err > e)
        {
            c = c2;
            e = m->heap[c2].err;
        }

        // If the child is already in order then we're done.
        if(e <= m->heap[p].err)
            break;

        // Otherwise, swap with the child.
        struct Interval tempP = m->heap[p];
        m->heap[p] = m->heap[c];
        m->heap[c] = tempP;
        p = c;
        c1 = 2*p + 1;
        c2 = c1 + 1;
    }
}

int meshCheck(struct Mesh *m)
{
    int p;
    for(p=0; p<=(m->N-2)/2; p++)
    {
        int c1 = 2*p+1;
        int c2 = c1 + 1;

        if(c1 < m->N && m->heap[c1].err > m->heap[p].err)
            return 0;
        
        if(c2 < m->N && m->heap[c2].err > m->heap[p].err)
            return 0;

    }

    return 1;
}

/***  Mesh 3  ***/

void mesh3Init(struct Mesh3 *m)
{
    size_t size = 4;
    m->totalSize = size;
    m->N = 0;
    m->heap = (struct Interval3 *)malloc(size * sizeof(struct Interval3));
}

void mesh3Free(struct Mesh3 *m)
{
    m->totalSize = 0;
    m->N = 0;
    free(m->heap);
    m->heap = NULL;
}

void mesh3Insert(struct Mesh3 *m, struct Interval3 i)
{
    // Resize if necessary
    while(m->N >= m->totalSize)
    {
        m->totalSize *= 2;
        m->heap = (struct Interval3 *)realloc(m->heap,
                                    m->totalSize * sizeof(struct Interval3));
    }
    // Add interval to end of heap
    m->heap[m->N] = i;
    (m->N)++;

    // Restore ordering
    mesh3HeapifyUp(m);
}

struct Interval3 mesh3Extract(struct Mesh3 *m)
{
    struct Interval3 worst = m->heap[0];

    m->heap[0] = m->heap[m->N-1];
    (m->N)--;

    mesh3HeapifyDown(m);

    return worst;
}

double mesh3TotalIntegral(struct Mesh3 *m)
{
    double I = 0.0;

    int i = 0;
    for(i=0; i<m->N; i++)
        I += m->heap[i].I;
    
    return I;
}

double mesh3TotalError(struct Mesh3 *m)
{
    double err = 0.0;

    int i = 0;
    for(i=0; i<m->N; i++)
        err += m->heap[i].err;
    
    return err;
}

void mesh3HeapifyUp(struct Mesh3 *m)
{
    int c = m->N-1;
    int p = (c-1)/2;

    while(c != 0 && m->heap[p].err < m->heap[c].err)
    {
        struct Interval3 tempP = m->heap[p];
        m->heap[p] = m->heap[c];
        m->heap[c] = tempP;
        c = p;
        p = (c-1)/2;
    }
}

void mesh3HeapifyDown(struct Mesh3 *m)
{
    int p = 0;
    int c1 = 2*p + 1;
    int c2 = c1 + 1;


    while(c1 < m->N)
    {
        //Find the child with largest error
        int c = c1;
        double e = m->heap[c1].err;

        if(c2 < m->N && m->heap[c2].err > e)
        {
            c = c2;
            e = m->heap[c2].err;
        }

        // If the child is already in order then we're done.
        if(e <= m->heap[p].err)
            break;

        // Otherwise, swap with the child.
        struct Interval3 tempP = m->heap[p];
        m->heap[p] = m->heap[c];
        m->heap[c] = tempP;
        p = c;
        c1 = 2*p + 1;
        c2 = c1 + 1;
    }
}

int mesh3Check(struct Mesh3 *m)
{
    int p;
    for(p=0; p<=(m->N-2)/2; p++)
    {
        int c1 = 2*p+1;
        int c2 = c1 + 1;

        if(c1 < m->N && m->heap[c1].err > m->heap[p].err)
            return 0;
        
        if(c2 < m->N && m->heap[c2].err > m->heap[p].err)
            return 0;

    }

    return 1;
}

/***  Mesh 5  ***/

void mesh5Init(struct Mesh5 *m)
{
    size_t size = 4;
    m->totalSize = size;
    m->N = 0;
    m->heap = (struct Interval5 *)malloc(size * sizeof(struct Interval5));
}

void mesh5Free(struct Mesh5 *m)
{
    m->totalSize = 0;
    m->N = 0;
    free(m->heap);
    m->heap = NULL;
}

void mesh5Insert(struct Mesh5 *m, struct Interval5 i)
{
    // Resize if necessary
    while(m->N >= m->totalSize)
    {
        m->totalSize *= 2;
        m->heap = (struct Interval5 *)realloc(m->heap,
                                    m->totalSize * sizeof(struct Interval5));
    }
    // Add interval to end of heap
    m->heap[m->N] = i;
    (m->N)++;

    // Restore ordering
    mesh5HeapifyUp(m);
}

struct Interval5 mesh5Extract(struct Mesh5 *m)
{
    struct Interval5 worst = m->heap[0];

    m->heap[0] = m->heap[m->N-1];
    (m->N)--;

    mesh5HeapifyDown(m);

    return worst;
}

double mesh5TotalIntegral(struct Mesh5 *m)
{
    double I = 0.0;

    int i = 0;
    for(i=0; i<m->N; i++)
        I += m->heap[i].I;
    
    return I;
}

double mesh5TotalError(struct Mesh5 *m)
{
    double err = 0.0;

    int i = 0;
    for(i=0; i<m->N; i++)
        err += m->heap[i].err;
    
    return err;
}

void mesh5HeapifyUp(struct Mesh5 *m)
{
    int c = m->N-1;
    int p = (c-1)/2;

    while(c != 0 && m->heap[p].err < m->heap[c].err)
    {
        struct Interval5 tempP = m->heap[p];
        m->heap[p] = m->heap[c];
        m->heap[c] = tempP;
        c = p;
        p = (c-1)/2;
    }
}

void mesh5HeapifyDown(struct Mesh5 *m)
{
    int p = 0;
    int c1 = 2*p + 1;
    int c2 = c1 + 1;


    while(c1 < m->N)
    {
        //Find the child with largest error
        int c = c1;
        double e = m->heap[c1].err;

        if(c2 < m->N && m->heap[c2].err > e)
        {
            c = c2;
            e = m->heap[c2].err;
        }

        // If the child is already in order then we're done.
        if(e <= m->heap[p].err)
            break;

        // Otherwise, swap with the child.
        struct Interval5 tempP = m->heap[p];
        m->heap[p] = m->heap[c];
        m->heap[c] = tempP;
        p = c;
        c1 = 2*p + 1;
        c2 = c1 + 1;
    }
}

int mesh5Check(struct Mesh5 *m)
{
    int p;
    for(p=0; p<=(m->N-2)/2; p++)
    {
        int c1 = 2*p+1;
        int c2 = c1 + 1;

        if(c1 < m->N && m->heap[c1].err > m->heap[p].err)
            return 0;
        
        if(c2 < m->N && m->heap[c2].err > m->heap[p].err)
            return 0;

    }

    return 1;
}
