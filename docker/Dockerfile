FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive 
ENV CMAKE_C_COMPILER=/usr/bin/gcc-10
ENV CMAKE_CXX_COMPILER=/usr/bin/g++-10
RUN apt-get update
RUN apt-get upgrade

RUN apt-get install gcc-10 g++-10 cmake -y git

WORKDIR /opt/ott/

COPY CMakeLists.txt  /opt/ott/
ADD lib /opt/ott/lib
ADD third_parties /opt/ott/third_parties
ADD script.sh /opt/ott
ADD setenv.sh /opt/ott


RUN ./script.sh

ENTRYPOINT ["/bin/bash", "-c"]
