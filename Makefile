NAME	= ft_nm

CC = gcc

#-----------------#
##### INCLUDE #####
#-----------------#

INCLUDES = includes

#SANITIZER = -g -fsanitize=address

CPPFLAGS = -Wall -Werror -Wextra $(SANITIZER)
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

$(OBJS)		: $(INCLUDES)/ft_nm.h

$(NAME)		: $(LIBFT_PATH)/$(LIBFT_NAME) $(OBJS)
		$(CC) $(SANITIZER) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

#.bonus:	$(NAME) $(OBJS_BONUS)
#		ar rcs $(NAME) $(OBJS_BONUS)
#		@touch .bonus

#bonus: .bonus

$(OBJ_DIR)/%.o	: %.c
	@mkdir -p `dirname $@`
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

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


#===== DOCKER =====#

CONTAINER_NAME=nm_container
IMAGE_NAME=nm:0.1

.PHONY: delete
delete:
	-@yes | docker rm $(CONTAINER_NAME)
	-@yes | docker rmi $(IMAGE_NAME)

.PHONY: build
build: $(NAME) delete
	docker build -t $(IMAGE_NAME) .
	docker run --name $(CONTAINER_NAME) -it $(IMAGE_NAME) /bin/bash

.PHONY: start
start:
	docker start -i $(CONTAINER_NAME)


.PHONY:	all clean fclean all re
