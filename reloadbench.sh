#!/usr/bin/zsh
clang++ -Wall -Wextra -Werror -std=c++98 -o ft bench_insert_delete_vector.cpp -Iincludes -DFT
clang++ -Wall -Wextra -Werror -std=c++98 -o std bench_insert_delete_vector.cpp -Iincludes
chmod 755 ft
chmod 755 std
./ft > "mine"
./std > "true"
diff "true" mine
