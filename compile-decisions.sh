pro=`find *_check.pro`
for i in $pro
do
/usr/lib/qt5/bin/qmake `pwd`/$i -r -spec linux-clang CONFIG+=release
make
done
