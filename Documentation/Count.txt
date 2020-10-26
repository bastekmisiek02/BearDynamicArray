"Count" - get size of list

const Uint& Count()

Example:

List<int> list;

list.Add(2);
list.Add(1);
list.Add(3);

for (const auto& item : list)
	std::cout << item << "\n";