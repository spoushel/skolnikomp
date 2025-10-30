CFLAGS := -Wall -Wextra
CC := clang
OBJS := test_factorial.o utils/math_utils.o

TARGET_EXE := program

all: program

$(TARGET_EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $TARGET_EXE 

%.o: %.c 
	$(CC) $(CFLAGS) -c $^.c -o $@

clean:
	rm program
	rm test_factorial.o utils/math_utils.o 

.PHONY: clean all

# @ pred dvojteckou, ^ za dvojteckou
# test_factorial.o: test_factorial.c 
#	clang $(CFLAGS) -c test_factorial.c -o test_factorial.o

#math_utils.o: utils/math_utils.c 
#	clang $(CFLAGS) -c utils/math_utils.c -o math_utils.o

