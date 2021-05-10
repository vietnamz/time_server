## boost

wget https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2

tar -xf boost_1_76_0.tar.bz2

mv boost_1_76_0  boost


./boostrap.sh

./b2 link=static runtime-link=static  toolset=gcc-10 install --prefix=build cxxflags="-std=c++20" linkflags="-std=c++20" --with-thread --with-atomic  --with-chrono --with-context --with-filesystem --with-log --with-json --with-coroutine --with-timer --with-date_time --with-exception --with-random
