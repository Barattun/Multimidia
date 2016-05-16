#ifndef _HUFF_H_
#define _HUFF_H_

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN extern
#endif


typedef unsigned int u_int32_t;
typedef u_int32_t weight_t;

typedef struct HuffStruct HuffStruct;
typedef struct HuffNode HuffNode;
typedef unsigned char Bit;

typedef struct Block {
    union {
	struct HuffNode* un_leader;
	struct Block* un_freeptr;
    } un;
} Block;


struct HuffNode {
    weight_t Weight;
    struct HuffNode *Parent;
    struct HuffNode *LeftChild;
    struct HuffNode *RightChild;
    struct HuffNode *LeftBlock;
    struct HuffNode *RightBlock;
    Block *MyBlock;
};


struct HuffStruct {
    int AlphabetSize;
    int ZeroFreqCount;
    int ZeroFreqExp;
    int ZeroFreqRem;
    int CodedDepth;

    int IsAdaptive;

    Bit *CodedBits;

    Block *BlockArray;
    Block *FreeBlock;

    HuffNode *DecodePtr;
    HuffNode *RemainingZeros;
    HuffNode *Alphabet;
    HuffNode *RootNode;
    HuffNode *FreeNode;

    const char* Tag;
};


EXTERN HuffStruct* Huff_Initialize_Adaptive_Encoder(const int AlphabetSize);


EXTERN HuffStruct* Huff_Initialize_Fixed_Encoder(const int AlphabetSize,
						 HuffNode* table);


EXTERN HuffStruct* Huff_Initialize_Training_Encoder(const int AlphabetSize,
						    const char* statsfile);


EXTERN int Huff_Encode_Data(HuffStruct* h, int n);


EXTERN Bit Huff_Get_Encoded_Bit(HuffStruct* h);


EXTERN int Huff_Decode_Bit(HuffStruct* h, Bit b);


EXTERN int Huff_Decode_Data(HuffStruct* h);


EXTERN void Huff_Delete(HuffStruct* h);


EXTERN int Huff_Dump_Stats(HuffStruct* H, const char* statsfile);

#endif
