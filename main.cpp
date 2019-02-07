#include "mbed.h"
#include "MMA7660FC.h"

#define ADDR_MMA7660 (0x4C << 1)

MMA7660FC acc(I2C_SDA, I2C_SCL, ADDR_MMA7660);
Serial pc(USBTX, USBRX);
DigitalOut GrovePower(GRO_POWR, 1);
InterruptIn collision(D20);
int hit = 0;

void func(void){
    hit = 1;
}

int main(void) {
    float x=0, y=0, z=0;
    acc.init();
    pc.baud(115200);
    collision.mode(PullUp);
    collision.fall(&func);
    pc.printf("*** sensor test start ***\n\n");

    while(1) {
        if (hit == 1) {
            pc.printf("*");
            hit = 0;
        }
        acc.read_Tilt(&x, &y, &z);
        pc.printf("x: %2.2f degree \n", x);                    // Print the tilt orientation of the X axis
        pc.printf("y: %2.2f degree \n", y);                    // Print the tilt orientation of the Y axis
        pc.printf("z: %2.2f degree \n", z);                    // Print the tilt orientation of the Z axis
        pc.printf("\n");
        wait(0.5);
    }
}