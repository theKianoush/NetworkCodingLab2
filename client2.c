// This is the client file that takes the config.file and messages.txt on the command line 
// it goes line by line in the config file send the message to every server (line by line) in the config file
// Written by Kianoush Ranjbar

#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LENGTH 200



int main(int argc, char *argv[])
{

  int sd; /* the socket descriptor */
  struct sockaddr_in server_address;  /* structures for addresses */
  struct sockaddr_in inaddr;  /* structures for checking addresses */
  int rc;
  char *lineFromFile = NULL;
  size_t lengthRead = 0;
  char serverIP[20]; // provided by the user on the command line */
  int portNumber = 0; // provided by the user on the command line
  
 

    
//------------------------------------------------------------------------
  /* check to see if the right number of parameters was entered, there should be 2 */
 if (argc < 3) {
        printf("Error: enter the name of the config file as a parameter, and the name of the text file as the second parameter\n");
        exit(1);
    }

    FILE *config_file = fopen(argv[1], "r");   // if config file is specified as parameter, open it
    if (config_file == NULL) {
        perror("Error opening config file");
        exit(EXIT_FAILURE);
    }
  
    

    int numServers = 0;
    
    while (fscanf(config_file, "%s %d", serverIP, &portNumber) == 2){   // starting with the first line of the config file 
        numServers++;   // these will incrmenet each line of the config file
        
        sd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */
        if (sd == -1){
            printf("Error creating socket\n");
            exit(1);
        }
        
        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET; /* use AF_INET addresses */
        server_address.sin_port = htons(portNumber); /* convert port number */
        server_address.sin_addr.s_addr = inet_addr(serverIP); /* convert IP addr */
        
        printf("Server %d: IP %s, port %d\n", numServers, serverIP, portNumber); // print which server we will send to 

        
        FILE *fp = fopen(argv[2], "r");     // open the text file 
        if (fp == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
    }
        
        while ((rc = getline(&lineFromFile, &lengthRead, fp)) != -1){       // and send line by line to the server
            int len = strlen(lineFromFile);
                if (lineFromFile[len-1] == '\n') {
                    lineFromFile[len-1] = '\0';
                }
            
            printf("Sending to server %d --- %s\n", numServers, lineFromFile);         //print what we are sending to server
            sendto(sd, lineFromFile, strlen(lineFromFile), 0, (struct sockaddr *) &server_address, sizeof(server_address)); // send it
        }
         fclose(fp);    // close the text file
        close(sd);      // close the sockets
    }
    
        fclose(config_file);    // close the config file
    return 0;
}
