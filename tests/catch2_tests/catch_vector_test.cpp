#include "include/catch.hpp"

#include "vector.hpp"
#include "map.hpp"
#include <map>
#include <vector>

namespace ft {
	template <typename T>
	bool operator==(const ft::vector<T>& my_v, const std::vector<T>& stl_v)
	{
		typename ft::vector<T>::const_iterator my_iter_start = my_v.begin();
		typename ft::vector<T>::const_iterator my_iter_end = my_v.end();
		typename std::vector<T>::const_iterator stl_iter_start = stl_v.begin();
		typename std::vector<T>::const_iterator stl_iter_end = stl_v.end();
		if (my_v.size() != stl_v.size() || my_v.capacity() != stl_v.capacity())
			return false;
		while (my_iter_start != my_iter_end && stl_iter_start != stl_iter_end)
		{
			if (*my_iter_start != *stl_iter_start)
			{
				return false;
			}
			my_iter_start++;
			stl_iter_start++;
		}
		return true;
	}

	template <typename T1,typename T2>
	bool operator==(const std::map<T1,T2>& stl_v, const ft::map<T1,T2>& my_v)
	{
		return my_v == stl_v;
	}

	template <typename T1,typename T2>
	bool operator!=(const std::map<T1,T2>& stl_v, const ft::map<T1,T2>& my_v)
	{
		return !(stl_v == my_v);
	}

	template <typename T1,typename T2>
	bool operator!=(const ft::map<T1,T2>& my_v, const std::map<T1,T2>& stl_v)
	{
		return !(my_v == stl_v);
	}
}

TEST_CASE("Creating an integers container", "[integers]") // [] - is a tag used to select which tests to run
{
        ft::vector<int> my_v;
        std::vector<int> stl_v;

        CHECK(my_v == stl_v);
        int int_arr[] = { 1, 2, 3, 4, 5, 6, 7, 100, 101, 102, 103, 104, 12, 13, 14, 89};
        size_t arr_size = sizeof(int_arr)/ sizeof(int_arr[0]);
        int int_arr1[] = { -200,-201, -202, -203, -204, -205, -206, -207, -208};
        size_t arr_size1 = sizeof(int_arr1)/ sizeof(int_arr1[0]);

    SECTION("Inserting one element: size is 1, capacity is 1, element is inserted")
    {
        my_v.insert(my_v.begin(), 30);
        stl_v.insert(stl_v.begin(), 30);
        CHECK(my_v.empty() == stl_v.empty());
        CHECK(my_v.size() == stl_v.size());
        CHECK(my_v.front() == stl_v.front());
        CHECK(my_v == stl_v);
    }
    SECTION("Filling the vector with assign(fill)")
    {      
        my_v.assign(100, 3);
        stl_v.assign(100, 3);
        CHECK(my_v == stl_v);
        CHECK(my_v.size() == 100);
        size_t size = my_v.size();

        SECTION("Assign ints range: previous values are destroyed, size changed")
        {
            my_v.assign(int_arr, int_arr + arr_size);
            stl_v.assign(int_arr, int_arr + arr_size);
            CHECK(my_v == stl_v);
            CHECK(my_v.size() != size);

            SECTION("Element access check")
            {
                CHECK(my_v.at(4) == stl_v.at(4));
                CHECK(my_v.front() == stl_v.front());
                CHECK(my_v.back() == stl_v.back());
                // CHECK(*(my_v.data()) == *(stl_v.data())); // c++11
                CHECK(my_v[6] ==7);

            }
            SECTION("Iterators check")
            {
                ft::vector<int>::iterator my_it = my_v.begin();
                std::vector<int>::iterator stl_it  = stl_v.begin();
                CHECK(*my_it == *stl_it);
                my_it++;
                stl_it++;
                CHECK(*my_it == *stl_it);
                ft::vector<int>::iterator my_it_end = my_v.end();
                std::vector<int>::iterator stl_it_end  = stl_v.end();
                CHECK(*(my_it_end - 1) == *(stl_it_end - 1));
                ft::vector<int>::reverse_iterator my_rev_it = my_v.rbegin();
                std::vector<int>::reverse_iterator stl_rev_it  = stl_v.rbegin();

            SECTION("Insert(fill): n elements(second arg) of the value(last argument) are added  to the position(first argument)")
            {
                my_v.insert(my_v.begin() + 5, 10, 30);
                stl_v.insert(stl_v.begin() + 5, 10, 30);
                CHECK(my_v.empty() == stl_v.empty());
                CHECK(my_v.size() == stl_v.size());
                CHECK(my_v.front() == stl_v.front());
                CHECK(my_v == stl_v);
            }
            SECTION("Inserting a range of elements: elements pointed by two iterators are inserted to the position(first argument)")
            {
                my_v.insert(my_v.begin() + 5, int_arr1, int_arr1 + arr_size1);
                stl_v.insert(stl_v.begin() + 5, int_arr1, int_arr1 + arr_size1);
                CHECK(my_v.empty() == stl_v.empty());
                CHECK(my_v.size() == stl_v.size());
                CHECK(my_v.front() == stl_v.front());
                CHECK(my_v == stl_v);
            }
            }
            SECTION("Reserving less than capacity does nothing")
            {
                size_t capacity_1 = my_v.capacity();
                my_v.reserve(10);
                stl_v.reserve(10);
                CHECK(my_v.capacity() == stl_v.capacity());

                SECTION("Reserving more space than capacity")
                {
                    my_v.reserve(200);
                    stl_v.reserve(200);
                    size_t capacity_2 = my_v.capacity();
                    CHECK(capacity_1 != capacity_2);
                    CHECK(my_v.capacity() == stl_v.capacity());
                }
            }
            SECTION("Creating a copy with copy constructor")
            {
                ft::vector<int> my_copy_v(my_v);
                std::vector<int> stl_copy_v(stl_v);
                CHECK(my_copy_v == stl_copy_v);

                SECTION("Clearing original vectors")
                {
                    my_v.clear();
                    stl_v.clear();
                    CHECK(my_v.size() == stl_v.size());
                }
            }
        }
    }
    SECTION("Creating a container with fill constructor")
    {
        ft::vector<int> my_v(5, 10);
        std::vector<int> stl_v(5, 10);
        CHECK(my_v.empty() == stl_v.empty());
        CHECK(my_v.size() == stl_v.size());
        CHECK(my_v.max_size() == stl_v.max_size());
        CHECK(my_v.capacity() == stl_v.capacity());
        CHECK(my_v.size() == 5);
    }

    SECTION("Creating a container with the range constructor")
    {
        int intArray[] = { 1, 2, 9, 10, 11, 12, 13, 14, 20, 28, 40, 9000, -9000, -4, -1000000000};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        CHECK(my_v.empty() == stl_v.empty());
        CHECK(my_v.size() == stl_v.size());
        CHECK(my_v.max_size() == stl_v.max_size());
        CHECK(my_v.capacity() == stl_v.capacity());
    }
}

TEST_CASE("Reserve() method", "[integers]")
{
    SECTION("Checking capacity after reserve")
    {
        ft::vector<int> my_v(5, 10);
        std::vector<int> stl_v(5,10);
        CHECK(my_v.capacity() == stl_v.capacity());
    }
}

TEST_CASE("Testing erase method", "[integers]")
{
    SECTION("Erasing the last element")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        ft::vector<int>::iterator my_itEnd = my_v.end();
        std::vector<int>::iterator stl_itEnd  = stl_v.end();
        my_v.erase(my_itEnd - 1);
        stl_v.erase(stl_itEnd - 1);
        CHECK(*(my_v.end() - 1) == *(stl_v.end() - 1));
    }
    SECTION("Erasing the first element")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        ft::vector<int>::iterator my_it = my_v.begin();
        std::vector<int>::iterator stl_it  = stl_v.begin();
        my_v.erase(my_it);
        stl_v.erase(stl_it);
        CHECK(*(my_v.begin()) == *(stl_v.begin()));
        CHECK(*(my_v.end() - 1) == *(stl_v.end() - 1));
    }
    SECTION("Erasing the range")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 0, 0, 0, 0, 0, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        ft::vector<int>::iterator my_it = my_v.begin();
        std::vector<int>::iterator stl_it  = stl_v.begin();
        ft::vector<int>::iterator ftReturnedIt =  my_v.erase(my_it + 5, my_it + 10);
        std::vector<int>::iterator stdReturnedIt  = stl_v.erase(stl_it + 5, stl_it + 10);
        CHECK(my_v.size() == stl_v.size());
        CHECK(*(my_v.begin() + 5) == *(stl_v.begin() + 5));
        CHECK(*(my_v.end() - 1) == *(stl_v.end() - 1));
        CHECK(*(ftReturnedIt) == *(stdReturnedIt));
    }
}
TEST_CASE("Resize method", "[integers]")
{
    SECTION("Resize to smaller size")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        ft::vector<int>::iterator my_itEnd = my_v.end();
        std::vector<int>::iterator stl_itEnd  = stl_v.end();
        my_v.resize(3);
        stl_v.resize(3);
        CHECK(my_v.size() == stl_v.size());
        CHECK(*(my_v.begin()) == *(stl_v.begin()));
        CHECK(*(my_v.end() - 1) == *(stl_v.end() - 1));
    }
    SECTION("Resize to larger size")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        my_v.resize(30);
        stl_v.resize(30);
        CHECK(my_v.size() == stl_v.size());
        CHECK(my_v.capacity() == stl_v.capacity());
        CHECK(*(my_v.begin()) == *(stl_v.begin()));
        CHECK(*(my_v.end() - 1) == *(stl_v.end() - 1));
    }
    SECTION("Resize to 0")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);
        my_v.resize(0);
        stl_v.resize(0);
        CHECK(my_v.size() == stl_v.size());
    }
}

TEST_CASE("Swap() method", "[integers]")
{
    SECTION("ft::swap")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);

        ft::vector<int> ftVectorInts1(5, 10);
        std::vector<int> stdVectorInts1(5,10);

        ft::swap(my_v,ftVectorInts1);
        std::swap(stl_v,stdVectorInts1);
        ft::vector<int>::iterator my_it = my_v.begin();
        std::vector<int>::iterator stl_it = stl_v.begin();
        CHECK(*(my_it) == *(stl_it));

    }
    SECTION("ft::vector::swap - member function")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> my_v(intArray, intArray + arraySize);
        std::vector<int> stl_v(intArray, intArray + arraySize);

        ft::vector<int> ftVectorInts1(5, 10);
        std::vector<int> stdVectorInts1(5,10);

        my_v.swap(ftVectorInts1);
        stl_v.swap(stdVectorInts1);

        ft::vector<int>::iterator my_it = my_v.begin();
        std::vector<int>::iterator stl_it = stl_v.begin();

        CHECK(*(my_it) == *(stl_it));
    }
}

TEST_CASE("Creating a complex vector: a vector of pairs", "[string, string]")
{
    std::vector<std::pair<std::string, std::string> > stl_v;
    ft::vector<ft::pair<std::string, std::string> > my_v;

    std::pair<std::string, std::string> s_p1 = std::make_pair("tree", "sycamore");
    ft::pair<std::string, std::string> my_p1 = ft::make_pair("tree", "sycamore");
    std::pair<std::string, std::string> s_p2 = std::make_pair("flower", "rose");
    ft::pair<std::string, std::string> my_p2 = ft::make_pair("flower", "rose");
    std::pair<std::string, std::string> s_p3 = std::make_pair("fruit", "banana");
    ft::pair<std::string, std::string> my_p3 = ft::make_pair("fruit", "banana");
    std::pair<std::string, std::string> s_p4 = std::make_pair("vegetable", "cucumber");
    ft::pair<std::string, std::string> my_p4 = ft::make_pair("vegetable", "cucumber");

    std::map<std::string, std::string> stl_m;
    ft::map<std::string, std::string> my_m;
    stl_m.insert(s_p1);
    my_m.insert(my_p1);
    stl_m.insert(s_p2);
    my_m.insert(my_p2);
    stl_m.insert(s_p3);
    my_m.insert(my_p3);
    stl_m.insert(s_p4);
    my_m.insert(my_p4);

    
    SECTION("Constructing a vector of pairs - map iterators are passed")
    {
        std::vector<std::pair<std::string, std::string> > stl_v1(stl_m.begin(), stl_m.end());
        ft::vector<ft::pair<std::string, std::string> > my_v1(my_m.begin(), my_m.end());
        CHECK(my_v1.size() == stl_v1.size());
        CHECK(my_v1.capacity() == stl_v1.capacity());
        CHECK(my_v1[3].second == stl_v1[3].second);
    }

    SECTION("Pushing back a map pair into a vector several times")
    {

        for (int i = 0; i < 100; ++i) 
        {
            stl_v.push_back(*(stl_m.begin()));
            my_v.push_back(*(my_m.begin()));
        }
        CHECK(my_v.size() == stl_v.size());
        CHECK(my_v.capacity() == stl_v.capacity());
        CHECK(my_v[3].second == stl_v[3].second);

    }

    SECTION("Inserting a range into a vector of pairs - map iterators are passed")
    {
        stl_v.insert(stl_v.begin(), stl_m.begin(), stl_m.end());
        my_v.insert(my_v.begin(), my_m.begin(), my_m.end());
        CHECK(my_v.size() == stl_v.size());
        CHECK(my_v.capacity() == stl_v.capacity());
        CHECK(my_v[my_v.size() - 1].second == stl_v[stl_v.size() - 1].second);
    }
}

TEST_CASE("Comparing vectors", "[small and big containers]")
{
	ft::vector<int> small(4,5);
	ft::vector<int> big(10000, 5);
	CHECK(small != big);
	CHECK(big != small);
	CHECK(big > small);
	CHECK(small < big);
}