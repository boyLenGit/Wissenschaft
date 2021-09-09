/*
   Copyright (C) 2004 Caltech
   Written by Lexing Ying
*/

#include "fdct_wrapping.hpp"
#include "fdct_wrapping_inline.hpp"
#include <time.h>
using namespace std;
using namespace fdct_wrapping_ns;
#define MNWZ 0x100000000
#define ANWZ 0x5DEECE66D
#define CNWZ 0xB16
#define INFINITY 0xFFFFFFFFF

int labelsize;
int dim;
 
static unsigned long long seed = 1;
 
double drand48(void)
 {
 seed = (ANWZ * seed + CNWZ) & 0xFFFFFFFFFFFFLL;
 unsigned int x =(unsigned int)( seed >> 16);
 return ((double)x / (double)MNWZ);
 }
 
 //static unsigned long long seed = 1; 
 
 void srand48(unsigned int i)
 {
 seed = (((long long int)i) << 16) | rand();
 }


int optionsCreate(const char* optfile, map<string,string>& options)
{
  options.clear();
  ifstream fin(optfile); assert(fin.good());
  string name;  fin>>name;
  while(fin.good()) {
	 char cont[100];	 fin.getline(cont, 99);
	 options[name] = string(cont);
	 fin>>name;
  }
  fin.close();
  return 0;
}

extern "C" void curvelet(int m,int n,int nbscales,int nbangles_coarse,int ac,void **p)
	
{
	//�������m��n�ֱ�Ϊ����ά���ݵ������������������¼���������͵��������ݰ��յ�һ�������һ����˳�����С�
	 // int nbscales--�߶�int nbangles_coarse--�Ƕ���,int ac--ʵ����δʹ�ã�,float *x������������
	//int * arrayscales--���ظ��߶ȶ�Ӧ�ĽǶȵ���ʼ����ֵֹ, int* arrayangles--���Ƕ����ݵ�ά���͵�һϵ��ƫ����, double *curvelety --����ϵ��
	float *x;

	int * arrayscales;
	int* arrayangles; 
	double *curvelety;
	double *curveleti;
	x=(float *)p[0];
	   CpxNumMat cd(m,n);
	 int cnt = 0;
	 for(int j=0; j<n; j++)
		for(int i=0; i<m; i++) {
		  cd(i,j) = cpx(x[cnt], 0);
		  cnt++;
		}
 		//fdct_wrapping_
  vector< vector<CpxNumMat> > c;  //vector<int> extra;
// cout<<"check ac="<<ac<<endl;
  fdct_wrapping(m, n, nbscales, nbangles_coarse, ac, cd, c);

  int nc = c.size();int totalangles=0;int totalcurvelet=0;
  arrayscales=(int *)malloc(2*nc*sizeof(int));
   for(int ci=0; ci<nc; ci++) {
	  int ncd=c[ci].size();
	   arrayscales[2*ci]=totalangles;
		totalangles=totalangles+ncd;
		arrayscales[2*ci+1]=totalangles;//��¼ÿ���߶ȶ�Ӧ�ĽǶ���Ŀ����ʼ�ͽ�����Ӧ�ĽǶ�������
	  //cout<< "\n    scal("<<ci<<")is :"<<ncd<<"check "<<arrayscales[2*ci]<<" to "<<arrayscales[2*ci+1];
	 
		for(int cj=0;cj<ncd;cj++)totalcurvelet=totalcurvelet+c[ci][cj].m()*c[ci][cj].n();
		   
			   int mcj=c[ci][0].m();int ncj=c[ci][0].n();
		   //cout<< "_array:"<<mcj<<"_"<<ncj<<endl;
	  }

//   	 for(int sc=1; sc<nbscales; sc++) {int nbangles=arrayscales[2*(sc-1)]-arrayscales[2*(sc-1)-1];
	// cout<<"angles of scal "<<sc <<" :"<<nbangles<<endl;
	 

   arrayangles=(int *)malloc(totalangles*3*sizeof(int));//��¼���г߶ȽǶȶ�Ӧ������ά��m��n�����һϵ����ƫ����
   curvelety=(double *)malloc(totalcurvelet*sizeof(double));//��¼���е������任ϵ��
   curveleti=(double *)malloc(totalcurvelet*sizeof(double));//��¼���е������任ϵ��
   	  int anglecounter=0;int ishift=0;//���ڽǶ����ļ���; ishif���ڼ�¼��һ��ϵ���������е�ƫ����
     for( int ci=0; ci<nc; ci++) {
	  int ncd=c[ci].size();//ÿ���߶ȵĽǶ���
	  //cout<< "\n    scal("<<ci<<")is :"<<ncd;
	     for(int cj=0;cj<ncd;cj++){

			 int mcj=c[ci][cj].m();int ncj=c[ci][cj].n();
			 arrayangles[3*anglecounter]=mcj;
			 arrayangles[3*anglecounter+1]=ncj;
			 arrayangles[3*anglecounter+2]=ishift;
			 int ipoint=ishift;
			 for(int ncount=0;ncount<ncj;ncount++)
				 for(int mcount=0;mcount<mcj;mcount++){
					 curvelety[ipoint]=real(c[ci][cj](mcount,ncount));
					 curveleti[ipoint]=imag(c[ci][cj](mcount,ncount));
					 ipoint++;
				 }
				 ishift=ishift+mcj*ncj;anglecounter=anglecounter+1;//��һ���Ƕȼ����͵�һϵ����ƫ����
		 }
 	  }
  
	p[1]=arrayscales;
	p[2]=arrayangles; 
	p[3]=curvelety;
	p[4]=curveleti;
	 return;

	}
extern "C" void icurvelet(int m,int n,int nbscales,int nbangles_coarse,int ac,void **p)
{
	//�������m��n�ֱ�Ϊ����ά���ݵ������������������¼���������͵��������ݰ��յ�һ�������һ����˳�����С�
	 // int nbscales--�߶�int nbangles_coarse--�Ƕ���,int ac--ʵ����δʹ�ã�,float *x������������
	//int * arrayscales--���ظ��߶ȶ�Ӧ�ĽǶȵ���ʼ����ֵֹ, int* arrayangles--���Ƕ����ݵ�ά���͵�һϵ��ƫ����, double *curvelety --
	float *x;
	int * arrayscales;
	int* arrayangles; 
	double *curvelety;
	double *curveleti;
	arrayscales=(int *)p[1];
	arrayangles=(int *)p[2]; 
	curvelety=(double *)p[3];
	curveleti=(double *)p[4];
	
	
	vector< vector<CpxNumMat> > c;  //vector<int> extra;����c++������ϵ������
  vector<int> nbangles(nbscales);	 //nbangles
	// nbangles[0] = 1;
	 for(int sc=0; sc<nbscales; sc++) nbangles[sc] =arrayscales[2*sc+1]-arrayscales[2*sc];

	// for(int sc=0;sc<nbscales;sc++)cout<<"angles of scal "<<sc <<" :"<<nbangles[sc]<<endl;
	 
	 
	 //c
	 c.resize(nbscales);
	 for(int sc=0; sc<nbscales; sc++)		c[sc].resize( nbangles[sc] );//
	   	  int anglecounter=0;int ishift=0;//���ڽǶ����ļ���; ishif���ڼ�¼��һ��ϵ���������е�ƫ����
     for( int ci=0; ci<nbscales; ci++) {
	  int ncd=c[ci].size();//ÿ���߶ȵĽǶ���
	  //cout<< "\n    scal("<<ci<<")is :"<<ncd;
	     for(int cj=0;cj<ncd;cj++){

			 int mcj=arrayangles[3*anglecounter];int ncj=arrayangles[3*anglecounter+1]; 
//			 cout<< anglecounter<<"   "<<mcj<<"   "<<ncj<<"    "<<arrayangles[3*anglecounter+2]<<endl;
			 CpxNumMat tpdata(mcj,ncj);
			 ishift=arrayangles[3*anglecounter+2];
			 int ipoint=ishift;
			 for(int ncount=0;ncount<ncj;ncount++)
				 for(int mcount=0;mcount<mcj;mcount++){
                tpdata(mcount,ncount)=cpx(curvelety[ipoint],curveleti[ipoint]);
//                 tpdata(mcount,ncount)=cpx(curvelety[ipoint],0.0);
					 ipoint++;
				 }
	             anglecounter=anglecounter+1;//��һ���Ƕȼ���
				 c[ci][cj]=tpdata;
		 }
 	  }
  //ifdct_wrapping_
  CpxNumMat y(m,n); clear(y);
  cout<<"check in ict  ac="<<ac<<endl;
    ifdct_wrapping(m, n, nbscales, nbangles_coarse, ac, c, y);
  x=(float *)malloc(m*n*sizeof(float));

   int cnt = 0;
  for(int j=0; j<n; j++)
	 for(int i=0; i<m; i++) {
		x[cnt] = (float)real(y(i,j));
		cnt++;
	 }
	 
	p[0]=x;

  return;
  
	}


int main(int argc, char** argv)
{
  clock_t ck0, ck1;

float *xin,*xout;
int * arrayscales;
int* arrayangles; 
double *curvelety;
double *curveleti;
double *curveletym;
double *curveletim;
void *p[5];
void *p1[5];
float *yin;
  
  assert(argc==2);
  //get options
  map<string, string> opts;  optionsCreate(argv[1], opts);
  
  //get input data
  map<string,string>::iterator mi;
  int m;
  mi = opts.find("-m"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>m; }
  
  int n;
  mi = opts.find("-n"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>n; }
  
  int nbscales;
  mi = opts.find("-nbscales"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>nbscales; }
  
  int nbangles_coarse;
  mi = opts.find("-nbangles_coarse"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>nbangles_coarse; }
  
  int ac;
  mi = opts.find("-ac"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>ac; }

  float threshold;
  mi = opts.find("-threshold"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>threshold; }

  float anglethreshold;
  mi = opts.find("-anglethreshold"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>anglethreshold; }

  int bwin;
  mi = opts.find("-bigwindow"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>bwin; }

  int swin;
  mi = opts.find("-smallwindow"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>swin; }

  string infile1;
  mi = opts.find("-infile1"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>infile1; }
  string infile2;
  mi = opts.find("-infile2"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>infile2; }
  string outfile1;
  mi = opts.find("-outfile1"); assert(mi!=opts.end());
  { istringstream ss((*mi).second); ss>>outfile1; }

  
//  CpxNumMat x(m,n);

  srand48( (long)time(NULL) );
  xin=(float *)malloc(m*n*sizeof(float));
  p[0]=xin;
  yin=(float *)malloc(m*n*sizeof(float));
  p1[0]=yin;

  int icount=0;
  
cout<<"open filename is :"<<infile1<<endl;

 ifstream fin(infile1,ios::binary);
 if(!fin){

cout<<"File open error! filename is :"<<infile1<<endl;
return -1;
}
fin.read((char *)xin,m*n*4);
fin.close();

ifstream fin2(infile2,ios::binary);
 if(!fin2){

cout<<"File open error! filename is :"<<infile2<<endl;
return -1;
}
 float *yyin=(float *)malloc(m*n*sizeof(float));
 double *xaverage=(double *)malloc(m*n*sizeof(double));
fin2.read((char *)yyin,m*n*4);
fin2.close();

   icount=0;double average,average1;
   
  for(int i=0; i<n; i++)
  { 
   icount=i*m;
   int j;
   average1=0.0;
   for(j=0;j<bwin;j++)average1=average1+abs(xin[icount+j]);
   for(j=0;j<bwin/2;j++)		   xaverage[icount+j]=average1;
      for(j=bwin/2;j<m-bwin/2;j++)
   {  average1=average1-abs(xin[icount+j-bwin/2])+abs(xin[icount+j+bwin/2]);
  	   xaverage[icount+j]=average1;
   }
	  for(j=m-bwin/2;j<m;j++)
   {  
  	   xaverage[icount+j]=average1;
   }
  }
  icount=0;
  for(int i=0;i<n;i++)
	  for(int j=0;j<m;j++){if(xaverage[icount]>0)xin[icount]=(float)(xin[icount]/xaverage[icount]*bwin);icount++;}
  

  for(int i=0; i<n; i++)
  { 
   icount=i*m;
   int j;
   average=0.0;average1=0.0;
   for(j=0;j<swin;j++){average=average+abs(yyin[icount+j]);average1=average1+abs(xin[icount+j]);}
   for(j=0;j<swin/2;j++)if(average>0)yin[icount+j]=(float)(yyin[icount+j]/average*average1);//ǰ�����������ƥ��
   
   for(j=swin/2;j<m-swin/2;j++)
   {average=average-abs(yyin[icount+j-swin/2])+abs(yyin[icount+j+swin/2]);
    
   average1=average1-abs(xin[icount+j-swin/2])+abs(xin[icount+j+swin/2]);
   
   if(average>0)		   yin[icount+j]=(float)(yyin[icount+j]/average*average1);//�������ƥ��
		   
      
   }
   for(j=m-swin/2;j<m;j++)if(average>0) yin[icount+j]=(float)(yyin[icount+j]/average*average1);  //���������ƥ��
   
  }
 //���Ԥ���β�ʱ���˳��Ը��ţ�����Ҫ��������޸ķ���λ
 // icount=0;
// for(int i=0; i<m; i++)
//	  for(int j=0; j<n; j++){yin[icount]=yin[icount]*(-1.0);icount++;}
	
  free(yyin);//�ͷ���ʱ����
  
  ck0 = clock();
curvelet(m,n,nbscales,nbangles_coarse,ac,p);
curvelet(m,n,nbscales,nbangles_coarse,ac,p1);
  
//��������任ϵ�����������
arrayscales=(int *)p[1];
arrayangles=(int *)p[2]; 
curvelety=(double *)p[3];
curveleti=(double *)p[4];
curveletym=(double *)p1[3];
curveletim=(double *)p1[4];

for(int myscali=0;myscali<nbscales;myscali++)
{

int anglestart=arrayscales[2*myscali];
int angleend=arrayscales[2*myscali+1];

double *cellx;cellx=(double *)malloc(m*n*sizeof(double));
double amp1,amp2,amp3;
//���߶Ⱥͷ�λ������Աȸ�С��ϵ��������������һ�¾����
for (int anglec=anglestart;anglec<angleend;anglec++)
{
	int cellpoint=arrayangles[3*anglec+2];
	int cellp=0;
	int cellm=arrayangles[3*anglec];
	int celln=arrayangles[3*anglec+1];

	for( int celli=0;celli<celln;celli++)for( int cellj=0;cellj<cellm;cellj++)
	{
		
		
		amp1=sqrt(curvelety[cellpoint]*curvelety[cellpoint]+curveleti[cellpoint]*curveleti[cellpoint]);
        amp2=sqrt(curveletym[cellpoint]*curveletym[cellpoint]+curveletim[cellpoint]*curveletim[cellpoint]);
		amp3=curvelety[cellpoint]*curveletym[cellpoint]+curveleti[cellpoint]*curveletim[cellpoint];
		if(amp2*amp1>0.0)amp3=amp3/amp1/amp2;
		//�������һ�¾����
		if(amp3>anglethreshold&&amp2>threshold*amp1)
			{
				curvelety[cellpoint]=0.0;
		        curveleti[cellpoint]=0.0;
		}

		if(amp2>=threshold*amp1&&amp1>0.0)
		{  
			
			curveletym[cellpoint]=curveletym[cellpoint]/amp2;
			curveletim[cellpoint]=curveletim[cellpoint]/amp2;
			amp3=curvelety[cellpoint]*curveletym[cellpoint]+curveleti[cellpoint]*curveletim[cellpoint];
			
//		 if(cellp<10)cout<<amp3/amp1<<" amp3"<<amp3<<"->"<<amp1<<endl;
			if(amp3/amp1>=0.0&&amp3/amp1<anglethreshold)
			{
			  curvelety[cellpoint]=curvelety[cellpoint]-curveletym[cellpoint]*amp3;
			  curveleti[cellpoint]=curveleti[cellpoint]-curveletim[cellpoint]*amp3;
//			  curvelety[cellpoint]=0;
//			  curveleti[cellpoint]=0;

			}	
			
		}

		
	cellpoint ++;cellp++;
	}
}

 free(cellx);
}


  ck1 = clock();  
  
  cout<<"FDCT_WRAPPING_  takes "<<double(ck1-ck0)/CLOCKS_PER_SEC<<" seconds"<<endl;  ck0 = ck1;

//���任�õ����


  icurvelet(m,n,nbscales,nbangles_coarse,ac,p);
  ck1 = clock();  cout<<"IFDCT_WRAPPING_ takes "<<double(ck1-ck0)/CLOCKS_PER_SEC<<" seconds"<<endl;  ck0 = ck1;
  xout=(float *)p[0];
  //ԭʼ��¼����������
  icount=0;
  for(int i=0;i<n;i++)
	  for(int j=0;j<m;j++)
	  {
		  if(xaverage[icount]>0)
		  {
			  xout[icount]=(float)(xout[icount]*xaverage[icount])/bwin;
			  xin[icount]=(float)(xin[icount]*xaverage[icount])/bwin;
		  }
			  icount++;
	  }

	  ofstream fout1("z1.dat",ios::binary);//��������������

//	  fout1.write((char *)xin,m*n*sizeof(float));//���������ԭʼ��¼
 
  float totalerror=0.0;icount=0;
  for(int i=0; i<m; i++)
	  for(int j=0; j<n; j++)
		xin[icount]=xin[icount]-xout[icount++];//�������������
 
  ofstream fout(outfile1,ios::binary);//������ǳˮ��β�������ļ�
fout.write((char *)xout,m*n*sizeof(float));
fout.close();
fout1.write((char *)xin,m*n*sizeof(float));//��������������������ļ��
//fout1.write((char *)xout,m*n*sizeof(float));//�������ǳˮ��β������ݵ�����ļ���
fout1.close();

	  //  cerr<<"accuracy of inversion "<<sqrt(energy(e)/(m*n))<<endl;
  
  

  vector< vector<double> > sx, sy;
  vector< vector<double> > fx, fy;
  vector< vector<int> > nx, ny;
  fdct_wrapping_param(m, n, nbscales, nbangles_coarse, ac, sx, sy, fx, fy, nx, ny);



free(xaverage);
free(xin);
free(xout);
free(p[2]);
free(p[3]); 
free(p[4]);
free(yin);
free(p1[2]);
free(p1[3]); 
free(p1[4]);

  return 0;
}

