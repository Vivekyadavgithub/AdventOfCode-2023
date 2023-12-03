#include <iostream>
#include <fstream>
#include <ranges>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

int main() {
    std::ifstream input("input.txt");
    int64_t ans = 0;
    std::vector<std::unordered_set<int>> symbols;
    std::vector<std::unordered_map<int, std::string>> values;
    for (const auto& line : std::views::istream<std::string>(input)) {
        std::string digitstr = "";
        std::unordered_map<int, std::string> value;
        std::unordered_set<int> symbol;
        for(int i = 0; i < line.size(); i++) {
            if(isdigit(line[i])){
                for(int j = i; ; j++){
                    digitstr += line[j];
                    if((j + 1) == line.size() || !isdigit(line[j + 1])){
                        value.insert({i, digitstr});
                        i = j;
                        break;
                    }
                }
                digitstr = "";
            } else if (line[i] != '.') {
                symbol.insert(i);
            }
        }
        symbols.push_back(symbol);
        values.push_back(value);   
    }
    auto bfs = [&symbols](int point, int level) -> bool {
        if(symbols[level].contains(point + 1) || symbols[level].contains(point - 1)) return true;
        
        auto cornerCase = [&](int pos) {  
            if(symbols[level + pos].contains(point) || symbols[level + pos].contains(point + 1) 
                || symbols[level + pos].contains(point - 1)) return true;
            return false;
        };

        if(level == symbols.size() - 1) { if (cornerCase(-1)) return true; }
        else if(level == 0)             { if (cornerCase(1)) return true; }
        else                            { if(cornerCase(-1) || cornerCase(1)) return true; }
        return false;
    };

    for (int i = 0 ; i < values.size(); i++) {
        for(const auto& it : values[i]){

            auto [st_index, val] = it;
            int end_index = st_index + (val.size() - 1);
            
            if(bfs(st_index, i) || bfs(end_index, i)){
                ans += stoi(val);
            } 
        }
    }
    std::cout << ans << "\n"; 
}