module;
#include <initializer_list>
#include <iterator>
#include <iostream>
export module Deque;

export namespace Deque {
	template <typename T>
	class DequeBasedOnBidirectionalCyclicLinkedList
	{
		using Iterator = T*;

		class CyclicLinkedList
		{
		public:
			CyclicLinkedList() : data(0), previous(this), next(this) {};
			explicit CyclicLinkedList(T data = T(), CyclicLinkedList* previous = nullptr, CyclicLinkedList* next = nullptr)
				: data(data), previous(previous), next(next)
			{
				if (!this->previous)
					this->previous = this;
				if (!this->next)
					this->next = this;
			};
			CyclicLinkedList*& Last() { return previous; };
			void changePrevious(CyclicLinkedList* previous) { this->previous = previous; }
			CyclicLinkedList* Next() { return this->next; };
			T operator++();
			T& Value() { return this->data; };
			CyclicLinkedList(const CyclicLinkedList&);
			CyclicLinkedList(CyclicLinkedList&&);
			explicit CyclicLinkedList(std::initializer_list<T>);
			unsigned GetSize() const;
			void InsertAt(T value, int index)
			{
				if (!index)
					throw NULL;
				CyclicLinkedList* temp = this;
				if (index < 0)
					for (auto i = index; i < 0; i++)
						temp = temp->previous;
				else
					for (auto i = 0; i > index; i++)
						temp = temp->next;
				temp->next = new CyclicLinkedList(value, temp, temp->next);
				temp->next->next->previous = temp->next;
			};
			T RemoveAt(int index)
			{
				try {
					CyclicLinkedList* temp = this;
					T data;
					if (index < 0)
						for (auto i = index; i < 0; i++)
							temp = temp->previous;
					else
						for (auto i = 0; i > index; i++)
							temp = temp->next;
					CyclicLinkedList* onDelete = temp;
					temp->next->previous = temp->previous;
					temp->previous->next = temp->next;
					data = onDelete->data;
					delete onDelete;
					return data;
				}
				catch (...) {}
				return T();
			};


		private:
			T data;
			CyclicLinkedList* previous;
			CyclicLinkedList* next;
		};
		CyclicLinkedList* list;
		unsigned size;

	public:
		DequeBasedOnBidirectionalCyclicLinkedList();
		explicit DequeBasedOnBidirectionalCyclicLinkedList(unsigned);
		DequeBasedOnBidirectionalCyclicLinkedList(const DequeBasedOnBidirectionalCyclicLinkedList&);
		DequeBasedOnBidirectionalCyclicLinkedList(DequeBasedOnBidirectionalCyclicLinkedList&&);
		DequeBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T>);
		~DequeBasedOnBidirectionalCyclicLinkedList();
		unsigned GetSize();

		Iterator begin();
		Iterator begin() const;
		Iterator end();
		Iterator end() const;
		const T& operator[](int) const;
		T& operator[](int);
		DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(const DequeBasedOnBidirectionalCyclicLinkedList&);
		DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(DequeBasedOnBidirectionalCyclicLinkedList&&);
		DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(std::initializer_list<T>);
		bool PushFront(const T& element);
		bool PushBack(const T& element);
		bool PopFront(T& element);
		bool PopBack(T& element);
		bool PeekFront(T& element);
		bool PeekBack(T& element);
	};









	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList()
		: size(0), list(nullptr)
	{
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(unsigned size)
	{
		if (size <= 0)
			throw 0;
		list = new CyclicLinkedList(T());
		for (auto i = 1; i < size; i++)
			PushBack(0);
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(const DequeBasedOnBidirectionalCyclicLinkedList& obj)
	{
		list = new CyclicLinkedList(obj.list->Value());
		CyclicLinkedList* iterator = obj.list->Next();
		while (iterator != obj.list)
		{
			PushBack(iterator->Value());
			iterator = iterator->Next();
		}
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(DequeBasedOnBidirectionalCyclicLinkedList&& obj)
	{
		list = obj.list;
		size = obj.size;
		obj.list = nullptr;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist)
	{
		for (const auto& element : ilist)
		{
			PushBack(element);
		}
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::~DequeBasedOnBidirectionalCyclicLinkedList()
	{
		T temp;
		for (auto i = 0; i < size; i++)
		{
			PopBack(temp);
		}
	}

	template<typename T>
	unsigned DequeBasedOnBidirectionalCyclicLinkedList<T>::GetSize()
	{
		return size;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::begin()
	{
		return Iterator(list);
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::begin() const
	{
		return Iterator(list);
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::end()
	{
		return Iterator(list->Last());
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::Iterator DequeBasedOnBidirectionalCyclicLinkedList<T>::end() const
	{
		return Iterator(list->Last());
	}

	template<typename T>
	const T& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index) const
	{
		CyclicLinkedList* iterator = this;
		for (auto i = 0; i < index; i++)
			iterator = iterator->Next();
		return iterator->Value();
	}

	template<typename T>
	T& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator[](int index)
	{
		CyclicLinkedList* iterator = this->list;
		for (auto i = 0; i < index; i++)
			iterator = iterator->Next();
		return iterator->Value();
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(const DequeBasedOnBidirectionalCyclicLinkedList& obj)
	{
		*list = *obj.list;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(DequeBasedOnBidirectionalCyclicLinkedList&& obj)
	{
		list = obj.list;
		size = obj.size;
		obj.list = nullptr;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist)
	{
		for (const auto& element : ilist)
			Push(element);
		return *this;
	}

	template<typename T>
	bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PushFront(const T& element)
	{
		try {
			if (!list) {
				list = new CyclicLinkedList(element);
				size++;
				return true;
			}
			list->InsertAt(element, 0);
			size++;
			return true;
		}
		catch (...) {}
		return false;
	}

	template<typename T>
	bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PushBack(const T& element)
	{
		try {
			if (!list) {
				list = new CyclicLinkedList(element);
				size++;
				return true;
			}
			list->InsertAt(element, -1);
			size++;
			return true;
		}
		catch (...) {}
		return false;
	}

	template<typename T>
	bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PopFront(T& element)
	{
		try
		{
			element = list->Value();
			CyclicLinkedList* temp = list;
			list->Last()->changePrevious(list->Next());
			list = list->Next();
			delete temp;
			--size;
			return true;
		}
		catch (...)
		{

		}
		return false;
	}

	template<typename T>
	bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PopBack(T& element)
	{
		try
		{
			element = list->Last()->Value();
			list->RemoveAt(-1);
			--size;
			return true;
		}
		catch (...)
		{

		}
		return false;
	}

	template<typename T>
	bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PeekFront(T& element)
	{
		if (list)
		{
			element = list->Value();
			return true;
		}
		return false;
	}

	template<typename T>
	bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PeekBack(T& element)
	{
		if (list)
		{
			element = list->Last()->Value();
			return true;
		}
		return false;
	}




	template<typename T>
	T DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::operator++()
	{
		return list->Next()->Value();
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(const CyclicLinkedList& obj)
	{
		const CyclicLinkedList* iterator = obj.next;
		CyclicLinkedList onDelete = this->next;
		this = new CyclicLinkedList(obj.data, this, this);
		while (iterator != obj.previous)
		{
			InsertAt(iterator, -1);
			iterator = iterator->next;
		}
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(CyclicLinkedList&& obj)
	{
		next = obj.next;
		previous = obj.previous;
		data = obj.data;
		obj.next = nullptr;
		obj.previous = nullptr;
	}

	template<typename T>
	DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::CyclicLinkedList(std::initializer_list<T> ilist)
	{
		CyclicLinkedList* temp = new CyclicLinkedList(T());
		unsigned i = 1;
		for (const auto& element : ilist)
			(*temp).InsertAt(element, i++);
	}

	template<typename T>
	unsigned DequeBasedOnBidirectionalCyclicLinkedList<T>::CyclicLinkedList::GetSize() const
	{
		CyclicLinkedList* iterator = this->next;
		if (!this->next)
			return 0;
		unsigned count = 1;
		while (iterator != this)
			count++;
		return count;
	}
}



