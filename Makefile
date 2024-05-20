NAME = arena
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

includefolder = includes/
INCLUDES = -I $(includefolder)

SRC_FOLDER = src/
OBJ_DIR = obj/
LIB_DIR = lib/

SRC_ROOT_FILES = arena.c

INCLUDE_HEADERS = $(addprefix $(includefolder), \
	arena.h assert_msg.h \
)

FILES = \
	$(SRC_ROOT_FILES)

OBJS = $(addprefix $(OBJ_DIR), $(FILES:%.c=%.o))

LIB_FILE = $(LIB_DIR)lib$(NAME).a

# Reset
Color_Off='\033[0m'       # Text Reset

IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
ICyan='\033[0;96m'        # Cyan

MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}

all: $(LIB_FILE)

$(LIB_FILE): $(OBJS)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_FILE) $(OBJS)
	$(MSG1)

$(OBJ_DIR)%.o: $(SRC_FOLDER)%.c $(INCLUDE_HEADERS)
	@mkdir -p $(OBJ_DIR) $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

run_grind:
	@valgrind --leak-check=full --show-leak-kinds=all ./test/test_arena

link_test: $(LIB_FILE)
	@$(CC) $(CFLAGS) -o test/test_arena test/test_arena.c -L$(LIB_DIR) -l$(NAME)

test: link_test
	@./test/test_arena
test_grind: link_test run_grind

clean:
	@/bin/rm -rf $(OBJ_DIR)
	$(MSG2)

fclean: clean
	@/bin/rm -rf $(NAME) ${LIB_DIR} $(OBJ_DIR) test/test_arena
	$(MSG3)

re: fclean all
