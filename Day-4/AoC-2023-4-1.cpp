#include <iostream>
#include <string>
#include <ranges>
#include <fstream>
#include <unordered_set>

int main()
{
    std::fstream input("input.txt");
    std::string line;
    
    int64_t ans = 0;
    while (std::getline(input, line)) {
        line = line.substr(line.find(": ") + 2);
        std::unordered_set<std::string> mp;
        bool sec_half = false;
        int64_t card_val = 0;
        for(const auto& numbers : line | std::views::split(std::string("|")))
        {
            for(const auto& num : numbers | std::views::split(std::string(" ")))
            {
                std::string num_str;
                for(auto it : num){
                    num_str += it;
                }
                if(num_str.empty()) continue;
                if(sec_half){
                    if(mp.contains(num_str)){
                        card_val *= 2;
                        
                        if(card_val == 0) card_val += 1;
                    }
                }
                else mp.insert(num_str);
            }
            sec_half = true;
        }
        ans += card_val;
    }
    std::cout << ans << "\n";
}