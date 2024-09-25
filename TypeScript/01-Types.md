# TS 基本类型

```typeScript

let a : boolean = false;
let b : number = 12;
let c : string = "hello world";

// | 表示联合类型，所有的赋值都只能从候选值中得到
let d : "CMake" | "Make";
d = "CMake";
d = "Make";
d = "Hello"; // error

// any变量，设置any，相当于关闭了类型检测，不建议使用
let e : any;

// unknown类型

// unknown 不能给别人，any可以给别人，它是一个类型安全的any
e as string;
if(typeof e === "string") {
    ...
}


```