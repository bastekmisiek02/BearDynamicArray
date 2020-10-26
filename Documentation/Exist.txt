"Exist" - check if exist element from parametr

const bool Exist(const T& Element, const bool FromEnd = false, Uint* Index = nullptr) const

Element - item to be checked if it is in the list
FromEnd - if true search from end
Index - if not null return index of "Element"

"Exist" function return true if "Element" exist in list, else false

Example:

List<int> list;

list.Add(1);
list.Add(100);
list.Add(14);
list.Add(4);
list.Add(2);
list.Add(3);

Uint index;

if (list.Exist(3, true, &index))
	std::cout << index << "\n";