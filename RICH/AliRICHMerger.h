#ifndef ALIRICHMERGER_H
#define ALIRICHMERGER_H
/* Copyright(c) 1998-2000, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

// #include "AliMerger.h"
// #include "AliMergable.h"

class AliRICHSDigit;
class AliHitMap;

typedef enum {kDigitize=0, kMerge = 1} MergeMode_t;

class AliRICHMerger {
 public:
    
    AliRICHMerger();
    virtual ~AliRICHMerger();
    
    // Compare pad hits
    virtual Bool_t Exists(const AliRICHSDigit * sdigit);
    // Update a pad hit
    virtual  void Update(AliRICHSDigit *sdigit);
    // Create a new hit
    virtual  void CreateNew(AliRICHSDigit *sdigit);

    // Initialize merging and digitisation
    virtual void Init();

    // Do the main work
    void Digitise(Int_t nev,Int_t flag) ;
    
    // Setters -> Later Communication with gAlice 
    void SetSignalEventNumber(Int_t i)     {fEvNrSig = i;}
    void SetBackgroundEventNumber(Int_t i) {fEvNrBgr = i;}    
    void SetBackgroundFileName(char* file) {fFnBgr = file;}        
    void SetMode(MergeMode_t mode) {fMerge = mode;}
	
    enum {kBgTag = -1};
    
 private:    
    // Open the bgr file
    TFile *InitBgr();
 private:
    TTree *fTrH1;                   //! Hits Tree for background event
    TClonesArray *fHitsBgr;         //! List of hits for one track only
    TClonesArray *fSDigitsBgr;      //! List of clusters for one track only
    AliHitMap **fHitMap;            //! pointer to array of pointers to hitmaps
    Int_t fNch;                     //! chamber nr (loop variable)
    Int_t fTrack;                   //! track nr (loop variable)
    Int_t fCharge;                  //! charge generated by fTrack
    Bool_t fSignal;                 //! kTRUE if signal file is processed
    TObjArray *fList;               //! list of AliRICHTransientDigit
    Int_t fCounter;                 //! nr. of AliRICHTransientDigit
    Int_t fDigits[5];               //! array with digits
    Int_t fEvNrSig;                 // signal     event number
    Int_t fEvNrBgr;                 // background event number    
    MergeMode_t fMerge;             // merging type kDigitize, kMerge
    char  *fFnBgr;                  // background file name
    TFile *fBgrFile;                // Pointer to background file
    
    ClassDef(AliRICHMerger,0)
};    
#endif

