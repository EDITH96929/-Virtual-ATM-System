#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define PIN_LENGTH 4

// Structure Definitions
typedef struct {
    int id;
    char name[50];
    char pin[PIN_LENGTH + 1];
    float balance;
} User;

// Global Variables
User users[MAX_USERS];
int userCount = 0;

// Function Prototypes
void createAccount();
void login();
void displayMenu(User* user);
void checkBalance(User* user);
void depositMoney(User* user);
void withdrawMoney(User* user);
void transferMoney(User* user);

// Main Function
int main() {
    int choice;

    while (1) {
        printf("\nVirtual ATM System\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                printf("Thank you for using the Virtual ATM System. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Create Account Function
void createAccount() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot create more accounts.\n");
        return;
    }

    User newUser;
    newUser.id = userCount + 1;

    printf("Enter your name: ");
    getchar();
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';

    printf("Set a 4-digit PIN: ");
    scanf("%4s", newUser.pin);

    newUser.balance = 0.0;

    users[userCount++] = newUser;

    printf("Account created successfully! Your User ID is %d.\n", newUser.id);
}

// Login Function
void login() {
    int userID;
    char enteredPIN[PIN_LENGTH + 1];

    printf("Enter your User ID: ");
    scanf("%d", &userID);

    if (userID <= 0 || userID > userCount) {
        printf("Invalid User ID.\n");
        return;
    }

    User* user = &users[userID - 1];

    printf("Enter your PIN: ");
    scanf("%4s", enteredPIN);

    if (strcmp(user->pin, enteredPIN) == 0) {
        printf("Login successful. Welcome, %s!\n", user->name);
        displayMenu(user);
    } else {
        printf("Invalid PIN. Please try again.\n");
    }
}

// Display Menu Function
void displayMenu(User* user) {
    int choice;

    while (1) {
        printf("\nATM Menu\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(user);
                break;
            case 2:
                depositMoney(user);
                break;
            case 3:
                withdrawMoney(user);
                break;
            case 4:
                transferMoney(user);
                break;
            case 5:
                printf("Logging out. Goodbye, %s!\n", user->name);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Check Balance Function
void checkBalance(User* user) {
    printf("Your current balance is: %.2f\n", user->balance);
}

// Deposit Money Function
void depositMoney(User* user) {
    float amount;
    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Please try again.\n");
        return;
    }

    user->balance += amount;
    printf("%.2f has been deposited to your account.\n", amount);
}

// Withdraw Money Function
void withdrawMoney(User* user) {
    float amount;
    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > user->balance) {
        printf("Invalid amount. Please try again.\n");
        return;
    }

    user->balance -= amount;
    printf("%.2f has been withdrawn from your account.\n", amount);
}

// Transfer Money Function
void transferMoney(User* user) {
    int recipientID;
    float amount;

    printf("Enter the recipient's User ID: ");
    scanf("%d", &recipientID);

    if (recipientID <= 0 || recipientID > userCount || recipientID == user->id) {
        printf("Invalid User ID.\n");
        return;
    }

    User* recipient = &users[recipientID - 1];

    printf("Enter the amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > user->balance) {
        printf("Invalid amount. Please try again.\n");
        return;
    }

    user->balance -= amount;
    recipient->balance += amount;

    printf("%.2f has been transferred to %s (User ID: %d).\n", amount, recipient->name, recipient->id);
}
