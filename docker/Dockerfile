FROM ubuntu:21.04

ENV DEBIAN_FRONTEND=noninteractive 
ENV CMAKE_C_COMPILER=/usr/bin/gcc-10
ENV CMAKE_CXX_COMPILER=/usr/bin/g++-10
RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install -y gcc-10 g++-10 cmake git wget bzip2

WORKDIR /opt/ott/

COPY CMakeLists.txt  /opt/ott/
ADD lib /opt/ott/lib
ADD third_parties /opt/ott/third_parties
ADD script.sh /opt/ott
ADD setenv.sh /opt/ott


#RUN ./script.sh

ENTRYPOINT ["/bin/bash", "-c"]
