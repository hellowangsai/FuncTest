/*
 * g++ -std=c++17 join_serialize_cpp17.cc
 * Use c++17 fold expressions to join serialize variable length basic vars. Need a compiler support c++17 to compile.
 */

#include <iostream>
#include <cstring>
#include <vector>

typedef std::vector<uint8_t> Bytes;

template <typename... Args>
Bytes JoinSerialize(const Args&... args) {
    uint32_t length = (sizeof(args) + ...);
    Bytes bytes(length);
    auto seril_to_data = [data = bytes.data()] (auto&& t) mutable {
        memcpy(data, &t, sizeof(t));
        data += sizeof(t);
    };
    (seril_to_data(args), ...);
    return bytes;
}

template <typename... Args>
bool JoinDeserialize(Bytes bytes, Args*... args) {
    uint32_t total_bytes = (sizeof(std::remove_pointer_t<decltype(args)>) + ...);
    if (bytes.size() != total_bytes) {
        return false;
    }
    auto deseril_from_data = [data = bytes.data()] (auto* t) mutable {
        using T = std::remove_pointer_t<decltype(t)>;
        memcpy(t, data, sizeof(T));
        data += sizeof(T);
    };
    (deseril_from_data(args), ...);
    return true;
}

int main() {
    Bytes s1 = JoinSerialize('1', '2', '3');
    std::cout << std::string((char*)s1.data(), s1.size()) << std::endl;
    Bytes s2 = JoinSerialize(123, '2', 466, '1');
    int v1, v3;
    char v2, v4;
    if (JoinDeserialize(s2, &v1, &v2, &v3, &v4, &v3)){
        std::cout << v1 << " "
                  << v2 << " "
                  << v3 << " "
                  << v4 << std::endl;
    } else {
        std::cout << "Deserialize fail." << std::endl;
    }
}
