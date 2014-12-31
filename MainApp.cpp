//
//  main.cpp
//  Make Symbolic Link
//
//  Created by Reevid on 2014. 7. 21..
//  Copyright (c) 2014년 Reevid. All rights reserved.
//

#include "GetFileList.h"

int main(int argc, char* argv[])
{
    CFileList FileList;
    FILE_LIST file_list;
    string strSrcDir;
    
    //심볼릭 링크를 저장할 폴더를 지정하고 기존에 있는 내용을 삭제 한다.
    FileList.targetDir = "/Users/reevid/Video/";
    FileList.CleanTargetDirectory();
    
    //해당 디렉토리에서 하위에 있는 폴더를 검색 한다.
    strSrcDir = "/Volumes/2000/";
    FileList.SearchDirectory(strSrcDir);
    
    //FileList.ShowFileList(file_list);
    return 0;
}
