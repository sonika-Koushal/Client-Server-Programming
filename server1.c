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
struct sockaddr_in clientSocketInformation;
int successCode;
int len;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind with port 5050\n");
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TM server is ready to accept the request\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
if(successCode>0)
{
printf("request arrived\n");
printf("%s\n",request);
}
strcpy(response,"welcome to client server network");
successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
if(successCode>0)
{
printf("response sent\n");
}
else
{
printf("Unable to sent response\n");
}
closesocket(serverSocketDescriptor);
closesocket(clientSocketDescriptor);
WSACleanup();
return 0;
}