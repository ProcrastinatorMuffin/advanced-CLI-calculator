// Include necessary libraries
#include<stdio.h>
#include<string.h>
#include<math.h>

// Function to display a list of commands and their explanations
void showHelp() {
    printf("\nAdvanced Calculator Commands:\n");
    // List of commands with descriptions
    printf("add [num1] [num2]         : Add two numbers\n");
    printf("subtract [num1] [num2]    : Subtract second number from first\n");
    printf("multiply [num1] [num2]    : Multiply two numbers\n");
    printf("divide [num1] [num2]      : Divide first number by second\n");
    printf("power [num] [exponent]    : Raise number to the power of exponent\n");
    printf("sqrt [num]                : Calculate the square root of a number\n");
    printf("sin [angle]               : Calculate the sine of an angle (in radians)\n");
    printf("cos [angle]               : Calculate the cosine of an angle (in radians)\n");
    printf("tan [angle]               : Calculate the tangent of an angle (in radians)\n");
    printf("help                      : Show this help message\n");
    printf("exit                      : Exit the calculator\n\n");
}

int main() {
    // Variables to store the command and numbers for calculations
    char command[50];
    double num1, num2, result;

    // Initial message to the user
    printf("Type 'help' for a list of commands.\n");

    // Infinite loop to continuously prompt user for commands
    while (1) {
        printf("> ");  // Command prompt
        scanf("%s", command);  // Read the command

        // Check the entered command and perform the corresponding operation
        if (strcmp(command, "exit") == 0) {
            break;  // Exit the program
        } else if (strcmp(command, "help") == 0) {
            showHelp();  // Display the list of commands
            continue;
        } else if (strcmp(command, "add") == 0) {
            scanf("%lf %lf", &num1, &num2);
            result = num1 + num2;
        } else if (strcmp(command, "subtract") == 0) {
            scanf("%lf %lf", &num1, &num2);
            result = num1 - num2;
        } else if (strcmp(command, "multiply") == 0) {
            scanf("%lf %lf", &num1, &num2);
            result = num1 * num2;
        } else if (strcmp(command, "divide") == 0) {
            scanf("%lf %lf", &num1, &num2);
            if (num2 == 0) {
                printf("Error: Division by zero.\n");
                continue;
            }
            result = num1 / num2;
        } else if (strcmp(command, "power") == 0) {
            scanf("%lf %lf", &num1, &num2);
            result = pow(num1, num2);
        } else if (strcmp(command, "sqrt") == 0) {
            scanf("%lf", &num1);
            if (num1 < 0) {
                printf("Error: Negative number for square root.\n");
                continue;
            }
            result = sqrt(num1);
        } else if (strcmp(command, "sin") == 0) {
            scanf("%lf", &num1);
            result = sin(num1);
        } else if (strcmp(command, "cos") == 0) {
            scanf("%lf", &num1);
            result = cos(num1);
        } else if (strcmp(command, "tan") == 0) {
            scanf("%lf", &num1);
            if (cos(num1) == 0) {
                printf("Error: Tangent undefined for this value.\n");
                continue;
            }
            result = tan(num1);
        } else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
            continue;  // Go back to the start of the loop and prompt the user again
        }

        // Display the result of the calculation
        printf("Result: %lf\n", result);
    }

    // Message displayed when the user exits the program
    printf("Goodbye!\n");
    return 0;
}

