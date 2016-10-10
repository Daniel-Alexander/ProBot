#ifndef _BOT_DEFINES
#define _BOT_DEFINES

#define MOTOR_ENABLE 15

#define ENGINE_OFF 0x0
#define ENGINE_ON 0x1

#define ENGINE_FORWARD 0x1 // 0b0001
#define ENGINE_BACKWARD 0x2 // 0b0010

#define SUCCESS 0x0
#define ERR_STAT_UNSUPPORTED 0x1
#define ERR_DIR_UNSUPPORTED 0x2
#define ERR_OUT_OF_RANGE 0x4

#define t_Result int

#endif