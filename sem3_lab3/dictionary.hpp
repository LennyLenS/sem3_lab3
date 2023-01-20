#pragma once
#include <string>
#include "avl.hpp"
#include "Pair.hpp"

template<typename Tkey, typename Tvalue>
class IDict {
protected:
	AVL<Pair<Tkey, Tvalue>>* dict;

public:
	IDict() {
		dict = new AVL<Pair<Tkey, Tvalue> >;
	}

	int add(Tkey k, Tvalue v) {
		Pair<Tkey, Tvalue> buf(k, v);
		if (!this->dict->find(buf)) {
			this->dict->add(buf);
		}
		return 0;
	}

	int delet(Tkey k) {
		Pair<Tkey, Tvalue> buf(k);
		this->dict->delet(buf);
		return 0;
	}

	bool find(Tkey k) {
		Pair<Tkey, Tvalue> buf(k);
		return this->dict->find(buf);
	}

	Tvalue get(Tkey k) {
		Pair<Tkey, Tvalue> k1(k);
		Pair<Tkey, Tvalue> ans();
		//ans = this->dict->get(k1);
		return this->dict->get(k1).value;
	}

	int get_length() {
		ArraySequence<Tvalue> buf = this->getelement();
		return buf.GetLength();
	}

	int is_empty() {
		if (this->get_length() == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	ArraySequence<Tvalue> getelement() {
		ArraySequence<Pair<Tkey, Tvalue> > buf = this->dict->getelements();
		ArraySequence <Tvalue> ans;
		for (int i = 0; i < buf.GetLength(); ++i) {
			ans.Append(buf.Get(i).value);
		}
		return ans;
	}

};
