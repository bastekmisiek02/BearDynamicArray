"RemoveCollection" - delete first element or all elements from collection

//////////////////////////////////////////std::vector//////////////////////////////////////////////////////

void RemoveCollection(const std::vector<T>& Elements, const bool& removeAll = false)

Elements - elements which will be delete from the list
removeAll - if true delete all element which equals "Elements", if false delete first element which equals "Element" (default false)

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

list.RemoveCollection(vector);

for (const auto& item : list)
	std::cout << item << "\n";

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////List/////////////////////////////////////////////////////////////

void RemoveCollection(const List<T>& Elements, const bool& removeAll = false)

Elements - elements which will be delete from the list
removeAll - if true delete all element which equals "Elements", if false delete first element which equals "Element" (default false)

Example:

List<int> list(4);
list[0] = 2;
list[1] = 3;
list[2] = 100;
list[3] = 100;

List<int> list2(3);
list2[0] = 2;
list2[1] = 100;
list2[2] = 20;

list.RemoveCollection(list2);

for (const auto& item : list)
	std::cout << item << "\n";

///////////////////////////////////////////////////////////////////////////////////////////////////////////