/**
 * @file:      container.c
 *
 * @date:      10 December 2023
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2023 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#include "../include/container.h"
#include <stdio.h>
#include <stdlib.h>

#define CONTAINER_INITIAL_CAPACITY 16

struct container_s
{
    void **entries;
    uint16_t capacity;
    uint16_t entry_type_size;
    uint16_t number_of_entries;
};

container_s *container_create(const uint16_t entry_type_size)
{
    container_s *container = calloc(1, sizeof(*container));

    container->capacity = CONTAINER_INITIAL_CAPACITY;
    container->entry_type_size = entry_type_size;
    container->number_of_entries = 0;
    container->entries = calloc(container->capacity, sizeof(void *));

    return container;
}

void container_destroy(container_s *const container)
{
    free(container->entries);
    free(container);
}

uint8_t container_add(container_s *const container, void *entry)
{
    if (container->number_of_entries == container->capacity)
    {
        uint16_t capacity = container->capacity * 2;
        void **entries = realloc(container->entries, capacity * sizeof(void *));

        // Failed to reallocate space for the container"
        if (!entries)
        {
            return 0;
        }

        container->capacity = capacity;
        container->entries = entries;
    }

    container->entries[container->number_of_entries] = entry;
    ++container->number_of_entries;

    return 1;
}

uint8_t container_remove_entry(container_s *const container, const void *entry)
{
    const int16_t entry_index = container_get_index_of_entry(container, entry);

    // Container does not contain the requested entry
    if (entry_index == -1)
    {
        return 0;
    }

    container_remove_entry_at_index(container, entry_index);

    return 1;
}

uint8_t container_remove_entry_at_index(container_s *const container, const uint16_t index)
{
    // Container index out of bounds
    if (index >= container->number_of_entries)
    {
        return 0;
    }

    for (uint16_t i = index; i < container->number_of_entries - 1; i++)
    {
        container->entries[i] = container->entries[i + 1];
    }

    container->entries[container->number_of_entries - 1] = NULL;

    --container->number_of_entries;

    return 1;
}

void *container_get_entry_at_index(const container_s *const container, const uint16_t index)
{
    // Container index out of bounds
    if (index >= container->number_of_entries)
    {
        return NULL;
    }

    return container->entries[index];
}

int16_t container_get_index_of_entry(const container_s *const container, const void *entry)
{
    for (uint16_t i = 0; i < container->number_of_entries; i++)
    {
        if (container->entries[i] == entry)
        {
            return i;
        }
    }

    // Container does not contain the requested entry
    return -1;
}

uint16_t container_get_entry_type_size(const container_s *const container)
{
    return container->entry_type_size;
}

uint16_t container_get_number_of_entries(const container_s *const container)
{
    return container->number_of_entries;
}
