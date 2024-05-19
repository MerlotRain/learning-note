#include <boost/format.hpp>
#include <iostream>

using namespace std;

/**
 * @brief
 *
 * https://www.boost.org/doc/libs/1_76_0/libs/format/doc/html/index.html
 *
 * format字符串简直是C++ 的一个噩梦，尤其是需要使用可变参数的情况下
 *
 * 我们会发现很多语言都采用了更为简单的format方式，这个东西真的非常有用，但std就是没有一个完美的支持
 * 虽然我们可以用stringstream 等手段处理，但一行代码和多行代码，感觉还是不一样的
 *
 * 一、boost.format组件
 * 1、boost.format组件介绍
 * C语言中的printf函数使用了可变参数（了解可变参使用点击）来实现被格式化的数据，但它是不安全的。
 * boost.format组件为了增加安全性，模仿了流操作符<<，重载了二元操作符operator%作为参数输入符来实现可变参数的功能。
 *
 * format组件的构造函数接受string类型作为格式化字符串，并提供了成员函数str()来返回已经格式化好的字符串，
 * 如果没有得到按照规则的格式化数据则会抛出异常。
 *
 *
 * 2、boost.format格式化语法
 * format使用了类似printf的格式化语法规则，比如说对齐、宽度、精度、字符类型等等。
 * 除了以上这些经典的printf用法，还增加了%|spec|来区分格式化选项与普通字符，
 * %N%来标记第N个参数的占位等功能，在语法上比printf的更加完善和易懂。
 */

void demo1() {
  cout << "----------------boost.format的使用示例-----------------" << endl;
  cout << "-------------------------------" << endl;
  boost::format fmt("(%1% + %2%) * %3% = %4%\n");
  fmt % 2 % 3 % 4 % ((2 + 3) * 4);
  cout << fmt.str() << endl;
  cout << "-------------------------------" << endl;
  cout << boost::format("%s: %d+%d=%d\n") % "sum" % 5 % 6 % (5 + 6);

  cout << "-------------------------------" << endl;


  // 占位和格式化输出同步进行

  // 对下面的表达式进行解释，||用来区分格式化选项功能，可以不要，当表达式中含有空格等特殊字符占位时，使用||表达更容易区分些
  //  %|04d|输出宽度为4的数值，不足位用0补充
  //  %|-8.4f|左对齐，输出宽度为8，小数位保留4为的浮点数
  //  %| 8s|输出宽度为8的字符串，不足位用空格填补的字符串
  //  %|06X|输出宽度为6的大写16进制整数，不足位用0填补
  boost::format tmpFormat("%|04d|\n %|-8.4f|\n %| 8s|\n %|06X|\n");
  tmpFormat % 44 % 3.1415926 % "123456" % 48;
  // 使用boost自带的str()函数获取表达式，也可以使用format的自带成员函数str()，注意二者的使用不同
  string tmpFormatStr = boost::str(tmpFormat);
  cout << tmpFormatStr << endl;
  std::cout << "Hello World!\n";
}

int main() { demo1(); }