#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>


#define SERVER_PORT 8888

static int sockfd,connfd = -1;
struct sockaddr_in server_addr = {0};
struct sockaddr_in client_addr = {0};
char ip_str[20] = {0};
int addrlen = sizeof(client_addr);
static char signal[10] = {0};
static long pos;


void *recv_write_thread(void *arg)
{
	int fd,ret;
	int temp = 0;
	char recvbuf[4];
		

	fd = open("../out/rec_A.txt",O_RDWR | O_CREAT | O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	if(fd == -1)
	{
		printf("%s open file filed\n",__func__);
		pthread_exit((void*)-1);
	}

	while(1)
	{	
		if(strncmp("start",signal,5) == 0){
			pos = lseek(fd,0,SEEK_END);
			memset(recvbuf,0x0,sizeof(recvbuf));
			ret = recv(connfd,recvbuf,sizeof(recvbuf),0);
			if(0 >= ret)
			{
				printf("recv error\n");
				continue;
			}

			if(0 == strncmp("end",recvbuf,3))
			{
				strcpy(signal,"end");
				continue;
			}
			if(0 == strncmp("cnd",recvbuf,4))
			{
				printf("recv finish\n");
				break;
			}
			ret = write(fd,recvbuf,sizeof(recvbuf));
			if(0 > ret)
			{
				perror("write file filed\n");
				break;
			}
			printf("from client:%s\n",recvbuf);
		}
		else
		{
			sleep(1);
			continue;
		}
	}
	printf("rcv_thread end\n");
	pthread_exit((void*) 0);
}



void *read_send_thread(void *arg)
{
	int fd,ret;	
	int file_end_flag = -1;
	char readbuf[6] = {0};

	fd = open("../data/B.txt",O_RDONLY);
	if(-1 == fd)
	{
		perror("open file failed");
		pthread_exit((void*)-1);
	}

while(1){
	if(strncmp("start",signal,5) == 0)
	{
		if(file_end_flag != 0 )//文件末尾判断
		{
			memset(readbuf,0x0,sizeof(readbuf));
			file_end_flag = read(fd,readbuf,sizeof(readbuf));
			if(file_end_flag < 0)
			{
				perror("read file failed\n");
				break;

			}
			ret = send(connfd,readbuf,sizeof(readbuf),0);	
			if(0 > ret)
			{
				perror("send error");
				break;
			}
			printf("readbuf: %s\n",readbuf);
			sleep(1);
		}
		else{
			strcpy(readbuf,"s_end");
			send(connfd,readbuf,sizeof(readbuf),0);
			printf("read to end of file\n");
			break;
		}
	}
	else
	{
		sleep(1);
		continue;
	}
}
	pthread_exit((void*) 0);
}


void *wait_client_thread(void *arg)
{
	int ret;
	while(1)
	{
		connfd = accept(sockfd,(struct sockaddr*)&client_addr,&addrlen);
		if(0 > connfd)
		{
			perror("accept error");
			sleep(1);
			continue;
		}
		
		ret = send(connfd,&pos,sizeof(pos),0);
		if(ret < 0)
		{
			perror("send pos failed\n");
			pthread_exit((void*)-1);
		}
		 ret = recv(connfd,signal,sizeof(signal),0);
		if(ret < 0)
		{
			perror("recv signal failed\n");	
		}
		printf("################客户端接入###############\n");
		inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,ip_str,sizeof(ip_str));
		printf("客户端主机的ip地址:%s\n",ip_str);
		printf("客户端进程的端口号:%d\n",client_addr.sin_port);
	}
}



int main(void)
{
	int ret;
	pthread_t tid_recv,tid_send,tid_wait;
	
//创建socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > sockfd){
		perror("socket error");
		exit(-1);


	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);


	ret = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(0>ret){
		perror("bind error");
		close(sockfd);
		exit(-1);
	}

	ret = listen(sockfd,50);
	if(0 > ret )
	{
		perror("listen error");
		close(sockfd);
		exit(-1);

	}

//创建线程
	ret = pthread_create(&tid_recv,NULL,recv_write_thread,NULL);
	if(ret != 0)
	{
		perror("create tid_recv failed\n");
		return -1;
		
	}
	ret = pthread_create(&tid_send,NULL,read_send_thread,NULL);
	if(ret != 0)
	{
		perror("create tid_send failed\n");
		return -1;
	}
	
	ret = pthread_create(&tid_wait,NULL,wait_client_thread,NULL);
	if(ret != 0)
	{
		perror("create tid_send failed\n");
		return -1;
	}

//回收线程


	ret = pthread_join(tid_recv,NULL);
	if(ret)
	{
		perror("tid_recv join failed\n");
		return -1;
	}
	ret = pthread_join(tid_send,NULL);
	if(ret)
	{
		perror("tid_send join failed\n");
		return -1;
	}
	ret = pthread_join(tid_wait,NULL);
	if(ret)
	{
		perror("tid_recv join failed\n");
		return -1;
	}

	close(sockfd);
	exit(0);

}




