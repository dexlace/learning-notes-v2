<template>
  <div id="root">
    <!-- <div class="todo-container">
      <div class="todo-wrap">
        <TodoHeader></TodoHeader>
        <TodoList :todos="todos"></TodoList>
        <TodoFooter></TodoFooter>
      </div>
    </div> -->
  </div>
</template>

<script>
import TodoHeader from "./components/TodoHeader"
import TodoList from "./components/TodoList"
import TodoFooter from "./components/TodoFooter"
export default {
  name: "App",
  components: { TodoHeader, TodoList, TodoFooter },
  data() {
    return {
      //由于todos是Header组件和Footer组件都在使用，所以放在App中（状态提升）
      todos: [
        { id: "001", title: "抽烟", done: true },
        { id: "002", title: "喝酒", done: false },
        { id: "003", title: "开车", done: true }
      ]
    }
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
