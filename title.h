#ifndef TITLE_H_
#define TITLE_H_

#include <nn/hid.h>

void Title_Initialize(void);
void Title_Finalize(void);
void Title_Update(nn::hid::PadStatus* pPadStatus);
void Title_Draw(void);

#endif // TITLE_H_
