# Bank Theft Detection System
A C++ console application simulating a bank security alert system
using Object-Oriented Programming principles.

## Features
- Real-time intrusion trigger logic
- Alert system activation on unauthorized access
- OOP-based modular design
- Inheritance and polymorphism implementation
- Encapsulation of security logic


## Tech Stack
![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white)

## Concepts Applied
- Object-Oriented Programming (OOP)
- Inheritance
- Polymorphism
- Encapsulation
- Abstraction
- Security Logic Design


## Files
- BTDS(project).cpp — Full source code

## How It Works
- Menu-driven console interface
- Login with PIN — locks after 3 failed attempts
- Withdrawal checks: amount, location, and time rules
- Custom FraudException class for all security alerts

## Sample Output
=== Bank Theft Detection System (BTDS) ===

Account Holder: Aina
Balance: 90000

Login
Withdraw (simulate transaction)
Show Account Info
Exit

## OOP Concepts Demonstrated
- Inheritance: Account → SavingAccount → HighSecurityAccount
- Polymorphism: virtual withdraw() and showInfo()
- Encapsulation: private balance and PIN
- Exception Handling: custom FraudException class
- Function Overloading: SecurityEngine detect() method
- Static member: Account::totalAccounts

## Academic Context
Developed as part of BSCS coursework at Muhammad Ali Jinnah
University (MAJU), Karachi — Semester 2, OOP course.

---
*Fatima Zehra | BSCS @ MAJU Karachi*
