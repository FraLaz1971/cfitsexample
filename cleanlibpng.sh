LIBPNGDIR=src/libpng-1.6.37
cd $LIBPNGDIR
# build zlib
LIBZDIR=src/libpng-1.6.37/zlib-1.2.11
cd $LIBZDIR
ZROOTDIR=$(pwd);
make clean
rm -f *.log
# build libpng
PNGROOTDIR=$(pwd);
make clean
rm -f *.log
cd $OLDPWD
