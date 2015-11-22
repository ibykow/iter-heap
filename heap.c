#include "debug.h"
#include "heap.h"

#define HEAP_PARENT(i) ((i - 1) >> 1)
#define HEAP_LAST_PARENT(len) (len > 1 ? HEAP_PARENT(len - 1) : 0)
#define HEAP_LEFT(i) ((i << 1) + 1)
#define HEAP_AT(h, s, i) ((char *) h + ((i) * size))

#define heap_sift_down(arr, len, e, size, cmp) \
    heap_sift_down_from(arr, len, e, size, cmp, 0)

/*
 * heap_sift_down_from
 *
 * Sifts the element 'e' down the 'heap' starting from index 'i'.
 *
 * Warning:
 * This function discards data at 'heap' index 'i'.
 */
static size_t heap_sift_down_from(void *arr, size_t len, void *e, size_t size,
    heap_cmp_f cmp, size_t i)
{
    if (!arr || !len || !e || !size || !cmp)
        return 0;

    if (len == 1) {
        memcpy(arr, e, size);
        return 1;
    }

    size_t next_i, last_parent = HEAP_LAST_PARENT(len);

    while (i < last_parent) {
        next_i = HEAP_LEFT(i);
        if (cmp(HEAP_AT(arr, size, next_i + 1),
            HEAP_AT(arr, size, next_i)) < 0) {
            next_i++;
        }

        if (cmp(e, HEAP_AT(arr, size, next_i)) < 0)
            break;

        memmove(HEAP_AT(arr, size, i), HEAP_AT(arr, size, next_i), size);

        i = next_i;
    }

    if (i == last_parent) {
        next_i = HEAP_LEFT(i);
        if ((len % 2) && cmp(HEAP_AT(arr, size, next_i + 1),
            HEAP_AT(arr, size, next_i)) < 0) {
            next_i++;
        }

        if (cmp(e, HEAP_AT(arr, size, next_i)) > 0) {
            memmove(HEAP_AT(arr, size, i), HEAP_AT(arr, size, next_i), size);
            i = next_i;
        }
    }

    memcpy(HEAP_AT(arr, size, i), e, size);

    return len;
}

void heap_init(struct heap_s *heap, void *arr, size_t len, size_t size,
    heap_cmp_f cmp)
{
    heap->arr = arr;
    heap->len = 0;
    heap->size = size;
    heap->max = len;
    heap->cmp = cmp;
}

struct heap_s *heap_new(size_t len, size_t size, heap_cmp_f cmp)
{
    struct heap_s *h = malloc(sizeof(*h));

    if (!h)
        return 0;

    h->arr = malloc(len * size);

    if (!h->arr) {
        free(h);
        return 0;
    }

    heap_init(h, h->arr, len, size, cmp);

    return h;
}

void heap_destroy(struct heap_s *heap)
{
    if (!heap)
        return;

    free(heap->arr);
    free(heap);
}

struct heap_s *heap_new_from(void *arr, size_t len, size_t size,
    heap_cmp_f cmp)
{
    struct heap_s *h = heap_new(len, size, cmp);
    if (!h)
        return 0;

    memcpy(h->arr, arr, len * size);
    h->len = len;

    return h;
}

struct heap_s *heap_build_new(void *arr, size_t len, size_t size,
    heap_cmp_f cmp)
{
    struct heap_s *h = heap_new_from(arr, len, size, cmp);

    if (!h)
        return 0;

    if (!heap_build(h)) {
        heap_destroy(h);
        h = 0;
    }

    return h;
}

size_t heap_insert_v(void *arr, size_t *len, void *e, size_t size,
    heap_cmp_f cmp)
{
    if (!arr || !e || !size || !cmp)
        return 0;

    size_t i = *len, parent_i = HEAP_PARENT(i);

    while(i && (cmp(e, HEAP_AT(arr, size, parent_i)) < 0)) {
        memmove(HEAP_AT(arr, size, i), HEAP_AT(arr, size, parent_i), size);
        i = parent_i;
        parent_i = HEAP_PARENT(i);
    }

    memcpy(HEAP_AT(arr, size, i), e, size);

    return ++(*len);
}

size_t heap_remove_v(void *arr, size_t *len, void *dest, size_t size,
    heap_cmp_f cmp)
{
    if (!arr || !len || !dest || !size || !cmp)
        return 0;

    (*len)--;

    memmove(dest, arr, size);
    heap_sift_down(arr, *len, HEAP_AT(arr, size, *len), size, cmp);

    return *len;
}

size_t heap_build_v(void *arr, size_t len, size_t size, heap_cmp_f cmp)
{
    if (!arr || !len || !size || !cmp)
        return 0;


    if (len < 2)
        return len;

    size_t i = HEAP_LAST_PARENT(len);
    char *e = malloc(size);

    if (!e)
        return 0;

    /* sift down all subtrees including the top-level */
    while (i + 1) {
        /* store the current root node */
        memmove(e, HEAP_AT(arr, size, i), size);

        heap_sift_down_from(arr, len, e, size, cmp, i);

        i--;
    }

    free(e);

    return len;
}

size_t heap_sort(void *arr, size_t len, size_t size,
    heap_cmp_f cmp)
{
    size_t i;

    struct heap_s *h = heap_build_new(arr, len, size, cmp);

    if (!h)
        return 0;

    for (i = 0; i < len; i++)
        heap_remove(h, HEAP_AT(arr, size, i));

    heap_destroy(h);

    return len;
}
