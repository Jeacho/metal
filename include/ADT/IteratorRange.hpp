//--- IteratorRange.hpp - Range adapter for iterators ---------------- C++ ---//
//
//	Adaptor for a begin and end iterator into a range type.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_ADT_ITERATORRANGE_HPP
#define METAL_ADT_ITERATORRANGE_HPP

#include <iterator>
#include <utility>

template <typename IteratorT>
class iterator_range {
  IteratorT begin_iterator, end_iterator;

public:
	template <typename Container>
	iterator_range(Container &&c)
		: begin_iterator(c.begin()), end_iterator(c.end()) { }

	iterator_range(IteratorT begin_iterator, IteratorT end_iterator)
		: begin_iterator(std::move(begin_iterator)),
		  end_iterator(std::move(end_iterator)) { }

	IteratorT begin() const { return begin_iterator; }
	IteratorT end() const { return end_iterator; }
};

template <class T> iterator_range<T> make_range(T x, T y) {
	return iterator_range<T>(std::move(x), std::move(y));
}

template <typename T> iterator_range<T> make_range(std::pair<T, T> p) {
	return iterator_range<T>(std::move(p.first), std::move(p.second));
}

template<typename T>
iterator_range<decltype(begin(std::declval<T>()))> drop_begin(T &&t, int n) {
	return make_range(std::next(begin(t), n), end(t));
}

#endif // METAL_ADT_ITERATORRANGE_HPP
