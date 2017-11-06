#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFSIZE 2048



int main(int argc, char* argv[]){

	char buff[BUFFSIZE];
	int numLines(0), fd(0), linePos(0), numRead(0), w(0);
	


	if( argc == 1 || (argc == 2 && atoi(argv[1]) < 0))
	{
	     if(argc == 2)
	     {
		for(int i = 0; i < (atoi(argv[1]) * -1); i++)
		{
			int n = read(STDIN_FILENO, buff, BUFFSIZE);
			w = write(STDOUT_FILENO,buff, n);

			if(n < 0)
			{
				perror("error reading the file");
				exit(EXIT_FAILURE);
			}
		
			else if( w < 0 )
			{
				perror("error writing to output");
				exit(EXIT_FAILURE);		
			}
	     	}
	     }	
		
	     else
	     {
		while(true)
		{
			int n = read(STDIN_FILENO, buff, BUFFSIZE);
                        w = write(STDOUT_FILENO,buff, n);
			
		}
	     }

		exit(EXIT_SUCCESS);
 	}


	else if(argc == 2)

	{
		fd = open(argv[1], O_RDONLY);

		if(fd > 0)
		{
			numRead = read(fd, buff, BUFFSIZE);

			for(int i = 0; i < numRead; i++)
			{
				if(numLines == 10)
				{
					break;
				}
				else if(buff[i] == '\n')
				{	
					linePos = i;
					numLines++;
				}
			}
			
			w = write(STDOUT_FILENO, buff, linePos);
			printf("\n");
			if(w < 0)
                        {
                                perror("Failure to write to standard output");
                                exit(EXIT_FAILURE);
			}
		
			if(close(fd) < 0)
			{
				perror("error closing the file");
				exit(EXIT_FAILURE);
			}				
					
			exit(EXIT_SUCCESS);
		}

		else
		{
			if(atoi(argv[1]) > 0)
			{

				perror("illegal line cound");
				
			}
			else
			{	
				perror("head: No such file or directory ");
			}
			exit(EXIT_FAILURE);
		}

	}


	else if(argc == 3)
	{
		fd = open(argv[2], O_RDONLY);
		if(atoi(argv[1]) < 0 && fd > 0)	
		{

			numRead = read(fd, buff, BUFFSIZE);
			if(numRead < 0)
			{
				perror("Failure to read from file");
				exit(EXIT_FAILURE);

			} 
			int i;
			for(i = 0; i < numRead; i++)
			{
				if(numLines == atoi(argv[1])* -1)
				{	
					break;
				}
				else if(buff[i] == '\n')
				{
					linePos = i;
					numLines++;
				}
			}
			 w = write(STDOUT_FILENO, buff, linePos);
			 printf("\n");			
			if(w < 0)
			{
				perror("Failure to write to standard output");
				exit(EXIT_FAILURE);
			}

			if(close(fd) < 0)
                        {
                                perror("error closing the file");
                                exit(EXIT_FAILURE);
                        }
			exit(EXIT_SUCCESS);
		}

		else
		{

			if(atoi(argv[1]) > 0)
			{
				perror("head: illegal line count --");
				printf("%s",argv[1]);
				printf("\n");
				printf("%d",numRead);
			}
			
			else
			{
				perror("head: No such file or directory");
			}
	
			exit(EXIT_FAILURE);
		}





	}


	else
	{	

		perror("Error: Invalid Input");
		exit(EXIT_FAILURE);

	}




}
