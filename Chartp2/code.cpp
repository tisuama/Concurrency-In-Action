#include <thread>
#include <chrono>
#include <iostream>

class background_task {
public:
		void operator() () const {
			// do_something();
			// do_something_else();
			std::cout << "background_task work" << std::endl;
		}
};

void test1() {
	background_task f;
	std::thread my_thread(f);
	
	// std::thread my_thread1(background_task());
	std::thread my_thread2((background_task()));
}

struct func {
	int& i;
	func(int& i_): i(i_) {}
	void operator() () {
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(2s);
		for (unsigned j = 0; j < 1000000; j++) {
			if (j % 100000 == 0) {
				printf("j: %d, i: %d\n", j, i);
			}
		}
	}
};

void test2() {
	int state = 0;
	func my_func(state);
	std::thread my_thread(my_func);
	my_thread.detach();
}

class thread_guard {
	std::thread& t;
public:
		explicit thread_guard(std::thread& t_): t(t_) {}
		~thread_guard() {
			if (t.joinable()) {
				t.join();
			}
		}
		thread_guard(thread_guard const&) = delete;
		thread_guard& operator=(thread_guard const&) = delete;
};

void f() {
	int state = 0;
	func my_func(state);
	std::thread t(my_func);
	try {
		printf("in current thread: %lu\n", std::this_thread::get_id());
	} catch(...) {
		t.join();
		throw;
	}
	t.join();
}

void f1() {
	int state = 0;
	func my_func(state);
	std::thread t(my_func);
	thread_guard g(t);
	printf("thread %lu exit now\n", std::this_thread::get_id());
}


// 隐式类型转换时机
void f2(int i, std::string const& s) {
	// do something
}

void not_oops(int some) {
	char buf[1024];
	// sprintf(buf, "%i", some);
	// std::thread t(f, 3, std::string(buf));
	// 为什么这种写法会有问题？隐式类型转换时机
	std::thread t(f2, 3, std::string(buf));
	t.detach();
}

void update_data_for_widget(int x, int&y) {
	printf("update data for widget, x: %d, y: %d\n", x, y);
}

void oops_again() {
	int state = 1;
	std::thread t(update_data_for_widget, 1, state);
	t.join();
}



// const rvalue的使用
class A {
public:
	A() {
		printf("A's constrcut is called\n");
	}
	~A() {
		printf("A's deconstruct is called\n");
	}
};

class B: public A {
public:
	B() {
		printf("B's constrcut is called\n");
	}
	~B() {
		printf("B's deconstruct is called\n");
	}
};

B factory() {
	return B();
}

int main() {
	printf("=== start to run test ===\n");
	// test1();
	// test2();
	// f();
	// f1();
	// oops_again();
	
	const A& a = factory();
	printf("=== sucesssfully run test ===\n");
}
