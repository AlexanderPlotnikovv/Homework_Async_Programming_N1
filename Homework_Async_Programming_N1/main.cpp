#include <iostream>
#include <vector>
#include <future>

int find_min_index(std::vector<int> vec, int i)
{
	int min = vec[i];
	int min_index = i;
	for (int j = i+1;j<vec.size();++j)
	{
		if (min > vec[j])
		{
			min = vec[j];
			min_index = j;
		}
	}
	return min_index;
}

void min_promise(std::vector<int>& vec, int i, std::promise<int>& p)
{
	int min = find_min_index(vec, i);
	p.set_value(min);
}

void selection_sort(std::vector<int>& vec)
{
	int min_index;
	for (int i = 0; i < vec.size() - 1; ++i)
	{
		std::promise<int> prom;
		std::future<int> fut = prom.get_future();
		std::thread t(min_promise, std::ref(vec), i, std::ref(prom));
		min_index = fut.get();
		t.join();
		std::swap(vec[i], vec[min_index]);
	}
}

int main()
{
	std::vector<int> vec = { 4,5,2,3,1 };
	selection_sort(vec);
	for (auto elem : vec)
	{
		std::cout << elem << " ";
	}
	return 0;
}