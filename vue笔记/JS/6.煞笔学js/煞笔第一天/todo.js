// Define an array to store todos
let todos = [];

// Function to add a new todo
function addTodo() {
  const todoInput = document.getElementById("todoInput");
  const todoText = todoInput.value.trim();

  // 添加并清除
  if (todoText !== "") {
    todos.push(todoText);
    renderTodos();
    todoInput.value = "";
  }
}

// Function to render todos
function renderTodos() {
  // 拿到todolist的dom元素
  const todoList = document.getElementById("todoList");
  todoList.innerHTML = "";

  todos.forEach((todo, index) => {
    // 创建一个li
    const li = document.createElement("li");
    // 设置li的内容
    li.textContent = todo;
    // 添加点击事件   点击立马删除
    li.addEventListener("click", () => removeTodo(index));
    // todolist下添加子元素li
    todoList.appendChild(li);
  });
}

// Function to remove a todo
function removeTodo(index) {
  todos.splice(index, 1);
  renderTodos();
}
