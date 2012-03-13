/* 
 * File:   XMLNode.c
 * Author: anantha
 *
 * Created on 13 March, 2012, 1:18 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "XMLNode.h"

/*
 * 
 */
XMLNode* createXMLNode(char* name,Attribute* attributeList)
{
    XMLNode* newNode = (XMLNode*)malloc(sizeof(XMLNode));
    
    if( newNode == NULL )
    {
        printf("Memory Error.");
        return NULL;
    }
    
    newNode->name = name;
    newNode->attributeList = attributeList;
    
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->data = NULL;
    
    return newNode;
}


void addChild(XMLNode* topNode,XMLNode* xmlNode)
{
    if(topNode == NULL)
    {
        //return
        return;
    }
    
    XMLNode* head = topNode->child;
    
    if(head == NULL)
    {
        //topNode contains 0 children
        
        //make xmlNode as topNode's child
        topNode->child = xmlNode;
        return;
    }
    
    while(head->sibling != NULL)
    {
        //traverse the topNode's children list
        head = head->sibling;
    }
    
    //make head's sibling as xmlNode
    head->sibling = xmlNode;
    return;
}
