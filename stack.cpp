#include <string.h>
#include <assert.h>
#include "stack.h"

void initStack(Stack *stk)
{
    assert(stk != nullptr);

    stk->head = stk->tail = nullptr;
    stk->size = 0;
}

void destroyStack(Stack *stk)
{
    assert(stk != nullptr);

    Node *temp = nullptr;

    while (stk->tail != nullptr)
    {
        temp = stk->tail->previous;

        free(stk->tail->element);

        free(stk->tail);

        stk->tail = temp;
    }

    stk->head = nullptr;

    stk->size = 0;
}

int stack_push(Stack *stk, const void *element, size_t elementSize,
               void (*copyFunction)(void *target, const void *source))
{
    assert(stk     != nullptr);
    assert(element != nullptr);

    if (stk->tail == nullptr)
    {
        stk->head = stk->tail = (Node *) calloc(1, sizeof(Node));

        if (stk->tail == nullptr)
            return 0;

        stk->tail->previous = stk->tail->next = nullptr;

        stk->tail->size = elementSize;

        stk->tail->element = calloc(1, elementSize);

        if (stk->tail->element == nullptr)
        {
            free(stk->tail);

            stk->head = stk->tail = nullptr;

            return 0;
        }

        copyFunction(stk->tail->element, element);

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

        stk->tail->size = elementSize;

        stk->tail->element = calloc(1, elementSize);

        if (stk->tail->element == nullptr)
        {
            temp->next = nullptr;

            free(stk->tail);

            stk->tail = temp;

            return 0;
        }

        copyFunction(stk->tail->element, element);

        ++(stk->size);
    }

    return 1;
}

int stack_pop(Stack *stk, void *element, void (*copyFunction)(void *target, const void *source))
{
    assert(stk     != nullptr);
    assert(element != nullptr);

    if (stk->size == 0)
        return 0;

    Node *temp = stk->tail;

    stk->tail = stk->tail->previous;

    if (stk->tail != nullptr)
        stk->tail->next = nullptr;

    --(stk->size);

    copyFunction(element, temp->element);

    free(temp->element);
    free(temp);

    if (stk->tail == nullptr)
        stk->head = nullptr;

    return 1;
}

size_t stack_size(const Stack *stk)
{
    assert(stk != nullptr);

    return stk->size;
}

int stack_isEmpty(const Stack *stk)
{
    assert(stk != nullptr);

    return stk->size == 0;
}
