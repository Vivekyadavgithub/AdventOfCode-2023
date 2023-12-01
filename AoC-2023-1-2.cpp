#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <ranges>
#include <iterator>

int main()
{
    auto toInt = [](const char c) { return static_cast<int>(c - '0'); };

    std::unordered_map<std::string, int> word_to_dec {
         {"one",   1}, {"two",   2}, {"three", 3},
         {"four",  4}, {"five",  5}, {"six",   6},
         {"seven", 7}, {"eight", 8}, {"nine",  9} 
    };

    std::ifstream input("input1.txt");
    int64_t ans = 0;
    for (const auto& line : std::views::istream<std::string>(input)) {
        std::string digits = "";
        for(const auto& it : line) {
            if(isdigit(it)) {
                digits += it;
            }
            else {
                for(int len = 3; len <= 5; len++){
                    int index = &it - line.data();
                    if(index >= line.size()) break;
                    const std::string sub = line.substr(index, len);
                    if(word_to_dec.contains(sub)) {
                        digits += word_to_dec[sub] + '0';
                    }
                }
            }
        }
        if(digits.size() == 0) continue;
        ans +=  toInt(digits.front()) * 10 + toInt(digits.back());
    }
    std::cout << ans << "\n";
}