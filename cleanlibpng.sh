LIBPNGDIR=src/libpng-1.6.37
LIBZDIR=src/libpng-1.6.37/zlib-1.2.11
cd $LIBZDIR
make clean
make -f win32/Makefile.i686-w64-mingw32-gcc clean
make -f win32/Makefile.x86_64-w64-mingw32-gcc clean
rm -f *.log
cd $OLDPWD
cd $LIBPNGDIR
# clean libpng
make clean
rm -f *.log
cd $OLDPWD
