软件授权的核心在三点：

## 1. 授权信息的生成。

该信息通常需要包含以下几点 ： 授权给谁（可以是用户，可以是具体的机器），授权多久（时间）

## 2. 授权的验证。

授权的验证必须是公钥和私钥的结合使用。

客户通过用户体系（例如邮箱）或者机器码，获取到一个授权文件。

这个授权文件中包含的就是授权信息。

比较复杂的校验可以根据这样的思路进行。

### 1) 授权文件包含信息

* 授权方式 - 网络授权/单机授权

* 授权公钥 - 公钥信息

* 授权数字签名 - 用户数字摘要混淆后的私钥加密结果

### 2) 授权验证过程

* 解析获取公钥

* 公钥解析数字签名得到摘要，去掉数字混淆

* 验证数字摘要中的标识，如果是用户体系，则根据摘要的ID和当前登录用户的ID进行匹配，如果是机器码，则根据机器码进行判断。

* 验证通过后，再判断授权时间。如果是单机版本，授权时间应该直接写到摘要中，如果是网络授权，则应该使用当前摘要ID去访问服务器，获取服务器上该授权记录的状态

## 3. 授权ID怎么获取

### 1) 用户体系下的ID

这种ID最常见的方式软件方的总ID，例如JetBrains的用户ID，它将用户登录官网等软件方，或者AppleID之类，也就是说这个ID通常是多个软件的ID

所以是先有ID再有软件。

这种ID的好处是，永远可以保持唯一，绝对唯一。

但缺点是，如果是小公司，搭建这种ID就很离谱，所以引入常见的三方软件ID就非常常见了。

### 2) 硬件ID

硬件ID获取比较简单，但是如果用户的硬件变化，则会引发授权失败的情况。
