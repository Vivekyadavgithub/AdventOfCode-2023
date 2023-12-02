#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

const std::vector<std::string> split(std::string str, char del) {
    std::istringstream iss(str);
    std::vector<std::string> res;
    std::string temp;
    while(getline(iss, temp, del)){
        if(temp.empty()) continue;
        res.push_back(temp);
    }
    return res;
}
int main() {

    std::fstream input("input2.txt");
    std::string line;
    int64_t ans = 0, curr_id = 0;

    

    while (std::getline(input, line)) {
        bool isPossible = true;
        std::unordered_map<std::string, int> color_names {
        {"red", 0},{ "blue", 0},{"green", 0}
        };
        curr_id++;
        line = line.substr(line.find(": ") + 2);
        std::vector<std::string> games = split(line, ';');
        for(const auto& game : games) {
            std::vector<std::string> colors = split(game, ',');
            for(const auto& color : colors) {
                std::vector<std::string> data = split(color, ' ');
                int count = stoi(data[0]);
                if(count > color_names[data[1]]){
                    color_names[data[1]] = count;
                }
            }
        }
        int product = 1;
        for(auto [k, v] : color_names) product *= v;
        ans += product;
    }
    std::cout << ans << "\n";
}