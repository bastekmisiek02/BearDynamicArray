"Remove" - delete element or all elements which equals first parametr

void Remove(const T& Element, const bool& removeAll = false)

Element - element which will be delete from the list
removeAll - if true delete all element which equals "Element", if false delete first element which equals "Element"

Example:

List<int> list;

for (int i = 0; i < 1000; i++)
{
	list.Add( 1 );
	list.Add( 100 );
	list.Add( 14 );
	list.Add( 4 );
	list.Add( 2 );
	list.Add( 3 );
}

list.Remove(1, true);

for (const auto& item : list)
	std::cout << item << "\n";