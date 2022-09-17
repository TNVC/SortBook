/// Stack work with heap

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

typedef struct element {
    const char *functionName;
    const char *fileName;
    int line;
} StackElement;

typedef struct node {
    StackElement element;
    node *previous;
    node *next;
} Node;

typedef struct stack {
    Node *head;
    Node *tail;
    int size;
} Stack;

/// Init Stack to use
/// @param [in/out] stk Pointer to stack for init
/// @note Call before all using
void initStack(Stack *stk);

/// Destroy Stack
/// @param [in] stk Pointer to stack for destroy
/// @note Call after all using
void destroyStack(Stack *stk);

/// Push one element to stack
/// @param [in/out] stk Stack
/// @param [in] element Element to push
/// @return 1 if element was push or 0 if element wasn`t push
int stack_push(Stack *stk, const StackElement *element);

/// Pop one element from stack
/// @param [in/out] stk Stack
/// @param [out] element Container for pop-element
/// @return 1 if was pop element or 0 if wasn`t pop element
int stack_pop(Stack *stk, StackElement *element);

/// Size of Stack
/// @param [in] stk Stack
/// @return Size of stack
int stack_size(const Stack *stk);

/// Check that stack is empty
/// @param [in] stk Stack
/// @return 1 if Stack is empty or 0 if is not
int stack_isEmpty(const Stack *stk);

/// Print Stack into filePtr
/// @param [in] stk Stack to print
/// @param [in] filePtr File for print
void stack_print(const Stack *stk, FILE *filePtr);

#endif
