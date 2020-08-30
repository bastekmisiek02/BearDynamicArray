#pragma once

#if __has_include(<vector>)
	#include <vector>
#endif

namespace Bear
{
	template <typename T>
	class List
	{
		typedef unsigned long long int BearListLongInt;

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
		BearListLongInt count;
	private:
		ListElements* firstElement;
		ListElements* lastElement;
	private:
		const T* GetFromIndex(const BearListLongInt& index) const
		{
			#ifndef BEAR_LIST_NOT_EXCEPTIONS
				if (index > count - 1)
					throw std::exception("Index is greater than count");
				
				if (index < 0)
					throw std::exception("Index must be greater than 0");
				
				if (!count)
					throw std::exception("List is clear");
			#endif

			BearListLongInt i = 0;

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
		#if __has_include(<vector>)
		List(const std::vector<T>& elements)
		{
			for (BearListLongInt i = 0; i < elements.size(); i++)
			{
				Add(elements[i]);
			}
		}
		#endif

		List(const List<T>& elements)
		{
			for (BearListLongInt i = 0; i < elements.count; i++)
			{
				Add(*elements.GetFromIndex(i));
			}
		}

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

		T& GetFirst() const
		{
			#ifndef BEAR_LIST_NOT_EXCEPTIONS
				if (!count)
					throw std::exception("First Element is null");
			#endif

			return *firstElement->element;
		}

		T& GetLast() const
		{
#			ifndef BEAR_LIST_NOT_EXCEPTIONS
				if (!count)
					throw std::exception("Last Element is null");
			#endif

			return *lastElement->element;
		}

		const BearListLongInt& GetMaxCount() const
		{
			return ULLONG_MAX;
		}

		const BearListLongInt& Count() const
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

		void Sort(const bool& (*SortFunc)(const T& firstElement, const T& secondElement)) const
		{
			#ifndef BEAR_LIST_NOT_EXCEPTIONS
			if (!count)
				throw std::exception("List is clear");
			#endif

			if (count == 1)
				return;

			ListElements* firstElement = this->firstElement;

			List<T> list;
			list.Add(*firstElement->element);

			for (BearListLongInt i = 1; i < count; i++)
			{
				firstElement = firstElement->nextElement;
				ListElements* secondElement = firstElement;

				list.Add(*secondElement->element);

				ListElements* lePtr = firstElement;

				for (BearListLongInt j = 0; j < list.count - 1; j++)
				{
					if (!(SortFunc(*lePtr->previewElement->element, *secondElement->element)))
					{
						const T helpItem = *lePtr->previewElement->element;
						*lePtr->previewElement->element = *secondElement->element;
						*secondElement->element = helpItem;

						lePtr = lePtr->previewElement;
						secondElement = lePtr;
					}
				}
			}
		}

	public:
		T& operator[](const BearListLongInt& index)
		{
			return (T&)*GetFromIndex(index);
		}
	};
}