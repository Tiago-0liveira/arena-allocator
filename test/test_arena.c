#include <arena.h>
#include <string.h>
#include <stdio.h>

int main() {
    // Initialize the arena with an initial capacity of 1 MB and the ARENA_GROWABLE flag
    Arena *arena = arena_create_flags(3 KB, ARENA_ASSERT_OVERFLOW | ARENA_ZEROED);

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