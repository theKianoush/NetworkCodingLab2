// this server file needs just the port number specifiec on the command line.
// first we create a socket, and bind the socket to the address and the port
// then we recv the input from the client
// and it takes the input, and tokenizes it, and prints the output in a specified format.
// Written by Kianoush Ranjbar


#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>





int main(int argc, char *argv[])
{
  int sd; /* socket descriptor */
  int i;  /* loop variable */
  struct sockaddr_in server_address; /* my address */
  struct sockaddr_in from_address;  /* address of sender */
  char bufferReceived[1000]; // used in recvfrom
  int portNumber; // get this from command line
  int rc; // always need to check return codes!
  socklen_t fromLength;
  int flags = 0; // used for recvfrom
  
  /* first, decide if we have the right number of parameters */
  if (argc < 2){
    printf("Error: enter <Port Number> as parameter\n");
    exit (1);
  }


//------------------------------------------------------------------------
  /* first create a socket */
  sd = socket(AF_INET, SOCK_DGRAM, 0); /* create a socket */

  /* always check for errors */
  if (sd == -1){ /* means some kind of error occured */
    perror ("Error creating the socket");
    exit(1); /* just leave if wrong number entered */
  }

  /* now fill in the address data structure we use to sendto the server */
  for (i=0;i<strlen(argv[1]); i++){
    if (!isdigit(argv[1][i]))
      {
	printf ("Error: the port number must be a numerical integer\n");
	exit(1);
      }
  }
//------------------------------------------------------------------------
// make ip address
    
    
  portNumber = strtol(argv[1], NULL, 10); /* many ways to do this */

  if ((portNumber > 65535) || (portNumber < 0)){
    printf ("Error: you entered an invalid port number out of the range of 0-65535\n");
    exit (1);
  }

  server_address.sin_family = AF_INET; /* use AF_INET addresses */
  server_address.sin_port = htons(portNumber); /* convert port number */
  server_address.sin_addr.s_addr = INADDR_ANY; /* any adapter */
  
//------------------------------------------------------------------------
  /* the next step is to bind to the address */
  rc = bind (sd, (struct sockaddr *)&server_address,
	     sizeof(struct sockaddr ));
  
  if (rc < 0){
    perror("Error binding to the socket");
    exit (1);
  }

//------------------------------------------------------------------------


    
  while(1){ // this while loop is to receive multple lines from the client
    memset (bufferReceived, 0, 1000); // zero out the buffers in C
  /* NOTE - you MUST MUST MUST give fromLength an initial value */
  fromLength = sizeof(struct sockaddr_in);
    
    
  rc = recvfrom(sd, bufferReceived, 1000, flags,
		(struct sockaddr *)&from_address, &fromLength);   // receive the input line from the client

  /* check for any possible errors */
  if (rc <=0){
    perror ("Error receiving message");
    printf ("there was an error due to the receiving function\n");
    exit (1);
  }
      

if (strstr(bufferReceived, argv[1])) {  // check if port number is in the string we received from client, if so proceed

  /* print out what i get */
  printf ("\n\nmessage received: '%s'\n\n", bufferReceived);
    
  char *ptr;  // creat pointer to received message so we can parse it properly
  ptr = strtok(bufferReceived, " ");

    printf("name:value\n");      
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // this is where we tokenize and print the string
  while (ptr !=NULL){
    
    
    int len = strcspn(ptr, "\"");
                      
    if (ptr[len] == '\"'){
        char quote[1000];
        strcpy(quote, ptr);
        ptr = strtok(NULL, " ");
        
        while (ptr != NULL && ptr[strcspn(ptr, "\"")] != '\"'){
            strcat(quote, " ");
            strcat(quote, ptr);
            ptr = strtok(NULL, " ");
        }
        if (ptr != NULL) {
            strcat(quote, " ");
            strcat(quote, ptr);
        printf ("'%s'\n",quote);

        }
    }
      
  else {

       printf ("'%s'\n",ptr);

    }
        ptr = strtok(NULL, " ");

    }
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

}
      else{     // if port number is not in message, print this
        printf("--------------------------------------------------\n");
          printf("Recieved a message not destined for me!\n");
        printf("--------------------------------------------------\n");

      }
     
  }   

	return 0;    

} // end of main()
