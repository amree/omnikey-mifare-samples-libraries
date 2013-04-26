// Prevent multiple includes
#ifndef __SM5121I_H__
	#define __SM5121I_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include "sm5121.h"

BYTE GetRandomByte();

void sm_create_signature(LPBYTE pbKey);
void sm_create_okdata(LPBYTE pbKey);
void sm_decrypt_okdata();

ULONG sm_check_hdh();
ULONG sm_check_signature();
ULONG sm_check_data();

ULONG sm_init_vars();

#ifdef __cplusplus
}
#endif

#endif
