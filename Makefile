NAME	= ft_nm

CC = gcc

#-----------------#
##### INCLUDE #####
#-----------------#

INCLUDES = includes

CPPFLAGS = -Wall -Werror -Wextra
CPPFLAGS += -I $(INCLUDES)

#---------------#
##### LIBFT #####
#---------------#

LIBFT_PATH	+= libft
LIBFT_NAME	+= libft.a

CPPFLAGS	+= -I $(LIBFT_PATH)/includes
LDFLAGS		+= -L $(LIBFT_PATH)
LDLIBS		+= -lft

#-------------------#
##### MANDATORY #####
#-------------------#

#SRC_DIR	= src/mandatory
SRC_DIR	= src
OBJ_DIR = objs

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.d))

#-----------------#
###### BONUS ######
#-----------------#

#BONUS_DIR = src/bonus

#SRC_BONUS = $(shell find $(BONUS_DIR) -type f -name "*.c")
#OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.o))
#DEPS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.d))




all			: $(NAME)

$(NAME)		: $(LIBFT_PATH)/$(LIBFT_NAME) $(OBJS)
		$(CC) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $(NAME)

#.bonus:	$(NAME) $(OBJS_BONUS)
#		ar rcs $(NAME) $(OBJS_BONUS)
#		@touch .bonus

#bonus: .bonus

$(OBJ_DIR)/%.o	: %.c
	@mkdir -p `dirname $@`
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

#@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi

$(OBJ_DIR):
	echo $@
	echo "-----"

clean			:
	rm -rf $(OBJ_DIR)

fclean			: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re				: fclean all

$(LIBFT_PATH)/$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH) bonus

#define F
#	@echo ====== TEST $(1) ======
#	@gcc -I includes libft.a $(1)
#	@./a.out
#
#endef
#
#xs := $(shell find main -type f -name "*.c")
#
#test			: all
#	$(foreach x,$(xs),$(call F, $(x)))

run: $(NAME)
	./$(NAME) ./parse_files/ELF/hello

.PHONY:	all clean fclean all
