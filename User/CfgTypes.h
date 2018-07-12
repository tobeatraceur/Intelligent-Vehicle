/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CfgTypes.h
** 最后修订日期:		2008-11-12
** 最后版本:			1.0
** 描述:				变量类型定义，提供了控制寄存器的操作宏
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:				律晔
** 创建日期:			2008-07-24
** 版本:				1.0
** 描述:				与BDMC项目统一函数接口
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:				律晔
** 修订日期:			2009-08-02
** 版本:				1.1
** 描述:				与AVRGCC内的库统一操作宏接口
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************************/
#ifndef CfgTypes_H_
#define CfgTypes_H_


#include "stm32f10x.h"
#include <stdlib.h>
#include <stdio.h>


/*************************************************************************************************************************
**                                                  逻辑操作符定义
*************************************************************************************************************************/
//#ifndef FALSE
//  #define  FALSE  0                    /* Boolean value FALSE. FALSE is defined always as a zero value. */
//#endif
//#ifndef TRUE
//  #define  TRUE   !FALSE               /* Boolean value TRUE. TRUE is defined always as a non zero value. */
//#endif
//
//#ifndef NULL
//  #define  NULL   0
//#endif


/*************************************************************************************************************************
**                                                  寄存器操作宏
*************************************************************************************************************************/
/*
#define SetRegBit(reg, bit)                                     (reg |= _BV(bit))
#define ClrRegBit(reg, bit)                                     (reg &= ~_BV(bit))
#define GetRegBit(reg, bit)                                     (reg & _BV(bit))
#define SetReg(reg, val)                                        (reg = (uint8)(val))
#define GetReg(reg)                                             (reg)
#define SetRegBits(reg, mask)                                   (reg |= (uint8)(mask))
#define GetRegBits(reg, mask)                                   (reg & (uint8)(mask))
#define ClrRegBits(reg, mask)                                   (reg &= (uint8)(~(mask)))
#define SetRegMask(reg, maskAnd, maskOr)                        (reg = (uint8)((GetReg(reg) & ~(maskAnd)) | (maskOr)))
#define SetRegBitVal(reg, bit, val)                             ((val) == 0 ? (reg &= ~_BV(bit)) : (reg |= _BV(bit)))
#define ChangeRegBits(reg, mask)                                (reg ^= (mask))
#define ChangeRegBit(reg, bit)                                  (reg ^= _BV(bit))
*/


/* 变量位长度修改宏 */
/*
#define In16(var,l,h)  (var = ((word)(l)) | (((word)(h)) << 8))
#define In32(var,l,h)  (var = ((dword)(l)) | (((dword)(h)) << 16))

#define Out16(l,h,val) { h = (byte)((val) >> 8); l = (byte)(val); }
#define Out32(l,h,val) { h = (short)((val) >> 16); l = (short)(val); }

#define Output(P, V) SetReg(P,V)
#define Input(P) GetReg(P)
*/


#endif
/*************************************************************************************************************************
**                                                      文件结束
*************************************************************************************************************************/
