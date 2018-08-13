// std::function has performance cost than lambda. But lambda can only pass as template,
// making the API not clear.
// std::is_convertible can detect whether the lambda meets the signature.

#include<type_traits>
#include<functional>

template <class Func>
void TestF(Func&& f) {
    static_assert(std::is_convertible<Func, std::function<void(int)>>::value, 
                  "input f signature must be void(int)");
}

int main() {
    TestF([]{});       //compile error, trigger static_assert
    TestF([](int){});  //compile pass
}
