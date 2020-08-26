#pragma once

namespace BearList
{
	template <typename T>
	class List
	{
		struct ListElements
		{
			ListElements()
				:nextElement(nullptr), previewElement(nullptr)
			{
			}

			ListElements(ListElements* NextElement, ListElements* PreviewElement, const T* Element)
				: nextElement(NextElement), previewElement(PreviewElement), element((T*)Element)
			{
			}

			~ListElements()
			{
				nextElement = nullptr;
				previewElement = nullptr;

				element = nullptr;
			}

			T* element;

			ListElements* nextElement;
			ListElements* previewElement;
		};

	private:
		unsigned long long int count;
	private:
		ListElements* firstElement;
		ListElements* lastElement;
	private:
		const T* GetFromIndex(const unsigned long long int& index) const
		{
			#ifndef BEAR_LIST_NOT_EXCEPTIONS
				if (index > count - 1)
					throw std::exception("Index is greater than count");
				
				if (index < 0)
					throw std::exception("Index must be greater than 0");
				
				if (!count)
					throw std::exception("List is clear");
			#endif

			int i = 0;

			ListElements* le = firstElement;

			while (le != nullptr)
			{
				if (i == index)
					return le->element;

				i++;
				le = le->nextElement;
			}

			return nullptr;
		}
	public:
		List()
			: count(0), firstElement(nullptr), lastElement(nullptr)
		{
		}

		~List()
		{
			Clear();
		}
	public:
		void Add(const T& Element)
		{
			switch (count)
			{
				case 0:
				{
					firstElement = new ListElements(nullptr, nullptr, &Element);
					lastElement = firstElement;
					count++;
					break;
				}
				case 1:
				{
					firstElement->nextElement = new ListElements(nullptr, firstElement, &Element);
					lastElement = firstElement->nextElement;
					count++;
					break;
				}
				default:
				{
					lastElement->nextElement = new ListElements(nullptr, lastElement, &Element);
					lastElement = lastElement->nextElement;
					count++;
					break;
				}
			}
		}

		const bool& Delete(const T& Element)
		{
			switch (count)
			{
			case 0:
				throw std::exception("List is clear");
			case 1:
			{
				if (*firstElement->element == Element)
				{
					delete firstElement;
					firstElement = nullptr;
					count--;
				}
				return true;
			}
			case 2:
			{
				if (*firstElement->element == Element)
				{
					delete firstElement;
					firstElement = lastElement;

					lastElement = nullptr;
				}
				else
				{
					delete lastElement;
					lastElement = nullptr;

					firstElement->nextElement = nullptr;
				}

				count--;

				return true;
			}
			default:
			{
				if (*firstElement->element == Element)
				{
					firstElement->element = nullptr;
					firstElement->nextElement->previewElement = nullptr;

					ListElements* element = firstElement->nextElement;
					delete firstElement;

					firstElement = element;
				}
				else if (*lastElement->element == Element)
				{
					lastElement->element = nullptr;
					lastElement->previewElement->nextElement = nullptr;

					ListElements* element = lastElement->previewElement;
					delete lastElement;

					lastElement = element;
				}
				else
				{
					ListElements* element = firstElement;

					while (element->nextElement != nullptr)
					{
						if (*element->element == Element)
						{
							ListElements* previewElement = element->previewElement;
							ListElements* nextElement = element->nextElement;

							previewElement->nextElement = nextElement;
							nextElement->previewElement = previewElement;

							delete element;

							break;
						}

						element = element->nextElement;
					}

					if (element == lastElement)
						return false;
				}

				count--;

				return true;
			}
			}
		}

		void DeleteFromIndex(const int& index)
		{
			Delete(*(GetFromIndex(index)));
		}

		T* GetFirst() const
		{
			#ifndef BEAR_LIST_NOT_EXCEPTIONS
				if (!count)
					throw std::exception("First Element is null");
			#endif

			return firstElement->element;
		}

		T* GetLast() const
		{
#			ifndef BEAR_LIST_NOT_EXCEPTIONS
				if (!count)
					throw std::exception("Last Element is null");
			#endif

			return lastElement->element;
		}

		const unsigned long long int& GetMaxCount() const
		{
			return ULLONG_MAX;
		}

		const unsigned long long int& Count() const
		{
			return count;
		}

		void Clear()
		{
			while (count)
			{
				ListElements* element = lastElement->previewElement;
				delete lastElement;

				lastElement = element;
				count--;
			}

			firstElement = nullptr;
		}

		void Sort(const bool& (*SortFunc)(const T& firstElement, const T& secondElement))
		{
			List<T> list;

			for (int i = 0; i < count; i++)
			{
				T firstItem = (*(GetFromIndex(i)));

				if (firstItem == *lastElement->element)
					break;

				T secondItem = (*(GetFromIndex(i + 1)));
				list.Add(firstItem);

				for (int j = 0; j < list.count; j++)
				{
					if (SortFunc(firstItem, secondItem))
					{
						const T helpItem = firstItem;
						firstItem = secondItem;
						secondItem = helpItem;
					}
				}
			}

			for (int i = 0; i < list.Count(); i++)
			{
				std::cout << *list[i] << "\n";
			}

			std::cout << "------------------------------" << "\n";

			//for (int i = 0; i < count; i++)
			//{
			//	ListElements* iterator = firstElement;

			//	while (iterator->nextElement)
			//	{

			//		iterator = iterator->nextElement;
			//	}
			//}
		}

	public:
		T* operator[](const unsigned long long int& index)
		{
			return (T*)GetFromIndex(index);
		}
	};
}