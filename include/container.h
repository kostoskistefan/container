/**
 * @file:      container.h
 *
 * @date:      10 December 2023
 *
 * @author:    Kostoski Stefan
 *
 * @copyright: Copyright (c) 2023 Kostoski Stefan.
 *             This work is licensed under the terms of the MIT license.
 *             For a copy, see <https://opensource.org/license/MIT>.
 */

#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>

typedef struct container_s container_s;

container_s *container_create(const uint16_t entry_type_size);
void container_destroy(container_s *const container);

uint8_t container_add(container_s *const container, void *entry);
uint8_t container_remove_entry(container_s *const container, const void *entry);
uint8_t container_remove_entry_at_index(container_s *const container, const uint16_t index);
void *container_get_entry_at_index(const container_s *const container, const uint16_t index);
int16_t container_get_index_of_entry(const container_s *const container, const void *entry);
uint16_t container_get_entry_type_size(const container_s *const container);
uint16_t container_get_number_of_entries(const container_s *const container);

#endif // CONTAINER_H
