"Swap" - swap elements

//////////////////////////////////////////Vector//////////////////////////////////////////////////////

void Swap(std::vector<T>& elements)

elements - vector which will be swap elements

Example:

List<int> list(4);
list[0] = 2;
list[1] = 3;
list[2] = 100;
list[3] = 10;

std::vector<int> vector(3);
vector[0] = 2;
vector[1] = 100;
vector[2] = 20;

list.Swap(vector);

for (const auto& item : list)
	std::cout << item << "\n";

std::cout << "---------------------------\n";

for (const auto& item : vector)
	std::cout << item << "\n";

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////List/////////////////////////////////////////////////////////////

void Swap(List<T>& elements)

elements - list which will be swap elements

Example:

List<int> list(4);
list[0] = 2;
list[1] = 3;
list[2] = 100;
list[3] = 10;

List<int> secondList(3);
secondList[0] = 2;
secondList[1] = 100;
secondList[2] = 20;

list.Swap(secondList);

for (const auto& item : list)
	std::cout << item << "\n";

std::cout << "---------------------------\n";

for (const auto& item : secondList)
	std::cout << item << "\n";

///////////////////////////////////////////////////////////////////////////////////////////////////////////