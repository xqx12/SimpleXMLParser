/* 
 * File:   FileUtil.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 9:01 AM
 */

#include "XMLUtil.h"

#include <stdio.h>
#include <stdlib.h>

int LTStarted = 0;

void parseXML(FILE* fp) {
    //If FILE Pointer is NULL return
    if (fp == NULL) {
        printf(" Unable to parse XML. Please give a valid input file.\n");
        return;
    }

    char ch = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '<') {
            //mark LTStarted flag as '<' is found
            LTStarted = 1;

            //Process node name and attributes list from the current xml node
            char* nodename = readNodeName(fp);
            if (nodename != NULL)
                printf("%s %d\n", nodename, LTStarted);
            //readAttributes(fp);
        }
    }
}

char* readNodeName(FILE* fp) {
    //initialize node name to NULL
    char* nodename = "";

    //No new word is encountered
    int newWord = 0;

    //set while processing end tag
    int endTag = 0;

    //return if File pointer is NULL
    if (fp == NULL) {
        printf(" Cannot parse XML File. Please provide a valid input file. ");
        return;
    }

    char ch = 0;
    //process the input file
    while ((ch = fgetc(fp)) != EOF) {
        //check whether the character is delimiter or not
        if (ch == ' ' || ch == '/' || ch == '>') {
            if (newWord == 1) {
                //check end tag is proper or contains '/' in between or at the end of tag name
                if (ch == '/' && endTag == 1) {
                    printf("Error while parsing end XML Node name.\n");
                    return NULL;
                }

                if (ch == '>' || ch == '/' ) {
                    //if '>' or '/' is found, reset the LTStarted flag
                    LTStarted = 0;
                }

                //Already we processed a new word now we found delimiter
                return nodename;
            } else {
                if (ch == '/') {
                    //It is an end tag, continue reading the end tag name
                    endTag = 1;
                    continue;
                }

                //space or '>' appears immediately after '<' 
                printf("Error while parsing XML Node name.\n");
                return NULL;
            }
        } else {
            //Process the character which belongs to current new word
            asprintf(&nodename, "%s%c", nodename, ch);

            //mark newWord which represents the current word that is being read
            newWord = 1;
        }
    }
    return NULL;
}
