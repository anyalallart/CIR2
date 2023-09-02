//
// Created by Administrateur on 27/09/2022.
//
#include<cstdlib>
#include <algorithm>

typedef float my_type;

class My_vector{
private:
    size_t size;
    my_type* tab;
public:
    My_vector();
    explicit My_vector(const size_t &size);
    My_vector(const My_vector &vector);
    ~My_vector();
    const size_t &get_size() const;
    void set_an_element(const size_t &index,const my_type &val);
    const my_type &get_an_element(const size_t &index) const;
    void push(const my_type &val);
};
