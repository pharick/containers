#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <set>

template<typename T>
void print_list(const std::list<T> &lst) {
    typename std::list<T>::const_iterator it;
    for (it = lst.begin(); it != lst.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_list_reverse(const std::list<T> &lst) {
    typename std::list<T>::const_reverse_iterator it;
    for (it = lst.rbegin(); it != lst.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_vector(const std::vector<T> &vct) {
    typename std::vector<T>::const_iterator it;
    for (it = vct.begin(); it != vct.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_vector_reverse(const std::vector<T> &vct) {
    typename std::vector<T>::const_reverse_iterator it;
    for (it = vct.rbegin(); it != vct.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename Key, typename T>
void print_map(const std::map<Key, T> &mp) {
    typename std::map<Key, T>::const_iterator it;
    for (it = mp.begin(); it != mp.end(); it++) {
        std::cout << "(" << it->first << ": " << it->second << ") ";
    }
    std::cout << std::endl;
}

template<typename Key, typename T>
void print_map_reverse(const std::map<Key, T> &mp) {
    typename std::map<Key, T>::const_reverse_iterator it;
    for (it = mp.rbegin(); it != mp.rend(); it++) {
        std::cout << "(" << it->first << ": " << it->second << ") ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_stack(const std::stack<T> st) {
    std::stack<T> st1 = st;
    while (!st1.empty()) {
        std::cout << st1.top() << " ";
        st1.pop();
    }
    std::cout << std::endl;
}

template<typename T>
void print_set(const std::set<T> st) {
    typename std::set<T>::const_iterator it;
    for (it = st.begin(); it != st.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_set_reverse(const std::set<T> st) {
    typename std::set<T>::const_reverse_iterator it;
    for (it = st.rbegin(); it != st.rend(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

bool is_even(int n) {
    return (n % 2 == 0);
}

bool is_both_even_or_odd(int a, int b) {
    return (a % 2 == b % 2);
}

bool isLessLen(const std::string &a, const std::string &b) {
    return (a.size() < b.size());
}

bool isFirstLetterLess(std::string &a, const std::string &b) {
    return (a[0] < b[0]);
}

void list_test() {
    /**
     * Empty container constructor (default constructor)
     */
    std::list<int> lst1;
    print_list(lst1);

    /**
     * Fill constructor
     */
    std::list<std::string> lst2(7, "hello");
    print_list(lst2);

     /**
      * Range constructor
      */
    std::list<std::string>::iterator lst2_it1 = lst2.begin();
    std::list<std::string>::iterator lst2_it2 = lst2.end();
    lst2_it1++;
    lst2_it2--;
    lst2_it2--;
    std::list<std::string> lst3(lst2_it1, lst2_it2);
    print_list(lst3);

    /**
     * Copy constructor
     */
    std::list<std::string> lst4(lst3);
    print_list(lst4);

    lst3.push_front("privet");
    lst3.push_back("poka");
    print_list_reverse(lst3);
    print_list(lst4);

    /**
     * operator=
     */
    lst4 = lst3;
    print_list(lst4);

    /**
     * begin
     */
    lst2_it1 = lst2.begin();
    std::cout << lst2.size() << " " << *lst2_it1 << std::endl;
    *lst2_it1 = "bazinga";
    print_list(lst2);
//    std::list<std::string>::const_iterator lst2_const_it = lst2_it1;
//    *lst2_const_it = "what?!";

    /**
     * end
     */
    lst2_it2 = lst2.end();
    std::cout << lst2.size() << std::endl;
    --lst2_it2;
    *lst2_it2 = "qq";
    print_list(lst2);
//    std::list<std::string>::const_iterator lst2_const_it2 = lst2_it2;
//    *lst2_const_it2 = "wtf?!";

    /**
     * rbegin
     */
    std::list<std::string>::reverse_iterator lst2_rev_it1 = lst2.rbegin();
    std::cout << *lst2_rev_it1 << std::endl;
    lst2_rev_it1++;
    *lst2_rev_it1 = "wine";
    print_list(lst2);
    std::list<std::string>::const_reverse_iterator lst2_const_rev_it1 = lst2_rev_it1;
//    *lst2_const_rev_it1 = "nope";
    lst2_const_rev_it1--;
    std::cout << *lst2_const_rev_it1 << std::endl;

    /**
     * rend;
     */
    std::list<std::string>::reverse_iterator lst2_rev_it2 = lst2.rend();
    lst2_rev_it2--;
    std::cout << *lst2_rev_it2 << std::endl;
    lst2_rev_it2--;
    *lst2_rev_it2 = "cplusplus";
    print_list(lst2);
    std::list<std::string>::const_reverse_iterator lst2_const_rev_it2 = lst2_rev_it2;
//    *lst2_const_rev_it2 = "ahaha!";
    std::cout << *lst2_const_rev_it2 << std::endl;

    /**
     * empty
     */
    std::cout << "lst1 empty: " << lst1.empty() << std::endl;
    std::cout << "lst2 empty: " << lst2.empty() << std::endl;

    /**
     * size
     */
    std::cout << "lst1 size: " << lst1.size() << std::endl;
    std::cout << "lst3 size: " << lst3.size() << std::endl;

    /**
     * max_size
     */
    std::cout << "lst1 max_size: " << lst1.max_size() << std::endl;

    /**
     * front
     */
    lst1.push_back(4);
    lst1.push_back(8);
    lst1.push_back(15);
    lst1.push_back(16);
    lst1.push_back(23);
    lst1.push_back(42);
    int &front_ref = lst1.front();
    std::cout << front_ref << std::endl;
    front_ref = 21;
    print_list(lst1);

    /**
     * back
     */
     const std::list<int> &lst1_ref = lst1;
//     lst1_ref.back() = 999;
    std::cout << lst1_ref.back() << std::endl;

    /**
     * assign
     */
    std::list<int> lst5(4, 7);
    print_list(lst5);
    lst5.assign(lst1.begin(), lst1.end());
    print_list(lst5);
    lst5.assign(7, 42);
    print_list(lst5);

    /**
     * push_front
     */
    lst1.push_front(555);
    print_list(lst1);

    /**
     * pop_front
     */
    lst1.pop_front();
    print_list(lst1);

    /**
     * push_back
     */
    lst1.push_back(555);
    print_list(lst1);

    /**
     * pop_back
     */
    lst1.pop_back();
    print_list(lst1);

    /**
     * insert
     */
    std::list<int>::iterator lst1_it1 = lst1.begin();
    lst1_it1++;
    lst1_it1++;
    lst1_it1 = lst1.insert(lst1_it1, 222);
    print_list(lst1);
    std::cout << *lst1_it1 << std::endl;

    lst1.insert(lst1_it1, 2, 4);
    print_list(lst1);

    lst1.insert(lst1_it1, lst5.begin(), lst5.end());
    print_list(lst1);

    /**
     * erase
     */
     lst1_it1 = lst1.erase(lst1_it1);
     print_list(lst1);
     std::cout << *lst1_it1 << std::endl;

     lst1_it1 = lst1.erase(lst1_it1, lst1.end());
     print_list(lst1);
     std::cout << (lst1_it1 == lst1.end()) << std::endl;

     /**
      * swap
      */
     print_list(lst1);
     print_list(lst5);
     lst1.swap(lst5);
     print_list(lst1);
     print_list(lst5);

    /**
     * resize
     */
    print_list(lst1);
    lst1.resize(3);
    print_list(lst1);
    lst1.resize(5, 21);
    print_list(lst1);
    lst1.resize(7);
    print_list(lst1);

    /**
     * clear
     */
    print_list(lst1);
    lst1.clear();
    print_list(lst1);

    /**
     * splice
     */
    lst1.push_back(4);
    lst1.push_back(8);
    lst1.push_back(15);
    lst1.push_back(16);

    print_list(lst1);
    print_list(lst5);

    std::list<int>::iterator lst5_it1 = lst5.begin();
    lst5_it1++;
    std::list<int>::iterator lst5_it2 = lst5_it1;
    lst5_it2++;
    lst5_it2++;
    lst5_it2++;
    lst5_it2++;

    lst1.splice(lst1.end(), lst5, lst5_it1, lst5_it2);
    print_list(lst1);
    print_list(lst5);

    lst1_it1 = lst1.begin();
    lst1_it1++;
    lst1_it1++;
    lst1.splice(lst1_it1, lst5);
    print_list(lst1);
    print_list(lst5);

    lst1_it1 = lst1.begin();
    lst1_it1++;
    lst5.splice(lst5.begin(), lst1, lst1_it1);
    print_list(lst1);
    print_list(lst5);

    std::list<int>::const_iterator lst1_const_it1 = lst1.begin();
    lst5.splice(lst5.begin(), lst1, lst1_const_it1);

    print_list(lst1);
    print_list(lst5);

    /**
     * remove
     */
    lst1.remove(42);
    print_list(lst1);

    /**
     * remove_if
     */
    lst1.push_back(57);
    print_list(lst1);
    lst1.remove_if(is_even);
    print_list(lst1);

    /**
     * unique
     */
    print_list(lst4);
    lst4.unique();
    print_list(lst4);

    lst1.push_back(22);
    lst1.push_back(8);
    lst1.push_back(32);
    lst1.push_back(23);
    lst1.push_back(7);
    print_list(lst1);
    lst1.unique(is_both_even_or_odd);
    print_list(lst1);

    /**
     * merge
     */
    lst1.clear();
    lst1.push_back(6);
    lst1.push_back(12);
    lst1.push_back(21);
    lst1.push_back(30);
    lst1.push_back(42);
    print_list(lst1);

    lst5.clear();
    lst5.push_back(3);
    lst5.push_back(15);
    lst5.push_back(45);
    lst5.push_back(50);
    print_list(lst5);

    lst1.merge(lst5);
    print_list(lst1);
    print_list(lst5);

    lst2.clear();
    lst2.push_back("qq");
    lst2.push_back("hello");
    lst2.push_back("bazzinga");
    print_list(lst2);

    lst3.clear();
    lst3.push_back("q");
    lst3.push_back("hi");
    lst3.push_back("school");
    lst3.push_back("poncho");
    print_list(lst3);

    lst2.merge(lst3, isLessLen);
    print_list(lst2);
    print_list(lst3);

    /**
     * sort
     */
    lst1.clear();
    lst1.push_back(15);
    lst1.push_back(4);
    lst1.push_back(8);
    lst1.push_back(16);
    lst1.push_back(42);
    lst1.push_back(23);
    print_list(lst1);

    lst1.sort();
    print_list(lst1);

    print_list(lst2);
    lst2.sort(isFirstLetterLess);
    print_list(lst2);

    /**
     * reverse
     */
    print_list(lst1);
    lst1.reverse();
    print_list(lst1);

    /**
     * get_allocator
     */
    int *array = lst1.get_allocator().allocate(5);
    for (int i = 0; i < 5; i++) {
        array[i] = i * i;
    }
    for (int i = 0; i < 5; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    lst1.get_allocator().deallocate(array, 5);

    /**
     * relational operators
     */
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 == lst5) << std::endl;
    lst5.assign(lst1.begin(), lst1.end());
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 == lst5) << std::endl;
    *(--lst5.end()) = 6;
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 == lst5) << std::endl;

    std::cout << (lst1 != lst5) << std::endl;
    *(--lst5.end()) = 4;
    std::cout << (lst1 != lst5) << std::endl;

    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 < lst5) << std::endl;
    *(--lst5.end()) = 3;
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 < lst5) << std::endl;
    *(--lst5.end()) = 6;
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 < lst5) << std::endl;
    lst5.pop_back();
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 < lst5) << std::endl;
    lst1.pop_back();
    lst1.pop_back();
    print_list(lst1);
    print_list(lst5);
    std::cout << (lst1 < lst5) << std::endl;

    /**
     * swap
     */
    print_list(lst2);
    print_list(lst4);
    swap(lst2, lst4);
    print_list(lst2);
    print_list(lst4);
}

void vector_test() {
    /**
     * empty container constructor (default constructor)
     */
    std::vector<int> vct1;
    print_vector(vct1);

    /**
     * fill constructor
     */
    std::vector<int> vct2(7, 42);
    print_vector(vct2);

    /**
     * range constructor
     */
    std::list<int> lst1;
    lst1.push_back(4);
    lst1.push_back(8);
    lst1.push_back(15);
    lst1.push_back(16);
    lst1.push_back(23);
    lst1.push_back(42);
    print_list(lst1);

    std::vector<int> vct3(lst1.begin(), lst1.end());
    print_vector(vct3);

    std::vector<int> vct4(vct3.begin(), vct3.end());
    print_vector(vct4);

    /**
     * copy constructor
     */
    std::vector<int> vct5(vct4);
    print_vector(vct5);

    /**
     * assignment operator
     */
    vct5 = vct2;
    print_vector(vct5);


    /**
     * reverse iterators
     */
    print_vector(vct4);
    print_vector_reverse(vct4);

    /**
     * size, max_size
     */
    print_vector(vct2);
    std::cout << vct2.size() << " " << vct2.max_size() << std::endl;
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.max_size() << std::endl;

    /**
     * resize, capacity
     */
    print_vector(vct2);
    std::cout << vct2.size() << " " << vct2.capacity() << std::endl;
    vct2.resize(3);
    print_vector(vct2);
    std::cout << vct2.size() << " " << vct2.capacity() << std::endl;
    vct2.resize(12, 21);
    print_vector(vct2);
    std::cout << vct2.size() << " " << vct2.capacity() << std::endl;

    /**
     * empty
     */
    std::cout << vct1.empty() << std::endl;
    std::cout << vct2.empty() << std::endl;

    /**
     * reserve
     */
    std::cout << vct1.capacity() << std::endl;
    vct1.reserve(5);
    std::cout << vct1.capacity() << std::endl;
    vct1.reserve(3);
    std::cout << vct1.capacity() << std::endl;

   /**
    * operator[]
    */
   print_vector(vct3);
   vct3[3] = 777;
   std::cout << vct3[0] << " " << vct3[3] << " " << vct3[5] << std::endl;
   const std::vector<int> vct6(vct3);
//   vct6[3] = 22;
   std::cout << vct3[0] << " " << vct3[3] << " " << vct3[5] << std::endl;

    /**
     * at
     */
    print_vector(vct3);
    try {
        std::cout << vct3.at(1) << std::endl;
        std::cout << vct3.at(7) << std::endl;
    } catch (std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }

    /**
     * front, back
     */
    print_vector(vct2);
    vct2.front() = 777;
    print_vector(vct2);
    std::cout << vct2.front() << std::endl;

    const std::vector<int> vct7(vct2);
    print_vector(vct7);
//    vct7.back() = 55;
    std::cout << vct7.back() << std::endl;

    /**
     * assign
     */
    print_vector(vct2);
    print_vector(vct3);
    vct2.assign(vct3.begin() + 2, vct3.end() - 1);
    print_vector(vct2);
    std::cout << vct2.size() << std::endl;
    vct2.assign(6, 9);
    print_vector(vct2);
    std::cout << vct2.size() << std::endl;

    /**
     * push_back
     */
    print_vector(vct2);
    std::cout << vct2.size() << std::endl;
    vct2.push_back(42);
    print_vector(vct2);
    std::cout << vct2.size() << std::endl;

    /**
     * pop_back
     */
    print_vector(vct4);
    vct4.pop_back();
    print_vector(vct4);

    /**
     * insert
     */
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;

    vct3.insert(vct3.begin() + 3, 45);
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;

    vct3.insert(vct3.begin() + 5, 6, 1);
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;

    print_list(lst1);
    vct3.insert(vct3.begin() + 3, lst1.begin(), lst1.end());
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;

    /**
     * erase
     */
    print_vector(vct3);
    std::cout << vct3.size() << std::endl;
    std::cout << *vct3.erase(vct3.end() - 9) << std::endl;
    print_vector(vct3);
    std::cout << vct3.size() << std::endl;

    std::cout << *vct3.erase(vct3.begin() + 5, vct3.end() - 2) << std::endl;
    print_vector(vct3);
    std::cout << vct3.size() << std::endl;

    /**
     * swap
     */
    print_vector(vct2);
    std::cout << vct2.size() << " " << vct2.capacity() << std::endl;
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;
    vct2.swap(vct3);
    print_vector(vct2);
    std::cout << vct2.size() << " " << vct2.capacity() << std::endl;
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;

    /**
     * clear
     */
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;
    vct3.clear();
    print_vector(vct3);
    std::cout << vct3.size() << " " << vct3.capacity() << std::endl;

    /**
     * relational operators
     */
    std::cout << (vct1 == vct2) << std::endl;
    vct1.assign(vct3.begin(), vct3.end());
    std::cout << (vct1 == vct2) << std::endl;
    vct1.assign(vct2.begin(), vct2.end());
    std::cout << (vct1 == vct2) << std::endl;

    print_vector(vct1);
    print_vector(vct2);
    std::cout << (vct1 != vct2) << std::endl;
    std::cout << (vct1 > vct2) << std::endl;
    *vct2.begin() = 2;
    print_vector(vct1);
    print_vector(vct2);
    std::cout << (vct1 > vct2) << std::endl;
    *vct2.begin() = 4;
    *(vct1.begin() + 1) = 5;
    print_vector(vct1);
    print_vector(vct2);
    std::cout << (vct1 > vct2) << std::endl;

    /**
     * swap
     */
    print_vector(vct1);
    print_vector(vct4);
    std::swap(vct1, vct4);
    print_vector(vct1);
    print_vector(vct4);
}

void map_test() {
    /**
     * Default constructor
     */
    std::map<int, std::string> mp1;

    int         keys[] = {42, 5, 5, 16, 8, 42};
    std::string values[] = {"hello", "i'm", "glad", "to", "see", "you"};
    std::pair< std::map<int, std::string>::const_iterator, bool > ins_res;
    for (int i = 0; i < 6; i++) {
        ins_res = mp1.insert(std::make_pair(keys[i], values[i]));
        if (ins_res.second)
            std::cout << "inserted: " << "(" << ins_res.first->first << ": " << ins_res.first->second << ")" << std::endl;
        else
            std::cout << "not inserted: " << "(" << ins_res.first->first << ": " << ins_res.first->second << ")" << std::endl;
    }
    print_map(mp1);

    /**
     * Range constructor
     */
    std::vector< std::pair<int, std::string> > vct;
    vct.push_back(std::make_pair(4, "hello"));
    vct.push_back(std::make_pair(7, "how"));
    vct.push_back(std::make_pair(4, "you"));
    vct.push_back(std::make_pair(3, "are"));
    vct.push_back(std::make_pair(6, "doing"));

    std::map<int, std::string> mp2(vct.begin(), vct.end());
    print_map(mp2);

    /**
     * Copy constructor
     */
    std::map<int, std::string> mp3(mp2);
    print_map(mp3);

    /**
     * Copy container content
     */
    std::map<int, std::string> mp4 = mp3;
    print_map(mp4);

    /**
     * empty
     */
    print_map(mp4);
    std::cout << mp4.empty() << std::endl;

    mp4.clear();

    print_map(mp4);
    std::cout << mp4.empty() << std::endl;

    /**
     * size
     */
    print_map(mp1);
    std::cout << mp1.size() << std::endl;
    print_map(mp3);
    std::cout << mp3.size() << std::endl;
    print_map(mp4);
    std::cout << mp4.size() << std::endl;

    /**
     * max_size
     */
    std::cout << mp1.max_size() << std::endl;
    std::cout << mp2.max_size() << std::endl;
    std::cout << mp3.max_size() << std::endl;

    /**
     * operator[]
     */
    print_map(mp1);
    std::cout << mp1.size() << std::endl;

    mp1[16] = "whooooa!";
    print_map(mp1);
    std::cout << mp1.size() << std::endl;

    mp1[777] = "nichesebe";
    print_map(mp1);
    std::cout << mp1.size() << std::endl;

    /**
     * insert
     */
    print_map(mp1);
    std::cout << mp1.size() << std::endl;

    mp1.insert(std::make_pair(30, "i see you"));
    print_map(mp1);
    std::cout << mp1.size() << std::endl;

    mp1.insert(vct.begin(), vct.end());
    print_map(mp1);
    std::cout << mp1.size() << std::endl;

    /**
     * erase
     */
    print_map(mp1);

    mp1.erase(mp1.begin());
    print_map(mp1);

    mp1.erase(16);
    print_map(mp1);

    mp1.erase(mp1.find(6), mp1.find(30));
    print_map(mp1);

    /**
     * swap
     */
    print_map(mp1);
    print_map(mp2);
    mp1.swap(mp2);
    print_map(mp1);
    print_map(mp2);

    mp2.insert(std::make_pair(10, "gigigigi"));
    print_map(mp1);
    print_map(mp2);

    /**
     * clear
     */
    print_map(mp1);
    mp1.clear();
    print_map(mp1);
    mp1.insert(vct.begin() + 1, vct.end() - 1);
    print_map(mp1);

    /**
     * Find
     */
    int fkeys[] = {3, 135, 4, 30};
    std::map<int, std::string>::const_iterator fi;
    for (int i = 0; i < 4; i++) {
        fi = mp1.find(fkeys[i]);
        if (fi != mp1.end())
            std::cout << "(" << fi->first << ": " << fi->second << ")" << std::endl;
        else
            std::cout << "Element not found" << std::endl;
    }

    /**
     * Reverse iterator
     */
    print_map(mp1);
    print_map_reverse(mp1);

    /**
     * count
     */
    std::cout << mp1.count(4) << std::endl;
    std::cout << mp1.count(42) << std::endl;

    /**
     * lower_bound
     */
    std::map<char, int> mp5;
    mp5['b'] = 20;
    mp5['d'] = 40;
    mp5['f'] = 60;
    mp5['g'] = 80;
    mp5['j'] = 100;
    print_map(mp5);

    std::map<char, int>::iterator it = mp5.lower_bound('e');
    if (it == mp5.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "(" << it->first << ": " << it->second << ")" << std::endl;

    it = mp5.lower_bound('f');
    if (it == mp5.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "(" << it->first << ": " << it->second << ")" << std::endl;

    it = mp5.lower_bound('k');
    if (it == mp5.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "(" << it->first << ": " << it->second << ")" << std::endl;

    /**
     * upper_bound
     */
    it = mp5.upper_bound('d');
    if (it == mp5.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "(" << it->first << ": " << it->second << ")" << std::endl;

    it = mp5.upper_bound('j');
    if (it == mp5.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "(" << it->first << ": " << it->second << ")" << std::endl;

    /**
     * equal_range
     */
    print_map(mp2);
    std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator> p = mp2.equal_range(5);
    std::map<int, std::string>::const_iterator it1;
    for (it1 = p.first; it1 != p.second; it1++) {
        std::cout << "(" << it1->first << ": " << it1->second << ")" << std::endl;
    }

    p = mp2.equal_range(40);
    for (it1 = p.first; it1 != p.second; it1++) {
        std::cout << "(" << it1->first << ": " << it1->second << ")" << std::endl;
    }
}

void stack_test() {
    /**
     * Constructor, insert
     */
    std::stack<int> st;
    st.push(4);
    st.push(8);
    st.push(15);
    st.push(16);
    st.push(23);
    st.push(42);
    print_stack(st);

    /**
     * empty, size
     */
    std::cout << st.empty() << " " << st.size() << std::endl;

    /**
     * front, pop
     */
    st.pop();
    print_stack(st);
    std::cout << st.empty() << " " << st.size() << std::endl;

    st.pop();
    st.pop();
    st.pop();
    st.pop();
    st.pop();
    print_stack(st);
    std::cout << st.empty() << " " << st.size() << std::endl;

    /**
     * relational operators
     */
    st.push(4);
    st.push(8);

    std::stack<int> st1(st);

    std::cout << (st == st1) << std::endl;
    std::cout << (st != st1) << std::endl;

    st1.push(42);
    print_stack(st);
    print_stack(st1);

    std::cout << (st == st1) << std::endl;
    std::cout << (st != st1) << std::endl;
    std::cout << (st > st1) << std::endl;
    std::cout << (st < st1) << std::endl;
}

void set_test() {
    /**
     * Default constructor
     */
    std::set<float> st1;
    print_set(st1);

    /**
     * Range constructor
     */
    std::vector<float> vct;
    vct.push_back(4.2);
    vct.push_back(8.006);
    vct.push_back(3.34);
    vct.push_back(5.47);
    vct.push_back(2.11);

    std::set<float> st2(vct.begin(), vct.end());
    print_set(st2);

    /**
     * Copy constructor
     */
    std::set<float> st3(st2);
    print_set(st3);

    /**
     * Copy container content
     */
    st1.insert(42);
    st1.insert(665.4);
    st1.insert(3.2);
    print_set(st1);
    st1 = st2;
    print_set(st1);

    /**
     * iterators
     */
    print_set(st3);
    print_set_reverse(st3);

    /**
     * empty, size
     */
    print_set(st3);
    std::cout << st3.empty() << " " << st3.size() << std::endl;

    st3.insert(42);
    print_set(st3);
    std::cout << st3.empty() << " " << st3.size() << std::endl;

    std::cout << st3.erase(4.2) << std::endl;
    std::cout << st3.erase(555) << std::endl;
    print_set(st3);
    std::cout << st3.empty() << " " << st3.size() << std::endl;

    st3.erase(++st3.begin());
    print_set(st3);
    std::cout << st3.empty() << " " << st3.size() << std::endl;

    st3.clear();
    print_set(st3);
    std::cout << st3.empty() << " " << st3.size() << std::endl;

    /**
     * max_size
     */
    std::cout << st1.max_size() << std::endl;

    /**
     * insert
     */
    std::vector<float> vct1;
    vct1.push_back(1.1);
    vct1.push_back(2.2);
    vct1.push_back(3.34);
    vct1.push_back(3.3);
    vct1.push_back(4.4);
    vct1.push_back(5.5);

    print_set(st1);
    st1.insert(vct1.begin() + 1, vct1.end() - 1);
    print_set(st1);

    /**
     * erase
     */
    print_set(st1);
    st1.erase(4.4);
    print_set(st1);
    st1.erase(++st1.begin(), --st1.end());
    print_set(st1);

    /**
     * swap
     */
    print_set(st1);
    print_set(st2);
    st1.swap(st2);
    print_set(st1);
    print_set(st2);

    /**
     * find, count
     */
    std::set<float>::iterator it;
    it = st1.find(4.2);
    std::cout << *it << std::endl;
    std::cout << st1.count(4.2) << std::endl;

    it = st1.find(42);
    if (it == st1.end())
        std::cout << "Not found" << std::endl;
    std::cout << st1.count(42) << std::endl;

    /**
     * equal range
     */
    std::pair<std::set<float>::iterator, std::set<float>::iterator> range;
    range = st1.equal_range(5.47);
    for (std::set<float>::iterator it1 = range.first; it1 != range.second; it1++) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl;

    range = st1.equal_range(547);
    for (std::set<float>::iterator it1 = range.first; it1 != range.second; it1++) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl;

}

int main() {
    std::cout << "====== LIST ======" << std::endl;
    list_test();

    std::cout << std::endl << "====== VECTOR ======" << std::endl;
    vector_test();

    std::cout << std::endl << "====== MAP ======" << std::endl;
    map_test();

    std::cout << std::endl << "====== STACK ======" << std::endl;
    stack_test();

    std::cout << std::endl << "====== SET ======" << std::endl;
    set_test();

//    while (1);
    return (0);
}
