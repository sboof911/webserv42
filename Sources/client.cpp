#include "../Includes/tt.hpp"

#define PORT 4245
int main(int ac,char **av)
{
 
int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "POST / HTTP/1.1\nHost:localhost:4245\r\n\r\nContent-type:text/html\r\n\r\n<html>\n<head>\n<title>Radio Button Data to CGI</title>\n</head>\n<body>\n<form action = /cgi-bin/cpp_radiobutton.cgi method = post target = _blank> <input type = radio name = subject value = maths checked = checked/> Maths   <input type = radio name = subject value = physics /> Physics  <input type = submit value = Select Subject /> </form> AAAAA ";
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
  
    // closing the connected socket
    close(client_fd);
    return 0;
}