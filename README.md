# Simple Time server which support http and websocket.


## Toolchain and libraries

1. gcc 10 which support c++20  or earlier
2. cmake 3.9.4 or earlier 
3. docker
4. docker compose
5. boost 1.76.0 or earlier
    a. the boost library was distributed in the third_parties forder for the sake of simplicity and ensure they work well together.

## Platform


 |OS | Supported | Build|
 |---| --- | ---| 
 |window | no | false| 
 |Ubuntu 18.04 | yes | true| 
 


## Build

If you use the ubuntu 20.04 or earlier. You can simple obtain the gcc 10 with already support c++20
Otherwise you need to install the gcc 10 in order to build the code.

````shell script
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt install gcc-10

sudo apt install g++-10
```

Ex : cmake command from the top of code base:

```shell script
export OTT_ROOT=`pwd`
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc-10 -DCMAKE_CXX_COMPILER=/usr/bin/g++-10 --prefix=build
````


There is a script to build the whole code base, just simply typing

```shell script
./script.sh
````

The script above will build the whole code base. But You need to make sure gcc and g++ that ship with your machine support c++10, othewise you have to export two variable environment below:

```shell script
export CMAKE_C_COMPILER=/usr/bin/gcc-10
export CMAKE_CPP_COMPILER=/usr/bin/g++-10
```

Please have a look in the setenv.sh for details


### Testing websocket

please take a look in the script folder for details.

#### TODO:


1. Support ssl
2. Combine websocket and http into once port. Right now, I think separating the http and websocket would be easy to scale independently.
( Sample: https://github.com/boostorg/beast/tree/1da229a27c6f0539d422bcedbcf47cfe2517164a/example/advanced )
3. Combine the share logic between http and websocket into one library.
4. Make it combine thing out
4. Something wrong with the current code, sow we need to ensure it gone
