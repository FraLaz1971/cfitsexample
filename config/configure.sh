#/usr/bin/env bash
echo "generating total makefile for $(uname) $OS ..." >&2
a=0;t=0;TARGETS="";RMTARGETS=""; EEXT=".exe";OEXT=".o"
echo 'CC=gcc -g -O2 -fPIC '
echo 'MAKE = make'
echo 'SRC = $(wildcard src/*.c)'
echo "OBJ = src/*.o"
echo 'CPPFLAGS = -Iinclude -Isrc -I/src/fun'
echo 'LIBS = src/fun/libfun.a src/libcfitsio.a'
echo 'LDFLAGS = -lm'
for t in $(ls -1 src/*.c)
do
	TARGET=$(basename ${t%.*})
	echo 'TARGET'$a = $TARGET
	TARGETS="$TARGET $TARGETS"
	RMTARGETS="src/$TARGET $RMTARGETS"
	a=$(($a+1)) 
done
echo 'TARGETS' = $TARGETS
echo 'RMTARGETS' = $RMTARGETS
echo 'all: libfun src/libcfitsio.a $(TARGETS)'
echo '#creating libfun'
echo 'all: $(TARGETS)'
echo 'libfun: src/fun/functions.o'
echo -e "\t"'cd src/fun && $(MAKE)'
echo -e 'src/libcfitsio.a: src/cfitsio/buffers.o src/cfitsio/cfileio.o  src/cfitsio/checksum.o \'
echo -e 'src/cfitsio/cookbook.o \'
echo -e 'src/cfitsio/drvrfile.o src/cfitsio/drvrmem.o src/cfitsio/drvrnet.o src/cfitsio/drvrsmem.o \'
echo -e 'src/cfitsio/editcol.o src/cfitsio/edithdu.o src/cfitsio/eval_f.o src/cfitsio/eval_l.o \'
echo -e 'src/cfitsio/eval_y.o src/cfitsio/f77_wrap1.o src/cfitsio/f77_wrap2.o src/cfitsio/f77_wrap3.o \'
echo -e 'src/cfitsio/f77_wrap4.o src/cfitsio/fits_hcompress.o src/cfitsio/fits_hdecompress.o \'
echo -e 'src/cfitsio/fitscopy.o src/cfitsio/fitscore.o \'
echo -e 'src/cfitsio/fpack.o src/cfitsio/fpackutil.o src/cfitsio/funpack.o \'
echo -e 'src/cfitsio/getcol.o src/cfitsio/getcolb.o src/cfitsio/getcold.o src/cfitsio/getcole.o \'
echo -e 'src/cfitsio/getcoli.o src/cfitsio/getcolj.o src/cfitsio/getcolk.o src/cfitsio/getcoll.o \'
echo -e 'src/cfitsio/getcols.o src/cfitsio/getcolsb.o src/cfitsio/getcolui.o src/cfitsio/getcoluj.o \'
echo -e 'src/cfitsio/getcoluk.o src/cfitsio/getkey.o src/cfitsio/group.o src/cfitsio/grparser.o \'
echo -e 'src/cfitsio/histo.o src/cfitsio/imcompress.o \'
echo -e 'src/cfitsio/imcopy.o src/cfitsio/iraffits.o src/cfitsio/iter_a.o \'
echo -e 'src/cfitsio/iter_b.o src/cfitsio/iter_c.o \'
echo -e 'src/cfitsio/listhead.o src/cfitsio/modkey.o src/cfitsio/pliocomp.o \'
echo -e 'src/cfitsio/putcol.o src/cfitsio/putcolb.o src/cfitsio/putcold.o src/cfitsio/putcole.o \'
echo -e 'src/cfitsio/putcoli.o src/cfitsio/putcolj.o src/cfitsio/putcolk.o src/cfitsio/putcoll.o \'
echo -e 'src/cfitsio/putcols.o src/cfitsio/putcolsb.o src/cfitsio/putcolu.o src/cfitsio/putcolui.o \'
echo -e 'src/cfitsio/putcoluj.o src/cfitsio/putcoluk.o src/cfitsio/putkey.o src/cfitsio/quantize.o \'
echo -e 'src/cfitsio/region.o src/cfitsio/ricecomp.o src/cfitsio/scalnull.o src/cfitsio/simplerng.o \'
echo -e 'src/cfitsio/smem.o src/cfitsio/speed.o \'
echo -e 'src/cfitsio/swapproc.o  \'
echo -e 'src/cfitsio/testprog.o src/cfitsio/wcssub.o src/cfitsio/wcsutil.o src/cfitsio/zlib/adler32.o \'
echo -e 'src/cfitsio/zlib/crc32.o src/cfitsio/zlib/deflate.o src/cfitsio/zlib/infback.o \'
echo -e 'src/cfitsio/zlib/inffast.o src/cfitsio/zlib/inflate.o src/cfitsio/zlib/inftrees.o \'
echo -e 'src/cfitsio/zlib/trees.o src/cfitsio/zlib/uncompr.o src/cfitsio/zlib/zcompress.o \'
echo -e 'src/cfitsio/zlib/zuncompress.o src/cfitsio/zlib/zutil.o'
echo -e "\t"'./buildcfitsio.sh;cd src/cfitsio && $(MAKE) && cp libcfitsio.a ../'
echo 'cleanlibfun:'
echo -e "\t"'cd src/fun && $(MAKE) clean; rm -f testlibfun'
echo 'cleancfitsio:'
echo -e "\t"'cd src/cfitsio && $(MAKE) clean; rm -f *.log *.fit cfitsio.pc'
a=0
for s in $(ls -1 src/*.c)
do
	TARGET=$(basename ${s%.*})
	echo '$(TARGET'$a').o: src/'$TARGET'.c'
	echo -e "\t"'$(CC) -c   $< -o src/'$TARGET'.o $(CPPFLAGS)'
	if [[ $TARGET != "src/analysis" ]]
	then
		echo '$(TARGET'$a'): src/'$TARGET'.o src/libcfitsio.a'
		echo -e "\t"'$(CC) $< $(LIBS) -o src/'$TARGET' $(LDFLAGS)'
	else
		echo 'src/analysis.o:'
		echo -e "\t"'$(CC) $< $(LIBS) -o src/'analysis' $(LDFLAGS)'
	fi
	a=$(($a+1)) 
done
echo 'echo created all targets' >&2
echo 'install: all'
echo -e '\tmv $(TARGETS) bin'
echo '.PHONY: clean distclean cleanlibfun cleancfitsio'
echo 'clean: cleanlibfun cleancfitsio'
echo -e "\t"'rm -f $(OBJ) $(RMTARGETS)'
echo 'distclean: clean'
echo -e "\t"'rm -f bin/* Makefile* */*.fit *.fit *.fits *.csv *.ssv *.tsv *.dat *.txt *.log src/*.fit src/libcfitsio.a '
echo "generating dirs" >&2
if ! test -d bin; then mkdir  bin; fi
