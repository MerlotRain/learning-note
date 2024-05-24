# Git的使用

## 一、Git的安装

Windows平台使用安装包，linux和Mac使用源码安装，推荐

## 二、Git的仓库

Git是一个分布式的版本控制工具，除此之外还有SVN等，Git和bitkeeper的故事可以在网上找，这里不赘述。

Git存在四个区域：工作区、暂存区、本地仓库、远程仓库

Git存在一个远程仓库，这一点很好理解，大家的代码交换终归需要一个中间节点，这个节点通常在服务器上，我们称为远程仓库

本地仓库就是你自己电脑上的仓库。

所谓仓库并不是一个分支的代码，而是对多个分支的管理，这是必须搞清楚的。

工作区可以简单理解为，你看得到的代码，这个代码是一个分支的，你也只可能在同一时间编辑一个分支。

暂存区，我们的代码写完后通过`add`命令可以提交到暂存区，不过大部分IDE都只提供了`commit`选项，这个命令执行前会主动执行`add`。

## Git基本命令

### init

`git init`，初始化一个仓库，部分语言的包管理工具在创建工程时自动创建，也挺方便。

### clone

`git clone ... ` 从远程仓库`clone`一份到本地，通常来说，仓库的名称就是你`clone`后文件夹的名称，但在多分支开发的时候，也可能会觉得不断切换分支不爽，那么可以用`git clone XXX branch-name`

这个时候，我们就将仓库克隆到了指定的文件夹中，也是个不错的做法，毕竟可能发生编译参数的变化，尤其是CMake，咋样输入命令都麻烦。

### add

`git add XXX`，将本地修改添加到暂存区。

正常来说，应该先添加到暂存区后再commit，但是IDE太智能，他们会直接执行`git commit -a`，这样操作很可能会将一些临时文件提交，所以建议还是先`add`再`commit`.

`add`支持很多种写法，最简单的`add .`，全部添加，也可以指定文件，指定文件夹，通配符处理，等等，总之有很多方法。

### commit

`git commit` 将暂存区提交到本地仓库。

我个人的使用方法通常是`git commit -m '....'`，这样来写提交日志。

### pull

### push

### status

### rm

### mv

### reset

### checkout

### switch

### restore

### log

### diff

## Git陌生但好用的命令

### rebase

### merge

### revert

### stash

### fetch

### tag

### diff

### cherry-pick

## Git分支合并和冲突处理