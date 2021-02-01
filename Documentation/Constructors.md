//////////////////////////////////////////std::vector//////////////////////////////////////////////////////

DynamicArray(const std::vector<T>& Elements)

Elements - std::vector<T> from which copy data to DynamicArray(Count of list is equals Elements.size())

Example:

```C++
std::vector<int> vector(3);
vector[0] = 1;
vector[1] = 1000;
vector[2] = 20;

DynamicArray<int> array(vector);
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////initializer_list//////////////////////////////////////////////////////

DynamicArray(const std::initializer_list<T>& elements)

Elements - std::initializer_list<T> from which copy data to DynamicArray(Count of list is equals elements.size())

Example:

```C++
Bear::DynamicArray<int> array{ 1, 100, 14, 4, 2, 3 };

for (const auto& item : array)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////DynamicArray/////////////////////////////////////////////////////////////

DynamicArray(const DynamicArray<T>& Elements)

Elements - other DynamicArray<T> from which copy data to this DynamicArray(Count of list is equals Elements.Count())

Example:

```C++
DynamicArray<float> firstArray(3);
firstArray[0] = 1.0f;
firstArray[1] = 1000.0f;
firstArray[2] = 20.0f;

DynamicArray<float> array(firstArray);
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Count////////////////////////////////////////////////////////////

DynamicArray(const DynamicArrayUInt& Count)

Count - count of elements in list

This constructor create empty elements

Example:

```C++
DynamicArray<unsigned int> array(3);
array[0] = 2000;
array[1] = 100;
array[2] = 1;
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Array////////////////////////////////////////////////////////////

DynamicArray(const T* Array, const DynamicArrayUInt& Count)

Array - array of elements T
Count - count of Array

This constructor create DynamicArray of "Count" elements and copy from "Array"

Example:

```C++
int array[]{ 5, 45};

Bear::DynamicArray<int> dynamicArray(array, sizeof(array) / sizeof(array[0]));

for (const auto& item : dynamicArray)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Value for items//////////////////////////////////////////////////

DynamicArray(const DynamicArrayUInt& Count, const T& Value)

Count - List size
Value - All items will be the same "Value"

Create list with count "Count" and set all items to "Value"

//////////////////////////////////////////Empty////////////////////////////////////////////////////////////

DynamicArray()

This constructor create empty DynamicArray

Example:

```C++
class TestClass
{
public:
	TestClass() {};
};

DynamicArray<TestClass> array;
array.Add({});
array.Add({});
array.Add({});
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////