"Exist" - check if exist element from parametr

const bool Exist(const T& Element, const bool FromEnd = false, DynamicArrayUint* Index = nullptr) const

Element - item to be checked if it is in the DynamicArray
FromEnd - if true search from end
Index - if not null return index of "Element"

"Exist" function return true if "Element" exist in list, else false

Example:

```C++
DynamicArray<int> array;

array.Add(1);
array.Add(100);
array.Add(14);
array.Add(4);
array.Add(2);
array.Add(3);

DynamicArrayUInt index;

if (array.Exist(3, true, &index))
	std::cout << index << "\n";
```