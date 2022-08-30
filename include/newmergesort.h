#ifndef NEWMERGESORT_H_
#define NEWMERGESORT_H_

/// Sort collection using merge sort algorithm
/// @param [in/out] buffer Collection who needing sort
/// @param [in] size Size of collection
/// @param [in] elementSize Size of one element in collection
/// @param [in] comparator Function pointer to comparator for elements in collection
void newMergeSort(void *buffer, size_t size, size_t elementSize, int (*comparator)(const void *, const void *));

#endif
