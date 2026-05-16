#include <REG52.H>

typedef unsigned char u8;
typedef unsigned int  u16;

/* ===================== 1. 硬件接口区 ===================== */
/* P0：数码管段选 A~DP；P2.0~P2.3：74HC154位选 */

sbit KEY_A       = P1^0;   // A加分
sbit KEY_B       = P1^1;   // B加分
sbit KEY_START   = P1^2;   // 开始
sbit KEY_STOP    = P1^3;   // 停止
sbit KEY_SET     = P1^4;   // 时间设置
sbit KEY_ADD     = P1^5;   // 时间加
sbit KEY_DEC     = P1^6;   // 时间减
sbit KEY_EXTRA   = P1^7;   // 加时

sbit KEY_24_STOP = P3^0;   // 24秒停止
sbit KEY_24_RUN  = P3^1;   // 24秒计时/重置
sbit ALARM       = P3^7;   // LED+蜂鸣器

/* ===================== 2. 基础配置区 ===================== */

#define FOSC 11059200UL
#define T0_RELOAD (65536UL - FOSC / 12 / 1000)
#define T0RH ((u8)(T0_RELOAD >> 8))
#define T0RL ((u8)(T0_RELOAD))

#define SEG_BLANK 16
#define SEG_DP    0x80

#define K_A       0x0001
#define K_B       0x0002
#define K_START   0x0004
#define K_STOP    0x0008
#define K_SET     0x0010
#define K_ADD     0x0020
#define K_DEC     0x0040
#define K_EXTRA   0x0080
#define K_24_STOP 0x0100
#define K_24_RUN  0x0200

/* 共阴极段码：P0.0~P0.7 = A B C D E F G DP */
u8 code SEG[17] = {
    0x3F,0x06,0x5B,0x4F,0x66,
    0x6D,0x7D,0x07,0x7F,0x6F,
    0x77,0x7C,0x39,0x5E,0x79,0x71,
    0x00
};

/* 74HC154 位选：Y0~Y13 */
u8 code DIG[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};

/* ===================== 3. 数据状态区 ===================== */

volatile u16 sys_ms = 0;
volatile u16 sec_cnt = 0;
volatile u8  scan_pos = 0;
volatile u8  disp[14];

volatile u16 score_a = 0;
volatile u16 score_b = 0;
volatile u16 game_sec = 10 * 60;
volatile u8  atk24 = 24;

volatile bit game_run = 0;
volatile bit atk_run = 0;
volatile u16 alarm_ms = 0;
u8 set_mode = 0;

/* ===================== 4. 显示数据处理区 ===================== */

u8 ToSeg(u8 n)
{
    if(n > 16) n = SEG_BLANK;
    return SEG[n];
}

u8 AddDp(u8 seg)
{
    return seg | SEG_DP;
}

void Put4(u8 pos, u16 num, u8 blank)
{
    u8 q,b,s,g;

    if(num > 9999) num = 9999;

    q = num / 1000;
    b = num / 100 % 10;
    s = num / 10 % 10;
    g = num % 10;

    disp[pos]   = (blank && q==0) ? ToSeg(SEG_BLANK) : ToSeg(q);
    disp[pos+1] = (blank && q==0 && b==0) ? ToSeg(SEG_BLANK) : ToSeg(b);
    disp[pos+2] = (blank && q==0 && b==0 && s==0) ? ToSeg(SEG_BLANK) : ToSeg(s);
    disp[pos+3] = ToSeg(g);
}

void UpdateDisplay(void)
{
    u8 min, sec;

    Put4(0, score_a, 1);
    Put4(4, score_b, 1);

    min = game_sec / 60;
    sec = game_sec % 60;

    if(min > 99) min = 99;

    disp[8]  = ToSeg(min / 10);
    disp[9]  = AddDp(ToSeg(min % 10));
    disp[10] = ToSeg(sec / 10);
    disp[11] = ToSeg(sec % 10);

    disp[12] = ToSeg(atk24 / 10);
    disp[13] = ToSeg(atk24 % 10);
}

/* ===================== 5. 硬件显示驱动区 ===================== */

void ScanDisplay(void)
{
    P0 = 0x00;
    P2 = (P2 & 0xF0) | DIG[scan_pos];
    P0 = disp[scan_pos];

    scan_pos++;
    if(scan_pos >= 14) scan_pos = 0;
}

/* ===================== 6. 按键读取与功能处理区 ===================== */

u16 ReadKeys(void)
{
    u16 k = 0;

    if(KEY_A       == 0) k |= K_A;
    if(KEY_B       == 0) k |= K_B;
    if(KEY_START   == 0) k |= K_START;
    if(KEY_STOP    == 0) k |= K_STOP;
    if(KEY_SET     == 0) k |= K_SET;
    if(KEY_ADD     == 0) k |= K_ADD;
    if(KEY_DEC     == 0) k |= K_DEC;
    if(KEY_EXTRA   == 0) k |= K_EXTRA;
    if(KEY_24_STOP == 0) k |= K_24_STOP;
    if(KEY_24_RUN  == 0) k |= K_24_RUN;

    return k;
}

u16 KeyScan(void)
{
    static u16 last = 0, stable = 0;
    static u8 cnt = 0;

    u16 raw, event = 0;

    raw = ReadKeys();

    if(raw == last) {
        if(cnt < 3) cnt++;
        else if(raw != stable) {
            event = raw & (~stable);
            stable = raw;
        }
    } else {
        cnt = 0;
        last = raw;
    }

    return event;
}

void HandleKey(u16 k)
{
    if(k & K_A) {
        if(score_a < 9999) score_a++;
    }

    if(k & K_B) {
        if(score_b < 9999) score_b++;
    }

    if(k & K_START) {
        set_mode = 0;
        if(game_sec > 0) game_run = 1;
    }

    if(k & K_STOP) {
        game_run = 0;
    }

    if(k & K_SET) {
        set_mode = !set_mode;
        game_run = 0;
        atk_run = 0;
    }

    if(k & K_ADD) {
        if(set_mode && game_sec <= 99*60-60) game_sec += 60;
    }

    if(k & K_DEC) {
        if(set_mode && game_sec >= 60) game_sec -= 60;
    }

    if(k & K_EXTRA) {
        if(game_sec <= 99*60-5*60) game_sec += 5*60;
        game_run = 0;
        atk_run = 0;
        set_mode = 0;
    }

    if(k & K_24_STOP) {
        atk_run = 0;
    }

    if(k & K_24_RUN) {
        atk24 = 24;
        atk_run = 1;
    }
}

/* ===================== 7. 定时器与主流程区 ===================== */

void Timer0Init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01;

    TH0 = T0RH;
    TL0 = T0RL;

    ET0 = 1;
    TR0 = 1;
    EA  = 1;
}

void Timer0_ISR(void) interrupt 1
{
    TH0 = T0RH;
    TL0 = T0RL;

    sys_ms++;
    ScanDisplay();

    sec_cnt++;

    if(sec_cnt >= 1000) {
        sec_cnt = 0;

        if(game_run && game_sec > 0) {
            game_sec--;

            if(game_sec == 0) {
                game_run = 0;
                atk_run = 0;
                alarm_ms = 3000;
            }
        }

        if(atk_run && atk24 > 0) {
            atk24--;

            if(atk24 == 0) {
                atk_run = 0;
                alarm_ms = 1500;
            }
        }
    }

    if(alarm_ms > 0) {
        alarm_ms--;
        ALARM = ((alarm_ms / 100) % 2) ? 1 : 0;
    } else {
        ALARM = 0;
    }
}

void ResetAll(void)
{
    EA = 0;

    score_a = 0;
    score_b = 0;
    game_sec = 10 * 60;
    atk24 = 24;

    game_run = 0;
    atk_run = 0;
    set_mode = 0;

    alarm_ms = 0;
    ALARM = 0;

    EA = 1;
}

void main(void)
{
    u16 last_key_ms = 0;
    u16 key;

    P0 = 0x00;
    P1 = 0xFF;
    P2 = 0x00;
    P3 = 0xFF;
    ALARM = 0;

    ResetAll();
    UpdateDisplay();
    Timer0Init();

    while(1) {
        if((u16)(sys_ms - last_key_ms) >= 5) {
            last_key_ms = sys_ms;

            key = KeyScan();

            if(key) {
                HandleKey(key);
            }

            UpdateDisplay();
        }
    }
}