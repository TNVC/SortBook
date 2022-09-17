#include <string.h>
#include <asserts.h>
#include "stack.h"

static void copyElement(StackElement *target, const StackElement *source);

void initStack(Stack *stk)
{
    pointerAssert(stk, nullptr);

    stk->head = stk->tail = nullptr;
    stk->size = 0;
}

void destroyStack(Stack *stk)
{
    pointerAssert(stk, nullptr);

    Node *temp = nullptr;

    while (stk->tail != nullptr)
    {
        temp = stk->tail->previous;

        free(stk->tail);

        stk->tail = temp;
    }

    stk->size = 0;
}

int stack_push(Stack *stk, const StackElement *element)
{
    pointerAssert(stk    , nullptr);
    pointerAssert(element, nullptr);

    if (stk->tail == nullptr)
    {
        stk->head = stk->tail = (Node *) calloc(1, sizeof(Node));

        if (stk->tail == nullptr)
            return 0;

        stk->tail->previous = stk->tail->next = nullptr;

        copyElement(&stk->tail->element, element);

        ++(stk->size);
    }
    else
    {
        Node *temp = stk->tail;

        stk->tail = (Node *) calloc(1, sizeof(Node));

        if (stk->tail == nullptr)
            return 0;

        stk->tail->previous = temp;
        stk->tail->next     = nullptr;

        temp->next = stk->tail;

        copyElement(&stk->tail->element, element);

        ++(stk->size);
    }

    return 1;
}

int stack_pop(Stack *stk, StackElement *element)
{
    pointerAssert(stk    , nullptr);
    pointerAssert(element, nullptr);

    if (stk->size == 0)
        return 0;

    Node *temp = stk->tail;

    stk->tail = stk->tail->previous;

    --(stk->size);

    copyElement(element, &temp->element);

    free(temp);

    if (stk->tail == nullptr)
        stk->head = nullptr;

    return 1;
}

int stack_size(const Stack *stk)
{
    pointerAssert(stk, nullptr);

    return stk->size;
}

int stack_isEmpty(const Stack *stk)
{
    pointerAssert(stk, nullptr);

    return stk->size == 0;
}

static void copyElement(StackElement *target, const StackElement *source)
{
    //target->functionName = strdup(source->functionName);
    //target->fileName     = strdup(source->fileName);
    //target->line = source->line;

    *target = *source;
}

void stack_print(const Stack *stk, FILE *filePtr)
{
    pointerAssert(stk    , nullptr);
    pointerAssert(filePtr, nullptr);

    int i = stk->size;

    fprintf(filePtr, "=========================STACK_TRACE=========================\n");

    for (Node *temp = stk->tail; temp != nullptr; temp = temp->previous, --i)
        fprintf(filePtr, "#%d %120s at %30s in line %4d\n",
                i, temp->element.functionName, temp->element.fileName, temp->element.line);

    fprintf(filePtr, "=============================================================\n");
}
