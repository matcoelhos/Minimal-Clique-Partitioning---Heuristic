#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "Graph.h"

using namespace std;

int main(int argc, char * argv[])
{
    vector<string> filelist;
    ifstream listfile;
    
    listfile.open("bmckList.txt");
    string s;
    while (getline(listfile, s))
    {
        filelist.push_back(s);
    }
    listfile.close();
    
    stringstream fs;
    
    fs << "result" << argv[1] << ".txt";
    
    ofstream resultfile;
    resultfile.open(fs.str());
    
    int index = 0;
    while (index < filelist.size()) {
    
        stringstream ss;
    
        ss << "Benchmark/" << filelist[index];
        Graph * G = NULL;
        char c;

        cout << "start up!" << endl;
        
        
        ifstream infile(ss.str());
        if (!infile)
        {
            cout << "ARQUIVO INDISPONIVEL" << endl;
            return 3;
        };

        string line;
        while (getline(infile, line))
        {
            istringstream i(line);

            char control;
            i >> control;
            if (control == 'p')
            {
                string s;
                int verts, a;
                i >> s >> verts >> a;
                G = new Graph(verts);

            }
            else if (control == 'e' && G != NULL)
            {
                vector<int> ins;
                int v1, v2;
                i >> v1 >> v2;
                ins.push_back(v1-1);
                ins.push_back(v2-1);
                G->insertEdge(ins);
            }
        }
        infile.close();

        if (G == NULL)
        {
            cout << "ALERTA! GRAFO NAO INICIALIZADO" << endl;
            return 4;
        }

        cout << "Verts: " << G->V << endl;
        cout << "Edges: " << G->E << endl << endl;
        
        vector<vector<int> > part;
    
        //G->cliquePartBTE(stoi(argv[2]));
        part = G->cliquePartBTGA(stoi(argv[1]), 20);
        
        resultfile << filelist[index] << "\t" << part.size() << endl;
    
        delete G;
        index ++;
    }
    resultfile.close();
    return 0;
}
