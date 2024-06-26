// @(#)root/gl:$Id$
// Author: Matevz Tadel 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TH3GL
#define ROOT_TH3GL

#include "TGLPlot3D.h"
#include <TGLUtil.h>
#include <TGLAxisPainter.h>

class TPolyMarker3D;
class TGLRnrCtx;
class TH3;
class TAxis;

class TH3;

class TH3GL : public TGLPlot3D
{
private:
   TH3GL(const TH3GL&) = delete;
   TH3GL& operator=(const TH3GL&) = delete;

protected:
   TH3                *fM;  // Model object dynamic-casted to TH3.

public:
   TH3GL();
   TH3GL(TH3 *h, TPolyMarker3D *pm);
   ~TH3GL() override;

   Bool_t SetModel(TObject* obj, const Option_t *opt = nullptr) override;
   void   SetBBox() override;

   void DirectDraw(TGLRnrCtx & rnrCtx) const override;

   // To support two-level selection
   // virtual Bool_t SupportsSecondarySelect() const { return kTRUE; }
   // virtual void ProcessSelection(TGLRnrCtx & rnrCtx, TGLSelectRecord & rec);

   ClassDefOverride(TH3GL, 0); // GL renderer class for TH3.
};

#endif
