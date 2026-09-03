/// <summary>
/// 功能说明:根据路径获取设备
/// </summary>
/// Copyright: Baosight Software LTD.co Copyright (c) 2010
/// Company: 上海宝信软件股份有限公司
/// Author:   项目组
/// Version:  1.0
/// History:  2015-12-2 kimmy [创建]
///          
///	

#include "stdafx.h"
#include "./Be2UserModel/SI/CFormDevConfig.h"

// Service 入口
BM2F_ENTERACE(test)
int f_epex_call_rest_tpsmodel_z_lib(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn);
int f_test(EIClass* bcls_rec, EIClass* bcls_ret, CDbConnection* conn)
{
	int doFlag = 0;
	CDbCommand cmd(conn);
	try
	{
		int i = f_epex_call_rest_tpsmodel_z_lib(bcls_rec, bcls_ret, conn);

	}
	catch (CException& ex)
	{
		strcpy(s.msg, ex.GetMsg());
		EDLog(1, 1, "s.msg = [%s]", s.msg);
		s.flag = -1;
		doFlag = -1;
	}
	return doFlag;
}