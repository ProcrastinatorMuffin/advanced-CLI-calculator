#include<stdio.h>

void displayMenu() {
    printf("Basic Calculator\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exit\n");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;
    double num1, num2, result;

    while(1) {
        displayMenu();

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        if(choice == 5) {
            printf("Exiting...\n");
            break;
        }

        printf("Enter two numbers: ");
        if (scanf("%lf %lf", &num1, &num2) != 2) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch(choice) {
            case 1:
                result = num1 + num2;
                break;
            case 2:
                result = num1 - num2;
                break;
            case 3:
                result = num1 * num2;
                break;
            case 4:
                if(num2 == 0) {
                    printf("Error: Division by zero.\n");
                    continue;
                }
                result = num1 / num2;
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        printf("Result: %lf\n", result);
    }

    return 0;
}

