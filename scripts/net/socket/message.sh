#!/bin/bash
echo "Socket server - start"
set -x
####################################################### VARIABLES ####################################################################

OPTION=$1
HOST=$2
project_root=$(dirname $(dirname $(dirname $(dirname $(realpath $0 )))))
socket_dir="$project_root/socket"
cd $socket_dir
make clean
if [ $OPTION == "-s" ]
then
    make message_srv
    ls

#elif [ $OPTION == '-c'  ]
#then

fi
