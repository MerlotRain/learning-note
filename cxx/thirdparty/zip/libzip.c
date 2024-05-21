/*

在C/C++中，有多种库可以用于处理ZIP格式的压缩文件，每种库都有其特定的用途和优势。以下是一些常见的ZIP库及其在C/C++中的适用性：

Zlib：Zlib是一个开源的压缩库，它提供了通用的数据压缩和解压缩算法。虽然Zlib本身并不直接支持ZIP文件格式，但可以通过与其他库（如Minizip）结合使用来实现ZIP文件的压缩和解压缩。Zlib库适用于需要高效压缩和解压缩数据的场景，如网络通信、数据存储等。

Minizip：Minizip是一个基于Zlib的ZIP处理库，它提供了ZIP文件的读取、写入和修改功能。Minizip适用于处理ZIP格式的压缩文件，包括创建新的ZIP文件、向ZIP文件中添加文件、从ZIP文件中提取文件等。

libzip：libzip是一个用于处理ZIP文件的C库，它提供了创建、读取和修改ZIP文件的功能。libzip库支持ZIP64扩展，可以处理大于4GB的文件和超过65535个条目的ZIP文件。它适用于需要处理大型ZIP文件或需要ZIP64扩展支持的场景。

Zip-Utils：Zip-Utils是一个基于C++/WIN32的压缩工具包，它提供了简单的ZIP文件压缩和解压缩功能。Zip-Utils适用于Windows平台上的ZIP文件处理，可以将zip.cpp和zip.h等文件添加到项目中，以使用其压缩和解压缩功能。

*/

#include <stdio.h>
#include <zip.h>

int main() {
  int err = 0;
  struct zip *za = zip_open("./c.zip", 0, &err);
  if (!za) {
    fprintf(stderr, "error");
    return -1;
  }

  int n = zip_get_num_entries(za, 0);
  for (int i = 0; i < n; ++i) {
    const char *name = zip_get_name(za, i, 0);
    printf("%s\n", name);
  }

  zip_close(za);
}