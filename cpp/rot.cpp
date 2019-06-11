// RotX cipher
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

#include <cassert>
#include <iostream>
#include <map>
#include <sstream>

#define wchar_t char
#define wcout cout
#define wcin cin

wchar_t splf(wchar_t c) {
#if 0
    std::map<wchar_t, wchar_t> chgs;
    chgs[L'Ŕ'] = L'R'; chgs[L'ŕ'] = L'r';
                       chgs[L'ñ'] = L'n';
                       chgs[L'ǹ'] = L'n';
    auto it = chgs.find(c);
    if (it != chgs.end()) return it->second;
#else
    if (false);
#endif
    else                  return c;
}

wchar_t encr(wchar_t c, int k) {
    c = splf(c);
         if (c > 0xFF)        return c;                          // Non-ASCII Character ? Return
         if (std::isupper(c)) return ((c - 'A') + k) % 26 + 'A'; // Upper ASCII ? Crypt
    else if (std::islower(c)) return ((c - 'a') + k) % 26 + 'a'; // Lower ASCII ? Crypt
    else                      return c;                          // Non-letter ASCII ? Return
}

int main(int argc, char** argv) {
    assert(argc > 0);
    std::istringstream iss(argv[1]);
    int k;
    iss >> k;
    wchar_t c;
    while (std::wcin.good()) {
        c = std::wcin.get();
        std::wcout.put(encr(c, k));
    }
    return 0;
}

