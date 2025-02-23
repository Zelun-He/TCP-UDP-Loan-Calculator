TCP/UDP Loan Calculator
This project implements a TCP/UDP-based Loan Calculator that allows a client to send loan details (principal, interest rate, and term) to a server, which calculates the monthly payment and sends the result back to the client. The project demonstrates basic socket programming in C++ and supports both TCP and UDP protocols.

Features
TCP and UDP Support: The server and client can communicate using either TCP (reliable, connection-oriented) or UDP (lightweight, connectionless).

Loan Calculation: The server calculates the monthly loan payment using the formula:

Payment = P ⋅ r /(1 − ( 1 + r ) ^− n)

 
where:

P
P = Principal amount

r
r = Monthly interest rate

n
n = Loan term in months

Cross-Platform: The code is written in C++ and can be compiled and run on Windows (using Winsock) or Unix-like systems (using POSIX sockets).

Prerequisites
C++ Compiler: Ensure you have a C++ compiler installed (e.g., g++ for Linux/macOS, or MinGW for Windows).

Winsock (Windows Only): If you're on Windows, ensure you have the Winsock library available (ws2_32.lib).

Folder Structure
Copy
TCP-UDP-Loan-Calculator/
├── Client.cpp       // Client code (TCP/UDP)
├── Server.cpp       // Server code (TCP/UDP)
├── README.md        // Project documentation
How to Build and Run
1. On Linux/macOS
Open a terminal in the project folder.

Compile the server and client:

bash
Copy
g++ Server.cpp -o server
g++ Client.cpp -o client
Run the server:

bash
Copy
./server
Open a new terminal and run the client:

bash
Copy
./client
2. On Windows
Open a terminal in the project folder.

Compile the server and client using g++ (MinGW):

bash
Copy
g++ Server.cpp -o server -lws2_32
g++ Client.cpp -o client -lws2_32
Run the server:

bash
Copy
./server.exe
Open a new terminal and run the client:

bash
Copy
./client.exe
Usage
Server
When you run the server, it will prompt you to choose between TCP or UDP:

Copy
Choose server type (1 for TCP, 2 for UDP):
After selecting the protocol, the server will start listening for incoming connections or messages.

Client
When you run the client, it will prompt you to choose between TCP or UDP:

Copy
Choose client type (1 for TCP, 2 for UDP):
Enter the loan details when prompted:

Copy
Enter principal amount: 10000
Enter annual interest rate (%): 5
Enter loan term (months): 12
The server will calculate the monthly payment and send the result back to the client:

Copy
Server response: Monthly Payment: $856.07
Example Workflow
Server Terminal
bash
Copy
$ ./server
Choose server type (1 for TCP, 2 for UDP): 1
TCP Server listening on port 8080
TCP Server: Result sent to client.
Client Terminal
bash
Copy
$ ./client
Choose client type (1 for TCP, 2 for UDP): 1
Enter principal amount: 10000
Enter annual interest rate (%): 5
Enter loan term (months): 12
Server response: Monthly Payment: $856.07
Supported Platforms
Windows: Use the Winsock API (included in the code).

Linux/macOS: Use the POSIX socket API.

Contributing
If you'd like to contribute to this project, feel free to:

Fork the repository.

Create a new branch for your feature or bugfix.

Submit a pull request.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Author
Zelun He

GitHub: zelunhe

Email: zelunhe@gmail.com
