#include <iostream>
#include <fstream>
#include <string>
#include <ranges>


int32_t main() {
    
    auto toInt = [](const char c) { return static_cast<int>(c - '0'); };

    std::ifstream input("input1.txt");
    int64_t ans = 0;
    for (const auto& line : std::views::istream<std::string>(input))
	{
		std::string digits = "";
		for(const auto &it : line){
			if(isdigit(it)){
				digits += it;
			}
		}
		if(digits.size() == 0) continue;
		ans +=  toInt(digits.front()) * 10 + toInt(digits.back());
	}
	std::cout << ans << "\n";
}