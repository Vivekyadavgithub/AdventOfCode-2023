#include <iostream>
#include <string>
#include <ranges>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <numeric>
void count_TotalCards(std::vector<int>& card_values)
{
    std::vector<int64_t> count(card_values.size(), 1);
    for(int i = 0 ; i < card_values.size() ; i++){
        int loop = count[i];
        while(loop--){
            for(int j = i + 1; j <= i + card_values[i] &&
                j < card_values.size(); j++){
                count[j]++;
            }
        }
    }
    std::cout << std::accumulate(count.begin(), count.end(), 0);
}
int main()
{
    std::fstream input("input.txt");
    std::string line;
    
    int64_t ans = 0;
    std::vector<int> card_values;
    while (std::getline(input, line)) {
        line = line.substr(line.find(": ") + 2);
        std::unordered_set<std::string> mp;
        bool sec_half = false;
        int64_t card_matches = 0;
        for(const auto& numbers : line | std::views::split(std::string("|")))
        {
            for(const auto& num : numbers | std::views::split(std::string(" ")))
            {
                std::string num_str = "";
                for(auto it : num){
                    num_str += it;
                }
                if(num_str.empty()) continue;
                if(sec_half && mp.contains(num_str)){
                        card_matches++;
                }
                else mp.insert(num_str);
            }
            sec_half = true;
        }
        card_values.push_back(card_matches);
    }
    count_TotalCards(card_values); 
}