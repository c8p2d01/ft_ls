# Output Name:
NAME:=		ft_ls

# Folders
BUILD:=		./build
SOURCE:=	./src

# Other variables:
COMPILER:=	cc
COMPFLAGS:=	-Wall -Werror -Wextra -g
LIB:=ft_libft/

# Source Files:
SRCFILES =	\
			ft_init_ls.c \
			ft_ls.c \

# Process Variables
CC:=		$(COMPILER)
CFLAGS:=	$(COMPFLAGS)
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.c=$(BUILD)/%.o)
NAME:=		./$(NAME)
OS:=		$(shell uname -s)

.PHONY: all clean fclean re

all: requirements
	make -C $(LIB)
	make -j $(nproc) $(NAME)

requirements:
	@if [ ! -f $(LIB)Makefile ]; then \
		git submodule update --init --recursive ; \
	fi

$(OBJS): $(BUILD)%.o : $(SOURCE)%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIB)libft.a -o $@

clean:
	make clean -C $(LIB)
	$(RM) -r $(BUILD)

fclean:
	make fclean -C $(LIB)
	$(RM) -r $(BUILD)
	$(RM) -r $(NAME)

re: fclean all

bonus: all
