#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "newmergesort.h"


/// One merge iteration into source
/// @param [in] source Source array
/// @param [out] targe Target array
/// @param [in] size Size of source array
/// @param [in] elementSize Size of one element in array
/// @param [in] comparator Function pointer to comparator
/// @return Count of merge in this iterate
static unsigned mergeIteration(void *source, void *target, size_t size, size_t elementSize,
                          int (*comparator)(const void *, const void *));

/// Merge two sub-arrays
/// @param [in] firstSubArray First sub array for merge
/// @param [in] secondSubArray Second sub array for merge
/// @param [in/out] targetArray Array who will has result of merge
/// @param [in] firstSize Size of first sub array
/// @param [in] secondSize Size of second sub array
/// @param [in] elementSize Size of one element in array
/// @param [in] comparator Function pointer to comparator for elements in collection
static void merge(void  *firstSubArray, void  *secondSubArray, void *targetArray,
                  size_t firstSize    , size_t secondSize    , size_t elementSize,
                  int (*comparator)(const void *, const void *));

void newMergeSort(void *buffer, size_t size, size_t elementSize, int (*comparator)(const void *, const void *))
{
    assert(buffer     != nullptr);
    assert(comparator != nullptr);

    assert(elementSize > 0);

    if (size < 2)
        return;

    void *temp = calloc(size, elementSize);

    if (temp == nullptr)
        return;

    void *source = buffer,
         *target = temp;

    while (mergeIteration(source, target, size, elementSize, comparator) != 0)
    {
        void *buff = source;

        source = target;
        target = buff;
    }

    if (source != buffer)
        memcpy(buffer, temp, size*elementSize);

    free(temp);
}

static unsigned mergeIteration(void *source, void *target, size_t size, size_t elementSize,
                           int (*comparator)(const void *, const void *))
{
    assert(source     != nullptr);
    assert(target     != nullptr);
    assert(comparator != nullptr);

    assert(elementSize > 0);

    void *first  = source,
         *second = source;

    size_t firstSize  = 0,
           secondSize = 0;

    void *end = source + size*elementSize;

    unsigned mergeCount = 0;

    while (first < end)
    {
        first = second + secondSize*elementSize;

        for (firstSize = 0; first + firstSize*elementSize < end; ++firstSize)
        {
            if (firstSize == 0)
                continue;

            if (comparator(first + (firstSize - 1)*elementSize, first + firstSize*elementSize) > 0)
                break;
        }

        if (first + firstSize*elementSize == end)
        {
            merge(first, second, target, firstSize, 0, elementSize, comparator);

            return mergeCount;
        }

        second = first + firstSize*elementSize;

        for (secondSize = 0; second + secondSize*elementSize < end; ++secondSize)
        {
            if (secondSize == 0)
                continue;

            if (comparator(second + (secondSize - 1)*elementSize, second + secondSize*elementSize) > 0)
                break;
        }

        merge(first, second, target, firstSize, secondSize, elementSize, comparator);

        ++mergeCount;

        target += (firstSize + secondSize)*elementSize;
    }

    return mergeCount;
}

static void merge(void  *firstSubArray, void  *secondSubArray, void *targetArray,
                  size_t firstSize    , size_t secondSize    , size_t elementSize,
                  int (*comparator)(const void *, const void *))
{
    assert(firstSubArray  != nullptr);
    assert(secondSubArray != nullptr);
    assert(targetArray    != nullptr);
    assert(comparator     != nullptr);

    assert(elementSize > 0);

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
