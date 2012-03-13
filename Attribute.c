
/* 
 * File:   FileUtil.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 7:34 PM
 */

#include "Attribute.h"
#include "StringUtil.h"

#include <stdio.h>
#include <stdlib.h>

Attribute* createAttributeNode(char* name, char* value)
{
    //create new node
    Attribute* newnode = (Attribute*)malloc(sizeof(Attribute));
    
    //check memory allocated successfully or not
    if(newnode == NULL)
    {
        printf("Error occured while allocating memory for attributes.");
        return;
    }
    
    //initialize newly created list node
    newnode->name = name;
    newnode->value = value;
    newnode->sibling = NULL;
    
    //return the newly created node
    return newnode;
}

void addtoAttributeList(Attribute** attrbList, char* name, char* value)
{
    
    //remove doublequotes from attribute value
    if( *value == '\"')
    {
        value++;
    }
    
    int len = stringlen(value);
    
    if( *(value + len - 1) == '\"')
    {
        *(value + len - 1) = '\0';
    }
    
    //create new node with name and value
    Attribute* newnode = createAttributeNode(name,value);
    
    //if attrbList is empty make newnode as head of list
    if(*attrbList == NULL)
    {
        *attrbList = newnode;
        return;
    }
    
    //add new node to the head of list
    newnode->sibling = *attrbList;
    
    //make newnode as new head
    *attrbList = newnode;
    
    return;
}

void reverseAttribList(Attribute** attrbList)
{
    //simply return if list is empty
    if(*attrbList == NULL)
    {
        return;
    }
    
    //have three pointers to reverse the list in O(n)
    Attribute* p = NULL;
    Attribute* q = *attrbList;
    Attribute* r = NULL;
    
    //if there is only one node, simple return
    if(q->sibling == NULL)
    {
        return;
    }
    
    //make r to point 2nd node initially
    r = q->sibling;
    
    //start reversing the given list
    while(1)
    {
        //reverse the link of q by pointing to p
        q->sibling = p;
        
        if( r == NULL )
        {
            //Reached end of list, make q as new head of the list
            *attrbList = q;
            return;
        }
        //now move p,q,r by one step
        p = q;
        q = r;
        //move r to the next node in the list
        r = r->sibling;
    }
}

void printAttributes(Attribute* attributeList)
{
    while(attributeList != NULL)
    {
        printf("\nName: %s,Value: %s\n",attributeList->name,attributeList->value);
        attributeList = attributeList->sibling;
    }
}