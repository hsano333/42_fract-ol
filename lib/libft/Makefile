CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
INCLUDE := -I./include
NAME 	:= libft.a
LIBFT = ./libft
SRCDIR	:= ./srcs/
SRC		:= parse.c parse_utils.c ft_atoi_base.c print.c ft_strnbr_base.c print_digit.c print_str.c print_utils.c common.c
ENTRY	:= ft_printf.c
ENTRYBONUS	:= ft_printf_bonus.c
ifdef WITH_BONUS
ENTRY	:= $(ENTRYBONUS)
endif
SRC	+= $(ENTRY)

SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.c=.o)
OBJDIR	:= ./obj
LIBFTNAME := libft.a
LIBFTOBJS := $(LIBFT)/$(LIBFTNAME)
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS	:= $(OBJECTS:.o=.d)
BDEPS	:= $(OBJECTS:.o=.d)

all:	
		@make bonus -C $(LIBFT)
		@make $(NAME)

$(NAME)	:	$(OBJECTS) $(LIBFTOBJS)
			@cp $(LIBFTOBJS) $(NAME)
			@ar rcs $(NAME) $(OBJECTS) 


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) / $(*D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -MP -MF $(OBJDIR)/$*.d  -o $@
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean	:
			$(RM) $(OBJECTS)
			$(RM) $(DEPS)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.d)
			make clean -C $(LIBFT)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBFTOBJS)

re		:	fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean fclean bonus re
