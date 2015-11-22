# Heap
Generic heap implementation

To run tests:

    $ ./run

### Using a heap structure
To create a new heap data structure for ```n``` elements of size ```s```:

    struct heap_s *my_heap = heap_new(n, s, compare_func);

Once a heap has been created, insert / remove elements using ```heap_insert``` and ```heap_remove```:

    heap_insert(my_heap, some_element);
    heap_remove(my_heap, place_to_copy_removed_element);

To create a new heap from an existing, un-heapified array:

    struct heap_s *my_heap = heap_build_new(unheapified_array, len, size,
        compare_function);

Destroy a heap structure created using heap_new or heap_build_new using ```heap_destroy(h)``` where h is a pointer to your heap structure.

### Without a heap structure

To build a heap from an existing array, without creating a heap structure around it, use:

    heap_build_v(array_to_heapify, num_elements, size, compare_func);

The use ```heap_insert_v``` and ```heap_remove_v``` to insert and remove elements from a heapified array.

### Sorting

    heap_sort(array, length, size, compare_function);

### Example

##### ```int``` min heap

The following code inserts the numbers 5, 3, 1, 4, and 2 into a heap and then removes them one at a time and prints them out (in order). It is an inefficient method of sorting a list of integers.

The functions ```heap_int_min_cmp``` and ```heap_int_max_cmp``` are provided by heap.h

    #define HEAP_LENGTH 5

    int main(int argc, char const *argv[]) {

        struct heap_s *my_heap =
            heap_new(HEAP_LENGTH, sizeof(int), heap_int_min_cmp);

        int i, n;

        if (!my_heap)
            return -1;

        heap_insert(my_heap, (int *) {5}); // insert the number 5
        heap_insert(my_heap, (int *) {3});
        heap_insert(my_heap, (int *) {1});
        heap_insert(my_heap, (int *) {4});
        heap_insert(my_heap, (int *) {2});

        for (i = 0; i < HEAP_LENGTH; i++) {
            heap_remove(my_heap, &n);
            printf("%d: %d\n", i, n);
            if (n != (i + 1)) {
                printf("Heap error!\n");
                return -1;
            }
        }

        return 0;
    }

##### Sorting

Efficiently heap-sorts an array of integers in descending order.

    int main(int argc, char const *argv[]) {
        int arr[] = { 8, 2, 12, 25, 5, 4, 3, 1 };

        size_t size = sizeof(int), len = sizeof(arr) / size, i;

        printf("Sorting array\n");
        heap_sort(arr, len, size, heap_int_max_cmp);

        for (i = 0; i < len; i++)
            printf("%lu: %d\n", i, arr[i]);

        return 0;
    }
