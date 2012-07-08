#!/bin/bash

CreatDir="/usr/share/fonts/msyh"

if [ ! -d $CreatDir ] ; then
    sudo mkdir $CreatDir
fi

sudo cp /media/027E04147E03FF63/Windows/Fonts/msyh* $CreatDir
sudo chmod 755 $CreatDir/*
cd $CreatDir
sudo mkfontscale && sudo mkfontdir && sudo fc-cache -fv > /dev/null
