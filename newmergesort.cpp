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
static int mergeIteration(void *source, void *target, size_t size, size_t elementSize,
                          int (*comparator)(const void *, const void *));            ///Rework

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

    if (size < 2)
        return;

    void *temp = calloc(size, elementSize);

    if (temp == nullptr)
        return;

    void *source = buffer,
         *target = temp;

    {
        void *last    = buffer + (size - 1)*elementSize,
             *prelast = buffer + (size - 2)*elementSize;

        if (size % 2 == 1 && comparator(prelast, last) > 0)
        {
            void *buff = calloc(1, elementSize);

            memcpy(buff   , prelast, elementSize);
            memcpy(prelast, last   , elementSize);
            memcpy(last   , buff   , elementSize);

            free(buff);
        }
    }

    for (size_t i = 0, iter = 1; i < iterCount; ++i, iter *= 2)
    {
        if (iter > size / 2)
            iter = size / 2;

        mergeIteration(source, target, iter, size, elementSize, comparator);

        void *buff = source;

        source = target;
        target = buff;
    }

    memcpy(buffer, temp, size*elementSize);

    free(temp);
}

static void mergeIteration(void *source, void *target, size_t subSize, size_t size, size_t elementSize,
                           int (*comparator)(const void *, const void *))
{
    assert(source     != nullptr);
    assert(target     != nullptr);
    assert(comparator != nullptr);

    assert(elementSize > 0);

    void *first  = source,
         *second = source    + ((size / subSize) / 2)*elementSize;

    void *firstEnd  = source + ((size / subSize) / 2)*elementSize;

    while (first < firstEnd)
    {
        size_t firstSize  = subSize,
               secondSize = subSize + (((size % 2 == 1) && (first + subSize*elementSize == firstEnd)) ? 1 : 0);

        merge(first, second, target, firstSize, secondSize, elementSize, comparator);

        first  +=  subSize*elementSize;
        second +=  subSize*elementSize;

        target += 2*subSize*elementSize;
    }


}

static void merge(void  *firstSubArray, void  *secondSubArray, void *targetArray,
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
