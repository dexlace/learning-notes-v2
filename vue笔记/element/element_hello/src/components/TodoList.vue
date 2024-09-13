<template>
  <ul class="todo-main">
    <!-- <TodoItem></TodoItem>
    <TodoItem></TodoItem>
    <TodoItem></TodoItem> -->
    <!-- <TodoItem></TodoItem> -->
    <!--todos v-for :todo传值-->
    <TodoItem v-for="todo in todos" :key="todo.id" :todo="todo"> </TodoItem>
  </ul>
</template>

<script>
import TodoItem from "./TodoItem.vue"
export default {
  name: "TodoList",
  components: { TodoItem },
  //声明接收App传递过来的数据，其中todos是自己用的
  props: ["todos"],
  data() {}
}
</script>
<style scoped>
/*main*/
.todo-main {
  margin-left: 0px;
  border: 1px solid #ddd;
  border-radius: 2px;
  padding: 0px;
}

.todo-empty {
  height: 40px;
  line-height: 40px;
  border: 1px solid #ddd;
  border-radius: 2px;
  padding-left: 5px;
  margin-top: 10px;
}
</style>
