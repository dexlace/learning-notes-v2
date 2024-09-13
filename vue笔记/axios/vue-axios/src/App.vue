<template>
  <div>
    <table>
      <thead>
        <tr>
          <th>id</th>
          <th>姓名</th>
          <th>年龄</th>
          <th>学校</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="(item, index) in users" :key="index">
          <td>{{ item.id }}</td>
          <td>{{ item.name }}</td>
          <td>{{ item.age }}</td>
          <td>{{ item.school }}</td>
        </tr>
      </tbody>
    </table>
    <el-radio v-model="radio" label="1">选择一</el-radio>
    <el-radio v-model="radio" label="2">选择二</el-radio>
    <el-button type="text" @click="open">点击打开 Message Box</el-button>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  name: 'App',
  components: {},
  methods: {
    getUsers() {
      axios.get('http://localhost:8081/user/list').then(res => {
        console.log(res.data)
        return res.data
      })
    },
    open() {
      this.$confirm('此操作将永久删除该文件, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      })
        .then(() => {
          this.$message({
            type: 'success',
            message: '删除成功!'
          })
        })
        .catch(() => {
          this.$message({
            type: 'info',
            message: '已取消删除'
          })
        })
    }
  },
  data() {
    // 组件(component)里的定义的data必须是Function类型的
    return {
      users: [],
      radio: '1'
    }
  },
  mounted() {
    axios.get('http://localhost:8081/user/list').then(res => {
      console.log(res.data)
      this.users = res.data
    })
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
