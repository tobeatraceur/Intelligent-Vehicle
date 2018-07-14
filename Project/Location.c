//定位模块

#include"Location.h"


void GetLocation()
{
	
  if(direction != pre_direction)//小车改变运动方向时重新计时
	{
		if(pre_direction == 1)                                               //计时不够10的时候更新坐标
		{
			location_x = location_x + this_direction_runtime / 10 * cos(angle * PI / 180);
			location_y = location_y + this_direction_runtime / 10 * sin(angle * PI / 180);
		}
		if(pre_direction == 2)
		{
			location_x = location_x - this_direction_runtime / 10 * cos(angle * PI / 180);
			location_y = location_y - this_direction_runtime / 10 * sin(angle * PI / 180);
		}
		if(pre_direction == 3)
		{
			location_x = location_x - this_direction_runtime / 10 * sin(angle * PI / 180);
			location_y = location_y + this_direction_runtime / 10 * cos(angle * PI / 180);
		}
		if(pre_direction == 4)
		{
			location_x = location_x + this_direction_runtime / 10 * sin(angle * PI / 180);
			location_y = location_y - this_direction_runtime / 10 * cos(angle * PI / 180);
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
		angle = (angle + 2);
		if (angle >= 360)
			angle = angle - 360;
	}
	else if(direction == 6)            //右转
	{
		angle = (angle - 2);
		if (angle < 0)
			angle = angle + 360;
	}
	
	else if(this_direction_runtime == 10)    //10个50ms刷新一次
	{
		if(direction == 1)                     //前进
		{
			location_x = location_x + cos(angle * PI / 180);
			location_y = location_y + sin(angle * PI / 180 );
			
		}
		if(direction == 2)
		{
			location_x = location_x - cos(angle * PI / 180);
			location_y = location_y - sin(angle * PI / 180);
			
		}
		if(direction == 3)
		{
			location_x = location_x - sin(angle * PI / 180);
		
			location_y = location_y + cos(angle * PI / 180);
		}
		if(direction == 4)
		{
			location_x = location_x + sin(angle * PI / 180);
		
			location_y = location_y - cos(angle * PI / 180);
		}
		this_direction_runtime = 0;
	}
	else                                //刷新计时器
	{
		this_direction_runtime ++;
  }
	
	if(runflag == 0)             //小车停止时将坐标复位
	{
		location_x = 0;
		location_y = 0;
		angle = 0;
  }
}