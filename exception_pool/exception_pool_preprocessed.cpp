// ... Includes

void foo(int a, int b) {
  std::cout << a << " " << b << std::endl;
}

int main(int, char**) {
  try {
    throw std::string("");
  } catch (std::logic_error e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  } catch (std::runtime_error e) {
    foo(1, 2);
  } catch (std::string const & e) {
    foo(1, 2);
  } catch(std::out_of_range const & e) {
    std::cerr << e.what() << std::endl;
  }
}
