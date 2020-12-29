"ToVector" - create new std::vector and fill elements(count of vector equals list.Count())

std::vector<T> ToVector()
const std::vector<T> ToVector() const

"ToVector" return std::vector<T>

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

std::vector<int> vector = list.ToVector();

for (const auto& item : vector)
	std::cout << item << "\n";