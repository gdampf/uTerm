#line 1 "rcc.c"





















  

#line 1 "vga-min.h"






















  




#line 1 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 985 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdio.h"



 

#line 29 "vga-min.h"
#line 1 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "C:\\CAD\\Keil_v5\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 30 "vga-min.h"

#line 1 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"










































 



 



 
    






  


 
  


 

#line 75 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 

 




 




 




 














 
   








 







 







 


































 
#line 180 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 



 




 





 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  HardFault_IRQn              = -13,     
  SVC_IRQn                    = -5,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

#line 264 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"
 
  WWDG_IRQn                   = 0,       
  RTC_IRQn                    = 2,       
  FLASH_IRQn                  = 3,       
  RCC_IRQn                    = 4,       
  EXTI0_1_IRQn                = 5,       
  EXTI2_3_IRQn                = 6,       
  EXTI4_15_IRQn               = 7,       
  DMA1_Channel1_IRQn          = 9,       
  DMA1_Channel2_3_IRQn        = 10,      
  DMA1_Channel4_5_IRQn        = 11,      
  ADC1_IRQn                   = 12,      
  TIM1_BRK_UP_TRG_COM_IRQn    = 13,      
  TIM1_CC_IRQn                = 14,      
  TIM3_IRQn                   = 16,      
  TIM14_IRQn                  = 19,      
  TIM15_IRQn                  = 20,      
  TIM16_IRQn                  = 21,      
  TIM17_IRQn                  = 22,      
  I2C1_IRQn                   = 23,      
  I2C2_IRQn                   = 24,      
  SPI1_IRQn                   = 25,      
  SPI2_IRQn                   = 26,      
  USART1_IRQn                 = 27,      
  USART2_IRQn                 = 28       
#line 351 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"
} IRQn_Type;



 

#line 1 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"
 







 

























 
























 




 


 

 













#line 110 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"


 







#line 145 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"

#line 147 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"
#line 1 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmInstr.h"
 







 

























 






 



 


 









 







 







 






 








 







 







 









 









 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}










 










 



#line 292 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmInstr.h"


#line 684 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmInstr.h"

   

#line 148 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"
#line 1 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"
 







 

























 






 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}


#line 271 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"


#line 307 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"


#line 634 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cmFunc.h"

 

#line 149 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"








 
#line 174 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"

 






 
#line 190 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"

 










 


 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[1];                  
       uint32_t RESERVED0[31];
  volatile uint32_t ICER[1];                  
       uint32_t RSERVED1[31];
  volatile uint32_t ISPR[1];                  
       uint32_t RESERVED2[31];
  volatile uint32_t ICPR[1];                  
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  volatile uint32_t IP[8];                    
}  NVIC_Type;

 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
       uint32_t RESERVED0;
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
       uint32_t RESERVED1;
  volatile uint32_t SHP[2];                   
  volatile uint32_t SHCSR;                    
} SCB_Type;

 















 



























 















 









 






 



 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 








 
 






 

 










 









 

 



 




 

 
 










 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}







 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}











 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}







 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}







 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] = (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( ((uint32_t)(IRQn) >> 2) )] = (((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( ((uint32_t)(IRQn) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
}












 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) & 0xFF) >> (8 - 2)));  }  
  else {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( ((uint32_t)(IRQn) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) & 0xFF) >> (8 - 2)));  }  
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (1UL << 2));
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 




 

















 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > (0xFFFFFFUL << 0))  return (1);       

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = ticks - 1;                                   
  NVIC_SetPriority (SysTick_IRQn, (1<<2) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 








#line 358 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"
#line 1 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\system_stm32f0xx.h"

























 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 359 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"
#line 360 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



   

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;



    



 

typedef struct
{
  volatile uint32_t ISR;           
  volatile uint32_t IER;           
  volatile uint32_t CR;            
  volatile uint32_t CFGR1;         
  volatile uint32_t CFGR2;         
  volatile uint32_t SMPR;          
  uint32_t   RESERVED1;        
  uint32_t   RESERVED2;        
  volatile uint32_t TR;            
  uint32_t   RESERVED3;        
  volatile uint32_t CHSELR;        
  uint32_t   RESERVED4[5];     
   volatile uint32_t DR;           
} ADC_TypeDef;

typedef struct
{
  volatile uint32_t CCR;
} ADC_Common_TypeDef;




 
typedef struct
{
  volatile uint32_t TIR;   
  volatile uint32_t TDTR;  
  volatile uint32_t TDLR;  
  volatile uint32_t TDHR;  
} CAN_TxMailBox_TypeDef;



 
typedef struct
{
  volatile uint32_t RIR;   
  volatile uint32_t RDTR;  
  volatile uint32_t RDLR;  
  volatile uint32_t RDHR;  
} CAN_FIFOMailBox_TypeDef;
  


 
typedef struct
{
  volatile uint32_t FR1;  
  volatile uint32_t FR2;  
} CAN_FilterRegister_TypeDef;



 
typedef struct
{
  volatile uint32_t              MCR;                  
  volatile uint32_t              MSR;                  
  volatile uint32_t              TSR;                  
  volatile uint32_t              RF0R;                 
  volatile uint32_t              RF1R;                 
  volatile uint32_t              IER;                  
  volatile uint32_t              ESR;                  
  volatile uint32_t              BTR;                  
  uint32_t                   RESERVED0[88];        
  CAN_TxMailBox_TypeDef      sTxMailBox[3];        
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];      
  uint32_t                   RESERVED1[12];        
  volatile uint32_t              FMR;                  
  volatile uint32_t              FM1R;                 
  uint32_t                   RESERVED2;            
  volatile uint32_t              FS1R;                 
  uint32_t                   RESERVED3;            
  volatile uint32_t              FFA1R;                
  uint32_t                   RESERVED4;            
  volatile uint32_t              FA1R;                 
  uint32_t                   RESERVED5[8];         
  CAN_FilterRegister_TypeDef sFilterRegister[28];  
} CAN_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;            
  volatile uint32_t CFGR;          
  volatile uint32_t TXDR;          
  volatile uint32_t RXDR;          
  volatile uint32_t ISR;           
  volatile uint32_t IER;           
}CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t CSR;      
} COMP_TypeDef;




 

typedef struct
{
  volatile uint32_t DR;           
  volatile uint8_t  IDR;          
  uint8_t       RESERVED0;    
  uint16_t      RESERVED1;    
  volatile uint32_t CR;           
  uint32_t      RESERVED2;    
  volatile uint32_t INIT;         
  volatile uint32_t POL;          
} CRC_TypeDef;



 
typedef struct 
{
volatile uint32_t CR;      
volatile uint32_t CFGR;    
volatile uint32_t ISR;     
volatile uint32_t ICR;     
} CRS_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;        
  volatile uint32_t SWTRIGR;   
  volatile uint32_t DHR12R1;   
  volatile uint32_t DHR12L1;   
  volatile uint32_t DHR8R1;    
  volatile uint32_t DHR12R2;   
  volatile uint32_t DHR12L2;   
  volatile uint32_t DHR8R2;    
  volatile uint32_t DHR12RD;   
  volatile uint32_t DHR12LD;   
  volatile uint32_t DHR8RD;    
  volatile uint32_t DOR1;      
  volatile uint32_t DOR2;      
  volatile uint32_t SR;        
} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;        
  volatile uint32_t CR;            
  volatile uint32_t APB1FZ;        
  volatile uint32_t APB2FZ;        
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;           
  volatile uint32_t CNDTR;         
  volatile uint32_t CPAR;          
  volatile uint32_t CMAR;          
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;           
  volatile uint32_t IFCR;          
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;           
  volatile uint32_t EMR;           
  volatile uint32_t RTSR;          
  volatile uint32_t FTSR;          
  volatile uint32_t SWIER;         
  volatile uint32_t PR;            
}EXTI_TypeDef;



 
typedef struct
{
  volatile uint32_t ACR;           
  volatile uint32_t KEYR;          
  volatile uint32_t OPTKEYR;       
  volatile uint32_t SR;            
  volatile uint32_t CR;            
  volatile uint32_t AR;            
  volatile uint32_t RESERVED;      
  volatile uint32_t OBR;           
  volatile uint32_t WRPR;          
} FLASH_TypeDef;




 
typedef struct
{
  volatile uint16_t RDP;           
  volatile uint16_t USER;          
  volatile uint16_t DATA0;         
  volatile uint16_t DATA1;         
  volatile uint16_t WRP0;          
  volatile uint16_t WRP1;          
  volatile uint16_t WRP2;          
  volatile uint16_t WRP3;          
} OB_TypeDef;
  



 

typedef struct
{
  volatile uint32_t MODER;         
  volatile uint16_t OTYPER;        
  uint16_t RESERVED0;          
  volatile uint32_t OSPEEDR;       
  volatile uint32_t PUPDR;         
  volatile uint16_t IDR;           
  uint16_t RESERVED1;          
  volatile uint16_t ODR;           
  uint16_t RESERVED2;          
  volatile uint32_t BSRR;          
  volatile uint32_t LCKR;          
  volatile uint32_t AFR[2];        
  volatile uint16_t BRR;           
  uint16_t RESERVED3;          
}GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t CFGR1;        
       uint32_t RESERVED;     
  volatile uint32_t EXTICR[4];    
  volatile uint32_t CFGR2;        
} SYSCFG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;       
  volatile uint32_t CR2;       
  volatile uint32_t OAR1;      
  volatile uint32_t OAR2;      
  volatile uint32_t TIMINGR;   
  volatile uint32_t TIMEOUTR;  
  volatile uint32_t ISR;       
  volatile uint32_t ICR;       
  volatile uint32_t PECR;      
  volatile uint32_t RXDR;      
  volatile uint32_t TXDR;      
}I2C_TypeDef;




 
typedef struct
{
  volatile uint32_t KR;    
  volatile uint32_t PR;    
  volatile uint32_t RLR;   
  volatile uint32_t SR;    
  volatile uint32_t WINR;  
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CSR;   
} PWR_TypeDef;




 
typedef struct
{
  volatile uint32_t CR;          
  volatile uint32_t CFGR;        
  volatile uint32_t CIR;         
  volatile uint32_t APB2RSTR;    
  volatile uint32_t APB1RSTR;    
  volatile uint32_t AHBENR;      
  volatile uint32_t APB2ENR;     
  volatile uint32_t APB1ENR;     
  volatile uint32_t BDCR;         
  volatile uint32_t CSR;         
  volatile uint32_t AHBRSTR;     
  volatile uint32_t CFGR2;       
  volatile uint32_t CFGR3;       
  volatile uint32_t CR2;         
} RCC_TypeDef;



 

typedef struct
{                           
  volatile uint32_t TR;          
  volatile uint32_t DR;          
  volatile uint32_t CR;          
  volatile uint32_t ISR;         
  volatile uint32_t PRER;        
  volatile uint32_t WUTR;        
       uint32_t RESERVED1;   
  volatile uint32_t ALRMAR;      
       uint32_t RESERVED2;   
  volatile uint32_t WPR;         
  volatile uint32_t SSR;         
  volatile uint32_t SHIFTR;      
  volatile uint32_t TSTR;        
  volatile uint32_t TSDR;        
  volatile uint32_t TSSSR;       
  volatile uint32_t CALR;        
  volatile uint32_t TAFCR;       
  volatile uint32_t ALRMASSR;    
       uint32_t RESERVED3;   
       uint32_t RESERVED4;   
  volatile uint32_t BKP0R;       
  volatile uint32_t BKP1R;       
  volatile uint32_t BKP2R;       
  volatile uint32_t BKP3R;       
  volatile uint32_t BKP4R;       
} RTC_TypeDef;

 




 
  
typedef struct
{
  volatile uint16_t CR1;       
  uint16_t  RESERVED0;     
  volatile uint16_t CR2;       
  uint16_t  RESERVED1;     
  volatile uint16_t SR;        
  uint16_t  RESERVED2;     
  volatile uint16_t DR;        
  uint16_t  RESERVED3;     
  volatile uint16_t CRCPR;     
  uint16_t  RESERVED4;     
  volatile uint16_t RXCRCR;    
  uint16_t  RESERVED5;     
  volatile uint16_t TXCRCR;    
  uint16_t  RESERVED6;      
  volatile uint16_t I2SCFGR;   
  uint16_t  RESERVED7;     
  volatile uint16_t I2SPR;     
  uint16_t  RESERVED8;         
} SPI_TypeDef;




 
typedef struct
{
  volatile uint16_t CR1;              
  uint16_t      RESERVED0;        
  volatile uint16_t CR2;              
  uint16_t      RESERVED1;        
  volatile uint16_t SMCR;             
  uint16_t      RESERVED2;        
  volatile uint16_t DIER;             
  uint16_t      RESERVED3;        
  volatile uint16_t SR;               
  uint16_t      RESERVED4;        
  volatile uint16_t EGR;              
  uint16_t      RESERVED5;        
  volatile uint16_t CCMR1;            
  uint16_t      RESERVED6;        
  volatile uint16_t CCMR2;            
  uint16_t      RESERVED7;        
  volatile uint16_t CCER;             
  uint16_t      RESERVED8;        
  volatile uint32_t CNT;              
  volatile uint16_t PSC;              
  uint16_t      RESERVED10;       
  volatile uint32_t ARR;              
  volatile uint16_t RCR;              
  uint16_t      RESERVED12;       
  volatile uint32_t CCR1;             
  volatile uint32_t CCR2;             
  volatile uint32_t CCR3;             
  volatile uint32_t CCR4;             
  volatile uint16_t BDTR;             
  uint16_t      RESERVED17;       
  volatile uint16_t DCR;              
  uint16_t      RESERVED18;       
  volatile uint16_t DMAR;             
  uint16_t      RESERVED19;       
  volatile uint16_t OR;               
  uint16_t      RESERVED20;       
} TIM_TypeDef;



 
typedef struct
{
  volatile uint32_t CR;         
  volatile uint32_t IER;        
  volatile uint32_t ICR;         
  volatile uint32_t ISR;        
  volatile uint32_t IOHCR;      
  volatile uint32_t RESERVED1;  
  volatile uint32_t IOASCR;     
  volatile uint32_t RESERVED2;  
  volatile uint32_t IOSCR;      
  volatile uint32_t RESERVED3;  
  volatile uint32_t IOCCR;      
  volatile uint32_t RESERVED4;  
  volatile uint32_t IOGCSR;     
  volatile uint32_t IOGXCR[8];  
} TSC_TypeDef;



 
  
typedef struct
{
  volatile uint32_t CR1;      
  volatile uint32_t CR2;      
  volatile uint32_t CR3;     
  volatile uint16_t BRR;     
  uint16_t  RESERVED1;     
  volatile uint16_t GTPR;    
  uint16_t  RESERVED2;   
  volatile uint32_t RTOR;      
  volatile uint16_t RQR;     
  uint16_t  RESERVED3;   
  volatile uint32_t ISR;     
  volatile uint32_t ICR;     
  volatile uint16_t RDR;     
  uint16_t  RESERVED4;   
  volatile uint16_t TDR;     
  uint16_t  RESERVED5;   
} USART_TypeDef;




 
typedef struct
{
  volatile uint32_t CR;    
  volatile uint32_t CFR;   
  volatile uint32_t SR;    
} WWDG_TypeDef;




 
  


 





 




#line 910 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 923 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 932 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"







#line 945 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
  


   

#line 973 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 986 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 1000 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 1007 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 



 
  
  

 
    
 
 
 
 
 
 
 
 
 
#line 1035 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 
#line 1046 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 






 
#line 1085 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 




 



 





 





 



 



 
#line 1138 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 




 
 
 
 
 
 
#line 1162 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1173 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1191 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"











 





 





 
#line 1229 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 












 
#line 1250 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 1390 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1407 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1424 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1441 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1475 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1509 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1543 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1577 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1611 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1645 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1679 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1713 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1747 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1781 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1815 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1849 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1883 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1917 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1951 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 1985 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2019 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2053 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2087 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2121 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2155 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2189 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2223 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2257 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2291 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2325 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2359 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2393 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"


 
 
 
 
 

 




 
#line 2416 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 
#line 2437 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2452 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
 
 
 
 
 
 
#line 2479 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"
 
#line 2499 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
 
 
 
 
 


 


 
#line 2520 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 
 
 
 
 

 
#line 2542 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2554 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2565 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 





 
 
 
 
 
 











































 



 


 


 


 


 



 
 
 
 
 

 


#line 2667 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 
#line 2683 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 





 
 
 
 
 

 
#line 2725 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2755 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2765 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"















 


 


 


 
 
 
 
 
 
#line 2827 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2861 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2885 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2909 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2933 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 2957 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
 
 
 
 

 





 


 


 



                                                               




 






 
#line 3004 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 




#line 3024 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 


 

 



 



 



 



 



 



 
 
 
 
 
 
#line 3114 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3132 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3182 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3232 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3282 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3300 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3318 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3352 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3371 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3381 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3391 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3401 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3411 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3429 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
 
 
 
 

 
#line 3458 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3471 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 




 




 






 






 
#line 3514 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3525 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 


 
 
 
 
 
 


 





 


 




 


 
 
 
 
 

 










 
#line 3586 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 


 





#line 3606 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 

 
 
 
 
 

 
#line 3626 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 








 










 
#line 3661 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"





 













#line 3687 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"





 


 






#line 3717 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 






#line 3740 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"






 
#line 3756 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 3766 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 3793 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3804 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 
#line 3827 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3840 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 
#line 3855 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 
#line 3879 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 












 








   
#line 3914 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 

 
#line 3925 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 
 






#line 3953 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3965 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 3975 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
 
 
 
 
 
#line 4009 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4039 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4064 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 
#line 4085 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 


 
#line 4134 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 



 
#line 4173 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4193 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 
#line 4211 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4226 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4253 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 
#line 4264 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 


 


 


 
 
 
 
 
 
#line 4303 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4321 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4338 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 


 


 
#line 4366 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 




 
 
 
 
 
 
#line 4404 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 







 
#line 4420 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



  
#line 4430 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 4440 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 4450 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 







 
#line 4466 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 4476 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 4486 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 4496 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 







 








 
#line 4521 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 4531 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 






 







 








 








 








 






 





 

 
 
 
 
 
 
















 









#line 4631 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



























 
#line 4676 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4690 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4700 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 




























 





















 




























 





















 
#line 4819 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 


 


 


 


 


 


 
#line 4854 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"





#line 4865 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4873 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

#line 4880 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 





 
 
 
 
 
 
#line 4926 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4950 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 4976 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 



 




 



 






 
#line 5020 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 
#line 5034 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"

 


 


 
 
 
 
 

 
#line 5056 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"



 
#line 5068 "C:\\CAD\\Keil_v5\\ARM\\Inc\\ST\\STM32F0xx\\stm32f0xx.h"







 




 

 

  







 


 









 

  

 

 
#line 32 "vga-min.h"
#line 1 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"
 







 

























 










#line 151 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"



#line 697 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"



#line 33 "vga-min.h"
#line 1 "hardware.h"





















  




#line 1 "gpio.h"





















  






enum GPIO_A_PINS
{ 
	PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,
  PA9=9,PA10=10,PA13=13,PA14=14
};

enum GPIO_B_PINS
{	
	PB1=1
};

enum GPIO_F_PINS
{
	PF0,PF1
};


























#line 28 "hardware.h"

#line 40 "hardware.h"


#line 34 "vga-min.h"

enum DPMS
{ 
	DPMSModeOn,          
  DPMSModeStandby,     
  DPMSModeSuspend,     
  DPMSModeOff          
};

typedef struct
{
	void 			(*VerticalBlank)(void);
	uint8_t		*TextBuffer_Ptr;
	uint16_t	Line;											
	uint8_t		Font_CurRow;							
	uint8_t		Render:1;									
	uint8_t		Display:1;								
	enum DPMS	DPMS_Mode:2;							
	} VGA_t;

extern VGA_t VGA;;
extern uint8_t  TextBuffer[];
extern volatile uint8_t MicroTimer0, MicroTimer1;

void   VGA_Init(void);
void   Delay(uint16_t Ticks);







































































 

#line 148 "vga-min.h"













#line 167 "vga-min.h"

#line 178 "vga-min.h"

#line 189 "vga-min.h"

#line 199 "vga-min.h"






























#line 236 "vga-min.h"

#line 248 "vga-min.h"






#line 25 "rcc.c"
#line 1 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"
 







 

























 










#line 151 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"



#line 697 "C:\\CAD\\Keil_v5\\ARM\\CMSIS\\Include\\core_cm0.h"



#line 26 "rcc.c"



void SystemInit(void)
{
	
	((FLASH_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00002000))->ACR = ((uint32_t)0x00000010) | ((uint32_t)0x00000001);

	

	
	((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CR |= ((uint32_t)0x00010000)|0;
	
	while(!(((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CR & ((uint32_t)0x00020000)))
		 ;
	
	
	((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFGR = ((uint32_t)0x00010000)|((uint32_t)0x00000000);
	((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CR |= ((uint32_t)0x01000000);
	
	
	while(!(((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CR & ((uint32_t)0x02000000)))
		;
	
	((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFGR |= ((uint32_t)0x00000002);
	
	
	while((((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CFGR & ((uint32_t)0x0000000C))!= ((uint32_t)0x00000008))
	 ;
	
	
	((RCC_TypeDef *) ((((uint32_t)0x40000000) + 0x00020000) + 0x00001000))->CR &= ~((uint32_t)0x00000001);
	
#line 77 "rcc.c"
}
