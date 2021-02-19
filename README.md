# RTOS_Assignmnet-2
Group chat

To run the code on server side:
gcc -o server server.c -lpthread
./server 5555

To run the code on client side:
gcc -o client client.c -lpthread
./client 4 <IP address of server> 5555 <name> <group_name>
