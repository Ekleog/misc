// Named variables registry
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

////////////////
// DEFINITION //
////////////////
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

/// RegisterEntry
///
/// A class to model a varible pointer to any type.
///
/// It is up to the user to determine to which type it points to.
///
/// It will raise an error when trying to access it if in an invalid
/// state.
/// You may avoid this exception by checking if the entry is valid()
/// before using as<T>().
///
/// Its only publicly-used methods should be valid() and as<T>().
class RegisterEntry {
    private:
        void * ptr_;
    public:
        RegisterEntry();
        bool valid() const;
        template <typename T>
            explicit RegisterEntry(T & val);
        template <typename T>
            T & as();
};

/// Register
///
/// The class storing all the Name-Entry pairs.
/// It is implemented as a stack, to allow redefining new variables with
/// the same name. (e.g. recursive functions)
///
/// Its only publicly-used method should be get().
class Register {
    private:
        typedef std::stack<RegisterEntry> Stack_;
        typedef std::map<std::string, Stack_> Map_;
        typedef Map_::iterator It_;

        Map_ map_;
    public:
        void         push(std::string const & name, RegisterEntry var);
        void          pop(std::string const & name);
        RegisterEntry get(std::string const & name);
};

/// getGlobalRegister()
///
/// Returns an unique static register.
/// It is the one selected by default when creating a Registered<T>, if
/// none is explicitly specified.
Register & getGlobalRegister();

/// Registered<T>
///
/// Models a registered variables.
///
/// Usage :
///  * Use special constructor : Registered<MyType>("VarName", MyValue)
///    It adds the variable name.
///    The MyValue will be selected as the value of the Registered<MyType>.
///  * Use as a normal variable of type MyType
///  * Access from the specified register (or the global register) at any time !
///  * Use name() if ever you didn't remember the variable name
///    I didn't find yet any interesting usage of this, but maybe could it get
///    useful ... So I wrote it !
template <typename T>
class Registered {
    private:
        Register * reg_;
        std::string name_;
        T val_;
    public:
        Registered(std::string const & name, T const & val,
                   Register & reg = getGlobalRegister());
        ~Registered();
        Registered<T> & operator = (T const & val);
        operator T       & ()      ;
        operator T const & () const;
        std::string const & name() const;
};

/// InvalidRegisterEntryException
///
/// Exception raised when somebody tries to access a register entry (using
/// as<T>) that is not a valid one.
///
/// It is likely to happen if the variable name asked to the register
/// doesn't exist.
class InvalidRegisterEntryException : public std::runtime_error {
    public:
        InvalidRegisterEntryException();
};

////////////////////
// IMPLEMENTATION //
////////////////////
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

RegisterEntry::RegisterEntry()
    : ptr_(0)
{ }
bool RegisterEntry::valid() const {
    return ptr_ != 0;
}
template <typename T>
RegisterEntry::RegisterEntry(T & val)
    : ptr_(static_cast<void *>(&val))
{ }
template <typename T>
T & RegisterEntry::as() {
    if (!valid()) throw InvalidRegisterEntryException();
    return *static_cast<Registered<T> *>(ptr_);
}

void Register::push(std::string const & name, RegisterEntry var) {
    std::pair<It_, bool> inserted = map_.insert(std::make_pair(name, Stack_()));
    inserted.first->second.push(var);
}
void Register::pop(std::string const & name) {
    It_ it = map_.find(name);
    it->second.pop();
    if (it->second.empty()) {
        map_.erase(it);
    }
}
RegisterEntry Register::get(std::string const & name) {
    It_ it = map_.find(name);
    if (it == map_.end()) {
        return RegisterEntry();
    } else {
        return it->second.top();
    }
}

Register & getGlobalRegister() {
    static Register reg;
    return reg;
}

template <typename T>
Registered<T>::Registered(std::string const & name, T const & val, Register & reg)
    : reg_(&reg), name_(name), val_(val) {
    reg_->push(name_, RegisterEntry(*this));
}
template <typename T>
Registered<T>::~Registered() {
    reg_->pop(name_);
}
template <typename T>
Registered<T> & Registered<T>::operator = (T const & val) {
    val_ = val;
}
template <typename T>
Registered<T>::operator T & () {
    return val_;
}
template <typename T>
Registered<T>::operator T const & () const {
    return val_;
}
template <typename T>
std::string const & Registered<T>::name() const {
    return name_;
}

InvalidRegisterEntryException::InvalidRegisterEntryException()
    : std::runtime_error("Trying to access an invalid register entry.")
{ }

///////////////////
// EXAMPLE USAGE //
///////////////////
#include <iostream>

int main(int, char**) {
    Registered<int> i1("i1", 0), i2("i2", 2);
    i1 = 1;
    std::string var;
    std::cout << "Recap' : i1 = " << i1 << " ; i2 = " << i2 << std::endl;

    std::cout << "Which one to set to 3 ? (i1 / i2) ";
    std::cin >> var;
    getGlobalRegister().get(var).as<int>() = 3;

    std::cout << "Which one to increment ? (i1 / i2) ";
    std::cin >> var;
    getGlobalRegister().get(var).as<int>()++;

    std::cout << "Which one to display ? (i1 / i2) ";
    std::cin >> var;
    std::cout << var << " = " << getGlobalRegister().get(var).as<int>() << std::endl; 

    std::cout << "Recap' : i1 = " << i1 << " ; i2 = " << i2 << std::endl;
}
