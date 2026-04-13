#include <iostream>
#include <string>

size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash = 0;

    for (size_t i = 0; i < s.size(); i++) {
        hash = (hash + s[i]) % max;
    }

    return hash;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash = 0;

    for (size_t i = 0; i < s.size(); i++) {
        hash = (hash + s[i] * (i + 1)) % max;
    }

    return hash;
}

int main() {
    std::string str;
    size_t max = 120;

    std::cout << "Entre un string ! : ";
    std::cin >> str;

    std::cout << "Hash simple : "
              << folding_string_hash(str, max) << std::endl;

    std::cout << "Hash ordonne : "
              << folding_string_ordered_hash(str, max) << std::endl;

    return 0;
}