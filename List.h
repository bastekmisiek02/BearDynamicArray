#pragma once

#if __has_include(<vector>)
	#include <vector>
#endif

namespace Bear
{
	#ifdef _WIN64
		typedef unsigned long long int BearListInt;
	#else
		typedef unsigned int BearListInt;
	#endif

	template <typename T>
	class List
	{
	private:
		BearListInt count;
	private:
		T* items;
	private:
		T& GetFromIndex(const BearListInt& index) const
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

			for (BearListInt i = 0; i < Elements.size(); i++)
			{
				items[i] = Elements[i];
			}
		}
		#endif

		List(const List<T>& Elements)
			: count(Elements.count)
		{
			items = new T[Elements.count];

			for (BearListInt i = 0; i < Elements.count; i++)
			{
				items[i] = Elements[i];
			}
		}

		List(const BearListInt& Count)
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
		const bool Exist(const T& Element) const
		{
			for (BearListInt i = 0; i < count; i++)
			{
				if (items[i] == Element)
					return true;
			}

			return false;
		}

		void AddCollection(const List<T>& Elements)
		{
			T* array = new T[count];

			for (BearListInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + Elements.count];

			for (BearListInt i = 0; i < count; i++)
				this->items[i] = array[i];

			for (BearListInt i = count; i < count + Elements.count; i++)
				this->items[i] = Elements[i - count];

			delete[] array;

			count += Elements.count;
		}

		#if __has_include(<vector>)
		void AddCollection(const std::vector<T>& Elements)
		{
			T* array = new T[count];

			for (BearListInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + Elements.size()];

			for (BearListInt i = 0; i < count; i++)
				this->items[i] = array[i];

			for (BearListInt i = count; i < count + Elements.size(); i++)
				this->items[i] = Elements[i - count];

			delete[] array;

			count += Elements.size();
		}
		#endif

		void Add(const T& Element)
		{
			T* array = new T[count];

			for (BearListInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + 1];

			for (BearListInt i = 0; i < count; i++)
				this->items[i] = array[i];

			this->items[count] = Element;

			delete[] array;

			count++;
		}

		void DeleteCollection(const List<T>& Elements, const bool& removeAll = false)
		{
			if (!items || !count)
				throw std::exception("List is clear");

			T* array = new T[count];

			if (removeAll)
			{
				BearListInt iterator = 0;
				BearListInt removeItems = 0;
				for (BearListInt i = 0; i < count; i++)
				{
					if (!Elements.Exist(items[i]))
					{
						array[iterator] = this->items[i];
						iterator++;
					}
					else
						removeItems++;
				}

				count -= removeItems;
				delete[] this->items;

				this->items = new T[count];

				for (BearListInt i = 0; i < count; i++)
					this->items[i] = array[i];

				delete[] array;
			}
			else
			{
				for (BearListInt i = 0; i < Elements.count - 1; i++)
					Delete(Elements[i], false);
			}
		}

		#if __has_include(<vector>)
		void DeleteCollection(const std::vector<T>& Elements, const bool& removeAll = false)
		{
			if (!items || !count)
				throw std::exception("List is clear");

			if (removeAll)
			{
				T* array = new T[count];

				BearListInt iterator = 0;
				BearListInt removeItems = 0;
				for (BearListInt i = 0; i < count; i++)
				{
					if (std::find(Elements.begin(), Elements.end(), items[i]) == Elements.end())
					{
						array[iterator] = this->items[i];
						iterator++;
					}
					else
						removeItems++;
				}

				delete[] this->items;

				count -= removeItems;

				this->items = new T[count];

				for (BearListInt i = 0; i < count; i++)
					this->items[i] = array[i];

				delete[] array;
			}
			else
			{
				for (BearListInt i = 0; i < Elements.size(); i++)
					Delete(Elements[i], false);
			}
		}
		#endif

		void Delete(const T& Element, const bool& removeAll = false)
		{
			if (!items || !count)
				throw std::exception("List is clear");

			T* array = new T[count];

			if (removeAll)
			{
				BearListInt j = 0;
				BearListInt removeItems = 0;
				for (BearListInt i = 0; i < count; i++)
				{
					if (this->items[i] != Element)
					{
						array[j] = this->items[i];
						j++;
					}
					else
						removeItems++;
				}

				count -= removeItems;
			}
			else
			{
				bool found = false;
				for (BearListInt i = 0; i < count; i++)
				{
					if (this->items[i] != Element || found)
						array[i - found] = this->items[i];
					else
						found = true;
				}

				count--;
			}

			delete[] this->items;

			this->items = new T[count];

			for (BearListInt i = 0; i < count; i++)
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

		const BearListInt GetMaxCount() const
		{
			#ifdef _WIN64
				return ULLONG_MAX;
			#else
				return INT_MAX;
			#endif
		}

		const BearListInt Count() const
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

		void Sort(const bool (*SortFunc)(const T& firstElement, const T& secondElement)) const
		{
			if (!items || !count)
				throw std::exception("List is clear");

			if (count == 1)
				return;

			for (BearListInt i = 1; i < count; i++)
			{
				T* firstElement = &items[i - 1];
				T* secondElement = &items[i];

				for (BearListInt j = 0; j < i; j++)
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

		void Swap(List<T>& elements)
		{
			T* items = new T[count];
			BearListInt count = this->count;

			for (BearListInt i = 0; i < count; i++)
			{
				items[i] = this->items[i];
			}

			delete[] this->items;

			this->items = elements.items;
			elements.items = items;

			this->count = elements.count;
			elements.count = count;
		}

		#if __has_include(<vector>)
		void Swap(std::vector<T>& elements)
		{
			T* items = new T[count];
			BearListInt count = this->count;

			for (BearListInt i = 0; i < count; i++)
				items[i] = this->items[i];

			delete[] this->items;

			this->count = elements.size();

			T* vectorItems = new T[elements.size()];

			for (BearListInt i = 0; i < elements.size(); i++)
				vectorItems[i] = elements[i];

			this->items = vectorItems;

			elements.resize(count);

			for (BearListInt i = 0; i < count; i++)
				elements[i] = items[i];

			delete[] items;
		}
		#endif

		void Resize(const BearListInt& Count)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;
		}

		void Resize(const BearListInt& Count, const T& value)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;

			for (BearListInt i = 0; i < Count; i++)
				items[i] = value;
		}

		#if __has_include(<vector>)
		std::vector<T> ToVector() const
		{
			std::vector<T> vector(count);

			for (BearListInt i = 0; i < count; i++)
			{
				vector[i] = items[i];
			}

			return vector;
		}
		#endif

		T* ToArray(BearListInt* Count = nullptr) const
		{
			T* array = new T[count];

			for (BearListInt i = 0; i < count; i++)
				array[i] = items[i];

			if(Count)
				*Count = count;

			return array;
		}

	public:
		void operator=(const List<T>& elements)
		{
			delete[] this->items;

			items = new T[elements.count];

			count = elements.count;

			for (BearListInt i = 0; i < count; i++)
				items[i] = elements[i];
		}

		#if __has_include(<vector>)
		void operator=(const std::vector<T>& elements)
		{
			delete[] this->items;

			items = new T[elements.size()];

			count = elements.size();

			for (BearListInt i = 0; i < count; i++)
				items[i] = elements[i];
		}
		#endif

		const bool operator==(const List<T>& elements) const
		{
			for (BearListInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}

		#if __has_include(<vector>)
		const bool operator==(const std::vector<T>& elements) const
		{
			for (BearListInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}
		#endif

		const bool operator==(const T& element) const
		{
			return Exist(element);
		}

		const bool operator!=(const List<T>& elements) const
		{
			for (BearListInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}

		#if __has_include(<vector>)
		const bool operator!=(const std::vector<T>& elements) const
		{
			for (BearListInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}
		#endif

		const bool operator!=(const T& element) const
		{
			return (!Exist(element));
		}

		void operator+=(const List<T>& elements)
		{
			AddCollection(elements);
		}

		#if __has_include(<vector>)
		void operator+=(const std::vector<T>& elements)
		{
			AddCollection(elements);
		}
		#endif

		void operator+=(const T& element)
		{
			Add(element);
		}

		void operator-=(const List<T>& elements)
		{
			DeleteCollection(elements);
		}

		#if __has_include(<vector>)
		void operator-=(const std::vector<T>& elements)
		{
			DeleteCollection(elements);
		}
		#endif

		void operator-=(const T& element)
		{
			Delete(element);
		}

		T& operator[](const BearListInt& index) const
		{
			return GetFromIndex(index);
		}
	};
}