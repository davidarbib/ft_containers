#!/usr/bin/zsh
clang++ -Wall -Wextra -Werror -std=c++98 -o ft main.cpp -Iincludes -DFT
clang++ -Wall -Wextra -Werror -std=c++98 -o std main.cpp -Iincludes
chmod 755 ft
chmod 755 std
./ft > "mine"
./std > "true"
diff "true" mine
