#include <iostream>
#include <string>
#include <time.h>
#include "DMWT.h"

using namespace std;
float timeNew;
int tileNum;

// for traigulation cmd line
// usage: TMP.exe <curveName> <useDT> <useMinSet> <areaWeight> <edgeWeight> <dihedralWeight> <useMinMaxDihedral> <saveObj> <useNormal>
// example: TMP.exe monkey 1 1 0 0 1 0 1 0
void suf_cmd( int argc, char *argv[] ){

	if (argc!=10) {
          cout<<"\nUsage: \n" << argv[0] << " <curveName> <useDT> <useMinSet> <areaWeight> <edgeWeight> <dihedralWeight> <useMinMaxDihedral> <saveObj> <useNormal>"<<endl;
          cout<<"\nExample: \n" << argv[0] << " monkey 1 1 0 0 1 0 1 0"<<endl;
		return;
	}

	char * testfile = argv[1];
	char * curvefile = new char[300];
	char * normalfile = new char[300];
	char * canTfile = new char[300];
	strcpy_s(curvefile,300,testfile); strcat_s(curvefile,300,".curve");
	strcpy_s(normalfile,300,testfile); strcat_s(normalfile,300,".normal");
	strcpy_s(canTfile,300,testfile); strcat_s(canTfile,300,".tri");

	bool useDT=true;
	const char* tagDT = argv[2];
	useDT=(strcmp(tagDT,"1")==0);

	bool filterWE=false;
	const char* tagFWE = argv[3];
	filterWE=(strcmp(tagFWE,"1")==0);

	float weightTri;	sscanf(argv[4],"%f",&weightTri);
	float weightEdge;	sscanf(argv[5],"%f",&weightEdge);
	float weightBiTri;	sscanf(argv[6],"%f",&weightBiTri);
	float weightTriBd;	sscanf(argv[7],"%f",&weightTriBd);

	bool saveObj=false;
	const char* tagObj = argv[8];
	saveObj=(strcmp(tagObj,"1")==0);

	bool useNormal=false;
	const char* tagNormal = argv[9];
	useNormal=(strcmp(tagNormal,"1")==0);

	DMWT * myDMWT;
	if (useNormal){
		myDMWT = new DMWT(curvefile, normalfile, useDT, 0, 1, filterWE, saveObj);
	} else {
		myDMWT = new DMWT(curvefile, useDT,  0, 1, filterWE, saveObj);
	}
	myDMWT->setWeights(weightTri, weightEdge, weightBiTri, weightTriBd);

	// ---------build lists--------
	clock_t start = clock(),end;
	myDMWT->buildList();
	end = clock();
	float timeList = (float)(end-start)/CLOCKS_PER_SEC; 

	// ---------tile--------
	start = clock();
	myDMWT->tile();
	end = clock();
	float timeTile = (float)(end-start)/CLOCKS_PER_SEC;

	// ---------statistics--------
	cout<<"============================="<<endl;
	cout<<"Curve Name: "<<testfile<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"<N> numCurves: "<<myDMWT->numofcurves<<endl;
	cout<<"<N> numPts: "<<myDMWT->orgnumofvertices<<endl;
	cout<<"<T> time: "<<timeList+timeTile<<" (secs)\n";
	cout<<"----------------------------"<<endl;
	cout<<"cost: "<<myDMWT->optCost<<endl;
	cout<<"numSub: "<<myDMWT->numSub<<endl;
	cout<<"============================="<<endl;
}

// for edge protection cmd line
// usage: TMP.exe -ep <curveName> <useNormal>
// example: TMP.exe monkey 0
void ep_cmd( int argc, char *argv[] ) {

	if (argc!=4) {
          cout<<"\nUsage: \n" << argv[0] << " <curveName> <useNormal>"<<endl;
          cout<<"\nExample: \n" << argv[0] << " monkey 0 "<<endl;
		return;
	}

	char * testfile = argv[2];
	char * curvefile = new char[300];
	char * normalfile = new char[300];
	strcpy_s(curvefile,300,testfile); strcat_s(curvefile,300,".curve");
	strcpy_s(normalfile,300,testfile); strcat_s(normalfile,300,".normal");

	bool useDT=true;
	bool filterWE=false;
	bool saveObj=false;
	bool useNormal=false;
	const char* tagNormal = argv[3];
	useNormal=(strcmp(tagNormal,"1")==0);

	float weightTri = 1.0;
	float weightEdge = 0.0;
	float weightBiTri = 0.0;
	float weightTriBd = 0.0;

	DMWT * myDMWT;
	if (useNormal){
		myDMWT = new DMWT(curvefile, normalfile, useDT, 0, 1, filterWE, saveObj);
	} else {
		myDMWT = new DMWT(curvefile, useDT,  0, 1, filterWE, saveObj);
	}
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main( int argc, char *argv[] ){

	timeNew = 0.0;
	tileNum = 0;

	if (cmdOptionExists(argv, argv+argc, "-ep")) {
		cout << "Start edge protection..."<<endl;
		ep_cmd(argc, argv);
	} else {
		suf_cmd(argc, argv);
	}

}
