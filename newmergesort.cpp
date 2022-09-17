#include <stdlib.h>
#include <string.h>
#include "newmergesort.h"
#include "asserts.h"

//#pragma GCC diagnostic ignored "-Wpointer-arith"

/// One merge iteration into source
/// @param [in] source Source array
/// @param [out] target Target array
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
    pointerAssert (buffer,      nullptr);
    pointerAssert (comparator,  nullptr);
    decimalAssert (elementSize, 0);

    LOG_LINE;

    if (size < 2)
        return;

    void *temp = calloc(size, elementSize);

    if (temp == nullptr)
        return;

    void *source = buffer,
         *target = temp;

    LOG_LINE;

    while (mergeIteration(source, target, size, elementSize, comparator) != 0)
    {
        void *buff = source;

        source = target;
        target = buff;
    }

    LOG_LINE;

    if (source != buffer)
        memcpy(buffer, temp, size*elementSize);

    free(temp);
}

static unsigned mergeIteration(void *source, void *target, size_t size, size_t elementSize,
                               int (*comparator)(const void *, const void *))
{
    pointerAssert (source,      nullptr);
    pointerAssert (target,      nullptr);
    pointerAssert (comparator,  nullptr);
    decimalAssert (elementSize, 0);

    char *first  = (char *)source,
         *second = (char *)source;

    size_t firstSize  = 0,
           secondSize = 0;

    char *end = (char *)source + size*elementSize;

    unsigned mergeCount = 0;

    LOG_LINE;

    while (first < end)
    {
        first = second + secondSize*elementSize;

        for (firstSize = 0; first + firstSize*elementSize < end; ++firstSize)
        {
            if (firstSize == 0)
                continue;

            if (comparator(first + (firstSize - 1)*elementSize,
                           first +  firstSize     *elementSize) > 0)
                break;
        }

        if (first + firstSize*elementSize == end)
        {
            merge(first, second, target, firstSize, 0, elementSize, comparator);

            return mergeCount;
        }

        LOG_LINE;

        second = first + firstSize*elementSize;

        for (secondSize = 0; second + secondSize*elementSize < end; ++secondSize)
        {
            if (secondSize == 0)
                continue;

            if (comparator(second + (secondSize - 1)*elementSize,
                           second +  secondSize     *elementSize) > 0)
                break;
        }

        merge(first, second, target, firstSize, secondSize, elementSize, comparator);

        ++mergeCount;

        target = (char *)target + (firstSize + secondSize)*elementSize;
    }

    return mergeCount;
}

static void merge(void  *firstSubArray, void  *secondSubArray, void *targetArray,
                  size_t firstSize    , size_t secondSize    , size_t elementSize,
                  int (*comparator)(const void *, const void *))
{
    pointerAssert(firstSubArray,  nullptr);
    pointerAssert(secondSubArray, nullptr);
    pointerAssert(targetArray,    nullptr);
    pointerAssert(comparator,     nullptr);
    decimalAssert(elementSize,    0);

    LOG_LINE;

    size_t i = 0, j = 0;

    size_t currentIndex = 0;

    void *temp = nullptr;

    while (currentIndex < firstSize + secondSize)
    {
        if      (i == firstSize)
            temp = ((char *)secondSubArray + (j++)*elementSize);
        else if (j == secondSize)
            temp = ((char *)firstSubArray  + (i++)*elementSize);
        else if (comparator(((char *)firstSubArray + i*elementSize), ((char *)secondSubArray + j*elementSize)) < 0)
            temp = ((char *)firstSubArray  + (i++)*elementSize);
        else
            temp = ((char *)secondSubArray + (j++)*elementSize);

        LOG_LINE;

        memcpy(((char *)targetArray + (currentIndex++)*elementSize), temp, elementSize);
    }
}
