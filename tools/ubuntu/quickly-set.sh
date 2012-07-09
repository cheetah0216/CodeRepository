#!/bin/bash

#在右键里面 添加一个“打开终端”的菜单,需重启图形界面
sudo apt-get install nautilus-open-terminal
#右键中添加"以管理员身份打开"，需重启图形界面
sudo apt-get install nautilus-gksu

#rar，7z支持
sudo apt-get install rar
sudo apt-get install p7zip

#多系统时更新启动项
apt-get install grub2
sudo update-grub

#重启图形界面
sudo service gdm restart




