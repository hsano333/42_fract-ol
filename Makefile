NAME 	:= fractol
LIB	:= ./lib/

LIBMLXDIR	:= $(LIB)/minilibx-linux
LIBMLX		:= $(LIBMLXDIR)/libmlx.a

LIBFTDIR	:= $(LIB)/libft
LIBFTNAME	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)

SRCDIR	:= ./srcs/
SRC	:= init.c key.c mouse.c image.c julia.c mandelbrot.c gasket.c fract_common.c color.c color2.c image_common.c affine.c image_util.c zoom.c burning_ship.c
ENTRY	:= main.c
ENTRYBONUS	:= main_bonus.c
ifdef WITH_BONUS
ENTRY	:= $(ENTRYBONUS)
endif
SRC	+= $(ENTRY)

SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.c=.o)
OBJDIR	:= ./obj
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS	:= $(OBJECTS:.o=.d)
INCS	:= ./include $(LIBFTDIR)/include $(LIBMLXDIR)

LIBDIRS	:= $(LIBFTDIR) $(LIBMLXDIR) 
IFLAGS	:= $(addprefix -I,$(INCS))
LFLAGS	:= $(addprefix -L,$(LIBDIRS))
LIBS	:= $(LIBFT) $(LIBMLX)



CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror -fsanitize=address
LDFLAGS := $(IFLAGS) $(LFLAGS) -lft -lmlx -lX11 -lXext -lm

all:	$(NAME)	

$(NAME)	:	$(OBJECTS) $(LIBS) 
		$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) / $(*D)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -MMD -MP -MF $(OBJDIR)/$*.d  -o $@
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

%.a:
	echo "Make libft"
	echo $@
	make -C $(dir $@)

clean	:
			$(RM) $(OBJECTS)
			$(RM) $(DEPS)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.d)
			make clean -C $(LIBFTDIR)
			make clean -C $(LIBMLXDIR)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBS)

re	:		fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean fclean bonus re
