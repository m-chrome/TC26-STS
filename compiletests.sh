pros=`find *test.pro`
for i in $pros
do
/usr/lib/qt5/bin/qmake `pwd`/$i -r -spec linux-clang CONFIG+=release
make
done
