#include <iostream>
#include <fstream>
#include <ranges>
#include <vector>
#include <utility>
#include <algorithm>
int main() {
    std::ifstream input("input.txt");
    int64_t ans = 0;
    std::vector<std::vector<char>> mat;
    std::vector<std::vector<int>> symbols;
    for (const auto& line : std::views::istream<std::string>(input)) {
        std::vector<char> arr;
        std::vector<int> symbol;
        for(int i = 0 ; i < line.size(); i++) {
            if(isdigit(line[i]))
                arr.push_back(line[i]);
            else arr.push_back('.');

            if(line[i] == '*') symbol.push_back(i);
        }
        mat.push_back(arr);
        symbols.push_back(symbol);
    }
    
    auto bfs = [&mat](int r, int c) -> int {
        std::vector<std::vector<bool>> vis(mat.size(), std::vector<bool>(mat[0].size(), false));
        std::vector<int> neighbour{};

        auto getString = [&mat, &vis](int r, int c) -> int {
            vis[r][c] = true;
            std::string temp = "";
            for(int i = c; i >= 0; i--){
                if(isdigit(mat[r][i])){
                    vis[r][i] = true;
                    temp += mat[r][i];
                } else break;

            }
            std::reverse(temp.begin(), temp.end());
            for(int i = c + 1; i < mat[r].size(); i++){
                if(isdigit(mat[r][i])){
                    vis[r][i] = true;
                    temp += mat[r][i];
                } else break;                
            }
            return stoi(temp);


        };

        auto pos_ok = [&mat, &r, &c](int row, int col){
            row += r;
            col += c;
            if(row < 0 || row >= mat.size()) return false;
            if(col < 0 || col >= mat[0].size()) return false;
            return true;
        };
        vis[r][c] = true;
        if(pos_ok(1,1) && !vis[r + 1][c + 1] && isdigit(mat[r + 1][c + 1])){
                neighbour.push_back(getString(r + 1,c + 1));
        }
        //std::cout << r << "      " << c << "\n";

        if(pos_ok(1,0) && !vis[r + 1][c] && isdigit(mat[r + 1][c])){
                neighbour.push_back(getString(r + 1, c));
        }
        if(pos_ok(1,-1) && !vis[r + 1][c - 1] && isdigit(mat[r + 1][c - 1])){
                neighbour.push_back(getString(r + 1,c - 1));
        }
        if(pos_ok(0,-1) && !vis[r ][c - 1] && isdigit(mat[r][c - 1])){
                neighbour.push_back(getString(r,c - 1));
        }
        if(pos_ok(0,1) && !vis[r][c + 1] && isdigit(mat[r][c + 1])){
                neighbour.push_back(getString(r,c  + 1));
        }
        if(pos_ok(-1,0) && !vis[r - 1][c] && isdigit(mat[r - 1][c])){
                neighbour.push_back(getString(r - 1,c));
        }
        if(pos_ok(-1,-1) && !vis[r - 1][c - 1] && isdigit(mat[r - 1][c - 1])){
                neighbour.push_back(getString(r - 1, c - 1));
        }
        if(pos_ok(-1,1) && !vis[r - 1][c + 1] && isdigit(mat[r - 1][c + 1])){
                neighbour.push_back(getString(r - 1,c + 1));
        }
        if(neighbour.size() == 2) return neighbour[0] * neighbour[1];
        return 0;
        
        
    };

    for(int i = 0 ; i < symbols.size(); i++) {
        for(int j = 0 ; j < symbols[i].size(); j++) {
            //std::cout << "first ===   "<<i << " " << symbols[i][j] << "\n";
            if(bfs(i, symbols[i][j])) std::cout << i << " " << symbols[i][j]<< " " << bfs(i, symbols[i][j]) << "\n";
            ans += bfs(i, symbols[i][j]); 
        }
    }    
    std::cout << ans << "\n";
}