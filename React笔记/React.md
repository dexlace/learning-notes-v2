## 一、 关于 React

整几个面试题来认识一下~~

> 什么是 React ？

**React** 是一个用于构建用户界面的 JavaScript 库。

- 是一个将数据渲染为 HTML 视图的开源 JS 库
- 它遵循基于组件的方法，有助于构建可重用的 UI 组件
- 它用于开发复杂的交互式的 web 和移动 UI

> React 有什么特点？

1. 使用虚拟 DOM 而不是真正的 DOM
2. 它可以用服务器渲染
3. 它遵循单向数据流或数据绑定
4. 高效
5. 声明式编码，组件化编码

> React 的一些主要优点？

1. 它提高了应用的性能
2. 可以方便在客户端和服务器端使用
3. 由于使用 JSX，代码的可读性更好
4. 使用React，编写 UI 测试用例变得非常容易

### 1.1 Hello React

- React 核心库、操作 DOM 的 react 扩展库、将 jsx 转为 js 的 babel 库

```javascript
    <script src="../js/react.development.js"></script>
    <!-- 引入react-dom 用于支持react操作DOM -->
    <script src="../js/react-dom.development.js"></script>
    <!-- 引入babel用于jsx转js -->
    <script src="../js/babel.min.js"></script>
```

```javascript
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <!--移动端适配-->
    <!-- <meta
      name="viewport"
      content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0"
    />
    <meta http-equiv="X-UA-Compatible" content="ie=edge" /> -->
    <title>react_hello</title>
  </head>
  <body>
    <!-- 0. 准备一个容器 -->
    <div id="test"></div>
    <!--引入需要顺序-->
    <!-- 引入react核心库 -->
    <script src="../js/react.development.js"></script>
    <!-- 引入react-dom 用于支持react操作DOM -->
    <script src="../js/react-dom.development.js"></script>
    <!-- 引入babel用于jsx转js -->
    <script src="../js/babel.min.js"></script>

    <!--此处使用bale 以使用jsx-->
    <script type="text/babel">
      /* babel转义 */
      // 1. 创建虚拟DOM
      const VDOM = <h1>Hello,React</h1>
      // 2. 渲染虚拟DOM到页面
      // render(虚拟DOM,容器)
      ReactDOM.render(VDOM, document.getElementById('test'))
    </script>
  </body>
</html>

```

### 1.2 虚拟 DOM 和真实 DOM 的两种创建方法

