

#ifndef DATA_TYPES_IL_INCLUDED
#define DATA_TYPES_IL_INCLUDED


	typedef struct{
		int (*defaultFsearch)    (void *ail, uint id, uint value);
		int (*defaultIntersect2) (void *ail, uint id1, uint id2, uint *noccs, uint **occs );
		int (*defaultIntersectN) (void *ail, uint *ids, uint nids, uint *noccs, uint **occs );
	}tdefFunctions;
	
		
	typedef struct {	
		uint nlists;		    //number of posting lists (equals to maxID+1)
		uint maxPostingValue;   //maximum value in any posting list (given as a source parameter)
		uint sizeUncompressed;	//size of the index-assuming an uncompressed representation (uint **)

		uint *lenList;		//len of each list

		uint sampleK;		// sample over the occurrences of each word (parameter for sampling)
		uint *occs;			// ptr to the begining of the occs of word i in zoneOccs.				
		uint *bcsptr;		// ptr to the begining of the bcs of word i in bcs.		
		uint *zoneOccs;		//bitVector with buckets [Abs|bcOff][Abs|bcOff]...
		uint zoneOccsSize;	//in bits

		uint *zoneBitmaps;	//bitMap representing a large posting list (with maxPostingValue elements).
		uint bits_bitmaps;  //bits used by each bitmap
		uint ints_bitmaps_aligned ;  //uints needed by each bitmap, for them to be W-aligned into zoneOccs.
		uint numBitmaps;	//in number of ids treated as bitmaps.
		uint lenBitmapThreshold;   // such that list i receives bitmap if lenlist[i]> threshold.
				
		uint numBuckets;	//in numberOfBuckets

		uint occsBucketSize;// kbits (bits offset into zoneMem)
		uint absOffsetSize; // kbits (bits to represent a jump)
		uint bcOffsetSize;  // kbits (bits for a ptr to bcsZone)
				
		byte *bcs;			// byteCodes with differential encoding of gaps.
		uint bcsSize;		// in bytes

		tdefFunctions defs; // functions used: fsearch /intersect2 / intersectN.

		//keeps info of the previous search --> speeding up searches ??
		uint sampleP;
		uint i;	//  position in the top level structure.
		uint bcpos; //  position inside bcs (botton level containing the compressed d-gaps).
		uint val; // value up to that position
		uint j;
		
	}t_il;


#endif


