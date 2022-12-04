#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdint.h>

struct Range
{
    public:
        int min;
        int max;
        Range(int _min, int _max) : min(_min), max(_max){};
        bool contains(Range other)
        {
            return other.min >= this->min && other.max <= this->max;
        }
        bool overlaps(Range other)
        {
            return this->min <= other.max && other.min <= this->max;
        }
};

int main()
{
    int encapsulates = 0;
    int overlaps = 0;
    
    // Open the file
    std::ifstream in("input.txt");
    if(!in)
    {
        std::cerr << "There was an error opening the input file." << std::endl;
        return 1;
    }
    std::string str;

    while(std::getline(in, str))
    {
        std::vector<Range> result;
        std::stringstream range(str);
        while(getline(range, str, ','))
        {
            std::size_t location = str.find('-');
            std::string first = str.substr(0, location);
            std::string second = str.substr(++location);

            result.push_back(Range(stoi(first), stoi(second)));
        }

        encapsulates += result[0].contains(result[1]) | result[1].contains(result[0]);
        overlaps += result[0].overlaps(result[1]);
    }

    in.close();
    std::cout << "Count of encapsulating pairs: " << encapsulates << std::endl;
    std::cout << "Count of overlapping pairs: " << overlaps << std::endl;
    return 0;
}