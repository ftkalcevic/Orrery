#pragma once

#include "main.h"
#include <string.h>
//#define INVERT


#define ADDRESS				(0b0111100<<1)
#define CMD_DISPLAY_ON		0b10101110
#define CMD_SET_COL_LOW		0b00000000
#define CMD_SET_COL_HI		0b00010000
#define CMD_SET_PAGE_ADDR	0b10110000
#define CMD_SET_ROW			0b01000000

class SH1106
{
private:
	uint8_t display_buffer[128 * 64 / 8];
	void write_cmd(uint8_t n)
	{
		HAL_StatusTypeDef  res;
		uint8_t buffer[2];
		buffer[0] = 0;	// C0=0,D/C=0
		buffer[1] = n;
		res = HAL_I2C_Master_Transmit(&hi2c1, ADDRESS, buffer, sizeof(buffer), 100);
	}
	
	void write_data(uint8_t n)
	{
		HAL_StatusTypeDef  res;
		uint8_t buffer[2];
		buffer[0] = 0b01000000;	// C0=0,D/C=1
		buffer[1] = n;
		res = HAL_I2C_Master_Transmit(&hi2c1, ADDRESS, buffer, sizeof(buffer), 100);
	}
	
public:
	SH1106(){}
	
	void init()
	{
		HAL_GPIO_WritePin(GPIO_Display_RST_GPIO_Port, GPIO_Display_RST_Pin, GPIO_PIN_SET);
		HAL_Delay(5); // ms
		HAL_GPIO_WritePin(GPIO_Display_RST_GPIO_Port, GPIO_Display_RST_Pin, GPIO_PIN_RESET);
		HAL_Delay(5); // ms
		HAL_GPIO_WritePin(GPIO_Display_RST_GPIO_Port, GPIO_Display_RST_Pin, GPIO_PIN_SET);
		HAL_Delay(5);	// ms
		
		Display(false);
		
		write_cmd(0x02); //set lower column address
		write_cmd(0x10); //set higher column address
		write_cmd(0x40); //set display start line
		write_cmd(0xB0); //set page address
		write_cmd(0x81); //contract control
		write_cmd(0xff); //128
		
#if !defined(INVERT)
		write_cmd(0xA0);   //--Set SEG/Column Mapping - normal
		write_cmd(0xC0);   //Set COM/Row Scan Direction   - normal
#else
		write_cmd(0xA1);   //--Set SEG/Column Mapping - invert
		write_cmd(0xC8);   //Set COM/Row Scan Direction   - invert
#endif
		
//		write_cmd(0xA1); //set segment remap
//		write_cmd(0xC8); //Com scan direction
		write_cmd(0xA6); //normal / reverse
		write_cmd(0xA8); //multiplex ratio
		write_cmd(0x3F); //duty = 1/64
		write_cmd(0xad); //set charge pump enable
		write_cmd(0x8b); // 0x8B 内供 VCC 
		write_cmd(0x33); //0X30---0X33 set VPP 9V 
		write_cmd(0xD3); //set display offset
		write_cmd(0x00); // 0x20 
		write_cmd(0xD5); //set osc division
		write_cmd(0x80);
		write_cmd(0xD9); //set pre-charge period
		write_cmd(0x1f); //0x22
		write_cmd(0xDA); //set COM pins
		write_cmd(0x12);
		write_cmd(0xdb); //set vcomh
		write_cmd(0x40);
		
		Clear();
		Display(true);
		HAL_Delay(100); // ms

		for (int y = 0; y < 64; y++)
			//for (int x = 0; x < 128; x++)
			{
				int x = y;
				SetPixel(x, y, 1);
			}
		Refresh();
	}
	
	void Display(bool enable)
	{
		write_cmd(CMD_DISPLAY_ON | (enable ? 1 : 0));
	}
	
	void SetColumnAddress(uint8_t n)
	{
		write_cmd(CMD_SET_COL_LOW | (n & 0x0F));
		write_cmd(CMD_SET_COL_HI | ((n>>4) & 0x0F));
	}

	void SetPageAddress(uint8_t n)
	{
		write_cmd(CMD_SET_PAGE_ADDR | (n & 0x0F));
	}

	void SetRowAddress(uint8_t n)
	{
		write_cmd(CMD_SET_ROW | (n & 0x3F));
	}
	
	void Clear()
	{
		memset(display_buffer, 0, sizeof(display_buffer));
		Refresh();
	}
	
	void Refresh()
	{
//#define DMA
#ifdef DMA
		uint8_t * p = display_buffer;
		for(uint8_t y = 0 ; y < 8 ; y++, p+=128) 
		{
			uint8_t page[2 + 2 + 2 + 2 * 128];
			page[0] = 0b10000000;	// C0=1,D/C=0
			page[1] = CMD_SET_PAGE_ADDR | (y & 0x0F);
			page[2] = 0b10000000;	// C0=1,D/C=0
			page[3] = CMD_SET_COL_LOW | (2 & 0x0F);
			page[4] = 0b10000000;	// C0=1,D/C=0
			page[5] = CMD_SET_COL_HI | ((2 >> 4) & 0x0F);

			uint8_t *b = page + 6;
			for (int i = 0; i < 128; i++)
			{
				if ( i == 128-1)
					*b++ = 0b01000000;	// C0=0,D/C=1
				else
					*b++ = 0b11000000;	// C0=1,D/C=1
				*b++ = p[i];
			}
			HAL_StatusTypeDef  res;
			res = HAL_I2C_Master_Transmit_DMA(&hi2c1, ADDRESS, page, sizeof(page));
			while (hi2c1.State != HAL_I2C_STATE_READY)
				continue;
		}
#else		
		uint8_t * p = display_buffer;
		for(uint8_t y = 0 ; y < 8 ; y++, p+=128) 
		{
			SetPageAddress(y);
			SetColumnAddress(2);

			for (int i = 0; i < 128; i++)
				write_data(p[i]);
		}
#endif
	}
	
	void SetPixel(uint8_t x, uint8_t y, uint8_t c)
	{
		
//		if (c == 0)
//			display_buffer[x / 8 + y * (128 / 8)] &= ~(1 << (x % 8));
//		else
//			display_buffer[x / 8 + y * (128 / 8)] |= 1 << (x % 8);
		if (c == 0)
			display_buffer[y / 8 * 128 + x] &= ~(1 << (y % 8));
		else
			display_buffer[y / 8 * 128 + x] |= 1 << (y % 8);
	}
};