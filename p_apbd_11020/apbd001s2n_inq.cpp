/// <summary>
/// 功能说明：太钢二炼钢工艺路径表查询
/// <version>1.0.0.0</para>
/// <creator>YZ</creator>
/// <history>2023/10/23文件创建</history>
/// </summary>
#include "stdafx.h"


BM2F_ENTERACE(apbd001s2n_inq);


int f_apbd001s2n_inq(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
{
	/*打印程序起止LOG*/
	CTracer log(__FUNCTION__);


	/* 程序内部变量 */
	int doFlag = 0;		//返回值

	/*数据库SQL操作字符串，用于捕获数据库操作异常情况*/
	CString sqlstr = "";
	CString sqlwhere = "";

	/* 业务变量 */
	CString st_no = "";


	//数据库变量
	CDbCommand cmd(conn);


	try
	{
		st_no = bcls_rec->Tables[0].Rows[0]["ST_NO"].ToString().Trim();
		Log::Trace("", __FUNCTION__, "st_no={0} ", st_no);//厂家号
		if (st_no != "")
		{
			sqlwhere += "　AND ST_NO = '" + st_no + "' ";
		}

		sqlstr = " SELECT * FROM TAPBD001S2N　WHERE 1 = 1 ";
		sqlstr = sqlstr + sqlwhere;
		Log::Trace("", __FUNCTION__, "sqlstr={0} ", sqlstr);
		cmd.SetCommandText(sqlstr);
		cmd.ExecuteQuery(bcls_ret->Tables[0]);
		cmd.Close();
	}
	/*捕获数据库操作异常*/
	catch (CDbException& ex)
	{
		CFormattable arguments[] = { ex.GetCode() };
		CMessageFormat::Format(s.msg, _RES("GCRSS0000006")/*数据库处理出错，sqlcode = [{0}]。请联系系统维护人员。*/, arguments, 1);
		CString str = ex.GetMsg() + "\r\n" + sqlstr;
		/*返回前台，与EI.EIInfo对象的sys_info.sysmsg参数对应*/
		strncpy(s.sysmsg, (const char *)str, sizeof(s.sysmsg) - 1);
		s.flag = -1;
		/*数据库异常时返回-1，事务将被回滚*/
		doFlag = -1;
	}
	/*捕获应用错误*/
	catch (CApplicationException& ex)
	{
		s.flag = ex.GetCode();
		doFlag = -1;
	}
	catch (CException& ex)
	{
		strncpy(s.msg, (const char *)ex.GetMsg(), sizeof(s.msg) - 1);
		s.flag = ex.GetCode();
		doFlag = -1;
	}

	s.flag = doFlag;
	return(doFlag);
}

