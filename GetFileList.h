//
//  GetFileList.h
//  Make Symbolic Link
//
//  Created by Reevid on 2014. 7. 21..
//  Copyright (c) 2014년 Reevid. All rights reserved.
//

#ifndef __Make_Symbolic_Link__GetFileList__
#define __Make_Symbolic_Link__GetFileList__

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <map>
#include <iterator>
#include <string>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <strings.h>
#include <memory.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <list>
using namespace std;

typedef map<string, bool> FILE_LIST;

class CFileList
{
public:
    list<string> sourceDir;
    list<string> subDir;
    string targetDir;
    
    CFileList();
    ~CFileList();
    
    bool CleanTargetDirectory();
    
    bool GetFileList(FILE_LIST& list, string strDir, string strDirSu); //Get directorys and file list
    void ShowFileList(FILE_LIST& list); //Show file list
    bool SearchDirectory(string strDir);
};





#endif /* defined(__Make_Symbolic_Link__GetFileList__) */
