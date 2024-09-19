# docker 安装部署

docker 核心组件

- image 
- container 
- 仓库（docker hub）
- dockerfile 将部署过程写成脚本

## 安装docker

1.更新软件源列表

```shell
sudo apt update
```

2.安装软件包依赖

```shell
sudo apt install apt-transport-https ca-certificates curl software-properties-commonsudo rm /var/lib/dpkg/lock-frontend
sudo rm /var/lib/dpkg/lock
sudo rm /var/cache/apt/archives/lock

sudo apt install apt-transport-https ca-certificates curl software-properties-common
```

3.在系统中添加Docker的官方密钥

```shell
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
```

4.添加Docker源,选择stable长期稳定版

```shell
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
```

5.再次更新源列表

```shell
sudo apt update
```

6.查看可以安装的Docker版本

```shell
sudo apt-cache policy docker-ce
```

7.开始安装Docker（ce表示社区版）

```shell
sudo apt install docker-ce
```

8.查看是否成功安装Docker，出现下图，说明安装成功

```shell
docker
```

9.查看安装的Docker版本

```shell
docker -v
```

10.启动Docker服务

```shell
sudo systemctl start docker//wsl 不好使换成 service
```

11.设置开机自启动docker

```shell
sudo systemctl enable docker
```

12.查看Docker是否开启，出现绿色圆点表示服务正常开启

```shell
sudo systemctl status docker
```

## docker 加速器

1、进入文件夹 `/etc/docker`

```shell
cd /etc/docker
```

如果你已经成功安装 Docker 了，那么这个文件夹应该是存在的。如果出现报错，你可能需要检查一下是不是你的 Docker 还没有安装成功（使用 `docker -v` 可以检查）

2、创建or编辑 `daemon.json`：

```bash
touch daemon.json
```

接下来，如果不会使用 `vi` 或者 `vim` 的用户，可能需要先用 `exit` 退出 root 用户的Bash，然后再用 `gedit` 打开可视化文本编辑软件：

```shell
# exit
$ sudo gedit daemon.json
```

这样会在 Ubuntu 系统打开一个类似 Windows 下记事本的对话框。

3、填写镜像地址：
如果你不知道怎么搞阿里云镜像，你可以在 `daemon.json` 中填写以下内容：

```json
{
  "registry-mirrors": ["https://docker.mirrors.ustc.edu.cn"]
}
```

4、重新加载Docker配置文件 并 重启 Docker

```shell
su root
systemctl reload  docker
systemctl restart  docker
```

## docker 基本操作

1. 获取镜像

   ```shell
   jszhou@hcss-ecs-f139:~/docker$ sudo docker search nginx
   NAME                               DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
   nginx                              Official build of Nginx.                        19291     [OK]
   unit                               Official build of NGINX Unit: Universal Web …   17        [OK]
   nginxinc/nginx-unprivileged        Unprivileged NGINX Dockerfiles                  135
   nginx/nginx-ingress                NGINX and  NGINX Plus Ingress Controllers fo…   86
   nginx/nginx-prometheus-exporter    NGINX Prometheus Exporter for NGINX and NGIN…   33
   nginxinc/nginx-s3-gateway          Authenticating and caching gateway based on …   3
   nginx/unit                         This repository is retired, use the Docker o…   64
   nginx/nginx-ingress-operator       NGINX Ingress Operator for NGINX and NGINX P…   2
   nginxinc/amplify-agent             NGINX Amplify Agent docker repository           1
   nginx/nginx-quic-qns               NGINX QUIC interop                              1
   nginxinc/ingress-demo              Ingress Demo                                    4
   nginxproxy/nginx-proxy             Automated Nginx reverse proxy for docker con…   119
   nginxproxy/acme-companion          Automated ACME SSL certificate generation fo…   127
   bitnami/nginx                      Bitnami nginx Docker Image                      180                  [OK]
   bitnami/nginx-ingress-controller   Bitnami Docker Image for NGINX Ingress Contr…   32                   [OK]
   ubuntu/nginx                       Nginx, a high-performance reverse proxy & we…   103
   nginxinc/nginmesh_proxy_debug                                                      0
   nginxproxy/docker-gen              Generate files from docker container meta-da…   14
   nginxinc/mra-fakes3                                                                0
   kasmweb/nginx                      An Nginx image based off nginx:alpine and in…   6
   nginxinc/ngx-rust-tool                                                             0
   nginxinc/mra_python_base                                                           0
   rancher/nginx-ingress-controller                                                   11
   nginxinc/nginmesh_proxy_init                                                       0
   docker pull nginx
   
   jszhou@hcss-ecs-f139:~/docker$ sudo docker pull nginx
   Using default tag: latest
   latest: Pulling from library/nginx
   1f7ce2fa46ab: Pull complete
   9b16c94bb686: Pull complete
   9a59d19f9c5b: Pull complete
   9ea27b074f71: Pull complete
   c6edf33e2524: Pull complete
   84b1ff10387b: Pull complete
   517357831967: Pull complete
   Digest: sha256:10d1f5b58f74683ad34eb29287e07dab1e90f10af243f151bb50aa5dbb4d62ee
   Status: Downloaded newer image for nginx:latest
   docker.io/library/nginx:latest
   
   root@hcss-ecs-f139:/home/jszhou# docker image ls
   REPOSITORY   TAG       IMAGE ID       CREATED      SIZE
   nginx        latest    a6bd71f48f68   7 days ago   187MB
   ```

   

2. 运行镜像

```perl
root@hcss-ecs-f139:/home/jszhou# docker image ls
REPOSITORY   TAG       IMAGE ID       CREATED      SIZE
nginx        latest    a6bd71f48f68   7 days ago   187MB
root@hcss-ecs-f139:/home/jszhou# docker run -d -p 80:80 a6bd71f48f68
c66b7b8fab560a19101ac001500fcf80966453dc603c5642dddc217ab779dd09
```

-d 表示在后台运行

-p 表示端口映射， 宿主机:容器

3、运行之后的结果

```shell 
root@hcss-ecs-f139:/home/jszhou# docker ps
CONTAINER ID   IMAGE     COMMAND                  CREATED         STATUS         PORTS                               NAMES
c66b7b8fab56   nginx     "/docker-entrypoint.…"   4 seconds ago   Up 3 seconds   0.0.0.0:80->80/tcp, :::80->80/tcp   nice_ride
```

4、停止dokcer 

```shell 
docker stop 容器ID
```

## 利用docker 实现系统发行版本的切换

```shell
docker pull centos:7.8.2003
docker pull ubuntu 

# 查看当前docmer images



# 查看发行版版本
root@hcss-ecs-f139:/home/jszhou# lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 18.04.6 LTS
Release:        18.04
Codename:       bionic

# 查看内核版本
root@hcss-ecs-f139:/home/jszhou# uname -r
4.15.0-213-generic

# 运行 docker centos 
root@hcss-ecs-f139:/etc/docker# docker run -it afb6fca791e0 bash 
[root@d11b45665154 /]# 
# 进入容器空间 ⬆ 
# -i 交互式操作
# -t 开启一个终端
# bash 进入容器之后，执行bash 脚本的

# 查看发行版本与内核版本
[root@d11b45665154 /]# cat /etc/redhat-release
CentOS Linux release 7.8.2003 (Core)
[root@d11b45665154 /]# uname -a
Linux d11b45665154 4.15.0-213-generic #224-Ubuntu SMP Mon Jun 19 13:30:12 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux

# 退出容器空间
[root@d11b45665154 /]# exit
exit
root@hcss-ecs-f139:/etc/docker#

# 进入 ubuntu 系统
root@hcss-ecs-f139:/etc/docker# docker run -it e4c58958181a bash
root@fb3d005cef4a:/# uname -a
Linux fb3d005cef4a 4.15.0-213-generic #224-Ubuntu SMP Mon Jun 19 13:30:12 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
root@fb3d005cef4a:/# cat /etc/lsb-release
DISTRIB_ID=Ubuntu
DISTRIB_RELEASE=22.04
DISTRIB_CODENAME=jammy
DISTRIB_DESCRIPTION="Ubuntu 22.04.3 LTS"
```

## docker 镜像原理

### **Docker镜像的核心原理一：镜像的存储和管理方式**

#### **镜像的设计**

​    一个镜像都由多个镜像层组成。
​    为了区别镜像层，Docker为每个镜像层都计算了UUID，根据镜像层中的数据使用加密哈希算法生成UUID。
​    所有镜像层和容器层都保存在宿主机的文件系统/var/lib/docker/中，由存储驱动进行管理。
​    在下载镜像时，Docker Daemon会检查镜像中的镜像层与宿主机文件系统中的镜像层进行对比，如果存在则不下载，只下载不存在的镜像层。
![img](C:\Files\code\Learning\Docker\images\e69e0729db8e6d4e1d59d2ee6c3f2e00_623x370.png)

#### **栈层式管理镜像层**

​    docker 中存储驱动用于管理镜像层和容器层。不同的存储驱动使用不同的算法和管理方式。在容器和镜像管理中，使用的两大技术是**栈式层管理和写时复制。**
​    Dockerfile中的每一条指令都会对应于Docker镜像中的一层，因此在docker build完毕之后，镜像的总大小将等于每一层镜像的大小总和。
​    每个镜像都由多个镜像层组成，从下往上以栈的方式组合在一起形成容器的根文件系统，Docker的存储驱动用于管理这些镜像层，对外提供单一的文件系统。Docker 的镜像实际上由一层一层的文件系统组成，这种层级的文件系统叫 UnionFS（联合文件系统）。

> **由于联合文件系统的存在，容器文件系统内容的大小不等于Docker镜像大小。**
> ![img](C:\Files\code\Learning\Docker\images\a088fc60fc529c2b5a01f9606d9359ab_369x231.png)
> 由于联合文件系统的存在，如果镜像层是相同的，则不同的镜像会共享该层。
> 如上图中，镜像A与镜像B就共享第二层镜像，使得A+B镜像文件大小并不等于A+B镜像占用宿主机存储空间容量的大小。
> `doker images`命令列出的镜像体积总和并不能代表实际使用的磁盘空间，需要使用`docker system df`命令来代替。



#### **UnionFS （联合文件系统）**

联合文件系统（UnionFS）是一种**分层**、轻量级并且高性能的文件系统，它支持对文件系统的修改作为一次提交来一层层的叠加，同时可以将不同目录挂载到同一个虚拟文件系统下。

> **分层的原因：**
>
> 1. 分层最大的一个好处就是共享资源
> 2. 有多个镜像都从相同的base镜像构建而来，那么宿主机只需在磁盘上保存一份base镜像；
> 3. 同时内存中也只需加载一份base镜像，就可以为所有容器服务了，而且镜像的每一层都可以被共享。

​    联合文件系统是 Docker 镜像的基础。镜像可以通过分层来进行继承，基于基础镜像（没有父镜像），可以制作各种具体的应用镜像。
​    特性：一次同时加载多个文件系统，但从外面看起来，只能看到一个文件系统，联合加载会把各层文件系统叠加起来，这样最终的文件系统会包含所有底层的文件和目录。

> 如图，在下载镜像时，也是一层一层下载的
> ![img](C:\Files\code\Learning\Docker\images\22fe564d9ed93e3961864acfe6d1c660_693x182.png)

## **Docker镜像的核心原理二：镜像结构**

​    要了解docker的镜像结构，需要先对linux的文件系统结构有所了解。

#### **linux文件系统结构**

​    Linux 文件系统由 `bootfs`和 `rootfs` 两部分组成。
​    bootfs(boot file system) 主要包含 bootloader 和 kernel，bootloader 主要是引导加载 kernel(内核)，当 kernel 被加载到内存中后 bootfs 就被 umount (卸载)了。
​    rootfs (root file system) 包含的就是典型 Linux 系统中的 /dev，/proc，/bin，/etc 等标准目录和文件。rootfs就是各种Linux发行版。比如redcat、centOS。
![img](C:\Files\code\Learning\Docker\images\05c2ac5198f3a8be072c4a8f35fc5eb3_681x464.png)

#### **docker镜像结构**

![img](C:\Files\code\Learning\Docker\images\04a4dc88522d13cba13089bcca714f41_430x324.png)
    docker的分层镜像结构如图所示，镜像的最底层必须是一个启动文件系统（`bootfs`）的镜像层。`bootfs`的上层镜像称为根镜像（`rootfs`）或者基础镜像（`Base Image`)，它一般是操作系统，比如centos、debian或者Ubuntu。
    用户的镜像必须构建在基础镜像之上。如图所示， emacs镜像层就是在基础镜像上安装emacs创建出来的镜像，在此基础上安装apache又创建了新的镜像层。利用这个新的镜像层启动的容器里运行的是一个已经安装好emacs和apache的Debian系统。

#### **docker镜像分层的理解**

查看镜像分层方式可以通过`docker image inspect [IMAGE]`命令。其中RootFS部分则是表示了分层信息。

```
[root@iZbp1bum6107bp8mgzkeunZ ~]# docker image inspect redis
[
    {
        "Id": "sha256:53aa81e8adfa939348cd4c846c0ab682b16dc7641714e36bfc57b764f0b947dc",
        ...
        ...
        "RootFS": {
            "Type": "layers",
            "Layers": [
                "sha256:ad6562704f3759fb50f0d3de5f80a38f65a85e709b77fd24491253990f30b6be",
                "sha256:49cba0f0997b2bb3a24bcfe71c7cbd6e9f6968ef7934e3ad56b0f1f9361b6b91",
                "sha256:309498e524b3e2da1f036d00cd5155e0b74cf9e1d964a3636c8ed63ca4a00d43",
                "sha256:f7c9b429437f7ada2d3d455ac4ea90ff38e0cb7ef2551b08d152264b74116309",
                "sha256:4dabdd56bbf16307e2328cb6ed1d42b0bb9b8f40551421271c0b38dc9a685dcc",
                "sha256:ea450ad6ef893e998f88a35dc9cc22f952c62b88d58f948344cf4eda1a6264fc"
            ]
        },
    }
]
```

​    所有的Docker镜像都起始于一个基础镜像层，当镜像修改或者新增新的内容时，就会在当前镜像层之上，创建新的镜像层。**即在添加额外的镜像层的同时，镜像始终保持是当前所有镜像的组合**。docker通过存储引擎（新版本采用快照机制）的方式实现镜像层堆栈，并保证多个镜像层对外展示为统一的文件系统。示例：
![img](C:\Files\code\Learning\Docker\images\15280ae5bbf2f1631907fe4266341647_547x379.png)
​    这个镜像中包含了三个镜像层，第一层有三个文件，第二层也有三个文件，第三层镜像中仅有一个文件，且这个文件是对第二层镜像中的文件5的一个更新版本。在这种情况下，上层镜像层中的文件会覆盖底层镜像层的文件，这样就使得文件的更新版本作为一个新的镜像层添加到镜像当中。
​    最后docker通过存储引擎将所有镜像层堆叠并合并，对外提供统一的视图。

![img](C:\Files\code\Learning\Docker\images\ff2301d18d0c7bf014cbc92be28985a6_626x180.png)

# docker 镜像的使用

## 获取docker 镜像

```shell
# docker search 镜像:版本
# docker image ls #查看本地的镜像
# docker pull 镜像 # 下载镜像
# docker info # 查看镜像相关信息

# 镜像保存的地址
root@hcss-ecs-f139:/home/jszhou# ls /var/lib/docker/image/overlay2/imagedb/content/sha256/
a6bd71f48f6839d9faae1f29d3babef831e76bc213107682c5cc80f0cbb30866
afb6fca791e071c66276202f8efca5ce3d3dc4fb218bcddff1bc565d981ddd1e
e4c58958181a5925816faa528ce959e487632f4cfd192f8132f71b32df2744b4
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY   TAG        IMAGE ID       CREATED       SIZE
nginx        latest     a6bd71f48f68   7 days ago    187MB
ubuntu       latest     e4c58958181a   7 weeks ago   77.8MB
centos       7.8.2003   afb6fca791e0   3 years ago   203MB

# 启动容器
# -it 通过交互式启动容器
# --rm 退出时删除容器

root@hcss-ecs-f139:/home/jszhou# docker run -it --rm centos:7.8.2003 bash
[root@d09cd261a1ca /]#
```

## 查看镜像

```shell 
docker images 
docker image ls 

docker images 镜像ID
docker images tags

#列出镜像id 
docker images -q 

# 格式化显示镜像信息
root@hcss-ecs-f139:/home/jszhou# docker ps --format "table 容器ID：{{.ID}}\n名称：{{.Names}}\n镜像：{{.Image}}\n状态：{{.Status}}\n端口：{{.Ports}}\n"
容器ID：84f0794afaba
名称：epic_proskuriakova
镜像：a6bd71f48f68
状态：Up 16 minutes
端口：0.0.0.0:80->80/tcp, :::80->80/tcp

# 表格显示

```

## 删除镜像

```shell
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY               TAG        IMAGE ID       CREATED       SIZE
nginx                    latest     a6bd71f48f68   7 days ago    187MB
ubuntu                   latest     e4c58958181a   7 weeks ago   77.8MB
centos                   7.8.2003   afb6fca791e0   3 years ago   203MB
chenlicn163/hello-word   latest     3ed90589c0b6   4 years ago   844kB
root@hcss-ecs-f139:/home/jszhou# docker rmi 3ed90589c0b6
Untagged: chenlicn163/hello-word:latest
Untagged: chenlicn163/hello-word@sha256:2b7b800ab2ef8f0c2c3331ee170af82c3613b167d20e56d1884dca4772fee6c3
Deleted: sha256:3ed90589c0b616588075b9b95a5e3dc65af7b05bd660d35f54a37f2473facea9
Deleted: sha256:6b73d082fc935f44cdd92c23bcabfd9ceee6dd4430ef4449d07d1e792059f84c
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY   TAG        IMAGE ID       CREATED       SIZE
nginx        latest     a6bd71f48f68   7 days ago    187MB
ubuntu       latest     e4c58958181a   7 weeks ago   77.8MB
centos       7.8.2003   afb6fca791e0   3 years ago   203MB
```

## 镜像管理

```shell 
docker rmi `docker images -aq`
# rmi 删除的后续的镜像
# a 列举出全部的镜像，q 列举出镜像的id

# 导出镜像
root@hcss-ecs-f139:/home/jszhou# docker image save centos:7.8.2003 > ./centos.7.8.2003.tgz
root@hcss-ecs-f139:/home/jszhou# ls
centos.7.8.2003.tgz  cpp  docker

# 导入镜像
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY   TAG       IMAGE ID       CREATED       SIZE
nginx        latest    a6bd71f48f68   7 days ago    187MB
ubuntu       latest    e4c58958181a   7 weeks ago   77.8MB
centos       latest    5d0da3dc9764   2 years ago   231MB
root@hcss-ecs-f139:/home/jszhou# docker image load -i ./centos.7.8.2003.tgz
fb82b029bea0: Loading layer [==================================================>]  211.1MB/211.1MB
Loaded image: centos:7.8.2003
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY   TAG        IMAGE ID       CREATED       SIZE
nginx        latest     a6bd71f48f68   7 days ago    187MB
ubuntu       latest     e4c58958181a   7 weeks ago   77.8MB
centos       latest     5d0da3dc9764   2 years ago   231MB
centos       7.8.2003   afb6fca791e0   3 years ago   203MB

# 查看镜像详细信息
root@hcss-ecs-f139:/home/jszhou# docker image inspect 5d0da3dc9764
[
    {
        "Id": "sha256:5d0da3dc976460b72c77d94c8a1ad043720b0416bfc16c52c45d4847e53fadb6",
        "RepoTags": [
            "centos:latest"
        ],
        "RepoDigests": [
            "centos@sha256:a27fd8080b517143cbbbab9dfb7c8571c40d67d534bbdee55bd6c473f432b177"
        ],
        "Parent": "",
        "Comment": "",
        "Created": "2021-09-15T18:20:05.184694267Z",
        "Container": "9bf8a9e2ddff4c0d76a587c40239679f29c863a967f23abf7a5babb6c2121bf1",
        "ContainerConfig": {
            "Hostname": "9bf8a9e2ddff",
            "Domainname": "",
            "User": "",
            "AttachStdin": false,
            "AttachStdout": false,
            "AttachStderr": false,
            "Tty": false,
            "OpenStdin": false,
            "StdinOnce": false,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
            ],
            "Cmd": [
                "/bin/sh",
                "-c",
                "#(nop) ",
                "CMD [\"/bin/bash\"]"
            ],
            "Image": "sha256:f5b050f177fd426be8fe998a8ecf3fb1858d7e26dff4080b29a327d1bd5ba422",
            "Volumes": null,
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": {
                "org.label-schema.build-date": "20210915",
                "org.label-schema.license": "GPLv2",
                "org.label-schema.name": "CentOS Base Image",
                "org.label-schema.schema-version": "1.0",
                "org.label-schema.vendor": "CentOS"
            }
        },
        "DockerVersion": "20.10.7",
        "Author": "",
        "Config": {
            "Hostname": "",
            "Domainname": "",
            "User": "",
            "AttachStdin": false,
            "AttachStdout": false,
            "AttachStderr": false,
            "Tty": false,
            "OpenStdin": false,
            "StdinOnce": false,
            "Env": [
                "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
            ],
            "Cmd": [
                "/bin/bash"
            ],
            "Image": "sha256:f5b050f177fd426be8fe998a8ecf3fb1858d7e26dff4080b29a327d1bd5ba422",
            "Volumes": null,
            "WorkingDir": "",
            "Entrypoint": null,
            "OnBuild": null,
            "Labels": {
                "org.label-schema.build-date": "20210915",
                "org.label-schema.license": "GPLv2",
                "org.label-schema.name": "CentOS Base Image",
                "org.label-schema.schema-version": "1.0",
                "org.label-schema.vendor": "CentOS"
            }
        },
        "Architecture": "amd64",
        "Os": "linux",
        "Size": 231268856,
        "VirtualSize": 231268856,
        "GraphDriver": {
            "Data": {
                "MergedDir": "/var/lib/docker/overlay2/decb815b84589b7eddd519272316104653392bb3a64a49a0303c6d854e3e57f3/merged",
                "UpperDir": "/var/lib/docker/overlay2/decb815b84589b7eddd519272316104653392bb3a64a49a0303c6d854e3e57f3/diff",
                "WorkDir": "/var/lib/docker/overlay2/decb815b84589b7eddd519272316104653392bb3a64a49a0303c6d854e3e57f3/work"
            },
            "Name": "overlay2"
        },
        "RootFS": {
            "Type": "layers",
            "Layers": [
                "sha256:74ddd0ec08fa43d09f32636ba91a0a3053b02cb4627c35051aff89f853606b59"
            ]
        },
        "Metadata": {
            "LastTagTime": "0001-01-01T00:00:00Z"
        }
    }
]
```

> 在学习使用 docker 技术过程中，基于 centos 镜像自定义新的镜像，其中基础镜像 centos 需要提前安装好 [vim](https://so.csdn.net/so/search?q=vim&spm=1001.2101.3001.7020) 和 net-tools，然而在刚开始通过 `yum -y install vim` 安装 vim 时，便出现了错误提示信息：
>
> ![2e718f6de6d94987ae2f2182c528d9c8.png](https://ucc.alicdn.com/pic/developer-ecology/ai6hinuswuadk_40f69cdd4d6f4efea8bd3e8218873d66.png)
>
> ```
> Error: Failed to download metadata for repo 'appstream': Cannot prepare internal mirrorlist: No URLs in mirrorlist
> ```
>
> ✨上面的报错信息意思是，从仓库 ‘appstream’ 下载元数据失败：由于镜像列表中没有 URL，不能准备内部镜像列表。
>
> 
>
> 🥎问题分析：
>
> 
>
> ✨第一种可能的情况便是网络连接问题。检查是否可以连接外部网络，可以使用 ping baidu.com 查看是否有丢包情况。如果丢包，则进一步检查网络连接是否正常；如果没有丢包，继续阅读下文
>
> ✨那么第二种情况，便是 CentOS 已经停止维护的问题。2020 年 12 月 8 号，CentOS 官方宣布了停止维护 CentOS Linux 的计划，并推出了 CentOS Stream 项目，CentOS Linux 8 作为 RHEL 8 的复刻版本，生命周期缩短，于 2021 年 12 月 31 日停止更新并停止维护（EOL），更多的信息可以查看 CentOS 官方公告。如果需要更新 CentOS，需要将镜像从 mirror.centos.org 更改为 vault.centos.org
>
> 🥎那么针对上面提到的第二种情况，给出的解决方法如下：
>
> 
>
> 🔔 首先，进入到 yum 的 repos 目录
>
> ```
> cd /etc/yum.repos.d/
> ```
>
> 🔔其次，修改 centos 文件内容
>
> ```
> sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
> sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*
> ```
>
> - 🔔 **然后**，生成缓存更新（第一次更新，速度稍微有点慢，耐心等待两分钟左右）
>
> ```
> yum makecache
> ```
>
> - 🔔 **最后**，运行 yum update 并重新安装 vim
>
> ```
> yum update -y
> yum -y install vim
> ```

## docker 生命周期

![在这里插入图片描述](C:\Files\code\Learning\Docker\images\20210323151515143.png)

 Docker 容器的生命周期包括以下几个关键阶段：

- 创建（Create）：使用 Docker 镜像创建容器实例。通过运行 docker create 或 docker run 命令，Docker 引擎会根据指定的镜像创建一个容器，并分配一个唯一的容器 ID。

- **启动（Start）：**将创建的容器实例启动起来。通过运行 docker start 命令，Docker 引擎会根据容器 ID 找到相应的容器，并将其启动起来。在启动过程中，Docker 引擎会执行容器定义中指定的命令或程序。

- **运行（Run）：**在容器内执行指定的命令或程序。可以通过 docker run 命令一次性创建并启动容器，并指定要在容器内运行的命令。运行过程中，可以与容器进行交互、查看日志等操作。

- **暂停（Pause）：**暂停容器的执行。通过运行 docker pause 命令，Docker 引擎会暂停容器的执行，即冻结容器的状态。此时，容器的文件系统和内存状态仍然保留，但容器内的进程将被暂停。

- **恢复（Unpause）：**从暂停状态恢复容器的执行。通过运行 docker unpause 命令，Docker 引擎会从暂停状态恢复容器的执行，使容器内的进程继续运行。

- **停止（Stop）：**停止容器的执行。通过运行 docker stop 命令，Docker 引擎会尝试优雅地停止容器内的进程，并将容器的状态设置为停止状态。如果在一定时间内容器无法正常停止，可以使用 docker kill 命令强制终止容器。

- **重启（Restart）：**重启已停止的容器。通过运行 docker restart 命令，Docker 引擎会停止并重新启动容器，可以为容器指定重启策略。

- **删除（Remove）：**删除容器实例。使用 docker rm 命令可以删除已停止的容器。删除容器时，可以选择保留容器的数据卷（docker rm -v）或强制删除容器（docker rm -f）。

# docker 容器管理

```shell 
# 运行一个挂掉的容器
docker run 镜像名

# 运行一个容器，并且执行某个命令
docker run -it contos bash 

# 运行一个容器，并且运行了某个程序
docker run centos ping www.baidu.com 

# 运行一个活着的容器
# -d 让程序再后台运行
root@hcss-ecs-f139:/home/jszhou# docker run -d centos ping www.baidu.com
ceb8a039fd7d8139208d8e5c98bf58887d2393bdeba43aef6499a90a1e4a94cf
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY   TAG        IMAGE ID       CREATED       SIZE
nginx        latest     a6bd71f48f68   7 days ago    187MB
ubuntu       latest     e4c58958181a   7 weeks ago   77.8MB
centos       latest     5d0da3dc9764   2 years ago   231MB
centos       7.8.2003   afb6fca791e0   3 years ago   203MB
root@hcss-ecs-f139:/home/jszhou# docker ps
CONTAINER ID   IMAGE          COMMAND                  CREATED             STATUS             PORTS
 NAMES
ceb8a039fd7d   centos         "ping www.baidu.com"     27 seconds ago      Up 25 seconds
 funny_lamarr
84f0794afaba   a6bd71f48f68   "/docker-entrypoint.…"   About an hour ago   Up About an hour   0.0.0.0:80->80/tcp, :::80->80/tcp   epic_proskuriakova
root@hcss-ecs-f139:/home/jszhou# docker stop ceb8a039fd7d
ceb8a039fd7d

# docker run -d --rm --name 镜像名
# --rm  运行结束之后，删除相对应的容器记录
# --name 给容器起名字

# 查看容器 日志
docker logs 容器id 

# 进入正在运行的容器空间内
docker exec -it 容器id bash

# 查看容器的详细记录
docker container inspect 镜像id 

# 容器的端口映射
docker run -d -it -p XX:XX 镜像id 

# 查看容器的端口映射情况
docker port 容器id

# 容器的提交
root@hcss-ecs-f139:/home/jszhou# docker ps -a
CONTAINER ID   IMAGE             COMMAND                  CREATED              STATUS                           PORTS     NAMES
88bae30d01d4   centos:7.8.2003   "bash"                   About a minute ago   Exited (130) 7 seconds ago                 nervous_swirles
root@hcss-ecs-f139:/home/jszhou# docker commit 88bae30d01d4 jszhou/centos_vim-7.8.2003
sha256:f105439b5cda41f511aa25fc546ca73fbaeeee0fa5e2c14d2ad67e9ac096a9ca
root@hcss-ecs-f139:/home/jszhou# docker images
REPOSITORY                   TAG        IMAGE ID       CREATED          SIZE
jszhou/centos_vim-7.8.2003   latest     f105439b5cda   19 seconds ago   488MB
nginx                        latest     a6bd71f48f68   7 days ago       187MB
ubuntu                       latest     e4c58958181a   7 weeks ago      77.8MB
centos                       latest     5d0da3dc9764   2 years ago      231MB
centos                       7.8.2003   afb6fca791e0   3 years ago      203MB

```

# docker file 实战

> 任务： 安装一个mysql

dockerfile 的主要组成部分：

当然可以！下面是一个基本的Dockerfile模板，你可以根据自己的需求进行修改：

```dockerfile
# 设置基础镜像
FROM 镜像名称:版本号

# 设置工作目录
WORKDIR /app

# 将本地文件复制到镜像中
COPY . /app

# 安装依赖或运行命令
RUN 命令1
RUN 命令2

# 暴露容器的端口
EXPOSE 端口号

# 设置容器启动时执行的命令
CMD ["启动命令"]
```

请注意替换以下内容：

- `镜像名称:版本号`：根据你需要的基础镜像选择合适的名称和版本号，例如 `ubuntu:latest`。
- `/app`：设置你的工作目录，可以根据自己的需求进行修改。
- `命令1`和`命令2`：根据你的需求安装依赖或运行其他命令。
- `端口号`：指定容器暴露的端口号，例如 `80`。
- `启动命令`：设置容器启动时要执行的命令，例如 `python app.py`。

## 实例1 docker运行nginx

>  通过dockerfile 实现nginx 部署

```shell
root@hcss-ecs-f139:/home/jszhou/docker# vim Dockerfile
# 写入以下内容
FROM nginx
RUN echo "<meta charset=utf8> docker 运行 nginx 服务。" > /usr/share/nginx/html/index.html

root@hcss-ecs-f139:/home/jszhou/docker# docker build .
[+] Building 0.4s (4/5)
[+] Building 0.6s (4/5)
[+] Building 0.7s (4/5)
[+] Building 0.9s (5/5)
[+] Building 0.9s (6/6) FINISHED
 => [internal] load build definition from Dockerfile   0.1s
 => => transferring dockerfile: 145B                   0.0s
 => [internal] load .dockerignore                      0.1s
 => => transferring context: 2B                        0.0s
 => [internal] load metadata for docker.io/library/nginx:latest  0.0s
 => [1/2] FROM docker.io/library/nginx                             0.1s
 => [2/2] RUN echo "<meta charset=utf8> docker 运行 nginx 服务。" > /usr/share/nginx/html/index.html                             0.6s
 => exporting to image                                       0.0s
 => => exporting layers                                      0.0s
 => => writing image sha256:6f037cae54b523c5d548f89a00db1f3e457d0197aec5754bba5d222a221a2aec                                0.0s
root@hcss-ecs-f139:/home/jszhou/docker# docker images
REPOSITORY                   TAG        IMAGE ID       CREATED             SIZE
<none>                       <none>     6f037cae54b5   23 seconds ago      187MB
jszhou/centos_vim-7.8.2003   latest     f105439b5cda   About an hour ago   488MB
nginx                        latest     a6bd71f48f68   8 days ago          187MB
ubuntu                       latest     e4c58958181a   7 weeks ago         77.8MB
centos                       latest     5d0da3dc9764   2 years ago         231MB
centos                       7.8.2003   afb6fca791e0   3 years ago         203MB
root@hcss-ecs-f139:/home/jszhou/docker# docker tag 6f037cae54b5 my_nginx
root@hcss-ecs-f139:/home/jszhou/docker# docker images
REPOSITORY                   TAG        IMAGE ID       CREATED             SIZE
my_nginx                     latest     6f037cae54b5   52 seconds ago      187MB
jszhou/centos_vim-7.8.2003   latest     f105439b5cda   About an hour ago   488MB
nginx                        latest     a6bd71f48f68   8 days ago          187MB
ubuntu                       latest     e4c58958181a   7 weeks ago         77.8MB
centos                       latest     5d0da3dc9764   2 years ago         231MB
centos                       7.8.2003   afb6fca791e0   3 years ago         203MB

# 检查容器运行情况，检查端口运行情况
root@hcss-ecs-f139:/home/jszhou/docker# docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
root@hcss-ecs-f139:/home/jszhou/docker# netstat -tunlp
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 127.0.0.53:53           0.0.0.0:*               LISTEN      550/systemd-resolve
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      1483/sshd
tcp6       0      0 :::22                   :::*                    LISTEN      1483/sshd
udp        0      0 0.0.0.0:5353            0.0.0.0:*                           19297/avahi-daemon:
udp        0      0 127.0.0.1:323           0.0.0.0:*                           989/chronyd
udp        0      0 0.0.0.0:34458           0.0.0.0:*                           19297/avahi-daemon:
udp        0      0 127.0.0.53:53           0.0.0.0:*                           550/systemd-resolve
udp        0      0 0.0.0.0:68              0.0.0.0:*                           1045/dhclient
udp6       0      0 :::5353                 :::*                                19297/avahi-daemon:
udp6       0      0 ::1:323                 :::*                                989/chronyd
udp6       0      0 :::46763                :::*                                19297/avahi-daemon:

root@hcss-ecs-f139:/home/jszhou/docker# docker images
REPOSITORY                   TAG        IMAGE ID       CREATED             SIZE
my_nginx                     latest     6f037cae54b5   4 minutes ago       187MB
jszhou/centos_vim-7.8.2003   latest     f105439b5cda   About an hour ago   488MB
nginx                        latest     a6bd71f48f68   8 days ago          187MB
ubuntu                       latest     e4c58958181a   7 weeks ago         77.8MB
centos                       latest     5d0da3dc9764   2 years ago         231MB
centos                       7.8.2003   afb6fca791e0   3 years ago         203MB
root@hcss-ecs-f139:/home/jszhou/docker# docker run -d -p 80:80 my_nginx
c7e11d556a90942dfe01f3767e9c1031223999265f7979b9a8f92c489eb8bd8e
root@hcss-ecs-f139:/home/jszhou/docker# docker ps
CONTAINER ID   IMAGE      COMMAND                  CREATED         STATUS         PORTS                               NAMES
c7e11d556a90   my_nginx   "/docker-entrypoint.…"   4 seconds ago   Up 3 seconds   0.0.0.0:80->80/tcp, :::80->80/tcp   naughty_gauss

```

![image-20231129170618045](C:\Files\code\Learning\Docker\images\image-20231129170618045.png)

## docker 命令详解

### docker COPY

`COPY` 命令用于将本地文件或目录复制到 Docker 镜像中的指定位置。它的基本语法如下：

```dockerfile
COPY <源路径> <目标路径>
```

其中：
- `<源路径>` 是主机上的文件或目录的路径，可以是相对路径或绝对路径。
- `<目标路径>` 是镜像内部的目标路径，表示文件或目录在镜像中的位置。

下面是一些 `COPY` 命令的常见使用方式：

1. 复制单个文件到镜像中：
```dockerfile
COPY app.py /app/app.py
```
上述命令将主机上的 `app.py` 文件复制到镜像内的 `/app/app.py` 路径。

2. 复制目录到镜像中：
```dockerfile
COPY src/ /app/src/
```
上述命令将主机上的 `src` 目录复制到镜像内的 `/app/src/` 路径。

3. 使用通配符复制多个文件：
```dockerfile
COPY *.txt /app/
```
上述命令将主机上所有以 `.txt` 结尾的文件复制到镜像内的 `/app/` 路径。

4. 复制远程文件到镜像中：
```dockerfile
COPY http://example.com/file.txt /app/
```
上述命令将从远程 URL 下载 `file.txt` 文件，并将其复制到镜像内的 `/app/` 路径。

值得注意的是，`COPY` 命令是在构建镜像的过程中执行的，它将文件复制到镜像中的指定位置。如果文件在构建过程中发生更改，需要重新构建镜像才能反映更改。

此外，`COPY` 命令还支持一些选项，例如：
- `--chown=<用户:组>`：指定复制文件时的用户和组。
- `--from=<源镜像>`：从另一个镜像中复制文件。

你可以根据自己的需求使用 `COPY` 命令来将所需的文件或目录复制到 Docker 镜像中。

### docker ADD

`ADD` 命令与 `COPY` 命令类似，都用于将文件从主机复制到 Docker 镜像中。但是，`ADD` 命令相对于 `COPY` 命令具有更多的功能和灵活性。它的基本语法如下：

```dockerfile
ADD <源路径> <目标路径>
```

与 `COPY` 命令相同，`<源路径>` 是主机上的文件或目录的路径，可以是相对路径或绝对路径。`<目标路径>` 是镜像内部的目标路径，表示文件或目录在镜像中的位置。

除了复制文件之外，`ADD` 命令还支持以下功能：

1. 自动解压缩压缩文件：
```dockerfile
ADD archive.tar.gz /app/
```
如果 `archive.tar.gz` 是一个压缩文件（如 `.tar.gz`、`.tar.bz2`、`.tar.xz`、`.tar`、`.gz`、`.bz2`、`.xz`），`ADD` 命令会自动解压缩该文件，并将解压后的文件复制到目标路径。

2. 复制远程文件到镜像中：
```dockerfile
ADD http://example.com/file.txt /app/
```
与 `COPY` 命令不同，`ADD` 命令可以从远程 URL 下载文件，并将其复制到镜像中的目标路径。

3. 增量复制：
```dockerfile
ADD src/*.txt /app/
```
如果 `<源路径>` 是一个文件通配符，而 `<目标路径>` 是一个目录，`ADD` 命令会将匹配的文件复制到目标路径。这意味着如果只有源目录中的某些文件发生更改，只有这些文件会被复制到镜像中，而不是整个目录。

需要注意的是，由于 `ADD` 命令的功能较多，它在某些情况下可能不太适合纯粹的文件复制操作。在大多数情况下，如果只需复制文件或目录，建议使用 `COPY` 命令。只有在确实需要 `ADD` 命令的附加功能时才使用它。

无论是使用 `COPY` 还是 `ADD` 命令，都可以根据你的需求将所需的文件或目录复制到 Docker 镜像中。

### docker CMD

`CMD` 命令用于设置容器启动时要执行的命令或程序。它有多种形式，可以指定命令和参数的方式来定义容器的默认行为。

以下是 `CMD` 命令的几种常见形式：

1. 命令数组形式：
```dockerfile
CMD ["executable", "param1", "param2"]
```
这种形式适用于执行可执行文件或脚本，并传递参数。例如：
```dockerfile
CMD ["python", "app.py"]
```
上述命令会在容器启动时执行 `python app.py`，其中 `python` 是可执行文件，`app.py` 是参数。

2. 字符串形式：
```dockerfile
CMD command param1 param2
```
这种形式适用于执行命令行命令。例如：
```dockerfile
CMD python app.py
```
上述命令会在容器启动时执行 `python app.py`。

请注意，在使用字符串形式时，Docker 会自动在命令前面添加 `/bin/sh -c`，因此可以执行类似于 `bash` 的命令。

3. 混合形式：
```dockerfile
CMD ["executable", "param1", "param2"] or CMD command param1 param2
```
这种形式结合了命令数组形式和字符串形式，可以在容器启动时执行可执行文件或命令行命令。例如：
```dockerfile
CMD ["python", "-u", "app.py"] or CMD python -u app.py
```
上述命令会在容器启动时执行 `python -u app.py`。

需要注意的是，Dockerfile 中只能有一个 `CMD` 命令。如果在同一个 Dockerfile 中指定了多个 `CMD` 命令，只有最后一个 `CMD` 命令会生效。

`CMD` 命令定义了容器的默认执行命令或程序。当使用 `docker run` 命令启动容器时，如果没有指定要执行的命令，容器将按照 `CMD` 命令中定义的方式执行默认命令。

例如，如果 Dockerfile 中定义了以下 `CMD` 命令：
```dockerfile
CMD ["python", "app.py"]
```
则在启动容器时，可以省略要执行的命令：
```shell
docker run <image_name>
```
容器将自动执行 `python app.py`。

通过合理使用 `CMD` 命令，可以定义容器的默认行为，使其在启动时执行所需的命令或程序。

### docker ENTRYPOINT 

`ENTRYPOINT` 是 Dockerfile 中的指令，用于设置容器启动时要执行的命令或程序。与 `CMD` 类似，`ENTRYPOINT` 也可以定义容器的默认执行命令，但有一些关键的区别。

`ENTRYPOINT` 的语法有两种形式：

1. 字符串形式：
```dockerfile
ENTRYPOINT command param1 param2
```
这种形式适用于执行命令行命令。例如：
```dockerfile
ENTRYPOINT echo "Hello, Docker!"
```
上述命令会在容器启动时执行 `echo "Hello, Docker!"`。

2. 命令数组形式：
```dockerfile
ENTRYPOINT ["executable", "param1", "param2"]
```
这种形式适用于执行可执行文件或脚本，并传递参数。例如：
```dockerfile
ENTRYPOINT ["python", "app.py"]
```
上述命令会在容器启动时执行 `python app.py`，其中 `python` 是可执行文件，`app.py` 是参数。

与 `CMD` 不同，`ENTRYPOINT` 的参数不会被覆盖，而是会被附加到命令中。这意味着在运行容器时，可以通过命令行参数来扩展 `ENTRYPOINT` 指定的命令。

例如，如果 Dockerfile 中定义了以下 `ENTRYPOINT`：
```dockerfile
ENTRYPOINT ["python", "app.py"]
```
那么在启动容器时，可以执行以下命令来覆盖默认的参数：
```shell
docker run <image_name> arg1 arg2
```
上述命令将执行 `python app.py arg1 arg2`，其中 `arg1` 和 `arg2` 是命令行参数，它们会附加到 `ENTRYPOINT` 指定的命令后面。

需要注意的是，在 Dockerfile 中只能有一个 `ENTRYPOINT` 指令。如果在同一个 Dockerfile 中指定了多个 `ENTRYPOINT`，只有最后一个 `ENTRYPOINT` 指令会生效。

通过合理使用 `ENTRYPOINT`，可以设置容器的默认执行命令或程序，并在运行容器时灵活地扩展或覆盖默认命令和参数。

### docker env 

在 Docker 中，`env` 是一个用于设置环境变量的参数。通过设置环境变量，可以在容器内部配置和传递各种配置项、密钥、连接字符串等信息。

在 Dockerfile 中，可以使用 `ENV` 指令来设置环境变量。它有两种常见的形式：

1. 单独设置一个环境变量：
```dockerfile
ENV key=value
```
其中 `key` 是环境变量的名称，`value` 是环境变量的值。例如：
```dockerfile
ENV DB_HOST=localhost
```
上述命令将设置一个名为 `DB_HOST` 的环境变量，其值为 `localhost`。

2. 设置多个环境变量：
```dockerfile
ENV key1=value1 \
    key2=value2 \
    key3=value3
```
可以使用反斜杠（`\`）将多个环境变量连接在一起，以便于阅读和维护。例如：
```dockerfile
ENV DB_HOST=localhost \
    DB_PORT=3306 \
    DB_USER=admin \
    DB_PASSWORD=secret
```
上述命令将设置多个环境变量，包括 `DB_HOST`、`DB_PORT`、`DB_USER` 和 `DB_PASSWORD`。

在容器运行时，可以使用 `-e` 或 `--env` 参数来设置环境变量的值。例如：
```shell
docker run -e DB_HOST=example.com -e DB_PORT=1234 <image_name>
```
上述命令将在运行容器时设置 `DB_HOST` 和 `DB_PORT` 的值。

容器内的应用程序可以读取这些环境变量，并根据环境变量的值来进行配置和运行。

通过使用环境变量，可以使容器具有更好的可配置性和灵活性，而无需在容器镜像中硬编码配置信息。这样可以更方便地在不同环境中部署和运行容器。

### docker ARG

在 Docker 中，`ARG` 是一个用于定义构建时参数的指令。它允许在构建过程中传递参数，并且可以在 Dockerfile 中引用这些参数。

`ARG` 指令有两种常见的形式：

1. 单独定义一个参数：
```dockerfile
ARG key=value
```
其中 `key` 是参数的名称，`value` 是参数的默认值。例如：
```dockerfile
ARG VERSION=latest
```
上述命令定义了一个名为 `VERSION` 的参数，并设置默认值为 `latest`。

2. 定义多个参数：
```dockerfile
ARG key1=value1 \
    key2=value2 \
    key3=value3
```
可以使用反斜杠（`\`）将多个参数连接在一起。例如：
```dockerfile
ARG USER=admin \
    PASSWORD=secret
```
上述命令定义了多个参数，包括 `USER` 和 `PASSWORD`。

在构建镜像时，可以通过 `--build-arg` 参数来传递参数的值。例如：
```shell
docker build --build-arg VERSION=1.0 .
```
上述命令将传递一个名为 `VERSION` 的参数，其值为 `1.0`。

在 Dockerfile 中，可以使用 `${key}` 的形式引用参数的值。例如：
```dockerfile
FROM ubuntu:${VERSION}
```
上述命令使用了之前定义的 `VERSION` 参数来指定基础镜像的版本。

需要注意的是，`ARG` 定义的参数只在构建过程中可用，而在容器运行时不可用。如果需要在容器运行时传递参数，应使用环境变量（`ENV`）。

通过使用 `ARG` 参数，可以在构建镜像过程中传递和使用参数，以实现更灵活的镜像构建。这样可以在构建过程中根据需要更改参数的值，而无需修改 Dockerfile。

### ARG 与ENV 的区别

`ARG` 和 `ENV` 是 Dockerfile 中用于定义参数和环境变量的指令，它们有一些区别和用途上的差异。

区别如下：

1. 作用域不同：
   - `ARG` 定义的参数只在构建过程中可用，用于在构建时传递参数值。
   - `ENV` 定义的环境变量在容器运行时可用，用于配置容器内部的环境。

2. 可见性不同：
   - `ARG` 定义的参数只在构建过程中可见，对于构建过程中的指令（例如 `FROM`、`RUN`、`COPY` 等）是可用的，但对于构建后的镜像中的运行时进程是不可见的。
   - `ENV` 定义的环境变量在构建过程中和容器运行时都可见，对于构建过程中的指令和容器运行时的进程都是可用的。

3. 默认值处理不同：
   - `ARG` 可以在 Dockerfile 中为参数定义一个默认值，如果在构建命令中未提供该参数的值，则使用默认值。
   - `ENV` 在 Dockerfile 中设置环境变量时，会直接将指定的值分配给环境变量，并没有默认值的概念。

4. 可变性不同：
   - `ARG` 允许在构建过程中通过 `--build-arg` 参数来传递参数值，使得构建过程中的参数可以根据需要进行更改。
   - `ENV` 在构建过程中是不可变的，环境变量的值在镜像构建期间确定，并且在容器运行时无法更改。

综上所述，`ARG` 用于在构建过程中传递参数值，而 `ENV` 用于在容器运行时配置容器内部的环境。它们在作用域、可见性、默认值处理和可变性等方面有所不同，因此在使用时需要根据需求来选择合适的指令。

### docker VOLUME

`VOLUME` 是 Dockerfile 中的指令之一，用于在容器中创建一个或多个挂载点，并将其用作持久化存储。

`VOLUME` 的语法有两种形式：

1. 单个挂载点：
```dockerfile
VOLUME /path/to/directory
```
上述命令将在容器中创建一个挂载点，并将其指定为 `/path/to/directory`。这个挂载点可以用来存储容器内的数据，并且在容器重新创建时，之前的数据可以保持不变。

2. 多个挂载点：
```dockerfile
VOLUME /path/to/directory1 /path/to/directory2 ...
```
可以指定多个挂载点，用空格分隔。

在使用 `VOLUME` 指令后，Docker 会自动在容器内部创建对应的目录，并将其标记为挂载点。当容器运行时，可以使用 `-v` 或 `--volume` 参数将本地主机的目录或其他容器的挂载点与容器中的挂载点进行绑定。这样可以实现数据的持久化存储，并且可以在容器之间共享数据。

例如，可以使用以下命令来运行一个挂载了 `/data` 目录的容器：
```shell
docker run -v /host/data:/data <image_name>
```
上述命令将将主机上的 `/host/data` 目录与容器内的 `/data` 挂载点进行绑定。

需要注意的是，如果在 Dockerfile 中使用了 `VOLUME` 指令，但在运行容器时没有显式指定挂载点，Docker 会自动创建一个匿名挂载点。但是，为了更好地控制挂载点的位置和行为，建议在运行容器时显式指定挂载点。

`VOLUME` 指令用于在容器中创建挂载点，从而实现数据的持久化存储和容器之间的数据共享。这对于需要持久化存储数据的应用程序非常有用，可以保证数据在容器重新创建时不会丢失。

### docker EXPORT

`docker export` 是 Docker 命令行工具提供的一个命令，用于将容器的文件系统导出为一个 tar 归档文件。这个命令可以用于将容器的文件系统快照导出到本地主机，然后可以在其他地方导入为一个新的镜像或者用于备份和迁移容器。

`docker export` 的使用语法如下：
```shell
docker export [OPTIONS] CONTAINER_ID/CONTAINER_NAME > output.tar
```

其中，`OPTIONS` 可以是以下选项之一：
- `--output, -o`：指定输出文件路径（tar 归档文件），而不是将输出重定向到标准输出。
- `--change, -c`：在导出过程中应用修改指令（类似于 Dockerfile 中的指令），比如添加标签、更改元数据等。

`CONTAINER_ID/CONTAINER_NAME` 是要导出的容器的标识符或名称。

例如，要将名为 "mycontainer" 的容器的文件系统导出为 tar 归档文件，可以运行以下命令：
```shell
docker export -o mycontainer.tar mycontainer
```

执行完上述命令后，将在当前目录下生成名为 `mycontainer.tar` 的 tar 归档文件，其中包含了容器的文件系统快照。

需要注意的是，`docker export` 只导出容器的文件系统，不包括容器的元数据（如标签、环境变量、容器配置等）和运行时状态。因此，通过 `docker export` 导出的内容无法直接作为镜像来创建新的容器。如果需要导出整个容器（包括元数据和运行时状态），可以考虑使用 `docker save` 命令。

总而言之，`docker export` 是用于将容器文件系统导出为 tar 归档文件的命令，适用于备份、迁移和共享容器的文件系统快照。

### docker USER 

在使用 Docker 时，涉及到与 Docker 相关的用户权限问题。下面是一些与 Docker 用户相关的概念和操作：

1. Docker Daemon 用户：Docker Daemon 是在宿主机上运行的 Docker 后台进程。它通常以 root 用户身份运行，具有对 Docker 资源的完全访问权限。

2. Docker 用户组：在安装 Docker 时，会创建一个名为 `docker` 的用户组。只有属于 `docker` 用户组的用户才能直接运行 Docker 命令，而无需使用 `sudo`。

3. 使用 `sudo` 运行 Docker 命令：默认情况下，非 `root` 用户无法直接运行 Docker 命令。但可以通过在命令前加上 `sudo` 来以超级用户权限执行 Docker 命令，例如 `sudo docker run ...`。这要求用户具有适当的权限和配置。

4. 添加用户到 `docker` 用户组：为了允许普通用户直接运行 Docker 命令，可以将用户添加到 `docker` 用户组。可以使用以下命令将用户添加到 `docker` 组（使用 `sudo`）：
   ````shell
   sudo usermod -aG docker <username>
   ```
   其中 `<username>` 是要添加到 `docker` 组的用户名。添加用户到 `docker` 组后，需要重新登录才能使更改生效。

5. Docker 容器内的用户：在 Docker 容器内部，通常以非特权用户运行应用程序，以增加容器的安全性。这可以通过在 Dockerfile 中使用 `USER` 指令来指定容器内部运行应用程序的用户身份。

这些是与 Docker 用户相关的一些关键概念和操作。理解和正确配置 Docker 用户权限可以提高容器的安全性，并使用户能够方便地使用 Docker 命令。

## 实例2 部署一个网站

1、 编写flask代码,文件命名为 `app.py`

```python
#coding:utf8

from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
    return "flask demo"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
```

2、 编写dockerfile文件

```shell
FROM centos:7.8.2003
RUN curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo;
RUN curl -o /etc/yum.repos.d/epel.repo http://mirrors.aliyun.com/repo/epel-7.repo;
RUN yum makecache fast
RUN yum install python3-devel python3-pip -y
RUN pip3 install -i https://pypi.douban.com/simple flask
COPY app.py /opt
WORKDIR /opt
EXPOSE 8080
CMD ["python3", "app.py"]
```

当前文件目录为：

```shell
root@hcss-ecs-f139:/home/jszhou/docker# tree
.
├── app.py
└── Dockerfile

0 directories, 2 files
```

3、 依次执行如下命令：

```shell
# 构建镜像
docker build -t flash_web_demo --no-cache .

# 查看镜像文件
docker images
REPOSITORY       TAG        IMAGE ID       CREATED          SIZE
flash_web_demo   latest     22198d99a6f8   11 minutes ago   814MB
nginx            latest     a6bd71f48f68   8 days ago       187MB
ubuntu           latest     e4c58958181a   7 weeks ago      77.8MB
centos           latest     5d0da3dc9764   2 years ago      231MB
centos           7.8.2003   afb6fca791e0   3 years ago      203MB

# 运行镜像
docker run -d -p 8080:8080 flash_web_demo

# 查看容器是否启动成功
root@hcss-ecs-f139:/home/jszhou/docker# docker ps
CONTAINER ID   IMAGE            COMMAND            CREATED          STATUS          PORTS                                       NAMES
f99279f3d14a   flash_web_demo   "python3 app.py"   10 minutes ago   Up 10 minutes   0.0.0.0:8080->8080/tcp, :::8080->8080/tcp   strange_bartik

# 检查防火墙、安全组，最终能访问到资源
```

![image-20231129200634947](C:\Files\code\Learning\Docker\images\image-20231129200634947.png)

### 如何修改网站内容

1、修改源代码，重新构建镜像（略）

2、进入到容器内部，修改代码，重启容器

```shell
# 进入容器
docker exec -it f99279f3d14a bash

#修改代码
[root@f99279f3d14a opt]# vim app.py
[root@f99279f3d14a opt]# cat app.py
#coding:utf8

from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
    return "flask web demo"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
# 退出容器
[root@f99279f3d14a opt]# exit

# 重启容器
root@hcss-ecs-f139:/home/jszhou/docker# docker restart f99279f3d14a
f99279f3d14a
root@hcss-ecs-f139:/home/jszhou/docker# docker ps
CONTAINER ID   IMAGE            COMMAND            CREATED          STATUS          PORTS                                       NAMES
f99279f3d14a   flash_web_demo   "python3 app.py"   16 minutes ago   Up 51 seconds   0.0.0.0:8080->8080/tcp, :::8080->8080/tcp   strange_bartik
```

## docker commit命令参数

| 参数                 | 描述                             |
| -------------------- | -------------------------------- |
| -a, --author string  | 作者。                           |
| -c, --change list    | 应用 dockerfile 指令来创建图像。 |
| -m, --message string | 提交信息。                       |
| -p, --pause          | 提交期间暂停容器（默认为true）。 |
