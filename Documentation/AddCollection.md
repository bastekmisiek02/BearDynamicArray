"AddCollection" - add elements to DynamicArray

//////////////////////////////////////////std::vector//////////////////////////////////////////////////////

AddCollection(const std::vector<T>& Elements)

Elements - std::vector<T> from which copy data to DynamicArray

Example:

```C++
std::vector<int> vector(3);
vector[0] = 1;
vector[1] = 1000;
vector[2] = 20;

DynamicArray<int> array;

array.AddCollection(vector);
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////DynamicArray/////////////////////////////////////////////////////////////

AddCollection(const DynamicArray<T>& Elements)

Elements - other DynamicArray<T> from which copy data to this DynamicArray

Example:

```C++
DynamicArray<float> firstArray(3);
firstArray[0] = 1.0f;
firstArray[1] = 1000.0f;
firstArray[2] = 20.0f;

DynamicArray<float> array;

array.AddCollection(firstArray);
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////