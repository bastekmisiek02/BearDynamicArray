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
	/// <summary>
	/// Standard uint for list
	/// </summary>
	typedef unsigned long long int ListUInt;
#else
	/// <summary>
	/// Standard uint for list
	/// </summary>
	typedef unsigned int ListUInt;
#endif

	/// <summary>
	/// Exception when it's something wrong
	/// </summary>
	enum class ListException
	{
		/// <summary>
		/// It's throwing when start index is greater than last index
		/// </summary>
		StartIndexGreaterThanEnd = 0, 
		/// <summary>
		/// It's throwing when index is greater than count
		/// </summary>
		OutOfRange = 1, 
		/// <summary>
		/// It's throwing when index is lower than 0
		/// </summary>
		IndexLower = 2,
		/// <summary>
		/// It's throwing when list is clear
		/// </summary>
		ListClear = 3
	};

	template <typename T>
	class List
	{
	private:
		/// <summary>
		/// Count of list
		/// </summary>
		ListUInt count;
	private:
		/// <summary>
		/// Array of items in list
		/// </summary>
		T* items;
	private:
		/// <summary>
		/// Get item from index and when something wrong throw exception
		/// </summary>
		/// <param name="index">Index from where get items</param>
		/// <returns>Return item from index</returns>
		T& GetFromIndex(const ListUInt& index) const
		{
			if (index > count - 1)
				throw ListException::OutOfRange;

			if (index < 0)
				throw ListException::IndexLower;

			if (!count)
				throw ListException::ListClear;

			return items[index];
		}
	public:
		#ifdef BEAR_LIST_VECTOR_ADDED
		/// <summary>
		/// Create list with count of Elements.size() and copy data from "Elements" to this->items
		/// </summary>
		/// <param name="Elements">- std::vector from where will be copy data</param>
		List(const std::vector<T>& Elements)
			: count(Elements.size())
		{
			items = new T[Elements.size()];

			for (ListUInt i = 0; i < Elements.size(); i++)
				items[i] = Elements[i];
		}
		#endif

		/// <summary>
		/// Create list with count of Elements.Count() and copy data from "Elements" to this->items
		/// </summary>
		/// <param name="Elements">- List from where will be copy data</param>
		List(const List<T>& Elements)
			: count(Elements.count)
		{
			items = new T[Elements.count];

			for (ListUInt i = 0; i < Elements.count; i++)
				items[i] = Elements[i];
		}

		/// <summary>
		/// Create empty list with Count
		/// </summary>
		/// <param name="Count">- Count of elements</param>
		List(const ListUInt& Count)
			: count(Count)
		{
			items = new T[Count];
		}

		/// <summary>
		/// Create list with count of Count and copy data from "Array" to this->items
		/// </summary>
		/// <param name="Array">- Array from where will be copy data</param>
		/// <param name="Count">- Count of elements</param>
		List(const T* Array, const ListUInt& Count)
			: count(Count)
		{
			items = new T[Count];

			for (ListUInt i = 0; i < Count; i++)
				items[i] = Array[i];
		}

		/// <summary>
		/// Create list with count "Count" and set all items to "Value"
		/// </summary>
		/// <param name="Count">- List size</param>
		/// <param name="Value">- All items will be the same "Value"</param>
		List(const ListUInt& Count, const T& Value)
		{
			Resize(Count, Value);
		}

		/// <summary>
		/// Create an empty list of size 0
		/// </summary>
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
		/// <summary>
		/// Iterator for list
		/// </summary>
		/// <typeparam name="T">Type of list</typeparam>
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
		/// <summary>
		/// Check if element exists and if "Index" isn't null "Index" will be index of search element
		/// </summary>
		/// <param name="Element">- Search element</param>
		/// <param name="FromEnd">- If true search will be from end</param>
		/// <param name="Index">- If isn't null return index of search element</param>
		/// <returns>Return true if element exist in list, otherwise return false</returns>
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

		/// <summary>
		/// Add elements from "Elements" and Count+=Elements.Count()
		/// </summary>
		/// <param name="Elements">- List from where will be add items</param>
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
		/// <summary>
		/// Add elements from "Elements" and Count+=Elements.size()
		/// </summary>
		/// <param name="Elements">- std::vector from where will be add items</param>
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

		/// <summary>
		/// Add "Element" to list
		/// </summary>
		/// <param name="Element">- Added element</param>
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

		/// <summary>
		/// Removing "Elements" from list
		/// </summary>
		/// <param name="Elements">- Removed elements</param>
		/// <param name="removeAll">- If true removing all elements where Elements[n]==items[i], otherwise remove first element where Elements[n]==items[i]</param>
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
		/// <summary>
		/// Removing "Elements" from list
		/// </summary>
		/// <param name="Elements">- Removed elements</param>
		/// <param name="removeAll">- If true removing all elements where Elements[n]==items[i], otherwise remove first element where Elements[n]==items[i]</param>
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

		/// <summary>
		/// Removing "Element" from list
		/// </summary>
		/// <param name="Element">- Removed element</param>
		/// <param name="removeAll">- If true removing all elements where Element==items[i], otherwise remove first element where Element==items[i]</param>
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

		/// <summary>
		/// Removing elements from "Start" to "End"
		/// </summary>
		/// <param name="Start">- Index from will be removed items</param>
		/// <param name="End">- End index removed items</param>
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

		/// <summary>
		/// Remove elements from "Start" index to end
		/// </summary>
		/// <param name="Start">- Index where we start removing elements</param>
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

		/// <summary>
		/// Return max count of list
		/// </summary>
		/// <returns>Max count of list</returns>
		const ListUInt GetMaxCount() const
		{
			#ifdef BEAR_LIST_WIN64
				return ULLONG_MAX;
			#else
				return INT_MAX;
			#endif
		}

		/// <summary>
		/// Return count of list
		/// </summary>
		/// <returns>Count of list</returns>
		const ListUInt Count() const
		{
			return count;
		}

		/// <summary>
		/// Clear the list
		/// </summary>
		void Clear()
		{
			delete[] items;
			items = nullptr;
			count = 0;
		}

		/// <summary>
		/// If items are pointers to heap use this to free memory
		/// </summary>
		void Destroy() const
		{
			for (ListUInt i = 0; i < count; i++)
				delete items[i];
		}

		/// <summary>
		/// Return pointer to first element of list
		/// </summary>
		/// <returns></returns>
		const T* Data() const
		{
			return items;
		}

		/// <summary>
		/// Return pointer to first element of list
		/// </summary>
		/// <returns></returns>
		T* Data()
		{
			return items;
		}
		
		/// <summary>
		/// Sort list
		/// </summary>
		/// <param name="SortFunc">- If return true "firstElement" will be closer </param>
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

		/// <summary>
		/// Swap items between this->items and "Elements"
		/// </summary>
		/// <param name="Elements"></param>
		void Swap(List<T>& Elements)
		{
			T* items = new T[count];
			ListUInt count = this->count;

			for (ListUInt i = 0; i < count; i++)
				items[i] = this->items[i];

			delete[] this->items;

			this->items = Elements.items;
			Elements.items = items;

			this->count = Elements.count;
			Elements.count = count;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		/// <summary>
		/// Swap items between this->items and "Elements"
		/// </summary>
		/// <param name="Elements"></param>
		void Swap(std::vector<T>& Elements)
		{
			T* items = new T[count];
			ListUInt count = this->count;

			for (ListUInt i = 0; i < count; i++)
				items[i] = this->items[i];

			delete[] this->items;

			this->count = Elements.size();

			T* vectorItems = new T[Elements.size()];

			for (ListUInt i = 0; i < Elements.size(); i++)
				vectorItems[i] = Elements[i];

			this->items = vectorItems;

			Elements.resize(count);

			for (ListUInt i = 0; i < count; i++)
				Elements[i] = items[i];

			delete[] items;
		}
		#endif

		/// <summary>
		/// Set count to "Count" and destroy data in list
		/// </summary>
		/// <param name="Count"></param>
		void Resize(const ListUInt& Count)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;
		}

		/// <summary>
		/// Set count to "Count" and set items to "Value"
		/// </summary>
		/// <param name="Count"></param>
		/// <param name="Value"></param>
		void Resize(const ListUInt& Count, const T& Value)
		{
			if (items)
				delete[] items;

			items = new T[Count];

			count = Count;

			for (ListUInt i = 0; i < Count; i++)
				items[i] = Value;
		}

		#ifdef BEAR_LIST_VECTOR_ADDED
		/// <summary>
		/// Convert List to std::vector
		/// </summary>
		/// <returns></returns>
		std::vector<T> ToVector()
		{
			std::vector<T> vector(count);

			for (ListUInt i = 0; i < count; i++)
				vector[i] = items[i];

			return vector;
		}

		/// <summary>
		/// Convert List to std::vector
		/// </summary>
		/// <returns></returns>
		const std::vector<T> ToVector() const
		{
			std::vector<T> vector(count);

			for (ListUInt i = 0; i < count; i++)
				vector[i] = items[i];

			return vector;
		}
		#endif

		/// <summary>
		/// Create array and return it with the same data and count equals List !!! REMEMBER use delete[] to destroy it !!!
		/// </summary>
		/// <param name="Count"></param>
		/// <returns></returns>
		T* ToArray(ListUInt* Count = nullptr)
		{
			T* array = new T[count];

			for (ListUInt i = 0; i < count; i++)
				array[i] = items[i];

			if (Count)
				*Count = count;

			return array;
		}

		/// <summary>
		/// Create array and return it with the same data and count equals List !!! REMEMBER use delete[] to destroy it !!!
		/// </summary>
		/// <param name="Count"></param>
		/// <returns></returns>
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