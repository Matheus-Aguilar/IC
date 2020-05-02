#!/bin/bash

# add postgresql official repository to apt
apt-get update
echo "deb http://apt.postgresql.org/pub/repos/apt/ trusty-pgdg main" >> /etc/apt/sources.list
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
apt-get update

# install required libraries
apt-get install -y autoconf build-essential cmake docbook-mathml docbook-xsl libboost-dev libboost-thread-dev libboost-filesystem-dev libboost-system-dev libboost-iostreams-dev libboost-program-options-dev libboost-timer-dev libcunit1-dev libgdal-dev libgeos++-dev libgeotiff-dev libgmp-dev libjson0-dev libjson-c-dev liblas-dev libmpfr-dev libopenscenegraph-dev libpq-dev libproj-dev libxml2-dev postgresql-server-dev-10 xsltproc git build-essential wget

apt-get install -y libcgal-dev

# install postgresql-10 server
apt-get install -y postgresql-10

# build sfcgal from source
wget https://github.com/Oslandia/SFCGAL/archive/v1.3.6.tar.gz
tar zxvf v1.3.6.tar.gz
cd SFCGAL-1.3.6 &&  cmake . && make  && make install
cd ..

# build postgis from source
wget http://download.osgeo.org/postgis/source/postgis-2.3.4.tar.gz
tar zxvf postgis-2.3.4.tag.gz
cd postgis-2.3.4
./configure --with-sfcgal=/usr/local/bin/sfcgal-config
make && make install

chmod 777 /usr/local/lib/libSFCGAL.*
cp /usr/local/lib/libSFCGAL.* /usr/lib/postgresql/10/lib

ldconfig -v | grep -i sfcgal 

su - postgres
psql -c "create database postgis_test;"
psql postgis_test -c "create extension postgis;"
psql postgis_test < /usr/share/postgresql/10/contrib/postgis-2.1/sfcgal.sql
psql postgis_test -c "select postgis_sfcgal_version();"
