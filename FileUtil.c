/* 
 * File:   FileUtil.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 9:01 AM
 */

#include "FileUtil.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
FILE* openFile(char* filename)
{
    //initialize File Pointer to NULL
    FILE* fp = NULL;
    
    //try to open file
    fp = fopen(filename,"r");
    
    //check File opened successfully or not
    if( fp == NULL )
    {
        printf(" Error while opening file. ");
        return 0;
    }
    
    //file opened successfully
    return fp;
    
}

//Split words from a sentence
void split(FILE* fp,char delimiter)
{
    //No new word is encountered
    int newWord = 0;
    
    //return if File pointer is NULL
    if( fp == NULL )
    {
        printf(" Cannot split words. Please provide a valid input file. ");
        return;
    }
    
    char ch = 0;
    //process the input file
    while( (ch = fgetc(fp)) != EOF )
    {
        //check whether the character is delimiter or not
        if( ch == delimiter )
        {
            if( newWord == 1 )
            {
                //Already we processed a new word now we found delimiter
                printf("\n");
                
                //reset newWord 
                newWord = 0;
            }
        }
        else
        {
            //Process the character which belongs to current new word
            printf("%c",ch);
            
            //mark newWord which represents the current word that is being read
            newWord = 1;
        }
    }
}