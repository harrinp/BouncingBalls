

CFLAGS+=-Wall -Wextra -g -std=c99 -O3 -Ideps
PREFIX?=/usr/local
BINDIR?=$(PREFIX)/bin

LIBS= -lncurses

all: BouncingBalls

BouncingBalls:
	gcc $(CFLAGS) Balls.c BallsMain.c -o BouncingBalls $(LIBS)

install: BouncingBalls
	mkdir -p $(DESTDIR)$(BINDIR)
	cp BouncingBalls $(DESTDIR)$(BINDIR)/
	chmod 755 ${DESTDIR}${BINDIR}/BouncingBalls
clean:
	rm BouncingBalls
	rm ${DESTDIR}${BINDIR}/BouncingBalls
