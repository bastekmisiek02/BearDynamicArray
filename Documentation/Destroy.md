"Destroy" - use this function if using pointer type

void Destroy() const

Example:

```C++
DynamicArray<int*> array;

array.Add(new int(2));
array.Add(new int(100));
array.Add(new int(14));
array.Add(new int(4));
array.Add(new int(2));
array.Add(new int(3));

for (const auto& item : array)
	std::cout << *item << "\n";

array.Destroy();
```