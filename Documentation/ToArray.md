"ToArray" - create new array on heap allocation and fill elements(count of array equals list.Count())

T* ToArray(ListUInt* Count = nullptr)

const T* ToArray(ListUInt* Count = nullptr) const

Count - if "Count" not null *Count equals list.Count()

"ToArray" return T array(remeber use delete if not use them)

Example:

List<int> list;

for (int i = 0; i < 1000; i++)
{
	list.Add(1);
	list.Add(100);
	list.Add(14);
	list.Add(4);
	list.Add(2);
	list.Add(3);
}

Uint count;
int* array = list.ToArray(&count);

for (Uint i = 0; i < count; i++)
	std::cout << array[i] << "\n";

delete[] array;