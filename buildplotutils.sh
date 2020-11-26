. buildlibpng.sh
LIBPNGDIR=src/libpng-1.6.37
LIBZDIR=src/libpng-1.6.37/zlib-1.2.11
# build plotutils
ZRPREFIX=src/libz
make 2>&1 | tee build_zlib_$(date --iso).log
make install 2>&1 | tee install_zlib_$(date --iso).log
# build libpng
PNGROOTDIR=$(pwd); PNGPREFIX="$PNGROOTDIR"/../libpng
./configure --prefix="$PNGPREFIX" --with-sysroot=$PREFIX --with-zlib-prefix=$ZPREFIX
make 2>&1 | tee build_libpng_$(date --iso).log
make install 2>&1 | tee install_libpng_$(date --iso).log
cd $OLDPWD
