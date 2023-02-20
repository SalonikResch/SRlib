#ifndef SRlib_arguments
#define SRlib_arguments

vector <int> int2ints(int idx, vector <int> lengths){
    vector <int> indices; //Indices to return
    int len = 1; //current length to divide by
    for(int i=0;i<lengths.size();i++){
        indices.push_back(idx/len % lengths[i]);
        len *= lengths[i];
    }
    return(indices);
}

#endif