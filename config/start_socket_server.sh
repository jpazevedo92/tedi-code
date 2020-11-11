#!/bin/bash

sudo gnome-terminal -- bash  -c '
        DIR=~/Repos/tedi-uavcommandforward/1_Code/config/socket;
		cd $DIR;
        make all;
        cd $DIR/bin;
        ./socket -S;
	    exec bash
' 


