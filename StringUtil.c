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

int compare(char* str1,char* str2)
{
    
    if( str1 == NULL && str2 == NULL )
    {
        //both strings are same if both are NULL
        return 1;
    }
    
    if( str1 == NULL || str2 == NULL )
    {
        //if any one string is NULL, both are different
        return 0;
    }
    
    while( *str1 != '\0' && *str2 != '\0' )
    {
        if( *str1 != *str2 )
        {
            //there is a mismatch
            return 0;
        }
        str1++;
        str2++;
    }
    
    if( *str1 == '\0' && *str2 == '\0' )
    {
        //reached end of the string after comparing the characters one-by-one 
        return 1;
    }
    
    //mismatch
    return 0;
}

