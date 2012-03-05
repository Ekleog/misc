// ...

int main() {
  some_type some_var;

  try {
    try {
      throw std::string();
    } catch (...) {
      exception_in<boost::mpl::vector<std::string> >();
      do {
        std::cerr << "std::string caught" << std::endl;
      } while (false);
    }
  } catch (...) {
    std::cerr << "Something else caught" << std::endl;
  }

  try {
    try {
      throw std::logic_error("");
    } catch (...) {
      exception_in<boost::mpl::vector<std::string> >();
      do {
        std::cerr << "std::string caught" << std::endl;
      } while (false);
    }
  } catch (...) {
    std::cerr << "Something else caught" << std::endl;
  }

  try {
    try {
      try {
        throw std::string();
      } catch (...) { exception_in<boost::mpl::vector<std::string> >();
        do {
          std::cerr << "std::string caught" << std::endl;
        } while (false);
      }
    } catch (...) {
      exception_in<boost::mpl::vector<std::logic_error, std::runtime_error> >();
      do {
        std::cerr << "std::[logic|runtime]_error caught" << std::endl;
      } while (false);
    }
  } catch (...) {
    std::cerr << "Something else caught" << std::endl;
  }

  try {
    try {
      try {
        throw std::logic_error("");
      } catch (...) {
        exception_in<boost::mpl::vector<std::string> >();
        do {
          std::cerr << "std::string caught" << std::endl;
        } while (false);
      }
    } catch (...) {
      exception_in<boost::mpl::vector<std::logic_error, std::runtime_error> >();
      do {
        std::cerr << "std::[logic|runtime]_error caught" << std::endl;
      } while (false);
    }
  } catch (...) {
    std::cerr << "Something else caught" << std::endl;
  }

  try {
    try {
      try {
        throw some_exception();
      } catch (...) {
        exception_in<boost::mpl::vector<std::string> >();
        do {
          std::cerr << "std::string caught" << std::endl;
        } while (false);
      }
    } catch (...) {
      exception_in<boost::mpl::vector<std::logic_error, std::runtime_error> >();
      do {
        std::cerr << "std::[logic|runtime]_error caught" << std::endl;
      } while (false);
    }
  } catch (...) {
    std::cerr << "Something else caught" << std::endl;
  }

  try {
    try {
      try {
        try {
          try {
            throw some_var;
          } catch (some_exception const & e) {
            do {
              std::cout << "some_exception caught" << std::endl;
            } while (false);
          }
        } catch (...) {
          exception_in<boost::mpl::vector<std::string> >();
          do {
            std::cerr << "std::string caught" << std::endl;
          } while (false);
        }
      } catch (std::exception e) {
        do {
          std::cerr << "std::exception caught" << std::endl;
        } while (false);
      }
    } catch (...) {
      exception_in<boost::mpl::vector<std::logic_error, std::runtime_error> >();
      do {
        std::cerr << "std::[logic|runtime]_error caught" << std::endl;
      } while (false);
    }
  } catch (...) {
    std::cerr << "Something else caught" << std::endl;
  }
}
