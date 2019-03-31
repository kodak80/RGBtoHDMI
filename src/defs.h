// defs.h

#ifndef DEFS_H
#define DEFS_H

// This is the default core clock, used when things got wrong
#define DEFAULT_CORE_CLOCK 384000000

// Define the legal range of HDMI pixel clocks
#define MIN_PIXEL_CLOCK  25.0 //  25MHz
#define MAX_PIXEL_CLOCK 165.0 // 165MHz

// Define how the Pi Framebuffer is initialized
// - if defined, use the property interface (Channel 8)
// - if not defined, use to the the framebuffer interface (Channel 1)
//
// Note: there seem to be some weird caching issues with the property interface
// so using the dedicated framebuffer interface is preferred.

// #define USE_PROPERTY_INTERFACE_FOR_FB

// Enable multiple buffering and vsync based page flipping
#define MULTI_BUFFER

// The maximum number of buffers used by multi-buffering
// (it can be set to less that this on the OSD)
#define NBUFFERS 4

#define VSYNCINT 16

// Control bits (maintained in r3)

#define BIT_MODE7         0x01       // bit  0, indicates mode 7
#define BIT_PROBE         0x02       // bit  1, indicates the mode is being determined
#define BIT_CALIBRATE     0x04       // bit  2, indicates calibration is happening
#define BIT_OSD           0x08       // bit  3, indicates the OSD is visible
#define BIT_MODE_DETECT   0x10       // bit  4, indicates mode changes should be detected
#define BIT_ELK           0x20       // bit  5, indicates we are an Electron
#define BIT_SCANLINES     0x40       // bit  6, indicates scan lines should be made visible
#define BIT_FIELD_TYPE    0x80       // bit  7, indicates the field type (0 = odd, 1 = even) of the last field
#define BIT_CLEAR        0x100       // bit  8, indicates the frame buffer should be cleared
#define BIT_VSYNC        0x200       // bit  9, indicates the red vsync indicator should be displayed
#define BIT_VSYNC_MARKER 0x400       // bit 10, indicates current line should be replaced by the red vsync indicator
#define BIT_DEBUG        0x800       // bit 11, indicates the debug grid should be displayed

#define OFFSET_LAST_BUFFER 12        // bit 12-13 LAST_BUFFER
#define MASK_LAST_BUFFER (3 << OFFSET_LAST_BUFFER)

#define OFFSET_CURR_BUFFER 14        // bit 14-15 CURR_BUFFER
#define MASK_CURR_BUFFER (3 << OFFSET_CURR_BUFFER)

#define OFFSETDUP_PALETTE_HIGH_NIBBLE 12        // bit 12-15
#define MASKDUP_PALETTE_HIGH_NIBBLE (15 << OFFSETDUP_PALETTE_HIGH_NIBBLE)

#define BIT_INTERLACED 0x10000       // bit 16, indicates the frame is expected to be interlaced
#define BIT_PSYNC_POL  0x20000       // bit 17, indicates psync inversion (NEEDS TO MATCH PSYNC_PIN below)

#define OFFSET_NBUFFERS    18        // bit 18-19 NBUFFERS
#define MASK_NBUFFERS    (3 << OFFSET_NBUFFERS)

#define OFFSET_INTERLACE   20        // bit 20-22 INTERLACE
#define MASK_INTERLACE   (7 << OFFSET_INTERLACE)

#define BIT_FIELD_TYPE1       0x00800000  // bit 23, indicates the field type of the previous field
#define BIT_FIELD_TYPE1_VALID 0x01000000  // bit 24, indicates FIELD_TYPE1 is valid

#define BITDUP_MODE2_16COLOUR    0x00800000  // bit 23, if set then 16 colour mode 2 is emulated by decoding mode 0


#define BIT_ODD_SAMPLES       0x02000000  // bit 25, if set only use odd samples
#define BIT_EVEN_SAMPLES      0x04000000  // bit 26, if set only use even samples

#define BIT_OLD_CPLDV1V2      0x08000000  // bit 27, indicates old CPLD v1 or v2
                                          // then a second time to capture stable data. The v3 CPLD delays PSYNC a
                                          // couple of cycles, so the read that sees the edge will always capture
                                          // stable data. The second read is skipped in this case.
#define BIT_NO_LINE_DOUBLE    0x10000000  // bit 28, if set then lines aren't duplicated in capture
#define BIT_NO_H_SCROLL       0x20000000  // bit 29, if set then smooth H scrolling disabled
#define BIT_NO_AUTOSWITCH     0x40000000  // bit 30, if set then autoselect enabled
                                          // bit 31 unused

// R0 return value bits
#define RET_SW1                 0x02
#define RET_SW2                 0x04
#define RET_SW3                 0x08
#define RET_EXPIRED             0x10
#define RET_INTERLACE_CHANGED   0x20
#define RET_SYNC_TIMING_CHANGED 0x40
#define RET_VSYNC_POLARITY_CHANGED 0x80
//paletteFlags
#define BIT_IN_BAND_ENABLE    0x01  // bit 0, if set in band data detection is enabled
#define BIT_IN_BAND_DETECTED  0x02  // bit 1, if set if in band data is detected
#define BIT_MODE2_PALETTE     0x04  // bit 2, if set mode 2 palette is customised
#define BIT_MODE7_PALETTE     0x08  // bit 3, if set mode 7 palette is customised
#define BIT_SET_MODE2_16COLOUR   0x10  // bit 4, if set mode 2 16 colour is enabled
#define BIT_MULTI_PALETTE        0x020   // bit 5  if set then multiple 16 colour palettes

#define VERTICAL_OFFSET         6      // start of actual bbc screen from start of buffer

// Offset definitions
#define NUM_OFFSETS  6

#define BIT_BOTH_BUFFERS (BIT_DRAW_BUFFER | BIT_DISP_BUFFER)

// Define the pixel clock for sampling
#define GPCLK_SOURCE               5      // PLLC (CORE_FREQ * 3)
#define DEFAULT_GPCLK_DIVISOR     12      // 96MHz

// Pi 2/3 Multicore options
#if defined(RPI2) || defined(RPI3)

// Indicate the platform has multiple cores
#define HAS_MULTICORE

#endif

#ifdef __ASSEMBLER__

#define GPFSEL0 (PERIPHERAL_BASE + 0x200000)  // controls GPIOs 0..9
#define GPFSEL1 (PERIPHERAL_BASE + 0x200004)  // controls GPIOs 10..19
#define GPFSEL2 (PERIPHERAL_BASE + 0x200008)  // controls GPIOs 20..29
#define GPSET0  (PERIPHERAL_BASE + 0x20001C)
#define GPCLR0  (PERIPHERAL_BASE + 0x200028)
#define GPLEV0  (PERIPHERAL_BASE + 0x200034)
#define GPEDS0  (PERIPHERAL_BASE + 0x200040)
#define FIQCTRL (PERIPHERAL_BASE + 0x00B20C)

#define INTPEND2 (PERIPHERAL_BASE + 0x00B208)
#define SMICTRL  (PERIPHERAL_BASE + 0x600000)

// Offsets into capture_info_t structure below
#define O_FB_BASE          0
#define O_FB_PITCH         4
#define O_FB_WIDTH         8
#define O_FB_HEIGHT       12
#define O_FB_HEIGHTX2     16
#define O_FB_BPP          20
#define O_CHARS_PER_LINE  24
#define O_NLINES          28
#define O_H_OFFSET        32
#define O_V_OFFSET        36
#define O_NCAPTURE        40
#define O_PALETTE_CONTROL 44
#define O_SAMPLE_WIDTH    48
#define O_H_ADJUST        52
#define O_V_ADJUST        56
#define O_SYNCTYPE        60
#define O_DETSYNCTYPE     64
#define O_CAPTURE_LINE    68

#else

typedef struct {
   unsigned char *fb;  // framebuffer base address
   int pitch;          // framebuffer pitch (in bytes per line)
   int width;          // framebuffer width (in pixels)
   int height;         // framebuffer height (in pixels, after any doubling is applied)
   int heightx2;       // if 1 then double frame buffer height
   int bpp;            // framebuffer bits per pixel (4 or 8)
   int chars_per_line; // active 8-pixel characters per line (83 in Modes 0..6, but 63 in Mode 7)
   int nlines;         // number of active lines to capture each field
   int h_offset;       // horizontal offset (in psync clocks)
   int v_offset;       // vertical offset (in lines)
   int ncapture;       // number of fields to capture, or -1 to capture forever
   int palette_control;// normal / in band data / ntsc artifacting etc
   int sample_width;   // 0(=3 bits) or 1(=6 bits)
   int h_adjust;       // h offset into large frame buffer
   int v_adjust;       // v offset into large frame buffer
   int sync_type;      // expected sync type and polarity
   int detected_sync_type;  // detected sync type and polarity
   int (*capture_line)(); // the capture line function to use
   int px_sampling;    // whether to sample normally, sub-sample or pixel double

} capture_info_t;

typedef struct {
   int clock;                // sample clock frequency (Hz)
   int line_len;             // length of a line (in sample clocks)
   int clock_ppm;            // sample clock frequency (Hz)
   int lines_per_frame;
} clk_info_t;

#endif // __ASSEMBLER__

// Quad Pixel input on GPIOs 2..13
#define PIXEL_BASE   (2)

#define SW1_PIN      (16) // active low
#define SW2_PIN      (26) // active low
#define SW3_PIN      (19) // active low
#define PSYNC_PIN    (17)
#define CSYNC_PIN    (23)
#define MODE7_PIN    (25)
#define GPCLK_PIN    (21)
#define SP_CLK_PIN   (20)
#define SP_CLKEN_PIN (1)
#define SP_DATA_PIN  (0)
#define MUX_PIN      (24)
#define SPARE_PIN    (22)
#define VERSION_PIN  (18) // active low, connects to GSR

// LED1 is left LED, driven by the Pi
// LED2 is the right LED, driven by the CPLD, as a copy of mode 7
// both LEDs are active high
#define LED1_PIN     (27)

#define SW1_MASK      (1U << SW1_PIN)
#define SW2_MASK      (1U << SW2_PIN)
#define SW3_MASK      (1U << SW3_PIN)
#define PSYNC_MASK    (1U << PSYNC_PIN)
#define CSYNC_MASK    (1U << CSYNC_PIN)
#define LED1_MASK     (1U << LED1_PIN)

#define INTERLACED_FLAG (1U << 31)

#define SYNC_BIT_HSYNC_INVERTED   0x01      // bit  0, indicates hsync/composite sync is inverted
#define SYNC_BIT_VSYNC_INVERTED   0x02      // bit  1, indicates vsync is inverted
#define SYNC_BIT_COMPOSITE_SYNC   0x04      // bit  2, indicates composite sync
#define SYNC_BIT_MIXED_SYNC       0x08      // bit  3, indicates H and V syncs eored in CPLD 
#define SYNC_BIT_MASK             0x07      // masks out bit 3

#define MAX_PROFILES 64
#define MAX_SUB_PROFILES 32
#define MAX_PROFILE_WIDTH 32
#define MAX_BUFFER_SIZE 1024
#define DEFAULT_STRING "Default"
#define DEFAULTTXT_STRING "Default.txt"
#define NOT_FOUND_STRING "Not Found"
#define NONE_STRING "None"


// PLLH registers, from:
// https://github.com/F5OEO/librpitx/blob/master/src/gpio.h

#define PLLH_CTRL (0x1160/4)
#define PLLH_FRAC (0x1260/4)
#define PLLH_AUX  (0x1360/4)
#define PLLH_RCAL (0x1460/4)
#define PLLH_PIX  (0x1560/4)
#define PLLH_STS  (0x1660/4)

#define XOSC_CTRL (0x1190/4)
#define XOSC_FREQUENCY 19200000

#define PIXELVALVE2_BASE  (volatile uint32_t *)(PERIPHERAL_BASE + 0x807000)
#define PIXELVALVE2_HORZA (volatile uint32_t *)(PERIPHERAL_BASE + 0x80700c)
#define PIXELVALVE2_HORZB (volatile uint32_t *)(PERIPHERAL_BASE + 0x807010)
#define PIXELVALVE2_VERTA (volatile uint32_t *)(PERIPHERAL_BASE + 0x807014)
#define PIXELVALVE2_VERTB (volatile uint32_t *)(PERIPHERAL_BASE + 0x807018)

#endif
