#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*

Under the same folder, file input.txt.
Each line contains a positive integer number and we guarantee the number is smaller than 1000.
You need to read the number in each line, add it by one, and write them line by line to another file called output.txt

NOTE: Please don't hardcode the results in your program because we change the content in input.txt when grading.

TIP: You can use sscanf to convert char array to int and sprintf to convert int to char array. 

*/
int main(){
    FILE *input_file, *output_file;
    char line[100];
    int base_number;
    int number;
    int result;
    char result_str[100];
    
    // Open input file for reading
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }
    
    // Open output file for writing
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error: Cannot create output.txt\n");
        fclose(input_file);
        return 1;
    }
    
    // Read the base number from the first line
    if (fgets(line, sizeof(line), input_file) != NULL) {
        sscanf(line, "%d", &base_number);
    } else {
        printf("Error: Cannot read base number\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }
    
    // Read the remaining 10 lines and process each number
    for (int i = 0; i < 10; i++) {
        if (fgets(line, sizeof(line), input_file) != NULL) {
            // Convert string to integer
            sscanf(line, "%d", &number);
            
            // Add base number to the current number
            result = number + base_number;
            
            // Convert result to string and write to output file
            sprintf(result_str, "%d\n", result);
            fputs(result_str, output_file);
        } else {
            printf("Error: Cannot read line %d\n", i + 2);
            break;
        }
    }
    
    // Close files
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}