"AddCollection" - add elements to List

//////////////////////////////////////////std::vector//////////////////////////////////////////////////////

AddCollection(const std::vector<T>& Elements)

Elements - std::vector<T> from which copy data to List

Example:

std::vector<int> vector(3);
vector[0] = 1;
vector[1] = 1000;
vector[2] = 20;

List<int> list;

list.AddCollection(vector);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////List/////////////////////////////////////////////////////////////

AddCollection(const List<T>& Elements)

Elements - other List<T> from which copy data to this List

Example:

List<float> firstList(3);
firstList[0] = 1.0f;
firstList[1] = 1000.0f;
firstList[2] = 20.0f;

List<float> list;

list.AddCollection(firstList);

///////////////////////////////////////////////////////////////////////////////////////////////////////////