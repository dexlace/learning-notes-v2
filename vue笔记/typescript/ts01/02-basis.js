//声明一个变量a，类型为number
var a;
//a 的类型设置为number，在以后的过程中a的值只能为数字
a = 100;
// a = 'a';
var b;
b = 'aaa';
//声明完直接赋值
var c = true;
//不声明类型会默认为第一次赋值的变量的类型为自己的类型
var d = '111';
// d = 222;
//返回值类型也是必须为number
function sum(a, b) {
    return a + b;
}
sum(1, 2);
// sum(1,'2');
