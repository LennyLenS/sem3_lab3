#pragma once

template <class T1, class T2>
class Pair {
public:
	T1 key;
	T2 value;
	Pair(T1 a, T2 b){
		key = a;
		value = b;
	}
	Pair(T1 a) {
		key = a;
	}
	Pair() {
	}

	Pair<T1, T2>& operator = (Pair<T1, T2> a) {
		this->key = a.key;
		this->value = a.value;
		return *this;
	}

	Pair(const Pair<T1, T2> &a) {
		this->key = a.key;
		this->value = a.value;
	}
};

template <class T1, class T2>
Pair<T1, T2> operator + (Pair<T1, T2>& a, Pair<T1, T2>& b) {
	Pair<T1, T2> buf(a.key, a.value + b.value);
	return buf;
}

template <class T1, class T2>
bool operator > (Pair<T1, T2>& a, Pair<T1, T2>& b) {
	return (a.key > b.key);
}

template <class T1, class T2>
bool operator >= (Pair<T1, T2>& a, Pair<T1, T2>& b) {
	return (a.key >= b.key);
}

template <class T1, class T2>
bool operator < (Pair<T1, T2>& a, Pair<T1, T2>& b) {
	return (a.key < b.key);
}

template <class T1, class T2>
bool operator == (Pair<T1, T2>& a, Pair<T1, T2>& b) {
	return (a.key == b.key);
}

template <class T1, class T2>
bool operator == (const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return (a.key == b.key);
}

template <class T1, class T2>
std::ostream& operator<< (std::ostream& out, Pair<T1, T2>& a){
	out << "(" << a.key << ", " << a.value << ")";

	return out;
}