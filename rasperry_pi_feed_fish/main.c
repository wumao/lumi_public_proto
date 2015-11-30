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
	char recv_msg[1000] = { 0 }; //����UDP server ���յ�������
	socklen_t addr_len = sizeof(peer_addr);
	
	//== ����UDPserver�ˣ��˿�9898�����������������ı���
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(9898);
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

	//== ����GPIO ʹ���� wiringPi��
	wiringPiSetup();
	pinMode(DEVICE_IO_PORT, OUTPUT);  //ʹ��GPIO7ȥ����

	for (;;) {
		ret = recvfrom(sockfd, recv_msg, 1000, 0, (struct sockaddr *)&peer_addr, &addr_len);
		if (ret >= 0) {
			recv_msg[ret] = 0;
			if (strstr(recv_msg, "gateway/info") != 0) { //��ѯ�����а�������Щ�豸
				char *send_msg = "{\"cmd\":\"read\",\"uri\":\"devices\",\"id\":1,\"data\":\"\"}";
				sendto(sockfd, send_msg, strlen(send_msg), 0, (struct sockaddr*)&peer_addr, sizeof(struct sockaddr));
				continue;
			}
			else if (strstr(recv_msg, "click") != 0) { //�п��ذ��£������л����click�����ﲻ�Ǻ��Ͻ���û�н������ġ�
				digitalWrite(DEVICE_IO_PORT, HIGH);  //����GPIO�ߵ�ƽ��ι�����ʼתһȦι�㣨ι����ӵ͵���תһȦ��
				delay(1000);
				digitalWrite(DEVICE_IO_PORT, LOW);  //����Ϊ�͵�ƽ���´��ٴθߵ�ƽʱ�Ż���Ч��
			}
		}
	}
}

