#ifndef _INCLUDE_CARDSRV_DMC
#define _INCLUDE_CARDSRV_DMC

//������������
#ifdef __IOC0640_EXPORTS
	#define IOC0640_API __declspec(dllexport)
#else
	#define IOC0640_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//�жϻص�����ָ�붨��
typedef unsigned int        UINT;
typedef UINT (__stdcall *IOC0640_OPERATE)(void* operate_data);



//---------------------   �忨��ʼ�����ú���  ----------------------
/********************************************************************************
** ��������: ioc_board_init
** ��������: ���ư��ʼ�������ó�ʼ�����ٶȵ�����
** �䡡  ��: ��
** �� �� ֵ: 0���޿��� 1-8���ɹ�(ʵ�ʿ���) 
**     
*********************************************************************************/
IOC0640_API int __stdcall ioc_board_init(void);

/********************************************************************************
** ��������: ioc_board_close
** ��������: �ر����п�
** �䡡  ��: ��
** �� �� ֵ: ��
*********************************************************************************/
IOC0640_API void __stdcall ioc_board_close(void); 

//IO���ƺ���
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