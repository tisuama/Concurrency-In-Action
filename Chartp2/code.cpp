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

void f(int i, std::string const& s) {
	// do something
}

void not_oops(int some) {
	char buf[1024];
	// sprintf(buf, "%i", some);
	// std::thread t(f, 3, std::string(buf));
	std::thread t(f, 3, buf);
	t.detach();
}


int main() {
	// test1();
	// test2();
	// f();
	f1();
}
