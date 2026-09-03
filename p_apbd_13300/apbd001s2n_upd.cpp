/// <summary>
/// 功能说明：太钢二炼钢工艺路径表新增
/// <version>1.0.0.0</para>
/// <creator>YZ</creator>
/// <history>2023/10/23文件创建</history>
/// </summary>
#include "stdafx.h"
#include "tapbd001s2n.h"
#include "tapbd002s2n.h"
BM2F_ENTERACE(apbd001s2n_upd);


int f_apbd001s2n_upd(EIClass * bcls_rec, EIClass * bcls_ret, CDbConnection * conn)
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
	CTAPBD001S2N tapbd001s2n(conn);
	CTAPBD002S2N tapbd002s2n(conn);
	try
	{
		if (bcls_rec->Tables["TAPBD001S2N"].Rows.get_Count() > 0)
		{
			for (int i = 0; i < bcls_rec->Tables["TAPBD001S2N"].Rows.get_Count(); i++)
			{
				//工艺路径表
				tapbd001s2n.Reset();
				tapbd001s2n.REC_REVISE_TIME = datetimeNow;
				tapbd001s2n.REC_REVISOR = s.userid;
				tapbd001s2n.ST_NO = bcls_rec->Tables["TAPBD001S2N"].Rows[i]["ST_NO"].ToString();
				tapbd001s2n.ROUTE_TYPE = bcls_rec->Tables["TAPBD001S2N"].Rows[i]["ROUTE_TYPE"].ToString();
				tapbd001s2n.RULE_DESC = bcls_rec->Tables["TAPBD001S2N"].Rows[i]["RULE_DESC"].ToString();
				tapbd001s2n.Update("REC_REVISE_TIME,REC_REVISOR,RULE_DESC,ROUTE_TYPE", "ST_NO");
				Log::Trace("", __FUNCTION__, "tapbd001s2n.ROUTE_TYPE={0} ", tapbd001s2n.ROUTE_TYPE);
				//重点品种等待时间表
				tapbd002s2n.Reset();
				tapbd002s2n.REC_REVISE_TIME = datetimeNow;
				tapbd002s2n.REC_REVISOR = s.userid;
				tapbd002s2n.ST_NO = bcls_rec->Tables["TAPBD001S2N"].Rows[i]["ST_NO"].ToString();
				tapbd002s2n.STD_WAIT_TIME = bcls_rec->Tables["TAPBD001S2N"].Rows[i]["STD_WAIT_TIME"].ToDecimal();
				tapbd002s2n.WAIT_TIME_MAX = bcls_rec->Tables["TAPBD001S2N"].Rows[i]["WAIT_TIME_MAX"].ToDecimal();
				tapbd002s2n.Update("REC_REVISE_TIME,REC_REVISOR,WAIT_TIME_MAX,STD_WAIT_TIME", "ST_NO");
				Log::Trace("", __FUNCTION__, "tapbd001s2n.WAIT_TIME_MAX={0} ", tapbd002s2n.WAIT_TIME_MAX);

			}
		}
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

