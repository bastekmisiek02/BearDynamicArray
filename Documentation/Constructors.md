//////////////////////////////////////////std::vector//////////////////////////////////////////////////////

List(const std::vector<T>& Elements)

Elements - std::vector<T> from which copy data to List(Count of list is equals Elements.size())

Example:

std::vector<int> vector(3);
vector[0] = 1;
vector[1] = 1000;
vector[2] = 20;

List<int> list(vector);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////List/////////////////////////////////////////////////////////////

List(const List<T>& Elements)

Elements - other List<T> from which copy data to this List(Count of list is equals Elements.Count())

Example:

List<float> firstList(3);
firstList[0] = 1.0f;
firstList[1] = 1000.0f;
firstList[2] = 20.0f;

List<float> list(firstList);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Count////////////////////////////////////////////////////////////

List(const BearListInt& Count)

Count - count of elements in list

This constructor create empty elements

Example:

List<unsigned int> list(3);
list[0] = 2000;
list[1] = 100;
list[2] = 1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Array////////////////////////////////////////////////////////////

List(const T* Array, const ListUInt& Count)

Array - array of elements T
Count - count of Array

This constructor create list of "Count" elements and copy from "Array"

Example:

int array[]{ 5, 45};

Bear::List<int> list(array, sizeof(array) / sizeof(array[0]));

for (const auto& item : list)
	std::cout << item << "\n";

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////Value for items//////////////////////////////////////////////////

List(const ListUInt& Count, const T& Value)

Count - List size
Value - All items will be the same "Value"

Create list with count "Count" and set all items to "Value"

//////////////////////////////////////////Empty////////////////////////////////////////////////////////////

List()

This constructor create empty List

Example:

class TestClass
{
public:
	TestClass() {};
};

List<TestClass> list;
list.Add({});
list.Add({});
list.Add({});

///////////////////////////////////////////////////////////////////////////////////////////////////////////