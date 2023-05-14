#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

void sum_vec_1th(std::vector<int> vec_1, vector<int> vec_2, int st, int fin) {
	int temp_sum = 0;
	for (int i = st; i < fin; i++) {
		vec_1[i] += vec_2[i];
	}
	for (int i = 0; i < vec_1.size(); i++) {
		temp_sum += vec_1[i];
	}
}

int main() {

	setlocale(LC_ALL, "rus");

	cout << " Количество аппаратных ядер - " << thread::hardware_concurrency() << endl;

	vector<int> vec_size = { 1000, 10000, 100000, 1000000 };
	vector<int> vec_1(vec_size[0]);
	vector<int> vec_2(vec_size[1]);
	vector<int> vec_3(vec_size[2]);
	vector<int> vec_4(vec_size[3]);
	vector<thread> vec_th;
	vector<chrono::duration<double, milli>> vec_el_sec;
	int temp = 0;

	mt19937 gen;
	uniform_int_distribution<int> distrib(1, 3000);
	auto rand_num([=]() mutable {return distrib(gen); });

	generate(vec_1.begin(), vec_1.end(), rand_num);
	generate(vec_2.begin(), vec_2.end(), rand_num);
	generate(vec_3.begin(), vec_3.end(), rand_num);
	generate(vec_4.begin(), vec_4.end(), rand_num);
	vector<vector<int>> vec_all_1(4);
	vector<vector<int>> vec_all_2(4);
	vec_all_1[0] = vec_all_2[0] = vec_1;
	vec_all_1[1] = vec_all_2[1] = vec_2;
	vec_all_1[2] = vec_all_2[2] = vec_3;
	vec_all_1[3] = vec_all_2[3] = vec_4;

	for (int i = 0; i < vec_size.size(); i++) {
		cout << "\t\t" << vec_size[i];
	}
	
	for (int i = 0; i < vec_size.size(); i++) {
		auto start = chrono::high_resolution_clock::now();
		vec_th.push_back(thread(sum_vec_1th, ref(vec_all_1[i]), ref(vec_all_2[i]), 0, vec_size[i]));
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> el_sec = end - start;
		vec_el_sec.push_back(el_sec);
	}
	for (auto& st : vec_th) {
		st.join();
	}
	std::cout << "\n" << "1 потоков: ";
	for (int i = 0; i < vec_el_sec.size(); i++) {
		std::cout << "\t" << vec_el_sec[i].count() << "s ";
	}

	vec_el_sec.clear();
	vec_th.clear();
	for (int i = 0; i < vec_size.size(); i++) {
		int st = 0,
			fin = vec_size[i] / 2;
		auto start = chrono::high_resolution_clock::now();
		for (int j = 0; j < 2; j++) {
			vec_th.push_back(thread(sum_vec_1th, ref(vec_all_1[i]), ref(vec_all_2[i]), st, fin));
			st += (vec_size[i] / 2);
			fin += (vec_size[i] / 2);
		}
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> el_sec = end - start;
		vec_el_sec.push_back(el_sec);
	}
	for (auto& st : vec_th) {
		st.join();
	}
	std::cout << "\n" << "2 потоков: ";
	for (int i = 0; i < vec_el_sec.size(); i++) {
		std::cout << "\t" << vec_el_sec[i].count() << "s ";
	}
	
	vec_el_sec.clear();
	vec_th.clear();
	for (int i = 0; i < vec_size.size(); i++) {
		int st = 0,
			fin = vec_size[i] / 4;
		auto start = chrono::high_resolution_clock::now();
		for (int j = 0; j < 4; j++) {
			vec_th.push_back(thread(sum_vec_1th, ref(vec_all_1[i]), ref(vec_all_2[i]), st, fin));
			st += (vec_size[i] / 4);
			fin += (vec_size[i] / 4);
		}
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> el_sec = end - start;
		vec_el_sec.push_back(el_sec);
	}
	for (auto& st : vec_th) {
		st.join();
	}
	std::cout << "\n" << "4 потоков: ";
	for (int i = 0; i < vec_el_sec.size(); i++) {
		std::cout << "\t" << vec_el_sec[i].count() << "s ";
	}

	vec_el_sec.clear();
	vec_th.clear();
	for (int i = 0; i < vec_size.size(); i++) {
		int st = 0,
			fin = vec_size[i] / 8;
		auto start = chrono::high_resolution_clock::now();
		for (int j = 0; j < 8; j++) {
			vec_th.push_back(thread(sum_vec_1th, ref(vec_all_1[i]), ref(vec_all_2[i]), st, fin));
			st += (vec_size[i] / 8);
			fin += (vec_size[i] / 8);
		}
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> el_sec = end - start;
		vec_el_sec.push_back(el_sec);
	}
	for (auto& st : vec_th) {
		st.join();
	}
	std::cout << "\n" << "8 потоков: ";
	for (int i = 0; i < vec_el_sec.size(); i++) {
		std::cout << "\t" << vec_el_sec[i].count() << "s ";
	}

	vec_el_sec.clear();
	vec_th.clear();
	for (int i = 0; i < vec_size.size(); i++) {
		int st = 0,
			fin = vec_size[i] / 16;
		auto start = chrono::high_resolution_clock::now();
		for (int j = 0; j < 16; j++) {
			vec_th.push_back(thread(sum_vec_1th, ref(vec_all_1[i]), ref(vec_all_2[i]), st, fin));
			st += (vec_size[i] / 16);
			fin += (vec_size[i] / 16);
		}
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> el_sec = end - start;
		vec_el_sec.push_back(el_sec);
	}
	for (auto& st : vec_th) {
		st.join();
	}
	std::cout << "\n" << "16 потоков: ";
	for (int i = 0; i < vec_el_sec.size(); i++) {
		std::cout << "\t" << vec_el_sec[i].count() << "s ";
	}
	cout << "\n";

	system("Pause");

	return 0;
}