## Charpt2 线程管理

#### 启动线程
启动线程通常就是构造`std::thread`对象；注意启动时提供的函数对象会复制到新线程的存储空间中，函数执行和调用都在线程的内存空间中进行。

只能使用一次`join`，一旦使用过，`std::thread`对象就不能再次汇入
	产生异常时，需要精心挑选join的位置，如果异常在join之前抛出，就会跳过join，这种情况下需要在异常处理中调用join。

#### 风险
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

3. 如果参数仅仅支持移动(move)，不能拷贝时会发生什么情况？“移动”指数据的所有权发生改变。`std::unqie_ptr`就是这样一种类型。移动构造函数(move constructor)和移动赋值操作符(move assignment operator)允许一个对象的所有权在多个`std::unique_ptr`中传递。当对象是临时变量时，则自动进行移动操作；但是当对象是一个命名变量，转移是要使用`std::move`显式移动。
```
void process_big_object(std::unqiue_ptr<big_object>);

std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t(process_big_object, std::move(p));
```
4. `std::thread`和`std::unique_ptr`所属权上相似，`std::thread`不能占用对象的所有权，但它能占有其他资源：每个实例都负责管理一个线程。这依赖于`std::thread`的可移动且不可复制性。
