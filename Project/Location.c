//��λģ��

#include"Location.h"


void GetLocation()
{
	
  if(direction != pre_direction)//С���ı��˶�����ʱ���¼�ʱ
	{
		if(pre_direction == 1)                                               //��ʱ����10��ʱ���������
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
	if(direction == 0)                 //ֹͣʱֱ�ӷ���
	{
		return;
  }
	else if(direction == 5)            //��ת�����Ƕ�
	{
		angle = (angle + 2);
		if (angle >= 360)
			angle = angle - 360;
	}
	else if(direction == 6)            //��ת
	{
		angle = (angle - 2);
		if (angle < 0)
			angle = angle + 360;
	}
	
	else if(this_direction_runtime == 10)    //10��50msˢ��һ��
	{
		if(direction == 1)                     //ǰ��
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
	else                                //ˢ�¼�ʱ��
	{
		this_direction_runtime ++;
  }
	
	if(runflag == 0)             //С��ֹͣʱ�����긴λ
	{
		location_x = 0;
		location_y = 0;
		angle = 0;
  }
}