"Destroy" - use this function if using pointer type

void Destroy() const

Example:

List<int*> list;

list.Add(new int(2));
list.Add(new int(100));
list.Add(new int(14));
list.Add(new int(4));
list.Add(new int(2));
list.Add(new int(3));

for (const auto& item : list)
	std::cout << *item << "\n";

list.Destroy();