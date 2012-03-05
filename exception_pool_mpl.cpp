#include <iostream>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
 
template <typename exception_pool, bool empty>
struct exception_in_impl { };
 
template <typename exc>
struct exception_in_impl<exc, false> {
  static void apply() {
    try {
      throw;
    } catch(typename boost::mpl::front<exc>::type const & e) {
      // Ignore exception : do *NOT* rethrow
    } catch(...) {
      typedef typename boost::mpl::pop_front<exc>::type next;
      typedef typename boost::mpl::empty<next>::type empty;
      exception_in_impl<next, empty::value>::apply();
    }
  }
};
 
template <typename exc>
struct exception_in_impl<exc, true> {
  static void apply() {
    throw;
  }
};
 
template <typename exc>
void exception_in() {
  typedef typename boost::mpl::empty<exc>::type empty;
  exception_in_impl<exc, empty::value>::apply();
}

#define try_pool_macro(z, n, data) { try
#define try_pool(n)                                     \
  try                                                   \
  BOOST_PP_REPEAT(BOOST_PP_DEC(n), try_pool_macro, ())

#define catch_pool(...)                                 \
  catch (...) {                                         \
    exception_in<__VA_ARGS__>();                        \
    do

#define catch_sth(name, ...)                            \
  catch (__VA_ARGS__ name) {                            \
    do

#define catch_other_pool(...)                           \
  catch_end()                                           \
  catch_pool(__VA_ARGS__)

#define catch_other_sth(name, ...)                      \
  catch_end()                                           \
  catch_sth(name, __VA_ARGS__)

#define catch_all_other()                               \
  catch_end()                                           \
  catch (...)

#define catch_end()                                     \
    while (false);                                      \
  } }

///////////
// USAGE //
///////////

#include <stdexcept>
#include <iostream>
#include <string>

struct some_exception { };

struct some_type { };

int main() {
  some_type some_var;

  try_pool(2) {
    throw std::string();
  } catch_pool(boost::mpl::vector<std::string>) {
    std::cerr << "std::string caught" << std::endl;
  } catch_all_other() {
    std::cerr << "Something else caught" << std::endl;
  }

  try_pool(2) {
    throw std::logic_error("");
  } catch_pool(boost::mpl::vector<std::string>) {
    std::cerr << "std::string caught" << std::endl;
  } catch_all_other() {
    std::cerr << "Something else caught" << std::endl;
  }

  try_pool(3) {
    throw std::string();
  } catch_pool(boost::mpl::vector<std::string>) {
    std::cerr << "std::string caught" << std::endl;
  } catch_other_pool(boost::mpl::vector<std::logic_error, std::runtime_error>) {
    std::cerr << "std::[logic|runtime]_error caught" << std::endl;
  } catch_all_other() {
    std::cerr << "Something else caught" << std::endl;
  }

  try_pool(3) {
    throw std::logic_error("");
  } catch_pool(boost::mpl::vector<std::string>) {
    std::cerr << "std::string caught" << std::endl;
  } catch_other_pool(boost::mpl::vector<std::logic_error, std::runtime_error>) {
    std::cerr << "std::[logic|runtime]_error caught" << std::endl;
  } catch_all_other() {
    std::cerr << "Something else caught" << std::endl;
  }

  try_pool(3) {
    throw some_exception();
  } catch_pool(boost::mpl::vector<std::string>) {
    std::cerr << "std::string caught" << std::endl;
  } catch_other_pool(boost::mpl::vector<std::logic_error, std::runtime_error>) {
    std::cerr << "std::[logic|runtime]_error caught" << std::endl;
  } catch_all_other() {
    std::cerr << "Something else caught" << std::endl;
  }

  try_pool(5) {
    throw some_var;
  } catch_sth(e, some_exception const &) {
    std::cout << "some_exception caught" << std::endl;
  } catch_other_pool(boost::mpl::vector<std::string>) {
    std::cerr << "std::string caught" << std::endl;
  } catch_other_sth(e, std::exception) {
    std::cerr << "std::exception caught" << std::endl;
  } catch_other_pool(boost::mpl::vector<std::logic_error, std::runtime_error>) {
    std::cerr << "std::[logic|runtime]_error caught" << std::endl;
  } catch_all_other() {
    std::cerr << "Something else caught" << std::endl;
  }
}

