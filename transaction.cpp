// Transactions in C++11
// Copyright (C) 2012  Leo Gaspard <ekleog@gmail.com>
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

#include <functional>
#include <vector>

using action_cb   = std::function<void ()>;
using rollback_cb = std::function<void ()>;

struct Transaction {
   action_cb    action;
   rollback_cb  rollback;
   Transaction* next;

   void execute() {
      action();
      if (next) {
         try {
            next->execute();
         } catch (...) {
            rollback();
            throw;
         }
      }
   }
};

void transaction(std::vector<std::pair<action_cb, rollback_cb>> const & actions) {
   // Build transaction array and linked-list
   std::vector<Transaction> transactions(actions.size());
   for (std::size_t i = 0 ; i < actions.size() ; ++i) {
      transactions[i].action   = actions[i].first;
      transactions[i].rollback = actions[i].second;
      transactions[i].next     = &transactions[i + 1];
   }
   // Fix last pointer
   transactions[actions.size() - 1].next = nullptr;
   // Execute
   transactions[0].execute();
}

#include <iostream>

int main() {
   try {
      transaction({
         { [] () { std::cout << "Running transaction\n"; },
           [] () { std::cout << "Rollbacked transaction\n"; }
         },
         { [] () { new int [999999999999999]; std::cout << "Unreachable.\n"; },
           [] () { std::cout << "Should never be called !\n"; }
         }
      });
   } catch (std::exception const & e) {
      std::cerr << "Exception caught : " << e.what() << " ; ignoring...\n";
   }

   std::vector<int> v1, v2, v3;
   transaction({
      { [&v1] () { v1.push_back(1); },
        [&v1] () { v1.pop_back(); }
      },
      { [&v2] () { v2.push_back(2); },
        [&v2] () { v2.pop_back(); }
      },
      { [&v3] () { v3.push_back(3); },
        [&v3] () { v3.pop_back(); }
      }
   });
   // Would likely diserve its own helper, but here the subject are "generic"
   // transactions, not only push_back ones !

   for (int i : v1) std::cout << i << " ";
   for (int i : v2) std::cout << i << " ";
   for (int i : v3) std::cout << i << " ";
   std::cout << "\n";
}
