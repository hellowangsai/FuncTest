// g++ -std=c++14 template_must_specify.cc
// view compile errors

// variable template since c++14
// an alternative is use class template contains static value, like as std::integral_constant.
template <class Cls>
constexpr bool FalseValue = false;

template <class Cls>
struct MustSpecify {
    static_assert(false, "this class template Must Specify"); // compile error, must be a false depends template param `Cls`
    static_assert(FalseValue<Cls>, "this class template Must Specify"); // compile pass
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
