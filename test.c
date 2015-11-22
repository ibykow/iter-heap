#include "debug.h"
#include "heap.h"

#define HEAP_LEN 5

static void test_heap_insert_remove_v()
{
    int heap[HEAP_LEN], prev = 0, n;
    size_t size = sizeof(int), len = 0, i, res;

    heap_insert_v(heap, &len, &(int) {30}, size, heap_int_min_cmp);
    heap_insert_v(heap, &len, &(int) {10}, size, heap_int_min_cmp);
    heap_insert_v(heap, &len, &(int) {55}, size, heap_int_min_cmp);
    heap_insert_v(heap, &len, &(int) {56}, size, heap_int_min_cmp);
    heap_insert_v(heap, &len, &(int) {4}, size, heap_int_min_cmp);

    for (i = 0; i < HEAP_LEN; i++) {
        res = heap_remove_v(heap, &len, &n, size, heap_int_min_cmp);
        TEST_Q(res == (HEAP_LEN - i - 1));
        TEST_Q(n > prev);
        prev = n;
    }
}

static void test_heap_build_v()
{
    int heap[HEAP_LEN] = { 5, 4, 3, 2, 1};

    int n, i;
    size_t len = HEAP_LEN, res;

    heap_build_v(heap, HEAP_LEN, sizeof(int), heap_int_min_cmp);

    for (i = 0; i < HEAP_LEN; i++) {
        res = heap_remove_v(heap, &len, &n, sizeof(int), heap_int_min_cmp);
        TEST_Q(res == (HEAP_LEN - (size_t) i - 1));

        TEST_Q((i + 1) == n);
    }
}

static void test_heap_new()
{
    struct heap_s *h = heap_new(HEAP_LEN, sizeof(int), heap_int_min_cmp);

    TEST_Q(h);
    TEST_Q(h->len == 0);
    TEST_Q(h->size == sizeof(int));
    TEST_Q(h->arr);
    TEST_Q(h->cmp == heap_int_min_cmp);

    heap_destroy(h);
}

static void test_heap_sort()
{
    int arr[] = { 8, 2, 12, 25, 5, 4, 3, 1 }, n = 0;

    size_t size = sizeof(int), len = sizeof(arr) / size, i;

    TEST_Q(heap_sort(arr, len, size, heap_int_min_cmp) == len);

    for (i = 0; i < len; i++) {
        TEST_Q(n < arr[i]);
        n = arr[i];
    }
}

static void test_heap_sort_max()
{
    int arr[] = { 8, 2, 12, 25, 5, 4, 3, 1 }, n = 100;

    size_t size = sizeof(int), len = sizeof(arr) / size, i;

    heap_sort(arr, len, size, heap_int_max_cmp);

    for (i = 0; i < len; i++) {
        TEST_Q(n > arr[i]);
        n = arr[i];
    }
}

static void test_max_heap()
{
    int arr[] = { 8, 2, 12, 25, 5, 4, 3, 1 }, prev = 100, n = 0;

    size_t size = sizeof(int), len = sizeof(arr) / size, i;
    struct heap_s *h = heap_new(len, size, heap_int_max_cmp);

    for (i = 0; i < len; i++)
        TEST_Q(heap_insert(h, arr + i) == (i + 1));

    for (i = 0; i < len; i++) {
        heap_remove(h, &n);
        TEST_Q(n < prev);
        prev = n;
    }

    heap_destroy(h);
}

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    INFO("Testing insert/remove_v");
    test_heap_insert_remove_v();
    TEST_SUMMARY();
    INFO("Testing heap_build_v");
    test_heap_build_v();
    TEST_SUMMARY();
    INFO("Testing heap_new");
    test_heap_new();
    TEST_SUMMARY();
    INFO("Testing heap_sort");
    test_heap_sort();
    TEST_SUMMARY();
    INFO("Testing heap_sort_max");
    test_heap_sort_max();
    TEST_SUMMARY();
    INFO("Testing heap_max_heap");
    test_max_heap();
    TEST_SUMMARY();


    return 0;
}
