#include <cassert>
#include <cstdint>

#include <iostream>
#include <sstream>
#include <string>

std::string digit2fr(unsigned char digit) {
    static const std::string numbers[] = {
        "zero", "un" , "deux", "trois", "quatre",
        "cinq", "six", "sept", "huit" , "neuf"
    };
    assert(digit < 10);
    return numbers[digit];
}

std::string ten2fr(unsigned char nb) {
    static const std::string numbers[] = {
        "dix", "onze", "douze", "treize",
        "quatorze", "quinze", "seize"
    };
    assert(nb < 20);
    if (nb < 10)      return digit2fr(nb);
    else if (nb < 17) return numbers[nb - 10];
    else              return "dix-" + digit2fr(nb - 10);
}

std::string ty2fr(unsigned char nb) {
    static const std::string numbers[] = {
        "vingt", "trente", "quarante", "cinquante", "soixante",
        "soixante-dix", "quatre-vingt", "quatre-vingt-dix"
    };
    assert(nb < 100);
    if (nb < 20)                  return ten2fr(nb);
    else if (nb == 71)            return "soixante-et-onze";
    else if (71 < nb && nb < 80)  return "soixante-" + ten2fr(nb - 60);
    else if (nb == 80)            return "quatre-vingts";
    else if (nb == 81)            return "quatre-vingt-un";
    else if (90 < nb && nb < 100) return "quatre-vingt-" + ten2fr(nb - 80);
    else if (nb % 10 == 1)        return numbers[nb / 10 - 2] + "-et-un";
    else if (nb % 10 != 0)        return numbers[nb / 10 - 2] + "-" + ten2fr(nb % 10);
    else                          return numbers[nb / 10 - 2];
}

std::string num2fr(std::intmax_t num) {
    std::string ret;
    std::uintmax_t nb;
    if (num < 0) {
        ret += "moins ";
        nb = -num;
    } else {
        nb = num;
    }
    auto numname = [&ret, &nb](unsigned long long Nb, const std::string & Lt) {
        if (nb / Nb >= 1) {
            if (nb / Nb == 80) {
                ret += "quatre-vingt-";
            } else {
                ret += num2fr(nb / Nb) + "-";
            }
            if (nb / Nb == 1) {
                ret += Lt + "-";
            } else {
                ret += Lt + "s-";
            }
            nb %= Nb;
        }
    };
    //numname(1000000000000000000000, "trilliard"); // Bigger than biggest possible integer
    numname(1000000000000000000, "trillion");
    numname(1000000000000000, "billiard");
    numname(1000000000000, "billion");
    numname(1000000000, "milliard");
    numname(1000000, "million");
    if (nb / 1000 >= 1) {
        if (nb / 1000 == 80) {
            ret += "quatre-vingt-";
        } else if (nb / 1000 > 1) {
            ret += num2fr(nb / 1000) + "-";
        }
        ret += "mille-";
        nb %= 1000;
    }
    if (nb / 100 >= 1) {
        if (nb / 100 == 1) {
            ret += "cent-";
        } else {
            if (nb % 100 != 0) {
                ret += ten2fr(nb / 100) + "-cent-";
            } else {
                ret += ten2fr(nb / 100) + "-cents-";
            }
        }
        nb %= 100;
    }
    if (nb > 0 || ret.empty()) {
        ret += ty2fr(nb);
    } else {
        ret.resize(ret.size() - 1);
    }
    return ret;
}

std::string usage(const std::string & arg) {
    return "Usage : " + arg + " NOMBRE";
}
int fail(const std::string & msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
}
int main(int argc, char** argv) {
    if (argc <= 1) return fail(usage(argv[0]));

    std::intmax_t nb;
    std::istringstream iss(argv[1]);
    iss >> nb;

    if (iss.fail()) return fail(usage(argv[0]));
    if (!iss.eof()) return fail(usage(argv[0]));
    if ( iss.bad()) return fail("Erreur inconnue");

    std::cout << num2fr(nb) << std::endl;

    return EXIT_SUCCESS;
}

