/* 
 * File:   FileUtil.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 9:01 AM
 */

#include "XMLUtil.h"
#include "Attribute.h"
#include "StringUtil.h"

#include <stdio.h>
#include <stdlib.h>

int LTStarted = 0;

//set while processing end tag
int endTag = 0;

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
            if (nodename != NULL) {
                if (endTag == 0) {
                    //endTag is not set so it is a start tag
                    printf("Start Tag: %s\n", nodename);
                } else {
                    //endTag is set, so it is an end tag
                    printf("End Tag: %s\n", nodename);
                }
            }

            //if LTStarted is set means that current node is not yet processed completely, i.e attributes may be present
            if (LTStarted == 1) {
                readAttributes(fp);
            }
        }
    }
}

char* readNodeName(FILE* fp) {
    //initialize node name to NULL
    char* nodename = "";

    //No new word is encountered
    int newWord = 0;

    //reset endTag
    endTag = 0;

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

                if (ch == '>') {
                    //if '>' is found, reset the LTStarted flag
                    LTStarted = 0;
                }

                if (ch == '/') {
                    if (fgetc(fp) == '>') {
                        //found end tag "/>"
                        endTag = 1;
                        //we have to reset LTStarted flag
                        LTStarted = 0;
                        return nodename;
                    } else {
                        //parsing error
                        printf("XML Parsing error. '>' does not appear immediately after '/'.\n");
                        return NULL;
                    }
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

void readAttributes(FILE* fp) {
    //create new Attribute list
    Attribute* attributeList = NULL;

    //initialize attribute to NULL
    char* attributename = "";
    char* attributevalue = "";

    //No new word is encountered
    int newWord = 0;

    int attribflag = 0;
    int attribquotes = 0;
    int readAttribute = 0;

    //return if File pointer is NULL
    if (fp == NULL) {
        printf(" Cannot parse XML File. Please provide a valid input file. ");
        return;
    }

    char ch = 0;
    //process the input file
    while ((ch = fgetc(fp)) != EOF) {

        //check whether the character is delimiter or not
        if ((ch == ' ' && readAttribute == 1) || ((ch == '/' || ch == '>') && attribflag == 0)) {


            //check end tag is proper or contains '/' in between or at the end of tag name
            if (ch == '/' && endTag == 1) {
                printf("Error while parsing end XML Node name.\n");
                return;
            }

            if (newWord == 1) {

                //if attribflag is unset, it is an parser error attribute value expected
                if (attribflag == 1 || (attribflag == 0 && readAttribute == 0)) {
                    printf("UnExpected Parser Error.\n");
                    return;
                }

                //if attribute appears in end tag like </country id="IND"> it should result in error
                if (endTag == 1) {
                    printf("Parsing Error. attribute appears in end tag like </country id='IND'>\n");
                    return;
                }

                /* Does it require?
                                if (attribflag != 0 && attribquotes != 0) {
                                    printf("Error while parsing XML \" Expected.");
                                }
                 */

                if (ch == '>' || ch == '/') {
                    //if '>' or '/' is found, reset the LTStarted flag
                    LTStarted = 0;
                    return;
                }

                //reinitialize attribute for further processing
                attributename = "";
                attributevalue = "";

                //reset newWord flag
                newWord = 0;
            } else {
                if (ch == '>') {
                    //found end of tag
                    return;
                }

                if (ch == '/') {
                    if (fgetc(fp) == '>') {
                        //found end tag "/>"
                        return;
                    } else {
                        //parsing error
                        printf("XML Parsing error. '>' does not appear immediately after '/'.\n");
                        return;
                    }
                }

            }
        } else {
            //still we are reading attribute
            readAttribute = 0;

            if (ch == '=') {
                //to check that we are going to read attribute value
                attribflag = 1;
                continue;
            }

            //Process the character which belongs to current new word
            if (attribflag == 0) {
                //save attribute name
                asprintf(&attributename, "%s%c", attributename, ch);
            } else {
                //save attribute value
                asprintf(&attributevalue, "%s%c", attributevalue, ch);
            }

            //mark newWord which represents the current word that is being read
            newWord = 1;

            if (ch == '\"' && attribflag == 0) {
                printf("XML Parsing error. Check \" \n");
                return;
            }

            if (attribflag == 1) {
                if (ch == '\"') {
                    //simply increment quotes count
                    attribquotes++;
                }
            }

            if (attribquotes == 2) {
                //We have read one attribute pair successfully
                //Already we processed a new word now we found delimiter
                attribflag = 0;
                attribquotes = 0;
                readAttribute = 1;
                printf("Attribute_1: |%s|%s|\n", trim(attributename), trim(attributevalue));
                attributename = "";
                attributevalue = "";
            }




        }
    }
    return;
}

