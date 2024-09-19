# Git 学习笔记

## 创建一个新分支  
```
git branch <branch-name> 
```
执行该命令后，Git会在当前分支上创建一个新分支，但是它并不会自动切换到新分支上。

为了切换到新的分支并开始工作，可以使用 git checkout 命令。例如，要切换到名为 feature 的新分支，可以执行以下操作：
```
git checkout feature
```

## Git如何创建远程分支
要在Git中创建远程分支，首先需要在本地创建一个新的分支，然后将该分支推送到远程仓库。可以使用以下命令创建并推送新的分支：
```
git checkout -b <branch-name> 
git push origin <branch-name>
```
其中，```<branch-name> ```是新分支的名称。第一条命令创建一个新的本地分支并切换到该分支。第二个命令将该新分支推送到远程仓库。

## Git创建本地分支
要在Git中创建本地分支，可以使用 git branch 命令。它的语法如下：
```
git branch <branch-name>
```
其中，```<branch-name> ```是新分支的名称。执行该命令后，Git会在当前分支上创建一个新分支，但是它并不会自动切换到新分支上。

## Git创建分支并推送到远程
要在Git中创建新的分支并将该分支推送到远程仓库，可以使用以下命令：
```
git checkout -b <branch-name> 
git push -u origin <branch-name>
```
其中，```<branch-name> ```是新分支的名称。第一条命令创建一个新分支并切换到该分支，第二个命令将该新分支推送到远程仓库，并将远程分支设置为新分支的上游分支。

## Git如何切换本地分支
在Git中，要切换到另一个本地分支，可以使用 git checkout 命令。它的语法如下：
```
git checkout <branch-name>
```
其中，```<branch-name> ```是要切换到的本地分支的名称。执行该命令后，Git会切换到指定的本地分支。

## Git如何切换分支命令
要在Git中切换到另一个分支，可以使用 git checkout 命令。它的语法如下：
```
git checkout <branch-name>```
其中，```<branch-name>``` 是要切换到的分支的名称。执行该命令后，Git会切换到指定的分支。

## Git如何切换远程分支
如果要在Git中切换到远程分支，需要先将该分支拉取到本地仓库中。可以使用以下命令将远程分支拉取到本地分支：
```
git checkout -b <branch-name> origin/<branch-name>
```

其中，```<branch-name> ```是要切换到的远程分支的名称。该命令创建一个新分支并将远程分支拉取到本地分支中，然后切换到新分支。
```

## 删除历史记录

```shell
# 切换到一个脱离主分支的另外一条全新主分支，不用太在意叫什么，因为后面还会修改分支名称
git checkout --orphan latest_branch
# 暂存所有改动过的文件，内容为当前旧分支的最新版本所有文件
git add -A
#提交更改
git commit -am "commit message"
#删除原始主分支
git branch -D main
#将当前分支重命名为 main
git branch -m main
#最后，强制更新您的存储库
git push -f origin main
```

