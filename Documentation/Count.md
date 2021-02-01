"Count" - get size of DynamicArray

const DynamicArrayUint& Count()

Example:

```C++
DynamicArray<int> array;

array.Add(2);
array.Add(1);
array.Add(3);

for (const auto& item : array)
	std::cout << item << "\n";
```