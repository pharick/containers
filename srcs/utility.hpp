#ifndef FT_CONTAINERS_UTILITY_HPP
# define FT_CONTAINERS_UTILITY_HPP

# include <ostream>

namespace ft {

    /**
     * Pair of values
     * @tparam T1 Type of member first
     * @tparam T2 Type of member second
     */
    template<typename T1, typename T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type  first;
        second_type second;

        pair();
        template<typename U, typename V>
        pair(const pair<U, V> &pr);
        pair(const first_type &a, const second_type &b);

        pair &operator=(const pair &pr);
    };

    template<typename T1, typename T2>
    pair<T1, T2>::pair(): first(T1()), second(T2()) {}

    template<typename T1, typename T2>
    template<typename U, typename V>
    pair<T1, T2>::pair(const pair<U, V> &pr): first(first_type(pr.first)), second(second_type(pr.second)) {}

    template<typename T1, typename T2>
    pair<T1, T2>::pair(const first_type &a, const second_type &b): first(a), second(b) {}

    template<typename T1, typename T2>
    pair<T1, T2> &pair<T1, T2>::operator=(const pair &pr) {
        if (this == &pr)
            return (*this);

        first = pr.first;
        second = pr.second;

        return (*this);
    }

    template<typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template<typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs == rhs));
    }

    template<typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template<typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(rhs < lhs));
    }

    template<typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (rhs < lhs);
    }

    template<typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs < rhs));
    }

    /**
     * Construct pair object
     * @param x Value for the member first
     * @param y Value for the member second
     * @return A pair object whose elements first and second are set to x and y respectivelly
     */
    template<typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y) {
        return (pair<T1, T2>(x, y));
    }

    template<typename T1, typename T2>
    std::ostream &operator<<(std::ostream &o, const pair<T1, T2> &p) {
        o << "(" << p.first << ", " << p.second << ")";
        return (o);
    }

}

#endif //FT_CONTAINERS_UTILITY_HPP
