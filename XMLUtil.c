/* 
 * File:   FileUtil.c
 * Author: anantha
 *
 * Created on 8 March, 2012, 9:01 AM
 */

#include "XMLUtil.h"
#include "Attribute.h"
#include "StringUtil.h"
#include "XMLNode.h"
#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

int LTStarted = 0;

//set while processing end tag
int endTag = 0;

//reset self-end tag
int isSelfEndTag = 0;

XMLNode* parseXML(FILE* fp) {
    //If FILE Pointer is NULL return
    if (fp == NULL) {
        printf(" Unable to parse XML. Please give a valid input file.\n");
        return;
    }

    //initialize node name to NULL
    char* nodedata = "";

    //Stack for processing nodes
    Stack* xmlNodeStack = NULL;

    //Attribute list of any node
    Attribute* attributeList = NULL;

    char ch = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '<') {

            //set top node's data
            XMLNode* topnode = top(&xmlNodeStack);
            if (topnode != NULL && topnode->data == NULL) {
                topnode->data = trim(nodedata);
            }

            //mark LTStarted flag as '<' is found
            LTStarted = 1;

            //Process node name and attributes list from the current xml node
            char* nodename = readNodeName(fp);

            //reset attributeList
            attributeList = NULL;

            //if LTStarted is set means that current node is not yet processed completely, i.e attributes may be present
            if (LTStarted == 1) {
                attributeList = readAttributes(fp);

                reverseAttribList(&attributeList);
                printAttributes(attributeList);
            }

            if (nodename != NULL) {
                if (endTag == 0 && isSelfEndTag == 0) {
                    //endTag is not set so it is a start tag
                    printf("Start Tag: %s\n", nodename);

                    //create new XML Node
                    XMLNode* xmlNode = createXMLNode(nodename, attributeList);

                    //push the newly created node into stack
                    push(&xmlNodeStack, xmlNode);

                } else {
                    XMLNode* xmlNode = NULL;
                    if (isSelfEndTag == 1) {
                        //Process self end tag

                        //create new XML Node
                        xmlNode = createXMLNode(nodename, attributeList);

                        printf("Self End Tag: %s\n", nodename);
                    } else {
                        //endTag is set, so it is an end tag
                        xmlNode = (XMLNode*) pop(&xmlNodeStack);

                        printf("End Tag: %s\n", nodename);

                        //check whether the end-tag is proper or not
                        //end-tag must be same as the start tag
                        if (compare(xmlNode->name, nodename) == 0) {
                            printf("XML Parse Error. XML tags mismatch: <%s>,</%s>", xmlNode->name, nodename);
                            return;
                        }


                    }

                    XMLNode* topNode = top(&xmlNodeStack);

                    if (topNode == NULL) {
                        printf("XML Parsed Successfully.");
                        return xmlNode;
                    }

                    //add xmlnode to topNode's children's list
                    addChild(topNode, xmlNode);
                }
            }

            //reset nodedata
            asprintf(&nodedata, "");
        } else {
            asprintf(&nodedata, "%s%c", nodedata, ch);
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

    //reset sef-end tag
    isSelfEndTag = 0;

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

                        //it is a self-end tag
                        isSelfEndTag = 1;

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

Attribute* readAttributes(FILE* fp) {
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
    int isReadingAttribName = 0;

    //reset sef-end tag
    isSelfEndTag = 0;

    //return if File pointer is NULL
    if (fp == NULL) {
        printf(" Cannot parse XML File. Please provide a valid input file. ");
        return NULL;
    }

    char ch = 0;
    //process the input file
    while ((ch = fgetc(fp)) != EOF) {

        //check whether the character is delimiter or not
        if ((ch == ' ' && readAttribute == 1) || ((ch == '/' || ch == '>') && attribflag == 0)) {


            //check end tag is proper or contains '/' in between or at the end of tag name
            if (ch == '/' && endTag == 1) {
                printf("Error while parsing end XML Node name.\n");
                return NULL;
            }

            if (newWord == 1) {

                //if attribflag is unset, it is an parser error, attribute value expected
                if (attribflag == 1 || (attribflag == 0 && readAttribute == 0)) {
                    printf("UnExpected Parser Error.\n");
                    return NULL;
                }

                //if attribute appears in end tag like </country id="IND"> it should result in error
                if (endTag == 1) {
                    printf("Parsing Error. attribute appears in end tag like </country id='IND'>\n");
                    return NULL;
                }

                /* Does it require?
                                if (attribflag != 0 && attribquotes != 0) {
                                    printf("Error while parsing XML \" Expected.");
                                }
                 */

                if (ch == '>') {
                    //if '>' is found, reset the LTStarted flag
                    LTStarted = 0;
                    return attributeList;
                }

                if (ch == '/') {
                    if (fgetc(fp) == '>') {

                        //it is a self-end tag
                        isSelfEndTag = 1;

                        //found end tag "/>"
                        return attributeList;
                    } else {
                        //parsing error
                        printf("XML Parsing error. '>' does not appear immediately after '/'.\n");
                        return NULL;
                    }
                }

                //reinitialize attribute for further processing
                attributename = "";
                attributevalue = "";

                //reset newWord flag
                newWord = 0;
            } else {
                if (ch == '>') {
                    //found end of tag
                    return attributeList;
                }

                if (ch == '/') {
                    if (fgetc(fp) == '>') {

                        //it is a self-end tag
                        isSelfEndTag = 1;

                        //found end tag "/>"
                        return attributeList;
                    } else {
                        //parsing error
                        printf("XML Parsing error. '>' does not appear immediately after '/'.\n");
                        return NULL;
                    }
                }

            }
        } else {

            //omit spaces in the beginning
            if (isReadingAttribName == 0 && ch == ' ') {
                continue;
            }

            //still we are reading attribute
            readAttribute = 0;

            if (ch == '=') {
                //to check that we are going to read attribute value
                attribflag = 1;
                continue;
            }

            //Process the character which belongs to current new word
            if (attribflag == 0) {

                //started reading attribute name
                isReadingAttribName = 1;

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
                return NULL;
            }

            if (attribflag == 1) {

                //check for end tag only after reading attribute value
                /*
                                if (ch == '/' || ch == '>') {
                                    //unexpected end of tag, attribute value expected
                                    printf("Unexpected end of tag, attribute value expected");
                                    return NULL;
                                }
                 */

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

                //insert into attribute list
                addtoAttributeList(&attributeList, trim(attributename), trim(attributevalue));

                attributename = "";
                attributevalue = "";
            }
        }
    }
    return attributeList;
}

void printXML(XMLNode* root) {
    Stack* stack = NULL;

    XMLNode* xmlnode = root;

    int depth = 0;

    while (xmlnode != NULL) {
        //print depth number of tabs
        printDepth(depth);

        //print open tag
        printf("<%s>\n", xmlnode->name);

        //print data if any
        if (xmlnode->data != NULL && stringlen(xmlnode->data) > 0) {
            //print depth number of tabs
            printDepth(depth + 1);
            printf("%s\n", xmlnode->data);
        }

        /*
                //print newline if child nodes are present
                if( xmlnode->child != NULL )
                {
                    printf("\n");
                }
         */

        //push xmlnode to stack
        push(&stack, xmlnode);

        if (xmlnode->child != NULL) {
            //Get the first child
            xmlnode = xmlnode->child;

            //increment the depth
            depth++;
        } else {
            do {
                //pop the element from stack
                xmlnode = pop(&stack);

                //print end tag
                if (xmlnode != NULL) {
                    //print depth number of tabs
                    printDepth(depth);

                    printf("</%s>\n", xmlnode->name);
                }

                if (xmlnode == NULL || xmlnode->sibling != NULL) {
                    //either stack is empty or node with sibling is found
                    if (xmlnode != NULL) {
                        xmlnode = xmlnode->sibling;
                    }
                    break;
                } else {
                    //decrement the depth
                    depth--;
                }
            } while (1);
        }
    }
}

int printDepth(int depth) {
    int i = 0;

    for (i = 0; i < depth; i++) {
        printf("\t");
    }
}