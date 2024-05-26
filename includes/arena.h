#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include <assert_msg.h>

#define KB * 1024
#define MB * 1024 KB
#define GB * 1024 MB
#define TB * 1024 GB

// Error Messages
#define ARENA_OVERFLOW_MSG	"Arena overflow! Try making the arena size bigger! Or use the flag ARENA_GROWABLE."

// Arena flags

// If not set the arena returns null pointer on the allocation
#define ARENA_ASSERT_OVERFLOW	0x01
// Grows the arena by 2x if the requested size is larger than the current capacity
#define ARENA_GROWABLE			0x02
// If set the arena will print a debug message when growing the arena
#define ARENA_GROWABLE_DEBUG	0x04
// If set the arena will be zeroed out on creation
#define ARENA_ZEROED			0x08
// If set the arena will be freed on allocation failure
#define ARENA_FREE_ON_FAIL		0x10

#define ARENA_DEFAULT_FLAGS		ARENA_ASSERT_OVERFLOW | ARENA_FREE_ON_FAIL
#define ARENA_ALL_FLAGS			0x0F

typedef struct {
	size_t	capacity;
	size_t	size;
	size_t	flags;
	void	*data;
} Arena;


Arena	*arena_create(size_t capacity);
Arena	*arena_create_flags(size_t capacity, size_t flags);
void	arena_free(Arena *arena);
void	*arena_alloc(Arena *arena, size_t size);
bool	check_flag(Arena *arena, size_t flag);
