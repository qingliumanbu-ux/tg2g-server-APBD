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
BM2F_ENTERACE(addplan_col)
int f_addplan_col(EIClass* bcls_rec, EIClass* bcls_ret, CDbConnection* conn)
{
	int doFlag = 0;
	CDbCommand cmd(conn);
	try
	{
		bcls_ret->Tables.Add("DEVCODE");
		bcls_ret->Tables.Add("PATHLIST");
		bcls_ret->Tables.Add("ROUTLIST");
		//最终默认设备
		CString sqlstr = "SELECT b.ROUTELIST,b.DEV_TECH_CODE,a.dev_code  FROM tpssmd7 b LEFT JOIN tpssmd1 a ON a.DEV_TECH_CODE = b.dev_tech_code WHERE b.DEV_TECH_CODE <> 'C' ORDER BY b.ROUTELIST,b.DEV_TECH_CODE,a.dev_code";
		Log::Trace("", __FUNCTION__, "sqlstr={0} ", sqlstr);
		cmd.SetCommandText(sqlstr);
		cmd.ExecuteQuery(bcls_ret->Tables["DEVCODE"]);
		cmd.Close();
		//工艺路线经过的设备
		sqlstr = "SELECT ROUTELIST,CHARGE_NO,DEV_TECH_CODE FROM tpssmd7 ORDER BY ROUTELIST,CHARGE_NO,DEV_TECH_CODE";
		Log::Trace("", __FUNCTION__, "sqlstr={0} ", sqlstr);
		cmd.SetCommandText(sqlstr);
		cmd.ExecuteQuery(bcls_ret->Tables["PATHLIST"]);
		cmd.Close();
		//工艺路线对应的精炼区分
		sqlstr = 
			" SELECT"
			"	ROUTELIST,"
			"	LISTAGG(to_char(T1.DEV_TECH_CODE), '') WITHIN GROUP("
			"	ORDER BY T1.ROUTELIST) AS DEV_TECH_CODE,"
			"		LISTAGG(to_char(T1.CHARGE_NO), '') WITHIN GROUP("
			"	ORDER BY T1.ROUTELIST) AS CHARGE_NO"
			" FROM "
			"	TPSSMD7 T1 "
			" WHERE"
			"	AREA_ID = '4'"
			"	GROUP  BY ROUTELIST "
			"ORDER BY"
			"	ROUTELIST ,CHARGE_NO ";
		Log::Trace("", __FUNCTION__, "sqlstr={0} ", sqlstr);
		cmd.SetCommandText(sqlstr);
		cmd.ExecuteQuery(bcls_ret->Tables["ROUTLIST"]);
		cmd.Close();

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