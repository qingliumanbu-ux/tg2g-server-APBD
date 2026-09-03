/// <summary>
/// 功能说明：太钢二炼钢工艺路径表新增
/// <version>1.0.0.0</para>
/// <creator>YZ</creator>
/// <history>2023/10/23文件创建</history>
/// </summary>
#include "stdafx.h"
#include "tapbd008s2n.h"
BM2F_ENTERACE(apbd008s2n_upd);


int f_apbd008s2n_upd(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
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
	CString datetimeNow = CDateTime::Now().ToString("yyyyMMddHHmmss");

	//数据库变量
	CDbCommand cmd(conn);
	CTAPBD008S2N tapbd008s2n(conn);
	try
	{
		for (int i = 0; i < bcls_rec->Tables["TAPBD008S2N"].Rows.get_Count(); i++)
		{
			//工艺路径表
			tapbd008s2n.Reset();
			tapbd008s2n.MergeFrom(bcls_rec->Tables[0].Rows[i]);
			tapbd008s2n.REC_REVISE_TIME = datetimeNow;
			tapbd008s2n.REC_REVISOR = s.userid;
			tapbd008s2n.Update("*", "DEV_CODE");
		}

	}
	/*捕获数据库操作异常*/
	catch (CDbException& ex)
	{
		CFormattable arguments[] = { ex.GetCode() };
		CMessageFormat::Format(s.msg, _RES("GCRSS0000008")/*数据库处理出错，sqlcode = [{0}]。请联系系统维护人员。*/, arguments, 1);
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

