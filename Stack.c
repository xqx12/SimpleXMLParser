/* 
 * File:   Stack.c
 * Author: anantha
 *
 * Created on 12 March, 2012, 6:37 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

Stack* createStackNode(void* data)
{
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    
    if( newNode == NULL )
    {
        printf("Stack - Memory Error.");
        return NULL;
    }
    
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}

Stack* push(Stack** S, void* data)
{
    Stack* newNode = createStackNode(data);
    
    if( newNode == NULL )
    {
        printf("Memory error");
        return;
    }
    newNode->next = *S;
    *S = newNode;
    
}

void* pop(Stack** S)
{
    Stack* node = *S;
    
    if( *S == NULL )
    {
        printf("Stack empty.");
        return NULL;
    }
    
    *S = (*S)->next;
    
    return node->data;
}

void* top(Stack** S)
{
    Stack* node = *S;
    
    if( *S == NULL )
    {
        printf("Stack empty.");
        return NULL;
    }
    
    return node->data;
}

