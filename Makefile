# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: izelensk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 12:17:24 by izelensk          #+#    #+#              #
#    Updated: 2016/11/07 13:20:08 by izelensk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS =  w_data_init.c w_tools.c w_hooks.c w_loop_end.c w_loop_mid.c w_main.c w_loop_start.c get_next_line.c convert_xpm_hex.c

OBJS = w_data_init.o w_tools.o w_hooks.o w_loop_end.o w_loop_mid.o w_main.o w_loop_start.o get_next_line.o convert_xpm_hex.o

HEADER = wolf3d.h get_next_line.h convert_xpm_hex.h

mlgcc = gcc -lmlx -framework OpenGL -framework AppKit

JUNK = $(wildcard .DS_Store */.DS_Store */*/.DS_Store *.gch \
		  get_next_line/*.gch )

all:$(NAME)

$(NAME): $(OBJS)
	@make -C libft/
	@gcc -c -Wall -Wextra -Werror $(HEADER) $(SRCS)
	@$(mlgcc) -o $(NAME) $(OBJS) libft/libft.a
	@rm -rf $(JUNK)
	@echo "compiled"

clean:
	@rm -rf $(OBJS)
	@rm -f wolf3d.h.gch get_next_line.h.gch convert_xpm_hex.h.gch
	@echo "cleaned"

fclean: clean
	@rm -rf $(NAME)
	@echo "fcleaned"

libclean: fclean
	@make fclean -C libft/
	@echo "libcleaned"

re: fclean all
