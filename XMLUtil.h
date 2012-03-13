/* 
 * File:   XMLUtil.h
 * Author: anantha
 *
 * Created on 8 March, 2012, 9:10 AM
 */

#ifndef XMLUTIL_H
#define	XMLUTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#include "Attribute.h"
#include "XMLNode.h"

    XMLNode* parseXML(FILE* fp);
    char* readNodeName(FILE* fp);
    Attribute* readAttributes(FILE* fp);
    
    void printXML(XMLNode* root);

#ifdef	__cplusplus
}
#endif

#endif	/* XMLUTIL_H */

