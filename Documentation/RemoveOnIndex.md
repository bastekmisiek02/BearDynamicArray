"RemoveOnIndex" - remove elements from first argument index to second argument or to end

//////////////////////////////////////////Only 1 Argument//////////////////////////////////////////////////////

void RemoveOnIndex(const DynamicArrayUint& Start)

Start - first index to remove

Remove elements from "Start" to end of List

Example:

```C++
DynamicArray<int> array;

array.Add(1);
array.Add(100);
array.Add(14);
array.Add(4);
array.Add(2);
array.Add(3);

array.RemoveOnIndex(1);

for (const auto& item : array)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////2 arguments//////////////////////////////////////////////////////

void RemoveOnIndex(const DynamicArrayUint& Start, const DynamicArrayUint& End)

Start - first index to remove
End - last index to remove

Remove elements from "Start" to "End" index

Example:

```
DynamicArray<int> array;

array.Add(1);
array.Add(100);
array.Add(14);
array.Add(4);
array.Add(2);
array.Add(3);

array.RemoveOnIndex(1, 3);

for (const auto& item : array)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////