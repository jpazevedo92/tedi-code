#!/bin/bash

DIR=socket
sudo su
cd $DIR
make all
cd $DIR/bin 
sudo su &
./socket -C 192.168.56.1 -R	
./socket -S &