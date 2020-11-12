CC	= gcc -g -O
RM	= rm -f
EEXT	= .exe
OEXT	= .o
TARGET1 = mycb
TARGET2 = read_first_fitsfile
OBJ	= $(TARGET1)$(OEXT) $(TARGET2)$(OEXT)
CPPFLAGS = -Icfitsio
LDFLAGS = cfitsio/libcfitsio.a -lm
DATASET = numbers.txt


all: $(TARGET1)$(EEXT) $(TARGET2)$(EEXT)

#TARGET1 is mycb

$(TARGET1)$(OEXT): $(TARGET1).c
	$(CC) -c $(TARGET1).c $(CPPFLAGS) -o $(TARGET1)$(OEXT)

$(TARGET1)$(EEXT): $(TARGET1)$(OEXT)
	$(CC) $(TARGET1)$(OEXT) -o $(TARGET1)$(EEXT) $(LDFLAGS)

#TARGET2 is read_first_fitsfile

$(TARGET2)$(OEXT): $(TARGET2).c
	$(CC) -c $(TARGET2).c $(CPPFLAGS) -o $(TARGET2)$(OEXT)

$(TARGET2)$(EEXT): $(TARGET2)$(OEXT)
	$(CC) $(TARGET2)$(OEXT) -o $(TARGET2)$(EEXT) $(LDFLAGS)

.PHONY: clean all plot data cleanplot

clean:
	$(RM) $(OBJ) $(TARGETS) $(DATASET)

data: $(TARGET1)
	./$(TARGET1) > $(DATASET)

plot: data
	gnuplot -p -e "plot '"$(DATASET)"'"

cleanplot: clean
