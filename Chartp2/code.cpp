#include <thread>
#include <iostream>

class background_task {
public:
		void operator() () const {
			// do_something();
			// do_something_else();
			std::cout << "background_task work" << std::endl;
		}
};

int main() {
	background_task f;
	std::thread my_thread(f);
	std::thread my_thread1(background_task());
}
