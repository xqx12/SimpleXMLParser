/* 
 * File:   FileUtil.h
 * Author: anantha
 *
 * Created on 8 March, 2012, 9:01 AM
 */

#ifndef FILEUTIL_H
#define	FILEUTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

    FILE* openFile(char* filename);
    void split(FILE* fp,char delimiter);

#ifdef	__cplusplus
}
#endif

#endif	/* FILEUTIL_H */

