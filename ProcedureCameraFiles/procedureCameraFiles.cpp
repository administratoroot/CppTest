#include <iostream>
#include <stdio.h>
#include <io.h>
#include <string>
#include <direct.h> 

//����ļ����Ƿ���ڣ��������򴴽�֮
//�ļ��д��ڷ��� 0
//�ļ��д���ʧ�ܷ���-1
//�ļ��д���ʧ�ܷ���1
int CheckDir(const char* Dir,const char* folderDir)
{
    //CreateDirectory(TEXT("aa"), NULL);
    FILE *fp = NULL;
    char TempDir[200];
    memset(TempDir, '\0', sizeof(TempDir));
    sprintf(TempDir, Dir);
    fp = fopen(TempDir, "w");
    if (!fp)
    {
        if (_mkdir(folderDir) == 0)
        {
            return 1;//�ļ��д����ɹ�
        }
        else
        {
            return -1;//can not make a dir;
        }
    }
    else
    {
        fclose(fp);
    }
    return 0;
}

int procedureFiles()
{
    _finddata_t fileDir;
    std::string baseDir = "F:\\��Ƭ\\";
    std::string dir = "F:\\��Ƭ\\*.JPG";
    long lfDir = -1l;

    if ((lfDir = _findfirst(dir.c_str(), &fileDir)) == -1l)
    {
        std::cout << "No file is found" << std::endl;
    }
    else 
    {
        std::cout << "file list:" << std::endl;
        do
        {
            
            if (strcmp(fileDir.name, ".") == 0|| strcmp(fileDir.name, "..") == 0)
            {
                continue;
            }
            std::cout << fileDir.name << std::endl;
            CFileStatus status = { 0 };
            std::string curFileDir = baseDir + fileDir.name;
            CFile::GetStatus(curFileDir.c_str(), status);
            CString createTime = status.m_ctime.Format("%Y-%m-%d");
            char createDate[100];
            strcpy_s(createDate, createTime);
            std::string curFolderDir = baseDir + createDate;
            CheckDir(baseDir.c_str(), curFolderDir.c_str());
            std::string oldPath = baseDir + fileDir.name;
            std::string newPath = curFolderDir + "\\" + fileDir.name;
            std::string cmd = "move " + oldPath + " " + newPath;
            system(cmd.c_str());
        }while(_findnext(lfDir, &fileDir) == 0);
    }
    _findclose(lfDir);

    return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
    procedureFiles();
	return 0;
}

