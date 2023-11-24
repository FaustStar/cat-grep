TARGET = s21_grep
CFLAGS = -Wall -Werror -Wextra -std=c11

.PHONY: all clean rebuild test

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o ../common/*.o

$(TARGET): s21_grep.o ../common/common.o
	gcc $(CFLAGS) s21_grep.o ../common/common.o -o $(TARGET)

s21_grep.o: s21_grep.c s21_grep.h
	gcc $(CFLAGS) -c s21_grep.c

../commom/commom.o: ../common/common.c ../common/common.h
	gcc $(CFLAGS) -c ../common/common.c

rebuild:
	$(MAKE) clean
	$(MAKE) all

test:
	chmod +x ./test/grep_test.sh
	./test/grep_test.sh