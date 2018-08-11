template <class Cls>
struct False {
    static constexpr bool value = false;
};

template <class Cls>
struct MustSpecify {
    static_assert(false, "this class template Must Specify"); // compile error, must be a false depends template param `Cls`
    static_assert(False<Cls>::value, "this class template Must Specify"); // compile pass
};

template <>
struct MustSpecify<int> {
};

int main() {
    MustSpecify<int>   a;              // compile pass
    MustSpecify<float> b;              // compile error, trigger static_assert
    using type1 = MustSpecify<float>;  // compile pass
    type1 c;                           // compile error, trigger static_assert
}
