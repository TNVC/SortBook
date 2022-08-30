#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "newmergesort.h"

/// Merge two sub-arrays
/// @param [in] firstSubArray First sub array for merge
/// @param [in] secondSubArray Second sub array for merge
/// @param [in/out] targetArray Array who will has result of merge
/// @param [in] firstSize Size of first sub array
/// @param [in] secondSize Size of second sub array
/// @param [in] elementSize Size of one element in array
/// @param [in] comparator Function pointer to comparator for elements in collection
void merge(void  *firstSubArray, void  *secondSubArray, void *targetArray,
                  size_t firstSize    , size_t secondSize    , size_t elementSize,
                  int (*comparator)(const void *, const void *));

void newMergeSort(void *buffer, size_t size, size_t elementSize, int (*comparator)(const void *, const void *))
{
    assert(buffer     != nullptr);
    assert(comparator != nullptr);

    if (size < 2)
        return;

    if (size == 2)
    {
        if (comparator(buffer, (buffer + elementSize)) > 0)
        {
            void *temp = calloc(1, elementSize);

            memcpy(temp                  ,  buffer               , elementSize);
            memcpy(buffer                , (buffer + elementSize), elementSize);
            memcpy((buffer + elementSize),  temp                 , elementSize);

            free(temp);
        }

        return;
    }

    size_t firstSize  = 0,
           secondSize = 0;

    firstSize  = size / 2;
    secondSize = size - firstSize;

    newMergeSort( buffer                         , firstSize , elementSize, comparator);
    newMergeSort((buffer + firstSize*elementSize), secondSize, elementSize, comparator);

    void *temp = calloc(size, elementSize);

    if (temp == nullptr)
        return;///remake

    merge(buffer, (buffer + secondSize*elementSize), temp, firstSize, secondSize, elementSize, comparator);

    memcpy(buffer, temp, size);

    free(temp);
}

void merge(void  *firstSubArray, void  *secondSubArray, void *targetArray,
                  size_t firstSize    , size_t secondSize    , size_t elementSize,
                  int (*comparator)(const void *, const void *))
{
    assert(firstSubArray  != nullptr);
    assert(secondSubArray != nullptr);
    assert(targetArray    != nullptr);
    assert(comparator     != nullptr);

    size_t i = 0, j = 0;

    size_t currentIndex = 0;

    void *temp = nullptr;

    while (currentIndex < firstSize + secondSize)
    {
        if      (i == firstSize)
            temp = (secondSubArray + (j++)*elementSize);
        else if (j == secondSize)
            temp = (firstSubArray  + (i++)*elementSize);
        else if (comparator((firstSubArray + i*elementSize), (secondSubArray + j*elementSize)) < 0)
            temp = (firstSubArray  + (i++)*elementSize);
        else
            temp = (secondSubArray + (j++)*elementSize);

        memcpy((targetArray + (currentIndex++)*elementSize), temp, elementSize);
    }
}
