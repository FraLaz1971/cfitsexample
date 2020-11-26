CC = gcc 
RM = rm -f
#CPPFLAGS = -DDEBUG=1
CPPFLAGS = -g -I.
CFLAGS = -O 
OEXT = .o
EEXT =
SLEXT = .a
AR = ar rcs
TARGET=testlibfun
OBJ = functions$(OEXT) plot$(OEXT)
all: libfun$(SLEXT) $(TARGET)$(EEXT)

$(TARGET)$(OEXT):

$(TARGET)$(EEXT): libfun$(SLEXT) 

functions$(OEXT): functions.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c functions.c

plot$(OEXT): plot.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c plot.c

libfun$(SLEXT): functions$(OEXT) plot$(OEXT)
	$(AR) libfun.a $(OBJ)

clean:
	$(RM) libfun$(SLEXT) $(OBJ)

.PHONY: clean

