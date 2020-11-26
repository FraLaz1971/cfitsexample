bash buildlibpng.sh
LIBPNGDIR=src/libpng-1.6.37
LIBZDIR=src/libpng-1.6.37/zlib-1.2.11
PUDIR=src/plotutils
# build plotutils
cd $PUDIR
if   [[ "$OS" == "Windows_NT" ]]
then
        echo "detected Microsoft $OS $(uname)"
        arch=$(uname -m)
        if [[ $arch == i686 ]]
        then
                echo 'ex. build-plotutils-win-mingw-i686.sh'
		configure-win-x86_64.sh
		mingw32-make
		mingw32-make install
        elif [[ $arch == x86_64 ]]
        then
                echo 'ex. build-plotutils-win-mingw-x86-64.sh'
		configure-win-i686.sh
		mingw32-make install
        else
                echo "unhandled arch"
        fi
	elif [[ $(uname) == "Linux" ]]
	then
        	echo "detected GNU/linux $OS"
        	uname -a
        	lsb_release -a
		. configure-linux.sh
		make
		make install
	elif [[ $(uname) == "Darwin" ]]
	then
        	echo "detected Apple $OS $(uname)"
        	. configure-mac.sh
		make
		make install
	else
        	echo "unknow OS"
	fi
cd $OLDPWD
