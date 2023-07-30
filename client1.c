#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
char request[5000];
char response[5000];
int serverSocketDescriptor;
int clientSocketDescriptor;
WORD ver;
WSADATA wsaData;
struct sockaddr_in serverSocketInformation;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"Hello ,I am Aakash Yadav , learning the networking");
send(clientSocketDescriptor,request,strlen(request)+1,0);
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("response recevied\n");
printf("%s\n",response);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}