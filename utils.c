#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void showDatasetSummary(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    double x, y;
    double sumX = 0, sumY = 0;
    double minX = 1e9, minY = 1e9;
    double maxX = -1e9, maxY = -1e9;
    int count = 0;
    char line[256];

    // Skip header line if present
    fgets(line, sizeof(line), fp);

    // Read each row
    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%lf,%lf", &x, &y) == 2)
        {
            sumX += x;
            sumY += y;
            if (x < minX)
                minX = x;
            if (x > maxX)
                maxX = x;
            if (y < minY)
                minY = y;
            if (y > maxY)
                maxY = y;
            count++;
        }
    }
    fclose(fp);

    if (count == 0)
    {
        printf("Dataset is empty or invalid.\n");
        return;
    }

    double meanX = sumX / count;
    double meanY = sumY / count;

    printf("\n========== DATASET SUMMARY ==========\n");
    printf("File: %s\n", filename);
    printf("Total Rows: %d\n", count);
    printf("-------------------------------------\n");
    printf("X -> Min: %.2lf  |  Max: %.2lf  |  Mean: %.2lf\n", minX, maxX, meanX);
    printf("Y -> Min: %.2lf  |  Max: %.2lf  |  Mean: %.2lf\n", minY, maxY, meanY);
    printf("=====================================\n");
}
