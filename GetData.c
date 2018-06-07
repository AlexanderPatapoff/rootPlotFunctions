#include "Engine.c"

//structure meant to hold data on current scan info TODO: make lumData non static array size
struct ID{
  Float_t scanRun;
  Int_t scanLumBlock;
  Int_t scanStep;
  char plane;
  Float_t planeCoord;
  int beamNumber;
  Float_t lumData [3564];

};

//Graph the IDS   ****NOT MODULABLE**** TODO: ADD FLEXIBILITY
void GraphIDs(Float_t data1[][3],Float_t data2[][3], ID beam1[],ID beam2[]){
  Double_t x[9], y[9],zy[9],zx[9];
  Double_t x2[9], y2[9],zy2[9],zx2[9];
    for (size_t i = 0; i < 9; i++) {
      y[i] = beam1[i].planeCoord-beam2[i].planeCoord;
      zy[i] = data1[i][0] ;
    }
    for (size_t i = 9; i < 18; i++) {
      x[i-9] = beam1[i].planeCoord-beam2[i].planeCoord;
      zx[i-9] = data1[i][0] + data1[i][1] + data1[i][2];
      zx[i-9] += data2[i][0] + data2[i][1] + data2[i][2];
    }


    TCanvas *cx = new TCanvas("cx","xPlaneCollisions",200,10,500,300);
    TGraph* gx = new TGraph(9,x,zx);
    TF1 *f1 = new TF1("f1","gaus",-0.1,0.1);
    gx->Fit("f1","R");
    gx->Draw("AL");
    TCanvas *cy = new TCanvas("cy","yPlaneCollisions",200,340,500,300);
    TGraph* gy = new TGraph(9,y,zy);
    TF1 *f2 = new TF1("f2","gaus",-0.1,0.1);
    gy->Fit("f2","R");
    gy->Draw("AL");



    // for (size_t i = 0; i < 9; i++) {
    //   y2[i] = beam2[i].planeCoord;
    //   zy2[i] = data2[i][0];
    // }
    // for (size_t i = 9; i < 18; i++) {
    //   x2[i-9] = beam2[i].planeCoord;
    //   zx2[i-9] = data2[i][0];
    // }
    //
    //
    //
    // TCanvas *cx2 = new TCanvas("cx2","xPlaneCollisions2",700,10,500,300);
    // TGraph* gx2 = new TGraph(9,x2,zx2);
    // gx2->SetFillColor(40);
    // gx2->Draw("AB");
    // TCanvas *cy2 = new TCanvas("cy2","yPlaneCollisions2",700,340,500,300);
    // TGraph* gy2 = new TGraph(9,y2,zy2);
    // gy2->SetFillColor(40);
    // gy2->Draw("AB");
}

//Writes the ID sturct into console
void printID(ID id){

  cout <<id.scanRun <<" " <<id.scanLumBlock << " "<<id.scanStep << " "<< id.plane<< " "<< id.planeCoord << endl;

}
//NULL
void Test(){
  cout <<"test"<< endl;



}


void compareData(Float_t data1[][3],Float_t data2[][3]){

  for (size_t i = 0; i < 9; i++) {
    cout<< data1[i][0]<< " " << data2[9-i][0]<< endl;
  }
}
//Entry function of the
void GetData(){

   TFile *filein = new TFile("file:~/Downloads/scan.root","READ");
   TTree *tree = (TTree*) filein->Get("vdMScanData;1");
   Int_t nentries = tree->GetEntries();

   ID idEntryB1 [18];
   ID idEntryB2 [18];
  // List<Int_t[]> totalData;
   cout <<"scanRun scanLB scanStep plane planeCoord" << endl;
   for (size_t i = 0; i < nentries; i++) {

     tree->GetEntry(i);
     idEntryB1[i].scanRun = tree->GetLeaf("ScanRun")->GetValue(0);
     idEntryB1[i].scanLumBlock = tree->GetLeaf("ScanLB")->GetValue(0);
     idEntryB1[i].scanStep = tree->GetLeaf("ScanStep")->GetValue(0);
     if( i >= 9)
     {
       idEntryB1[i].plane = 'x';
       idEntryB1[i].planeCoord = tree->GetLeaf("B1DeltaXSet")->GetValue(0);

     }else{
       idEntryB1[i].plane = 'y';
       idEntryB1[i].planeCoord = tree->GetLeaf("B1DeltaYSet")->GetValue(0);
     }

     Int_t nBaskets = tree->GetLeaf("lucBiHitOR_BunchInstLumi")->GetLen();


     for (size_t s = 0; s < nBaskets; s++) {
       idEntryB1[i].lumData[s] = tree->GetLeaf("lucBiHitOR_BunchInstLumi")->GetValue(s);
     }
     printID(idEntryB1[i]);
   }


    cout <<"-----------------------------------------" << endl;
    cout <<"scanRun scanLB scanStep plane planeCoord" << endl;
   for (size_t i = 0; i < nentries; i++) {

     tree->GetEntry(i);
     idEntryB2[i].scanRun = tree->GetLeaf("ScanRun")->GetValue(0);
     idEntryB2[i].scanLumBlock = tree->GetLeaf("ScanLB")->GetValue(0);
     idEntryB2[i].scanStep = tree->GetLeaf("ScanStep")->GetValue(0);
     if( i >= 9)
     {
       idEntryB2[i].plane = 'x';
       idEntryB2[i].planeCoord = tree->GetLeaf("B2DeltaXSet")->GetValue(0);

     }else{
       idEntryB2[i].plane = 'y';
       idEntryB2[i].planeCoord = tree->GetLeaf("B2DeltaYSet")->GetValue(0);
     }

     Int_t nBaskets = tree->GetLeaf("lucBi2HitOR_BunchInstLumi")->GetLen();


     for (size_t s = 0; s < nBaskets; s++) {
       idEntryB2[i].lumData[s] = tree->GetLeaf("lucBi2HitOR_BunchInstLumi")->GetValue(s);
     }

     printID(idEntryB2[i]);

 }
   //GraphIDs(idEntry[4].lumData);


   //cout << tree->GetLeaf("B1BCIDs")->GetValues() << endl;

  Int_t nBaskets = tree->GetLeaf("B1BCIDs")->GetLen();

  Float_t output1 [18][3];

  for (size_t p = 0; p < nBaskets; p++) {
     Int_t temp = tree->GetLeaf("B1BCIDs")->GetValue(p);

     for (size_t l = 0; l < 18; l++){
       output1 [l][p] = idEntryB1[l].lumData[temp];
     }

   }

   nBaskets = tree->GetLeaf("B2BCIDs")->GetLen();

   Float_t output2 [18][3];

   for (size_t p = 0; p < nBaskets; p++) {
      Int_t temp = tree->GetLeaf("B2BCIDs")->GetValue(p);

      for (size_t l = 0; l < 18; l++){
        output2 [l][p] = idEntryB2[l].lumData[temp];
      }

    }




  GraphIDs(output1,output2, idEntryB1,idEntryB2);
  //compareData(output1, output2);


   filein->Close();

}
