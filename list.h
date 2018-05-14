#include <iostream>
#include <ostream>
template<class T>
class Node{
	public:
	  //Node() {}
		T value;
		Node<T>* next;
		Node(const T&);
};
template<class T>
class LinkedList{
	typedef Node<T>* pNode;
  public:
		pNode pHead;
		pNode pLast;
	public:
		LinkedList();
		void popFront();
		void popBack();
		bool find(T, pNode*&);
		bool recursiveFind(T&, pNode&);
		T greaterElement();
		void deleteElement(T);
		LinkedList<T> concatenate(const LinkedList<T>&);
		LinkedList<T> intersection(const LinkedList<T>&);
		template<class U>
		friend std::ostream& operator<<(std::ostream& output, const LinkedList<U>& o){
  		pNode temp=o->pHead;
  		for (;temp != NULL;temp=temp->next)
    		output << temp->value << std::endl;
  		return output;
		}
		bool insert(T);
};
///////clase Node//////////
template<class T>
Node<T>::Node(const T& _value): value(_value), next(NULL) {}
//////clase LinkedList///////
template<class T>
LinkedList<T>::LinkedList(): pHead(NULL), pLast(NULL) {}
template<class T>
void LinkedList<T>::popFront(){
	if(pHead){
		if (pHead==pLast)
			pLast=NULL;
		pNode temp = pHead;
		pHead = pHead->next;
		delete temp;
	}
}
template<class T>
void LinkedList<T>::popBack(){
	if(pLast){
		if (pHead==pLast){
			delete pLast;
			pLast = pHead = NULL;
		}
		else{
			pNode temp=pHead;
			while(temp->next!=pLast)
				temp=temp->next;
			delete pLast;
			pLast=temp;
		}
	}
}
template<class T>
bool LinkedList<T>::find(T _value, pNode*&p){
	p = &pHead;
	while ((*p)){
		if((*p)->value == _value)
			return true;
    if((*p)->value > _value)
  		return false;
		p=&((*p)->next);
	}
	return false;
}
template<class T>
bool LinkedList<T>::recursiveFind(T& element, pNode& fnode){
	if (!fnode) return 0;
	if (fnode->value==element) return 1;
	else return recursiveFind(element, fnode->next);
}
template<class T>
void LinkedList<T>::deleteElement(T _value){
	if(!pHead) return;
	if (pHead->value==_value){
		if (pHead==pLast)
			pLast=NULL;
		delete pHead;
		pHead=NULL;
	}
	else{
		pNode back = pHead;
		pNode cur = back->next;
		for (;cur;cur=cur->next){
			if (cur->value==_value){
				back->next=cur->next;
				if (cur==pLast)
					pLast=back;
				delete cur;
				break;
			}
			back=cur;
		}
	}
}
template<class T>
T LinkedList<T>::greaterElement(){
	if (!pHead) return -1;
	T greater=pHead->value;
	pNode temp=pHead;
	for(;temp;temp=temp->next){
		if (temp->value>greater)
			greater=temp->value;
	}
	return greater;
}
template<class T>
LinkedList<T> LinkedList<T>::intersection(const LinkedList<T>& list){
	LinkedList<T> newList = new LinkedList<T>;
	pNode temp = pHead;
	for (;temp;temp=temp->next){
    if (list->find(temp->value))
      if (!newList->find(temp->value))
				newList->pushBack(temp->value);
  }
	return newList;
}
template<class T>
LinkedList<T> LinkedList<T>::concatenate(const LinkedList<T>& list){
	LinkedList<T> newList = new LinkedList<T>;
  pNode temp = pHead;
	for (;temp;temp=temp->next)
		if (!newList->find(temp->value))
			newList->pushBack(temp->value);
	temp=list->pHead;
		if (!this->find(temp->value))
			if (!newList->find(temp->value))
				newList->pushBack(temp->value);
  return newList;
}
template<class T>
bool LinkedList<T>::insert(T _value){
  pNode *p;
  if(!find(_value, p)){
  	pNode newNode = new Node<T>(_value);
  	newNode->next = *p;
  	*p = newNode;
		if(!newNode->next)
			pLast = newNode;
  	return true;
  }
  return false;
}
