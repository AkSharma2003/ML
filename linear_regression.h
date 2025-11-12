#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

// Structure to store model parameters
typedef struct
{
    double m; // slope
    double c; // intercept
} LinearModel;

// Function to train the linear regression model using gradient descent
void trainLinearRegression(const char *filename, double *m, double *c, double learning_rate, int epochs);

// Function to predict output for a given input using trained model
double predictLinearRegression(double x, double m, double c);

// Function to save trained model weights into a file
void saveLinearModel(double m, double c);

// Function to load saved model weights from a file
void loadLinearModel(double *m, double *c);

#endif
