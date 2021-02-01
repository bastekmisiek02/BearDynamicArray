"RemoveCollection" - delete first element or all elements from collection

//////////////////////////////////////////std::vector//////////////////////////////////////////////////////

void RemoveCollection(const std::vector<T>& Elements, const bool& removeAll = false)

Elements - elements which will be delete from the DynamicArray
removeAll - if true delete all element which equals "Elements", if false delete first element which equals "Element" (default false)

Example:

```C++
DynamicArray<int> array(4);
array[0] = 2;
array[1] = 3;
array[2] = 100;
array[3] = 10;

std::vector<int> vector(3);
vector[0] = 2;
vector[1] = 100;
vector[2] = 20;

array.RemoveCollection(vector);

for (const auto& item : array)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////DynamicArray/////////////////////////////////////////////////////////////

void RemoveCollection(const DynamicArray<T>& Elements, const bool& removeAll = false)

Elements - elements which will be delete from the list
removeAll - if true delete all element which equals "Elements", if false delete first element which equals "Element" (default false)

Example:

```C++
DynamicArray<int> array(4);
array[0] = 2;
array[1] = 3;
array[2] = 100;
array[3] = 100;

DynamicArray<int> array2(3);
array2[0] = 2;
array2[1] = 100;
array2[2] = 20;

array.RemoveCollection(array2);

for (const auto& item : array)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////