//
//  main.c
//  vm_2_hack
//
//  Created by Derrick Ho on 11/28/12.
//  Copyright (c) 2012 Derrick Ho. All rights reserved.
//

#include "vm_2_hack.h"
#include "VM_2_hack_fn_arr.h"

extern int line_cnt;//extern tells compiler that its declared elsewhere
extern char file_name[1024];

int main(int argc, const char * argv[])
{
	char line[1024];
	const int response_SIZE= sizeof(r)/sizeof(response);

	char *s3;
	line_cnt = 0;
	
	if(argc == 3)
		add_bootstrap();//loads the boot stap code
	FILE* f = fopen(argv[1], "r");
//	char * fname_start = argv[1];
	char * fname_start = strdup(argv[1]);
	char * head_ptr = fname_start;
	for ( ;strstr(fname_start, "/");++fname_start){}
	//strcpy(file_name, fname_start);
	sscanf(fname_start, "%[^.]", file_name);
	free(head_ptr);
	while(1==fscanf(f, "%1022[^\r\n]\r\n", line)){
		int i;
		for( i = 0; i < response_SIZE; ++i){
			if(strstr(line, r[i].syntax) &&
			   (strstr(line, r[i].syntax)-line) < strlen(r[i].syntax) ){
				
				s3 = line + strlen(r[i].syntax);
				(r[i].fn_ptr)(s3);

				//printf("@22222//end_%s(%s)\n",r[i].syntax, ++s3);// Debug. dummy A-inst to help visualize end of command
				
				if (strstr(line , "label")) break; else line_cnt++;
				break;
			}
		}
	}
    return 0;
}
