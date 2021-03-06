#include <iostream>
#include <cassert>
#include <algorithm>
#include "RepairPost.h"

using namespace std;

int main(int argc, char ** argv) {
  if(argc<2) {
    cout << "Usage: " << argv[0] << " <base_name>" << endl;
    return 0;
  }
  uint max_outdegree = 0;
  char * fname = argv[1];
  char * fout = new char[strlen(argv[1])+20];
  sprintf(fout,"%s.rebuilt",fname);
  FILE * fp = fopen64(fout,"w");
  assert(fp!=NULL);
  RepairPost * g = new RepairPost(fname);
  cout << "Nodes: " << g->nodes << endl;
  cout << "Edges: " << g->edges << endl;
	cout << "Graph size: " << g->size() << endl;
	cout << "Bits per link: " << 1.*g->size()/g->edges*8 << endl;
	fwrite(&g->nodes,sizeof(int),1,fp);
	fwrite(&g->edges,sizeof(long),1,fp);
  for(uint i=1;i<=g->nodes;i++) {
    uint * adj = g->adj(i);
//    uint * adj = g->adjSkip(i);
    uint outd = g->outdegree(i);
    sort(adj+1,adj+adj[0]+1);         //** !!!!!!!!!!!!  SORT VALUES  NO HACE FALTA !!!!
    int w = -i;
    fwrite(&w,sizeof(int),1,fp);
    
    for(uint j=1;j<=adj[0];j++) {
      fwrite(&adj[j],sizeof(int),1,fp);
      //if (i==1) printf("[%d]",adj[j]);
  	}
	
//	//**fari
//    for(uint i=1;i<=adj[0];i++){
//      int vall=adj[i]-1;
//      fwrite(&vall,sizeof(int),1,fp);
//    }
//    //**fari
      
    if(adj[0]>max_outdegree)
      max_outdegree=adj[0];
    if(adj[0]!=outd) {
      cout << "Error, el outdegree no coincide!!!" << endl;
      break;
    }
    free(adj);
  }
  cout << "Max outdegree: " << max_outdegree << endl;
	
	fclose(fp);
	delete [] fout;
  delete g;
  return 0;
}

