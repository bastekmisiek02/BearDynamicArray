"ToVector" - create new std::vector and fill elements(count of vector equals array.Count())

std::vector<T> ToVector()
const std::vector<T> ToVector() const

"ToVector" return std::vector<T>

Example:

```C++
DynamicArray<int> array;

for (int i = 0; i < 1000; i++)
{
	array.Add(1);
	array.Add(100);
	array.Add(14);
	array.Add(4);
	array.Add(2);
	array.Add(3);
}

std::vector<int> vector = array.ToVector();

for (const auto& item : vector)
	std::cout << item << "\n";
```