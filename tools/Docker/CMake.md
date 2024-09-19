在Ubuntu系统安装cmake时，通过sudo apt-get install安装版本很低，且很可能因为一些依赖关系报错，因此建议通过cmake官网来安装。

我们可以先通过wget下载cmake版本文件：

wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz
然后解压缩，cd进去文件目录；通过./bootstrap来进行编译：

tar -zxvf cmake-3.20.0.tar.gz
cd cmake-3.20.0
./bootstrap
但是这中间可能遇到报错：

![img](C:\Files\code\Learning\Docker\images\9045ae90adf14ed38b5650eb3c80874c.png)

报错中明确说了：Could not find OpenSSL，OpenSSL在ubuntu系统中即libssl，

因此需要安装libssl-dev，通过以下指令安装即可；

sudo apt-get install libssl-dev
（如果成功安装libssl-dev可以跳过这段）这中间我出现了一个困扰非常久的报错：

E: 无法修正错误，因为您要求某些软件包保持现状，就是它们破坏了软件包间的依赖关系

或者：

E：无法定位软件包

此时网上大部分方法都说要换源，比如通过：sudo vi /etc/apt/sources.list，或者在ubuntu自带的软件更新里面更改服务器镜像，但是这些方法对我都没用

最后我是通过命令： 

lsb_release -c
查看自己ubuntu系统的版本，发现是focal类型，而我的镜像都是bionic的，所以在这里我把之前的镜像全部换成了focal类型：

# 阿里云镜像源
deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse

deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse

deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse

deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse

deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse

deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse

#清华园
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan main restricted universe multiverse

deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan main restricted universe multiverse

deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-updates main restricted universe multiverse

deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-updates main restricted universe multiverse

deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-backports main restricted universe multiverse

deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-backports main restricted universe multiverse

deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-security main restricted universe multiverse

deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-security main restricted universe multiverse

deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-proposed main restricted universe multiverse

deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ eoan-proposed main restricted universe multiverse
换源后记得更新一下：

sudo apt-get update
sudo apt-get upgrade

然后通过

sudo apt-get install
成功安装了libssl-dev，

在我继续./bootstrap时候，又出现下面报错：

 ![img](C:\Files\code\Learning\Docker\images\e979418508434d9993dac2ff726043f3.png) 

此时请考虑手动安装缺失文件：

sudo apt install mesa-common-dev libglu1-mesa-dev
然后继续执行./bootstrap，完成之后用make指令编译构建，然后用sudo make install 完成安装：

make 
sudo make install
最后可以通过cmake --version检查是否成功！