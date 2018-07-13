#ifndef WP_LOCATION_H
#define WP_LOCATION_H

#include "stm32f10x.h"
#include "Wp_Globle.h"
#include "math.h"

extern void GetLocation();
static u16 this_direction_runtime = 0;  //当前状态运行时间
static int pre_direction = 0;            //前一个状态
                      

#endif