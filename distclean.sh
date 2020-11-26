LIBPNGDIR=src/libpng-1.6.37
LIBZDIR=src/libpng-1.6.37/zlib-1.2.11
PUDIR=src/plotutils
rm -rf src/libpng
rm -rf src/plotutils27
cd $LIBZDIR
ZROOTDIR=$(pwd);
make distclean
rm -f *.log
cd $OLDPWD
# clean libpng
cd $LIBPNGDIR
PNGROOTDIR=$(pwd);
make distclean
rm -f *.log
cd $OLDPWD
cd $PUDIR
make distclean
rm -f *.log
cd $OLDPWD
