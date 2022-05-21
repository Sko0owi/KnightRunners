
CC = gcc
CFLAGS= -c -std=c99 -Wall
LIBS = `pkg-config  --cflags --libs gtk+-3.0`
LFLAGS = -lm

BUILD_DIR ?= ./Build
SRC_DIR ?= ./Source

SRC_TMP ?= Source/

NAME = KnightRunners

SRC := $(SRC_DIR)/main.c  $(SRC_DIR)/GameManager/gamemanager.c  $(SRC_DIR)/Fifo/lin-fifo.c  $(SRC_DIR)/Player/player.c $(SRC_DIR)/Map/map.c $(SRC_DIR)/Room/room.c  $(SRC_DIR)/Enemy/enemy.c  $(SRC_DIR)/Attributes/attributes.c


OBJS := $(BUILD_DIR)/main.o $(BUILD_DIR)/gamemanager.o $(BUILD_DIR)/player.o $(BUILD_DIR)/lin-fifo.o $(BUILD_DIR)/map.o $(BUILD_DIR)/room.o $(BUILD_DIR)/enemy.o $(BUILD_DIR)/attributes.o



DEPS = $(SRC_DIR)/GameManager/gamemanager.h \
 $(SRC_DIR)/GameManager/../Player/player.h \
 $(SRC_DIR)/GameManager/../Player/../Map/map.h \
 $(SRC_DIR)/GameManager/../Player/../Map/../Room/room.h \
 $(SRC_DIR)/GameManager/../Player/../Map/../Room/../Enemy/enemy.h \
 $(SRC_DIR)/GameManager/../Player/../Map/../Room/../Enemy/../Attributes/attributes.h \
 $(SRC_DIR)/GameManager/../Fifo/fifo.h


YOU: $(OBJS) $(NAME) 


$(NAME):$(OBJS)
	$(CC) -o $(BUILD_DIR)/$(NAME) $(OBJS) $(LIBS)
	

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/gamemanager.o: $(SRC_DIR)/GameManager/gamemanager.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/player.o: $(SRC_DIR)/Player/player.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/lin-fifo.o: $(SRC_DIR) /Fifo/lin-fifo.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/map.o: $(SRC_DIR)/Map/map.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/room.o: $(SRC_DIR)/Room/room.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/enemy.o: $(SRC_DIR)/Enemy/enemy.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
$(BUILD_DIR)/attributes.o: $(SRC_DIR)/Attributes/attributes.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)


clean:
	rm -f $(OBJS)
	


