"Sort" - Sort the DynamicArray 

void Sort(const bool (*SortFunc)(const T& firstElement, const T& secondElement)) const

if "SortFunc" return true first element will be closer

Example:

```C++
const bool Sort(const int& firstElement, const int& secondElement)
{
	return firstElement < secondElement;
}

DynamicArray<int> array;

for (int i = 0; i < 1000; i++)
{
	array.Add( 1 );
	array.Add( 100 );
	array.Add( 14 );
	array.Add( 4 );
	array.Add( 2 );
	array.Add( 3 );
}

array.Sort(Sort);

for (const auto& item : array)
	std::cout << item << "\n";
```