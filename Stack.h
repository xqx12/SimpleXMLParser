/* 
 * File:   Stack.h
 * Author: anantha
 *
 * Created on 12 March, 2012, 6:21 PM
 */

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct Stack
    {
        void* data;
        struct Stack* next;
    }Stack;
    
    Stack* createStackNode(void* data);
    Stack* push(Stack** S,void* data);
    void* pop(Stack** S);
    void* top(Stack** S);


#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */

