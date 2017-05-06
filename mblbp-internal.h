#ifndef __INTERNAL_H__
#define __INTERNAL_H__


#ifdef _OPENMP
#include <omp.h>
#endif


#define __MAX_FACE_NUM__ 4096
#define MBLBP_LUTLENGTH  59

#if MBLBP_LUTLENGTH == 59
static unsigned char LBPMAP[256] = {1,   2,   3,   4,   5,   0,   6,   7,   8,   0,   0,   0,   9,   0,  10,  11,
	12,   0,   0,   0,   0,   0,   0,   0,  13,   0,   0,   0,  14,   0,  15,  16,
	17,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	18,   0,   0,   0,   0,   0,   0,   0,  19,   0,   0,   0,  20,   0,  21,  22,
	23,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	24,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	25,   0,   0,   0,   0,   0,   0,   0,  26,   0,   0,   0,  27,   0,  28,  29,
	30,  31,   0,  32,   0,   0,   0,  33,   0,   0,   0,   0,   0,   0,   0,  34,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  35,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  36,
	37,  38,   0,  39,   0,   0,   0,  40,   0,   0,   0,   0,   0,   0,   0,  41,
	0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  42,
	43,  44,   0,  45,   0,   0,   0,  46,   0,   0,   0,   0,   0,   0,   0,  47,
	48,  49,   0,  50,   0,   0,   0,  51,  52,  53,   0,  54,  55,  56,  57,  58};

#elif MBLBP_LUTLENGTH == 256
static unsigned char LBPMAP[256] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  
    16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  
    32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  
    48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  
    64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  
    80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  
    96,  97,  98,  99,  100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,  
    112,  113,  114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,  
    128,  129,  130,  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,  141,  142,  143,  
    144,  145,  146,  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,  157,  158,  159,  
    160,  161,  162,  163,  164,  165,  166,  167,  168,  169,  170,  171,  172,  173,  174,  175,  
    176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,  
    192,  193,  194,  195,  196,  197,  198,  199,  200,  201,  202,  203,  204,  205,  206,  207,  
    208,  209,  210,  211,  212,  213,  214,  215,  216,  217,  218,  219,  220,  221,  222,  223,  
    224,  225,  226,  227,  228,  229,  230,  231,  232,  233,  234,  235,  236,  237,  238,  239,  
    240,  241,  242,  243,  244,  245,  246,  247,  248,  249,  250,  251,  252,  253,  254,  255};
#else
  #error "LBP table undefinded."
#endif

typedef struct Size{
    int width;
    int height;
}Size;

typedef struct FaceRect{
    short x;
    short y;
    short width;
    short height;
    short neighbors;
    short angle;
} FaceRect;
typedef struct FaceRects{
    int count;
    FaceRect faces[__MAX_FACE_NUM__];
} FaceRects;

typedef struct FaceRectBuf{
    int x; //int type, to avoid overflow
    int y;
    int width;
    int height;
    int neighbors;
    int angle;
} FaceRectBuf;
typedef struct FaceRectsBuf{
    int count;
    FaceRectBuf faces[__MAX_FACE_NUM__];
} FaceRectsBuf;

typedef struct MBLBPWeak_
{
    int x;
    int y;
    int cellwidth;
    int cellheight;
    int soft_threshold;
    int* p[16]; // fast pointer
    int look_up_table[MBLBP_LUTLENGTH]; // look up table
}MBLBPWeak;

typedef struct MBLBPStage_
{
    int count;
    int threshold;
    MBLBPWeak * weak_classifiers;
}MBLBPStage;

typedef struct MBLBPCascade_
{
    int count;
    int win_width;
    int win_height;
    MBLBPStage * stages;
}MBLBPCascade;


#ifndef MIN
#  define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

extern FaceRects       g_faceRects;
extern FaceRectsBuf    g_faceRectsBuf;

Size createSize(int w, int h);
int nearest_pow2_factor(int factor1024x);

void myResize(unsigned char * psrc, int swidth, int sheight, int sstep,
         unsigned char * pdst, int dwidth, int dheight, int dstep);

void GroupRects(FaceRects * pFaces, FaceRectsBuf * pFacesBuf, int min_neighbors);

void MBLBPDetectSingleScale( unsigned char * pimg, int width, int height, int step,
                             MBLBPCascade * pCascade,
                             Size winStride,
                             int factor1024x,
                             int angle = 0,
                             bool isflip = false);


#endif
