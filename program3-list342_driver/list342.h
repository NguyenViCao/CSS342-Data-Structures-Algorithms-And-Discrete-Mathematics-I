#ifndef LIST342_H_
#define LIST342_H_
#include <iostream>
#include <string>
#include <fstream>
#include "child.h"
using namespace std;

template<class T>
class List342
{
	struct Node
	{
		T* data = nullptr;
		Node* next = nullptr;
	};

public:
	List342();
	List342(const List342<T>& source);
	~List342();

	//required actions
	bool BuildList(string file_name);
	bool Insert(T* obj);
	bool Remove(T target, T& result);
	bool Peek(T target, T& result) const;
	bool isEmpty() const;
	void DeleteList();
	bool Merge(List342& source);
	bool RemoveDuplicate(List342<T>& source);
	int Size();

	//operator overloading
	List342<T> operator+(const List342<T>& source) const;
	List342<T>& operator+=(const List342<T>& source);
	List342<T>& operator=(const List342<T>& source);
	bool operator==(List342<T>& source);
	bool operator!=(List342<T>& source);

	friend ostream& operator<<(ostream& stream, const List342<T>& source)
	{
		Node* p_node = source.head_;
		while (p_node != nullptr)
		{
			stream << *(p_node->data);
			p_node = p_node->next;
		}
		return stream;
	}

private:
	Node* head_;
};

template <class T>
List342<T>::List342() :head_(nullptr)
{
}

template <class T>
List342<T>::List342(const List342<T>& source)
{
	head_ = nullptr;
	*this = source;
}

template <class T>
List342<T>::~List342()
{
	DeleteList();
}

template <class T>
bool List342<T>::BuildList(string file_name)
{
	ifstream file;
	file.open(file_name);

	if (file.is_open())
	{
		while (!file.eof())
		{
			T obj;
			file >> obj;
			Insert(&obj);
		}
		file.close();
		return true;
	}
	else
	{
		cout << "Can't open file." << endl;
		return false;
	}
}

template <class T>
bool List342<T>::Insert(T *obj)
{
	T* object = new T(*obj);

	//if list is empty
	if (head_ == nullptr)
	{
		head_ = new Node;
		head_->data = object;
		head_->next = nullptr;
		return true;
	}

	//first in line
	if (*object <= *head_->data)
	{
		if (*object == *head_->data)
		{
			delete object;
			return false;
		}

		Node* insert_node = new Node;
		insert_node->data = object;
		insert_node->next = head_;
		head_ = insert_node;
		return true;
	}

	//temp sort into the right order
	Node* tmp = head_;
	while (tmp->next != nullptr && *tmp->next->data <= *object)
	{
		if (*tmp->next->data == *object)
		{
			delete object;
			return false;
		}
		tmp = tmp->next;
	}

	//add object node in front of the node that has larger value
	Node* insert_node = new Node;
	insert_node->data = object;
	insert_node->next = tmp->next;
	tmp->next = insert_node;
	return true;
}

template <class T>
bool List342<T>::Remove(T target, T& result)
{
	//if list is empty
	if (head_ == nullptr)
	{
		return false;
	}

	//target at first node of the list
	if (*head_->data == target)
	{
		result = target;
		Node* tmp = head_;
		head_ = head_->next;
		delete tmp->data;
		delete tmp;
		return true;
	}

	//current node move until its next node has a larger value than object
	Node* insert_node = head_;
	while ((insert_node->next != nullptr) && (*insert_node->next->data < target))
	{
		insert_node = insert_node->next;
	}

	//stop if end of list or can't find target
	if ((insert_node->next == nullptr) || (*insert_node->next->data != target))
	{
		return false;
	}

	//remove if target found
	Node* tmp = insert_node->next;
	insert_node->next = insert_node->next->next;
	result = target;
	delete tmp->data;
	delete tmp;
	return true;
}

template <class T>
bool List342<T>::Peek(T target, T& result) const
{
	//check if list is empty
	if (head_ == nullptr)
	{
		return false;
	}

	Node* insert_node = head_;
	while (insert_node != nullptr)
	{
		if (*insert_node->data == target)
		{
			result = target;
			return true;
		}
		insert_node = insert_node->next;
	}
	return false;
}

template <class T>
bool List342<T>::isEmpty()const
{
	return (head_ == nullptr);
}

template <class T>
void List342<T>::DeleteList()
{
	while (head_ != nullptr)
	{
		Node* tmp = head_;
		head_ = head_->next;
		delete tmp->data;
		delete tmp;
	}
}

template <class T>
bool List342<T>::Merge(List342<T>& source)
{
	if (this == &source)
	{
		return false;
	}

	Node* lhs = head_;
	Node* tmp_lhs = nullptr;
	Node* tmp_rhs = nullptr;

	if (source.isEmpty())
	{
		return false;
	}

	//if lhs is empty then rhs = lhs
	if (isEmpty())
	{
		head_ = source.head_;
		source.head_ = nullptr;
		return true;
	}

	//lhs head larger or equal to rhs head
	if (*head_->data >= *source.head_->data)
	{
		if (*head_->data == *source.head_->data)
		{
			RemoveDuplicate(source);
		}
		else
		{
			head_ = source.head_;
			source.head_ = source.head_->next;
			head_->next = lhs;
			lhs = head_;
		}
	}

	//merge until rhs = nullptr
	while (!source.isEmpty())
	{
		//end node of lhs
		if (lhs->next == nullptr && (*lhs->data <= *source.head_->data))
		{
			if (*lhs->data == *source.head_->data)
			{
				RemoveDuplicate(source);
			}

			lhs->next = source.head_;
			source.head_ = nullptr;
			return true;
		}

		//insert rhs node to lhs source before the smallest larger value node
		if (lhs->next != nullptr && *lhs->next->data >= *source.head_->data)
		{
			if (*lhs->next->data == *source.head_->data)
			{
				RemoveDuplicate(source);
			}
			else
			{
				tmp_rhs = source.head_;
				tmp_lhs = lhs->next;
				source.head_ = source.head_->next;
				lhs->next = tmp_rhs;
				tmp_rhs->next = tmp_lhs;
			}
		}

		lhs = lhs->next;
	}
	return true;
}

template< class T>
bool List342<T>::RemoveDuplicate(List342<T>& source)
{
	Node* insert_node = source.head_;
	source.head_ = source.head_->next;
	delete insert_node->data;
	delete insert_node;
	return true;
}

template <class T>
int List342<T>::Size()
{
	Node* tmp = head_;
	int size = 0;
	while (tmp != nullptr)
	{
		size += 1;
		tmp = tmp->next;
	}
	return size;
}

template <class T>
List342<T>& List342<T>::operator=(const List342<T>& source)
{
	if (this == &source)
	{
		return *this;
	}
	DeleteList();

	Node* tmp = source.head_;
	while (tmp != nullptr)
	{
		Insert(tmp->data);
		tmp = tmp->next;
	}
	return *this;
}

template< class T>
List342<T> List342<T>::operator+(const List342<T>& source) const
{
	List342<T> new_list, tmp_list;
	new_list = *this;
	tmp_list = source;
	new_list += tmp_list;
	return new_list;
}

template <class T>
List342<T>& List342<T>::operator+=(const List342<T>& source)
{
	List342<T> tmp_list;
	tmp_list = source;
	Merge(tmp_list);
	return *this;
}

template <class T>
bool List342<T>::operator==(List342<T>& source)
{
	if (Size() != source.Size())
	{
		return false;
	}

	Node* rhs = source.head_;
	Node* lhs = head_;
	while (lhs != nullptr && rhs != nullptr)
	{
		if (*lhs->data != *rhs->data)
		{
			return false;
		}
		lhs = lhs->next;
		rhs = rhs->next;
	}
	return true;
}

template <class T>
bool List342<T>::operator!=(List342<T>& source)
{
	return !(*this == source);
}
#endif