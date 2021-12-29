CC:=gcc
B_OUT_DIR := bin
LDFLAGS = -lpthread
CFLAGS = $(shell if [ ! -e $(B_OUT_DIR) ];then mkdir -p $(B_OUT_DIR); fi)
TARGET = simple \
		test \

all: $(TARGET)

simple: simple.c
	${CC} ${CFLAGS} ${LDFLAGS} \
		-o $(B_OUT_DIR)/$@ $^
	./$(B_OUT_DIR)/$@

test: test.c
	${CC} ${CFLAGS} ${LDFLAGS} \
		-o $(B_OUT_DIR)/$@ $^
	./$(B_OUT_DIR)/$@
