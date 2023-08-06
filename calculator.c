#include<stdio.h>
#include<math.h>  // Include the math library

void displayMenu() {
    printf("Advanced Calculator\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exponentiation\n");
    printf("6. Square Root\n");
    printf("7. Sine\n");
    printf("8. Cosine\n");
    printf("9. Tangent\n");
    printf("10. Exit\n");
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

        if(choice == 10) {
            printf("Exiting...\n");
            break;
        }

        if (choice >= 1 && choice <= 4) { // For operations that require two inputs
            printf("Enter two numbers: ");
            if (scanf("%lf %lf", &num1, &num2) != 2) {
                printf("Invalid input!\n");
                clearBuffer();
                continue;
            }
        } else {  // For operations that require one input
            printf("Enter a number: ");
            if (scanf("%lf", &num1) != 1) {
                printf("Invalid input!\n");
                clearBuffer();
                continue;
            }
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
            case 5:
                result = pow(num1, num2);
                break;
            case 6:
                if (num1 < 0) {
                    printf("Error: Negative number for square root.\n");
                    continue;
                }
                result = sqrt(num1);
                break;
            case 7:
                result = sin(num1);
                break;
            case 8:
                result = cos(num1);
                break;
            case 9:
                if (cos(num1) == 0) {
                    printf("Error: Tangent undefined for this value.\n");
                    continue;
                }
                result = tan(num1);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        printf("Result: %lf\n", result);
    }

    return 0;
}

