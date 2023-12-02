#include <cctype>
#include <iostream>
#include <fstream>
#include <ranges>

auto digit = [](const char c) { return std::isdigit(c); };
auto toInt = [](const char c) { return static_cast<int>(c - '0'); };

int main() {
    std::string s = "123456";
    auto digits = s | std::views::transform([](char c){return int(c - '0');});
    std::cout << digits;
}