
#ifndef Account_hpp
#define Account_hpp

#include <stdio.h>

void display_header(); 

class Account {
private:
    double AccId;
    char FirstName [20];
    char LastName [30];
    long double amount {0};
public:
    // Helper Methods
    double return_id();
    void deposit(const long double &total);
    void withdraw(const long double &total);
    // Main Methods
    void add_record(); 
    void show_account_details();
    void show_all_records();
    void search_record();
    void edit_record();
    void delete_record();
    void deposit_record();
    void withdraw_record(); 
};

#endif /* Account_hpp */
