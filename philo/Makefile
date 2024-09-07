
NAME = philo

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c \
		parser.c \
		utils.c \
		table.c \
		eating.c \
		routine.c \
		death.c \

SRCS := $(SRCS:%.c=$(SRC_DIR)/%.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall \
			-Werror \
			-Wextra \
			-g \

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo PHILO COMPILED : ✓

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm  -rf $(OBJS) $(OBJ_DIR)
	@echo PHILO CLEAN : ✓

fclean: clean
	@rm -f $(NAME)
	@echo PHILO FCLEAN : ✓

re: fclean all
