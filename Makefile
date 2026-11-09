TARGET := snake

CFILES := main.c

CC := clang
CFLAGS := -Wall -Wextra -Werror -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

${TARGET}: ${CFILES}
	${CC} ${CFILES} -o ${TARGET} ${CFLAGS}

run: ${TARGET}
	./${TARGET}

clean:
	rm ${TARGET}
