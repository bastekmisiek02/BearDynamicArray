"Resize" - Resize the DynamicArray to "Count" size

//////////////////////////////////////////without value//////////////////////////////////////////////////////

void Resize(const DynamicArrayUint& Count)

Elements of DynamicArray are empty

Example:

```C++
DynamicArray<int> array;

int count;

std::cout << "Type count of DynamicArray: \n";
std::cin >> count;

array.Resize(count);

std::cout << "DynamicArray size: " << array.Count() << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////with value///////////////////////////////////////////////////////

void Resize(const DynamicArrayUint& Count, const T& value)

Elements of list are equals of "value"

Example:

```C++
DynamicArray<int> array;

int count;

std::cout << "Type count of DynamicArray: \n";
std::cin >> count;

int value;

std::cout << "Type value of DynamicArray: \n";
std::cin >> value;

array.Resize(count, value);

for (DynamicArrayUint i = 0; i < array.Count(); i++)
	std::cout << "Value : " << i << " = " << array[i] << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////