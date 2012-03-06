#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

//{{{ catch_pool
#define catch_pool(name, pool, ...)                                           \
  BOOST_PP_REPEAT(                                                            \
    BOOST_PP_TUPLE_SIZE(pool),                                                \
    catch_pool_macro,                                                         \
    (name, (__VA_ARGS__), BOOST_PP_TUPLE_TO_SEQ(pool))                        \
  )
#define catch_pool_macro(z, n, data)                                          \
    catch (                                                                   \
      BOOST_PP_SEQ_ELEM(n, catch_pool_macro_type(data))                       \
      catch_pool_macro_name(data)                                             \
    ) {                                                                       \
      BOOST_PP_TUPLE_ELEM(1, 0, catch_pool_macro_code(data))                  \
    }
#define catch_pool_macro_name(data) BOOST_PP_TUPLE_ELEM(3, 0, data)
#define catch_pool_macro_code(data) BOOST_PP_TUPLE_ELEM(3, 1, data)
#define catch_pool_macro_type(data) BOOST_PP_TUPLE_ELEM(3, 2, data)
//}}}

///////////
// USAGE //
///////////

#include <iostream>
#include <stdexcept>
#include <string>

void foo(int a, int b) {
  std::cout << a << " " << b << std::endl;
}

int main(int, char**) {
  try {
    throw std::string("");
  } catch_pool(e, (std::logic_error, std::exception &),
    std::cerr << e.what() << std::endl;
  ) catch_pool(e, (std::runtime_error, std::string const &),
    foo(1, 2);
  ) catch(std::out_of_range const & e) {
    std::cerr << e.what() << std::endl;
  }
}
