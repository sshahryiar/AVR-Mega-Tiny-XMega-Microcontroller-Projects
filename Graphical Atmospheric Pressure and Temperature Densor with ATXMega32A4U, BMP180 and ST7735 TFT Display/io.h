/*                Definitions for I/O Ports                */        


/* PINnCTRL – Pin n Configuration Register Definitions */

#define PORT_ISC_BOTHEDGES_gc                                                        0x00
#define PORT_ISC_RISING_gc                                                           0x01
#define PORT_ISC_FALLING_gc                                                          0x02
#define PORT_ISC_LEVEL_gc                                                            0x03
#define PORT_ISC_INPUT_DISABLE_gc                                                    0x07

#define PORT_OPC_TOTEM_gc                                                            0x00
#define PORT_OPC_BUSKEEPER_gc                                                        0x08
#define PORT_OPC_PULLDOWN_gc                                                         0x10
#define PORT_OPC_PULLUP_gc                                                           0x18
#define PORT_OPC_WIREDOR_gc                                                          0x20
#define PORT_OPC_WIREDAND_gc                                                         0x28
#define PORT_OPC_WIREDORPULL_gc                                                      0x30
#define PORT_OPC_WIREDANDPULL_gc                                                     0x38

#define PORT_INVEN_bm                                                                0x40
                                                                
#define PORT_SRLEN_bm                                                                0x80


/* REMAP – Pin Remap Register Definitions */

#define PORT_SPI_bp                                                                  0x05
#define PORT_USART0_bp                                                               0x04
#define PORT_TC0D_bp                                                                 0x03
#define PORT_TC0C_bp                                                                 0x02
#define PORT_TC0B_bp                                                                 0x01
#define PORT_TC0A_bp                                                                 0x00


/* CLKEVOUT – Clock and Event Out Register Definitions */


#define PORTCFG_CLKEVPIN_bp                                                          0x07
#define PORTCFG_CLKEVPIN_bm                                                          0x80

#define PORTCFG_RTCOUT_bm                                                            0x40

#define PORTCFG_EVOUT_gm                                                             0x30

#define PORTCFG_CLKOUTSEL_gm                                                         0x0C
                                                           
#define PORTCFG_CLKOUT_gm                                                            0x03
                                 
#define PORTCFG_EVOUT_PC7_gc                                                         0x10
#define PORTCFG_EVOUT_PD7_gc                                                         0x20
                                               
#define PORTCFG_CLKOUTSEL_CLK1X_gc                                                   0x00
#define PORTCFG_CLKOUTSEL_CLK2X_gc                                                   0x04
#define PORTCFG_CLKOUTSEL_CLK4X_gc                                                   0x08

#define PORTCFG_CLKOUT_PC7_gc                                                        0x01
#define PORTCFG_CLKOUT_PD7_gc                                                        0x02


/* INTCTRL – Interrupt Control Register Definitions */

#define PORT_INT0LVL_gm                                                              0x03
#define PORT_INT1LVL_gm                                                              0x0C

#define PORT_INT0LVL_OFF_gc                                                          0x00
#define PORT_INT0LVL_LO_gc                                                           0x01
#define PORT_INT0LVL_MED_gc                                                          0x02
#define PORT_INT0LVL_HI_gc                                                           0x03

#define PORT_INT1LVL_OFF_gc                                                          0x00
#define PORT_INT1LVL_LO_gc                                                           0x04
#define PORT_INT1LVL_MED_gc                                                          0x08
#define        PORT_INT1LVL_HI_gc                                                    0x0C

                                                            
/* VPCTRLx – Virtual Port-map Control Registers Definitions */                                            

#define PORTCFG_VP02MAP_PORTA_gc                                                     0x00
#define PORTCFG_VP02MAP_PORTB_gc                                                     0x01
#define PORTCFG_VP02MAP_PORTC_gc                                                     0x02
#define PORTCFG_VP02MAP_PORTD_gc                                                     0x03
#define PORTCFG_VP02MAP_PORTE_gc                                                     0x04
#define PORTCFG_VP02MAP_PORTF_gc                                                     0x05
#define PORTCFG_VP02MAP_PORTG_gc                                                     0x06
#define PORTCFG_VP02MAP_PORTH_gc                                                     0x07
#define PORTCFG_VP02MAP_PORTJ_gc                                                     0x08
#define PORTCFG_VP02MAP_PORTK_gc                                                     0x09
#define PORTCFG_VP02MAP_PORTL_gc                                                     0x0A
#define PORTCFG_VP02MAP_PORTM_gc                                                     0x0B
#define PORTCFG_VP02MAP_PORTN_gc                                                     0x0C
#define PORTCFG_VP02MAP_PORTP_gc                                                     0x0D
#define PORTCFG_VP02MAP_PORTQ_gc                                                     0x0E
#define PORTCFG_VP02MAP_PORTR_gc                                                     0x0F

#define PORTCFG_VP13MAP_PORTA_gc                                                     0x00
#define PORTCFG_VP13MAP_PORTB_gc                                                     0x10
#define PORTCFG_VP13MAP_PORTC_gc                                                     0x20
#define PORTCFG_VP13MAP_PORTD_gc                                                     0x30
#define PORTCFG_VP13MAP_PORTE_gc                                                     0x40
#define PORTCFG_VP13MAP_PORTF_gc                                                     0x50
#define PORTCFG_VP13MAP_PORTG_gc                                                     0x60
#define PORTCFG_VP13MAP_PORTH_gc                                                     0x70
#define PORTCFG_VP13MAP_PORTJ_gc                                                     0x80
#define PORTCFG_VP13MAP_PORTK_gc                                                     0x90
#define PORTCFG_VP13MAP_PORTL_gc                                                     0xA0
#define PORTCFG_VP13MAP_PORTM_gc                                                     0xB0
#define PORTCFG_VP13MAP_PORTN_gc                                                     0xC0
#define PORTCFG_VP13MAP_PORTP_gc                                                     0xD0
#define PORTCFG_VP13MAP_PORTQ_gc                                                     0xE0
#define PORTCFG_VP13MAP_PORTR_gc                                                     0xF0