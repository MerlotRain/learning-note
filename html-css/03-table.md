# Table

表格相关的标签有`<table>`,`<caption>`,`<thead>`,`<tbody>`,`<tfoot>`

```html

<!DOCTYPE html>  
<html>  
<head>  
    <title>使用 caption, thead, tbody, tfoot 的 HTML 表格</title>  
</head>  
<body>  
    <table border="1">  
        <caption>我的表格标题</caption>  
        <thead>  
            <tr>  
                <th>列标题1</th>  
                <th>列标题2</th>  
                <th>列标题3</th>  
            </tr>  
        </thead>  
        <tbody>  
            <tr>  
                <td>数据1</td>  
                <td>数据2</td>  
                <td>数据3</td>  
            </tr>  
            <tr>  
                <td>数据4</td>  
                <td>数据5</td>  
                <td>数据6</td>  
            </tr>  
        </tbody>  
        <tfoot>  
            <tr>  
                <td colspan="3">这是表格的底部信息</td>  
            </tr>  
        </tfoot>  
    </table>  
</body>  
</html>

```

在这个示例中：

* `<caption>` 标签用于为表格提供描述性标题。

* `<thead>` 标签用于定义表格的头部，通常包含一列或多列标题。

* `<tbody>` 标签用于定义表格的主体，包含表格的数据行。

* `<tfoot>` 标签用于定义表格的底部，通常包含总结性的信息或操作按钮。

* `<th>` 标签用于定义表格的表头单元格，它们通常是粗体并居中显示的。

* `<td>` 标签用于定义表格的数据单元格，它们包含表格的实际数据。

* `colspan` 属性在`<td>`标签中用于指定单元格应横跨多少列。在这个例子中，tfoot 里的单元格横跨了所有三列。