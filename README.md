# Arena Allocator

The Arena Allocator is a memory management library that simplifies dynamic memory allocation by using a single large block of memory (arena). This allocator supports various flags to enhance functionality, such as automatic resizing, to eliminate manual memory management burdens.

## Features

- No need to check for `NULL` pointers after memory allocation (if using the right flags).
- Simplified memory allocation within a single contiguous block.
- Automatic resizing with the `ARENA_GROWABLE` flag.
- Customizable behavior through various flags.
- Efficient and fast memory allocations without frequent calls to `malloc` and `free`.

## Flags

### `ARENA_GROWABLE`

- **Description**: When the `ARENA_GROWABLE` flag is set, the arena will automatically grow to 2x its current capacity if a requested allocation exceeds the current capacity.
- **Use Case**: This flag allows for dynamic memory allocation without the need to manually check and handle memory reallocation, making the code cleaner and safer.

### `ARENA_GROWABLE_DEBUG`

- **Description**: When this flag is set, the arena will print debug information when it grows.

### `ARENA_ZEROED`

- **Description**: When this flag is set, the memory allocated from the arena will be zero-initialized.
- **Use Case**: This is useful for ensuring that all allocated memory is initialized to zero, which can help prevent bugs related to uninitialized memory.

### `ARENA_ASSERT_OVERFLOW`

- **Description**: When this flag is set, the arena will assert if the allocation size exceeds the maximum capacity.
- **Use Case**: This can help catch potential buffer overflow issues during memory allocation and tells you to allocate more memory!.

### `ARENA_FREE_ON_FAIL`

- **Description**: When this flag is set, the arena will automatically free all memory and destroy itself if an allocation fails.


## Usage Examples

### Initialization

```c
#include <string.h>
#include <stdio.h>
#include <arena.h>

int main() {
    // Initialize the arena with an initial capacity of 1 MB and the ARENA_GROWABLE flag
    Arena *arena = arena_create_flags(3 KB, ARENA_GROWABLE | ARENA_GROWABLE_DEBUG | ARENA_ZEROED);

    // Allocation examples
    int *numbers = arena_alloc(arena, 1000 * sizeof(int));
    char *buffer = arena_alloc(arena, 256);

    // Use the allocated memory
    for (int i = 0; i < 1000; i++) {
        numbers[i] = i;
    }
	strcpy(buffer, "Hello, World!");
	printf("Buffer: %s\n", buffer);
    // Free the arena when done
    arena_free(arena);
    return 0;
}
```

> Output
```bash
$ > ./example
 Arena grown to 6144 bytes
 Buffer: Hello, World!
```