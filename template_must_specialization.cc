// g++ -std=c++14 template_must_specify.cc
// view compile errors

// variable template since c++14
// an alternative is use class template contains static value, like as std::integral_constant.
template <class Cls>
constexpr bool FalseValue = false;

template <class Cls>
struct MustSpec {
    static_assert(false, "this class template must specialize"); // compile error, must be a false depends template param `Cls`
    static_assert(FalseValue<Cls>, "this class template must specialize"); // compile pass
};

template <>
struct MustSpec<int> {
};

int main() {
    MustSpec<int>   a;              // compile pass
    MustSpec<float> b;              // compile error, trigger static_assert
    using type1 = MustSpec<float>;  // compile pass
    type1 c;                           // compile error, trigger static_assert
}
