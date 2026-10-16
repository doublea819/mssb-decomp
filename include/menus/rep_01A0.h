#ifndef __MENUS_REP_01A0_H_
#define __MENUS_REP_01A0_H_

#include "mssbTypes.h"

// Menu music sequence table entry (lbl_2_data_128).
typedef struct {
    u16 a;
    u16 b;
    u16 c;
} SeqEnt;

extern SeqEnt lbl_2_data_128[2];
#ifdef TARGET_PC
extern void (*lbl_2_data_138[19])(void); // menu scene handlers, indexed by scene id (18: Career, PC)
#else
extern void (*lbl_2_data_138[18])(void); // menu scene handlers, indexed by scene id
#endif

void fn_2_A70(u16 frames);
void fn_2_B38(void);
void fn_2_C18(void);
void fn_2_C74(u8 volume);

#endif
