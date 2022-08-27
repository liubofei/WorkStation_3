#ifndef _INCLUDE_CARDSRV_DMC
#define _INCLUDE_CARDSRV_DMC

//定义输入和输出
#ifdef __IOC0640_EXPORTS
	#define IOC0640_API __declspec(dllexport)
#else
	#define IOC0640_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//中断回调函数指针定义
typedef unsigned int        UINT;
typedef UINT (__stdcall *IOC0640_OPERATE)(void* operate_data);



//---------------------   板卡初始和配置函数  ----------------------
/********************************************************************************
** 函数名称: ioc_board_init
** 功能描述: 控制板初始化，设置初始化和速度等设置
** 输　  入: 无
** 返 回 值: 0：无卡； 1-8：成功(实际卡数) 
**     
*********************************************************************************/
IOC0640_API int __stdcall ioc_board_init(void);

/********************************************************************************
** 函数名称: ioc_board_close
** 功能描述: 关闭所有卡
** 输　  入: 无
** 返 回 值: 无
*********************************************************************************/
IOC0640_API void __stdcall ioc_board_close(void); 

//IO控制函数
IOC0640_API int __stdcall ioc_read_inbit(unsigned short cardno, unsigned short bitno);
IOC0640_API int __stdcall  ioc_read_outbit(unsigned short cardno, unsigned short bitno);
IOC0640_API unsigned long __stdcall ioc_write_outbit(unsigned short cardno, unsigned short bitno,unsigned short on_off);
IOC0640_API unsigned long __stdcall ioc_reverse_outbit(unsigned short cardno, unsigned short bitno,double ms_time);

IOC0640_API long __stdcall ioc_read_inport(unsigned short cardno,unsigned short m_PortNo);
IOC0640_API long __stdcall ioc_read_outport(unsigned short cardno,unsigned short m_PortNo) ;
IOC0640_API unsigned long __stdcall ioc_write_outport(unsigned short cardno,unsigned short m_PortNo, unsigned long port_value);

IOC0640_API unsigned long __stdcall ioc_int_enable(unsigned short cardno, IOC0640_OPERATE funcIntHandler, void* operate_data);
IOC0640_API unsigned long __stdcall ioc_int_disable(unsigned short cardno);

IOC0640_API unsigned long __stdcall ioc_config_intbitmode(unsigned short cardno, unsigned short bitno,unsigned short enable,unsigned short logic);
IOC0640_API unsigned long __stdcall ioc_read_intbitmode(unsigned short cardno, unsigned short bitno,unsigned short *enable,unsigned short *logic);
IOC0640_API int __stdcall ioc_read_intbitstatus(unsigned short cardno, unsigned short bitno);

IOC0640_API unsigned long __stdcall ioc_config_intporten(unsigned short cardno,unsigned short m_PortNo, unsigned long port_en);
IOC0640_API unsigned long __stdcall ioc_config_intportlogic(unsigned short cardno,unsigned short m_PortNo, unsigned long port_logic);

IOC0640_API unsigned long __stdcall ioc_read_intportmode(unsigned short cardno, unsigned short m_PortNo,unsigned long *enable,unsigned long *logic);
IOC0640_API long __stdcall ioc_read_intportstatus(unsigned short cardno,unsigned short m_PortNo);

IOC0640_API unsigned long __stdcall ioc_set_filter(unsigned short cardno, double filter);



#ifdef __cplusplus
}
#endif

#endif 