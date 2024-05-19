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
	if (arena->data)
		free(arena->data);
	if (arena)
		free(arena);
}

void	*arena_alloc(Arena *arena, size_t size)
{
	if (check_flag(arena, ARENA_ASSERT_OVERFLOW) && !check_flag(arena, ARENA_GROWABLE))
		assert_msg_clean(arena->size + size <= arena->capacity, ARENA_OVERFLOW_MSG, arena_free(arena));
	if (arena->size + size > arena->capacity)
	{
		if (check_flag(arena, ARENA_GROWABLE))
		{
			while (arena->size + size > arena->capacity)
				arena->capacity *= 2;
			arena->data = realloc(arena->data, arena->capacity);
			if (!arena->data)
			{
				if (check_flag(arena, ARENA_FREE_ON_FAIL))
					arena_free(arena);
				return NULL;
			}
			if (check_flag(arena, ARENA_ZEROED))
				memset(arena->data + arena->size, 0, arena->capacity - arena->size);
			if (check_flag(arena, ARENA_GROWABLE_DEBUG))
				printf("Arena grown to %zu bytes\n", arena->capacity);
			return arena_alloc(arena, size);
		}
		return NULL;
	}
	void *ptr = arena->data + arena->size;
	arena->size += size;
	return ptr;
}


bool	check_flag(Arena *arena, size_t flag)
{
	return arena->flags & flag;
}
