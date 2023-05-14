#include<iostream>
#include<thread>


using namespace std;

void print_queue(int& queue) {
	std::cout << "\n" << " Queue: " << queue << " Id Thread: " << std::this_thread::get_id() << " " << "\n";
}

void oper(int& queue) {
	do {
		print_queue(queue);
		std::this_thread::sleep_for(2000ms);
		--queue;
	} while (queue != 0);
}
void guest(int& queue) {
	do {
		print_queue(queue);
		std::this_thread::sleep_for(1000ms);
		++queue;
	} while (queue <= 10);
}


int main() {

	int queue = 1;
	thread Guest(guest, std::ref(queue));
	thread Oper(oper, std::ref(queue));
	Guest.join();
	Oper.join();

	return 0;
}