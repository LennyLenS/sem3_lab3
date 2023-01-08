#pragma once
#include <string>
#include "avl.hpp"
#include "Pair.hpp"
#include "main_container.hpp"

template<typename Type>
class IDict : public Main_container<Type> {
protected:
	AVL<Pair<Type, int>>* dict;

public:
	IDict() {
		dict = new AVL<Pair<Type, int> >;
	}

	int bin_search(Type k) {
		return 0;
	}

	int add(Type k) override {
		Pair<Type, int> buf(k, 1);
		if (!this->dict->find(buf)) {
			this->dict->add(buf);
		}
		else {
			Pair<Type, int> a;
			this->dict->get(buf, a);
			buf.value++;
			update(buf.key, buf.value);
		}
		return 0;
	}

	int delet(Type k) override {
		Pair<Type, int> buf(k, 1);
		this->dict->delet(buf);
		return 0;
	}

	int update(Type k, int q = 1) override {
		Pair<Type, int> buf(k, q);
		this->dict->delet(buf);
		this->dict->add(buf);

		return 0;
	}

	bool find(Type k) override {
		Pair<Type, int> buf(k, 1);
		return this->dict->find(buf);
	}

	int get(Type k, Type& buf) override {
		Pair<Type, int> k1(k, 1);
		Pair<Type, int> ans(k, 1);
		this->dict->get(k1, ans);
		buf = ans.key;
		return 0;
	}

	int get_length() override {
		ArraySequence<Type> buf = this->getelement();
		return buf.GetLength();
	}

	int is_empty() override {
		if (this->get_length() == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	Type get_index(int index) override {
		ArraySequence<Type> buf = this->getelement();
		return buf.Get(index);
	}
	ArraySequence<Type> getelement() override {
		ArraySequence<Pair<Type, int> > buf = this->dict->getelements();
		ArraySequence <Type> ans;
		for (int i = 0; i < buf.GetLength(); ++i) {
			for (int j = 0; j < buf.Get(i).value; ++j) {
				ans.Append(buf.Get(i).key);
			}
		}
		return ans;
	}

};
