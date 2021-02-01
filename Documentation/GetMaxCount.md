"GetMaxCount" - Return max count of DynamicArray

const DynamicArrayUint GetMaxCount() const

Example:

```C++
DynamicArray<int> array;

for (int i = 0; i < 1000; i++)
{
	if (array.Count() == array.GetMaxCount() - 1)
		break;

	array.Add(1);
	array.Add(100);
	array.Add(14);
	array.Add(4);
	array.Add(2);
	array.Add(3);
}
```