1. ��¡��Ŀ�� ~/Ŀ¼

2. ����gcc_rpi.sh �� ~/ Ŀ¼

3. ���ն˲�����
   source ~/gcc_rpi.sh

4. ����~/rpi Ŀ¼����
   arm-bcm2708hardfp-linux-gnueabi-gcc -o feed_fish main.c -I ./wiringPi/wiringPi/ ./wiringPi/wiringPi/wiringPi.c ./wiringPi/wiringPi/softPwm.c ./wiringPi/wiringPi/softTone.c ./wiringPi/wiringPi/piHiPri.c -lpthread