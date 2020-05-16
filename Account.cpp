
#include "Account.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

// Helper Method to display header
void display_header() {
    std::cout << std::endl;
    int  width_account {25}, width_name {25}, width_balance {20};
    std::cout << std::setw(width_account) << std::left << "Account Number";
    std::cout << std::setw(width_name) << std::left << "Name";
    std::cout << std::setw(width_balance) << std::right << "£ Balance" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

// Helper Method to return Account ID
double Account::return_id() {
    return AccId; 
}

// Helper Method to add to balance
void Account::deposit(const long double &total) {
    amount += total;
}

// Helper Method to withdraw from balance
void Account::withdraw(const long double &total) {
        amount -= total;
}

// Method to add an Account Record to file
void Account::add_record() {
    int n {};
    bool matching_id = false;
    std::cout << "Enter Account ID: ";
    std::cin >> n;

    std::ifstream in_file; // Checking to see if ID already exists
    in_file.open("Account.txt", std::ios::in | std::ios::binary);
    if (!in_file) {
        std::cerr << "Error accessing file" << std::endl;
    }
    while (in_file.read((char *)this, sizeof(*this))) {
        if (return_id() == n) {
            matching_id = true;
        }
    }
    in_file.close();
    
    if (matching_id == false) {
       AccId = n;
       std::cout << "Enter a first name: ";
       std::cin >> FirstName;
       std::cout << "Enter a second name: ";
       std::cin >> LastName;
       std::cout << "Enter an Amount to deposit: ";
       std::cin >> amount;
       
       std::ofstream out_file;
       out_file.open("Account.txt", std::ios::out | std::ios::app | std::ios::binary);
       if (!out_file) {
           std::cerr << "Error Adding Account to File" << std::endl;
       }
       out_file.write((char*)this, sizeof(*this)); // Adding an Account object to file
       out_file.close();
    }
    else {
        std::cout << "An Account with that ID already exsits" << std::endl;
    }
    std::cout << std::endl;
    return;
}

// Method to show Account details
void Account::show_account_details() {
    double width_account {25}, width_first_name {7.5}, width_last_name {22.5}, width_balance {15};
    std::cout << std::setw(width_account) << std::left << std::fixed << std::setprecision(0) << AccId;
    std::cout << std::setw(width_first_name) << std::left << FirstName << " "
              << std::setw(width_last_name) << std::left << LastName;
    std::cout << std::setw(width_balance) << std::right << std::fixed << std::setprecision(2) << amount << std::endl;
}

// Method to show all records
void Account::show_all_records() {
    std::ifstream in_file {"Account.txt", std::ios::in | std::ios::binary};
    if (!in_file) {
        std::cerr << "Error acessing file" << std::endl;
    }
    display_header();
    while (in_file) {
        if(in_file.read((char *)this, sizeof(*this))) { // Reading all account objects to console
            show_account_details();
        }
    }
    
    in_file.close();
    std::cout << std::endl;
}

// Method to search for a specific record
void Account::search_record() {
    std::cout << std::endl;
    int n {};
    std::cout << "Enter an account number to search for: ";
    std::cin >> n;
    
    std::ifstream in_file {"Account.txt", std::ios::in | std::ios::binary};
    if (!in_file) {
        std::cerr << "Error acessing file" << std::endl;
    }
    
    while (in_file.read((char *)this,  sizeof(*this))) {
        if (return_id() == n) { // Searching for the correct id in the file
            display_header();
            show_account_details();
        }
    }
    in_file.close();
    std::cout << std::endl;
}

// Method to delete a record on file
void Account::delete_record() {
    std::cout << std::endl;
    int n {};
    
    std::string selection;
    std::cout << "Enter an account number for the record you'd like to delete: ";
    
    std::cin >> n;
    
    std::cout << "Are you sure you'd like to delete this file? Y/N ";
    std::cin >> selection;
    
    if (selection == "Y" || selection == "y") {
    
       std::ifstream in_file;
       std::ofstream out_file;
    
       in_file.open ("Account.txt", std::ios::in | std::ios::binary);
       out_file.open("Temp.txt", std::ios::out | std::ios::binary);
       if (!in_file || !out_file) {
           std::cerr << "Error accessing file" << std::endl;
       }
       while (in_file.read((char*)this, sizeof(*this))) {
           if (return_id() != n) {
              out_file.write((char*)this, sizeof(*this));
           }
       }
       remove("Account.txt");
       rename("Temp.txt", "Account.txt");
       in_file.close();
       out_file.close();
        
    }
    std::cout << "The account on file has been deleted" << std::endl;
    std::cout << std::endl; 
}

// Method to edit details of an Account
void Account::edit_record() {
    std::cout << std::endl;
    std::ifstream in_file;
    std::ofstream out_file;
    int n;
    bool found {false};
    std::string selection {};
    std::cout << "Enter the account ID you'd like to edit: ";
    std::cin >> n;
    
    in_file.open("Account.txt", std::ios::binary | std::ios::in);
    if (!in_file) {
        std::cerr << "Error accessing file" << std::endl;
    }
    while (in_file.read((char*)this, sizeof(*this))) { // Checking if the Account is found on file first
        if (return_id() == n) {
            found = true;
        }
    }
    in_file.close(); 
    
    if (found == true) {
       std::cout << "Are you sure you'd like to edit this file? Y/N ";
       std::cin >> selection;
        
       if (selection == "Y" || selection == "y") {
          in_file.open("Account.txt", std::ios::binary | std::ios::in);
          out_file.open("Temp.txt", std::ios::binary | std::ios::out); // Writing accounts != n on to Temp file
          if (!in_file || !out_file){
              std::cerr << "Error accessing file" << std::endl;
          }
          while(in_file.read((char*)this, sizeof(*this))) {
              if (return_id() != n) {
                  out_file.write((char*)this, sizeof(*this));
              }
          }
       remove("Account.txt");
       rename("Temp.txt", "Account.txt"); // Making Temp file Account file
       in_file.close();
       out_file.close();
      }
       std::cout << std::endl;
    }
    else {
        std::cout << "\nFile not found" << std::endl;
        std::cout << std::endl;
    }
    
    std::cout << "\nEnter the new details " << std::endl;
    add_record(); // Adding new Account to the new file
}

// Method to deposit money to a record
void Account::deposit_record() {
    std::ifstream in_file;
    std::ofstream out_file;
    double n{};
    long double total {};
    std::cout << "Enter the account ID you'd like to deposit money to: ";
    std::cin >> n;
    std::cout << "Enter the amount you'd like to deposit in to the account: ";
    std::cin >> total;
    std::cout << std::endl;
    
    in_file.open("Account.txt", std::ios::binary | std::ios::in);
    out_file.open("Temp.txt", std::ios::binary | std::ios::out);
    if (!in_file || !out_file) {
        std::cerr << " Error in accessing file" << std::endl;
    }
    while (in_file.read((char *)this, sizeof (*this))) {
        if (return_id() == n) {
            deposit(total);
            out_file.write((char *)this, sizeof(*this));
        }
        else {
            out_file.write((char *)this, sizeof(*this));
        }
    }
    remove("Account.txt");
    rename("Temp.txt", "Account.txt");
    in_file.close();
    out_file.close();
}

// Method to withdraw money from an Account
void Account::withdraw_record() {
    std::ifstream in_file;
    std::ofstream out_file;
    double n{};
    double total {};
    std::cout << "Enter the account ID you'd like to withdraw money from: ";
    std::cin >> n;
    std::cout << "Enter the amount you'd like to withdraw from the account: ";
    std::cin >> total;
    std::cout << std::endl;
    
    in_file.open("Account.txt", std::ios::binary | std::ios::in);
    out_file.open("Temp.txt", std::ios::binary | std::ios::out);
    if (!in_file || !out_file) {
        std::cerr << " Error in accessing file" << std::endl;
    }
    while (in_file.read((char *)this, sizeof (*this))) {
        if (return_id() == n && total < amount) {
            withdraw(total);
            out_file.write((char *)this, sizeof(*this));
            std::cout << total << " withdrawn from account "
                      << std::fixed << std::setprecision(0) << n << std::endl;
        }
        else if (return_id() == n && total > amount) {
            out_file.write((char *)this, sizeof(*this));
            std::cout << "Insufficient Funds to withdraw " << total  << " from acccount "
                      << std::fixed << std::setprecision(0) << n << std::endl;
        }
        else {
            out_file.write((char *)this, sizeof(*this));
        }
        std::cout << std::endl;
    }
    remove("Account.txt");
    rename("Temp.txt", "Account.txt");
    in_file.close();
    out_file.close();
}

