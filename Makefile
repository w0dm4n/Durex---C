# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/10/17 05:57:05 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_DUREX	=	Durex

NAME		=   Durex
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc -lpthread
FLAGS_O		=

SRCDIR_DUREX		=	srcs/
OBJDIR_DUREX		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_DUREX	=	\
					main.c							\
					durex.c							\
					env.c							\
					utils.c							\
					infection.c						\
					daemon.c						\
					server.c						\
					client.c						\
					authentication.c				\
					password.c						\
					service.c						\
					library.c						\
					entry.c							\
					shell.c							\
					chdir.c
INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_DUREX			=	$(addprefix $(SRCDIR_DUREX), $(SRCBASE_DUREX))
OBJS_DUREX			=	$(addprefix $(OBJDIR_DUREX), $(SRCBASE_DUREX:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_DUREX) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make re -C libft/ &&														\
		make DUREX && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_DUREX):
	mkdir -p $(OBJDIR_DUREX)
	mkdir -p $(dir $(OBJS_DUREX))

$(OBJDIR_DUREX)%.o : $(SRCDIR_DUREX)%.c | $(OBJDIR_DUREX)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

DUREX: $(OBJDIR_DUREX) $(OBJS_DUREX)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_DUREX) $(OBJS_DUREX) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_DUREX)"

clean:
	@rm -rf $(OBJDIR_DUREX)
	@make -C $(LIBFT_DIR) clean
	echo "\r\033[38;5;124m📕  CLEAN $(OBJDIR_DUREX)\033[0m\033[K";

fclean:		clean
	@rm -rf $(NAME_DUREX)
	@make -C $(LIBFT_DIR) fclean
	echo "\r\033[38;5;124m📕  FCLEAN $(NAME_DUREX)\033[0m\033[K";

-include $(OBJS:.o=.d)
