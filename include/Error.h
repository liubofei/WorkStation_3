#pragma once
#ifndef _OCTOPUS_COMMON_ERROR_H
#define _OCTOPUS_COMMON_ERROR_H

//�������
enum EM_ERR_CODE
{
	ERR_INPUT_PARAM = -1000,        //���Ϊ�ջ��߲��Ϸ�

	//comm err
	ERR_TIMEOUT,                    //�ȴ���ʱ
	ERR_NO_CONNECT,                 //δ����
	ERR_NOINIT_COMM,                //δ��ʼ��comm��
	ERR_NO_REG,                     //δע��
	ERR_REPEAT_REG,                 //�ظ�ע��
	ERR_DATA_OVERLIMIT,             //�������
	ERR_INVALID_ID,                 //��ID�����ڣ����߲��Ϸ�
	ERR_NO_NAME,                    //�����Ʋ�����
	ERR_NAME_EXIST,                 //�������Ѿ�����
	ERR_CFG_ACTION,                 //�����ļ���ȡ/д�����
	ERR_CFG_DATA,                   //�����ļ�����

	//NetWork
	ERR_NOINIT,						//δ��ʼ��
	ERR_INVALID_IP,                 //��ЧIP
	ERR_INVALID_PORT,               //��Ч�˿�
	ERR_INVALID_SOCKET,             //��Ч���
	ERR_CONN_CLOSE,					//���ӶϿ�
	ERR_LISTEN,						//socket����ʧ��
	ERR_ACCEPT,						//��������ʧ��
	ERR_CONNECT,					//���ӷ����ʧ��
	ERR_RECV_MSG,                   //������Ϣ����
	ERR_SEND_MSG,                   //������Ϣ����
	ERR_GET_SKTINFO,                //��ȡsocket��Ϣ(ip,port)
	ERR_SEND_CHECK,                 //����У��ʧ��

	//user
	ERR_NOINIT_USER,                //δ��ʼ��user��
	ERR_NO_LOGIN,                   //δ��¼
	ERR_NO_LIMIT,                   //��Ȩ��
	ERR_INVALID_PWD,                //������Ч
	ERR_LIMIT_OVER,                 //Ȩ������ֻ��32λ��������

	//cntl
	ERR_NOINIT_CNTL,                //δ��ʼ�����ڿ�
	ERR_OPEN_COM,                   //�򿪴���ʧ��
	ERR_INVALID_COM,                //��Ч�Ĵ��ھ��
	ERR_COM_WRITE,                  //����/д�봮�ڴ���

	//motor err
	ERR_MOTOR_API,                  //���ƿ��ӿ�����ش���
	ERR_NO_CARD,                    //���ƿ������ڣ������޿�
	ERR_CARD_EXIST,                 //���ƿ��Ѿ�����
	ERR_LOAD_CFG,                   //���������ļ�ʧ��
	ERR_INIT_MOTOR,                 //��ʼ�����ƿ�ʧ��
	ERR_INVALID_AXIS,               //��Ч��
	ERR_INVALID_CARD,               //��Ч��
	ERR_INVALID_EXT,                //��Ч��IOģ��(���Դ�����չģ��)
	ERR_NOINIT_MOTOR,               //δ��ʼ�����ƿ�
	ERR_AXIS_HOME,                  //���ԭʧ��
	ERR_SET_HOMEPOS,                //����ԭ��λ��ʧ��
	ERR_AXIS_MOVING,                //�������˶���
	ERR_GET_CURPOS,                 //��ȡ��ǰλ��ʧ��
	ERR_CARD_RESET,                 //����λʧ��
	ERR_AXIS_RESET,                 //�Ḵλʧ��
	ERR_AXIS_TRAP,                  //���λ�˶�ʧ��
	ERR_AXIS_CAPTURE,               //Ӳ������ģʽʧ��
	ERR_AXIS_GEAR,                  //����ģʽ�˶�ʧ��
	ERR_SET_CRD,                    //��������ϵʧ��
	ERR_CRD_OVERLIMIT,              //����ϵ����2��
	ERR_GET_CRD,                    //��ȡ����ϵʧ��
	ERR_ARC_MOVE,                   //Բ���岹���Ϸ������ݴ���
	ERR_CRD_MOVE,                   //����ϵ�˶�ʧ��
	ERR_IO_TYPE,                    //io���ʹ���
	ERR_WRITE_IO,                   //д��ioʧ��

	//control err
	ERR_NOINIT_CONTROL,             //δ��ʼ��control��
	ERR_MOVE_OVERLIMIT,             //�˶�����
	ERR_OCCUPY_IO,                  //IO��ռ��
	ERR_OCCUPY_AXIS,                //�ᱻռ��
	ERR_STATION_NOREADY,            //��վδ����
	ERR_ROBOT_EXEC,                 //robotָ���ʧ��
	ERR_ROBOT_CONNECT,              //������ͨѶ����

	//ops error
	ERR_PROC_NOREADY,               //����δ����
	ERR_VISION_CONN,                //�Ӿ����Ӵ���
	ERR_VISION_GR,                  //�Ӿ�����ʧ��
	ERR_SYS_NOREADY,                //ϵͳδ����

	//��������
	ERR_ERROR,

    ERR_EM_MAX,                     //���ֵ,���Ǵ�����
    RETURN_OK = 0,                  //��������
};

#endif  //��ֹ�ظ�����