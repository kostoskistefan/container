# Container

Container is a simple dynamic array library written in C. It supports any data type as long as you provide its size.

## Supported operations

 * Add
 * Remove by index
 * Remove by entry pointer
 * Get entry by index
 * Get index of entry
 * Get number of entries in the container
 * Get the size of entries type in the container

## Example usage

```c
#include <container.h>
#include <stdio.h>
#include <string.h>

struct custom_type
{
    int number;
    char text[64];
};

void print_container_entries(const container_s *const container)
{
    printf("----------------------------------------------\n");

    for (int i = 0; i < container_get_number_of_entries(container); ++i)
    {
        struct custom_type *entry = (struct custom_type *) container_get_entry_at_index(container, i);
        printf("ENTRY %d: Number: %d, Text: %s\n", i, entry->number, entry->text);
    }

    printf("----------------------------------------------\n\n");
}

int main(void)
{
    container_s *container = container_create(sizeof(struct custom_type));
    
    struct custom_type entries[5];
    
    for (int i = 0; i < 5; ++i)
    {
        // Create a custom text for the particular entry
        char text_buffer[64];
        sprintf(text_buffer, "Hello from entry %d", 100 + i);

        // Initialize the entry
        entries[i].number = i;
        strncpy(entries[i].text, text_buffer, 64);
        
        // Add the entry into the container
        container_add(container, (void *) &entries[i]);
    }

    printf("Number of entries in container: %d\n", container_get_number_of_entries(container));
    printf("Size of each entry in container: %d\n\n", container_get_entry_type_size(container));
    
    print_container_entries(container);
    
    // Remove an entry by a pointer to the entry
    container_remove_entry(container, (void *) &entries[0]);
    print_container_entries(container);
    
    // Remove an entry by index
    container_remove_entry_at_index(container, 3);
    print_container_entries(container);

    // Find an existing entry by index
    struct custom_type *entry = container_get_entry_at_index(container, 0);

    if (entry != NULL)
    {
        printf("Entry at index 0: Number: %d, Text: %s\n\n", entry->number, entry->text);
    }

    // Find the index of an entry 
    const uint16_t index_of_entry = container_get_index_of_entry(container, (void *) entry); 
    printf("Index of the previously found entry: %d\n\n", index_of_entry);

    // Try to find a non-existant entry by index
    struct custom_type *non_existent_entry = container_get_entry_at_index(container, 10);

    if (non_existent_entry == NULL)
    {
        printf("Entry at index 10 does not exist!\n\n");
    }

    container_destroy(container);

    return 0; 
}
```

## Build

### Dependencies

 * C compiler (ex. GCC) 
 * Meson with Ninja

### Instructions

 1. Clone this repository: `git clone https://github.com/kostoskistefan/container.git`
 2. Navigate inside the cloned repository: `cd container`
 3. Let meson prepare the build directory: `meson setup build --prefix=/usr --libdir=/usr/lib`
 4. Compile the library: `meson compile -C build`
 5. (Optionally) Install the library to make it available system-wide: `meson install -C build`

If you choose to skip the last step, you will find the library inside a folder called `build` in the root directory of this project, which can then be linked to your application.
