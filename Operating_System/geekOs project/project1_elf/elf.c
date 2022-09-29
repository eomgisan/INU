/*
 * ELF executable loading
 * Copyright (c) 2003, Jeffrey K. Hollingsworth <hollings@cs.umd.edu>
 * Copyright (c) 2003, David H. Hovemeyer <daveho@cs.umd.edu>
 *
 * All rights reserved.
 *
 * This code may not be resdistributed without the permission of the copyright holders.
 * Any student solutions using any of this code base constitute derviced work and may
 * not be redistributed in any form.  This includes (but is not limited to) posting on
 * public forums or web sites, providing copies to (past, present, or future) students
 * enrolled in similar operating systems courses the University of Maryland's CMSC412 course.
 *
 * $Revision: 1.31 $
 *
 */

#include <geekos/errno.h>
//#include <geekos/kassert.h>
#include <geekos/ktypes.h>
#include <geekos/screen.h>      /* for debug Print() statements */
#include <geekos/pfat.h>
#include <geekos/malloc.h>
#include <geekos/string.h>
#include <geekos/user.h>
#include <geekos/fileio.h>
#include <geekos/elf.h>

#include <geekos/paging.h>

int elfDebug = 0;

/**
 * From the data of an ELF executable, determine how its segments
 * need to be loaded into memory.
 * @param exeFileData buffer containing the executable file
 * @param exeFileLength length of the executable file in bytes
 * @param exeFormat structure describing the executable's segments
 *   and entry address; to be filled in
 * @return 0 if successful, < 0 on error
 */
int Parse_ELF_Executable(char *exeFileData, ulong_t exeFileLength,
                         struct Exe_Format *exeFormat) {
	
	programHeader *pPH;
	elfHeader *pEH;
	int EmptySegment = 0;
	int i;
	struct Exe_Segment *pES;

	pEH = (elfHeader *)exeFileData;
	pPH = (programHeader *)(exeFileData + pEH->phoff);
	pES = exeFormat->segmentList;

	if(exeFileData == 0) {
		Print("exeFileData = 0");
		return -1;
	}

	if(!((pEH->ident[0] == 0x7f)||(pEH->ident[1]=='E')||(pEH->ident[2]=='L')||(pEH->ident[3]=='F'))){
		Print("ident is not ELF!");
		return -1;
	}
	
	if(pEH->type==0){
		Print(" not exist type");
		return -1;
	}

	if(pEH->machine == 0){
		Print("not exist machine");
		return -1;
	}

	if(pEH->version==0){
		Print("can not match the version");
		return -1;
	}

	if(pEH->entry ==0){
		Print("not exist entry");
		return -1;
	}

	if(pEH->phoff ==0){
		Print("not exist program header table");
		return -1;
	}

	if(pEH->sphoff == 0){
		Print("not exist section header table");
		return -1;
	}

	if(pEH->phnum > EXE_MAX_SEGMENTS){
		Print("!= segment #");
		return -1;
	}

	for(i=0;i<pEH->phnum;i++){
		if(pEH->phentsize == 0){
			pES += 1;
			EmptySegment += 1;
			pPH += 1;
		}
		else{
			pES->startAddress = pPH->vaddr;
			pES->sizeInMemory = pPH->memSize;
			pES->lengthInFile = pPH->fileSize;
			pES->offsetInFile = pPH->offset;
			pES->protFlags = pPH->flags;
			pES += 1;
			pPH += 1;
		}
	}
	exeFormat->entryAddr = pEH->entry;
	exeFormat->numSegments = pEH->phnum - EmptySegment;

	
	return 0;
}

