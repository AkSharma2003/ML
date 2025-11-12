#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "linear_regression.h"
#include "utils.h"
#include <sys/ioctl.h>

// ✅ Color codes
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

// ✅ Clear screen command (cross-platform)
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void showMenu(){
    int width = get_terminal_width();

    const char *title_lines[] = {
        CYAN "======================================" RESET,
        YELLOW "   MACHINE LEARNING LIBRARY IN C" RESET,
        CYAN "======================================" RESET
    };

    const char *menu_lines[] = {
        GREEN "1. Train Linear Regression Model" RESET,
        GREEN "2. Predict using Saved Model" RESET,
        GREEN "3. Save Trained Model" RESET,
        GREEN "4. Load Model" RESET,
        GREEN "5. Display Dataset Summary" RESET,
        RED   "6. Exit" RESET,
        CYAN  "--------------------------------------" RESET
    };

    printf("\n");

    // 🟢 Center the title lines only
    for (int i = 0; i < 3; i++) {
        int len = strlen(title_lines[i]);
        int padding = (width - len) / 2;
        if (padding < 0) padding = 0;
        printf("%*s%s\n", padding, "", title_lines[i]);
    }

    printf("\n");

    // 🟢 Left-align all menu items with equal left margin
    int left_margin = (width - 40) / 2; // adjust 40 based on menu width
    if (left_margin < 0) left_margin = 0;

    for (int i = 0; i < 7; i++) {
        printf("%*s%s\n", left_margin, "", menu_lines[i]);
    }

    // 🟢 Input prompt left-aligned (no centering)
    printf("\nEnter your choice: ");
}

int main()
{
    int choice;
    double m = 0.0, c = 0.0;
    int trained = 0;
    double new_x;
    char datasetFile[100] = "data.csv";

    
    do
    {
        system(CLEAR); // 🧼 clear screen for each menu
        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid input! Please enter a number.\n" RESET);
            fflush(stdin);
            continue;
        }
        getchar(); // 🟢 flush newline

        switch (choice)
        {
        case 1:
        {
            printf(YELLOW "\n[Training Linear Regression Model...]\n" RESET);
            printf("Enter dataset filename (or press Enter for default '%s'): ", datasetFile);
            char tempFile[100];
            fgets(tempFile, sizeof(tempFile), stdin);
            if (tempFile[0] != '\n')
            {
                tempFile[strcspn(tempFile, "\n")] = 0;
                strcpy(datasetFile, tempFile);
            }
            trainLinearRegression(datasetFile, &m, &c, 0.01, 1000);
            trained = 1;
            break;
        }

        case 2:
            if (!trained)
            {
                printf(RED "No model trained yet. Train or load one first.\n" RESET);
            }
            else
            {
                printf("Enter new input X: ");
                scanf("%lf", &new_x);
                getchar();
                double pred = predictLinearRegression(new_x, m, c);
                printf(GREEN "Predicted Output Y = %.1lf\n" RESET, pred);
            }
            break;

        case 3:
            if (trained)
            {
                saveLinearModel(m, c);
                printf(GREEN "Model saved successfully!\n" RESET);
            }
            else
            {
                printf(RED "Train a model before saving!\n" RESET);
            }
            break;

        case 4:
            loadLinearModel(&m, &c);
            trained = 1;
            printf(GREEN "Model loaded successfully!\n" RESET);
            break;

        case 5:
            showDatasetSummary(datasetFile);
            break;

        case 6:
            printf(YELLOW "Exiting...\n" RESET);
            break;

        default:
            printf(RED "Invalid choice. Try again.\n" RESET);
        }

        printf("\nPress Enter to continue...");
        getchar(); // wait before showing menu again

    } while (choice != 6);

    return 0;
}
