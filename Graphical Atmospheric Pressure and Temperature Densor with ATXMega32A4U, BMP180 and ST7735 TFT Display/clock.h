/*                Definitions for Clock System                */ 
  
           
//Signatures for protect I/O

#define CCP_IOREG_gc                                                                 0xD8
#define CCP_SPM_gc                                                                   0x9D


/* CTRL – Control Register Definitions */   

#define CLK_SCLKSEL_gm                                                               0x07
   
#define CLK_SCLKSEL_RC2M_gc                                                          0x00
#define CLK_SCLKSEL_RC32M_gc                                                         0x01
#define CLK_SCLKSEL_RC32K_gc                                                         0x02
#define CLK_SCLKSEL_XOSC_gc                                                          0x03
#define CLK_SCLKSEL_PLL_gc                                                           0x04
                                 

/*PSCTRL – Prescaler Register Definitions */ 
                                            
#define CLK_PSADIV_gm                                                                0x7C

#define CLK_PSBCDIV1_bm                                                              0x02
#define CLK_PSBCDIV0_bm                                                              0x01

#define CLK_PSADIV_1_gc                                                              0x00
#define CLK_PSADIV_2_gc                                                              0x04
#define CLK_PSADIV_4_gc                                                              0x0C
#define CLK_PSADIV_8_gc                                                              0x14
#define CLK_PSADIV_16_gc                                                             0x1C
#define CLK_PSADIV_32_gc                                                             0x24
#define CLK_PSADIV_64_gc                                                             0x2C
#define CLK_PSADIV_128_gc                                                            0x34
#define CLK_PSADIV_256_gc                                                            0x3C
#define CLK_PSADIV_512_gc                                                            0x44

#define CLK_PSBCDIV_1_1_gc                                                           0x00
#define CLK_PSBCDIV_1_2_gc                                                           0x01
#define CLK_PSBCDIV_4_1_gc                                                           0x02
#define CLK_PSBCDIV_2_2_gc                                                           0x03


/* LOCK – Lock Register Definitions */          

#define CLK_LOCK_bm                                                                  0x01


/* RTCCTRL – RTC Control Register Definitions */   
                                                    
#define CLK_RTCEN_bm                                                                 0x01

#define CLK_RTCSRC_gm                                                                0x0E
                                   
#define CLK_RTCSRC_ULP_gc                                                            0x00
#define CLK_RTCSRC_TOSC_gc                                                           0x02
#define CLK_RTCSRC_RCOSC_gc                                                          0x04
#define CLK_RTCSRC_TOSC32_gc                                                         0x0A
#define CLK_RTCSRC_RCOSC32_gc                                                        0x0C
#define CLK_RTCSRC_EXTCLK_gc                                                         0x0E


/* USBCTRL – USB Control Register Definitions */           
                                                    
#define CLK_USBSEN_bm                                                                0x01

#define CLK_USBPSDIV_gm                                                              0x38

#define CLK_USBSRC_gm                                                                0x06
                                                  
#define CLK_USBPSDIV_1_gc                                                            0x00
#define CLK_USBPSDIV_2_gc                                                            0x08
#define CLK_USBPSDIV_4_gc                                                            0x10
#define CLK_USBPSDIV_8_gc                                                            0x18
#define CLK_USBPSDIV_16_gc                                                           0x20
#define CLK_USBPSDIV_32_gc                                                           0x28
                                    
#define CLK_USBSRC_PLL_gc                                                            0x00
#define CLK_USBSRC_RC32M_gc                                                          0x02


/* CTRL – Oscillator Control Register Definitions */
                                    
#define OSC_RC2MEN_bm                                                                0x01
#define OSC_RC32MEN_bm                                                               0x02
#define OSC_RC32KEN_bm                                                               0x04
#define OSC_XOSCEN_bm                                                                0x08
#define OSC_PLLEN_bm                                                                 0x10
                                

/* STATUS – Oscillator Status Register Definitions */
                                    
#define OSC_RC2MRDY_bm                                                               0x01
#define OSC_RC32MRDY_bm                                                              0x02
#define OSC_RC32KRDY_bm                                                              0x04
#define OSC_XOSCRDY_bm                                                               0x08
#define OSC_PLLRDY_bm                                                                0x10

                                          
/* XOSCCTRL – XOSC Control Register Definitions */
                                    
#define OSC_XOSCSEL_EXTCLK_gc                                                        0x00
#define OSC_XOSCSEL_32KHz_gc                                                         0x02
#define OSC_XOSCSEL_XTAL_256CLK_gc                                                   0x03
#define OSC_XOSCSEL_XTAL_1KCLK_gc                                                    0x07
#define OSC_XOSCSEL_XTAL_16KCLK_gc                                                   0x0B
                                                 
#define OSC_XOSCPWR_bm                                                               0x10
                                        
#define OSC_X32KLPM_bm                                                               0x20

#define OSC_FRQRANGE_04TO2_gc                                                        0x00
#define OSC_FRQRANGE_2TO9_gc                                                         0x40
#define OSC_FRQRANGE_9TO12_gc                                                        0x80
#define OSC_FRQRANGE_12TO16_gc                                                       0x0C
                                                 

/* XOSCFAIL – XOSC Failure Detection Register Definitions */ 

#define OSC_XOSCFDEN_bm                                                              0x01
#define OSC_XOSCFDIF_bm                                                              0x02
#define OSC_PLLFDEN_bm                                                               0x04
#define OSC_PLLFDIF_bm                                                               0x08
                                                        
                                    
/* PLLCTRL – PLL Control Register Definitions */    

// OSC_PLLFAC contains the amount of frequency multiplication needed

#define OSC_PLLDIV_bm                                                                0x20
#define OSC_PLLDIV_bp                                                                0x05

#define OSC_PLLSRC_RC2M_gc                                                           0x00
#define OSC_PLLSRC_RC32M_gc                                                          0x80
#define OSC_PLLSRC_XOSC_gc                                                           0xC0
                                                 
  
/* DFLLCTRL – DFLL Control Register Definitions */             
                                            
#define OSC_RC32MCREF_gm                                                             0x06
#define OSC_RC2MCREF_bm                                                              0x01

#define OSC_RC32MCREF_RC32K_gc                                                       0x00
#define OSC_RC32MCREF_XOSC32K_gc                                                     0x03
#define OSC_RC32MCREF_USBSOF_gc                                                      0x04
                                            

//DFLL32M/2M CTRL – DFLL Control Register Definitions
                     
#define DFLL_ENABLE_bm                                                               0x01
#define DFLL_ENABLE_bp                                                               0x00