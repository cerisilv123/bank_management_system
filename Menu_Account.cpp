
#include "Menu_Account.hpp"
#include "Account.hpp"
#include <iostream>

void Menu_Account::show_menu() {
    std::cout << "1 - Add Account Record" << std::endl;
    std::cout << "2 - Show all Account Records" << std::endl;
    std::cout << "3 - Search For an Account Record" << std::endl;
    std::cout << "4 - Edit Account Record" << std::endl;
    std::cout << "5 - Delete Account Record" << std::endl;
    std::cout << "6 - Deposit Money to Account" << std::endl;
    std::cout << "7 - Withdraw Money from Account" << std::endl;
    std::cout << "8 - Exit Program" << std::endl;
}

void Menu_Account::choose_selection() {
    Account obj;
    int selection {};
    
    do {
        show_menu();
        std::cout << std::endl;
        std::cout << "Enter a selection: ";
        std::cin >> selection;
        
        if (selection == 1)
            obj.add_record();
        if (selection == 2)
            obj.show_all_records();
        if (selection == 3)
            obj.search_record();
        if (selection == 4)
            obj.edit_record(); 
        if (selection == 5)
            obj.delete_record();
        if (selection == 6)
            obj.deposit_record();
        if (selection == 7)
            obj.withdraw_record();
                
    } while (selection != 8);
    
}
