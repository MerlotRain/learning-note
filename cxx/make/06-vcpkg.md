# vcpkg

## 安装

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
```

## 配置

```bash
# 设置环境变量
export VCPKG_ROOT=/path/to/vcpkg
export PATH=${VCPKG_ROOT}/vcpkg:${PATH}

# 设置默认triplet
vcpkg install zlib:x64-windows
vcpkg install zlib:x64-linux
vcpkg install zlib:x64-osx
```
    
## 使用

```bash
vcpkg search <library>
vcpkg install <library>
vcpkg remove <library>
vcpkg list
```


