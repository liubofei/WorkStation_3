#pragma once
#ifndef _OCTOPUS_COMMON_ERROR_H
#define _OCTOPUS_COMMON_ERROR_H

//错误代码
enum EM_ERR_CODE
{
	ERR_INPUT_PARAM = -1000,        //入参为空或者不合法

	//comm err
	ERR_TIMEOUT,                    //等待超时
	ERR_NO_CONNECT,                 //未连接
	ERR_NOINIT_COMM,                //未初始化comm库
	ERR_NO_REG,                     //未注册
	ERR_REPEAT_REG,                 //重复注册
	ERR_DATA_OVERLIMIT,             //数据溢出
	ERR_INVALID_ID,                 //此ID不存在，或者不合法
	ERR_NO_NAME,                    //该名称不存在
	ERR_NAME_EXIST,                 //该名称已经存在
	ERR_CFG_ACTION,                 //配置文件读取/写入错误
	ERR_CFG_DATA,                   //配置文件错误

	//NetWork
	ERR_NOINIT,						//未初始化
	ERR_INVALID_IP,                 //无效IP
	ERR_INVALID_PORT,               //无效端口
	ERR_INVALID_SOCKET,             //无效句柄
	ERR_CONN_CLOSE,					//连接断开
	ERR_LISTEN,						//socket监听失败
	ERR_ACCEPT,						//接受连接失败
	ERR_CONNECT,					//连接服务端失败
	ERR_RECV_MSG,                   //接收消息出错
	ERR_SEND_MSG,                   //发送消息出错
	ERR_GET_SKTINFO,                //获取socket信息(ip,port)
	ERR_SEND_CHECK,                 //发送校验失败

	//user
	ERR_NOINIT_USER,                //未初始化user库
	ERR_NO_LOGIN,                   //未登录
	ERR_NO_LIMIT,                   //无权限
	ERR_INVALID_PWD,                //密码无效
	ERR_LIMIT_OVER,                 //权限设置只有32位，超限了

	//cntl
	ERR_NOINIT_CNTL,                //未初始化串口库
	ERR_OPEN_COM,                   //打开串口失败
	ERR_INVALID_COM,                //无效的串口句柄
	ERR_COM_WRITE,                  //设置/写入串口错误

	//motor err
	ERR_MOTOR_API,                  //控制卡接口命令返回错误
	ERR_NO_CARD,                    //控制卡不存在，或者无卡
	ERR_CARD_EXIST,                 //控制卡已经存在
	ERR_LOAD_CFG,                   //加载配置文件失败
	ERR_INIT_MOTOR,                 //初始化控制卡失败
	ERR_INVALID_AXIS,               //无效轴
	ERR_INVALID_CARD,               //无效卡
	ERR_INVALID_EXT,                //无效的IO模块(卡自带或扩展模块)
	ERR_NOINIT_MOTOR,               //未初始化控制卡
	ERR_AXIS_HOME,                  //轴回原失败
	ERR_SET_HOMEPOS,                //设置原点位置失败
	ERR_AXIS_MOVING,                //轴正在运动中
	ERR_GET_CURPOS,                 //获取当前位置失败
	ERR_CARD_RESET,                 //卡复位失败
	ERR_AXIS_RESET,                 //轴复位失败
	ERR_AXIS_TRAP,                  //轴点位运动失败
	ERR_AXIS_CAPTURE,               //硬件捕获模式失败
	ERR_AXIS_GEAR,                  //跟随模式运动失败
	ERR_SET_CRD,                    //建立坐标系失败
	ERR_CRD_OVERLIMIT,              //坐标系超过2个
	ERR_GET_CRD,                    //获取坐标系失败
	ERR_ARC_MOVE,                   //圆弧插补不合法，数据错误
	ERR_CRD_MOVE,                   //坐标系运动失败
	ERR_IO_TYPE,                    //io类型错误
	ERR_WRITE_IO,                   //写入io失败

	//control err
	ERR_NOINIT_CONTROL,             //未初始化control库
	ERR_MOVE_OVERLIMIT,             //运动超限
	ERR_OCCUPY_IO,                  //IO被占用
	ERR_OCCUPY_AXIS,                //轴被占用
	ERR_STATION_NOREADY,            //工站未就绪
	ERR_ROBOT_EXEC,                 //robot指令返回失败
	ERR_ROBOT_CONNECT,              //机器人通讯错误

	//ops error
	ERR_PROC_NOREADY,               //流程未就绪
	ERR_VISION_CONN,                //视觉连接错误
	ERR_VISION_GR,                  //视觉处理失败
	ERR_SYS_NOREADY,                //系统未就绪

	//公共错误
	ERR_ERROR,

    ERR_EM_MAX,                     //最大值,不是错误码
    RETURN_OK = 0,                  //正常返回
};

#endif  //防止重复包含