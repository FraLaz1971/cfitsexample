#/usr/bin/env bash
echo "generating total makefile for $(uname) $OS ..." >/dev/stderr
a=0;t=0;TARGETS="";RMTARGETS=""
EEXT=.exe
OEXT=.o
echo 'LDFLAGS =  -L"."  -g'
echo 'LIBS = '
echo 'INCS =  -I"."'
echo 'CXXINCS =  -I"include"'
echo 'CXXFLAGS = $(CXXINCS)   -g'
echo 'CFLAGS = $(INCS)  -g'
echo 'RM = rm -f'
echo 'CXX  = x86_64-w64-mingw32-g++ -g -O'
echo 'CC   = x86_64-w64-mingw32-gcc -g -O'
echo 'SRC = $(wildcard src/*.c)'
echo "OBJ = src/*"$OEXT
echo 'CPPFLAGS = -Iinclude -Isrc/cfitsio'
echo 'LIBS = src/cfitsio/libcfitsio.a'
echo 'LDFLAGS = -lm'

for t in $(ls -1 src/*.c)
do
	TARGET=$(basename ${t%.*})
	echo 'TARGET'$a = $TARGET$EEXT
	TARGETS="$TARGET$EEXT $TARGETS"
	RMTARGETS="src/$TARGET$EEXT $RMTARGETS"
	a=$(($a+1)) 
done
echo 'TARGETS' = $TARGETS
echo 'all: cfitsio $(TARGETS)'
echo '#cfitsio lib target'
echo 'cfitsio: src/cfitsio/libcfitsio.a'
echo
echo 'src/cfitsio/libcfitsio.a:'
echo -e "\t"' bash buildcfitsio.sh'
echo 'cleancfitsio:'
echo -e "\t"' bash cleancfitsio.sh'
a=0
for s in $(ls -1 src/*.c)
do
	TARGET=$(basename ${s%.*})
	echo '$(TARGET'$a')'$OEXT': src/'$TARGET'.c'
	echo -e "\t"'$(CC) -c   $< -o src/'$TARGET$OEXT' $(CPPFLAGS)'
	if [[ $TARGET != "analysis" ]]
	then
		echo '$(TARGET'$a'): src/'$TARGET$OEXT
		echo -e "\t"'$(CC) $< $(LIBS) -o src/'$TARGET$EEXT' $(LDFLAGS)'
	else
		echo 'analysis:'
	fi
	a=$(($a+1)) 
done
echo 'echo created all targets' >/dev/stderr
echo 'install: all'
echo -e '\tmv $(TARGETS) bin'
echo '.PHONY: clean cleancfitsio distclean'
echo 'clean:'
echo -e "\t"'rm -f $(OBJ) $(RMTARGETS)'
echo 'distclean: clean cleancfitsio'
echo -e "\trm -f bin/* Makefile* *.fit *.fits *.csv *.ssv *.tsv *.dat *.txt *.log"
echo "generating dirs" >/dev/stderr
if ! test -d bin; then mkdir  bin; fi
