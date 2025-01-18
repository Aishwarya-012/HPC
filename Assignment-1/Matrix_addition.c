#include <stdio.h>

void getMatrix(FILE *file, int matrix[10][10], int *rows, int *cols, const char *name) {
    printf("Enter the number of rows and columns for %s: ", name);
    scanf("%d %d", rows, cols);
    fprintf(file, "\n%s\nDimensions: %dx%d\n\n", name, *rows, *cols);
    printf("Enter the elements of %s (%d x %d):\n", name, *rows, *cols);
    for (int i = 0; i < *rows; i++){
        for (int j = 0; j < *cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
            fprintf(file, "%d ", matrix[i][j]);
        }
    fprintf(file, "\n");
    }
}

void readMatrix(FILE *file, int matrix[10][10], int *rows, int *cols) {
    fscanf(file, "%d %d", rows, cols);
    for (int i = 0; i < *rows; i++)
        for (int j = 0; j < *cols; j++)
            fscanf(file, "%d", &matrix[i][j]);
}

void addMatrices(int m1[10][10], int m2[10][10], int res[10][10], int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res[i][j] = m1[i][j] + m2[i][j];
}

int main() {
    int m1[10][10], m2[10][10], res[10][10], r1, c1, r2, c2;
    FILE *inputFile = fopen("input.txt", "w+"), *outputFile;

    if (!inputFile) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    getMatrix(inputFile, m1, &r1, &c1, "Matrix 1");
    getMatrix(inputFile, m2, &r2, &c2, "Matrix 2");
    fclose(inputFile);

    inputFile = fopen("input.txt", "r");
    readMatrix(inputFile, m1, &r1, &c1);
    readMatrix(inputFile, m2, &r2, &c2);
    fclose(inputFile);

    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Error: Cannot open output file.\n");
        return 1;
    }

    if (r1 != r2 || c1 != c2)
        fprintf(outputFile, "Error: The dimensions of the matrices do not match.\n");
    else {
        addMatrices(m1, m2, res, r1, c1);
        fprintf(outputFile, "Output matrix \n\nDimensions: %dx%d\n\n", r1, c1);
        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c1; j++)
                fprintf(outputFile, "%d ", res[i][j]);
            fprintf(outputFile, "\n");
        }
    }

    fclose(outputFile);
    printf("Matrix addition completed. Results are stored in output.txt.\n");
    return 0;
}