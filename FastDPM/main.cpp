#include "stdafx.h"
#include "FastDPM.h"
#include <conio.h>
#include "Windows.h"

vector<string>  yuStdDirFiles( string DirName, vector<string> FileExtensions );
string trim_file_name( string FileName, int FLAG );

int	main()
{
	/* I. Get images */
	string	img_dir = "D:\\people\\";
	//string	img_dir = "D:\\FastDPM\\FastDPM\\";
	string extensions[] = { ".jpg" };
	vector<string>	img_extensions( extensions, extensions+1 );
	vector<string>	imgnames = yuStdDirFiles(img_dir, img_extensions);
	//imgnames.clear();
	//imgnames.push_back("1.jpg");

	/* II. Perform Part_Model based detection */

	//FastDPM	PM( "model_inria_14_2_features.txt" );
	 FastDPM	PM("person_final.txt");
	//FastDPM	PM("car_final_2010.txt");
	

	//FastDPM	PM("car_final_2010.txt");

	bool	flag = false;
	for( unsigned i=0; i<imgnames.size(); i++ ){
		string	img_name = imgnames[i];
		Mat	img_uint8 = imread( img_name.c_str() );	
		//Mat	img_uint8 = imread("1.jpg");
		if( img_uint8.empty() ){
			cout<<"Cannot get image "<<img_name<<endl;
			getchar();
			return -2;
		}
		cout<<"Processing "<<trim_file_name(img_name,0)<<endl;
		Mat	img = PM.prepareImg( img_uint8 );
		PM.detect( img, -0.0f, true, true );	
		cout<<"------------------------------------------------------------"<<endl;
		if( PM.detections.empty() )
			continue;
		flag = true;
		Sleep(1);
		char key = waitKey(1);
		if( key==27 )
			break;
	}
	cout<<"Finished!"<<endl;
	if( flag )
		waitKey();
	else
		_getch();

	return	0;
}