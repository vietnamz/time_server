
#!/bin/bash

set -e

echo "**** building boost ****"


cd $DEPENDENCIES_ROOT/boost

BOOST_VERSION=1_76_0

# a file we use/touch to indicate ffmpeg has been built
VERSION_FILE=ver-$BOOST_VERSION

if [ ! -e $VERSION_FILE ] ; then

    if [ -d "boost/" ] ; then
        echo "Removing existing directory..."
        rm -Rf boost/
    fi
    
    
    BOOST_DISTFILE=boost_$BOOST_VERSION.tar.bz2

    echo "$BOOST_DISTFILE "

    if [ -d "$BOOST_DISTFILE" ]; then
        echo "$BOOST_DISTFILE already exist!"
    else
        wget https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2
    fi

    echo "Extracting $BOOST_DISTFILE..."

    tar -xf $BOOST_DISTFILE
    
    mv boost_$BOOST_VERSION/ boost/

    cd boost/

    ./bootstrap.sh

    ./b2 link=static install --prefix=build --with-thread --with-atomic --with-chrono --with-context --with-date_time    

    echo "**** installing boost ****"
    
    # touch a marker file
    cd $DEPENDENCIES_ROOT/boost/

    rm -rf ver*

    touch $VERSION_FILE
fi
