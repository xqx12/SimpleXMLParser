/* 
 * File:   Attribute.h
 * Author: anantha
 *
 * Created on 8 March, 2012, 2:32 PM
 */

#ifndef ATTRIBUTE_H
#define	ATTRIBUTE_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct Attribute
    {
        char* name;
        char* value;
        struct Attribute* sibling;
    }Attribute;
    
    Attribute* createAttributeNode(char* name,char* value);
    void addtoAttributeList(Attribute** attrbList,char* name,char* value);
    void reverseAttribList(Attribute** attrbList);

#ifdef	__cplusplus
}
#endif

#endif	/* ATTRIBUTE_H */

