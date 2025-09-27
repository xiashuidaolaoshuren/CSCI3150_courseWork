#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define MAX_ARG_NUM 30 

int shell_execute(char ** args, int argc)
{
	// Print args and args count
	for (int i = 0; i < argc; i++)
	{
		printf("arg %d: %s\n", i, args[i]);
	}

    // Check for EXIT command
    if (strcmp(args[0], "EXIT") == 0)
        return -1;

    // Find all pipe positions
    int pipe_positions[MAX_ARG_NUM];
    int num_pipes = 0;
    
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_positions[num_pipes] = i;
            num_pipes++;
        }
    }
    
    // If no pipes, execute normally
    if (num_pipes == 0) {
        int child_pid, wait_return, status;

	printf("Child process running...\n\n");
        
        if((child_pid = fork()) < 0)
		{
			perror("fork() error \n");
		}
		else if (child_pid == 0)
		{

			if ( execvp(args[0], args) < 0)
			{ 
				perror("execvp() error \n");
				exit(-1);
			}
		}
		else
		{
			if ((wait_return = wait(&status)) < 0)
				perror("wait() error \n"); 
		}

		printf("\nChild process finished\n");
				
		return 0;
    }
    
    // Handle piped commands
    int pipefd[2];
    int read_fd = 0;  // Initially no input pipe
    int write_fd;

    for (int i = 0; i <= num_pipes; i++) {
        // Determine start and end positions for this command
        int start = (i == 0) ? 0 : pipe_positions[i-1] + 1;
        int end = (i == num_pipes) ? argc - 1 : pipe_positions[i];
        
        // Create a new argument array for this command
        char *cmd_args[MAX_ARG_NUM];
        int cmd_argc = 0;
        
		// Copy args to cmd_args with NULL terminator
        for (int j = start; j < end; j++) {
            cmd_args[cmd_argc++] = args[j];
        }
        cmd_args[cmd_argc] = NULL;
        
        // Create pipe for all commands except the last one
        if (i < num_pipes) {
            if (pipe(pipefd) == -1) {
                perror("pipe() error \n");
                exit(-1);
            }
            write_fd = pipefd[1];
        } else {
            write_fd = -1;  // Last command writes to stdout
        }
        
        int child_pid = fork();

        if (child_pid == -1) {
            perror("fork() error \n");
			return 0;
        }
        
        if (child_pid == 0) {
			if (i == 0) printf("\n");
			printf("Child process %d executing: %s\n", i, cmd_args[0]);
			if (i == num_pipes) printf("\n");
				
            // Redirect input if not the first command
            if (read_fd != 0) {
                dup2(read_fd, STDIN_FILENO);
                close(read_fd);
            }
            
            // Redirect output if not the last command
            if (write_fd != -1) {
                dup2(write_fd, STDOUT_FILENO);
                close(write_fd);
            }
            
			// Execute command
            execvp(cmd_args[0], cmd_args);
            perror("execvp() error \n");
            exit(1);
        }
        
        // Close file descriptors in parent
        if (read_fd != 0) {
            close(read_fd);
        }
        if (write_fd != -1) {
            close(write_fd);
        }
        
        // Write end becomes the read end for next command
        read_fd = pipefd[0];
    }
    
    // Wait for all children to complete
    for (int i = 0; i <= num_pipes; i++) {
        int status;
        wait(&status);
    }

	printf("Child process finished\n");
    
    return 0;
}
