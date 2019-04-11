#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

using std::string;

namespace LOGGER
{
	//��־�������ʾ��Ϣ
	static const string strFatalPrefix = "Fatal\t";		//����
	static const string strErrorPrefix = "Error\t";
	static const string strWarningPrefix = "Warning\t";
	static const string strInfoPrefix = "Info\t";			//��Ϣ

	//��־����ö��
	enum EnumLogLevel
	{
		LogLevel_Stop = 0,	//ʲô������¼
		LogLevel_Fatal,		//ֻ��¼���ش���
		LogLevel_Error,		//��¼���ش�����ͨ����
		LogLevel_Warning,	//��¼���ش�����ͨ���󣬾���
		LogLevel_Info		//��¼���ش�����ͨ���󣬾��棬��ʾ��Ϣ(Ҳ����ȫ����¼)
	};

	class CLogger
	{
	public:
		//nLogLevel����־��¼�ĵȼ����ɿ�
		//strLogPath����־Ŀ¼���ɿ�
		//strLogName����־���ƣ��ɿ�
		CLogger(EnumLogLevel nLogLevel = EnumLogLevel::LogLevel_Info, const string strLogPath = "", const string strLogName = "");
		//��������
		virtual ~CLogger();
	public:
		//д���ش�����Ϣ
		void TraceFatal(const char *lpcszFormat, ...);
		//д������Ϣ
		void TraceError(const char *lpcszFormat, ...);
		//д������Ϣ
		void TraceWarning(const char *lpcszFormat, ...);
		//д��ʾ��Ϣ
		void TraceInfo(const char *lpcszFormat, ...);
		//�ı�д��־����
		void ChangeLogLevel(EnumLogLevel nLevel);
		//��ȡ��������·��
		static string GetAppPathA();
		//��ʽ���ַ���
		static string FormatString(const char *lpcszFormat, ...);
	private:
		//д�ļ�����
		void Trace(const string &strLog);
		//��ȡ��ǰϵͳʱ��
		string GetTime();
		//�ļ�ȫ·���õ��ļ���
		const char *path_file(const char *path, char splitter);
	private:
		//д��־�ļ���
		FILE * m_pFileStream;
		//д��־����
		EnumLogLevel m_nLogLevel;
		//��־Ŀ¼
		string m_strLogPath;
		//��־������
		string m_strLogName;
		//��־�ļ�ȫ·��
		string m_strLogFilePath;
		//�߳�ͬ�����ٽ�������
		CRITICAL_SECTION m_cs;
	};
}
