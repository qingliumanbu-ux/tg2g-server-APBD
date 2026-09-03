/*************************************************
Copyright: Baosight Software LTD.co Copyright (c) 2024
Author:      195255
Version:     1.0
Date:        2024-05-10 09:27:01
Description: 中频炉模型
**************************************************/

#include "stdafx.h"
#include "./Be2UserModel/SI/CFormDevConfig.h"

int f_epex_call_rest_tpsmodel_z_lib(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn);
// Service 入口
BM2F_ENTERACE(apbd_iff_model)

int f_apbd_iff_model(EIClass* bcls_rec, EIClass* bcls_ret, CDbConnection* conn)
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


