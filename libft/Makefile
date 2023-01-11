NAME	= libft.a

CC = gcc

#-----------------#
##### INCLUDE #####
#-----------------#

INCLUDES = includes

#-------------------#
##### MANDATORY #####
#-------------------#

SRC_DIR	= src/mandatory
OBJ_DIR = objs

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

#-----------------#
###### BONUS ######
#-----------------#

BONUS_DIR = src/bonus

SRC_BONUS = $(shell find $(BONUS_DIR) -type f -name "*.c")
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.o))
DEPS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.d))


CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I $(INCLUDES)

all			: $(NAME)

$(NAME)		: $(OBJS)
		ar rcs $(NAME) $(OBJS)

.bonus:	$(NAME) $(OBJS_BONUS)
		ar rcs $(NAME) $(OBJS_BONUS)
		@touch .bonus

bonus: .bonus

$(OBJ_DIR)/%.o	: %.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) -o $@ -c $<

clean			:
	rm -rf $(OBJ_DIR)

fclean			: clean
	rm -f $(NAME)

re				: fclean all

define F
	@echo ====== TEST $(1) ======
	@gcc -I includes libft.a $(1)
	@./a.out

endef

xs := $(shell find main -type f -name "*.c")

test			: all
	$(foreach x,$(xs),$(call F, $(x)))

.PHONY:	all clean fclean all
