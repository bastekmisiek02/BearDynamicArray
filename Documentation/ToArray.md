"ToArray" - create new array on heap allocation and fill elements(count of array equals array.Count())

T* ToArray(DynamicArrayUInt* Count = nullptr)

const T* ToArray(DynamicArrayUInt* Count = nullptr) const

Count - if "Count" not null *Count equals array.Count()

"ToArray" return T array(remeber use delete if not use them)

Example:

```C++
DynamicArray<int> dynamicArray;

for (int i = 0; i < 1000; i++)
{
	dynamicArray.Add(1);
	dynamicArray.Add(100);
	dynamicArray.Add(14);
	dynamicArray.Add(4);
	dynamicArray.Add(2);
	dynamicArray.Add(3);
}

DynamicArrayUint count;
int* array = dynamicArray.ToArray(&count);

for (DynamicArrayUint i = 0; i < count; i++)
	std::cout << array[i] << "\n";

delete[] array;
```