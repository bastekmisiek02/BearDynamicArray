#pragma once

#if __has_include(<vector>)
	#define BEAR_LIST_VECTOR_ADDED
	#include <vector>
#endif

#ifdef _WIN64
	#define BEAR_LIST_WIN64
#endif

namespace Bear
{

#ifdef BEAR_LIST_WIN64
	typedef unsigned long long int ListUInt;
#else
	typedef unsigned int ListUInt;
#endif

	enum class ListException
	{
		StartIndexGreaterThanEnd, OutOfRange, IndexGreater, IndexLower, ListClear
	};

	template <typename T>
	class List
	{
	private:
		ListUInt count;
	private:
		T* items;
	private:
		T& GetFromIndex(const ListUInt& index) const
		{
			if (index > count - 1)
				throw ListException::IndexGreater;

			if (index < 0)
				throw ListException::IndexLower;

			if (!count)
				throw ListException::ListClear;

			return items[index];
		}
	public:
		#ifdef BEAR_LIST_VECTOR_ADDED
		List(const std::vector<T>& Elements)
			: count(Elements.size())
		{
			items = new T[Elements.size()];

			for (ListUInt i = 0; i < Elements.size(); i++)
				items[i] = Elements[i];
		}
		#endif

		List(const List<T>& Elements)
			: count(Elements.count)
		{
			items = new T[Elements.count];

			for (ListUInt i = 0; i < Elements.count; i++)
				items[i] = Elements[i];
		}

		List(const ListUInt& Count)
			: count(Count)
		{
			items = new T[Count];
		}

		List(const T* Array, const ListUInt& Count)
			: count(Count)
		{
			items = new T[Count];

			for (ListUInt i = 0; i < Count; i++)
				items[i] = Array[i];
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
		template<typename T>
		class Iterator
		{
		private:
			T* ptr;
		public:
			Iterator(T* Ptr)
				: ptr(Ptr)
			{
			}

			const T& operator*() const
			{
				return *ptr;
			}

			T& operator*()
			{
				return *ptr;
			}

			const Iterator& operator++()
			{
				ptr++;
				return *this;
			}

			bool operator==(const Iterator& other)
			{
				return ptr == other.ptr;
			}

			const bool operator==(const Iterator& other) const
			{
				return ptr == other.ptr;
			}

			bool operator!=(const Iterator& other)
			{
				return ptr != other.ptr;
			}

			const bool operator!=(const Iterator& other) const
			{
				return ptr != other.ptr;
			}
		};
	public:
		const bool Exist(const T& Element, const bool FromEnd = false, ListUInt* Index = nullptr) const
		{
			if (FromEnd)
			{
				#ifdef BEAR_LIST_WIN64
				typedef long long int Int;
				#else
				typedef int Int;
				#endif

				for (Int i = count - 1; i > -1; i--)
				{
					if (items[i] == Element)
					{
						if (Index)
							*Index = i;

						return true;
					}
				}
			}
			else
			{
				for (ListUInt i = 0; i < count; i++)
				{
					if (items[i] == Element)
					{
						if (Index)
							*Index = i;

						return true;
					}
				}
			}

			return false;
		}

		void AddCollection(const List<T>& Elements)
		{
			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + Elements.count];

			for (ListUInt i = 0; i < count; i++)
				this->items[i] = array[i];

			for (ListUInt i = count; i < count + Elements.count; i++)
				this->items[i] = Elements[i - count];

			delete[] array;

			count += Elements.count;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		void AddCollection(const std::vector<T>& Elements)
		{
			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + Elements.size()];

			for (ListUInt i = 0; i < count; i++)
				this->items[i] = array[i];

			for (ListUInt i = count; i < count + Elements.size(); i++)
				this->items[i] = Elements[i - count];

			delete[] array;

			count += Elements.size();
		}
		#endif

		void Add(const T& Element)
		{
			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = this->items[i];

			delete[] this->items;

			this->items = new T[count + 1];

			for (ListUInt i = 0; i < count; i++)
				this->items[i] = array[i];

			this->items[count] = Element;

			delete[] array;

			count++;
		}

		void RemoveCollection(const List<T>& Elements, const bool& removeAll = false)
		{
			if (!items || !count)
				throw ListException::ListClear;

			T* array = new T[count];

			if (removeAll)
			{
				ListUInt iterator = 0;
				ListUInt removeItems = 0;
				for (ListUInt i = 0; i < count; i++)
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

				for (ListUInt i = 0; i < count; i++)
					this->items[i] = array[i];

				delete[] array;
			}
			else
			{
				for (ListUInt i = 0; i < Elements.count - 1; i++)
					Remove(Elements[i], false);
			}
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		void RemoveCollection(const std::vector<T>& Elements, const bool& removeAll = false)
		{
			if (!items || !count)
				throw ListException::ListClear;

			if (removeAll)
			{
				T* array = new T[count];

				ListUInt iterator = 0;
				ListUInt removeItems = 0;
				for (ListUInt i = 0; i < count; i++)
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

				for (ListUInt i = 0; i < count; i++)
					this->items[i] = array[i];

				delete[] array;
			}
			else
			{
				for (ListUInt i = 0; i < Elements.size(); i++)
					Remove(Elements[i], false);
			}
		}
		#endif

		void Remove(const T& Element, const bool& removeAll = false)
		{
			if (!items || !count)
				throw ListException::ListClear;

			T* array = new T[count];

			if (removeAll)
			{
				ListUInt j = 0;
				ListUInt removeItems = 0;
				for (ListUInt i = 0; i < count; i++)
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
				for (ListUInt i = 0; i < count; i++)
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

			for (ListUInt i = 0; i < count; i++)
				this->items[i] = array[i];

			delete[] array;
		}

		void RemoveOnIndex(const ListUInt& Start, const ListUInt& End)
		{
			if (!items || !count)
				throw ListException::ListClear;

			if (Start > count || End > count)
				throw ListException::OutOfRange;

			if (Start > End)
				throw ListException::StartIndexGreaterThanEnd;

			T* array = new T[count];

			ListUInt j = 0;
			for (ListUInt i = 0; i < count; i++)
			{
				if (!(i >= Start && i <= End))
					array[i - j] = items[i];
				else
					j++;
			}

			delete[] items;

			count -= (End - Start) + 1;

			items = new T[count];

			for (ListUInt i = 0; i < count; i++)
				items[i] = array[i];

			delete[] array;
		}

		void RemoveOnIndex(const ListUInt& Start)
		{
			if (!items || !count)
				throw ListException::ListClear;

			if (Start > count)
				throw ListException::OutOfRange;

			count = Start;

			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = items[i];

			delete[] items;

			items = new T[count];

			for (ListUInt i = 0; i < count; i++)
				items[i] = array[i];

			delete[] array;
		}

		Iterator<T> begin()
		{
			return Iterator<T>(items);
		}

		Iterator<T> end()
		{
			return Iterator<T>(items + count);
		}

		const Iterator<T> begin() const
		{
			return Iterator<T>(items);
		}

		const Iterator<T> end() const
		{
			return Iterator<T>(items + count);
		}

		const ListUInt GetMaxCount() const
		{
			#ifdef BEAR_LIST_WIN64
				return ULLONG_MAX;
			#else
				return INT_MAX;
			#endif
		}

		const ListUInt Count() const
		{
			return count;
		}

		void Clear()
		{
			delete[] items;
			items = nullptr;
			count = 0;
		}

		void Destroy() const
		{
			for (ListUInt i = 0; i < count; i++)
				delete items[i];
		}

		const T* Data() const
		{
			return items;
		}

		T* Data()
		{
			return items;
		}

		void Sort(const bool (*SortFunc)(const T& firstElement, const T& secondElement)) const
		{
			if (!items || !count)
				throw ListException::ListClear;

			if (count == 1)
				return;

			for (ListUInt i = 1; i < count; i++)
			{
				T* firstElement = &items[i - 1];
				T* secondElement = &items[i];

				for (ListUInt j = 0; j < i; j++)
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
			ListUInt count = this->count;

			for (ListUInt i = 0; i < count; i++)
				items[i] = this->items[i];

			delete[] this->items;

			this->items = elements.items;
			elements.items = items;

			this->count = elements.count;
			elements.count = count;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		void Swap(std::vector<T>& elements)
		{
			T* items = new T[count];
			ListUInt count = this->count;

			for (ListUInt i = 0; i < count; i++)
				items[i] = this->items[i];

			delete[] this->items;

			this->count = elements.size();

			T* vectorItems = new T[elements.size()];

			for (ListUInt i = 0; i < elements.size(); i++)
				vectorItems[i] = elements[i];

			this->items = vectorItems;

			elements.resize(count);

			for (ListUInt i = 0; i < count; i++)
				elements[i] = items[i];

			delete[] items;
		}
		#endif

		void Resize(const ListUInt& Count)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;
		}

		void Resize(const ListUInt& Count, const T& value)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;

			for (ListUInt i = 0; i < Count; i++)
				items[i] = value;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		std::vector<T> ToVector()
		{
			std::vector<T> vector(count);

			for (ListUInt i = 0; i < count; i++)
				vector[i] = items[i];

			return vector;
		}

		const std::vector<T> ToVector() const
		{
			std::vector<T> vector(count);

			for (ListUInt i = 0; i < count; i++)
				vector[i] = items[i];

			return vector;
		}
		#endif

		T* ToArray(ListUInt* Count = nullptr)
		{
			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = items[i];

			if (Count)
				*Count = count;

			return array;
		}

		const T* ToArray(ListUInt* Count = nullptr) const
		{
			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = items[i];

			if (Count)
				*Count = count;

			return array;
		}
	public:
		void operator=(const List<T>& elements)
		{
			delete[] this->items;

			items = new T[elements.count];

			count = elements.count;

			for (ListUInt i = 0; i < count; i++)
				items[i] = elements[i];
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		void operator=(const std::vector<T>& elements)
		{
			delete[] this->items;

			items = new T[elements.size()];

			count = elements.size();

			for (ListUInt i = 0; i < count; i++)
				items[i] = elements[i];
		}
		#endif

		bool operator==(const List<T>& elements)
		{
			for (ListUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		bool operator==(const std::vector<T>& elements)
		{
			for (ListUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}
		#endif

		bool operator==(const T& element)
		{
			return Exist(element);
		}

		const bool operator==(const List<T>& elements) const
		{
			for (ListUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		const bool operator==(const std::vector<T>& elements) const
		{
			for (ListUInt i = 0; i < count; i++)
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

		bool operator!=(const List<T>& elements)
		{
			for (ListUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		bool operator!=(const std::vector<T>& elements)
		{
			for (ListUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}
		#endif

		bool operator!=(const T& element)
		{
			return (!Exist(element));
		}

		const bool operator!=(const List<T>& elements) const
		{
			for (ListUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		const bool operator!=(const std::vector<T>& elements) const
		{
			for (ListUInt i = 0; i < count; i++)
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

		#ifdef BEAR_LIST_VECTOR_ADDED
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

		#ifdef BEAR_LIST_VECTOR_ADDED
		void operator-=(const std::vector<T>& elements)
		{
			DeleteCollection(elements);
		}
		#endif

		void operator-=(const T& element)
		{
			Remove(element);
		}

		T& operator[](const ListUInt& index)
		{
			return GetFromIndex(index);
		}

		const T& operator[](const ListUInt& index) const
		{
			return GetFromIndex(index);
		}
	};
}