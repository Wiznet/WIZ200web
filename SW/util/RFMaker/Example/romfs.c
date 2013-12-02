/*
 * This file is automatically created by ROM File Maker
 */
#include <string.h>
#include "romfs.h"

/*
 * File 0 : D:\I2CHIP_TEST_APP\ROMFileMaker\example\Hello.txt
 */
code_area file0data[] = {
0x48,0x65,0x6c,0x6c,0x6f,0x2c,0x20,0x57,0x49,0x5a,0x6e,0x65,0x74,0x2e,
};
static ROMFILE file0entry = { 0, "Hello.txt", 14, (code_area *)file0data };

ROMFILE* romfl_list = &file0entry;



/*
Description  : Search a file from ROM FILE
Argument     : name - file name
               buf - file contents to be return
               len - file length to be return
Return Value : 
Note         : 
*/
u_char search_file(u_char * name, code_area ** buf, u_int * len)
{
	int i;
	ROMFILE *romfs;

	i = 0;

	for (romfs = romfs_list; romfs; romfs = romfs->romfs_next)
	{
		if (!strcmp(name, romfs->romfs_name))
		{
			*len = romfs->romfs_size;
			*buf = romfs->romfs_data;
			return ++i;
		}
	}

	return 0;
}
