"GetMaxCount" - Return max ciunt of list

const Uint GetMaxCount() const

Example:

List<int> list;

for (int i = 0; i < 1000; i++)
{
	if (list.Count() == list.GetMaxCount() - 1)
		break;

	list.Add(1);
	list.Add(100);
	list.Add(14);
	list.Add(4);
	list.Add(2);
	list.Add(3);
}