#pragma once

#include <stdio.h>
#include <stdlib.h>

#define assert_msg(expr, msg) assert_msg_clean(expr, msg, {})

#define assert_msg_clean(expr, msg, cleanup) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: (%s), file %s, line %d: %s\n", #expr, __FILE__, __LINE__, msg); \
            cleanup; \
            exit(EXIT_FAILURE); \
        } \
    } while (0)


