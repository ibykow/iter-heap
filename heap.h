/*
 * heap.h
 * Generic heap implementation
 * @Ilia Bykow, 2015 | ibykow@gmail.com
 *
 * To create an empty heap structure, use heap_new.
 * heap_insert/heap_remove inserts and removes items into a heap structure
 * respectively.
 *
 * To heapify an existing array, use heap_build_new.
 *
 * To free structures created with heap_build new or heap_new, use heap_destroy.
 *
 * To insert/remove into an array which you know is a heap use
 * heap_insert_v / heap_remove_v respectively.
 *
 * To build a heap out of an existing array without creating a heap structure
 * use heap_build_v
 */

#ifndef HEAP_H
#define HEAP_H

#define heap_def_cmp_f(type) \
    static inline type heap_##type##_min_cmp(const void *a, const void *b) { \
        return *(const type *) a - *(const type *) b; } \
    static inline type heap_##type##_max_cmp(const void *a, const void *b) { \
        return *(const type *) b - *(const type *) a; }

heap_def_cmp_f(int)

#define heap_insert(h, e) ((h && (h->len < h->max)) \
    ? heap_insert_v(h->arr, &h->len, e, h->size, h->cmp) : 0)

#define heap_remove(h, d) ((h && h->len) \
    ? heap_remove_v((h)->arr, &((h)->len), (d), (h)->size, (h)->cmp) : 0)

#define heap_build(h) (h ? heap_build_v(h->arr, h->len, h->size, h->cmp) : 0)

typedef int (*heap_cmp_f)(const void *, const void *);

struct heap_s {
    void *arr;
    size_t len, size, max;
    heap_cmp_f cmp;
};

void heap_init(struct heap_s *heap, void *arr, size_t len, size_t size,
    heap_cmp_f cmp);

struct heap_s *heap_new(size_t len, size_t size, heap_cmp_f cmp);

void heap_destroy(struct heap_s *heap);

struct heap_s *heap_new_from(void *arr, size_t len, size_t size,
    heap_cmp_f cmp);

struct heap_s *heap_build_new(void *arr, size_t len, size_t size,
    heap_cmp_f cmp);

size_t heap_insert_v(void *arr, size_t *len, void *e, size_t size,
    heap_cmp_f cmp);

size_t heap_remove_v(void *arr, size_t *len, void *dest, size_t size,
    heap_cmp_f cmp);

size_t heap_build_v(void *arr, size_t len, size_t size, heap_cmp_f cmp);

size_t heap_sort(void *arr, size_t len, size_t size, heap_cmp_f cmp);

#endif /* end of include guard: HEAP_H */
