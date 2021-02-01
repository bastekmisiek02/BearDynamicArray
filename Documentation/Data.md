"Data" - Return pointer to element storage. It equals address of first element.

const T* Data() const
T* Data()

Example:

```C++
DynamicArray<int> array;

array.Add(2);
array.Add(1);
array.Add(3);

std::cout << *array.Data() << "\n";
```