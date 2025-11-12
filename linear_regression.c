#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linear_regression.h"

// Function to train linear regression using gradient descent
void trainLinearRegression(const char *filename, double *m, double *c, double learning_rate, int epochs)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: Unable to open dataset file '%s'\n", filename);
        return;
    }

    double x[1000], y[1000];
    int n = 0;
    char line[100];

    // Skip header if present
    fgets(line, sizeof(line), fp);

    // Read CSV data
    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%lf,%lf", &x[n], &y[n]) == 2)
            n++;
    }
    fclose(fp);

    if (n == 0)
    {
        printf("Error: No data found in '%s'\n", filename);
        return;
    }

    *m = 0.0;
    *c = 0.0;

    // Gradient Descent
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double dm = 0.0, dc = 0.0, loss = 0.0;

        for (int i = 0; i < n; i++)
        {
            double y_pred = (*m) * x[i] + (*c);
            double diff = y_pred - y[i];

            dm += diff * x[i];
            dc += diff;
            loss += diff * diff;
        }

        dm /= n;
        dc /= n;

        *m -= learning_rate * dm;
        *c -= learning_rate * dc;

        if (epoch % 100 == 0)
            printf("Epoch %d -> Loss: %.6lf\n", epoch, loss / n);
    }

    printf("\nTraining completed!\n");
    printf("Final Model: y = %.4lfx + %.4lf\n", *m, *c);
}

// Function to predict Y using trained model
double predictLinearRegression(double x, double m, double c)
{
    return (m * x + c);
}

// Function to save model parameters (m, c) into file
void saveLinearModel(double m, double c)
{
    FILE *fp = fopen("model_weights.txt", "w");
    if (!fp)
    {
        printf("Error: Unable to save model.\n");
        return;
    }
    fprintf(fp, "%.6lf %.6lf\n", m, c);
    fclose(fp);
    printf("Model saved to 'model_weights.txt'\n");
}

// Function to load saved model parameters
void loadLinearModel(double *m, double *c)
{
    FILE *fp = fopen("model_weights.txt", "r");
    if (!fp)
    {
        printf("Error: No saved model found.\n");
        return;
    }
    fscanf(fp, "%lf %lf", m, c);
    fclose(fp);
    printf("Loaded model: y = %.4lfx + %.4lf\n", *m, *c);
}
