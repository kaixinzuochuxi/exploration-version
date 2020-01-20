/* The copyright in this software is being made available under the BSD
* License, included below. This software may be subject to other third party
* and contributor rights, including patent rights, and no such rights are
* granted under this license.
*
* Copyright (c) 2010-2019, ITU/ISO/IEC
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  * Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*/

/** \file     Unit.h
 *  \brief    defines unit as a set of blocks and basic unit types (coding, prediction, transform)
 */


#ifndef __UNIT__
#define __UNIT__




#include "CommonDef.h"
#include "Common.h"
#include "Mv.h"
#include "MotionInfo.h"
#include "ChromaFormat.h"

//#if codingparameters
#include "TypeDef.h"
//#endif
#if intermediate
class Rate
{
public:

  double m_bpp_comp;
  double m_bpp_real;
  int m_bit_comp;
  int m_bit_real;

  Rate() { m_bpp_comp = 0; m_bpp_real = 0; m_bit_comp = 0; m_bit_real = 0; }
  Rate(double bpp_comp, double bpp_real, int bit_comp, int bit_real) { m_bpp_comp = bpp_comp; m_bpp_real = bpp_real; m_bit_comp = bit_comp; m_bit_real = bit_real; }
  Rate(const Rate& R) { m_bpp_comp = R.m_bpp_comp; m_bpp_real = R.m_bpp_real; m_bit_comp = R.m_bit_comp; m_bit_real = R.m_bit_real; }

  void setbppcomp(double bpp_comp) { m_bpp_comp = bpp_comp; }
  void setbppreal(double bpp_real) { m_bpp_real = bpp_real; }
  void setbitcomp(int bit_comp) { m_bit_comp = bit_comp; }
  void setbitreal(int bit_real) { m_bit_real = bit_real; }

  void setall(double bpp_comp, double bpp_real, int bit_comp, int bit_real) { m_bpp_comp = bpp_comp; m_bpp_real = bpp_real; m_bit_comp = bit_comp; m_bit_real = bit_real; }
  void setall(const Rate& R) { m_bpp_comp = R.m_bpp_comp; m_bpp_real = R.m_bpp_real; m_bit_comp = R.m_bit_comp; m_bit_real = R.m_bit_real; }

  double getbppcomp() { return m_bpp_comp; }
  double getbppreal() { return m_bpp_real; }
  int getbitcomp() { return m_bit_comp; }
  int getbitreal() { return m_bit_real; }
};
class coding_para
{

public:
  double m_lambda[MAX_NUM_COMPONENT];
  // COMPONENT_Y, COMPONENT_Cb, COMPONENT_Cr
  int m_QP;

  coding_para() {
    memset(m_lambda, 0, sizeof(m_lambda)); m_QP = 0;
  }
  coding_para(const coding_para& cp) { memcpy(m_lambda, cp.m_lambda, sizeof(m_lambda)); m_QP = cp.m_QP; }

  void setlambda(const double* lambda) { memcpy(m_lambda, lambda, sizeof(m_lambda)); }
  void setqp(int qp) { m_QP = qp; }
  double getlambda(ComponentID ch) { return m_lambda[ch]; }
  int getqp() { return m_QP; }
};

class RCmodel
{
public:
  double m_modelparaA;
  double m_modelparaB;
  double m_SATD;
  RCmodel() { m_modelparaA = 0; m_modelparaB = 0; m_SATD = 0; }


  void setmodelpara(double a, double b) { m_modelparaA = a; m_modelparaB = b; }
  void getmodelpara(double &a, double &b) { a = m_modelparaA; b = m_modelparaB; }
  void setSATD(double satd) { m_SATD = satd; }
  double getSATD() { return m_SATD; }
};
class framelevel
{
public:
  coding_para m_cp;
  Rate m_R;
  RCmodel m_RCmodel;

  framelevel() {};

  // output function
  void output_prefix() { printf(" |[frame_level:\t"); }
  // output cp
  void output_cp_qp() { printf("QP: %d\t", m_cp.getqp()); }
  void output_cp_lambda(ComponentID ch) { printf("lambda: %f\t", m_cp.getlambda(ch)); }
  // output R

  void output_R_bitcomp() { printf("bitcomp: %d\t", m_R.getbitcomp()); }
  void output_R_bitreal() { printf("bitreal: %d\t", m_R.getbitreal()); }
  void output_R_bppcomp() { printf("bppcomp: %f\t", m_R.getbppcomp()); }
  void output_R_bppreal() { printf("bppreal: %f\t", m_R.getbppreal()); }

  // output model para
  void output_RCmodel_modelpara() { double a; double b; m_RCmodel.getmodelpara(a, b); printf(" modelpara: %f %f\t", a, b); }
  void output_RCmodel_SATD() { printf("%f\t", m_RCmodel.getSATD()); }

  void output_suffix() { printf(" ]|\t"); }

  void RC_output() {
    output_prefix();
    output_cp_qp();
    output_cp_lambda(COMPONENT_Y);
    output_R_bitcomp();
    output_R_bitreal();
    output_RCmodel_SATD();
    output_RCmodel_modelpara();
    output_suffix();
  }
};

extern framelevel fl;

class intra_pred
{
public:

};

class inter_pred
{
public:

};


class ctulevel
{
public:
  // source info
  int m_size;
  // R
  Rate m_R;
  RCmodel m_RCmodel;
  coding_para m_cp;

  ctulevel() { m_size = 128; }


  // output function
  void output_prefix() { printf("|[ctu_level:\t"); }
  // output cp
  void output_cp_qp() { printf("QP: %d\t", m_cp.getqp()); }
  void output_cp_lambda(ComponentID ch) { printf("lambda: %f\t", m_cp.getlambda(ch)); }
  // output R

  void output_R_bitcomp() { printf("bitcomp: %d\t", m_R.getbitcomp()); }
  void output_R_bitreal() { printf("bitreal: %d\t", m_R.getbitreal()); }
  void output_R_bppcomp() { printf("bppcomp: %f\t", m_R.getbppcomp()); }
  void output_R_bppreal() { printf("bppreal: %f\t", m_R.getbppreal()); }
  // output model para
  void output_RCmodel_modelpara() { double a; double b; m_RCmodel.getmodelpara(a, b); printf(" modelpara: %f %f\t", a, b); }
  void output_RCmodel_SATD() { printf("%f\t", m_RCmodel.getSATD()); }


  void output_suffix() { printf(" ]|\t"); }

  void RC_output() {
    output_prefix();
    output_cp_qp();
    output_cp_lambda(COMPONENT_Y);
    output_R_bppcomp();
    output_R_bppreal();
    output_RCmodel_SATD();
    output_RCmodel_modelpara();
    output_suffix();
  }

};

extern ctulevel cl;

class culevel {
public:
  Mv mv;

  double intra_cost;
  double inter_cost;


};

extern cul;
#endif


#if codingparameters
class coding_parameterscy
{
public:
  double lambda[3];

  int QP[3];

  uint64_t R_mode;
  //uint64_t R_resi;
  //uint64_t R_luma;
  uint64_t R_resi[MAX_NUM_COMPONENT];
  Distortion D[MAX_NUM_COMPONENT];
  

  coding_parameterscy() {
    memset(lambda, 0, sizeof(lambda));
    memset(QP, 0, sizeof(QP));
    memset(R_resi, 0, sizeof(R_resi));
    memset(D, 0, sizeof(D));
  }

  void initialize() {
    memset(lambda, 0, sizeof(lambda));
    memset(QP, 0, sizeof(QP));
    R_mode = 0;
    //R_resi = 0;
    memset(D, 0, sizeof(D));
    memset(R_resi, 0, sizeof(R_resi));
  }
  void initializeR() {    
    R_mode = 0;
    //R_resi = 0;
    memset(R_resi, 0, sizeof(R_resi));
  }
  void setlambdas(double luma, double cb, double cr) { lambda[0] = luma; lambda[1] = cb; lambda[2] = cr; }

  void setQPs(int QPL, int QPCb, int QPCr) { QP[0] = QPL; QP[1] = QPCb; QP[2] = QPCr; }

  //void updateRlumachroma(uint64_t rluma, uint64_t rchroma) { R_luma = rluma; R_chroma = rchroma; }

  //void updateRmoderesi(uint64_t rmode, uint64_t rresi) { R_mode = rmode; R_resi = rresi; }

  //void updateDlumachroma(Distortion dluma, Distortion dchroma) { D_luma = dluma; D_chroma = dchroma; }
  coding_parameterscy& operator=(const coding_parameterscy& cp) {
    memcpy(lambda, cp.lambda, sizeof(lambda));
    memcpy(QP, cp.QP, sizeof(QP));
    R_mode = cp.R_mode;
    //R_resi = cp.R_resi;
    memcpy(R_resi, cp.R_resi, sizeof(R_resi));
    memcpy(D, cp.D, sizeof(D));
    return *this;
  }
};

extern coding_parameterscy framecp;
extern coding_parameterscy ctucp;
#endif
// ---------------------------------------------------------------------------
// tools
// ---------------------------------------------------------------------------

inline Position recalcPosition(const ChromaFormat _cf, const ComponentID srcCId, const ComponentID dstCId, const Position &pos)
{
  if( toChannelType( srcCId ) == toChannelType( dstCId ) )
  {
    return pos;
  }
  else if (isLuma(srcCId) && isChroma(dstCId))
  {
    return Position(pos.x >> getComponentScaleX(dstCId, _cf), pos.y >> getComponentScaleY(dstCId, _cf));
  }
  else
  {
    return Position(pos.x << getComponentScaleX(srcCId, _cf), pos.y << getComponentScaleY(srcCId, _cf));
  }
}

inline Position recalcPosition( const ChromaFormat _cf, const ChannelType srcCHt, const ChannelType dstCHt, const Position &pos )
{
  if( srcCHt == dstCHt )
  {
    return pos;
  }
  else if( isLuma( srcCHt ) && isChroma( dstCHt ) )
  {
    return Position( pos.x >> getChannelTypeScaleX( dstCHt, _cf ), pos.y >> getChannelTypeScaleY( dstCHt, _cf ) );
  }
  else
  {
    return Position( pos.x << getChannelTypeScaleX( srcCHt, _cf ), pos.y << getChannelTypeScaleY( srcCHt, _cf ) );
  }
}

inline Size recalcSize( const ChromaFormat _cf, const ComponentID srcCId, const ComponentID dstCId, const Size &size )
{
  if( toChannelType( srcCId ) == toChannelType( dstCId ) )
  {
    return size;
  }
  else if( isLuma( srcCId ) && isChroma( dstCId ) )
  {
    return Size( size.width >> getComponentScaleX( dstCId, _cf ), size.height >> getComponentScaleY( dstCId, _cf ) );
  }
  else
  {
    return Size( size.width << getComponentScaleX( srcCId, _cf ), size.height << getComponentScaleY( srcCId, _cf ) );
  }
}

inline Size recalcSize( const ChromaFormat _cf, const ChannelType srcCHt, const ChannelType dstCHt, const Size &size )
{
  if( srcCHt == dstCHt )
  {
    return size;
  }
  else if( isLuma( srcCHt ) && isChroma( dstCHt ) )
  {
    return Size( size.width >> getChannelTypeScaleX( dstCHt, _cf ), size.height >> getChannelTypeScaleY( dstCHt, _cf ) );
  }
  else
  {
    return Size( size.width << getChannelTypeScaleX( srcCHt, _cf ), size.height << getChannelTypeScaleY( srcCHt, _cf ) );
  }
}

// ---------------------------------------------------------------------------
// block definition
// ---------------------------------------------------------------------------

struct CompArea : public Area
{
  CompArea() : Area(), chromaFormat(NUM_CHROMA_FORMAT), compID(MAX_NUM_TBLOCKS)                                                                                                                                 { }
  CompArea(const ComponentID _compID, const ChromaFormat _cf, const Area &_area, const bool isLuma = false)                                          : Area(_area),          chromaFormat(_cf), compID(_compID) { if (isLuma) xRecalcLumaToChroma(); }
  CompArea(const ComponentID _compID, const ChromaFormat _cf, const Position& _pos, const Size& _size, const bool isLuma = false)                    : Area(_pos, _size),    chromaFormat(_cf), compID(_compID) { if (isLuma) xRecalcLumaToChroma(); }
  CompArea(const ComponentID _compID, const ChromaFormat _cf, const uint32_t _x, const uint32_t _y, const uint32_t _w, const uint32_t _h, const bool isLuma = false) : Area(_x, _y, _w, _h), chromaFormat(_cf), compID(_compID) { if (isLuma) xRecalcLumaToChroma(); }

  ChromaFormat chromaFormat;
  ComponentID compID;

  Position chromaPos() const;
  Position lumaPos()   const;

  Size     chromaSize() const;
  Size     lumaSize()   const;

  Position compPos( const ComponentID compID ) const;
  Position chanPos( const ChannelType chType ) const;

  Position topLeftComp    (const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, *this);                                                     }
  Position topRightComp   (const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, { (PosType) (x + width - 1), y                          }); }
  Position bottomLeftComp (const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, { x                        , (PosType) (y + height - 1 )}); }
  Position bottomRightComp(const ComponentID _compID) const { return recalcPosition(chromaFormat, compID, _compID, { (PosType) (x + width - 1), (PosType) (y + height - 1 )}); }

  bool valid() const { return chromaFormat < NUM_CHROMA_FORMAT && compID < MAX_NUM_TBLOCKS && width != 0 && height != 0; }

  const bool operator==(const CompArea &other) const
  {
    if (chromaFormat != other.chromaFormat) return false;
    if (compID       != other.compID)       return false;

    return Position::operator==(other) && Size::operator==(other);
  }

  const bool operator!=(const CompArea &other) const { return !(operator==(other)); }

#if REUSE_CU_RESULTS_WITH_MULTIPLE_TUS
  void     resizeTo          (const Size& newSize)          { Size::resizeTo(newSize); }
#endif
  void     repositionTo      (const Position& newPos)       { Position::repositionTo(newPos); }
  void     positionRelativeTo(const CompArea& origCompArea) { Position::relativeTo(origCompArea); }

private:

  void xRecalcLumaToChroma();
};

inline CompArea clipArea(const CompArea &compArea, const Area &boundingBox)
{
  return CompArea(compArea.compID, compArea.chromaFormat, clipArea((const Area&) compArea, boundingBox));
}

// ---------------------------------------------------------------------------
// unit definition
// ---------------------------------------------------------------------------

typedef static_vector<CompArea, MAX_NUM_TBLOCKS> UnitBlocksType;

struct UnitArea
{
  ChromaFormat chromaFormat;
  UnitBlocksType blocks;

  UnitArea() : chromaFormat(NUM_CHROMA_FORMAT) { }
  UnitArea(const ChromaFormat _chromaFormat);
  UnitArea(const ChromaFormat _chromaFormat, const Area &area);
  UnitArea(const ChromaFormat _chromaFormat, const CompArea  &blkY);
  UnitArea(const ChromaFormat _chromaFormat,       CompArea &&blkY);
  UnitArea(const ChromaFormat _chromaFormat, const CompArea  &blkY, const CompArea  &blkCb, const CompArea  &blkCr);
  UnitArea(const ChromaFormat _chromaFormat,       CompArea &&blkY,       CompArea &&blkCb,       CompArea &&blkCr);

        CompArea& Y()                                  { return blocks[COMPONENT_Y];  }
  const CompArea& Y()                            const { return blocks[COMPONENT_Y];  }
        CompArea& Cb()                                 { return blocks[COMPONENT_Cb]; }
  const CompArea& Cb()                           const { return blocks[COMPONENT_Cb]; }
        CompArea& Cr()                                 { return blocks[COMPONENT_Cr]; }
  const CompArea& Cr()                           const { return blocks[COMPONENT_Cr]; }

        CompArea& block(const ComponentID comp)       { return blocks[comp]; }
  const CompArea& block(const ComponentID comp) const { return blocks[comp]; }

  bool contains(const UnitArea& other) const;
  bool contains(const UnitArea& other, const ChannelType chType) const;

        CompArea& operator[]( const int n )       { return blocks[n]; }
  const CompArea& operator[]( const int n ) const { return blocks[n]; }

  const bool operator==(const UnitArea &other) const
  {
    if (chromaFormat != other.chromaFormat)   return false;
    if (blocks.size() != other.blocks.size()) return false;

    for (uint32_t i = 0; i < blocks.size(); i++)
    {
      if (blocks[i] != other.blocks[i]) return false;
    }

    return true;
  }

#if REUSE_CU_RESULTS_WITH_MULTIPLE_TUS
  void resizeTo    (const UnitArea& unit);
#endif
  void repositionTo(const UnitArea& unit);

  const bool operator!=(const UnitArea &other) const { return !(*this == other); }

  const Position& lumaPos () const { return Y(); }
  const Size&     lumaSize() const { return Y(); }

  const Position& chromaPos () const { return Cb(); }
  const Size&     chromaSize() const { return Cb(); }

  const UnitArea  singleComp(const ComponentID compID) const;
  const UnitArea  singleChan(const ChannelType chType) const;

  const SizeType  lwidth()  const { return Y().width; }  /*! luma width  */
  const SizeType  lheight() const { return Y().height; } /*! luma height */

  const PosType   lx() const { return Y().x; }           /*! luma x-pos */
  const PosType   ly() const { return Y().y; }           /*! luma y-pos */

  bool valid() const { return chromaFormat != NUM_CHROMA_FORMAT && blocks.size() > 0; }
};

inline UnitArea clipArea(const UnitArea &area, const UnitArea &boundingBox)
{
  UnitArea ret(area.chromaFormat);

  for (uint32_t i = 0; i < area.blocks.size(); i++)
  {
    ret.blocks.push_back(clipArea(area.blocks[i], boundingBox.blocks[i]));
  }

  return ret;
}

struct UnitAreaRelative : public UnitArea
{
  UnitAreaRelative(const UnitArea& origUnit, const UnitArea& unit)
  {
    *((UnitArea*)this) = unit;
    for(uint32_t i = 0; i < blocks.size(); i++)
    {
      blocks[i].positionRelativeTo(origUnit.blocks[i]);
    }
  }
};

class SPS;
#if HEVC_VPS
class VPS;
#endif
class PPS;
class Slice;

// ---------------------------------------------------------------------------
// coding unit
// ---------------------------------------------------------------------------

#include "Buffer.h"

struct TransformUnit;
struct PredictionUnit;
class  CodingStructure;

struct CodingUnit : public UnitArea
{
  CodingStructure *cs;
  Slice *slice;
  ChannelType    chType;

  PredMode       predMode;

  uint8_t          depth;   // number of all splits, applied with generalized splits
  uint8_t          qtDepth; // number of applied quad-splits, before switching to the multi-type-tree (mtt)
  // a triple split would increase the mtDepth by 1, but the qtDepth by 2 in the first and last part and by 1 in the middle part (because of the 1-2-1 split proportions)
  uint8_t          btDepth; // number of applied binary splits, after switching to the mtt (or it's equivalent)
  uint8_t          mtDepth; // the actual number of splits after switching to mtt (equals btDepth if only binary splits are allowed)
  int8_t          chromaQpAdj;
  int8_t          qp;
  SplitSeries    splitSeries;
  bool           skip;
  bool           mmvdSkip;
  bool           affine;
  int            affineType;
  bool           triangle;
  bool           transQuantBypass;
  bool           ipcm;
  uint8_t          imv;
  bool           rootCbf;
#if JVET_M0140_SBT
  uint8_t        sbtInfo;
#endif
#if HEVC_TILES_WPP
  uint32_t           tileIdx;
#endif
#if !JVET_M0464_UNI_MTS
  uint8_t          emtFlag;
#endif
  uint8_t         GBiIdx;
  int             refIdxBi[2];
  // needed for fast imv mode decisions
  int8_t          imvNumCand;
#if JVET_M0170_MRG_SHARELIST
  Position       shareParentPos;
  Size           shareParentSize;
#endif
#if JVET_M0483_IBC ==0
  bool           ibc;
#endif
#if JVET_M0444_SMVD
  uint8_t          smvdMode;
#endif
#if JVET_M0102_INTRA_SUBPARTITIONS
  uint8_t        ispMode;
#endif

  CodingUnit() : chType( CH_L ) { }
  CodingUnit(const UnitArea &unit);
  CodingUnit(const ChromaFormat _chromaFormat, const Area &area);

  CodingUnit& operator=( const CodingUnit& other );

  void initData();

  unsigned    idx;
  CodingUnit *next;

  PredictionUnit *firstPU;
  PredictionUnit *lastPU;

  TransformUnit *firstTU;
  TransformUnit *lastTU;
#if ENABLE_SPLIT_PARALLELISM || ENABLE_WPP_PARALLELISM

  int64_t cacheId;
  bool    cacheUsed;
#endif
#if JVET_M0140_SBT
  const uint8_t     getSbtIdx() const { assert( ( ( sbtInfo >> 0 ) & 0xf ) < NUMBER_SBT_IDX ); return ( sbtInfo >> 0 ) & 0xf; }
  const uint8_t     getSbtPos() const { return ( sbtInfo >> 4 ) & 0x3; }
  void              setSbtIdx( uint8_t idx ) { CHECK( idx >= NUMBER_SBT_IDX, "sbt_idx wrong" ); sbtInfo = ( idx << 0 ) + ( sbtInfo & 0xf0 ); }
  void              setSbtPos( uint8_t pos ) { CHECK( pos >= 4, "sbt_pos wrong" ); sbtInfo = ( pos << 4 ) + ( sbtInfo & 0xcf ); }
  uint8_t           getSbtTuSplit() const;
  const uint8_t     checkAllowedSbt() const;
#endif

#if codingparameters
  coding_parameterscy cucp;
  
#endif // codingparameters

  
};

// ---------------------------------------------------------------------------
// prediction unit
// ---------------------------------------------------------------------------

struct IntraPredictionData
{
  uint32_t  intraDir[MAX_NUM_CHANNEL_TYPE];
  int       multiRefIdx;
#if build_cu_tree
  Distortion intradist;
  //Distortion interdist;
  //double cost;
  uint64_t intrabits;
#if predfromori
  Distortion intradistori;
  uint64_t intrabitsori;
#endif
#endif
};

struct InterPredictionData
{
  bool      mergeFlag;
  uint8_t     mergeIdx;
#if JVET_M0883_TRIANGLE_SIGNALING
  uint8_t     triangleSplitDir;
  uint8_t     triangleMergeIdx0;
  uint8_t     triangleMergeIdx1;
#endif
  bool           mmvdMergeFlag;
  uint32_t       mmvdMergeIdx;
  uint8_t     interDir;
  uint8_t     mvpIdx  [NUM_REF_PIC_LIST_01];
  uint8_t     mvpNum  [NUM_REF_PIC_LIST_01];
  Mv        mvd     [NUM_REF_PIC_LIST_01];
  Mv        mv      [NUM_REF_PIC_LIST_01];
  int16_t     refIdx  [NUM_REF_PIC_LIST_01];
  MergeType mergeType;
#if JVET_M0147_DMVR
  bool      mvRefine;
  Mv        mvdL0SubPu[MAX_NUM_SUBCU_DMVR];
#endif
  Mv        mvdAffi [NUM_REF_PIC_LIST_01][3];
  Mv        mvAffi[NUM_REF_PIC_LIST_01][3];
  bool      mhIntraFlag;

#if JVET_M0170_MRG_SHARELIST
  Position  shareParentPos;
  Size      shareParentSize;
#endif
  Mv        bv;                             // block vector for IBC
  Mv        bvd;                            // block vector difference for IBC
#if JVET_M0823_MMVD_ENCOPT
  uint8_t   mmvdEncOptMode;                  // 0: no action 1: skip chroma MC for MMVD candidate pre-selection 2: skip chroma MC and BIO for MMVD candidate pre-selection
#endif
                                             
#if build_cu_tree
  //Distortion intradist;
  Distortion interdist;
  uint64_t interbits;
  Distortion D_currecwoilf_curori_refrec;
  double orisigma;
  double refsigma0;
  double refsigma1;
  double D_refrec_curori_0;
  double D_refrec_curori_1;
#if predfromori
  Distortion interdistori;
  Distortion D_currecwoilf_curori_refori;
  uint64_t interbitsori;
  double reforisigma0;
  double reforisigma1;
  double D_refori_curori_0;
  double D_refori_curori_1;
#endif
  //double cost;
#endif
};

struct PredictionUnit : public UnitArea, public IntraPredictionData, public InterPredictionData
{
  CodingUnit      *cu;
  CodingStructure *cs;
  ChannelType      chType;

  // constructors
  PredictionUnit(): chType( CH_L ) { }
  PredictionUnit(const UnitArea &unit);
  PredictionUnit(const ChromaFormat _chromaFormat, const Area &area);

  void initData();

  PredictionUnit& operator=(const IntraPredictionData& predData);
  PredictionUnit& operator=(const InterPredictionData& predData);
  PredictionUnit& operator=(const PredictionUnit& other);
  PredictionUnit& operator=(const MotionInfo& mi);

  unsigned        idx;
#if JVET_M0170_MRG_SHARELIST
  Position shareParentPos;
  Size     shareParentSize;
#endif

  PredictionUnit *next;

  // for accessing motion information, which can have higher resolution than PUs (should always be used, when accessing neighboring motion information)
  const MotionInfo& getMotionInfo() const;
  const MotionInfo& getMotionInfo( const Position& pos ) const;
  MotionBuf         getMotionBuf();
  CMotionBuf        getMotionBuf() const;

#if ENABLE_SPLIT_PARALLELISM || ENABLE_WPP_PARALLELISM

  int64_t cacheId;
  bool    cacheUsed;
#endif
#if build_cu_tree
  //Distortion intradist;
  //Distortion interdist;
  //double cost;
  
#endif
};

// ---------------------------------------------------------------------------
// transform unit
// ---------------------------------------------------------------------------

struct TransformUnit : public UnitArea
{
  CodingUnit      *cu;
  CodingStructure *cs;
  ChannelType      chType;
 #if JVET_M0427_INLOOP_RESHAPER
  int              m_chromaResScaleInv;
#endif

  uint8_t        depth;
#if JVET_M0464_UNI_MTS
  uint8_t        mtsIdx;
#else
  uint8_t        emtIdx;
#endif
#if JVET_M0140_SBT
  bool           noResidual;
#endif
  uint8_t        cbf        [ MAX_NUM_TBLOCKS ];
  RDPCMMode    rdpcm        [ MAX_NUM_TBLOCKS ];
#if !JVET_M0464_UNI_MTS
  bool         transformSkip[ MAX_NUM_TBLOCKS ];
#endif
  int8_t        compAlpha   [ MAX_NUM_TBLOCKS ];

  TransformUnit() : chType( CH_L ) { }
  TransformUnit(const UnitArea& unit);
  TransformUnit(const ChromaFormat _chromaFormat, const Area &area);

  void initData();

  unsigned       idx;
  TransformUnit *next;
#if JVET_M0102_INTRA_SUBPARTITIONS
  TransformUnit *prev;
#endif

#if printoriresi
  void init(TCoeff **coeffs, Pel **pcmbuf, TCoeff **resiwoq , TCoeff **resiwq, Pel **spresiwoq, Pel **spresiwq);
#else
  //void TransformUnit::init(TCoeff **coeffs, Pel **pcmbuf);
  void init(TCoeff **coeffs, Pel **pcmbuf);
#endif
  

  TransformUnit& operator=(const TransformUnit& other);
  void copyComponentFrom  (const TransformUnit& other, const ComponentID compID);
#if JVET_M0140_SBT
  void checkTuNoResidual( unsigned idx );
#endif

         CoeffBuf getCoeffs(const ComponentID id);
  const CCoeffBuf getCoeffs(const ComponentID id) const;
         PelBuf   getPcmbuf(const ComponentID id);
  const CPelBuf   getPcmbuf(const ComponentID id) const;
#if JVET_M0427_INLOOP_RESHAPER
        int       getChromaAdj( )                 const;
        void      setChromaAdj(int i);
#endif

#if ENABLE_SPLIT_PARALLELISM || ENABLE_WPP_PARALLELISM
  int64_t cacheId;
  bool    cacheUsed;

#endif
#if printoriresi
public:
  TCoeff *m_resiwoq[MAX_NUM_TBLOCKS];
  TCoeff *m_resiwq[MAX_NUM_TBLOCKS];
  Pel *m_spresiwoq[MAX_NUM_TBLOCKS];
  Pel *m_spresiwq[MAX_NUM_TBLOCKS];
#else
private:
#endif
  TCoeff *m_coeffs[ MAX_NUM_TBLOCKS ];
  Pel    *m_pcmbuf[ MAX_NUM_TBLOCKS ];


};

// ---------------------------------------------------------------------------
// Utility class for easy for-each like unit traversing
// ---------------------------------------------------------------------------

#include <iterator>

template<typename T>
class UnitIterator : public std::iterator<std::forward_iterator_tag, T>
{
private:
  T* m_punit;

public:
  UnitIterator(           ) : m_punit( nullptr ) { }
  UnitIterator( T* _punit ) : m_punit( _punit  ) { }

  typedef T&       reference;
  typedef T const& const_reference;
  typedef T*       pointer;
  typedef T const* const_pointer;

  reference        operator*()                                      { return *m_punit; }
  const_reference  operator*()                                const { return *m_punit; }
  pointer          operator->()                                     { return  m_punit; }
  const_pointer    operator->()                               const { return  m_punit; }

  UnitIterator<T>& operator++()                                     { m_punit = m_punit->next; return *this; }
  UnitIterator<T>  operator++( int )                                { auto x = *this; ++( *this ); return x; }
  bool             operator!=( const UnitIterator<T>& other ) const { return m_punit != other.m_punit; }
  bool             operator==( const UnitIterator<T>& other ) const { return m_punit == other.m_punit; }
};

template<typename T>
class UnitTraverser
{
private:
  T* m_begin;
  T* m_end;

public:
  UnitTraverser(                    ) : m_begin( nullptr ), m_end( nullptr ) { }
  UnitTraverser( T* _begin, T* _end ) : m_begin( _begin  ), m_end( _end    ) { }

  typedef T                     value_type;
  typedef size_t                size_type;
  typedef T&                    reference;
  typedef T const&              const_reference;
  typedef T*                    pointer;
  typedef T const*              const_pointer;
  typedef UnitIterator<T>       iterator;
  typedef UnitIterator<const T> const_iterator;

  iterator        begin()        { return UnitIterator<T>( m_begin ); }
  const_iterator  begin()  const { return UnitIterator<T>( m_begin ); }
  const_iterator  cbegin() const { return UnitIterator<T>( m_begin ); }
  iterator        end()          { return UnitIterator<T>( m_end   ); }
  const_iterator  end()    const { return UnitIterator<T>( m_end   ); }
  const_iterator  cend()   const { return UnitIterator<T>( m_end   ); }
};

typedef UnitTraverser<CodingUnit>     CUTraverser;
typedef UnitTraverser<PredictionUnit> PUTraverser;
typedef UnitTraverser<TransformUnit>  TUTraverser;

typedef UnitTraverser<const CodingUnit>     cCUTraverser;
typedef UnitTraverser<const PredictionUnit> cPUTraverser;
typedef UnitTraverser<const TransformUnit>  cTUTraverser;



#endif

