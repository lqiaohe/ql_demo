#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<math.h>
//#include "sub_project.cpp"
#include "test.cpp"
#include "gurobi.cpp"
using namespace std;
const int MAX=-99;
int my_pow(int m,int n){
    int tmp=1;
    for(int i=0;i<n;i++)
        tmp*=m;
    return tmp;
}

void clear_data(vector <vector <int> > &data,int max){
    for(int i=0;i<7;i++){
        for(int j=0;j<max;j++){
            data[i][j]=MAX;
        }
    }
}

void clear_data(vector <vector <int> > &data,int hang_first,int hang_end,int lie_first,int lie_end){
    for(int i=hang_first-1;i<=hang_end-1;i++){
        for(int j=lie_first-1;j<=lie_end-1;j++){
            data[i][j]=MAX;
        }
    }
}

void give_data(vector <vector <int> > &data,int hang_first,int hang_end,int lie_first,int lie_end,int select){
    for(int i=hang_first-1;i<=hang_end-1;i++){
        for(int j=lie_first-1;j<=lie_end-1;j++){
            data[i][j]=select;
        }
    }
}

int my_sum(int hang_first,int hang_last,int lie,vector <vector <int> > data){
    int tmp=0;
    for(int i=hang_first-1;i<=hang_last-1;i++){
        tmp+=data[i][lie-1];
    }
    return tmp;
}

int read_data(int &row,int &col,vector <vector <int> > &data,string filename){
    ifstream ifile(filename);
    string line;
    row=0;
    col=0;

    while(getline(ifile,line)){
        istringstream sin(line);
        string field;
        col=0;
        while(getline(sin,field,',')){

            if(field==""||field=="\n"||field=="\r"){
                data[row][col]==MAX;
            }else {
               data[row][col]=atoi(field.c_str());
            }
            col+=1;
        }
        row+=1;
    }
    ifile.close();
    return 0;
}

vector < vector <int> > data_transform(int m,int &n,vector <vector <int> > data){
    n/=2;
    vector <vector <int> > new_data(m,vector<int>(n,MAX));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(data[i][2*j]!=MAX&&data[i][2*j+1]!=MAX){
                 new_data[i][j]=data[i][2*j]*100000+data[i][2*j+1];
            }

        }
    }
    return new_data;
}

void write_data(string filename,vector <vector <int> > data,int row,int col){
    ofstream ofile(filename);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            ofile<<data[i][j]<<"\t";
        }
        ofile<<endl;
    }
    ofile.close();
}
int get_data(int row,int col,vector < vector <int> > data){
    return data[row-1][col-1];
}

//int main(int argc, char *argv[]){
//    QCoreApplication a(argc, argv);
//    bool ans=gurobi();
//    if(ans){
//        cout<<"there is answer"<<endl;
//    }
//    return a.exec();
//}

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    //file data;

    bool ans=gurobi();
    cout<<"debug";
    cout<<ans<<endl;
    cout<<"debug";


    int cs_row=15,cs_col=4;
    int pmf_row=0,pmf_col=0;
    int o_row=0,o_col=0;
    int pmb_row=0,pmb_col=0;
    int inv_row=0,inv_col=0;
    int invt_row=0,invt_col=0;
    int cojO_row=0,cojO_col=0;
    int tm_row=0,tm_col=0;
     int obj_row=0,obj_col=0;
     int opie_row=0,opie_col=0;

     vector <vector <int> > cs_data(15,vector<int>(4,MAX));
     vector <vector <int> > pmf_data(9,vector<int>(8,MAX));
     vector <vector <int> > o_data(9,vector<int>(18,MAX));
     vector <vector <int> > pmb_data(9,vector<int>(8,MAX));
     vector <vector <int> > inv_data(9,vector<int>(8,MAX));
     vector <vector <int> > invt_data(9,vector<int>(34,MAX));
     vector <vector <int> > cojO_data(3,vector<int>(8,MAX));
     vector <vector <int> > tm_data(9,vector<int>(8,MAX));
     vector <vector <int> > obj_data(3,vector<int>(6,MAX));
     vector <vector <int> > opie_data(1,vector<int>(2,MAX));

    string cs_path="/home/wsc/project/basic data/cs.csv";
    string pmf_path="/home/wsc/project/basic data/pmf.csv";
     string o_path="/home/wsc/project/basic data/o.csv";
     string pmb_path="/home/wsc/project/basic data/pmb.csv";
     string inv_path="/home/wsc/project/basic data/inv.csv";
     string invt_path="/home/wsc/project/basic data/invt.csv";
     string cojO_path="/home/wsc/project/basic data/cojO.csv";
     string tm_path="/home/wsc/project/basic data/tm.csv";
     string obj_path="/home/wsc/project/basic data/obj.csv";
     string opie_path="/home/wsc/project/basic data/o-.csv";

    read_data(cs_row,cs_col,cs_data,cs_path);
    read_data(pmf_row,pmf_col,pmf_data,pmf_path);
    read_data(o_row,o_col,o_data,o_path);
    read_data(pmb_row,pmb_col,pmb_data,pmb_path);
    read_data(inv_row,inv_col,inv_data,inv_path);
    read_data(invt_row,invt_col,invt_data,invt_path);
    read_data(cojO_row,cojO_col,cojO_data,cojO_path);
    read_data(tm_row,tm_col,tm_data,tm_path);
    read_data(obj_row,obj_col,obj_data,obj_path);
    read_data(opie_row,opie_col,opie_data,opie_path);

    cs_data=data_transform(cs_row,cs_col,cs_data);
    pmf_data=data_transform(pmf_row,pmf_col,pmf_data);
    o_data=data_transform(o_row,o_col,o_data);
    pmb_data=data_transform(pmb_row,pmb_col,pmb_data);
    inv_data=data_transform(inv_row,inv_col,inv_data);
    invt_data=data_transform(invt_row,invt_col,invt_data);
    cojO_data=data_transform(cojO_row,cojO_col,cojO_data);
    tm_data=data_transform(tm_row,tm_col,tm_data);
    obj_data=data_transform(obj_row,obj_col,obj_data);
    opie_data=data_transform(opie_row,opie_col,opie_data);


    cout<<"debug yes"<<endl;
    int all_row=cs_data[1][0];
    //program data
    vector <vector <int> > sch_data(all_row+1+1,vector<int>(50,MAX));
    vector <vector <int> > sce_data(all_row+1,vector <int> (50,MAX));
    vector <vector <int> > presh_data(all_row+1,vector <int> (50,MAX));
    vector <vector <int> > prsh_data(all_row+1,vector <int> (50,MAX));
    vector <double> xzi_data;

    int all_row_cj=cs_data[2][0];

    vector <vector <int> > coj_data(all_row_cj+1,vector<int>(5+2*cs_data[1][0],MAX));
    vector <vector <int> > coj1_data(all_row_cj+1,vector<int>(5+2*cs_data[1][0],MAX));
    vector <vector <int> > coj2_data(all_row_cj+1,vector<int>(5,MAX));

    vector <vector <int> > x_data(all_row+1,vector<int>(2,MAX));
    vector <vector <int> > aim_data(all_row+1,vector<int>(5,MAX));
    vector <vector <int> > c_data(7,vector <int> (2*max(all_row+1,9),MAX));
    vector <vector <int> > m_data(6*cs_data[1][0]+1+4*cs_data[1][0]*cs_data[2][0],vector<int>(1+2*cs_data[1][0],MAX));
    vector <vector <int> > m0_data(6*cs_data[1][0]+1+4*cs_data[1][0]*cs_data[2][0],vector<int>(1,MAX));
    cout<<"debug";
    //01
    for(int i=0;i<cs_data[1][0];i++){
        sch_data[i][0]=sce_data[i][0]=presh_data[i][0]=prsh_data[i][0]=i+1;
    }
    for(int i=0;i<cs_data[2][0];i++){
        coj_data[i][0]=coj1_data[i][0]=coj2_data[i][0]=i+1;
    }
    //yingshe sch_data[0][j]=0
    for(int i=0;i<50;i++){
        sch_data[all_row+1][i]=0;
    }
    for(int i=0;i<cs_data[1][0];i++){
        sch_data[i][1]=1;
        sch_data[i][2]=0;
        sch_data[i][3]=0;
    }
    if(cs_data[2][1]>0){
        for(int i=0;i<cs_data[2][1];i++){
            for(int j=0;j<9;j++){
                o_data[cs_data[1][0]+i][j]=opie_data[i][j];
            }
        }

    }
    cs_data[1][0]+=cs_data[2][1];
    //02
    int n_1_5=0;
    int num_ceng=0;
    cout<<"debug"<<endl;
    for(int n_1_6=0;n_1_6<=cs_data[1][1]-1;n_1_6++){
            int n_1_1;
            int n_1_2;
            if(n_1_6<=cs_data[1][1]-1){
                int shangjie=0;
                //
                if(n_1_6==0){
                    n_1_1=0;
                    n_1_2=-1;
                }
                else{
                    int tmp=0;
                    for(int i1=0;i1<n_1_6;i1++){
                        tmp+=obj_data[i1][2];
                        shangjie+=obj_data[i1][2];
                    }
                   n_1_1=tmp;
                   shangjie+=obj_data[n_1_6-1][2];
                   n_1_2=shangjie-1;
                }

                cout<<"debug yes";
                for(n_1_1=n_1_2+1;n_1_1<=n_1_2+obj_data[n_1_6][2];n_1_1++){//conflicts
                    //07
                    if(sch_data[n_1_1][3]==0){
                        // zuole yige chuli no problem
                        //clear_data(c_data,all_row);
                        for(int tmps=0;tmps<7;tmps++){
                            for(int js=0;js<2*max(9,cs_data[1][0]+1);js++){
                                c_data[tmps][js]=MAX;
                            }
                        }
                        //08 yes
                        cout<<"debug yes";
                        int tmp_max_3=max(1,pmf_data[n_1_1][1]);
                        tmp_max_3=max(tmp_max_3,pmb_data[n_1_1][1]);

                        for(int i3=0;i3<tmp_max_3;i3++){
                            c_data[0][i3]=i3+1;
                        }
                        for(int i4=0;i4<8;i4++){
                            c_data[3][i4]=0;
                        }
                        c_data[3][5]=-1;
                        c_data[3][7]=-1;
                        bool to_17=false;
                        //09
                        cout<<"debug yes";
                        if(pmf_data[n_1_1][1]==0){
                            c_data[3][0]=-1;
                            to_17=true;
                            cout<<"";
                        }
                        if(pmf_data[n_1_1][1]>0||to_17){

                            if(!to_17){
                                //10 yes
                                for(int i5=0;i5<=pmf_data[n_1_1][1]-1;i5++){
                                    c_data[1][i5]=pmf_data[n_1_1][2+i5];
                                }
                                //11
                               int n_2_1=0;
                               int n_2_4=0;
                               for(n_2_1=0;n_2_1<=pmf_data[n_1_1][1]-1;n_2_1++){

                                    if(n_2_1+1<=pmf_data[n_1_1][1]){
                                        //12 code yes
                                        int n_2_2=0;
                                        if(n_2_1==0)
                                            n_2_2=0;
                                        else if(n_2_1>=1){
                                            int tmp3=0;
                                            for(int i6=0;i6<=n_2_1-1;i6++){
                                                tmp3+=pmf_data[n_1_1][2+i6];
                                            }
                                            n_2_2=tmp3;
                                        }
                                        //14
                                        int n_2_3=3+pmf_data[n_1_1][1]+n_2_2;
                                        //15

                                        for(;n_2_3<=pmf_data[n_1_1][2+n_2_1]+2+pmf_data[n_1_1][1]+n_2_2;n_2_3++){


                                            //16 yes
                                            if(sch_data[pmf_data[n_1_1][n_2_3-1]-1][3]==0){
                                                continue;
                                            }
                                            if(sch_data[pmf_data[n_1_1][n_2_3-1]-1][3]==-1){
                                                c_data[1][n_2_1]=-1;
                                                c_data[3][0]+=1;

                                            }
                                            if(sch_data[pmf_data[n_1_1][n_2_3-1]-1][3]==1){
                                                c_data[1][n_2_1]-=1;

                                            }
                                        }

                                        //n_2_3> ......
                                        if(c_data[1][n_2_1]==0){
                                            n_2_4+=1;
                                            c_data[4][2*n_2_4-1-1]=n_2_1+1;
                                            c_data[4][2*n_2_4-1]=-1;
                                            c_data[3][2]+=1;

                                        }
                                        if(c_data[1][n_2_1]!=0){
                                            continue;
                                            //n_2_1++
                                        }
                                   }

                                }
                                 cout<<"debug"<<endl;
                               //13 code yes
                               if(n_2_1+1>=pmf_data[n_1_1][1]){
                                   if(c_data[3][2]==0&&
                                           c_data[3][0]==pmf_data[n_1_1][1]){

                                       sch_data[n_1_1][3]=-1;
                                       continue;
                                   }
                                   if(c_data[3][2]==0 && c_data[3][0]<pmf_data[n_1_1][1]){
                                       continue;
                                   }
                               }

                            }

                           //17
                           if(pmb_data[n_1_1][1]>0||to_17){
                               //18 yes
                               for(int i7=0;i7<=pmb_data[n_1_1][1]-1;i7++){//important yes
                                   c_data[2][i7]=pmb_data[n_1_1][2+i7];
                               }
                               int n_2_11=0;
                               int n_2_14=0;
                               for(n_2_11=0;n_2_11<=pmb_data[n_1_1][1]-1;n_2_11++){
                                   if(n_2_11<=pmb_data[n_1_1][1]-1){
                                       //21
                                       int n_2_12=0;
                                       if(n_2_11==0){
                                           n_2_12=0;
                                       }else if(n_2_11>=1){
                                           int tmp3=0;
                                           for(int i8=0;i8<=n_2_11-2;i8++){
                                               tmp3+=pmb_data[n_1_1][2+i8];
                                           }
                                           n_2_12=tmp3;
                                       }
                                       //22,23
                                       int n_2_13=3 + pmb_data[n_1_1][1];
                                       for(n_2_13=3 + pmb_data[n_1_1][1]; n_2_13<=pmb_data[n_1_1][1] + 2 + n_2_12  + pmb_data[n_1_1][2+n_2_11]; n_2_13++){
                                           //24 yes
                                           if(sch_data[pmb_data[n_1_1][n_2_13-1]-1][3]==-1){
                                               c_data[3][n_2_11]=-1;
                                               c_data[3][1]+=1;
                                               break;
                                               //n_2_11+1
                                               //to 20
                                           }
                                           if(sch_data[pmb_data[n_1_1][n_2_13-1]-1][3]>=0){
                                               c_data[2][n_2_11]-=1;
                                               continue;
                                               //to 23

                                           }
                                       }
                                       //23 yes
                                       if(n_2_13>=pmb_data[n_1_1][1] + 2 + n_2_12 + pmb_data[n_1_1][2+n_2_11]){
                                            if(c_data[2][n_2_11]==0){
                                                n_2_14+=1;
                                                c_data[2][n_2_11]=0;
                                                c_data[5][2*n_2_14- 1 - 1]=n_2_11+1;
                                                c_data[5][2* n_2_14 -1]=-1;
                                                c_data[3][3]+=1;
                                                continue;
                                                //n_2_11++
                                            }else{
                                                continue;
                                            }
                                           //nothing to do and n_2_11+1
                                           //to 20
                                       }
                                   }
                               }
                               if(n_2_11>=pmb_data[n_1_1][1]-1){
                                   if(c_data[3][3]>0){
                                        //nothing to do and to 25
                                       //to 25 end the for
                                   }
                                   if(c_data[3][3]==0){
                                       sch_data[n_1_1][3]=-1;
                                       break;
                                       //n_1_1++
                                   }
                               }
                           }
                           //25
                           bool to_36=false;
                           //if1
                           if(pmf_data[n_1_1][1]==pmb_data[n_1_1][1]&&pmb_data[n_1_1][1]==0){
                               c_data[3][4]=0;
                               to_36=true;
                           }
                           //if2
                           else if(pmf_data[n_1_1][1]==0&& c_data[3][3]>0){
                               c_data[3][4]=0;
                               for(int i9=0;i9<=c_data[3][3]-1;i9++){
                                   c_data[5][2*(i9+1)-1]=1;
                               }
                               to_36=true;
                           }
                           //if3
                           else if(c_data[3][2]>0&&pmb_data[n_1_1][1]==0){
                               c_data[3][4]=c_data[3][2];
                               for(int i9=0;i9<=c_data[3][2] - 1;i9++){
                                   c_data[4][2*(i9+1)-1]=1;
                               }
                               to_36=true;//to 36
                           }
                           //if4 yes
                           else if(c_data[3][2]>0 && c_data[3][3]>0){
                               //26
                               if(inv_data[n_1_1][1]==0){
                                   c_data[3][4]=c_data[3][2];
                                   for(int i7=0;i7<c_data[3][2];i7++){
                                       c_data[6][i7]=c_data[4][2*(i7+1)-1-1];
                                   }
                                   for(int a1=0;a1<=c_data[3][2]-1;a1++){
                                       c_data[4][2*(a1+1)-1]=1;
                                   }
                                   for(int a2=0;a2<=c_data[3][3]-1;a2++){
                                       c_data[5][2*(a2+1)-1]=1;
                                   }
                                   to_36=true;//to 36
                               }
                               //mark
                               if(inv_data[n_1_1][1]>0){
                                   int n_2_21=0;
                                   //
                                   for(n_2_21=0;n_2_21<=c_data[3][2]-1;n_2_21++){
                                       //28
                                       int n_2_22=0;
                                       //29
                                       for(n_2_22=0;n_2_22<=inv_data[n_1_1][1] - 1;n_2_22++){
                                           //30
                                          if(n_2_22<=inv_data[n_1_1][1]-1){
                                              //30
                                              bool is_exit=false;
                                              for(int a2=1;a2<=c_data[3][3];a2++){
                                                  if(c_data[5][2*a2-1 -1]==inv_data[n_1_1][2+ 2*(n_2_22+1)- 1]){
                                                      is_exit=true;
                                                      break;
                                                  }
                                              }
                                              if(c_data[4][2*(n_2_21+1) - 1 - 1] - inv_data[n_1_1][2+ 2*(n_2_22+1)-1 - 1]==0 && is_exit){
                                                  c_data[4][2*(n_2_21+1)-1]=0;
                                                  c_data[3][4]+=1;
                                                  c_data[6][c_data[3][4]-1] = c_data[4][2*(n_2_21+1)-1-1];
                                                  break;
                                                  //n_2_21+1
                                                  //num_ceng=5;//to 27
                                              }
                                              if(c_data[4][2*(n_2_21+1) - 1 - 1] - inv_data[n_1_1][2+ 2*(n_2_22+1)-1 - 1]==0 && !is_exit){
                                                  c_data[4][2*(n_2_21+1)-1]-=1;
                                                  break;
                                                  //n_2_21 +1
                                                  //num_ceng=6;//to 29
                                              }
                                              if(c_data[4][2*(n_2_21+1)-1-1]  -inv_data[n_1_1][2+2*(n_2_22+1)-1-1]!=0){
                                                  c_data[4][2*(n_2_21+1)-1]+=1;
                                                  continue;
                                                  //n_2_22+1
                                              }
                                          }
                                       }
                                       //29 yes
                                       if(n_2_22>inv_data[n_1_1][1]-1){//important
                                           if(c_data[4][2*(n_2_21+1)-1]==inv_data[n_1_1][1] - 1){
                                               c_data[4][2*(n_2_21+1)-1]=1;
                                               c_data[3][4]+=1;
                                               c_data[6][c_data[3][4]-1]=c_data[4][2*(n_2_21+1)-1-1];
                                               //num_ceng=5;//to 27
                                               continue;
                                               //n_2_21 +1
                                           }
                                           if(c_data[4][2*(n_2_21+1)-1]<inv_data[n_1_1][1]-1){
                                               c_data[4][2*(n_2_21+1)-1]=-1;
                                               //num_ceng=5;//to 27;
                                           }
                                       }
                                   }
                                   //27
                                   if(n_2_21+1>c_data[3][2]){
                                       if(c_data[3][4]==0){
                                           if(pmf_data[n_1_1][1]-c_data[3][0]-c_data[3][2]==0){
                                               sch_data[n_1_1][3]=-1;
                                               //n_1_1++
                                               continue;
                                           }
                                           if(pmf_data[n_1_1][1]-c_data[3][0]-c_data[3][2]>0){
                                               continue;
                                           }
                                       }
                                       if(c_data[3][4]>0){
                                          //to 36
                                           to_36=true;
                                       }
                                   }
                               }
                           }
                           //36
                           int tmp3=0;
                           tmp3=max(1,n_1_5);
                           //n_1_5 is not the variable
                           clear_data(sce_data,1,cs_data[1][0],2,1+2*tmp3);
                           int n_7_1=0;
                           cs_data[4][0]=0;
                           //37
                           if(n_1_5==0){

                               sch_data[n_1_1][4]=1;
                               sch_data[n_1_1][3]=1;
                               sch_data[n_1_1][5]=max(cojO_data[o_data[n_1_1][3]-1][1],o_data[n_1_1][6]);
                               n_1_5=1;
                               presh_data[n_1_1][1]=0;
                               continue;
                               //n_1_1 +1
                               // return to 06
                           }
                           if(n_1_5>0){
                                //to 38

                           }
                           //38
                           cout<<"";
                           int n_3_11=0;
                           //39
                           for(n_3_11=0;n_3_11<=c_data[3][4];n_3_11++){
                               bool to_42=false;
                                int n_3_12=0;
                               if(c_data[3][4]==0){
                                           to_42=true;

                               }
                               if(c_data[3][4]>0&&n_3_11==0&&!to_42){
                                        continue;
                                   //n_3_11++
                               }
                               if(c_data[3][4]>0&&n_3_11>0&&!to_42){
                                   //41
                                   if(c_data[6][(n_3_11)-1]==1){
                                       n_3_12=0;
                                   }
                                   else  if(c_data[6][(n_3_11)]>=2){
                                       int tmp4=0;
                                       for(int b=0;b<c_data[6][(n_3_11-1 )-1 ] -1;b++){
                                           tmp4+=pmf_data[n_1_1][b+2];
                                       }
                                       n_3_12=tmp4;
                                   }
                               }
                               //42
                               //have checked
                               int n_3_1=0;
                               for(n_3_1=0;n_3_1<=n_1_5-1;n_3_1++){
                                       //44
                                       clear_data(coj_data,1,cs_data[2][0],2,5+2*cs_data[1][0]);
                                       for(int c=1;c<=cs_data[2][0];c++){
                                            coj_data[c-1][1]=0;
                                            coj_data[c-1][2]=0;
                                       }

                                           //45
                                           int n_3_2=0;
                                           for(n_3_2=0;n_3_2<=cs_data[1][0]-1;n_3_2++){//46
                                               //47
                                               if(sch_data[n_3_2][3]==1){
                                                   //48
                                                   coj_data[o_data[n_3_2][3]-1][3+2*(sch_data[n_3_2][4+2*(n_3_1+1)-1-1])-1-1]=n_3_2+1;
                                                   coj_data[o_data[n_3_2][3]-1][1]+=1;
                                                   if(c_data[3][4]==0){
                                                       //50
                                                       continue;
                                                       //to 46
                                                   }
                                                   if(c_data[3][4]>0){
                                                       bool is_exit=false;
                                                       for(int d=1;d<=pmf_data[n_1_1][2+c_data[6][(n_3_11)-1]-1];d++){
                                                           if(n_3_2+1-pmf_data[n_1_1][2+pmf_data[n_1_1][1]+n_3_12+d-1]==0){
                                                               is_exit=true;
                                                               break;
                                                           }
                                                       }
                                                       if(is_exit){
                                                           coj_data[o_data[n_3_2][3]-1][2]=max(coj_data[o_data[n_3_2][3]-1][2],sch_data[n_3_2][4+2*(n_3_1+1)-1-1]);
                                                          //50
                                                       }else{
                                                           //50 not exist
                                                           continue;
                                                           //num_ceng=6;//to 46
                                                       }

                                                   }
                                               }
                                               //47
                                               if(sch_data[n_3_2][3]==-1||sch_data[n_3_2][3]==0){
                                                   continue;
                                                   //n_3_2++ to 46

                                               }
                                           }


                                           //51
                                           int n_6_1=0;
                                           int n_6_2=0;
                                           int n_6_3=0;
                                           int n_8_1=0;
                                           int n_5_1=0;
                                           //52
                                           for(n_5_1=0;n_5_1<=cs_data[2][0]-1;n_5_1++){
                                               //53
                                               if(n_5_1+1==o_data[n_1_1][3]){
                                                   n_6_2=n_6_1;
                                                   n_6_1=n_6_1+coj_data[n_5_1][1]+1;
                                                    //to 52
                                                   continue;
                                               }
                                               if(n_5_1!=o_data[n_1_1][3]){
                                                   //54
                                                   if(coj_data[n_5_1][1]==0){
                                                        //to 52
                                                       continue;
                                                   }
                                                   if(coj_data[n_5_1][1]!=0){
                                                       int n_5_2=0;
                                                       //55
                                                       for(n_5_2=0;n_5_2<=coj_data[n_5_1][1]-1;n_5_2++){
                                                           //56
                                                           //57
                                                           n_6_1+=1;
                                                           coj_data[n_5_1][3+2*(n_5_2+1)-1]=n_6_1;
                                                           x_data[n_6_1-1][0]=n_6_1;
                                                           aim_data[n_6_1-1][0]=n_6_1;

                                                           //if1
                                                           if((o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][7]  -   o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][6])
                                                                   >o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][5]){
                                                               int tmp4=0;
                                                               tmp4=cojO_data[o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][3]-1][1];
                                                               int tmp5=0;
                                                               tmp5=o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][6];
                                                               aim_data[n_6_1-1][1]=max(tmp4,tmp5);
                                                               int tmp6=cojO_data[o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][3]-1][2]
                                                                       -o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][5];
                                                               int tmp7=o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][7]
                                                                       -o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][5];
                                                               aim_data[n_6_1-1][2]=min(tmp6,tmp7);
                                                               aim_data[n_6_1-1][4]=2;

                                                           }
                                                           //if2
                                                           if(o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][7]    -   o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][6]
                                                                   ==o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][5]){
                                                               aim_data[n_6_1-1][1]=o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][6];

                                                               aim_data[n_6_1-1][2]=o_data[coj_data[n_5_1][3+2*(n_5_2+1)-1-1]-1][6];
                                                               aim_data[n_6_1-1][4]=1;
                                                           }

                                                           if(n_5_2+1==1){
                                                               //58
                                                               continue;//
                                                               //n_5_2+1

                                                           }
                                                           if(n_5_2+1>1){
                                                                int n_1_21=0;
                                                               if(coj_data[n_5_1][3+2*(n_5_2+1)-1-1] > coj_data[n_5_1][3+2*(n_5_2+1-1)-1-1]){
                                                                   //
                                                                   n_1_21=invt_data[ coj_data[n_5_1][3+2*(n_5_2+1)-1-1] -1]  [ 1+ coj_data[n_5_1][3+2*(n_5_2)-1-1] -1 ];
                                                               }
                                                               if(coj_data[n_5_1][3+2*(n_5_2+1)-1-1] < coj_data[n_5_1][3+2*(n_5_2)-1-1]){
                                                                   n_1_21=invt_data[ coj_data[n_5_1][3+2*(n_5_2)-1-1] -1]  [ 1+ 2*coj_data[n_5_1][3+2*(n_5_2+1)-1-1] -1 -1];
                                                               }
                                                               int tmp4=n_1_21/my_pow(10,9);
                                                                switch(tmp4){

                                                                case 1:
                                                                {
                                                                    //A and B then to 58
                                                                    //operation A
                                                                    n_8_1+=1;
                                                                    m_data[n_8_1-1][0]=o_data[coj_data[n_5_1][3+2*(n_5_2+1-1)-1-1] -1][5]+
                                                                            max( (n_1_21- (n_1_21/my_pow(10,9)   *   my_pow(10,9)  ) ) /my_pow(10,5)
                                                                                 ,cojO_data[n_5_1][3] );
                                                                    m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                    m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                    m0_data[n_8_1-1][0]=-1;
                                                                    //operation B
                                                                    n_8_1+=1;

                                                                    m_data[n_8_1-1][0]=o_data[coj_data[n_5_1][3+2*(n_5_2+1-1)-1-1]  -1][5]  +
                                                                           max( n_1_21 - (n_1_21/my_pow(10,9))*my_pow(10,9) - (n_1_21-(n_1_21/my_pow(10,9)*my_pow(10,9)))/my_pow(10,5)*my_pow(10,5),
                                                                                cojO_data[n_5_1][3]);
                                                                    m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                    m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                    m0_data[n_8_1-1][0]=1;
                                                                    break;
                                                                }

                                                                case  2:
                                                                {
                                                                    //operation A
                                                                    n_8_1+=1;
                                                                    m_data[n_8_1-1][0]=o_data[coj_data[n_5_1][3+2*(n_5_2+1-1)-1-1] -1][5]+
                                                                            max( (n_1_21- (n_1_21/my_pow(10,9)   *   my_pow(10,9)  ) ) /my_pow(10,5) ,
                                                                                 cojO_data[n_5_1][3] );
                                                                    m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                    m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                    m0_data[n_8_1-1][0]=-1;
                                                                    break;
                                                                }

                                                                case 3:
                                                                {
                                                                    //B then to 58
                                                                    //operation B
                                                                    n_8_1+=1;
                                                                    m_data[n_8_1-1][0]=o_data[coj_data[n_5_1][3+2*(n_5_2+1-1)-1-1]  -1][5]  +
                                                                           max( n_1_21 - (n_1_21/my_pow(10,9))*my_pow(10,9) - (n_1_21-(n_1_21/my_pow(10,9)*my_pow(10,9)))/my_pow(10,5)*my_pow(10,5),
                                                                                cojO_data[n_5_1][3]);
                                                                    m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                    m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                    m0_data[n_8_1-1][0]=1;
                                                                    break;
                                                                }

                                                                case 4:
                                                                {
                                                                    //Z then to 58
                                                                    n_8_1+=1;
                                                                    m_data[n_8_1-1][0]=o_data[coj_data[n_5_1][3+2*(n_5_2+1-1)-1-1]-1 ][5] +
                                                                            max((n_1_21-(n_1_21/my_pow(10,9)*my_pow(10,9)))/my_pow(10,5)
                                                                                ,cojO_data[n_5_1][3]);
                                                                    m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                    m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                    m0_data[n_8_1-1][0]=0;
                                                                    break;
                                                                }

                                                                default:
                                                                    break;
                                                                }
                                                                //58
                                                                continue;
                                                               //num_ceng=6;//to 56


                                                           }


                                                       }
                                                       //56
                                                       if(n_5_2+1>=coj_data[n_5_1][1]){
                                                           continue;
                                                           //n_5_1++
                                                           //num_ceng=6;//to 52
                                                       }

                                                   }
                                               }
                                           }
                                           //xiang dangyu n_5_1 >cs_data[3][1]
                                            n_5_1=o_data[n_1_1][3]-1;
                                            clear_data(coj1_data,1,cs_data[2][0],2,5+2*cs_data[1][0]);
                                           int n_5_3=0;

                                           for(n_5_3=0;n_5_3<=coj_data[n_5_1][1]+1-coj_data[n_5_1][2]-1;n_5_3++){
                                                    coj1_data[n_5_1][1+2*(coj_data[n_5_1][2]+n_5_3+1)-1-1]=n_1_1+1;
                                                    //62 yes
                                                    if(coj_data[n_5_1][2]+n_5_3+1>1){
                                                        for(int i1=1;i1<=coj_data[n_5_1][2]+n_5_3+1-1;i1++){
                                                            coj1_data[n_5_1][1+2*i1-1-1]=coj_data[n_5_1][3+2*i1-1-1];
                                                        }
                                                    }
                                                    //63 yes
                                                    if(coj_data[n_5_1][2]+n_5_3+1<coj_data[n_5_1][1]+1){
                                                       for(int d=coj_data[n_5_1][2]+n_5_3+1+1;d<=coj_data[n_5_1][1]+1;d++){
                                                            coj1_data[n_5_1][1+2*d-1-1]=coj_data[n_5_1][3+2*(d-1)-1-1];
                                                       }
                                                    }
                                                    //64 yes
                                                    n_6_3=n_6_1;
                                                    n_6_1=n_6_2;
                                                    int n_5_12=0;
                                                  int n_1_31=0;
                                                    for(n_5_12=0;n_5_12<=coj_data[n_5_1][1]+1-1;n_5_12++){

                                                        //66 yes
                                                        n_6_1+=1;
                                                        coj1_data[n_5_1][1+2*(n_5_12+1)-1]=n_6_1;
                                                        x_data[n_6_1-1][0]=n_6_1;
                                                        aim_data[n_6_1-1][0]=n_6_1;

                                                        //if1 yes
                                                        if(o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][7]  -   o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]][6]
                                                                >o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]][5]){
                                                            int tmp4=0;
                                                            tmp4=cojO_data[o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][3]-1][1];
                                                            int tmp5=0;
                                                            tmp5=o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1] [6];
                                                            aim_data[n_6_1-1][1]=max(tmp4,tmp5);
                                                            int tmp6=cojO_data[o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][3]-1][2]
                                                                    -o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][5];
                                                            int tmp7=o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]][7]
                                                                    -o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][5];
                                                            aim_data[n_6_1-1][2]=min(tmp6,tmp7);
                                                            aim_data[n_6_1-1][4]=2;

                                                        }
                                                        //if2 yes
                                                        if(o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][7]   -    o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][6]
                                                                ==o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][5]  ){
                                                            aim_data[n_6_1-1][1]=o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][6];

                                                            aim_data[n_6_1-1][2]=o_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]-1][6];
                                                            aim_data[n_6_1-1][4]=1;
                                                        }

                                                        if(n_5_12+1>1){
                                                                    //all time
                                                                   if(coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]  >  coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]){
                                                                       n_1_31=invt_data[coj1_data[n_5_1][1+2*(n_5_12+1)-1-1]]  [1+2*coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]];
                                                                   }
                                                                   if(coj1_data[n_5_1][1+2*(n_5_12+1-1)-1]  <  coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]){
                                                                       n_1_31=invt_data[coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]]  [1+2*coj1_data[n_5_1][1+2*(n_5_12+1)-1-1] - 1];
                                                                   }
                                                                   int swi=n_1_31/pow(10,9);
                                                                   switch(swi){
                                                                   case 1:
                                                                   {
                                                                       //implement C and D,then to 67
                                                                       //operation C yes
                                                                       n_8_1+=1;
                                                                       int c_tmp=max((n_1_31-(n_1_31)/my_pow(10,9)*my_pow(10,9))/my_pow(10,5), cojO_data[n_5_1][3]);
                                                                       m_data[n_8_1][0]=o_data[ coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]][5]  +
                                                                              c_tmp ;
                                                                       m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                       m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                       m0_data[n_8_1-1][0]=-1;
                                                                       //operation D yes
                                                                       n_8_1+=1;
                                                                       int d_tmp=max(
                                                                                   n_1_31-
                                                                                    (n_1_31/my_pow(10,9)*my_pow(10,9))
                                                                                      -(n_1_31-n_1_31/my_pow(10,9)*my_pow(10,9))/my_pow(10,5)*my_pow(10,5)
                                                                                   ,cojO_data[n_5_1][3]);
                                                                       m_data[n_8_1][0]=o_data[ coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]][5]  + d_tmp;
                                                                       m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                       m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                       m0_data[n_8_1-1][0]=1;
                                                                       break;
                                                                   }

                                                                   case 2:
                                                                   {
                                                                       //implement C ,then to 67
                                                                       //operation C
                                                                       n_8_1+=1;
                                                                       int tmp_m=(n_1_31-(n_1_31)/my_pow(10,9)*pow(10,9))/pow(10,5);
                                                                       m_data[n_8_1][0]=o_data[ coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]][5]  +
                                                                               max(tmp_m,cojO_data[n_5_1][3]);
                                                                       m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                       m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                       m0_data[n_8_1-1][0]=-1;
                                                                       break;
                                                                   }

                                                                   case 3:
                                                                   {
                                                                       //implement D,then to 67
                                                                       //operation D
                                                                       n_8_1+=1;
                                                                       int tmp_s=n_1_31-
                                                                               (n_1_31/pow(10,9)*pow(10,9))
                                                                                 - (n_1_31-n_1_31/pow(10,9)*pow(10,9))/pow(10,5)*pow(10,5);
                                                                       int d_tmp=max(
                                                                                   tmp_s
                                                                                   ,cojO_data[n_5_1][3]);
                                                                       m_data[n_8_1][0]=o_data[ coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]][5]  + d_tmp;
                                                                       m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                       m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                       m0_data[n_8_1-1][0]=1;
                                                                       break;
                                                                   }

                                                                   case 4:
                                                                   {
                                                                       //implement Z,then to 67
                                                                       //operation Z yes
                                                                       n_8_1+=1;
                                                                       int tmp_p=(n_1_31-n_1_31/pow(10,9)*pow(10,9));
                                                                       m_data[n_8_1-1][0]=o_data[coj1_data[n_5_1][1+2*(n_5_12+1-1)-1-1]][5]+
                                                                               max(tmp_p,cojO_data[n_5_1][3]);
                                                                       m_data[n_8_1-1][1+n_6_1-1]=1;
                                                                       m_data[n_8_1-1][1+n_6_1-1-1]=-1;
                                                                       m0_data[n_8_1-1][0]=0;
                                                                       break;
                                                                   }

                                                                   default:
                                                                       break;
                                                                   }

                                                               }else{
                                                            continue;//to 65;
                                                        }
                                                    }

                                                    //65 yes
                                                    bool to_72=false;
                                                    if(n_5_12+1>coj_data[n_5_1][1]+1){
                                                        if(c_data[3][4]>0){
                                                                //to 67
                                                        }
                                                        if(c_data[3][4]==0){
                                                               //to 72
                                                            to_72=true;
                                                        }
                                                    }
                                                    //67 code
                                                    int n_9_1=0;
                                                    int n_1_41=0;
                                                   if(!to_72){

                                                       for(n_9_1=0;n_9_1<=cs_data[2][0]-1;n_9_1++){
                                                           if(n_9_1+1==o_data[n_1_1][3]){
                                                               continue;
                                                               //to 68
                                                           }
                                                           if(n_9_1+1!=o_data[n_1_1][3]){
                                                               if(coj_data[n_9_1][2]==0){
                                                                   continue;
                                                                   //to 68
                                                               }
                                                               //71 yes
                                                               if(coj_data[n_9_1][2]!=0){
                                                                   if(n_1_1+1>coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1-1]){
                                                                       n_1_41=invt_data[n_1_1][1+2*(coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1-1])-1];
                                                                   }
                                                                   if(n_1_1+1<coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1-1]){
                                                                       n_1_41=invt_data[coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1-1]][1+2*(n_1_1+1)-1-1];
                                                                   }

                                                                   int swi=n_1_41/pow(10,9);
                                                                   switch (swi) {
                                                                   case 1:
                                                                   {
                                                                       //implement E and F, then to 72
                                                                       //operation E yes
                                                                       n_8_1+=1;
                                                                       m_data[n_8_1-1][0]=o_data[coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1-1]-1][5]
                                                                               + (n_1_41-  n_1_41/my_pow(10,9)*my_pow(10,9)   )/my_pow(10,5);

                                                                       m_data[n_8_1-1][1+coj1_data[o_data[n_1_1][3]-1][1+2*(coj_data[o_data[n_1_1][3]-1][2])+n_5_3+1-1]-1]=1;
                                                                       m_data[n_8_1-1][1+coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1]-1]=-1;
                                                                       m0_data[n_8_1-1][0]=-1;
                                                                       //operation F yes
                                                                       n_8_1+=1;
                                                                        m_data[n_8_1-1][0]=o_data[coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1-1]-1][5]
                                                                                + (n_1_41)-n_1_41/my_pow(10,9)*my_pow(10,9)-(n_1_41-n_1_41/my_pow(10,9)*my_pow(10,9))/my_pow(10,5)*my_pow(10,5);
                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_1_1][3]-1]  [1+2*(coj_data[o_data[n_1_1][3]-1][2])+n_5_3+1-1]-1]=1;
                                                                        m_data[n_8_1-1][1+coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1]-1]=-1;
                                                                        m0_data[n_8_1-1][0]=1;
                                                                       break;
                                                                   }

                                                                   case 2:
                                                                   {
                                                                       //implement E,then to 72
                                                                       //operation E yes
                                                                       n_8_1+=1;
                                                                       m_data[n_8_1-1][0]=o_data[coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1-1]-1][5]
                                                                               + (n_1_41-  n_1_41/my_pow(10,9)*my_pow(10,9)   )/my_pow(10,5);

                                                                       m_data[n_8_1-1][1+coj1_data[o_data[n_1_1][3]-1][1+2*(coj_data[o_data[n_1_1][3]-1][2])+n_5_3+1-1]-1]=1;
                                                                       m_data[n_8_1-1][1+coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1]-1]=-1;
                                                                       m0_data[n_8_1-1][0]=-1;
                                                                       break;
                                                                   }

                                                                   case 3:
                                                                   {
                                                                       //implement F,then to 72
                                                                       //operation F yes
                                                                       n_8_1+=1;
                                                                        m_data[n_8_1-1][0]=o_data[coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1-1]-1][5]
                                                                                + (n_1_41)-n_1_41/my_pow(10,9)*my_pow(10,9)-(n_1_41-n_1_41/my_pow(10,9)*my_pow(10,9))/my_pow(10,5)*my_pow(10,5);
                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_1_1][3]-1]  [1+2*(coj_data[o_data[n_1_1][3]-1][2])+n_5_3+1-1]-1]=1;
                                                                        m_data[n_8_1-1][1+coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1]-1]=-1;
                                                                        m0_data[n_8_1-1][0]=1;
                                                                       break;
                                                                   }

                                                                   case 4:
                                                                   {
                                                                       //implement Z,then to 72
                                                                       //operation Z
                                                                        n_8_1+=1;
                                                                        m_data[n_8_1-1][0]=o_data[coj_data[n_9_1][3+2*coj_data[n_9_1][2]-1]-1][5]
                                                                                + (n_1_41-n_1_41/my_pow(10,9)*my_pow(10,9))/my_pow(10,5);
                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_1_1][3]-1]  [1+2*(coj_data[o_data[n_1_1][3]-1][2])+n_5_3+1-1]-1]=1;
                                                                        m_data[n_8_1-1][1+coj_data[n_9_1][3+2*(coj_data[n_9_1][2])-1]-1]=-1;
                                                                        m0_data[n_8_1-1][0]=0;
                                                                       break;
                                                                   }

                                                                   default:
                                                                       break;
                                                                   }
                                                                   continue;
                                                               }
                                                           }
                                                       }

                                                   }
                                                    int n_9_2=0;
                                                    if(n_9_1+1>cs_data[2][0]){
                                                            //to 72
                                                    }
                                                    //72 code
                                                    int n_9_12=0;
                                                     clear_data(coj2_data,1,cs_data[2][0],2,5);
                                                    for(int d2=0;d2<=cs_data[2][0]-1;d2++){
                                                        coj2_data[d2][1]=0;
                                                    }
                                                    for(n_9_2=0;n_9_2<=cs_data[1][0]-1;n_9_2++){
                                                        //7201
                                                        clear_data(coj2_data,1,cs_data[2][0],2,5);
                                                        for(int d2=0;d2<cs_data[2][0]-1;d2++){
                                                            coj2_data[d2][1]=0;
                                                        }
                                                        //7302 yes
                                                        if(sch_data[n_9_2][3]==1){

                                                            if(presh_data[n_9_2][1+n_3_1]==0){
                                                                continue;
                                                                //n_9_2++
                                                            }
                                                            if(presh_data[n_9_2][1+n_3_1]>0){
                                                                if(presh_data[n_9_2][1+n_3_1]==1){
                                                                    n_9_12=0;
                                                                }
                                                                if(presh_data[n_9_2][1+n_3_1]>=2){
                                                                    int tmp4=0;
                                                                    for(int e=1;e<=presh_data[n_9_2][1+n_3_1]-1;e++){
                                                                        tmp4+=pmf_data[n_9_2][2+e-1];
                                                                    }
                                                                    n_9_12=tmp4;
                                                                }
                                                                int n_9_3=0;
                                                                //yes
                                                                for(n_9_3=0;n_9_3<=pmf_data[n_9_2][2+presh_data[n_9_2][n_3_1+1]-1]-1;n_9_3++){
                                                                    if(o_data[n_9_2][3]==o_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1]-1][3]){
                                                                        continue;
                                                                        //n_9_3 ++
                                                                    }
                                                                    if(o_data[n_9_2][3]!=o_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1]-1][3]){

                                                                        //yingshe
                                                                        //yes the extra instance
                                                                        if(coj2_data[o_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]]+n_9_12+1+n_9_3+1-1][3]-1][1]==0){
                                                                            if(
                                                                                    sch_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1]-1][4+2*(n_3_1+1)-1-1]
                                                                                    >= sch_data[   cs_data[2][1]+1 -1   ]  [4+2*(n_3_1+1)-1-1]){


                                                                                coj2_data[o_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1]-1][3]-1][1]
                                                                                        =pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1];
                                                                                continue;
                                                                                //to 7206
                                                                            }
                                                                            else{
                                                                                continue;
                                                                                //to 7206
                                                                            }
                                                                        }

                                                                        if(
                                                                                sch_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1]-1][4+2*(n_3_1+1)-1-1]
                                                                                >= sch_data[   cs_data[2][1]+1 -1   ]  [4+2*(n_3_1+1)-1-1]){


                                                                            coj2_data[o_data[pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1]-1][3]-1][1]
                                                                                    =pmf_data[n_9_2][2+pmf_data[n_9_2][1]+n_9_12+1+n_9_3+1-1];
                                                                            continue;
                                                                            //to 7206
                                                                        }
                                                                        else{
                                                                            continue;
                                                                            //to 7206
                                                                        }

                                                                    }
                                                                }
                                                                //mark
                                                                int n_9_4=0;
                                                                int n_9_22=0;
                                                                for(n_9_4=0;n_9_4<=cs_data[2][0]-1;n_9_4++){
                                                                    if(coj2_data[n_9_4][1]<=0){
                                                                        continue;
                                                                        //to 7210
                                                                    }
                                                                    if(coj2_data[n_9_4][1]>0){
                                                                        if(n_9_2+1>coj2_data[n_9_4][1]){
                                                                            //yes
                                                                            n_9_22=invt_data[n_9_2][1+2*(coj2_data[n_9_4][1])-1];
                                                                        }
                                                                        if(n_9_2+1<coj2_data[n_9_4][1]){
                                                                            n_9_22=invt_data[ coj2_data[n_9_4][1] -1] [1+2*(n_9_2+1)-1-1];
                                                                        }
                                                                        int tmp=n_9_22/my_pow(10,9);
                                                                        switch (tmp) {
                                                                        case 1:
                                                                        {
                                                                            //implement G and H,then to 73
                                                                            //operation G
                                                                            //yes
                                                                            n_8_1+=1;
                                                                            m_data[n_8_1-1][0]=o_data[coj2_data[n_9_4][1]-1] [5]+(n_9_22-n_9_22/my_pow(10,9)*my_pow(10,9))/my_pow(10,5);
                                                                            if(o_data[n_9_2][3]!=o_data[n_1_1][3]){
                                                                                int n_9_31=0;
                                                                                for(n_9_31=0;;n_9_31++){
                                                                                    if(coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }else{
                                                                                            continue;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][3+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }else{
                                                                                            continue;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=-1;
                                                                            }



                                                                            if(o_data[n_9_2][3]==o_data[n_1_1][3]){
                                                                                int n_9_51=0;
                                                                                for(n_9_51=0;;n_9_51++){
                                                                                    if(coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1-1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1]]=1;
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][1+2*(n_9_61+1)-1]]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=-1;
                                                                            }



                                                                            //operation H
                                                                            //yes
                                                                            n_8_1+=1;
                                                                            m_data[n_8_1-1][0]=o_data[coj2_data[n_9_4][1]-1][5]+
                                                                                    n_9_22-(n_9_22/my_pow(10,9)*my_pow(10,9))-(n_9_22-n_9_22/my_pow(10,9)*my_pow(10,9))/my_pow(10,5)*my_pow(10,5);
                                                                            if(o_data[n_9_2][3]!=o_data[n_1_1][3]){
                                                                                int n_9_31=0;
                                                                                for(n_9_31=0;;n_9_31++){
                                                                                    if(coj_data[o_data[n_9_2][3]][3+2*(n_9_31+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_41+1)-1]-1]= -1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][1+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=1;
                                                                            }


                                                                            if(o_data[n_9_2][3]==o_data[n_1_1][3]){
                                                                                int n_9_51=0;
                                                                                for(n_9_51=0;;n_9_51++){
                                                                                    if(coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][1+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=1;
                                                                            }
                                                                            break;
                                                                        }

                                                                        case 2:
                                                                        {
                                                                            //operation G
                                                                            //yes
                                                                            n_8_1+=1;
                                                                            m_data[n_8_1-1][0]=o_data[coj2_data[n_9_4][1]-1] [5]+(n_9_22-n_9_22/my_pow(10,9)*my_pow(10,9))/my_pow(10,5);
                                                                            if(o_data[n_9_2][3]!=o_data[n_1_1][3]){
                                                                                int n_9_31=0;
                                                                                for(n_9_31=0;;n_9_31++){
                                                                                    if(coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }else{
                                                                                            continue;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][3+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }else{
                                                                                            continue;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=-1;
                                                                            }



                                                                            if(o_data[n_9_2][3]==o_data[n_1_1][3]){
                                                                                int n_9_51=0;
                                                                                for(n_9_51=0;;n_9_51++){
                                                                                    if(coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1-1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1]]=1;
                                                                                        break;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][1+2*(n_9_61+1)-1]]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=-1;
                                                                            }


                                                                            break;
                                                                        }

                                                                        case 3:
                                                                        {
                                                                            //operation H
                                                                            //yes
                                                                            n_8_1+=1;
                                                                            m_data[n_8_1-1][0]=o_data[coj2_data[n_9_4][1]-1][5]+
                                                                                    n_9_22-(n_9_22/my_pow(10,9)*my_pow(10,9))-(n_9_22-n_9_22/my_pow(10,9)*my_pow(10,9))/my_pow(10,5)*my_pow(10,5);
                                                                            if(o_data[n_9_2][3]!=o_data[n_1_1][3]){
                                                                                int n_9_31=0;
                                                                                for(n_9_31=0;;n_9_31++){
                                                                                    if(coj_data[o_data[n_9_2][3]][3+2*(n_9_31+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_41+1)-1]-1]= -1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][1+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=1;
                                                                            }


                                                                            if(o_data[n_9_2][3]==o_data[n_1_1][3]){
                                                                                int n_9_51=0;
                                                                                for(n_9_51=0;;n_9_51++){
                                                                                    if(coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][1+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=1;
                                                                            }


                                                                            break;
                                                                        }

                                                                        case 4:
                                                                        {
                                                                            //operation Z
                                                                            n_8_1+=1;
                                                                            m_data[n_8_1-1][0]=o_data[coj2_data[n_9_4][1]-1][5]+
                                                                                    (n_9_22-n_9_22/my_pow(10,9)*my_pow(10,9))/my_pow(10,5);
                                                                            if(o_data[n_9_2][3]!=o_data[n_1_1][3]){
                                                                                int n_9_31=0;
                                                                                for(n_9_31=0;;n_9_31++){
                                                                                    if(coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj_data[o_data[n_9_2][3]-1][3+2*(n_9_31+1)-1]]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else{
                                                                                    int n_9_41=0;
                                                                                    for(n_9_41=0;;n_9_41++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_41+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][1+2*(n_9_41+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=0;
                                                                            }


                                                                           else{
                                                                                int n_9_51=0;
                                                                                for(n_9_51=0;;n_9_51++){
                                                                                    if(coj1_data[o_data[n_9_2][3]][1+2*(n_9_51+1)-1-1]==n_9_2+1){
                                                                                        m_data[n_8_1-1][1+coj1_data[o_data[n_9_2][3]-1][1+2*(n_9_51+1)-1]-1]=1;
                                                                                        break;
                                                                                    }
                                                                                    else{
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1!=o_data[n_1_1][3]){
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj_data[n_9_4][3+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj_data[n_9_4][3+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                if(n_9_4+1==o_data[n_1_1][3]){
                                                                                    int n_9_61=0;
                                                                                    for(n_9_61=0;;n_9_61++){
                                                                                        if(coj1_data[n_9_4][1+2*(n_9_61+1)-1-1]==coj2_data[n_9_4][1]){
                                                                                            m_data[n_8_1-1][1+coj1_data[n_9_4][1+2*(n_9_61+1)-1]-1]=-1;
                                                                                            break;
                                                                                        }
                                                                                    }
                                                                                }
                                                                                m0_data[n_8_1-1][0]=0;
                                                                            }

                                                                            break;
                                                                        }

                                                                        default:
                                                                            break;
                                                                        }

                                                                    }
                                                                }
//                                                                            continue;
                                                                //n_9_2+1
                                                                //to 7210

                                                            }

                                                        }else{
                                                            continue;
                                                            //n_9_2++
                                                        }
                                                    }
                                                    //73
                                                    //yes
                                                    if(n_9_2>=cs_data[1][0]-1){
                                                        n_6_1=max(n_6_1,n_6_3);
                                                        for(int d=0;d<=n_6_1-1;d++){
                                                            aim_data[d][3]=1;
                                                        }
                                                        //zichengxu
                                                        bool have=false;
                                                        have = train(m_data,m0_data,aim_data,xzi_data,n_8_1,n_6_1,n_8_2);
                                                        if(have){
                                                            cs_data[4][0]=1;
                                                        }else{
                                                            cs_data[4][0]=0;
                                                        }
                                                        clear_data(m_data,1,6*cs_data[1][0]+1+4*cs_data[1][0]*cs_data[2][0],1,1+2*cs_data[1][0]);
                                                        clear_data(m0_data,1,6*cs_data[1][0]+1+4*cs_data[1][0]*cs_data[2][0],1,6*cs_data[1][0]+1+4*cs_data[1][0]*cs_data[2][0]);
                                                        clear_data(aim_data,1,all_row+1,1,5);

                                                    }
                                                    if(cs_data[4][0]==1){
                                                        n_7_1+=1;
                                                    }
                                                    if(cs_data[4][0]==0){
                                                        clear_data(coj1_data,o_data[n_1_1][3],o_data[n_1_1][3],2,1+2*(coj_data[o_data[n_1_1][3]-1][1]+1));
                                                        continue;
                                                        //n_5_3++
                                                        //to 60
                                                    }
                                                    //75
                                                    int n_10_1=0;
                                                    for(int n_10_1=0;n_10_1<=cs_data[2][0];n_10_1++){
                                                        int n_11_1=0;
                                                        if(n_10_1==o_data[n_1_1][3]){
                                                             n_11_1=coj_data[o_data[n_1_1][3]-1][1]+1;
                                                        }else{
                                                            if(coj_data[n_10_1][1]>0){
                                                                n_11_1=coj_data[n_10_1][1];
                                                            }else if(coj_data[n_10_1][1]==0){
                                                                continue;
                                                            }
                                                        }
                                                        int n_10_3=0;
                                                        for(n_10_3=0;n_10_3<=n_11_1-1;n_10_3++){
                                                            //80
                                                            if(n_10_1+1==o_data[n_1_1][3]){
                                                                sce_data[coj1_data[n_10_1][1+2*(n_10_3+1)-1-1]][1+2*(n_7_1+1)-1-1]=n_10_3+1;
                                                                sce_data[coj1_data[n_10_1][1+2*(n_10_3+1)-1-1]][1+2*(n_7_1+1)-1]=xzi_data[coj1_data[n_10_1][1+2*(n_10_3+1)-1]];
                                                            }else{
                                                                sce_data[coj1_data[n_10_1][3+2*(n_10_3+1)-1-1]][1+2*(n_7_1+1)-1-1]=n_10_3+1;
                                                                sce_data[coj1_data[n_10_1][3+2*(n_10_3+1)-1-1]][1+2*(n_7_1+1)-1]=xzi_data[coj1_data[n_10_1][3+2*(n_10_3+1)-1]];
                                                            }
                                                            continue;
                                                            //to 79
                                                            //not finished
                                                        }
                                                        if(n_10_3>n_11_1-1){
                                                            break;
                                                            //to 76
                                                            //mark
                                                        }
                                                    }
                                                    //76 yes
                                                    if(n_10_1>=cs_data[2][0]){
                                                        //if1
                                                        if(c_data[3][4]==1){
                                                            int n_10_11=0;
                                                            for(n_10_11=0;n_10_11<=cs_data[1][0]-1;n_10_11++){
                                                                if(n_1_1==n_10_11){
                                                                    prsh_data[n_10_11][1+n_7_1]=c_data[6][(n_3_11+1)-1];
                                                                    continue;
                                                                }
                                                                else{
                                                                    prsh_data[n_10_11][1+n_7_1]=presh_data[n_10_11][1+n_3_1];
                                                                    continue;
                                                                }

                                                            }
                                                            clear_data(x_data,1,max(1,n_6_1),2,2);
                                                            clear_data(coj1_data,o_data[n_1_1][3],o_data[n_1_1][3],2,1+2*(coj_data[o_data[n_1_1][3]-1][1]+1)-1);
                                                            clear_data(aim_data,1,max(1,n_6_1),1,5);
                                                            break;
                                                            //n_5_3+1
                                                        }
                                                        //if2
                                                        if(c_data[3][4]==0){
                                                            int n_10_11=0;
                                                            for(n_10_11=0;n_10_11<=cs_data[1][0]-1;n_10_11++){
                                                                if(n_1_1==n_10_11){
                                                                    prsh_data[n_10_11][1+n_7_1]=0;
                                                                    continue;
                                                                }
                                                                else {
                                                                    prsh_data[n_10_11][1+n_7_1]=presh_data[n_10_11][1+n_3_1];
                                                                    continue;
                                                                    }

                                                                }

                                                            clear_data(x_data,1,max(1,n_6_1),2,2);
                                                            clear_data(coj1_data,o_data[n_1_1][3],o_data[n_1_1][3],2,1+2*(coj_data[o_data[n_1_1][3]][1]+1)-1);
                                                            clear_data(aim_data,1,max(1,n_6_1),1,5);
                                                            break;
                                                            //n_5_3+1
                                                        }

                                                        //if3
                                                        if(c_data[3][4]>1){
                                                            //to 82
                                                        }
                                                    }

                                                    //82
                                                    int n_12_1=0;
                                                    //84 yes
                                                    for(n_12_1=0;n_12_1<=n_7_1-1;n_12_1++){
                                                        int tmp_int=0;

                                                        for(int i=0;i<n_1_1;i++){
                                                            if(sch_data[i][3]==1){
                                                                tmp_int+=abs(sce_data[i][2*(n_12_1+1)-1-1]   -   sce_data[i][2*n_7_1-1-1]);
                                                            }

                                                        }
                                                        if(tmp_int!=0){
                                                            continue;
                                                        }else{
                                                            clear_data(sce_data,1,cs_data[1][0],1+2*n_7_1-1,1+2*n_7_1-1);
                                                            clear_data(sce_data,1,cs_data[1][0],1+2*n_7_1,1+2*n_7_1);
                                                            clear_data(x_data,1,max(1,n_6_1),1,2);
                                                            n_7_1-=1;
                                                            for(int c=1;c<=2*(coj_data[o_data[n_1_1][3]-1][1]+1);c++){
                                                                coj1_data[o_data[n_1_1][3]][c-1]=MAX;
                                                            }
                                                            clear_data(aim_data,1,max(1,n_6_1),1,5);
                                                            break;
                                                            //n_5_3 +1
                                                        }

                                                        int tmp=0;
                                                        //84
                                                        for(int i=0;i<=n_1_1;i++){
                                                            if(sch_data[i][3]==1){
                                                                 tmp+=abs(sce_data[i][2*(n_12_1+1)-1-1]   -    sce_data[i][2*(n_7_1+1)-1-1]);
                                                            }

                                                        }
                                                        if(tmp!=0){
                                                            continue;
                                                            //to 83
                                                        }
                                                        if(tmp==0){
                                                            clear_data(sce_data,1,cs_data[1][0],2*(n_7_1+1)-1-1,2*(n_7_1+1)-1-1);
                                                            clear_data(sce_data,1,n_1_1+1,2*(n_7_1+1)-1,2*(n_7_1+1)-1);
                                                            clear_data(x_data,1,max(n_6_1,1),1,2);
                                                            n_7_1-=1;
                                                            clear_data(coj1_data,o_data[n_1_1][3],o_data[n_1_1][3],2,1+2*(coj_data[o_data[n_1_1][3]][1]+1));
                                                            clear_data(aim_data,1,max(1,n_6_1),1,5);
                                                            break;
                                                            //to 60
                                                        }

                                                    }
                                                    //83 yes
                                                    if(n_12_1>=n_7_1-1){
                                                    //830102
                                                    int n_12_11=0;
                                                    for(n_12_11=0;n_12_11<=cs_data[1][0]-1;n_12_11++){
                                                        if(n_12_11==n_1_1){
                                                            prsh_data[n_12_11][1+n_7_1]=c_data[7][(n_3_11+1)-1];
                                                            continue;
                                                        }
                                                        else{
                                                            prsh_data[n_12_11][1+n_7_1]=presh_data[n_12_11][1+n_3_1];
                                                            continue;
                                                        }
                                                    }
                                                    clear_data(x_data,1,max(n_6_1,1),2,2);
                                                    clear_data(coj1_data,o_data[n_1_1][3],o_data[n_1_1][3],2,1+2*(coj_data[o_data[n_1_1][3]-1][1]+1));
                                                    clear_data(aim_data,1,max(n_6_1,1),1,5);
                                                    continue;
                                                    //to 60

                                                    }
                                       }

                                           //43

                           }
                               continue;
                               //n_3_11 ++

                           //39

                           }

                           if(n_3_11>=c_data[3][4]){//experiment
                               if(n_7_1==0){
                                   if(pmf_data[n_1_1][1]-c_data[3][0]-c_data[3][2]==0){
                                        sch_data[n_1_1][3]=-1;
                                        continue;
                                        //n_1_1+1
                                   }
                                   if(pmf_data[n_1_1][1]-c_data[3][0]-c_data[3][2]>0){
                                       continue;
                                       //n_1_1+1
                                   }

                               }
                               if(n_7_1>0){
                                   sch_data[n_1_1][3]=1;
                                   int tmp5=max(1,n_1_5);
                                   clear_data(sch_data,1,max(1,cs_data[1][0]),5,4+2*tmp5);
                                   clear_data(presh_data,1,max(1,cs_data[1][0]),2,1+max(1,n_1_5));
                                   for(int i=1;i<=cs_data[1][0];i++){
                                       for(int j=1;j<=2*(n_7_1);j++){//n_7_1 is not the variable
                                           sch_data[i-1][4+j-1]=sce_data[i-1][1+j-1];
                                       }
                                   }
                                   for(int i=1;i<=cs_data[1][0];i++){
                                       for(int j=1;j<=(n_7_1);j++){
                                            presh_data[i-1][1+j-1]=prsh_data[i-1][1+j-1];
                                       }
                                   }
                                   n_1_5=n_7_1;
                                   clear_data(sce_data,1,cs_data[1][0],2,1+2*(n_7_1));
                                   clear_data(prsh_data,1,cs_data[1][0],2,1+n_7_1);
                                   continue;//n_1_1+1
                                   //num_ceng=1;//to 06
                               }
                           }


                        }


                  }
                    else{
                              //n_1_1+=1;
                        if(n_1_1==2){
                            cout<<"";
                        }
                              continue;
                      }

                }


                int tmp2=0;
                for(int i2=0;i2<n_1_6;i2++){
                    tmp2+=obj_data[i2][2];
                }
                if(n_1_1>tmp2){
                    int tmpp=1;
                    for(int m=0;m<obj_data[n_1_6][2]-1;m++){
                        tmpp*=sch_data[n_1_2+m][3];
                    }
                    if(tmpp!=0){
                        continue;
                        //n_1_6=n_1_6+1;
                        //num_ceng=1;
                    }
                    if(tmpp==0){
                        //0501
                        n_1_6-=1;
                        continue;
                        //again from 0501
                        num_ceng=2;
                    }
                }

                //06
                if(n_1_1+1<=my_sum(1,n_1_6,3,obj_data)){
                    if(obj_data[n_1_6][3]==obj_data[n_1_6][4]){
                        n_1_6+=1;
                        num_ceng=1;
                    }
                    if(obj_data[n_1_6][3]>obj_data[n_1_6][4]){
                        num_ceng=2;
                    }
                }
        }

    }

    if(n_1_5>0){
        ofstream ofile;
        ofile.open("/home/wsc/project/result",ios::out);
        for(int i=0;i<cs_data[1][0];i++){
            int tmp=max(1,n_1_5);//n_1_5 is not the variable in for
            for(int j=0;j<4+2*tmp;j++){
                ofile<<sch_data[i][j]<<"\t";
            }
           ofile<<endl;
        }
    }

    if(n_1_5==0){
        cout<<"check your parameters"<<endl;
        return 0;
    }
    return a.exec();
}



