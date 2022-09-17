/// Stack work with heap

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *element;
    size_t size;
    node *previous;
    node *next;
} Node;

typedef struct stack {
    Node *head;
    Node *tail;
    size_t size;
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
/// @param [in] elementSize Size of element
/// @param [in] copyFunction Function for copy element
/// @return 1 if element was push or 0 if element wasn`t push
int stack_push(Stack *stk, const void *element, size_t elementSize,
               void (*copyFunction)(void *target, const void *source));

/// Pop one element from stack
/// @param [in/out] stk Stack
/// @param [out] element Container for pop-element
/// @param [in] copyFunction Function for copy element
/// @return 1 if was pop element or 0 if was not
int stack_pop(Stack *stk, void *element, void (*copyFunction)(void *target, const void *source));

/// Size of Stack
/// @param [in] stk Stack
/// @return Size of stack
size_t stack_size(const Stack *stk);

/// Check that stack is empty
/// @param [in] stk Stack
/// @return 1 if Stack is empty or 0 if is not
int stack_isEmpty(const Stack *stk);

#endif
