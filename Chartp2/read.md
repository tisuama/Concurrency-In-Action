## Charpt2 线程管理

#### 启动线程
	启动线程通常就是构造`std::thread`对象；注意启动时提供的函数对象会复制到新线程的存储空间中，函数执行和调用都在线程的内存空间中进行。

	只能使用一次`join`，一旦使用过，`std::thread`对象就不能再次汇入
	产生异常时，需要精心挑选join的位置，如果异常在join之前抛出，就会跳过join，这种情况下需要在异常处理中调用join。

### 风险
1. const string& 问题
```
string f() { return "abc"}
void g() {
	const string& s = f(); // 注意这里有const变量
	cout << s << endl;  	 // 合法操作
}

```
注意：只有左值能绑定到非常量引用; const 延长了rvalue的生命周期，析构操作在{}之后

2. 拷贝后以右值的方式进行传递
```
void update_data_for_widget(int x, int&y) {
	printf("update data for widget, x: %d, y: %d\n", x, y);
}

void oops_again() {
	int state = 1;
	std::thread t(update_data_for_widget, 1, state);
	t.join();
}
```

