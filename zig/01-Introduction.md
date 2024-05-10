# Zig

我知道`Zig`是因为前一段时间搜`JavaScript`相关内容的时候，偶然了解到`Bun`这个全新的运行时，这个对标`NodeJS`的运行时，底层居然是`Zig`。

对于他为什么舍弃`C++`，没有选择`C`而使用了`Zig`这门还不是很火热的语言，原因不明，也不详究。

但我还是准备简单学习一下这门语言，知道一点新东西，总没有坏处。

## 一、安装

### Zig

`Zig`目前的安装，官方提供的都是压缩包，任何平台似乎都是如此，我们只需要从[官方下载](https://ziglang.org/download/)并安装即可。

基本来说大家安装自己的平台和架构安装即可。

我安装的`MacOS-aarch64`这个包。

下载并解压之后，因为默认的文件夹名称带版本后缀，所以建议大家直接改成`Zig`，配置环境变量也简单。

我在下载完成后将文件夹拖到了`usr/local/`下面，然后在`.bash_profile`文件里面配置了环境变量，只要能正常找到`Zig`就可以。

### Zls

接下来我们还要安装`Zls(Zig language server)`，这个是用来编码的，打开[链接](https://github.com/zigtools/zls/releases)，选择和`Zig`版本匹配的包。

下载后就是一个可执行程序，将它放入到`Zig`同目录下面。

```sh
cd /usr/local/zig/

ll

# 结果如下
# -rw-r--r--@  1 merlot  wheel   1.1K  4 20 16:55 LICENSE
# -rw-r--r--@  1 merlot  wheel   5.5K  4 20 16:55 README.md
# drwxr-xr-x@  3 merlot  wheel    96B  4 20 16:55 doc
# drwxr-xr-x@ 16 merlot  wheel   512B  4 20 16:55 lib
# -rwxr-xr-x@  1 merlot  wheel   166M  4 20 16:55 zig
# -rwxr-xr-x@  1 merlot  wheel   3.1M  4 26 17:36 zls

# 可以看到`zig`和`zls`在一个目录下面，结束配置

```
### VSCode

安装`Zig language`这个插件

注意，我们在使用VSCode编码的时候可能会出现Apple检测到未知的应用程序，这个还是zig的问题，大家要去`设置-安全与隐私`里面配置，

```sh

sudo spctl --master-disable

```

然后设置`允许所有`就ok。
