#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

Float_t zOffset = 4500;


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
   std::cout<< "x1: "<<x1<<", y1: "<<y1 <<", x2:"<< x2<<", y2:"<<y2 << std::endl;
   std::cout<< "Theta: " << theta<< std::endl;
     
   Double_t znew = 31700.;

   Double_t rnew = (znew-zlo)*tan(theta)+rlo;
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



void drawCollimator1(){

Double_t z[10] = {175+zOffset, 175+100+zOffset, 175+190+zOffset, 175+310+zOffset, 175+400+zOffset, 175+500+zOffset, 175+725+zOffset, 175+725+zOffset, 175+zOffset, 175+zOffset};
Double_t r[10]= {20, 16.25, 15.1, 14.1, 13.629, 13.908, 14.536, 27, 27, 20};

TPolyLine *coll1=new TPolyLine(10, z, r);
coll1->SetFillStyle(0);
coll1->Draw("lsame");

}

void drawAcceptCollimators(){

TBox* coll2_bot=new TBox(-4500+5250+zOffset, 27, -4500+5400+zOffset, 35.0); // Give bottom left and top right cooridnate
coll2_bot->SetFillStyle(0);
coll2_bot->Draw("lsame");

TBox* coll2_top=new TBox(-4500+5250+zOffset, 101, -4500+5400+zOffset, 150.0); // Give bottom left and top right cooridnate
coll2_top->SetFillStyle(0);
coll2_top->Draw("lsame");


TBox* coll4_bot=new TBox(-4500+7725+zOffset, 30.861, -4500+7875+zOffset, 53.5); // Give bottom left and top right cooridnate
coll4_bot->SetFillStyle(0);
coll4_bot->Draw("lsame");

TBox* coll4_top=new TBox(-4500+7725+zOffset, 196.5, -4500+7875+zOffset, 250.0); // Give bottom left and top right cooridnate
coll4_top->SetFillStyle(0);
coll4_top->Draw("lsame");

TBox* coll5=new TBox(-4500+12300+zOffset, 74.22, -4500+12370+zOffset, 116.38); // Give bottom left and top right cooridnate
coll5->SetFillStyle(0);
coll5->Draw("lsame");


}


void drawUSCoil(){

Double_t z[5]= {1103.025+zOffset, 1103.025+zOffset, 2895.755+zOffset, 2895.755+zOffset, 1103.025+zOffset};
Double_t r[5]= {31.152-1, 239.284+1, 243.899+1, 35.767-1, 31.152-1};

TPolyLine *usCoil=new TPolyLine(5, z, r);
usCoil->SetFillStyle(0);
usCoil->Draw("lsame");

TArc *front= new TArc( z[0], (r[1]+r[0])/2.0, (r[1]-r[0])/2.0, 90, 270);
front->Draw("lsame");

TArc *back= new TArc( z[3], (r[3]+r[4])/2.0, (r[3]-r[4])/2.0, 0, 90);
back->Draw("lsame");
back->DrawArc(z[3], (r[3]+r[4])/2.0, (r[3]-r[4])/2.0, 0, 270, 360);



}

void drawDSCoil(){

Double_t z1[5]= {5000+zOffset, 5000+zOffset, 5860+zOffset, 5860+zOffset, 5000+zOffset};
Double_t r1[5]= {40.68-1, 173.22+1, 198.23+1, 42.89-1, 40.68-1} ;

TPolyLine *ds1=new TPolyLine(5, z1, r1);
ds1->SetFillStyle(0);
ds1->Draw("lsame");

Double_t z2[5]= {6036+zOffset, 6036+zOffset, 6876+zOffset, 6876+zOffset, 6036+zOffset};
Double_t r2[5]= {43.35-1, 214.19+1, 238.35+1, 45.51-1, 43.35-1} ;

TPolyLine *ds2=new TPolyLine(5, z2, r2);
ds2->SetFillStyle(0);
ds2->Draw("lsame");

Double_t z3[5]= {7097+zOffset, 7097+zOffset, 7850+zOffset, 7850+zOffset, 7097+zOffset};
Double_t r3[5]= {46.08-1, 260.35+1, 277.29+1, 48.02-1, 46.08-1} ;

TPolyLine *ds3=new TPolyLine(5, z3, r3);
ds3->SetFillStyle(0);
ds3->Draw("lsame");

Double_t z4[27]= {8117.861+zOffset, 9478.17411+zOffset, 11454.99469+zOffset, 11670.388+zOffset, 11670.388+zOffset, 9760.31833+zOffset, 9743.34349+zOffset, 9726.46292+zOffset, 9709.79228+zOffset, 9693.44576+zOffset, 9677.53537+zOffset, 9662.17008+zOffset, 9647.5517+zOffset, 9633.39145+zOffset, 9620.37456+zOffset, 9602.09365+zOffset, 9582.63092+zOffset, 9562.12010+zOffset, 9540.70217+zOffset, 9518.52430+zOffset, 9495.73892+zOffset, 9472.50260+zOffset, 9448.97504+zOffset, 9425.31792+zOffset, 8426.68591+zOffset, 8117.861+zOffset, 8117.861+zOffset};
Double_t r4[27]={ 50.505-1,  78.91171-1, 182.79241-1, 149.310-1, 410.970+1, 289.03516+1, 289.47212+1, 291.31138+1, 294.54033+1, 299.13685+1, 305.06944+1, 312.29747+1, 320.77142+1, 330.43324+1, 341.21674+1, 356.24363+1, 369.70471+1, 381.50749+1, 391.57084+1, 399.82562+1, 406.21508+1, 410.69533+1, 413.23557+1, 413.81834+1, 378.94544+1, 325.750+1, 50.505-1  };

TPolyLine *ds4=new TPolyLine(27, z4, r4);
ds4->SetFillStyle(0);
ds4->Draw("lsame");

        
}




void draw2bShields(){

Double_t z_us[5]={-4500+5400+zOffset, -4500+5400+zOffset, -4500+5400+2100+zOffset, -4500+5400+2100+zOffset, -4500+5400+zOffset};
Double_t r_us[5]={41/2.0, 47/2.0, 61/2.0, 55/2.0, 41/2.0};

TPolyLine *usShield=new TPolyLine(5, z_us, r_us);
usShield->SetFillStyle(0);
usShield->Draw("lsame");

Double_t z_ds[7]={-4500+7875+zOffset, -4500+7875+zOffset, -4500+9500+zOffset, -4500+13000+zOffset, -4500+13000+zOffset, -4500+9500+zOffset, -4500+7875+zOffset};
Double_t r_ds[7]={32, 38, 38, 49, 43, 32, 32};

TPolyLine *dsShield=new TPolyLine(7, z_ds, r_ds);
dsShield->SetFillStyle(0);
dsShield->Draw("lsame");

}


void drawDetectors(){


TBox* pmt=new TBox(zOffset+21995, 1200, zOffset+22100, 1500);
pmt->SetFillColor(7);

TBox* ring6=new TBox(zOffset+21995, 1035, zOffset+22100, 1140);
ring6->SetFillColor(6);

TBox* ring5=new TBox(zOffset+21995, 875, zOffset+22100, 1035);
ring5->SetFillColor(5);

TBox* ring4=new TBox(zOffset+21995, 785, zOffset+22100, 885);
ring4->SetFillColor(4);

TBox* ring3=new TBox(zOffset+21995, 725, zOffset+22100, 785);
ring3->SetFillColor(3);

TBox* ring2=new TBox(zOffset+21995, 680, zOffset+22100, 725);
ring2->SetFillColor(2);

TBox* ring1=new TBox(zOffset+21995, 640, zOffset+22100, 680);
ring1->SetFillColor(1);

ring1->Draw("same");
ring2->Draw("same");
ring3->Draw("same");
ring4->Draw("same");
ring5->Draw("same");
ring6->Draw("same");
pmt->Draw("same");

}


void drawExperiment(){
   auto C = new TCanvas();
   gStyle->SetOptTitle(kFALSE);
   gStyle->SetOptStat(0);


  
   auto h1 = new TH2F ("h1","Entire Experiment",1000,-1000, 31700.,1000,0,1500);
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
   
   const int nboxes =2;
   Double_t s1[nboxes]={-1250/2,  1500.};
   Double_t s2[nboxes]={ 1250/2,  1500.002};
   Double_t r1[nboxes]={     -2.5,  0.};
   Double_t r2[nboxes]={    10.,  140.};

   
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
   //   Double_t collr1[ncolls]={21.336,  101., 30.861, 196.5, 74.22};
   Double_t collr1[ncolls]={16.,  101., 30.861, 196.5, 74.22};
   //   Double_t r1[nboxes]={     0., 21.336,  103.};
   Double_t collr2[ncolls]={   35.,  150.,   53.5,  250., 116.38};
 
   //beampipe and ds window
   const int npipe = 8; 
   Double_t bps1[npipe]={23010.,  23290.4, 23920.8, 24133.1, 24320.4, 23015.12};
   Double_t bpl1[npipe]={  280.4,   630.4,   212.3,   187.3,  6506.,    280.4 };
   //   Double_t bpr1[npipe]={  504.76,  504.78,  525.,    526.6,   550.,    504.76, 25.5};
   //Double_t bpr2[npipe]={  504.76,  528.33,  525.,    550.,    746.45,  988., 28.5};
   //Double_t bpt1[npipe]={    2.38,    4.76,   28.6,     6.35,   19.05,    2.38125, 3. };
   Double_t bpr1[npipe]={  504.76,  504.78,  525.,    526.6,   550.,    504.76    };
   Double_t bpr2[npipe]={  504.76,  528.33,  525.,    550.,    746.45,  988.};
   Double_t bpt1[npipe]={    2.38,    4.76,   28.6,     6.35,   19.05,    2.38125 };



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
