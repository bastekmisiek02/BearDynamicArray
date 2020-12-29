"Sort" - Sort the list 

void Sort(const bool (*SortFunc)(const T& firstElement, const T& secondElement)) const

if "SortFunc" return true first element will be closer

Example:

```C++
const bool Sort(const int& firstElement, const int& secondElement)
{
	return firstElement < secondElement;
}

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

list.Sort(Sort);

for (const auto& item : list)
	std::cout << item << "\n";
```