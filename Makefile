
# Makefile:
#
#	Make IoT Touch Screen App
#
#	Ovidiu MM November 2015
#	Based on makefile by Gordon Henderson
###############################################################################

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe
DEPS    = temphum.h blinkie.h
LDFLAGS	= -L/usr/local/lib
LIBS    = -lm -lpthread -lwiringPi -lgeniePi

SRC	= main.c

# May not need to  alter anything below this line
###############################################################################

OBJ	=	$(SRC:.c=.o)
BINS	=	$(SRC:.c=)


main:	main.o
	@echo [link]
	@$(CC) -o $@ main.o temphum.o blinkie.o $(LDFLAGS) $(LIBS)
tempAPP: main.o

.c.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONEY:	clean
clean:
	rm -f $(OBJ) $(BINS) *~ core tags *.bak

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)

.PHONEY:	depend
depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
