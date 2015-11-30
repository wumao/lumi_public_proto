#include <wiringPi.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define  DEVICE_IO_PORT 7

int main(int argc, char**argv)
{
	struct sockaddr_in my_addr;
	struct sockaddr_in peer_addr;
	int ret;
	char recv_msg[1000] = { 0 }; //保存UDP server 接收到的数据
	socklen_t addr_len = sizeof(peer_addr);
	
	//== 开启UDPserver端，端口9898，监听绿米网关来的报文
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(9898);
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

	//== 设置GPIO 使用了 wiringPi库
	wiringPiSetup();
	pinMode(DEVICE_IO_PORT, OUTPUT);  //使用GPIO7去控制

	for (;;) {
		ret = recvfrom(sockfd, recv_msg, 1000, 0, (struct sockaddr *)&peer_addr, &addr_len);
		if (ret >= 0) {
			recv_msg[ret] = 0;
			if (strstr(recv_msg, "gateway/info") != 0) { //查询网关中包含有哪些设备
				char *send_msg = "{\"cmd\":\"read\",\"uri\":\"devices\",\"id\":1,\"data\":\"\"}";
				sendto(sockfd, send_msg, strlen(send_msg), 0, (struct sockaddr*)&peer_addr, sizeof(struct sockaddr));
				continue;
			}
			else if (strstr(recv_msg, "click") != 0) { //有开关按下，报文中会包含click。这里不是很严谨，没有解析报文。
				digitalWrite(DEVICE_IO_PORT, HIGH);  //设置GPIO高电平，喂鱼机开始转一圈喂鱼（喂鱼机从低到高转一圈）
				delay(1000);
				digitalWrite(DEVICE_IO_PORT, LOW);  //设置为低电平，下次再次高电平时才会生效。
			}
		}
	}
}

