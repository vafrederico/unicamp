CC=gcc
C_FLAGS=-g
SRC_FILES=server.c
OBJ_FILES=server.o security_app.o utils.o
INCLUDE_DIRS=.
EXEC=server

# $^: lista de dependencias
# $<: primeira dependencia
# $@: nome da regra

all: $(EXEC)

server: $(OBJ_FILES)
	$(CC) $(C_FLAGS) $^ -lpthread -o $(EXEC)

server.o: $(SRC_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@ -I$(INCLUDE_DIRS)

security_app.o: security_app.c
	$(CC) $(C_FLAGS) -c $^ -o $@ -I$(INCLUDE_DIRS)

utils.o: utils.c
	$(CC) $(C_FLAGS) -c $^ -o $@ -I$(INCLUDE_DIRS)

clean:
	rm -rf *.o
