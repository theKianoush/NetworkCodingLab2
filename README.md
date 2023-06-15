To run this program you want to 

first run the make file

and then run the command "./server2 <port number>"
 
and then you run the command "./client2 config.file messages.txt" in another window
 
the server will print out the messages that were desinted for it, and print out a message saying "Recieved a message not destined for me!", because it will also recieve messages not meant for it

 
the client side takes the config file first, and then runs a loop to make the first socket, and sends the messages one line at a time to the server, and the loop will increment to the next server in the config file and repeat the proccess 
  
  
i have included an image of myself running it on the csegrid server, Thanks
