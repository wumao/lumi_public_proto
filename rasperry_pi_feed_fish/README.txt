1. 克隆项目到 ~/目录

2. 拷贝gcc_rpi.sh 到 ~/ 目录

3. 打开终端并输入
   source ~/gcc_rpi.sh

4. 进入~/rpi 目录编译
   arm-bcm2708hardfp-linux-gnueabi-gcc -o feed_fish main.c -I ./wiringPi/wiringPi/ ./wiringPi/wiringPi/wiringPi.c ./wiringPi/wiringPi/softPwm.c ./wiringPi/wiringPi/softTone.c ./wiringPi/wiringPi/piHiPri.c -lpthread