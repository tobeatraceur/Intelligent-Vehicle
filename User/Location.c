//定位模块

#include"Location.h"


void GetLocation()
{
	if(runflag == 0)             //小车停止时将坐标复位
	{
		location_x = 0;
		location_y = 0;
		angle = 0;
  }
	
  if(direction != pre_direction)//小车改变运动方向时重新计时
	{
		if(pre_direction == 1)                                               //计时不够10的时候更新坐标
		{
			location_x = location_x + this_direction_runtime / 10 * cos(angle);
			location_y = location_y + this_direction_runtime / 10 * sin(angle);
		}
		if(pre_direction == 2)
		{
			location_x = location_x - this_direction_runtime / 10 * cos(angle);
			location_y = location_y - this_direction_runtime / 10 * sin(angle);
		}
		if(pre_direction == 3)
		{
			location_x = location_x - this_direction_runtime / 10 * sin(angle);
			location_y = location_y + this_direction_runtime / 10 * cos(angle);
		}
		if(pre_direction == 4)
		{
			location_x = location_x + this_direction_runtime / 10 * sin(angle);
			location_y = location_y - this_direction_runtime / 10 * cos(angle);
		}
		
		pre_direction = direction;
		this_direction_runtime = 0;
  }
	if(direction == 0)                 //停止时直接返回
	{
		return;
  }
	else if(direction == 5)            //左转调整角度
	{
		angle = (angle + 2) % 360;
	}
	else if(direction == 6)            //右转
	{
		angle = (angle - 2) % 360;
	}
	else if(this_direction_runtime == 10)    //10个50ms刷新一次
	{
		if(direction == 1)                     //前进
		{
			location_x = location_x + cos(angle);
			location_y = location_y + sin(angle);
		}
		if(direction == 2)
		{
			location_x = location_x - cos(angle);
			location_y = location_y - sin(angle);
		}
		if(direction == 3)
		{
			location_x = location_x - sin(angle);
			location_y = location_y + cos(angle);
		}
		if(direction == 4)
		{
			location_x = location_x + sin(angle);
			location_y = location_y - cos(angle);
		}
		this_direction_runtime = 0;
	}
	else                                //刷新计时器
	{
		this_direction_runtime ++;
  }
}