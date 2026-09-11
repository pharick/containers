# containers

A C++98 reimplementation of `std::list`, `std::vector`, `std::map`, `std::set` and `std::stack` for the École 42 `ft_containers` project, including a red-black tree, iterators, `reverse_iterator`, `pair` and the `enable_if`/`is_integral` traits needed to make the interfaces behave like the standard ones.

Implementation of some standard containers from the C++ STL library. A project completed at Ecole42. Everything lives in header-only templates under `namespace ft` and mirrors the C++98 interface of the corresponding `std::` container: the same typedefs, the default/fill/range/copy constructors, allocator support, relational operators and `swap`. A test program exists in two copies, one compiled against `ft::` and one against `std::`, so their output can be diffed.

## Highlights

- Red-black tree behind `map` and `set` (`srcs/rb_tree.hpp`, ~950 lines): nodes carry parent pointers and a sentinel `_end` node is linked above the root, so `end()` is decrementable and in-order `++`/`--` walk parent links without an auxiliary stack. Insertion is a plain BST insert followed by the standard fix-up (red uncle: recolour and move up; otherwise one or two rotations and a colour swap), and the tree exposes `lower_bound`, `upper_bound`, `equal_range`, deep copy that preserves colours, and a `print()` dump showing each node's colour.
- Node value storage is separate from the node: each node holds a `T *` obtained from the element allocator, and the node itself comes from a node allocator. This is what lets `pair<const Key, T>` live in the tree and be replaced (the two-child erase case destroys and reconstructs the value in place through the allocator).
- One iterator template per container, parameterised on `<T, Pointer, Reference>`, so `iterator` and `const_iterator` are instances of the same class; a converting constructor provides iterator-to-const_iterator, and the comparison operators are templated over both sides.
- SFINAE without C++11: range constructors, `assign` and `insert` are guarded by `ft::enable_if<!ft::is_integral<It>::value && ft::is_input_iterator_tag<...>::value>` so that `vector<int> v(5, 42)` does not resolve to the iterator overload. `ft::distance` dispatches on random-access vs other iterator categories the same way.
- `vector` growth: capacity doubles on overflow (`max(min(capacity * 2, max_size()), needed)`), reallocation copies elements with the allocator's `construct`/`destroy`, and `at()` throws `std::out_of_range`. Random-access iterator arithmetic is implemented on a raw pointer.
- `list` is a circular doubly-linked list with a sentinel node: O(1) `splice` by relinking, `sort` is a recursive merge sort using a slow/fast-pointer split and an in-place `merge`, plus `unique`, `remove_if`, `reverse`.
- `stack` is an adapter over `ft::vector` by default with friend relational operators; `map::operator[]` is implemented as insert-or-find.
- Doxygen-style comments on every public method; compiled with `-Wall -Wextra -Werror -std=c++98`.

## Is it C++98?

Yes. The Makefile compiles with `-std=c++98 -Werror`; the sources use no `auto`, `nullptr`, rvalue references, initializer lists or `>>` template closers. The only C++11-era item is the `long long` specialisations of `is_integral`, which compilers accept in C++98 mode as an extension.

## Project layout

```
srcs/
  vector.hpp                 ft::vector
  list.hpp                   ft::list (circular, sentinel node)
  map.hpp                    ft::map  (wraps RBTree with a value_compare on keys)
  set.hpp                    ft::set  (wraps RBTree directly)
  stack.hpp                  ft::stack (adapter, default container ft::vector)
  rb_tree.hpp                RBTree<T, Compare, Alloc, NodeAlloc>
  iterators/
    vector_iterator.hpp      random-access iterator over T*
    list_iterator.hpp        bidirectional iterator over ListNode
    rb_tree_iterator.hpp     bidirectional in-order iterator over RBTreeNode
  iterator.hpp               iterator tags, iterator_traits, distance, reverse_iterator
  type_traits.hpp            enable_if, is_integral
  utility.hpp                pair, make_pair, relational operators
  functional.hpp             binary_function, less
  algorithm.hpp              swap, min, max
main_ft.cpp                  test program using ft:: containers
main_std.cpp                 the same program using std:: containers
```

About 4,500 lines of headers plus two 1,181-line test drivers.

## Building and running tests

Requirements: `clang++` (called by name in the Makefile) and `make`.

```
make && ./containers_ft
```

`make` builds two binaries, `containers_ft` and `containers_std`. Both run the same sequence of list, vector, map, stack and set operations (constructors, iterators, reverse iterators, insert/erase, splice/sort/merge, bounds queries, relational operators) and print the results, so the two outputs can be compared with `diff`. Other targets: `make clean`, `make fclean`, `make re`.

## Limitations / notes

- `insert(hint, value)` ignores the hint. `list::size()` walks the list (O(n), allowed in C++98).
- `map::find`, `count`, `erase(key)` and the bound queries build a temporary `pair(key, mapped_type())`, so the mapped type must be default-constructible.
- No allocator-aware `swap` of the sentinel node in `list`, and no `multimap`/`multiset`/`deque`.

## Context

École 42 `ft_containers`: reimplement the listed STL containers in C++98 with the same interface and behaviour as the standard ones, using a red-black tree for the associative containers, without any C++11 features.
