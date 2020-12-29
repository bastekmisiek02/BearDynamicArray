"Resize" - Resize the list to "Count" size

//////////////////////////////////////////without value//////////////////////////////////////////////////////

void Resize(const Uint& Count)

Elements of list are empty

Example:

```C++
List<int> list;

int count;

std::cout << "Type count of list: \n";
std::cin >> count;

list.Resize(count);

std::cout << "List size: " << list.Count() << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////with value///////////////////////////////////////////////////////

void Resize(const Uint& Count, const T& value)

Elements of list are equals of "value"

Example:

```C++
List<int> list;

int count;

std::cout << "Type count of list: \n";
std::cin >> count;

int value;

std::cout << "Type value of list: \n";
std::cin >> value;

list.Resize(count, value);

for (Uint i = 0; i < list.Count(); i++)
	std::cout << "Value : " << i << " = " << list[i] << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////