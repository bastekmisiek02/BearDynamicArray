"Remove" - delete element or all elements which equals first parametr

void Remove(const T& Element, const bool& removeAll = false)

Element - element which will be delete from the DynamicArray
removeAll - if true delete all element which equals "Element", if false delete first element which equals "Element"

Example:

```C++
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

array.Remove(1, true);

for (const auto& item : array)
	std::cout << item << "\n";
```