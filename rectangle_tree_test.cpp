#include "RectangleTree.h"

#include <string>

template <typename T>
void print_vector(const std::vector<T>& v) {
    for(typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << "    " << *it << " (" << *(it->value) << ")" << std::endl;
}

int main()
{
    typedef Rectangle<std::string*> rect;
    std::string a = "a", b = "b", c = "c", d = "d", e = "e";
    std::vector<rect> rectangles;
    rectangles.push_back(rect(2,4,8,10,&a));
    rectangles.push_back(rect(6,11,6,12,&b));
    rectangles.push_back(rect(9,13,4,8,&c));
    rectangles.push_back(rect(10,12,11,14,&d));
    rectangles.push_back(rect(10,12,2,7,&e));
    std::cout << "input:" << std::endl;
    print_vector(rectangles);
    RectangleTree<std::string*> rt(rectangles);

    std::vector<rect> r1;
    rt.findOverlapping(11,11,6,6,r1);
    std::cout << "result for query overlapping(11,11,6,6):" << std::endl;
    print_vector(r1);

    std::vector<rect> r2;
    rt.findContained(8,14,1,11,r2);
    std::cout << "result for query contained(8,14,1,11):" << std::endl;
    print_vector(r2);

    return 0;
}

