#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

void draw_box(double x1, double x2, double y1, double y2, int syes, int col){

   TLine *r_inner = new TLine(x1,y1,x2,y1);
   TLine *r_outer = new TLine(x1,y2,x2,y2);
   TLine *s_up = new TLine(x1,y1,x1,y2);
   TLine *s_down = new TLine(x2,y1,x2,y2);

   r_inner->SetLineColor(col);
   r_outer->SetLineColor(col);
   s_up->SetLineColor(col);
   s_down->SetLineColor(col);

   r_inner->Draw("same");
   r_outer->Draw("same");

   if(syes==0){
     
   }
   else if(syes==1){
     s_up->Draw("same");
     s_down->Draw("same");
   }
   else if(syes==2){
     s_up->Draw("same");
   }
   else if(syes==3){
     s_down->Draw("same");  
   }
}
void draw_pipe(double zup, double l, double r1, double r2, double tr){

   TLine *r_inner = new TLine(zup,r1,zup+l,r2);
   TLine *r_outer = new TLine(zup,r1+tr,zup+l,r2+tr);

   r_inner->Draw("same");
   r_outer->Draw("same");

}
void draw_ray(double x1, double x2, double y1, double y2, int col){
  
   Double_t rhi = y2;
   Double_t rlo = y1;
   Double_t zhi = x2;
   Double_t zlo = x1;

   Double_t theta = atan((rhi-rlo)/(zhi-zlo));
   Double_t znew = 31700.;

   Double_t rnew = (znew-zlo)*tan(theta);
   TLine *ray = new TLine(zlo,rlo,znew,rnew);
   ray->SetLineColor(col);
   ray->Draw("same");

   cout<<"new radius = "<<rnew<<endl;
}

void draw_los(double x1, double x2, double y1, double y2, int col){

  Double_t rhi = y2;
  Double_t rlo = y1;
  Double_t zhi = x2;
  Double_t zlo = x1;
  
  Double_t theta = atan((rhi-rlo)/(zhi-zlo));
  Double_t znew = zlo-rlo/tan(theta);
  Double_t rnew = 0.;
  zhi = 31700;
  rhi = rhi + (31700-26500)*tan(theta);
  TLine *los = new TLine(zhi,rhi,znew,rnew);
  los->SetLineColor(col);
  los->Draw("same");
   cout<<"line of sight z  = "<<znew<<endl;
}

void draw_track(double x1, double x2, double y1, double y2, int col){

  Double_t rhi = y2;
  Double_t rlo = y1;
  Double_t zhi = x2;
  Double_t zlo = x1;
  
  //  Double_t theta = atan((rhi-rlo)/(zhi-zlo));
  //Double_t znew = zlo-rlo/tan(theta);
  //Double_t rnew = 0.;
  //zhi = 31700;
  //rhi = rhi + (31700-26500)*tan(theta);
  TLine *track = new TLine(zhi,rhi,zlo,rlo);
  track->SetLineColor(col);
  track->Draw("same");

}

void drawExperiment(){
   auto C = new TCanvas();
   gStyle->SetOptTitle(kFALSE);
   gStyle->SetOptStat(0);
   
   auto h1 = new TH2F ("h1","Histogram drawn with full circles",100,-700,31700.,100,0,1500);
   h1->Draw("");

  h1->GetXaxis()->SetTitle("z (mm)");
  h1->GetYaxis()->SetTitle("r (mm)");

  h1->GetYaxis()->SetTitleOffset(1.1);

  auto* legend = new TLegend(0.1,0.75,0.35,0.9);
  //  legend->AddEntry(h, "Histogram \"h\"", "l");

  TLegendEntry *leg1 = legend->AddEntry((TObject*)0, "Inner Photon Envelop", "l");
  TLegendEntry *leg2 = legend->AddEntry((TObject*)0, "Outer Photon Envelop", "l");
  TLegendEntry *leg3 = legend->AddEntry((TObject*)0, "``Line of sight''", "l");
  TLegendEntry *leg4 = legend->AddEntry((TObject*)0, "Moller electrons", "l");
  TLegendEntry *leg5 = legend->AddEntry((TObject*)0, "Elastic ep electrons", "l");
  leg1->SetLineColor(2);
  leg2->SetLineColor(3);
  leg3->SetLineColor(4);
  leg4->SetLineColor(66);
  leg5->SetLineColor(46);
  legend->Draw();
   
   // s1=xup,  s2=xdown, r1=rinner, r2=router

   //              target us window         detector rings
  /*   const int nboxes =4;
   Double_t s1[nboxes]={-1250/2,  1500.,    26500., 26500.};
   Double_t s2[nboxes]={ 1250/2,  1500.002, 26550., 26550.};
   Double_t r1[nboxes]={     0.,  0.,        855.,   680.};
   Double_t r2[nboxes]={    10.,  140., 1070.,   730.};
  */
    //target us window   
   const int nboxes =2;
   Double_t s1[nboxes]={-1250/2,  1500.};
   Double_t s2[nboxes]={ 1250/2,  1500.002};
   Double_t r1[nboxes]={     0.,  0.};
   Double_t r2[nboxes]={    10.,  140.};

   const int nrings =6;
   Double_t dets1[nrings]={26500., 26500., 26500., 26500., 26500., 26500.};
   Double_t dets2[nrings]={26550., 26550., 26550., 26550., 26550., 26550.};
   Double_t detr1[nrings]={860.,     675.,   640.,   710.,   760.,  1020.};
   Double_t detr2[nrings]={1020.,    710.,   675.,   760.,   860.,  1200.};
   
   /*
   Double_t s1[nboxes]={-1250/2,  26500.};
   Double_t s2[nboxes]={ 1250/2,  26550.};
   Double_t r1[nboxes]={     0.,    680.};
   Double_t r2[nboxes]={    10.,  1070.};
   */
   //colls
   //Collimator 1
   const int ncoll1 = 5;
   Double_t c1s1[ncoll1]={4675.,  4775.,  4875.,  4975.,  5075.};
   Double_t c1s2[ncoll1]={4775.,  4875.,  4975.,  5075.,  5175.};
   Double_t c1r1[ncoll1]={22.1,   18.489, 16.796, 13.629, 13.908};
   Double_t c1r2[ncoll1]={28.703, 28.703, 26.703, 26.703, 26.703};

   //trapezoidal collimators
   const int ncolls = 5;
   Double_t colls1[ncolls]={ 5250., 5250.,  7725., 7725., 12300.};
   Double_t colls2[ncolls]={ 5400., 5400.,  7875., 7875., 12370.};
   //   Double_t collr1[ncolls]={21.336,  98., 30.861, 196.5};
   Double_t collr1[ncolls]={21.336,  101., 30.861, 196.5, 74.22};
   //   Double_t r1[nboxes]={     0., 21.336,  103.};
   Double_t collr2[ncolls]={   35.,  150.,   53.5,  250., 116.38};
 
   //beampipe and ds window
   const int npipe = 6; 
   Double_t bps1[npipe]={23010.,  23290.4, 23920.8, 24133.1, 24320.4, 23015.12};
   Double_t bpl1[npipe]={  280.4,   630.4,   212.3,   187.3,  6506.,    280.4};
   Double_t bpr1[npipe]={  504.76,  504.78,  525.,    526.6,   550.,    504.76};
   Double_t bpr2[npipe]={  504.76,  528.33,  525.,    550.,    746.45,  988.};
   Double_t bpt1[npipe]={    2.38,    4.76,   28.6,     6.35,   19.05,    2.38125 };
   
   //lintels and collars
   /*   const int nlint =5; 
   Double_t lints1[nlint]={2000., 12300., 17311., 19000., 23000.};
   Double_t lints2[nlint]={2300., 12400., 17411., 19100., 23100.};
   Double_t lintr1[nlint]={  35.,   404.,   650.,   732., 928.};
   Double_t lintr2[nlint]={  105.,  430.,   682.,   750., 980.};
 
   const int nlint =4;
   Double_t lints1[nlint]={2000., 12300., 18000., 23000.};
   Double_t lints2[nlint]={2300., 12400., 18100., 23100.};
   Double_t lintr1[nlint]={  35.,   404.,   640.,   910.};
   Double_t lintr2[nlint]={  105.,  430.,  1100.,  1100.};

   */
   const int nlint =6;
   // lead collars near target and lintels in magnets
   Double_t lints1[nlint]={1200., 2851., 12285., 16750., 23350., 8930.5};
   Double_t lints2[nlint]={1600., 3051., 12385., 16900., 23500., 9180.5};
   Double_t lintr1[nlint]={ 140.,   74.,   435.,   600.,   952.,  265.};
   Double_t lintr2[nlint]={1150.,  330.,   650.,   750.,  1200., 1200.};

  
   //===========================================
  // Draw tracks and rays
   int tarbeam = 1;
   int detrings = 1;
   int firstcoll = 1;
   int trapcoll = 1;
   int pipe = 1;
   int lint = 1;
   int slogic = 1;
   
   for(int i=0;i<7;i++){
     if(i<nboxes&&tarbeam>0)  draw_box(s1[i],s2[i],r1[i],r2[i],slogic,1);
     if(i<ncolls&&trapcoll>0) draw_box(colls1[i],colls2[i],collr1[i],collr2[i],slogic,1);
     if(i<nlint&&lint>0)     draw_box(lints1[i],lints2[i],lintr1[i],lintr2[i],slogic,1);
     if(i<nrings&&detrings>0)     draw_box(dets1[i],dets2[i],detr1[i],detr2[i],slogic,i+1);

     if(i<npipe&&pipe>0){
       slogic = 0;
       draw_pipe(bps1[i],bpl1[i],bpr1[i],bpr2[i],bpt1[i]);
       slogic = 1;
       if(i==2) draw_box(bps1[i],bps1[i]+bpl1[i],bpr1[i],bpr2[i]+bpt1[i],slogic,1);
     }
     
     if(i<ncoll1&&firstcoll>0){
       if (i==0){
	 slogic =2;
       }
       else if (i==ncoll1-1){
	 slogic = 3;
       }
       else {
	 slogic=0;
       }
       draw_box(c1s1[i],c1s2[i],c1r1[i],c1r2[i],slogic,1);
       
       slogic =1;
       
     }
  }

   TLine *coll1_a = new TLine(c1s1[1],c1r1[1],c1s1[1],c1r1[0]);
   TLine *coll1_b = new TLine(c1s1[2],c1r2[2],c1s1[2],c1r2[1]);
   TLine *coll1_c = new TLine(c1s1[2],c1r1[2],c1s1[2],c1r1[1]);
   TLine *coll1_d = new TLine(c1s1[3],c1r1[3],c1s1[3],c1r1[2]);
   //TLine *coll1_a = new TLine(4775., 18.489, 4775., 22.1);
   coll1_a->Draw("same");
   coll1_b->Draw("same");
   coll1_c->Draw("same");
   coll1_d->Draw("same");
 
   draw_ray(s2[0],c1s2[3],r1[0],c1r1[3],2);  //IPE
   draw_ray(s1[0],colls1[2],r1[0],collr2[2],3); //OPE inner
   draw_ray(s2[0],colls2[1],r1[0],collr1[1],3); //OPE outer

   //   draw_los(colls2[3],s1[2],collr1[3],r2[2],4);
   //draw_los(lints2[3],dets1[0],lintr1[3],detr2[0],4);
   draw_los(colls2[3],dets1[0],collr1[3],detr2[0],4);
   draw_los(colls2[1],dets1[0],collr1[1],detr1[1],4);
   

   //===========================================
   //envelopes
   // Read in the track values vs. radius for each particle/angle
   // currently works for one track
   //need to either add a check for z < something and start over or have separate files?
  float position[3][1196];
  float tmp_position[2]={0.,0.};//  float velocity[3][3589];
  //float time[305]={0.};

  int debug=0;  

  ifstream in;
  //  in.open("one_cartoon_track.txt");
  //  in.open("processed_tracks.txt");
  in.open("tracks/extreme_tracks_bfil125.txt");

  ofstream out;
  out.open("test.txt", ofstream::out);

  //  if (!out.good()) {
  //cout<<"ERROR: file doesn't exist"<<endl;
  // return 0;
  // }
  
  //  int maxlines=305;
  // int maxlines=3589;
 int maxlines=1197;
  int nlines=0;
  float rmax = 0;
  int track_col[5]={46,66,46,66,46};
  int i_col = 0;
  while (nlines<maxlines) {
    //    in >> position[0][nlines] >> position[1][nlines]  >> position[2][nlines] >> velocity[0][nlines] >>velocity[1][nlines] >> velocity[2][nlines] >> time[nlines];
    in >> position[0][nlines] >> position[1][nlines]  >> position[2][nlines];
    
    //   cout<<position[0][nlines]<<"\t"<<position[1][nlines]<<"\t"<<position[2][nlines]<<"\t"<<endl;
    if(nlines>0&&position[2][nlines]>position[2][nlines-1]){
      if(position[2][nlines-1]>1350.&&position[2][nlines]>1350.){
	tmp_position[0] = position[0][nlines]-(position[2][nlines]-1350.)*0.001;
	tmp_position[1] = position[0][nlines-1]-(position[2][nlines-1]-1350.)*0.001;
	draw_track(10*position[2][nlines-1],10*position[2][nlines],-10*tmp_position[1],-10*tmp_position[0],track_col[i_col]);
      }
      else {
	draw_track(10*position[2][nlines-1],10*position[2][nlines],-10*position[0][nlines-1],-10*position[0][nlines],track_col[i_col]);	
      }
    } else {
      i_col+=1;
      cout<<i_col<<endl;
    }
    nlines++;
  }
  
  if (debug==1){
    printf("r \t position[0][0] \n");
    //printf("%f \t %f \n",r_field[0],B[0][0]);
    for (int i=0;i<305;i++){
      printf("%f \t ",position[0][i]);
      for (int j=0;j<6;j++){
	printf(" %f\t",position[0][i]);
      }  
      printf("\n");
    }
  }
  
  rmax = position[0][nlines-1];
  printf(" found %d points, rmax = %f \n",nlines, rmax);
  in.close();
   
   //gPad->BuildLegend();
}
