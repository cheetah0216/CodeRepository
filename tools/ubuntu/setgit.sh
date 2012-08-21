#!/bin/bash

GitDir="/home/liufei/github"
if [ ! -d "$GitDir" ] ; then
	mkdir -p "$GitDir"
fi

git config --global user.name "liufei"
git config --global user.email "flying0216@gmail.com"
git config --global credential.helper 'cache --timeout=3600' 
git config --global core.excludesfile ~/.gitignor

echo "登录 Github 帐号，找到帐号设置 -> SSH Keys"
echo "点击 Add New SSH Key"
echo "将本地生成的公钥文件（~/.ssh/csser-github.pub）中的文字全选复制到 key 栏，点击 add key 保存。"

ssh-keygen -t rsa -C "flying0216@gmail.com" -f ~/.ssh/csser-github

git clone https://github.com/cheetah0216/CodeRepository.git
git clone https://github.com/cheetah0216/OurMoney.git
git clone https://github.com/cheetah0216/snack.git

