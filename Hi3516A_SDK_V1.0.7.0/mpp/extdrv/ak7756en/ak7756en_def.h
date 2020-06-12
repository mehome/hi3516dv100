#ifndef _INC_AK7756EN_DEF
#define _INC_AK7756EN_DEF

typedef union
{
    struct
    {
        unsigned char reserved1	: 2; //[1..0]
        unsigned char bitfs		: 2;	//[3..2]
        unsigned char ckm 		: 3;	//[6..4]
        unsigned char reserved0	: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register0;

typedef union
{
    struct
    {
        unsigned char reserved3	: 1;	//[0]
        unsigned char dsps		: 3;	//[3..1]
        unsigned char dfs		: 2;	//[5..4]
        unsigned char reserved2	: 1;	//[6]
        unsigned char crce		: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register1;

typedef union
{
    struct
    {
        unsigned char reserved5	: 1;	//[0]
        unsigned char ckrstn	: 1;	//[1]
        unsigned char cpde		: 1;	//[2]
        unsigned char reserved4	: 1;	//[3]
        unsigned char pcm		: 2;	//[5..4]
        unsigned char difi2s	: 1;	//[6]
        unsigned char difpcm	: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register2;

typedef union
{
    struct
    {
        unsigned char reserved8	: 1;	//[0]
        unsigned char ss		: 2;	//[2..1]
        unsigned char reserved7	: 1;	//[3]
        unsigned char bank		: 2;	//[5..4]
        unsigned char reserved6	: 1;	//[6]
        unsigned char wdten		: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register3;

typedef union
{
    struct
    {
        unsigned char reserved10: 1;	//[0]
        unsigned char efen		: 1;	//[1]
        unsigned char wavp		: 2;	//[3..2]
        unsigned char wavm		: 1;	//[4]
        unsigned char reserved9	: 1;	//[5]
        unsigned char dataram	: 1;	//[6]
        unsigned char pomode	: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register4;

typedef union
{
    struct
    {
        unsigned char reserved11	: 1;	//[0]
        unsigned char dif			: 3;	//[3..1]
        unsigned char seldo1		: 2;	//[5..4]
        unsigned char seldo2		: 2;	//[7..6]
    } bit;
    unsigned char b8;
} Control_Register5;

typedef union
{
    struct
    {
        unsigned char reserved13	: 1;	//[0]
        unsigned char dof1			: 3;	//[3..1]
        unsigned char dof2			: 2;	//[5..4]
        unsigned char reserved12	: 2;	//[7..6]
    } bit;
    unsigned char b8;
} Control_Register6;

typedef union
{
    struct
    {
        unsigned char reserved14	: 3;	//[2..0]
        unsigned char pdaout		: 1;	//[3]
        unsigned char out3e			: 1;	//[4]
        unsigned char seldo3		: 1;	//[5]
        unsigned char jx0e			: 1;	//[6]
        unsigned char jx1e			: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register7;

typedef union
{
    struct
    {
        unsigned char reserved15	: 3;	//[2..0]
        unsigned char out1e			: 1;	//[3]
        unsigned char out2e			: 1;	//[4]
        unsigned char lrcken		: 1;	//[5]
        unsigned char bicken		: 1;	//[6]
        unsigned char seldi2		: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register8;

typedef union
{
    struct
    {
        unsigned char reserved16	: 4;	//[3..0]
        unsigned char mdif			: 1;	//[4]
        unsigned char mgain			: 3;	//[7..5]
    } bit;
    unsigned char b8;
} Control_Register9;

typedef union
{
    struct
    {
        unsigned char reserved17	: 1;	//[0]
        unsigned char pmosc			: 1;	//[1]
        unsigned char dsprstn		: 1;	//[2]
        unsigned char crstn			: 1;	//[3]
        unsigned char pmmb			: 1;	//[4]
        unsigned char psdac			: 1;	//[5]
        unsigned char pmdac			: 1;	//[6]
        unsigned char pmadc			: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register10;

typedef union
{
    struct
    {
        unsigned char reserved19	: 1;	//[0]
        unsigned char dls			: 1;	//[1]
        unsigned char reserved18	: 5;	//[6..2]
        unsigned char sto			: 1;	//[7]
    } bit;
    unsigned char b8;
} Control_Register11;


#endif

