/* 
 * File:   XMLNode.h
 * Author: anantha
 *
 * Created on 9 March, 2012, 3:40 AM
 */

#ifndef XMLNODE_H
#define	XMLNODE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "Attribute.h"

    typedef struct XMLNode
    {
        char* name;
        struct XMLNode* child;
        struct XMLNode* sibling;
        struct Attribute* attributeList;
    }XMLNode;


    XMLNode* createXMLNode(char* name,Attribute* attributeList);
    
#ifdef	__cplusplus
}
#endif

#endif	/* XMLNODE_H */

