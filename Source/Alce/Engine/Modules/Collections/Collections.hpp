#pragma once

#include <vector>
#include <map>
#include "../Exceptions/Exceptions.hpp"
#include <algorithm>
#include <set>
#include <functional>

namespace alce
{
	template<typename T>
	class List
	{
	public:

	    using CompareFunction = std::function<bool(const T&, const T&)>;

		List()
		{

		}

		List(std::initializer_list<T> in_list) : vector(in_list)
		{
			
		}

		List(std::vector<T> vector) : vector(std::move(vector))
		{
			
		}

		List<T>& Add(const T& element)
		{
			vector.push_back(element);

			return *this;
		}

		List<T>& AddFirst(const T& element)
		{
			if (front_offset == 0)
			{
				size_t oldSize = vector.size();
				size_t grow = std::max<size_t>(1, oldSize / 2);

				vector.insert(vector.begin(), grow, T{});
				front_offset = grow;
			}

			vector[--front_offset] = element;
			return *this;
		}

		List<T>& SetFirst(size_t index)
		{
			if (index >= this->Length()) 
			{
            	throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::MoveToFront(size_t index)\n<!> Reason -> Index out of bounds");
			}

        	size_t real = front_offset + index;
			T element = std::move(vector[real]);

			vector.erase(vector.begin() + real);
			vector.insert(vector.begin() + front_offset, std::move(element));

			return *this;
		}

		List<T>& PopFirst()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::PopFirst()\n<!> Reason -> Empty list");

			++front_offset;
    		return *this;
		}

		List<T>& PopLast()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::PopLast()\n<!> Reason -> Empty list");

			vector.pop_back();

			return *this;
		}

		T& Last()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::Last()\n<!> Reason -> Empty list");

			return vector.back();
		}

		T& First()
		{
			if (this->Length() == 0) 
				throw exception::collections::EmptyListException("<?> Here -> alce::List::First()\n<!> Reason -> Empty list");

			return vector[front_offset];
		}

		List<T>& Clear()
		{
			vector.clear();

			return *this;
		}

		T& Get(size_t index)
		{
			if (index > this->Length() - 1) 
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::Get(size_t index)\n<!> Reason -> Index out of bounds");

			return vector[front_offset + index];
		}

		List<T>& Set(size_t index, const T& value)
		{
			if (index >= vector.size()) 
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::Set(size_t index, T value)\n<!> Reason -> Index out of bounds");

			vector[front_offset + index] = value;

			return *this;
		}

		size_t Length() const
		{
			return vector.size() - front_offset;
		}

		template<typename Predicate>
		List<T> Filter(Predicate condition)
		{
			List<T> result = {};

			for (auto it = begin(); it != end(); ++it)
			{
				if (condition(*it))
					result.Add(*it);
			}
			
			return result;
		}

		int FindIndex(const T& element)
		{
			for (size_t i = 0; i < Length(); i++)
			{
				if (vector[front_offset + i] == element)
					return static_cast<int>(i);
			}
			return -1;
		}

		List<T>& FindAndRemove(const T& element)
		{
			auto it = std::find(begin(), end(), element);
			if (it != end())
			{
				vector.erase(it);
			}
			return *this;
		}

		List<T>& RemoveIndex(size_t index)
		{
			if (index >= Length())
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::RemoveIndex(size_t index)\n<!> Reason -> Index out of bounds");

			vector.erase(vector.begin() + front_offset + index);
			return *this;
		}

		template<typename Predicate>
		List<T>& RemoveIf(Predicate condition)
		{
			auto first = begin();
			auto last  = end();

			vector.erase(
				std::remove_if(first, last, condition),
				last
			);

			return *this;
		}

		List<T>& Sort(CompareFunction compare)
	    {
        	std::sort(begin(), end(), compare);
			
			return *this;
    	}

		List<T>& Merge(const List<T>& other)
		{
			for (auto it = other.begin(); it != other.end(); ++it)
			{
				if (!Contains(*it))
					Add(*it);
			}
			return *this;
		}

		template<typename Func>
		List<T>& ForEach(Func func)
		{
			for (auto it = begin(); it != end(); ++it)
			{
				func(*it);
			}

			return *this;
		}

		bool Contains(const T& element) const
		{
			return std::find(begin(), end(), element) != end();
		}

		bool IsEmpty() const
		{
			return this->Length() == 0;
		}

		void Normalize()
		{
			if (front_offset > 0)
			{
				vector.erase(vector.begin(), vector.begin() + front_offset);
				front_offset = 0;
			}
		}

		std::vector<T> ToStdVector()
		{
			Normalize();
    		return vector;
		}

		std::vector<T>* ToStdVectorPtr()
		{
			Normalize();
			return &vector;
		}

		void operator=(std::initializer_list<T> in_list)
		{
			this->vector = in_list;
		}

		void operator=(const std::vector<T>& vector)
		{
			this->vector = vector;
		}

		T& operator[](size_t index)
		{
			if (index > this->Length() - 1) 
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::operator[](size_t index)\n<!> Reason -> Index out of bounds");

			return vector[front_offset + index];
		}

		const T& operator[](size_t index) const
		{
			if (index > this->Length() - 1)
				throw exception::collections::OutOfBoundsException("<?> Here -> alce::List::operator[](size_t index)\n<!> Reason -> Index out of bounds");

			return vector[front_offset + index];
		}

		void operator<<(T element)
		{
			vector.push_back(element);
		}

		std::vector<T> operator~()
		{
			Normalize();
			return vector;
		}

		//Iteration stuff

		auto begin() { return vector.begin() + front_offset; }
		auto end() { return vector.end(); }

		auto begin() const { return vector.begin() + front_offset; }
		auto end() const { return vector.end(); }

	protected:

		std::vector<T> vector = {};
		size_t front_offset = 0;
	};

	template<typename F, typename S>
	class Pair
	{
	public:

		Pair()
		{

		}

		Pair(F first, S second)
		{
			this->first = first;
			this->second = second;
		}

		void operator=(std::pair<F, S> pair)
		{
			first = pair.first;
			second = pair.second;
		}

		F first;
		S second;
	};

	template<typename K, typename V>
	class Dictionary
	{
	public:

		Dictionary() = default;

		Dictionary(std::initializer_list<std::pair<K, V>> map)
		{
			for (const auto& p : map)
				list.Add(Pair<K, V>(p.first, p.second));
		}

		// Devuelve un std::vector de pares
		std::vector<Pair<K, V>> std_vector() const
		{
			return ~list;
		}

		// Métodos de consulta
		size_t Length() const
		{
			return list.Length();
		}

		bool IsEmpty() const
		{
			return list.IsEmpty();
		}

		bool HasKey(const K& key) const
		{
			return GetKeyList().Contains(key);
		}

		V Get(const K& key) const
		{
			for (size_t i = 0; i < list.Length(); ++i)
				if (list[i].first == key)
					return list[i].second;

			throw exception::collections::NotFoundKeyException(
				"<?> Here -> alce::Dictionary::Get(K key)\n<!> Reason -> Key not found in the dictionary");
		}

		List<K> GetKeyList() const
		{
			List<K> keys;
			for (size_t i = 0; i < list.Length(); ++i)
				keys.Add(list[i].first);
			return keys;
		}

		List<V> GetValueList() const
		{
			List<V> values;
			for (size_t i = 0; i < list.Length(); ++i)
				values.Add(list[i].second);
			return values;
		}

		Dictionary<K, V> FilterByValue(const V& value) const
		{
			Dictionary<K, V> filtered;
			for (size_t i = 0; i < list.Length(); ++i)
				if (list[i].second == value)
					filtered.Set(list[i].first, list[i].second);
			return filtered;
		}

		// Métodos de modificación
		void Set(const K& key, const V& value)
		{
			for (size_t i = 0; i < list.Length(); ++i)
			{
				if (list[i].first == key)
				{
					list[i].second = value;
					return;
				}
			}
			list.Add(Pair<K, V>(key, value));
		}

		void RemoveByKey(const K& key)
		{
			for (size_t i = 0; i < list.Length(); ++i)
			{
				if (list[i].first == key)
				{
					list.RemoveIndex(i);
					return;
				}
			}
		}

		void RemoveByValue(const V& value)
		{
			for (size_t i = 0; i < list.Length(); )
			{
				if (list[i].second == value)
					list.RemoveIndex(i);
				else
					++i;
			}
		}

		void Clear()
		{
			list.Clear();
		}

		// Operadores
		V operator[](const K& key) const
		{
			return Get(key);
		}

		void operator+=(const std::pair<K, V>& pair)
		{
			Set(pair.first, pair.second);
		}

		bool operator==(const Dictionary<K, V>& d) const
		{
			if (Length() != d.Length())
				return false;

			for (size_t i = 0; i < list.Length(); ++i)
			{
				if (list[i].first != d.list[i].first || list[i].second != d.list[i].second)
					return false;
			}

			return true;
		}

		bool operator!=(const Dictionary<K, V>& d) const
		{
			return !(*this == d);
		}

		std::vector<Pair<K, V>> operator~() const
		{
			return ~list;
		}

		// Iteradores
		auto begin() { return list.begin(); }
		auto end() { return list.end(); }
		auto begin() const { return list.begin(); }
		auto end() const { return list.end(); }

	private:

		List<Pair<K, V>> list;
	};
}