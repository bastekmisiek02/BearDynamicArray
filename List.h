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

	private:
		BearListLongInt count;
	private:
		T* items;
	private:
		const T& GetFromIndex(const BearListLongInt& index) const
		{
			if (index > count - 1)
				throw std::exception("Index is greater than count");

			if (index < 0)
				throw std::exception("Index must be greater than 0");

			if (!count)
				throw std::exception("List is clear");

			return items[index];
		}
	public:
		#if __has_include(<vector>)
			List(const std::vector<T>& Elements)
				: count(Elements.size())
			{
				items = new T[Elements.size()];

				for (BearListLongInt i = 0; i < Elements.size(); i++)
				{
					items[i] = Elements[i];
				}
			}
		#endif

		List(const List<T>& Elements)
			: count(Elements.count)
		{
			items = new T[Elements.count];

			for (BearListLongInt i = 0; i < Elements.count; i++)
			{
				items[i] = Elements[i];
			}
		}

		List(const BearListLongInt& Count)
			: count(Count)
		{
			items = new T[Count];
		}

		List()
			: count(0)
		{
			items = new T[0];
		}

		~List()
		{
			Clear();
		}
	public:
		const bool& Exist(const T& element)
		{
			for (BearListLongInt i = 0; i < count; i++)
			{
				if (items[i] == element)
					return true;
			}

			return false;
		}

		void Add(const T& Element)
		{
			T* array = new T[count];

			for (BearListLongInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + 1];

			for (BearListLongInt i = 0; i < count; i++)
				this->items[i] = array[i];

			this->items[count] = Element;

			delete[] array;

			count++;
		}

		void Delete(const T& Element, const bool& checkToExist = true)
		{
			if (!items || !count)
				throw std::exception("List is clear");

			if (checkToExist)
			{
				if (!Exist(Element))
					throw std::exception("Can't find this element");
			}

			T* array = new T[count - 1];

			int j = 0;
			int removeItems = 0;
			for (BearListLongInt i = 0; i < count; i++)
			{
				if (this->items[i] != Element)
				{
					array[j] = this->items[i];
					j++;
				}
				else
					removeItems++;
			}

			delete[] this->items;

			count -= removeItems;

			this->items = new T[count];

			for (BearListLongInt i = 0; i < count; i++)
				this->items[i] = array[i];

			delete[] array;
		}

		T& GetFirst() const
		{
			if (!count)
				throw std::exception("First Element is null");

			return items[0];
		}

		T& GetLast() const
		{
			if (!count)
				throw std::exception("Last Element is null");

			return items[count - 1];
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
			delete[] items;
			items = nullptr;
			count = 0;
		}

		T* Data() const
		{
			return items;
		}

		void Foreach(void(*ForeachFunc)(const T& element,const int& iterator))
		{
			for (BearListLongInt i = 0; i < count; i++)
				ForeachFunc(items[i], i);
		}

		void Sort(const bool& (*SortFunc)(const T& firstElement, const T& secondElement)) const
		{
			if (!items || !count)
				throw std::exception("List is clear");

			if (count == 1)
				return;

			for (BearListLongInt i = 1; i < count; i++)
			{
				T* firstElement = &items[i - 1];
				T* secondElement = &items[i];

				for (BearListLongInt j = 0; j < i; j++)
				{
					if (!SortFunc(*firstElement, *secondElement))
					{
						const T helpItem = *firstElement;
						*firstElement = *secondElement;
						*secondElement = helpItem;

						firstElement = &items[i - j - 2];
						secondElement = &items[i - j - 1];
					}
					else
						break;
				}
			}
		}

		void Resize(const BearListLongInt& Count)
		{
			if(items)
				delete[] items;

			items = new T[Count];
			
			count = Count;
		}

		void Resize(const BearListLongInt& Count, const T value)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;

			for (BearListLongInt i = 0; i < Count; i++)
			{
				items[i] = value;
			}
		}

		#if __has_include(<vector>)
		std::vector<T> ToVector() const
		{
			std::vector<T> vector(count);

			for (BearListLongInt i = 0; i < count; i++)
			{
				vector[i] = items[i];
			}

			return vector;
		}
		#endif

	public:
		T& operator[](const BearListLongInt& Index) const
		{
			return (T&)GetFromIndex(Index);
		}
	};
}