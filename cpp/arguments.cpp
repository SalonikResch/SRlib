#ifndef SRlib_arguments
#define SRlib_arguments

vector <int> int2int(int idx, vector <int> lengths){
    vector <int> indices; //Indices to return
    int len = 1; //current length to divide by
    for(int i=0;i<length.size();i++){
        indices.push_back(idx/len) % lengths[i];
        len *= lengths[i];
    }
    return(indices)
}

#endif