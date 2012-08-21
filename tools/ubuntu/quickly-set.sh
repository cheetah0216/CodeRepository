#!/bin/bash
#更新源列表
apt-get update
#在右键里面 添加一个“打开终端”的菜单,需重启图形界面
sudo apt-get -y install nautilus-open-terminal
#右键中添加"以管理员身份打开"，需重启图形界面
sudo apt-get -y install nautilus-gksu

#rar，7z支持
sudo apt-get -y install rar
sudo apt-get -y install p7zip

sudo apt-get -y install python3.2
#sudo apt-get -y install chromium-browser
sudo apt-get -y install vim
sudo apt-get -y install vim-gnome
sudo apt-get -y install git
#sudo apt-get -y install wine
sudo apt-get -y install g++
sudo apt-get -y install playonlinux
sudo apt-get -y install putty
sudo apt-get -y install cscope
#多系统时更新启动项
#ubuntun10.10
#apt-get install grub2
#sudo update-grub

#重启图形界面
#ubuntu10.10
#sudo service gdm restart




