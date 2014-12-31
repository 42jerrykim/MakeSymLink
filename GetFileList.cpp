//
//  GetFileList.cpp
//  Make Symbolic Link
//
//  Created by Reevid on 2014. 7. 21..
//  Copyright (c) 2014년 Reevid. All rights reserved.
//

#include "GetFileList.h"



CFileList::CFileList()
{
}

CFileList::~CFileList()
{
}

bool CFileList::GetFileList(FILE_LIST& list, string strDir, string strDirSu)
{
    struct stat statinfo;
    memset(&statinfo, 0, sizeof(statinfo));
    lstat(strDir.c_str(), &statinfo);
    
    if(!S_ISDIR(statinfo.st_mode))
    {
        cout<<strDir + " is not directory"<<endl;
        return false;
    }
    
    DIR *dir;
    struct dirent *entry;
    
    if ((dir = opendir(strDir.c_str())) == NULL)
    {
        cout<<strDir + " open error"<<endl;
        return false;
    }
    
    while ((entry = readdir(dir)) != NULL)
    {
        memset(&statinfo, 0, sizeof(statinfo));
        string strFilePath = strDir + "/" + entry->d_name;
        while(strFilePath.find("//") != string::npos)
            strFilePath.replace(strFilePath.find("//"), 2, "/");
        
        lstat(strFilePath.c_str(), &statinfo);
        
        if(S_ISDIR(statinfo.st_mode)) // if path is directory
        {
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            
            list.insert(pair<string, bool>(strFilePath, true));
            
            string pathOfSymbolicLink = "";
            pathOfSymbolicLink = pathOfSymbolicLink + "/Users/reevid/Video/" + strDirSu + entry->d_name;
            
            //cout << strFilePath << " " << temp << endl;
            if (symlink(strFilePath.c_str(), pathOfSymbolicLink.c_str()) != 0) {
                cout << strFilePath << " " << pathOfSymbolicLink << endl;
                perror("symlink() error");
                unlink(strFilePath.c_str());
            }
            //string strSubDir = strDir + "/" + entry->d_name;
            //GetFileList(list, strSubDir);
        }
        else // if path is file
        {
            list.insert(pair<string, bool>(strFilePath, false));
        }
    }
    
    closedir(dir);
    
    return true;
}


void CFileList::ShowFileList(FILE_LIST& list)
{
    FILE_LIST::iterator itr;
    
    for(itr = list.begin(); itr != list.end(); itr++)
    {
        if(itr->second == true) {
            cout<<"[DIRECTORY] " + itr->first<<endl;
        }
        else {
            //cout<<"[FILE]" + itr->first<<endl;
        }
    }
}

//파라미터로 들어온 파일 패스에서 하위에 Movie, Drama, 등과 같은 폴더만 검색한다.
bool CFileList::SearchDirectory(string strDir)
{
    CFileList FileList;
    FILE_LIST file_list;
    string strScrDir = "";
    
    strScrDir = strDir + "Movie/";
    FileList.GetFileList(file_list, strScrDir, "Movie/");
    
    strScrDir = strDir + "Drama/";
    FileList.GetFileList(file_list, strScrDir, "Drama/");
    
    strScrDir = strDir + "Movie Korea/";
    FileList.GetFileList(file_list, strScrDir, "Movie Korea/");
    return 0;
}

bool CFileList::CleanTargetDirectory()
{
    system("exec rm -rdf /Users/reevid/Video/Movie/*");
    system("exec rm -rdf /Users/reevid/Video/Drama/*");
    system("exec rm -rdf /Users/reevid/Video/Movie\\ Korea/*");
    
    return 0;
}