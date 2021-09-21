#ifndef FT_CONTAINERS_VECTOR_ITERATOR_HPP
# define FT_CONTAINERS_VECTOR_ITERATOR_HPP

# include "../iterator.hpp"
# include "../vector.hpp"

namespace ft {

    /**
     * Vector iterator
     * @tparam T Vector elements type
     */
    template<typename T, typename Pointer, typename Reference>
    class vector_iterator {
    public:
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef Pointer                    pointer;
        typedef Reference                  reference;
        typedef random_access_iterator_tag iterator_category;

    private:
        pointer _p;

    public:
        vector_iterator();
        explicit vector_iterator(pointer p);
        template<typename SPointer, typename SReference>
        explicit vector_iterator(const vector_iterator<T, SPointer, SReference> &src);

        ~vector_iterator();

        pointer               base() const;

        template<typename SPointer, typename SReference>
        vector_iterator       &operator=(vector_iterator<T, SPointer, SReference> const &other);

        reference             operator*() const;
        pointer               operator->() const;

        vector_iterator       &operator++();
        const vector_iterator operator++(int);

        vector_iterator       &operator--();
        const vector_iterator operator--(int);

        vector_iterator       operator+(difference_type n) const;
        vector_iterator       operator-(difference_type n) const;

        vector_iterator       operator+=(difference_type n);
        vector_iterator       operator-=(difference_type n);

        reference             operator[](difference_type n) const;
    };

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference>::vector_iterator(): _p(NULL) {}

    /**
     * Constructor from pointer
     * @param node Pointer to elem
     */
    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference>::vector_iterator(pointer p): _p(p) {}

    template<typename T, typename Pointer, typename Reference>
    template<typename SPointer, typename SReference>
    vector_iterator<T, Pointer, Reference>::vector_iterator(const vector_iterator<T, SPointer, SReference> &src): _p(src.base()) {}

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference>::~vector_iterator() {}

    template<typename T, typename Pointer, typename Reference>
    typename vector_iterator<T, Pointer, Reference>::pointer vector_iterator<T, Pointer, Reference>::base() const {
        return (_p);
    }

    template<typename T, typename Pointer, typename Reference>
    template<typename SPointer, typename SReference>
    vector_iterator<T, Pointer, Reference> &vector_iterator<T, Pointer, Reference>::operator=(const vector_iterator<T, SPointer, SReference> &other) {
        this->_p = other.base();
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    typename vector_iterator<T, Pointer, Reference>::reference vector_iterator<T, Pointer, Reference>::operator*() const {
        return (*_p);
    }

    template<typename T, typename Pointer, typename Reference>
    typename vector_iterator<T, Pointer, Reference>::pointer vector_iterator<T, Pointer, Reference>::operator->() const {
        return (_p);
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> &vector_iterator<T, Pointer, Reference>::operator++() {
        _p++;
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    const vector_iterator<T, Pointer, Reference> vector_iterator<T, Pointer, Reference>::operator++(int) {
        vector_iterator it(*this);
        _p++;
        return (it);
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> &vector_iterator<T, Pointer, Reference>::operator--() {
        _p--;
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    const vector_iterator<T, Pointer, Reference> vector_iterator<T, Pointer, Reference>::operator--(int) {
        vector_iterator it(*this);
        _p--;
        return (it);
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> vector_iterator<T, Pointer, Reference>::operator+(vector_iterator::difference_type n) const {
        return (vector_iterator(_p + n));
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> vector_iterator<T, Pointer, Reference>::operator-(vector_iterator::difference_type n) const {
        return (vector_iterator(_p - n));
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> vector_iterator<T, Pointer, Reference>::operator+=(vector_iterator::difference_type n) {
        _p += n;
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> vector_iterator<T, Pointer, Reference>::operator-=(vector_iterator::difference_type n) {
        _p -= n;
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    typename vector_iterator<T, Pointer, Reference>::reference vector_iterator<T, Pointer, Reference>::operator[](vector_iterator::difference_type n) const {
        return (*(*this + n));
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator==(const vector_iterator<T, LPointer, LReference> &lhs, const vector_iterator<T, RPointer, RReference> &rhs) {
        return (lhs.base() == rhs.base());
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator!=(const vector_iterator<T, LPointer, LReference> &lhs, const vector_iterator<T, RPointer, RReference> &rhs) {
        return (lhs.base() != rhs.base());
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator<(const vector_iterator<T, LPointer, LReference> &lhs, const vector_iterator<T, RPointer, RReference> &rhs) {
        return (rhs > lhs);
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator>(const vector_iterator<T, LPointer, LReference> &lhs, const vector_iterator<T, RPointer, RReference> &rhs) {
        return (lhs.base() > rhs.base());
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator<=(const vector_iterator<T, LPointer, LReference> &lhs, const vector_iterator<T, RPointer, RReference> &rhs) {
        return (!(lhs > rhs));
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator>=(const vector_iterator<T, LPointer, LReference> &lhs, const vector_iterator<T, RPointer, RReference> &rhs) {
        return (!(rhs > lhs));
    }

    template<typename T, typename Pointer, typename Reference>
    vector_iterator<T, Pointer, Reference> operator+(typename vector_iterator<T, Pointer, Reference>::difference_type n, const vector_iterator<T, Pointer, Reference> x) {
        return (x + n);
    }

    template<typename T, typename Pointer, typename Reference>
    typename vector_iterator<T, Pointer, Reference>::difference_type
    operator-(const vector_iterator<T, Pointer, Reference> &lhs, const vector_iterator<T, Pointer, Reference> &rhs) {
        return (lhs.base() - rhs.base());
    }

}

#endif //FT_CONTAINERS_VECTOR_ITERATOR_HPP
