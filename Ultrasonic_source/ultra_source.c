#include "lcd_ultra.h"

void delay(unsigned int k)
{
    for(j=0;j<=k;j++)
    {
            for(i=0;i<10;i++);
    }
}
void data_write(void)
{
    ENABLE_HIGH;
    delay(2);
    ENABLE_LOW;
}
void data_read(void)
{
    ENABLE_LOW;
    delay(2);
    ENABLE_HIGH;
    }
void check_busy(void)
{
    P2DIR &= ~(BIT3); // make P1.3 as input
    while((P2IN&BIT3)==1)
    {
        data_read();
    }
    P2DIR |= BIT3; // make P1.3 as output
}
void send_command(unsigned char cmd)
{
    check_busy();
    WRITE;
    CWR;
    P2OUT = (P2OUT & 0xF0)|((cmd>>4) & 0x0F); // send higher nibble
    data_write(); // give enable trigger
    P2OUT = (P2OUT & 0xF0)|(cmd & 0x0F); // send lower nibble
    data_write(); // give enable trigger
}

void send_data(unsigned char data)
{
    check_busy();
    WRITE;
    DR;
    P2OUT = (P2OUT & 0xF0)|((data>>4) & 0x0F); // send higher nibble
    data_write(); // give enable trigger
    P2OUT = (P2OUT & 0xF0)|(data & 0x0F); // send lower nibble
    data_write(); // give enable trigger
}
void send_string(char *s)
{
    while(*s)
    {
        send_data(*s);
        s++;
    }
}

unsigned char find_char(int n)
{
    if (n==0)
        return '0';
    if (n==1)
        return '1';
    if (n==2)
        return '2';
    if (n==3)
        return '3';
    if (n==4)
        return '4';
    if (n==5)
        return '5';
    if (n==6)
        return '6';
    if (n==7)
        return '7';
    if (n==8)
        return '8';
    else
        return '9';
}

void send_integer(int dst)
{
    int n= dst;
    int len =0;
    int rem;
    unsigned char xtern;
    while(n!=0)
    {
        len++;
        n/=10;
    }

    int i;
    for (i=0;i<len;i++)
    {
        rem = dst % 10;
        dst = dst/10;
        xtern = find_char(rem);
        send_data(xtern);
    }
    send_data('\0');
}

int reverse_my_int(int n)
{
    int r = 0;
    while (n !=0)
    {
        r=r*10;
        r=r+ n%10;
        n=n/10;
    }
    return r;
}
void lcd_init(void)
{
    P2SEL &= ~BIT6;
    P2DIR |= 0xFF;
    P2OUT &= 0x00;
    send_command(0x33);
    send_command(0x32);
    send_command(0x28); // 4 bit mode
    send_command(0x0E); // clear the screen
    send_command(0x01); // display on cursor on
    send_command(0x06); // increment cursor
    send_command(0x80); // row 1 column 1
}



