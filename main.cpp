#include "mbed.h"
#include "MMA7660FC.h"

#define ADDR_MMA7660 (0x4C << 1)

#if defined(TARGET_WIO_3G) || defined (TARGET_WIO_BG96)
DigitalOut GrovePower(GRO_POWR, 1);
#define COLISN_PIN D20
#else
#define COLISN_PIN D2
#endif

MMA7660FC acc(I2C_SDA, I2C_SCL, ADDR_MMA7660);
InterruptIn collision(COLISN_PIN);

int hits = 0;

void func(void){
    hits++;
}

int main(void) {
    float x=0, y=0, z=0;
    acc.init();
    collision.mode(PullUp);
    collision.fall(&func);

    printf("*** sensor test start ***\n\n");

    while(1) {
        acc.read_Tilt(&x, &y, &z);
        printf("hits: %d\n", hits);
        printf("x: %6.2f degree\n", x);
        printf("y: %6.2f degree\n", y);
        printf("z: %6.2f degree\n", z);
        printf("\n");
        wait(0.5);
    }
}