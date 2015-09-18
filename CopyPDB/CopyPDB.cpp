#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
string getFtpPath(string& sContent)
{
	int nLength = sContent.length();
	int nContinuous = 0;//连续的"\"个数
	bool bStart = false;
	int nStartPos = 0;
	int nEndPos = 0;
	int nFtpPathLength = 0;
	for (int nIndex = 0; nIndex < nLength; ++nIndex)
	{
		if (!bStart)//计算nStartPos
		{
			if (sContent.at(nIndex) == '\\')
			{
				nContinuous++;
			}
			else
			{
				nContinuous = 0;
			}

			if (nContinuous == 2)
			{
				nStartPos = nIndex - 1;
				bStart = true;
			}
		}
		else//计算nEndPos
		{
			if (sContent.at(nIndex) == '\n')
			{
				nEndPos = nIndex;
				break;
			}
		}
	}
	nFtpPathLength = nEndPos - nStartPos;
	string sFtpPath = sContent.substr(nStartPos, nFtpPathLength);
	return sFtpPath;
}

int main()
{
	fstream file;
	string sContent;
	system("getSvnLog.bat > svnLogText.txt");
	file.open("svnLogText.txt");
	if (!file)
	{
		cout << "file open fail" << endl;
	}
	if (!getline(file, sContent, '\r'))
	{
		return -1;
	}
	string sFtpPath = getFtpPath(sContent);
	file.close();
	DeleteFile("svnLogText.txt");
	string sCmd = "xcopy " + sFtpPath + " c:\\tmp /e /i /y /f";
	system(sCmd.c_str());
	system("CopyPDB.bat");
	system("pause");
	return 0;
}


