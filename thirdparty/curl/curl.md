# cURL

## http-GET

与浏览器一样，`curl`的默认请求方式也是`GET`，具体的例子可以看`test_curl_get_method`

* `CURLOPT_URL`：这是你要请求的URL地址。这是进行GET请求时最重要的选项之一。

* `CURLOPT_WRITEFUNCTION`和`CURLOPT_WRITEDATA`：这两个选项用于处理服务器的响应。CURLOPT_WRITEFUNCTION是一个回调函数，用于接收服务器返回的数据；CURLOPT_WRITEDATA通常是一个指向你希望存储响应数据的变量的指针。

* `超时设置`：虽然不直接涉及GET请求的设置，但通常还需要设置超时选项，如CURLOPT_TIMEOUT，来确保请求不会无限期地等待。

* `其他选项`：根据具体需求，可能还需要设置其他选项，如代理、认证信息、HTTP头部字段等。

## http-POST

这种就需要主动设置请求方式。

以下是进行POST请求时通常需要设置的一些选项：

* `CURLOPT_URL`：这是你要请求的URL地址。

* `CURLOPT_POST`：设置为1来告诉libcurl这是一个POST请求。

* `CURLOPT_POSTFIELDS`：这是你要发送的POST数据。它可以是一个字符串，也可以是一个指向数据的指针以及数据的长度。

* `CURLOPT_POSTFIELDSIZE`：对于长参数，需要设置这个选项来告诉libcurl POST数据的大小，否则数据可能会被截断。

* `CURLOPT_HTTPHEADER`：如果需要，你可以设置自定义的HTTP头部字段。例如，你可以设置Content-Type字段来指定发送数据的类型（如application/x-www-form-urlencoded或application/json）。

* `CURLOPT_WRITEFUNCTION`和`CURLOPT_WRITEDATA`：这两个选项用于处理服务器的响应。CURLOPT_WRITEFUNCTION是一个回调函数，用于接收服务器返回的数据；CURLOPT_WRITEDATA通常是一个指向你希望存储响应数据的变量的指针。

* `超时设置`：虽然不直接涉及POST请求的设置，但通常还需要设置超时选项，如CURLOPT_TIMEOUT，来确保请求不会无限期地等待。

* `其他选项`：根据具体需求，可能还需要设置其他选项，如代理、认证信息等。

## http-proxy

http通信设置代理服务器

* `CURLOPT_PROXY`：设置代理信息，内容一般为`url:port`

* `CURLOPT_PROXYUSERPWD`：设置代理服务器的登陆属性，内容一般是`username:password`

## http-put

`PUT`通常是客户端向服务器传递数据，可能是一块内存，也可能是一份文件.

在使用libcurl库发起PUT请求时，需要设置以下选项：

* `CURLOPT_URL`：指定请求的目标URL。

* `CURLOPT_CUSTOMREQUEST`：设置为"PUT"，以指示libcurl使用PUT方法。

* `CURLOPT_READFUNCTION`：设置一个回调函数，该函数用于读取要上传的数据。当libcurl需要发送数据时，它会调用这个函数来获取数据。
 
* `CURLOPT_READDATA`：设置为回调函数的用户数据指针。这通常是一个指向包含要上传数据的结构的指针，或者是文件描述符等。

* `CURLOPT_UPLOAD`：设置为1，以指示这是一个上传请求。

* `CURLOPT_INFILESIZE_LARGE`：设置要上传的数据的大小。如果数据大小是未知的，可以设置为-1，libcurl会根据CURLOPT_READFUNCTION的返回值来确定何时结束上传。