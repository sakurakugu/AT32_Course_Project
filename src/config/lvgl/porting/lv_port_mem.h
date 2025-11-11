/**
 * Lightweight LVGL memory adapter using FreeRTOS heap.
 * Implements malloc/free/realloc wrappers with size header for safe copying.
 */
#ifndef LV_PORT_MEM_H
#define LV_PORT_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>
#include "FreeRTOS.h"

/*
 * Allocation layout:
 * [ size_t stored_size ][ user bytes ... ]
 * This lets realloc copy min(old_size, new_size) safely.
 */
static inline void * lv_port_malloc(size_t size)
{
    if(size == 0) {
        /* LVGL will handle zero-size separately; still allocate 1 byte to keep pointer distinct */
        size = 1;
    }

    size_t total = sizeof(size_t) + size;
    void * raw = pvPortMalloc(total);
    if(raw == NULL) return NULL;

    /* store size at header */
    size_t * hdr = (size_t *)raw;
    *hdr = size;

    /* return user pointer */
    return (void *)(hdr + 1);
}

static inline void lv_port_free(void * ptr)
{
    if(ptr == NULL) return;
    /* move back to header and free */
    size_t * hdr = ((size_t *)ptr) - 1;
    vPortFree((void *)hdr);
}

static inline void * lv_port_realloc(void * ptr, size_t new_size)
{
    if(ptr == NULL) {
        return lv_port_malloc(new_size);
    }

    if(new_size == 0) {
        /* Free and signal failure; lv_mem_realloc() handles zero size separately */
        lv_port_free(ptr);
        return NULL;
    }

    /* read old size from header */
    size_t * old_hdr = ((size_t *)ptr) - 1;
    size_t old_size = *old_hdr;

    void * new_user = lv_port_malloc(new_size);
    if(new_user == NULL) {
        return NULL;
    }

    /* copy min(old_size, new_size) */
    size_t copy_sz = old_size < new_size ? old_size : new_size;
    memcpy(new_user, ptr, copy_sz);

    /* free old block */
    lv_port_free(ptr);

    return new_user;
}

#ifdef __cplusplus
}
#endif

#endif /* LV_PORT_MEM_H */