#include <arena.h>

Arena	*arena_create(size_t capacity)
{
	return arena_create_flags(capacity, ARENA_DEFAULT_FLAGS);
}

Arena	*arena_create_flags(size_t capacity, size_t flags)
{
	Arena *arena = malloc(sizeof(Arena));
	if (!arena)
		return NULL;
	arena->capacity = capacity;
	arena->size = 0;
	arena->flags = flags;
	arena->_next = NULL;
	arena->data = malloc(capacity);
	if (!arena->data)
	{
		free(arena);
		return NULL;
	}
	if (flags & ARENA_ZEROED)
		memset(arena->data, 0, capacity);
	return arena;
}

void	arena_free(Arena *arena)
{
	Arena *next;
	while (arena)
	{
		next = arena->_next;
		if (arena->data)
			free(arena->data);
		free(arena);
		arena = next;
	}
}

void *arena_alloc(Arena *arena, size_t size)
{
    if (check_flag(arena, ARENA_ASSERT_OVERFLOW) && !check_flag(arena, ARENA_GROWABLE))
        assert_msg_clean(arena->size + size <= arena->capacity, ARENA_OVERFLOW_MSG, arena_free(arena));

    if (arena->size + size <= arena->capacity)
    {
        void *ptr = arena->data + arena->size;
        arena->size += size;
        return ptr;
    }

    if (!check_flag(arena, ARENA_GROWABLE))
    {
        if (check_flag(arena, ARENA_FREE_ON_FAIL))
            arena_free(arena);
        return NULL;
    }

    size_t new_capacity = arena->capacity;
    while (arena->size + size > new_capacity)
        new_capacity *= 2;

    Arena *new_arena = arena_create_flags(new_capacity, arena->flags);
    if (!new_arena)
    {
        if (check_flag(arena, ARENA_FREE_ON_FAIL))
            arena_free(arena);
        return NULL;
    }

    arena->_next = new_arena;
    if (check_flag(arena, ARENA_ZEROED))
        memset(new_arena->data, 0, new_arena->capacity);
    if (check_flag(arena, ARENA_GROWABLE_DEBUG))
        printf("Arena grown to %zu bytes\n", new_arena->capacity);

    return arena_alloc(new_arena, size);
}


bool	check_flag(Arena *arena, size_t flag)
{
	return arena->flags & flag;
}
