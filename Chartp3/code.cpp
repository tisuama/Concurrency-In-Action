#include <iostream>
#include <mutex>

class X {
public:
	X(const int x): x(x) {}
	
	friend void swap(X& lhs, X& rhs) {
		if (&lhs == &rhs) {
			return ;
		}
		std::lock(lhs.m, rhs.m);
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		std::swap(lhs.x, rhs.x);
	}
	
	// c++17写法
	void swap(X& lhs, X& rhs) {
		if (&lhs == &rhs) {
			return ;
		}
		// C++17自动推导模板参数
		std::scoped_lock gurad(lhs.m, rhs.m);
		// 等价于
		// std::scoped_lock<std::mutex, std::mutex> gurad(lhs.m, rhs.m);
		swap(lhs.x, rhs.x);
	}

private:
	int x;
	std::mutex m;
};


int main() {
	X x(2);
	
}
