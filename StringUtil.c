/* 
 * File:   StringUtil.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 3:59 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "StringUtil.h"

/*
 * 
 */
char* trim(char* str)
{
    char* lptr = NULL;
    char* rptr = NULL;
    char* newstr = NULL;
    char* temp = NULL;
    
    //First trim left side
    lptr = str;
    while(*lptr != '\0')
    {
        if(*lptr == ' ' || *lptr == '\n' || *lptr == '\r' || *lptr == '\t')
        {
            //trim it
            lptr++;
        }
        else
        {
            //stop trimming
            break;
        }
    }
    
    //Trim the right side
    rptr = str + stringlen(str) - 1;
    
    while(rptr > lptr)
    {
        if(*rptr == ' ' || *rptr == '\n' || *rptr == '\r' || *rptr == '\t')
        {
            //trim it
            rptr--;
        }
        else
        {
            //stop trimming
            break;
        }
    }
    
    //allocate new string
    newstr = (char*)malloc(rptr-lptr+2);
    temp = newstr;
    
    while(lptr <= rptr)
    {
        //copy string from lptr to rptr
        *newstr = *lptr;
        newstr++;
        lptr++;
    }
    //set the end of string in newstr
    *newstr = '\0';
    
    //free memory of str
    //free(str);
    
    //return newstr
    return temp;
}

int stringlen(char* str)
{
    int length = 0;
    char* s = str;
    while(*s != '\0')
    {
        length++;
        s++;
    }
    return length;
}

