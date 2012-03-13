/* 
 * File:   simpleXMLParser.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 8:52 AM
 */

#include "FileUtil.h"
#include "XMLUtil.h"
#include "StringUtil.h"

#include <stdio.h>
#include <stdlib.h>

int readFile()
{
    //initialize File Pointer to NULL
    FILE* fp = NULL;
    
    //try to open file
    fp = fopen("test.txt","r");
    
    //check File opened successfully or not
    if( fp == NULL )
    {
        printf(" Error while opening file. ");
        return EXIT_FAILURE;
    }
    
    //read character by character and display them in console
    char ch = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c",ch);
    }
    
    return EXIT_SUCCESS;
}



/*
 * 
 */
int main(int argc, char** argv) {

    FILE* fp = openFile("input.xml");
    
    XMLNode* root = parseXML(fp);
    
    printXML(root);
    
    return (EXIT_SUCCESS);
}

