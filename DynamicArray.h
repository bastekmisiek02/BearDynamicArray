#pragma once

#if __has_include(<vector>)
	#define BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
	#include <vector>
#endif

#ifdef _WIN64
	#define BEAR_DYNAMIC_ARRAY_WIN64
#endif

namespace Bear
{
#ifdef BEAR_DYNAMIC_ARRAY_WIN64
	/// <summary>
	/// Standard uint for dynamic array
	/// </summary>
	typedef unsigned long long int DynamicArrayUInt;
#else
	/// <summary>
	/// Standard uint for dynamic array
	/// </summary>
	typedef unsigned int DynamicArrayUInt;
#endif

	/// <summary>
	/// Exception when it's something wrong
	/// </summary>
	enum class DynamicArrayException
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
		/// It's throwing when dynamic array is clear
		/// </summary>
		DynamicArrayClear = 3
	};

	template <typename T>
	class DynamicArray
	{
	private:
		/// <summary>
		/// Count of list
		/// </summary>
		DynamicArrayUInt count;
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
		constexpr T& GetFromIndex(const DynamicArrayUInt& index) const
		{
			if (index > count - 1)
				throw DynamicArrayException::OutOfRange;

			if (index < 0)
				throw DynamicArrayException::IndexLower;

			if (!count)
				throw DynamicArrayException::DynamicArrayClear;

			return items[index];
		}
	public:
#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		/// <summary>
		/// Create dynamic array with count of Elements.size() and copy data from "Elements" to this->items
		/// </summary>
		/// <param name="Elements">- std::vector from where will be copy data</param>
		constexpr DynamicArray(const std::vector<T>& elements)
			: count(elements.size())
		{
			items = new T[count];

			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = elements[i];
		}

		/// <summary>
		/// Create dynamic array with count of elements.size() and copy data from "elements" to this->items
		/// </summary>
		/// <param name="elements">- initializer list from where will be copy data</param>
		constexpr DynamicArray(const std::initializer_list<T>& elements)
			: count(elements.size())
		{
			items = new T[count];

			auto it = elements.begin();
			for (DynamicArrayUInt i = 0; i < count; i++)
			{
				this->items[i] = *it;
				it++;
			}
		}
#endif
		/// <summary>
		/// Create dynamic array with count of Elements.Count() and copy data from "Elements" to this->items
		/// </summary>
		/// <param name="Elements">- DynamicArray from where will be copy data</param>
		constexpr DynamicArray(const DynamicArray<T>& elements)
			: count(elements.count)
		{
			items = new T[elements.count];

			for (DynamicArrayUInt i = 0; i < elements.count; i++)
				items[i] = elements[i];
		}

		/// <summary>
		/// Create empty dynamic array with Count
		/// </summary>
		/// <param name="Count">- Count of elements</param>
		constexpr DynamicArray(const DynamicArrayUInt& count)
			: count(count)
		{
			items = new T[count];
		}

		/// <summary>
		/// Create list with count of Count and copy data from "Array" to this->items
		/// </summary>
		/// <param name="Array">- Array from where will be copy data</param>
		/// <param name="Count">- Count of elements</param>
		constexpr DynamicArray(const T* array, const DynamicArrayUInt& count)
			: count(count)
		{
			items = new T[count];

			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = array[i];
		}

		/// <summary>
		/// Create dynamic array with count "Count" and set all items to "Value"
		/// </summary>
		/// <param name="Count">- Dynamic array size</param>
		/// <param name="Value">- All items will be the same "Value"</param>
		constexpr DynamicArray(const DynamicArrayUInt& count, const T& value)
		{
			Resize(count, value);
		}

		/// <summary>
		/// Create an empty dynamic array of size 0
		/// </summary>
		constexpr DynamicArray()
			: count(0), items(nullptr)
		{
		}

		~DynamicArray()
		{
			Clear();
		}
	public:
		/// <summary>
		/// Iterator for dynamic array
		/// </summary>
		/// <typeparam name="T">Type of dynamic array</typeparam>
		template<typename T>
		class Iterator
		{
		private:
			T* ptr;
		public:
			constexpr Iterator(T* ptr)
				: ptr(ptr)
			{
			}

			constexpr T& operator*()
			{
				return *ptr;
			}

			constexpr const T& operator*() const
			{
				return *ptr;
			}

			constexpr Iterator& operator--()
			{
				ptr--;
				return *this;
			}

			constexpr const Iterator& operator--() const
			{
				ptr--;
				return *this;
			}

			constexpr Iterator& operator++()
			{
				ptr++;
				return *this;
			}

			constexpr const Iterator& operator++() const
			{
				ptr++;
				return *this;
			}

			constexpr Iterator& operator-=(const DynamicArrayUInt& offset)
			{
				ptr -= offset;
				return *this;
			}

			constexpr const Iterator& operator-=(const DynamicArrayUInt& offset) const
			{
				ptr -= offset;
				return *this;
			}

			constexpr Iterator& operator+=(const DynamicArrayUInt& offset)
			{
				ptr += offset;
				return *this;
			}

			constexpr const Iterator& operator+=(const DynamicArrayUInt& offset) const
			{
				ptr += offset;
				return *this;
			}

			constexpr Iterator& operator*=(const DynamicArrayUInt& offset)
			{
				ptr *= offset;
				return *this;
			}

			constexpr const Iterator& operator*=(const DynamicArrayUInt& offset) const
			{
				ptr *= offset;
				return *this;
			}

			constexpr Iterator& operator/=(const DynamicArrayUInt& offset)
			{
				if (!offset)
					throw ("Can't division by 0");

				ptr /= offset;
				return *this;
			}

			constexpr const Iterator& operator/=(const DynamicArrayUInt& offset) const
			{
				if(!offset)
					throw ("Can't division by 0");

				ptr /= offset;
				return *this;
			}

			constexpr Iterator& operator%=(const DynamicArrayUInt& offset)
			{
				ptr %= offset;
				return *this;
			}

			constexpr const Iterator& operator%=(const DynamicArrayUInt& offset) const
			{
				ptr %= offset;
				return *this;
			}

			constexpr bool operator==(const Iterator& other)
			{
				return ptr == other.ptr;
			}

			constexpr const bool operator==(const Iterator& other) const
			{
				return ptr == other.ptr;
			}

			constexpr bool operator!=(const Iterator& other)
			{
				return ptr != other.ptr;
			}

			constexpr const bool operator!=(const Iterator& other) const
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
		constexpr const bool Exist(const T& element, const bool fromEnd = false, DynamicArrayUInt* index = nullptr) const
		{
			if (fromEnd)
			{
				#ifdef BEAR_DYNAMIC_ARRAY_WIN64
				typedef long long int Int;
				#else
				typedef int Int;
				#endif

				for (Int i = count - 1; i > -1; i--)
				{
					if (items[i] == element)
					{
						if (index)
							*index = i;

						return true;
					}
				}
			}
			else
			{
				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					if (items[i] == element)
					{
						if (index)
							*index = i;

						return true;
					}
				}
			}

			return false;
		}

		/// <summary>
		/// Add elements from "Elements" and Count += Elements.Count()
		/// </summary>
		/// <param name="Elements">- DynamicArray from where will be add items</param>
		constexpr void AddCollection(const DynamicArray<T>& elements)
		{
			T* array = new T[count + elements.count];

			for (DynamicArrayUInt i = 0; i < count + elements.count; i++)
			{
				if (i < count)
				{
					array[i] = items[i];
					continue;
				}

				array[i] = elements.items[i - count];
			}

			operator delete[](items);

			items = array;

			count += elements.count;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		/// <summary>
		/// Add elements from "Elements" and Count += Elements.size()
		/// </summary>
		/// <param name="Elements">- std::vector from where will be add items</param>
		constexpr void AddCollection(const std::vector<T>& elements)
		{
			T* array = new T[count + elements.size()];

			for (DynamicArrayUInt i = 0; i < count + elements.size(); i++)
			{
				if (i < count)
				{
					array[i] = items[i];
					continue;
				}

				array[i] = elements[i - count];
			}

			operator delete[](items);

			items = array;

			count += elements.size();
		}
		#endif

		/// <summary>
		/// Add "Element" to dynamic array
		/// </summary>
		/// <param name="Element">- Added element</param>
		constexpr void Add(const T& element)
		{
			T* array = new T[count + 1];

			for (DynamicArrayUInt i = 0; i < count; i++)
				array[i] = this->items[i];

			array[count] = element;

			operator delete[](this->items);

			this->items = array;

			count++;
		}

		/// <summary>
		/// Removing "Elements" from dynamic array
		/// </summary>
		/// <param name="Elements">- Removed elements</param>
		/// <param name="removeAll">- If true removing all elements where Elements[n] == items[i], otherwise remove first element where Elements[n] == items[i]</param>
		constexpr void RemoveCollection(const DynamicArray<T>& elements, const bool& removeAll = false)
		{
			if (!items || !count)
				return;

			if (removeAll)
			{
				DynamicArrayUInt&& removeElements = 0;

				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					bool&& found = false;

					for (DynamicArrayUInt j = 0; j < elements.count; j++)
					{
						if (items[i] == elements.items[j])
						{
							found = true;
							break;
						}
					}

					if (found)
						removeElements++;
					else
					{
						T element = items[i];

						items[i] = items[i - removeElements];
						items[i - removeElements] = element;
					}
				}

				if (removeElements)
				{
					count -= removeElements;

					T* array = new T[count];

					for (DynamicArrayUInt i = 0; i < count; i++)
						array[i] = items[i];

					delete[] items;

					items = array;
				}
			}
			else
			{
				bool* notRemoved = new bool[elements.count];

				DynamicArrayUInt&& removeElements = 0;

				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					bool&& found = false;

					for (DynamicArrayUInt j = 0; j < elements.count; j++)
					{
						if ((items[i] == elements.items[j]) && (notRemoved[j]))
						{
							notRemoved[j] = false;
							found = true;
							break;
						}
					}

					if (found)
						removeElements++;
					else
					{
						T element = items[i];

						items[i] = items[i - removeElements];
						items[i - removeElements] = element;
					}
				}

				if (removeElements)
				{
					count -= removeElements;

					T* array = new T[count];

					for (DynamicArrayUInt i = 0; i < count; i++)
						array[i] = items[i];

					delete[] items;

					items = array;
				}

				delete[] notRemoved;
			}
		}

#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		/// <summary>
		/// Removing "Elements" from dynamic array
		/// </summary>
		/// <param name="Elements">- Removed elements</param>
		/// <param name="removeAll">- If true removing all elements where Elements[n] == items[i], otherwise remove first element where Elements[n] == items[i]</param>
		constexpr void RemoveCollection(const std::vector<T>& elements, const bool& removeAll = false)
		{
			if (!items || !count)
				return;

			if (removeAll)
			{
				DynamicArrayUInt&& removeElements = 0;

				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					bool&& found = false;

					for (DynamicArrayUInt j = 0; j < elements.size(); j++)
					{
						if (items[i] == elements[j])
						{
							found = true;
							break;
						}
					}

					if (found)
						removeElements++;
					else
					{
						T element = items[i];

						items[i] = items[i - removeElements];
						items[i - removeElements] = element;
					}
				}

				if (removeElements)
				{
					count -= removeElements;

					T* array = new T[count];

					for (DynamicArrayUInt i = 0; i < count; i++)
						array[i] = items[i];

					delete[] items;

					items = array;
				}
			}
			else
			{
				bool* notRemoved = new bool[elements.size()];

				DynamicArrayUInt&& removeElements = 0;

				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					bool&& found = false;

					for (DynamicArrayUInt j = 0; j < elements.size(); j++)
					{
						if ((items[i] == elements[j]) && (notRemoved[j]))
						{
							notRemoved[j] = false;
							found = true;
							break;
						}
					}

					if (found)
						removeElements++;
					else
					{
						T element = items[i];

						items[i] = items[i - removeElements];
						items[i - removeElements] = element;
					}
				}

				if (removeElements)
				{
					count -= removeElements;

					T* array = new T[count];

					for (DynamicArrayUInt i = 0; i < count; i++)
						array[i] = items[i];

					delete[] items;

					items = array;
				}

				delete[] notRemoved;
			}
		}
#endif

		/// <summary>
		/// Removing "Element" from dynamic array
		/// </summary>
		/// <param name="Element">- Removed element</param>
		/// <param name="removeAll">- If true removing all elements where Element == items[i], otherwise remove first element where Element == items[i]</param>
		void Remove(const T& element, const bool& removeAll = false)
		{
			if (!items || !count)
				return;

			T* array = new T[count];

			if (removeAll)
			{
				DynamicArrayUInt&& j = 0;
				DynamicArrayUInt&& removeItems = 0;
			
				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					if (this->items[i] != element)
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
				bool&& found = false;
			
				for (DynamicArrayUInt i = 0; i < count; i++)
				{
					if (this->items[i] != element || found)
						array[i - found] = this->items[i];
					else
						found = true;
				}
			
				count--;
			}
			
			delete[] this->items;
			
			this->items = array;
		}

		/// <summary>
		/// Removing elements from "Start" to "End"
		/// </summary>
		/// <param name="Start">- Index from will be removed items</param>
		/// <param name="End">- End index removed items</param>
		void RemoveOnIndex(const DynamicArrayUInt& start, const DynamicArrayUInt& end)
		{
			if (!items || !count)
				return;

			if (start > count || end > count)
				throw DynamicArrayException::OutOfRange;

			if (start > end)
				throw DynamicArrayException::StartIndexGreaterThanEnd;

			T* array = new T[count];

			DynamicArrayUInt&& j = 0;

			for (DynamicArrayUInt i = 0; i < count; i++)
			{
				if (!(i >= start && i <= end))
					array[i - j] = items[i];
				else
					j++;
			}

			delete[] items;

			count -= (end - start) + 1;

			items = array;
		}

		/// <summary>
		/// Remove elements from "Start" index to end
		/// </summary>
		/// <param name="Start">- Index where we start removing elements</param>
		void RemoveOnIndex(const DynamicArrayUInt& start)
		{
			if (!items || !count)
				return;

			if (start > count)
				throw DynamicArrayException::OutOfRange;

			count = start;

			T* array = new T[count];

			for (DynamicArrayUInt i = 0; i < count; i++)
				array[i] = items[i];

			delete[] items;

			items = array;
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
		/// Return max count of dynamic array
		/// </summary>
		/// <returns>Max count of dynamic array</returns>
		const DynamicArrayUInt GetMaxCount() const
		{
			#ifdef BEAR_DYNAMIC_ARRAY_WIN64
				return ULLONG_MAX;
			#else
				return INT_MAX;
			#endif
		}

		/// <summary>
		/// Return count of dynamic array
		/// </summary>
		/// <returns>Count of dynamic array</returns>
		const DynamicArrayUInt Count() const
		{
			return count;
		}

		/// <summary>
		/// Clear the dynamic array
		/// </summary>
		void Clear()
		{
			delete[] items;
			items = nullptr;
			count = 0;
		}

		/// <summary>
		/// If "T" is pointer to heap, use this to free memory
		/// </summary>
		void Destroy() const
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
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
		void Sort(const bool (*sortFunc)(const T& firstElement, const T& secondElement)) const
		{
			if (!items || !count)
				throw DynamicArrayException::DynamicArrayClear;

			if (count == 1)
				return;

			for (DynamicArrayUInt i = 1; i < count; i++)
			{
				T* firstElement = &items[i - 1];
				T* secondElement = &items[i];

				for (DynamicArrayUInt j = 0; j < i; j++)
				{
					if (!sortFunc(*firstElement, *secondElement))
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
		void Swap(DynamicArray<T>& elements)
		{
			if (!items || !count)
			{
				operator=(elements);
				elements.count = 0;
				operator delete[](elements.items);
			}

			const DynamicArrayUInt count = this->count;
			T* items = new T[count];

			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = this->items[i];

			operator delete[](this->items);

			this->items = elements.items;
			elements.items = items;

			this->count = elements.count;
			elements.count = count;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		/// <summary>
		/// Swap items between this->items and "Elements"
		/// </summary>
		/// <param name="Elements"></param>
		void Swap(std::vector<T>& elements)
		{
			if (!items || !count)
			{
				operator=(elements);
				elements.clear();
			}

			DynamicArrayUInt count = this->count;
			T* items = new T[count];
			
			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = this->items[i];
			
			operator delete[](this->items);
			
			this->count = elements.size();
			
			T* vectorItems = new T[elements.size()];
			
			for (DynamicArrayUInt i = 0; i < elements.size(); i++)
				vectorItems[i] = elements[i];
			
			this->items = vectorItems;
			
			elements.resize(count);
			
			for (DynamicArrayUInt i = 0; i < count; i++)
				elements[i] = items[i];
			
			delete[] items;
		}
		#endif

		/// <summary>
		/// Set count to "Count" and destroy data in dynamic array
		/// </summary>
		/// <param name="Count"></param>
		void Resize(const DynamicArrayUInt& count)
		{
			if (items)
				delete[] items;

			items = new T[count];

			this->count = count;
		}

		/// <summary>
		/// Set count to "Count" and set items to "Value"
		/// </summary>
		/// <param name="Count"></param>
		/// <param name="Value"></param>
		void Resize(const DynamicArrayUInt& count, const T& value)
		{
			if (items)
				delete[] items;

			items = new T[count];

			this->count = count;

			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = value;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		/// <summary>
		/// Convert DynamicArray to std::vector
		/// </summary>
		/// <returns></returns>
		std::vector<T> ToVector()
		{
			std::vector<T> vector(count);

			for (DynamicArrayUInt i = 0; i < count; i++)
				vector[i] = items[i];

			return vector;
		}

		/// <summary>
		/// Convert DynamicArray to std::vector
		/// </summary>
		/// <returns></returns>
		const std::vector<T> ToVector() const
		{
			std::vector<T> vector(count);

			for (DynamicArrayUInt i = 0; i < count; i++)
				vector[i] = items[i];

			return vector;
		}
		#endif

		/// <summary>
		/// Create array and return it with the same data and count equals Array !!! REMEMBER use delete[] to destroy it !!!
		/// </summary>
		/// <param name="Count"></param>
		/// <returns></returns>
		T* ToArray(DynamicArrayUInt* count = nullptr)
		{
			T* array = new T[this->count];

			for (DynamicArrayUInt i = 0; i < this->count; i++)
				array[i] = items[i];

			if (count)
				*count = this->count;

			return array;
		}

		/// <summary>
		/// Create array and return it with the same data and count equals Array !!! REMEMBER use delete[] to destroy it !!!
		/// </summary>
		/// <param name="Count"></param>
		/// <returns></returns>
		const T* ToArray(DynamicArrayUInt* count = nullptr) const
		{
			T* array = new T[this->count];

			for (DynamicArrayUInt i = 0; i < this->count; i++)
				array[i] = items[i];

			if (count)
				*count = this->count;

			return array;
		}
	public:
		void operator=(const DynamicArray<T>& elements)
		{
			delete[] this->items;

			items = new T[elements.count];

			count = elements.count;

			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = elements[i];
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		void operator=(const std::vector<T>& elements)
		{
			delete[] this->items;

			items = new T[elements.size()];

			count = elements.size();

			for (DynamicArrayUInt i = 0; i < count; i++)
				items[i] = elements[i];
		}
		#endif

		bool operator==(const DynamicArray<T>& elements)
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		bool operator==(const std::vector<T>& elements)
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
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

		const bool operator==(const DynamicArray<T>& elements) const
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return false;
			}

			return true;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		const bool operator==(const std::vector<T>& elements) const
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
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

		bool operator!=(const DynamicArray<T>& elements)
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		bool operator!=(const std::vector<T>& elements)
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
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

		const bool operator!=(const DynamicArray<T>& elements) const
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
			{
				if (items[i] != elements[i])
					return true;
			}

			return false;
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		const bool operator!=(const std::vector<T>& elements) const
		{
			for (DynamicArrayUInt i = 0; i < count; i++)
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

		void operator+=(const DynamicArray<T>& elements)
		{
			AddCollection(elements);
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		void operator+=(const std::vector<T>& elements)
		{
			AddCollection(elements);
		}
		#endif

		void operator+=(const T& element)
		{
			Add(element);
		}

		void operator-=(const DynamicArray<T>& elements)
		{
			DeleteCollection(elements);
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		void operator-=(const std::vector<T>& elements)
		{
			DeleteCollection(elements);
		}
		#endif

		void operator-=(const T& element)
		{
			Remove(element);
		}

		#ifdef BEAR_DYNAMIC_ARRAY_VECTOR_ADDED
		operator std::vector<T>()
		{
			return ToVector();
		}

		operator const std::vector<T>() const
		{
			return ToVector();
		}
		#endif

		T& operator[](const DynamicArrayUInt& index)
		{
			return GetFromIndex(index);
		}

		const T& operator[](const DynamicArrayUInt& index) const
		{
			return GetFromIndex(index);
		}
	};
}