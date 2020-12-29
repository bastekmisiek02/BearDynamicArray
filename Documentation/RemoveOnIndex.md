"RemoveOnIndex" - remove elements from first argument index to second argument or to end

//////////////////////////////////////////Only 1 Argument//////////////////////////////////////////////////////

void RemoveOnIndex(const Uint& Start)

Start - first index to remove

Remove elements from "Start" to end of List

Example:

```C++
List<int> list;

list.Add(1);
list.Add(100);
list.Add(14);
list.Add(4);
list.Add(2);
list.Add(3);

list.RemoveOnIndex(1, 3);

for (const auto& item : list)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////2 arguments//////////////////////////////////////////////////////

void RemoveOnIndex(const Uint& Start, const Uint& End)

Start - first index to remove
End - last index to remove

Remove elements from "Start" to "End" index

Example:

```
List<int> list;

list.Add(1);
list.Add(100);
list.Add(14);
list.Add(4);
list.Add(2);
list.Add(3);

list.RemoveOnIndex(1);

for (const auto& item : list)
	std::cout << item << "\n";
```

///////////////////////////////////////////////////////////////////////////////////////////////////////////