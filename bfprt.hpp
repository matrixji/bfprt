// header only bfprt for top k select

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>

namespace mj {
namespace bfprt {

// partial sort interface
template<typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
void nth_element(Iterator begin, Iterator nth, Iterator end, Compare compare = {});

namespace detail {

// block size for using insert sort
inline constexpr size_t minimal_block_size() {
    return 5;
}

// sort for short ranges, using std::sort
template<typename Iterator, typename Compare = std::less<typename Iterator::value_type>>
inline void inner_sort(Iterator begin, Iterator end, Compare compare = {}) {
    return std::sort(begin, end, compare);
}

template<typename Iterator, typename Compare = std::less<typename Iterator::value_type>>
inline Iterator partition(Iterator begin, Iterator end, Iterator pivot, Compare compare = {}) {
    Iterator i = begin;
    Iterator j = std::prev(end);
    std::swap(*pivot, *i);
    pivot = i++;
    while (i < j) {
        while (compare(*i, *pivot)) {
            i++;
        }
        while (!compare(*j, *pivot)) {
            j--;
        }
        if (i < j) {
            std::swap(*i, *j);
        }
    }
    while (compare(*pivot, *i)) {
        i--;
    }
    std::swap(*pivot, *i);
    return i;
}

template<typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
inline Iterator select_nth(Iterator begin, Iterator nth, Iterator end, Compare compare = {});

template<typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
inline Iterator mid_of_median(Iterator begin, Iterator end, Compare compare = {}) {
    if (end - begin <= minimal_block_size()) {
        inner_sort(begin, end, compare);
        return begin + (end - begin) / 2;
    }
    Iterator cursor = begin;
    Iterator it = begin;
    size_t range = 0;
    while (it < end) {
        size_t range = std::min<size_t>(minimal_block_size(), end - it);
        Iterator next = it + range;
        inner_sort(it, next, compare);
        std::swap(*cursor, *(it + range / 2));
        cursor++;
        it = next;
    }
    return select_nth(begin, begin + (cursor - begin) / 2, cursor, compare);
}

template<typename Iterator, typename Compare>
inline Iterator select_nth(Iterator begin, Iterator nth, Iterator end, Compare compare) {
    if (end - begin <= minimal_block_size()) {
        inner_sort(begin, end, compare);
        return nth;
    }
    Iterator mom = mid_of_median(begin, end, compare);
    Iterator iter = partition(begin, end, mom, compare);
    if (iter == nth) {
        return iter;
    } else if (iter > nth) {
        return select_nth(begin, nth, iter, compare);
    } else {
        return select_nth(iter + 1, nth, end, compare);
    }
}

}  // namespace detail

template<typename Iterator, typename Compare>
void nth_element(Iterator begin, Iterator nth, Iterator end, Compare compare) {
    (void)detail::select_nth(begin, nth, end, compare);
}

}  // namespace bfprt
}  // namespace mj
