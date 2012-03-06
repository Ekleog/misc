// Exception pool management
// Copyright (C) 2012  Leo "Ekleog" Gaspard <ekle removethis og at gmail dot com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
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
