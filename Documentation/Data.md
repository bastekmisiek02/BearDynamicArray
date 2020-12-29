"Data" - Return pointer to element storage. It equals address of first element.

const T* Data() const
T* Data()

Example:

List<int> list;

list.Add(2);
list.Add(1);
list.Add(3);

std::cout << *list.Data() << "\n";