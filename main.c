//this helps check if a character is an alphabet
#include <ctype.h>
//C standard library functions
#include <stdio.h>
//give access to system functions like cls to clear the screen
#include <stdlib.h>
//string functions like strcpy, strlen
#include <string.h>
//includes C standard library functions like time and date functions
#include <time.h>

// Program Constants that can be used inside any Function
#define MIN_PLUGGING_AGE 18
#define MAX_PLUGGING_AGE 100
#define DISCOUNT_PERCENTAGE 0.20f // this means 20%
#define MAX_SALES 53
#define MENU_OPTION_VIEW_CAR_STOCK 1
#define MENU_OPTION_BUY_CARS 2
#define MENU_OPTION_VIEW_SALES_DATA 3
#define MENU_OPTION_CUSTOMER_FEEDBACKS 4
#define MENU_OPTION_EXIT 5

// I defined the Car and Sale structures here
typedef struct {
    char model[50];
    unsigned short year;
    unsigned int price;
    unsigned short stock;
} Car;

typedef struct {
    char customer_name[50];
    unsigned short customer_age;
    unsigned int total_price;
    unsigned short discount;
    unsigned int num_cars;
    char date[50];
    char feedback[255];
    unsigned short rating;
    char car_model[50];
} Sale;

// Initialize the cars and sales arrays
Car cars[] = {
    {"300CE", 1995, 500000, 5},
    {"C63s", 2015, 70000, 7},
    {"G63s", 2024, 200000, 2},
    {"SLS", 2014, 250000, 9},
    {"SL73", 1995, 280000, 6},
    {"E63s", 2023, 150000, 4},
    {"E55", 2005, 200000, 7},
    {"GTs", 2021, 300000, 8},
    {"E53", 2025, 90000, 5}
};


Sale sales[100];  // Array to store sales data
int num_sales = 0;  // Number of sales made

// Fuction to display the welcome message
void welcome_message() {
    printf("\n");
    printf("\n");
    printf("=======================================================\n");
    printf("                Welcome to Benz Plug!\n");
    printf("       Your No.1 Dealership for Mercedes Benz:)\n");
    printf("     We are here to help you plug into the future!\n");
    printf("=======================================================\n");
}

// Function to clear the screen
void clear_screen() {
    // this tells the Command Prompt (i.e. the System's output mechanism)
    // to do something to clear the screen/console
    // this is purely for the user's benefit, to keep the screen clear of clutter
    system("cls");
}

// Function to print a new line
void new_line() {
    printf("\n");
}

// function to check if a string only contains alphabets
int is_alpha_string(char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {  // Allow spaces in the name
            return 0;  // Return false if a non-alphabet character is found
        }
    }
    return 1;  // Return true if all characters are alphabet characters
}

// Function to display the car stock
void display_stock() {
    int i, j;
    int n = sizeof(cars) / sizeof(cars[0]);  // Get the number of cars

    // Bubble sort
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (cars[j].year < cars[j+1].year) {
                Car temp = cars[j];
                cars[j] = cars[j+1];
                cars[j+1] = temp;
            }
        }
    }

    new_line();
    printf("              CAR STOCK         \n");
    printf("_____________________________________\n");
    // Display the car stock
    printf("Index\tModel\tYear\tPrice\tStock\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\n", i, cars[i].model, cars[i].year, cars[i].price, cars[i].stock);
    }
    printf("_____________________________________\n");
    new_line();
}

// Function to display the menu
void show_menu() {
    // present the various actions the user can choose from
    printf("\n");
    printf("Menu:\n");
    printf("%d. View Cars Stock\n", MENU_OPTION_VIEW_CAR_STOCK);
    printf("%d. Buy Cars\n", MENU_OPTION_BUY_CARS);
    printf("%d. View Sales Data\n", MENU_OPTION_VIEW_SALES_DATA);
    printf("%d. Customer Feedbacks\n", MENU_OPTION_CUSTOMER_FEEDBACKS);
    printf("%d. Exit\n\n", MENU_OPTION_EXIT);
}

//Fuction to clear the buffer
void clear_buffer() {
    while (getchar() != '\n');
}

// Function to display the exit message
void menu_exit() {
    // this is a custom message to the user
    // it is always good to give the user a warm message when they are about to exit
    printf("\n\nThank you for visiting Benz Plug!\n");
    printf("We hope to see you again soon!\n");
}

// Function to handle the buy car process
void buy_car() {
    unsigned short car_index, quantity, with_plug;
    char customer_name[50];
    unsigned short customer_age;
    char date[50];
    unsigned short rating;
    char comment[255];


    // This will loop until a valid car index is entered
    while (1) {
        printf("Enter car index: ");
        int result = scanf("%hu", &car_index);
        clear_buffer();   // Clear the buffer

        // This is to validate car index entered by the user
        if (result == 1 && car_index >= 0 && car_index < sizeof(cars) / sizeof(cars[0])) {
            break;  // If the car index is valid, break the loop
        }

        printf("Invalid car index. Please try again.\n");
    }

    // Print the model and year of the selected car
    printf("_____________________________________\n");
    printf("You selected %d Mercedes Benz %s AMG\n", cars[car_index].year, cars[car_index].model);
    printf("Price: %d GBP\n", cars[car_index].price);
    printf("Stock: %d\n", cars[car_index].stock);
    printf("_____________________________________\n");


    // This is a loop to make sure a valid quantity is entered
    while (1) {
        printf("Enter quantity: ");
        scanf("%hu", &quantity);
        clear_buffer();  // Clear the buffer

        // Validate quantity
        if (quantity > 0 && quantity <= cars[car_index].stock) {
            break;  // If the quantity is valid, break the loop
        }

        printf("Invalid quantity. Please try again.\n");
    }
    new_line();

    // This loop will make sure a valid name containing only alphabets is entered
    while (1) {
        printf("Enter your name: ");
        scanf(" %[^\n]", customer_name);  // Use this to read a line of text
        clear_buffer();  // Clear the buffer

        // Validate name
        if (strlen(customer_name) > 0 && is_alpha_string(customer_name)) {
            break;  // If the name is valid (not empty and only contains alphabets), break the loop
        }

        printf("Invalid name. Please try again.\n");
    }

    // Loop until a valid age is entered
    while (1) {
        printf("Enter your age: ");
        int result = scanf("%hu", &customer_age);
        clear_buffer();  // Clear the buffer

        // check if the age is within the plugging age range
        if (result == 1) {
            if (customer_age < MIN_PLUGGING_AGE) {
                new_line();
                printf("You are below the plugging age:(\n");
                printf("See you when you turn %d :)\n", MIN_PLUGGING_AGE);
                new_line();
                printf("Exiting...........\n");
                return;  // Exit the function if the age is not within the plugging age range
            } else if (customer_age > MAX_PLUGGING_AGE) {
                new_line();
                printf("You are too old to plug:(\n");
                printf("We hope you had a good run!\n");
                new_line();
                printf("Exiting...........\n");
                return;  // Exit the function if the age is not within the plugging age range
            }
            break;  // If the age is valid, break the loop
        }

        printf("Invalid age. Please enter a valid integer.\n");
    }

    // This will get the current date and store it in the date variable
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(date, sizeof(date), "%d/%m/%Y", tm);



    // Loop until a valid response is entered
    while (1) {
        printf("Are you with the plug(1 for yes, 0 for no):");
        int result = scanf("%hu", &with_plug);
        clear_buffer();  // Clear the buffer

        // Validate response (1 for yes, 0 for no)
        if (result == 1 && (with_plug == 0 || with_plug == 1)) {
            break;  // If the response is valid, break the loop
        }

        printf("Invalid response. Please enter 1 for yes or 0 for no.\n");
    }

    // Calculate total price
    int total_price = cars[car_index].price * quantity;

    // Apply discount if customer is with the plug
    if (with_plug == 1) {
        total_price *= (1 - DISCOUNT_PERCENTAGE);
        printf("You have been given a discount of %.2f%%\n", DISCOUNT_PERCENTAGE * 100);
    } else {
        printf("No discount was given.\n");
    }

    // Update car stock
    cars[car_index].stock -= quantity;

    // Record sale data
    Sale sale;
    strcpy(sale.customer_name, customer_name);
    sale.customer_age = customer_age;
    sale.total_price = total_price;
    sale.discount = with_plug ? DISCOUNT_PERCENTAGE * 100 : 0;
    sale.num_cars = quantity;
    strcpy(sale.date, date);
    strcpy(sale.car_model, cars[car_index].model);  // Store the car model in the sales array
    sales[num_sales] = sale;  // Store the sale in the sales array

    printf("Purchase successful!\n");
    printf("You bought %d %d Mercedes Benz %s AMG for %d GBP.\n", quantity, cars[car_index].year, cars[car_index].model, total_price);

    new_line();
    //give use time to read the output
    printf("Press Enter to continue...");
    getchar();
    clear_screen();
    new_line();

    // Feedback process
    printf("Please leave a rating from 1 to 5.\n");
    printf("We promise not to be as fast as your purchase :)\n");

    // Loop until a valid rating between 1 and 5 is entered
    while (1) {
        printf("Rating: ");
        int result = scanf("%hu", &rating);
        clear_buffer();  // Clear the buffer

        // Validate rating
        if (result == 1 && rating >= 1 && rating <= 5) {
            break;  // If the rating is valid, break the loop
        }

        printf("Invalid rating. Please enter a number between 1 and 5.\n");
    }

    // Loop until a valid feedback containing only alphabets is entered
    while (1) {
        printf("Please leave a short comment: ");
        scanf(" %[^\n]", comment);  // Read a line of text
        clear_buffer();  // Clear the buffer

        // Validate feedback
        if (is_alpha_string(comment)) {
            break;  // If the feedback is valid (only contains alphabets), break the loop
        }

        printf("Invalid feedback. Please only use alphabets.\n");
    }

    // Store feedback
    sales[num_sales].rating = rating;  // Store the rating in the sales array
    strcpy(sales[num_sales].feedback, comment);  // Store the feedback in the sales array

    num_sales++;  // Increment the number of sales

    new_line();

    printf("Now you can drive away with style!\n");
    printf("Thank you for your feedback\3\n");
    printf("Drive Safely\n");
}

// Function to display the sales data
void display_sales_data() {
    new_line();
    printf("                                    SALES DATA      \n");
    printf("__________________________________________________________________________________________\n");
    printf("%-20s%-15s%-15s%-15s%-15s%-15s\n", "Name", "Model", "Quantity", "Discount", "Total Price", "Date");
    for (int i = 0; i < num_sales; i++) {
        printf("%-20s%-15s%-15d%-15s%-15u%-15s\n",
               sales[i].customer_name,
               sales[i].car_model,
               sales[i].num_cars,
               sales[i].discount > 0 ? "YES" : "NO",
               sales[i].total_price,
               sales[i].date);
    }
    printf("__________________________________________________________________________________________\n");
    new_line();
}

// Function to display the general sales data
void display_general_sales() {
    int total_sold = 0;
    int total_revenue = 0;
    int total_left = 0;

    for (int i = 0; i < num_sales; i++) {
        total_sold += sales[i].num_cars;
        total_revenue += sales[i].total_price;
    }

    int n = sizeof(cars) / sizeof(cars[0]);
    for (int i = 0; i < n; i++) {
        total_left += cars[i].stock;
    }

    printf("We have sold %d cars for a total revenue of %d GBP and we have %d cars left\n\n", total_sold, total_revenue, total_left);
}

// Function to display the model sales data
void display_model_sales() {
    int n = sizeof(cars) / sizeof(cars[0]);  // Get the number of car models

    // Initialize arrays to store the total sales and total revenue for each model
    int total_sales[n];
    int total_revenue[n];
    for (int i = 0; i < n; i++) {
        total_sales[i] = 0;
        total_revenue[i] = 0;
    }

    // Calculate the total sales and total revenue for each model
    for (int i = 0; i < num_sales; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(sales[i].car_model, cars[j].model) == 0) {
                total_sales[j] += sales[i].num_cars;
                total_revenue[j] += sales[i].total_price;
            }
        }
    }

    // Bubble sort by total revenue in descending order
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (total_revenue[j] < total_revenue[j+1]) {
                int temp = total_revenue[j];
                total_revenue[j] = total_revenue[j+1];
                total_revenue[j+1] = temp;

                temp = total_sales[j];
                total_sales[j] = total_sales[j+1];
                total_sales[j+1] = temp;

                Car tempCar = cars[j];
                cars[j] = cars[j+1];
                cars[j+1] = tempCar;
            }
        }
    }

    printf("                                 MODEL SALES DATA   \n");
    printf("__________________________________________________________________________________________\n");
    printf("%-25s%-23s%-23s%-23s\n", "Model", "Year", "Units Sold", "Total Revenue");

    // Display the total sales and total revenue for each model
    for (int i = 0; i < n; i++) {
        // Only display models that have been purchased at least once
        if (total_sales[i] > 0) {
            printf("%-25s%-23d%-23d%-23d\n", cars[i].model, cars[i].year, total_sales[i], total_revenue[i]);
        }
    }
    printf("__________________________________________________________________________________________\n");
}

// Function to display the customer feedback
void display_feedback() {
    new_line();
    printf("                  CUSTOMER FEEDBACK   \n");
    printf("______________________________________________________\n");
    printf("%-20s%-15s%-10s%-15s\n", "Customer", "Model", "Rating", "Feedback");
    for (int i = 0; i < num_sales; i++) {
        printf("%-20s%-15s%-10d%-15s\n",
               sales[i].customer_name,
               sales[i].car_model,
               sales[i].rating,
               sales[i].feedback);
    }
    printf("______________________________________________________\n");
    new_line();
}


// Function to pause the program
void pauseProgram(int choice) {
    // give the user a chance to read the previous output, allow them to continue when ready
    // customise the output depending on the user's choice
    if (choice == MENU_OPTION_EXIT) {
        printf("\n\nPress Enter to Exit...");
    }
    else {
        printf("\n\nPress Enter to return to the Menu...");
    }

    getchar();
}

// Function to read sales data from the sales_data.txt file
void read_sales_data() {
    FILE *file = fopen("sales_data.txt", "r");  // Open the file in read mode

    // If the file does not exist, return
    if (file == NULL) {
        printf("No previous sales data found.\n");
        return;
    }

    // Read the sales data from the file
    while (fscanf(file, "%s %s %hu %u %hu %u %s %hu\n",
                  sales[num_sales].customer_name,
                  sales[num_sales].car_model,
                  &sales[num_sales].customer_age,
                  &sales[num_sales].total_price,
                  &sales[num_sales].discount,
                  &sales[num_sales].num_cars,
                  sales[num_sales].date,
                  &sales[num_sales].rating) == 8) {
        fgets(sales[num_sales].feedback, 255, file);  // Read the feedback
        sales[num_sales].feedback[strcspn(sales[num_sales].feedback, "\n")] = 0;  // Remove the newline character at the end of the feedback
        num_sales++;
                  }

    fclose(file);  // Close the file
}

// Function to write sales data to the sales_data.txt file
void write_sales_data() {
    FILE *file = fopen("sales_data.txt", "w");  // Open the file in write mode

    // If the file cannot be opened, print an error message and return
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the sales data to the file
    for (int i = 0; i < num_sales; i++) {
        fprintf(file, "%s %s %hu %u %hu %u %s %hu %s\n",
                sales[i].customer_name,
                sales[i].car_model,
                sales[i].customer_age,
                sales[i].total_price,
                sales[i].discount,
                sales[i].num_cars,
                sales[i].date,
                sales[i].rating,
                sales[i].feedback);
    }

    fclose(file);  // Close the file
}

// The main function in this code is the entry point of the program.
// It starts by reading any existing sales data from a file.
// Then, it enters a loop where it displays a welcome message and a menu of options to the user.
// Depending on the user's choice, it can display the car stock, handle the car buying process,
// display sales data, display customer feedback, or exit the program.
// If the user chooses to exit, a farewell message is displayed.
// Finally, the function writes the updated sales data back to the file.


int main() {
    // Read sales data from the file
    read_sales_data();

    // Variable to store the user's choice
    int choice;
    do {
        clear_screen();  // Clear the screen

        // Display the welcome message
        welcome_message();


        // Display the menu and get the user's choice
        show_menu();
        fflush(stdout);  // Flush the output buffer

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_buffer();  // Clear the buffer

        // Switch performs different actions based on the user's choice
        switch (choice) {
            case MENU_OPTION_VIEW_CAR_STOCK:
                display_stock();
            break;
            case MENU_OPTION_BUY_CARS:
                display_stock();
                buy_car();
            break;
            case MENU_OPTION_VIEW_SALES_DATA:
                if (num_sales == 0) {
                    new_line();
                    printf("No sales data :(\n");
                    new_line();
                } else {
                    display_sales_data();
                    display_model_sales();
                    display_general_sales();
                }
            break;
            case MENU_OPTION_CUSTOMER_FEEDBACKS:
                if (num_sales == 0) {
                    new_line();
                    printf("No feedback data :(\n");
                    new_line();
                } else {
                    display_feedback();
                }
            break;
            case MENU_OPTION_EXIT:
                menu_exit();
            break;
            default:
                new_line();
                printf("Invalid choice. Please try again.\n");
        }
        // give the user a chance to read the previous output, allow them to continue when ready
        pauseProgram(choice);

    } while (choice != MENU_OPTION_EXIT);

    // again, keep the screen clear
    clear_screen();

    // a good sentence almost never fails to warm the heart...
    printf("\n\nHave a good day!\n\n");
    printf("Thank you for visiting Benz Plug!\n");
    printf("Please Drive Safely\n");

    //write the updated sales data to the file
    write_sales_data();

    return 0;
}