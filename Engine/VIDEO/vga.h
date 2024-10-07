/////////////////////////////////////////////////////////
// vga.c header file
/////////////////////////////////////////////////////////


#define VGA_VIDEO_INT 				0x10		 // Video interrupt number
#define VGA_MODE_13					0x13
#define VGA_TEXT_MODE 				0x03      // use to set back to 80x25 text mode.

#define VGA_ADDRESS					0xA000    // VGA VRAM Adrress

#define VGA_SEQ_INDEX            0x03c4    // VGA sequence controller
#define VGA_SEQ_DATA             0x03c5
#define VGA_MEMORY_MODE			   0x04
#define VGA_ALL_PLANES				0xff02

#define VGA_CRTC_INDEX				0x03d4	  // CRT Controller Index
#define VGA_CRTC_DATA		      0x03d5
#define VGA_CRTC_V_TOTAL_REG    	0x06
#define VGA_CRTC_OVERFLOW_REG   	0x07
#define VGA_CRTC_V_START_REG     0x10
#define VGA_CRTC_RETRACE_END     0x11
#define VGA_CRTC_V_DISPLAY_END   0x12
#define VGA_CRTC_OFFSET_REG      0x13
#define VGA_CRTC_ULINE_LOC		   0x14
#define VGA_CRTC_V_BLANK_START   0x15
#define VGA_CRTC_V_BLANK_END	   0x16
#define VGA_CRTC_MODE_CONTROL    0x17
#define VGA_CRTC_LINE_COMPARE		0x18

#define VGA_CRTC_HIGHADDRESS	0x0C
#define VGA_CRTC_LOWADDRESS	0x0D

#define VGA_INPUT_STATUS		0x03da
/* VGA status bits */
#define VGA_DISPLAY_ENABLE 	0x01
#define VGA_OVERFLOW            0x07
#define VGA_VRETRACE 			0x08
#define VGA_MAX_SCANLINE       0x09

#define VGA_GC_INDEX            0x03ce    // VGA graphics controller
#define VGA_GC_DATA             0x03cf

#define VGA_MAP_MASK           0x02

#define VGA_PALETTE_INDEX      0x03c8
#define VGA_PALETTE_DATA        0x03c9

#define VGA_AC_WRITE 0x3C0
#define VGA_AC_READ 0x3C1
#define VGA_AC_HPP_REG         0X20 | 0X13    // Horizontal Pel Panning Register
#define VGA_AC_MODE_CONTROL		0x10	  //Index of Mode COntrol register in AC
#define VGA_AC_INDEX			0x03c0	  //Attribute controller index register




/* Attribute controller registers */
#define VGA_PEL_PANNING 0x13

// Programable interval timer Command/mode port
#define PTI_MODE 0x43
#define PTI_CH0  0x40
#define PTI_CH1  0x41
#define PTI_CH2  0x42


