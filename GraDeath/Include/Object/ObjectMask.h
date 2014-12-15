#ifndef _OBJECT_MASK_H__
#define _OBJECT_MASK_H__

enum OBJECT_MASK{
	MASK_STAGE = 0x0001,
	MASK_COL_ATK = 0x0002 | MASK_STAGE,
	MASK_COL_DEF = 0x0004 | MASK_STAGE,
	MASK_COL_ATK_DEF = MASK_COL_ATK | MASK_COL_DEF,
	MASK_NON_COL = 0x0000,
};

static int categoryBits[] = {
	MASK_COL_ATK, MASK_COL_DEF, MASK_COL_ATK_DEF, MASK_NON_COL, MASK_STAGE,
};




#endif	// end of ObjectMask