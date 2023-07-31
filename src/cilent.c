#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fcntl.h>


#define SERVER_PORT  8888
#define SERVER_IP	"127.0.0.1"


static int sockfd,fd1,fd2;
static long read_pos;
struct sockaddr_in server_addr = {0};


void *recv_write_thread()
{
	int ret;
	char recvbuf[6];
		

	fd1 = open("../out/rec_B.txt",O_RDWR | O_CREAT | O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
	if(fd1 == -1)
	{
		printf("%s open file filed\n",__func__);
		pthread_exit((void *)-1);

	}
	while(1)
	{	
		memset(recvbuf,0x0,sizeof(recvbuf));
		ret = recv(sockfd,recvbuf,sizeof(recvbuf),0);
		if(0 >= ret)
		{
			perror("recv error");
			break;
		}
		else
		{	
			printf("from server:%s\n",recvbuf);
			if(0 == strncmp("s_end",recvbuf,5))
			{
				printf("recv file finish\n");
				break;
			}
			ret = write(fd1,recvbuf,sizeof(recvbuf));
			if(0 > ret)
			{
				perror("write file filed\n");
				break;
			}
		}
	}
	printf("rcv_thread end\n");
	close(fd1);
	pthread_exit(0);
}


void *read_send_thread()
{

	char buf[4];
	int ret;	
	int file_end_flag = -1;

	fd2 = open("../data/A.txt",O_RDONLY);
	if(-1 == fd2)
	{
		perror("open file failed");
		pthread_exit(0);
	}
	int temp = lseek(fd2,read_pos,SEEK_SET);
	printf("read_pos:%ld\n",read_pos);

	while(1)
	{
		if(file_end_flag != 0)//文件末尾判断
		{
			memset(buf,0,sizeof(buf));
			file_end_flag = read(fd2,buf,sizeof(buf));
			printf("read buf:%s\n",buf);
			if(file_end_flag > 0)
				ret = send(sockfd,buf,strlen(buf),0);
			if(0 > ret)
			{
				perror("send error");
				break;
			}
			sleep(1);
		}
		else if(file_end_flag == 0)
		{
			strcpy(buf,"cnd");
			send(sockfd,buf,strlen(buf),0);
			printf("read to end of file\n");
			break;
		}
	}
	close(fd2);
	pthread_exit(0);
}



int main(void)
{
	int ret;
	char signal[10] = {"start"};
	pthread_t tid_recv,tid_send;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > sockfd)
	{
		perror("socket error");
		exit(-1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr);


	ret = connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(0 > ret)
	{
		perror("connect error");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	printf("##################服务器连接成功###################\n");
//发送开始信号，接收read_pos	

	ret = recv(sockfd,&read_pos,sizeof(read_pos),0);
	if(ret < 0)
	{
		perror("recv pos failed\n");
	}
	ret = send(sockfd,signal,sizeof(signal),0);
	if(ret < 0)
	{
		perror("send signal failed\n");
		return -1;

	}
//线程创建
	ret = pthread_create(&tid_recv,NULL,recv_write_thread,NULL);
	if(ret < 0)
	{
		perror("create tid_recv failed\n");
		return -1;
	}

	ret = pthread_create(&tid_send,NULL,read_send_thread,NULL);
	if(ret < 0)
	{
		perror("create tid_send failed\n");
		return -1;
	}

//客户端提前结束判断 --signal == end 提前结束，	
	printf("if you want to end,input end\n");
	while(1){
		scanf("%s",signal);
		if(strncmp("end",signal,3) != 0)
		{
			continue;
		}
		
		else if(strncmp("end",signal,3) == 0)
		{
			send(sockfd,signal,sizeof(signal),0);
			close(fd1);
			close(fd2);
			close(sockfd);
			exit(0);
		}
	}
		ret = pthread_join(tid_recv,NULL);
		if(ret < 0)
		{
			perror("join tid_recv failed\n");
			return -1;

		}
		ret = pthread_join(tid_recv,NULL);
		if(ret < 0)
		{
			perror("join tid_send failed\n");
			return -1;

		}
	
	exit(0);

}





