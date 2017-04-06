
#include<iostream>
#include<sstream>
#include<Windows.h>
#include<NuiApi.h>
#include<time.h>
#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <winbase.h>
#include <stdio.h>
#include <process.h>
#include <iostream>  // for debug writing
#include <string>    // useful for reading and writing
#include <fstream>   // ifstream, ofstream
#pragma comment(linker, "/nodefaultlib:\"libc.lib\"")
//#pragma comment(linker, "/entry:\"WinMain\"")
//#pragma comment(linker, "/opt:nowin98")
#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")






#define ERROR_CHECK( ret )  \
  if ( ret != S_OK ) {    \
  std::stringstream ss;	\
  ss << "failed " #ret " " << std::hex << ret << std::endl;\
  throw std::runtime_error( ss.str().c_str() );\
  }

const NUI_IMAGE_RESOLUTION CAMERA_RESOLUTION = NUI_IMAGE_RESOLUTION_640x480;
		//ƒXƒPƒ‹ƒgƒ“‰æ‘œ‚ÌŠeŠÖß‚ÌÀ•W‚ðŠi”[‚·‚é‚½‚ß‚Ì•Ï”‚Q‚OŒÂ
	LONG colorX;
	LONG colorY;
	LONG colorX0;//‚¨Ki‰¡ˆÚ“®j
	LONG colorY0;//‚¨KicˆÚ“®j
	LONG colorX1;//Ò’Œi‰¡ˆÚ“®j
	LONG colorY1;//Ò’ŒicˆÚ“®j
	LONG colorX2;//Žñi‰¡ˆÚ“®j
	LONG colorY2;//ŽñicˆÚ“®j
	LONG colorX3;//“ªi‰¡ˆÚ“®j
	LONG colorY3;//“ªicˆÚ“®j
	LONG colorX4;//¶Œ¨i‰¡ˆÚ“®j
	LONG colorY4;//¶Œ¨icˆÚ“®j
	LONG colorX5;//¶•Ii‰¡ˆÚ“®j
	LONG colorY5;//¶•IicˆÚ“®j
	LONG colorX6;//¶ŽèŽñi‰¡ˆÚ“®j
	LONG colorY6;//¶ŽèŽñicˆÚ“®j
	LONG colorX7;//¶Žèi‰¡ˆÚ“®j
	LONG colorY7;//¶ŽèicˆÚ“®j
	LONG colorX8;//‰EŒ¨i‰¡ˆÚ“®j
	LONG colorY8;//‰EŒ¨icˆÚ“®j
	LONG colorX9;//‰E•Ii‰¡ˆÚ“®j
	LONG colorY9;//‰E•IicˆÚ“®j
	LONG colorX10;//‰EŽèŽñi‰¡ˆÚ“®j
	LONG colorY10;//‰EŽèŽñicˆÚ“®j
	LONG colorX11;//‰EŽèi‰¡ˆÚ“®j
	LONG colorY11;//‰EŽèicˆÚ“®j
	LONG colorX12;//¶‹r•t‚¯ªi‰¡ˆÚ“®j
	LONG colorY12;//¶‹r•t‚¯ªicˆÚ“®j
	LONG colorX13;//¶•Gi‰¡ˆÚ“®j
	LONG colorY13;//¶•GicˆÚ“®j
	LONG colorX14;//¶‘«Žñi‰¡ˆÚ“®j
	LONG colorY14;//¶‘«ŽñicˆÚ“®j
	LONG colorX15;//¶‚Â‚Üæi‰¡ˆÚ“®j
	LONG colorY15;//¶‚Â‚ÜæicˆÚ“®j
	LONG colorX16;//‰E‹r•t‚¯ªi‰¡ˆÚ“®j
	LONG colorY16;//‰E‹r•t‚¯ªicˆÚ“®j
	LONG colorX17;//‰E•Gi‰¡ˆÚ“®j
	LONG colorY17;//‰E•GicˆÚ“®j
	LONG colorX18;//‰E‘«Žñi‰¡ˆÚ“®j
	LONG colorY18;//‰E‘«ŽñicˆÚ“®j
	LONG colorX19;//‰E‚Â‚Üæi‰¡ˆÚ“®j
	LONG colorY19;//‰E‚Â‚ÜæicˆÚ“®j
	LONG colorX20;
	LONG colorY20;
	int skeletontracked;
	double tokuten;
	int kataashi;
	int kataashikensyutu;
	int squatcounterkaisuua;
	int hipcentersyokitix=colorX0;
	int hipcentersyokitiy;
	int kneeleftsyokitix;
	int kneeleftsyokitiy;
	int kneerightsyokitix;
	int kneerightsyokitiy;
	int squatdown;
	int squatup;
	int end;
	
	int squatcounterkaisuub;
	int squatstopper;
	int tokuten2;
	int squatonseistopper;
	int pastSec;
	int pastSec2;
	time_t timer;//Œ»ÝŽžŽæ“¾—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
	time_t last = time(0);//ƒ^ƒCƒ}[—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
	time_t next;


 class KinectSample
{

 

	
private:


  INuiSensor* kinect;
  HANDLE imageStreamHandle;
  HANDLE depthStreamHandle;
  HANDLE streamEvent;

  DWORD width;
  DWORD height;

public:

  KinectSample()

  {
  }

  ~KinectSample()
  {
    // I—¹ˆ—
    if ( kinect != 0 ) {
      kinect->NuiShutdown();
      kinect->Release();
    }
  }

  void initialize()
  {
    createInstance();

    // Kinect‚ÌÝ’è‚ð‰Šú‰»‚·‚é
    ERROR_CHECK( kinect->NuiInitialize( NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON ) );

    // RGBƒJƒƒ‰‚ð‰Šú‰»‚·‚é
    ERROR_CHECK( kinect->NuiImageStreamOpen( NUI_IMAGE_TYPE_COLOR, CAMERA_RESOLUTION,
      0, 2, 0, &imageStreamHandle ) );

    // ‹——£ƒJƒƒ‰‚ð‰Šú‰»‚·‚é
    ERROR_CHECK( kinect->NuiImageStreamOpen( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, CAMERA_RESOLUTION,
      0, 2, 0, &depthStreamHandle ) );

    // Nearƒ‚[ƒh
   // ERROR_CHECK( kinect->NuiImageStreamSetImageFrameFlags(
     //depthStreamHandle, NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE ) );

    // ƒXƒPƒ‹ƒgƒ“‚ð‰Šú‰»‚·‚é
    ERROR_CHECK( kinect->NuiSkeletonTrackingEnable( 0,NUI_SKELETON_TRACKING_FLAG_TITLE_SETS_TRACKED_SKELETONS ) );//‚à‚µƒXƒPƒ‹ƒgƒ“‚ªŽæ“¾‚Å‚«‚È‚¯‚ê‚ÎÅŒã‚ÌNUI--‚ð0‚É‚·‚éB

    // ƒtƒŒ[ƒ€XVƒCƒxƒ“ƒg‚Ìƒnƒ“ƒhƒ‹‚ðì¬‚·‚é
    streamEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
    ERROR_CHECK( kinect->NuiSetFrameEndEvent( streamEvent, 0 ) );

    // Žw’è‚µ‚½‰ð‘œ“x‚ÌA‰æ–ÊƒTƒCƒY‚ðŽæ“¾‚·‚é
    ::NuiImageResolutionToSize(CAMERA_RESOLUTION, width, height );
  }

  void run()
  {
    cv::Mat image;

    // ƒƒCƒ“ƒ‹[ƒv
    while ( 1 ) {
      // ƒf[ƒ^‚ÌXV‚ð‘Ò‚Â
      DWORD ret = ::WaitForSingleObject( streamEvent, INFINITE );
      ::ResetEvent( streamEvent );

      drawRgbImage( image );
      drawDepthImage( image );
      drawSkeleton( image );

      // ‰æ‘œ‚ð•\Ž¦‚·‚é
     cv::imshow("Tocco Kinect Screen : ‘ˆî“c‘åŠwlŠÔ‰ÈŠwŠwp‰@@‰Â•”Œ¤‹†Žº",image);

      // I—¹‚Ì‚½‚ß‚ÌƒL[“ü—Íƒ`ƒFƒbƒNŒ“A•\Ž¦‚Ì‚½‚ß‚ÌƒEƒFƒCƒg
      int key = cv::waitKey( 1 );
      if ( key == 'q' ) {
        break;
      }
	  //Kinect–{‘Ì‚ÌŒü‚«’²®
			//ãƒL[
			else if ((key>>16) == VK_UP){
				LONG angle = 0;
				kinect->NuiCameraElevationGetAngle(&angle);
				angle = std::min(angle + 5,(LONG)NUI_CAMERA_ELEVATION_MAXIMUM);
				kinect->NuiCameraElevationSetAngle(angle);
			}
			else if((key>>16) == VK_DOWN){
				LONG angle = 0;
				kinect->NuiCameraElevationGetAngle(&angle);
				angle = std::max(angle - 5,(LONG)NUI_CAMERA_ELEVATION_MINIMUM );
				kinect->NuiCameraElevationSetAngle(angle);
			}
    }
  }

private:

  void createInstance()
  {
    // Ú‘±‚³‚ê‚Ä‚¢‚éKinect‚Ì”‚ðŽæ“¾‚·‚é
    int count = 0;
    ERROR_CHECK( ::NuiGetSensorCount( &count ) );
    if ( count == 0 ) {
      throw std::runtime_error( "Kinect ‚ðÚ‘±‚µ‚Ä‚­‚¾‚³‚¢" );
    }

    // Å‰‚ÌKinect‚ÌƒCƒ“ƒXƒ^ƒ“ƒX‚ðì¬‚·‚é
    ERROR_CHECK( ::NuiCreateSensorByIndex( 0, &kinect ) );

    // Kinect‚Ìó‘Ô‚ðŽæ“¾‚·‚é
    HRESULT status = kinect->NuiStatus();
    if ( status != S_OK ) {
      throw std::runtime_error( "Kinect ‚ª—˜—p‰Â”\‚Å‚Í‚ ‚è‚Ü‚¹‚ñ" );
    }
  }

  void drawRgbImage( cv::Mat& image )
  {
    // RGBƒJƒƒ‰‚ÌƒtƒŒ[ƒ€ƒf[ƒ^‚ðŽæ“¾‚·‚é
    NUI_IMAGE_FRAME imageFrame = { 0 };
    ERROR_CHECK( kinect->NuiImageStreamGetNextFrame( imageStreamHandle, INFINITE, &imageFrame ) );

    // ‰æ‘œƒf[ƒ^‚ðŽæ“¾‚·‚é
    NUI_LOCKED_RECT colorData;
    imageFrame.pFrameTexture->LockRect( 0, &colorData, 0, 0 );

    // ‰æ‘œƒf[ƒ^‚ðƒRƒs[‚·‚é
    image = cv::Mat( height, width, CV_8UC4, colorData.pBits );

    // ƒtƒŒ[ƒ€ƒf[ƒ^‚ð‰ð•ú‚·‚é
    ERROR_CHECK( kinect->NuiImageStreamReleaseFrame( imageStreamHandle, &imageFrame ) );
  }

  void drawDepthImage( cv::Mat& image )
  {
    // ‹——£ƒJƒƒ‰‚ÌƒtƒŒ[ƒ€ƒf[ƒ^‚ðŽæ“¾‚·‚é
    NUI_IMAGE_FRAME depthFrame = { 0 };
    ERROR_CHECK( kinect->NuiImageStreamGetNextFrame( depthStreamHandle, 0, &depthFrame ) );

    // ‹——£ƒf[ƒ^‚ðŽæ“¾‚·‚é
    NUI_LOCKED_RECT depthData = { 0 };
    depthFrame.pFrameTexture->LockRect( 0, &depthData, 0, 0 );
	if ( depthData.Pitch == 0 ) {
		std::cout << "zero" << std::endl;
	}

    USHORT* depth = (USHORT*)depthData.pBits;
    for ( int i = 0; i < (depthData.size / sizeof(USHORT)); ++i ) {
      USHORT distance = ::NuiDepthPixelToDepth( depth[i] );
      USHORT player = ::NuiDepthPixelToPlayerIndex( depth[i] );

      LONG depthX = i % width;
      LONG depthY = i / width;
      LONG colorX = depthX;
      LONG colorY = depthY;

      // ‹——£ƒJƒƒ‰‚ÌÀ•W‚ðARGBƒJƒƒ‰‚ÌÀ•W‚É•ÏŠ·‚·‚é
      kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(
        CAMERA_RESOLUTION, CAMERA_RESOLUTION,
        0, depthX , depthY, 0, &colorX, &colorY );

	  //•ÏŠ·‚³‚ê‚½À•W‚ð—˜—p‚µ‚ÄA•\Ž¦‰æ‘œ‚ÌƒsƒNƒZƒ‹ƒf[ƒ^‚ð•\Ž¦‚·‚é
			int index = ((colorY*width)+colorX)*4;
			UCHAR* data = &image.data[index];

	  

      // ƒvƒŒƒCƒ„[
     // if ( player != 0 ) {
       // int index = ((colorY * width) + colorX) * 4;
       // UCHAR* data = &image.data[index];
        //data[0] = 0;
        //data[1] = 0;
        //data[2] = 255;
      //}
     // else {
        // ˆê’èˆÈã‚Ì‹——£‚ð•`‰æ‚µ‚È‚¢
       //if ( distance >= 1000 ) {
         //int index = ((colorY * width) + colorX) * 4;
          //UCHAR* data = &image.data[index];
         //data[0] = 255;
         //data[1] = 255;
         //data[2] = 255;//
       //}
	//}
	}

    // ƒtƒŒ[ƒ€ƒf[ƒ^‚ð‰ð•ú‚·‚é
    ERROR_CHECK( kinect->NuiImageStreamReleaseFrame( depthStreamHandle, &depthFrame ) );
  }

  void drawSkeleton( cv::Mat& image )
  {
    // ƒXƒPƒ‹ƒgƒ“‚ÌƒtƒŒ[ƒ€‚ðŽæ“¾‚·‚é
    NUI_SKELETON_FRAME skeletonFrame = { 0 };
    kinect->NuiSkeletonGetNextFrame( 0, &skeletonFrame );
	selectActiveSkeleton(skeletonFrame);

	
	
   //ERROR_CHECK( kinect->NuiSkeletonGetNextFrame( 0, &skeletonFrame ) );//
    for ( int i = 0; i < NUI_SKELETON_COUNT; ++i ) {

      NUI_SKELETON_DATA& skeletonData = skeletonFrame.SkeletonData[i];
      if ( skeletonData.eTrackingState == NUI_SKELETON_TRACKED ) {
		
        for ( int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j ) {

			
	
          if ( skeletonData.eSkeletonPositionTrackingState[j] != NUI_SKELETON_POSITION_NOT_TRACKED ) {
          // drawJoint( image, skeletonData.SkeletonPositions[j] );
			    skeletontracked=1;
			  drawJoint0(image,skeletonData.SkeletonPositions[0]);
						drawJoint1(image,skeletonData.SkeletonPositions[1]);
						drawJoint2(image,skeletonData.SkeletonPositions[2]);
						drawJoint3(image,skeletonData.SkeletonPositions[3]);
						drawJoint4(image,skeletonData.SkeletonPositions[4]);
						drawJoint5(image,skeletonData.SkeletonPositions[5]);
						drawJoint6(image,skeletonData.SkeletonPositions[6]);
						drawJoint7(image,skeletonData.SkeletonPositions[7]);
						drawJoint8(image,skeletonData.SkeletonPositions[8]);
						drawJoint9(image,skeletonData.SkeletonPositions[9]);
						drawJoint10(image,skeletonData.SkeletonPositions[10]);
						drawJoint11(image,skeletonData.SkeletonPositions[11]);
						drawJoint12(image,skeletonData.SkeletonPositions[12]);
						drawJoint13(image,skeletonData.SkeletonPositions[13]);
						drawJoint14(image,skeletonData.SkeletonPositions[14]);
						drawJoint15(image,skeletonData.SkeletonPositions[15]);
						drawJoint16(image,skeletonData.SkeletonPositions[16]);
						drawJoint17(image,skeletonData.SkeletonPositions[17]);
						drawJoint18(image,skeletonData.SkeletonPositions[18]);
						drawJoint19(image,skeletonData.SkeletonPositions[19]);
						drawJoint20(image,skeletonData.SkeletonPositions[20]);
						//ŽÀÛ‚ÉƒEƒBƒ“ƒhƒEã‚ÉŠeŠÖß‚ð‚Â‚È‚¬‡‚í‚¹‚éƒXƒPƒ‹ƒgƒ“‰æ‘œ‚Ì•`‰æ
						cv::line(image,cv::Point(colorX15,colorY15),cv::Point(colorX14,colorY14),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX14,colorY14),cv::Point(colorX13,colorY13),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX13,colorY13),cv::Point(colorX12,colorY12),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX12,colorY12),cv::Point(colorX0,colorY0),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX19,colorY19),cv::Point(colorX18,colorY18),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX18,colorY18),cv::Point(colorX17,colorY17),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX17,colorY17),cv::Point(colorX16,colorY16),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX16,colorY16),cv::Point(colorX0,colorY0),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX0,colorY0),cv::Point(colorX1,colorY1),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX1,colorY1),cv::Point(colorX2,colorY2),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX2,colorY2),cv::Point(colorX3,colorY3),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX7,colorY7),cv::Point(colorX6,colorY6),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX6,colorY6),cv::Point(colorX5,colorY5),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX5,colorY5),cv::Point(colorX4,colorY4),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX4,colorY4),cv::Point(colorX2,colorY2),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX11,colorY11),cv::Point(colorX10,colorY10),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX10,colorY10),cv::Point(colorX9,colorY9),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX9,colorY9),cv::Point(colorX8,colorY8),cv::Scalar(0,255,0),3);
						cv::line(image,cv::Point(colorX8,colorY8),cv::Point(colorX2,colorY2),cv::Scalar(0,255,0),3);
						 //ŽÀÛ‚ÉƒEƒBƒ“ƒhƒEã‚ÉŠeŠÖß‚ð‚Â‚È‚¬‡‚í‚¹‚éƒXƒPƒ‹ƒgƒ“‰æ‘œ‚Ì•`‰æ
						if(kataashi==1&&kataashikensyutu==1){
							cv::rectangle(image, cv::Point(colorX12,colorY12), cv::Point(colorX15, colorY15), cv::Scalar(0,255,0), 3, 4);
							}//‘«‚ªã‚ª‚Á‚Ä‚¢‚é‚Æ—Î˜g‚ª•\Ž¦‚³‚ê‚éB
						if(kataashi==1&&kataashikensyutu==2){
							cv::rectangle(image, cv::Point(colorX12,colorY12), cv::Point(colorX15, colorY15), cv::Scalar(0,0,200), 3, 4);
							}//‘«‚ª‰º‚ª‚Á‚Ä‚¢‚é‚ÆÔ˜g‚É‚È‚éB
						if(kataashi==1&&kataashikensyutu==5){
							cv::rectangle(image, cv::Point(colorX12,colorY12), cv::Point(colorX15, colorY15), cv::Scalar(200,0,0), 3, 4);
							}//‘«‚ª‰º‚ª‚Á‚Ä‚¢‚é‚ÆÔ˜g‚É‚È‚éB

						if(kataashi==1&&kataashikensyutu==3){
							cv::rectangle(image, cv::Point(colorX16,colorY16), cv::Point(colorX19, colorY19), cv::Scalar(0,255,0), 3, 4);	
							}//‘«ã‚ª‚èŽž‰E‘«‹éŒ`•\Ž¦
						if(kataashi==1&&kataashikensyutu==4){
							cv::rectangle(image, cv::Point(colorX16,colorY16), cv::Point(colorX19, colorY19), cv::Scalar(0,0,200), 3, 4);
							}//‘«‚ª‰º‚ª‚Á‚Ä‚¢‚é‚ÆÔ˜g‚É‚È‚éB
						if(kataashi==1&&kataashikensyutu==6){
							cv::rectangle(image, cv::Point(colorX16,colorY16), cv::Point(colorX19, colorY19), cv::Scalar(200,0,0), 3, 4);
							}//‘«‚ª‰º‚ª‚Á‚Ä‚¢‚é‚ÆÔ˜g‚É‚È‚éB
		  }
        }
		
      }
      else if ( skeletonData.eTrackingState == NUI_SKELETON_POSITION_ONLY ) {
		  skeletontracked=0;
        drawJoint( image, skeletonData.Position );
      }
	}
 
						
  }

  

 
	void drawJoint(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX = 0,depthY = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX,&depthY,CAMERA_RESOLUTION);
		colorX=0;
		colorY=0;

		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX,(LONG)depthY,0,&colorX,&colorY);
		cv::circle(image,cv::Point(colorX,colorY),10,cv::Scalar(0,255,0),-1);
	}
	void drawJoint0(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX0 = 0,depthY0 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX0,&depthY0,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX0,(LONG)depthY0,0,&colorX0,&colorY0);
		cv::circle(image,cv::Point(colorX0,colorY0),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint1(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX1 = 0,depthY1 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX1,&depthY1,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX1,(LONG)depthY1,0,&colorX1,&colorY1);
		cv::circle(image,cv::Point(colorX1,colorY1),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint2(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX2 = 0,depthY2 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX2,&depthY2,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX2,(LONG)depthY2,0,&colorX2,&colorY2);
		cv::circle(image,cv::Point(colorX2,colorY2),5,cv::Scalar(0,255,0),-1);
		
	}
	
	void drawJoint3(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX3 = 0,depthY3 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX3,&depthY3,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX3,(LONG)depthY3,0,&colorX3,&colorY3);
		cv::circle(image,cv::Point(colorX3,colorY3),5,cv::Scalar(0,255,0),-1);
		
	}

	void drawJoint4(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX4 = 0,depthY4 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX4,&depthY4,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX4,(LONG)depthY4,0,&colorX4,&colorY4);
		cv::circle(image,cv::Point(colorX4,colorY4),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint5(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX5 = 0,depthY5 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX5,&depthY5,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX5,(LONG)depthY5,0,&colorX5,&colorY5);
		cv::circle(image,cv::Point(colorX5,colorY5),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint6(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX6 = 0,depthY6 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX6,&depthY6,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX6,(LONG)depthY6,0,&colorX6,&colorY6);
		cv::circle(image,cv::Point(colorX6,colorY6),5,cv::Scalar(0,255,0),-1);
	
	}
	void drawJoint7(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX7 = 0,depthY7 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX7,&depthY7,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX7,(LONG)depthY7,0,&colorX7,&colorY7);
		cv::circle(image,cv::Point(colorX7,colorY7),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint8(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX8 = 0,depthY8 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX8,&depthY8,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX8,(LONG)depthY8,0,&colorX8,&colorY8);
		cv::circle(image,cv::Point(colorX8,colorY8),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint9(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX9 = 0,depthY9 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX9,&depthY9,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX9,(LONG)depthY9,0,&colorX9,&colorY9);
		cv::circle(image,cv::Point(colorX9,colorY9),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint10(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX10 = 0,depthY10 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX10,&depthY10,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX10,(LONG)depthY10,0,&colorX10,&colorY10);
		cv::circle(image,cv::Point(colorX10,colorY10),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint11(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX11 = 0,depthY11 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX11,&depthY11,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX11,(LONG)depthY11,0,&colorX11,&colorY11);
		cv::circle(image,cv::Point(colorX11,colorY11),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint12(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX12 = 0,depthY12 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX12,&depthY12,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX12,(LONG)depthY12,0,&colorX12,&colorY12);
		cv::circle(image,cv::Point(colorX12,colorY12),5,cv::Scalar(0,255,0),-1);
		
	}
	
	void drawJoint13(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX13 = 0,depthY13 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX13,&depthY13,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX13,(LONG)depthY13,0,&colorX13,&colorY13);
		cv::circle(image,cv::Point(colorX13,colorY13),5,cv::Scalar(0,255,0),-1);
		
	}

	void drawJoint14(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX14 = 0,depthY14 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX14,&depthY14,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX14,(LONG)depthY14,0,&colorX14,&colorY14);
		cv::circle(image,cv::Point(colorX14,colorY14),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint15(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX15 = 0,depthY15 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX15,&depthY15,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX15,(LONG)depthY15,0,&colorX15,&colorY15);
		cv::circle(image,cv::Point(colorX15,colorY15),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint16(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX16 = 0,depthY16 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX16,&depthY16,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX16,(LONG)depthY16,0,&colorX16,&colorY16);
		cv::circle(image,cv::Point(colorX16,colorY16),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint17(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX17 = 0,depthY17 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX17,&depthY17,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX17,(LONG)depthY17,0,&colorX17,&colorY17);
		cv::circle(image,cv::Point(colorX17,colorY17),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint18(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX18 = 0,depthY18 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX18,&depthY18,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX18,(LONG)depthY18,0,&colorX18,&colorY18);
		cv::circle(image,cv::Point(colorX18,colorY18),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint19(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX19 = 0,depthY19 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX19,&depthY19,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX19,(LONG)depthY19,0,&colorX19,&colorY19);
		cv::circle(image,cv::Point(colorX19,colorY19),5,cv::Scalar(0,255,0),-1);
		
	}
	void drawJoint20(cv::Mat& image,Vector4 position)
	{
		FLOAT depthX20 = 0,depthY20 = 0;
		::NuiTransformSkeletonToDepthImage(position,&depthX20,&depthY20,CAMERA_RESOLUTION);
		kinect->NuiImageGetColorPixelCoordinatesFromDepthPixelAtResolution(CAMERA_RESOLUTION,CAMERA_RESOLUTION,0,(LONG)depthX20,(LONG)depthY20,0,&colorX20,&colorY20);
		cv::circle(image,cv::Point(colorX20,colorY20),5,cv::Scalar(0,255,0),-1);
		
	}
	DWORD activeTrackId;
	void selectActiveSkeleton(NUI_SKELETON_FRAME& skeletonFrame){
		const int center = width/2;
		FLOAT minpos = 0;
		DWORD trackedId = 0;

		//1”Ô’†S‚É‹ß‚¢ƒvƒŒƒCƒ„[‚ð’T‚·
		for(int i = 0; i < NUI_SKELETON_COUNT;++i){
			NUI_SKELETON_DATA& skeletonData = skeletonFrame.SkeletonData[i];
			if(skeletonData.eTrackingState != NUI_SKELETON_NOT_TRACKED){
				FLOAT depthX=0,depthY=0;
				::NuiTransformSkeletonToDepthImage(skeletonData.Position,&depthX,&depthY,CAMERA_RESOLUTION);
				if(abs(minpos-center)>abs(depthX-center)){
					minpos=depthX;
					trackedId=skeletonData.dwTrackingID;
				}
			}
		}
		if((trackedId!=0)||(trackedId != activeTrackId)){
			DWORD trackedIds[]={trackedId,0};
			kinect->NuiSkeletonSetTrackedSkeletons(trackedIds);
			activeTrackId=trackedId;
		}
	}
};
	


///////////////////////////////////////////////////‚±‚±‚©‚ç‚ª•Àsˆ—•”•ª,Šî–{“I‚É‚Í‚±‚±‚©‚ç‰º‚ð‚¢‚¶‚é///////////////////////////////////////////////////

 unsigned int __stdcall tocco(void *dmy)//•Ð‘«—§‚¿,ƒXƒNƒƒbƒg•À—ñˆ—‹Lq•”
{
	int i;
	skeletontracked=0;
	for(i=0;i=10;i--){         //for•¶‚Åcsvƒtƒ@ƒCƒ‹‚Ì‘‚«ž‚Ý‚ðŠÄŽ‹(csvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—)
		Sleep(50);//ˆ—ŒyŒ¸—p
		printf("%f\n",colorY17);
		//ŽžŠÔŒv‘ª
			if (time(&next) != last){//í‚ÉŽžŠÔ‚ÌŒo‰ß‚ðŠÄŽ‹‚µ‚Ä‚¢‚Ä‚P•bˆÈã‚¸‚ê‚½‚çpastSec‚ð‚P‘‚â‚µnext‚Ælast‚Ì”’l‚ð“¯‚¶‚É‚·‚é
				last = next;
				pastSec2++;
				}
			printf("%d\n",pastSec2);
			if(pastSec2==181){
				pastSec2=0;
				}
	std::ifstream ifs( "start.csv" );
	std::string str1;
	ifs >> str1;
	std::ofstream ofs("tokuten.csv");
	ofs << "0"<< std::endl;//“¾“_‚ð‰Šú‰»
	

			
///////////////////////////////////////‚±‚±‚©‚ç‚ª•Ð‘«—§‚¿¶‘«////////////////////////////////////////////////////////////////////////////////////////////

	if(str1=="1"||pastSec2==60||colorY5<=300&&colorY13<=500&&skeletontracked==1){//•Ð‘«—§‚¿ˆ—‹Lq•”//‚à‚µcsvƒtƒ@ƒCƒ‹‚É‚P‚ª‘‚«ž‚Ü‚ê‚Ä‚¢‚ÄƒXƒPƒ‹ƒgƒ“‚ªŒŸo‚³‚ê‚Ä‚¢‚½ê‡ƒXƒ^[ƒg‚³‚¹‚éB||colorY5<=80&&skeletontracked==1
	
		time_t timer;//Œ»ÝŽž•\Ž¦—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
		printf("‚©‚½‚ ‚µ‚¾‚¿‚Ð‚¾‚è[\n");
		sndPlaySound("leftstart.wav",SND_ASYNC);//‰¹º‚ðÄ¶‚·‚éA‚±‚ÌƒR[ƒh‚Å‚Í“¯ŽžÄ¶‚Í‚Å‚«‚È‚¢
		std::ofstream ofs("macro1.csv");
		ofs << "1" << std::endl;
		Sleep(4000);//‰¹º‚ÆBGM‚ª”í‚ç‚È‚¢‚æ‚¤‚É’x‰„‚ð‚³‚¹‚Ä‚¢‚é
		static MCI_OPEN_PARMS mop;//BGMÄ¶‚ð‚·‚é‚±‚Ì•”•ª‚Å“¯ŽžÄ¶‚ð‚µ‚Ä‚¢‚éB
		mop.lpstrDeviceType="WaveAudio";//ƒtƒ@ƒCƒ‹‚ÌŽí—Þ‚ðÝ’è
		mop.lpstrElementName="newdays.wav";//ƒtƒ@ƒCƒ‹‚ðÝ’è
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mop);
		mciSendCommand(mop.wDeviceID,MCI_PLAY,0,0);//Ý’è‚µ‚½ƒtƒ@ƒCƒ‹‚ðÄ¶‚·‚é
		std::string filename = "start.csv";
		std::ofstream writing_file;//ƒ}ƒNƒ‚É‰½“x‚à‚P‚ª“ü‚ç‚È‚¢‚æ‚¤‚Éstart.csv‚ð‰Šú‰»‚·‚éB
		writing_file.open(filename, std::ios::out);
		Sleep(3000);//”FŽ¯‚ªˆÀ’è‚·‚é‚Ü‚Å‚Ì‘Ò‚¿ŽžŠÔ
		time_t last = time(0);//ƒ^ƒCƒ}[—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
		time_t next;//ƒ^ƒCƒ}[—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
		time_t SEC;
	
   
		for(int j = 0; j < 20; j--) {
			kataashi=1;//‹éŒ`‚ð•\Ž¦‚³‚¹‚é‚½‚ß‚ÌƒgƒŠƒK[
			Sleep(40);//‚±‚±‚Åˆê„‚ÌƒTƒCƒNƒ‹‚ðŒˆ‚ß‚é(‚±‚±‚Æ”»’èˆ—•”‚Å“¾“_‚Ì’²®‚ð‚µ‚Ä‚¢‚é‚Ì‚Å‚¢‚¶‚é‚Æ‚«‚Í”»’èˆ—•”‚ÆƒZƒbƒg‚Ål‚¦‚é)
			/* Œ»ÝŽž‚ÌŽæ“¾ */
			time(&timer);
			/* Œ»ÝŽž‚ð•¶Žš—ñ‚É•ÏŠ·‚µ‚Ä•\Ž¦ */
			printf("Œ»ÝŽž: %s\n", ctime(&timer));
			//ŽžŠÔŒv‘ª
			if (time(&next) != last){//í‚ÉŽžŠÔ‚ÌŒo‰ß‚ðŠÄŽ‹‚µ‚Ä‚¢‚Ä‚P•bˆÈã‚¸‚ê‚½‚çpastSec‚ð‚P‘‚â‚µnext‚Ælast‚Ì”’l‚ð“¯‚¶‚É‚·‚é
				last = next;
				pastSec++;
				}


			//‚±‚±‚©‚ç‰º‚ª•Ð‘«—§‚¿¶‘«‚Ì”»’èˆ—•”(‚±‚±‚ÌðŒ‚ÍŽÀŒ±‚ÌãÄ’²®‚ª•K—v)

			if(((colorX19-colorX15)!=0)&&((colorY19-colorY15)>2)&&((colorY17-colorY13)>=1)){//‚“¾“_ˆ—
				tokuten=tokuten+0.071;//1„‚²‚Æ‚É“_”‚ªˆê“_‰ÁŽZ‚³‚ê‚é
				tokuten2=tokuten;//‚±‚±‚ÅdoubleŒ^‚©‚çintŒ^‚É•ÏŠ·‚µ‚Ä‚¢‚é
				printf("%d\n",tokuten2);
				kataashikensyutu=5;//Â˜g‚ð•\Ž¦‚³‚¹‚é‚½‚ß‚ÌƒgƒŠƒK[
				}
    
			
			if(((colorX19-colorX15)!=0)&&((colorY19-colorY15)<0)&&((colorY17-colorY13)<0)){
				kataashikensyutu=2;//Ô˜g‚ð•\Ž¦‚³‚¹‚é‚½‚ß‚ÌƒgƒŠƒK[
				}
			std::ofstream ofs("tokuten.csv");
				ofs << tokuten2 << std::endl;
			//////////////////////////¶‘«part1///////////////////////////////////
			struct tm *ltm;
			time( &SEC );
			ltm = localtime( &SEC );

			printf("%d\n",ltm->tm_sec );
			if(ltm->tm_sec<=30&&pastSec==7){//7•b–Ú
				std::string filename = "macro1.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚éB
				writing_file.open(filename, std::ios::trunc);
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("iityousi.wav",SND_ASYNC);
				
				};
			if(ltm->tm_sec<=30&&pastSec==15){//15•b–Ú
			std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("nikonikoegao.wav",SND_ASYNC);
			};
				
			if(ltm->tm_sec<=30&&pastSec==22){//22•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "4" << std::endl;
				sndPlaySound("puronolocotorewomitayo1.wav",SND_ASYNC);
				};
		
			if(ltm->tm_sec<=30&&pastSec==30){//‚¿‚å‚¤‚Ç”¼•ª
				std::ofstream ofs("macro1.csv");
				ofs << "5" << std::endl;
				sndPlaySound("halfendhappy.wav",SND_ASYNC);
				};
			if(ltm->tm_sec<=30&&pastSec==37){//37•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "1" << std::endl;
				sndPlaySound("konomamaganbatte.wav",SND_ASYNC);
				};
			if(ltm->tm_sec<=30&&pastSec==45){//45•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("murisuna.wav",SND_ASYNC);
				};

			if(ltm->tm_sec<=30&&pastSec==53){//53•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("last.wav",SND_ASYNC);
				};

			/////////////////////////////¶‘«part2/////////////////////////////////////

			if(ltm->tm_sec>30&&pastSec==7){//7•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("goodcondition.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==15){//15•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("kiotuketene.wav",SND_ASYNC);
			};
				
			if(ltm->tm_sec>30&&pastSec==22){//22•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "4" << std::endl;
				sndPlaySound("iine1.wav",SND_ASYNC);
				};
		
			if(ltm->tm_sec>30&&pastSec==30){//‚¿‚å‚¤‚Ç”¼•ª
				std::ofstream ofs("macro1.csv");
				ofs << "5" << std::endl;
				sndPlaySound("nokori30.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==37){//37•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "1" << std::endl;
				sndPlaySound("iinesono.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==45){//45•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("wounderful.wav",SND_ASYNC);
				};

			if(ltm->tm_sec>30&&pastSec==53){//53•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("atochotto.wav",SND_ASYNC);
				};

			std::ifstream ifs( "start.csv" );//csv‚ÌŠÄŽ‹
			std::string str1;
			ifs >> str1;
			if(pastSec==60){ //I—¹ˆ—‹Lq•”(ˆ—‚ª1•ªŒo‚Â‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é
				int tokuten2=tokuten;//‚±‚±‚ÅdoubleŒ^‚©‚çintŒ^‚É•ÏŠ·‚µ‚Ä‚¢‚é
				printf("%d\n",tokuten2);
				pastSec=0;//ƒ^ƒCƒ}[‚ð‰Šú‰»
				skeletontracked=0;
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚éB
				writing_file.open(filename, std::ios::out);
				kataashi=0;//ˆ—‚ªI—¹‚µ‚½‚½‚ß‹éŒ`‚ð•\Ž¦‚³‚¹‚éƒgƒŠƒK[‚ð‰Šú‰»‚·‚éB
				tokuten=0;//“¾“_‚ð‰Šú‰»
				kataashikensyutu=0;//—Î˜g‚ðo‚·‚½‚ß‚ÌƒgƒŠƒK[‚ð‰Šú‰»
				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv‚³‚¹‚é
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðæ“ª‚ÉŠª‚«–ß‚·
				mciSendCommand(mop.wDeviceID,MCI_CLOSE,0,0);//mci‚ðƒNƒ[ƒY‚³‚¹‚é
				
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				
				if(tokuten2>=77){//“¾“_‚É‚æ‚Á‚Ä’‚é“à—e‚ª•Ï‚í‚é
					sndPlaySound("omedeto.wav",SND_ASYNC);
					Sleep(3000);
				}
				if(tokuten2<77&&tokuten>33){
					sndPlaySound("maamaa2.wav",SND_ASYNC);
					Sleep(6200);
				}
				if(tokuten2<=33){
					sndPlaySound("mouchoi.wav",SND_ASYNC);
					Sleep(3500);
				}
				std::ofstream ofs("tokuten.csv");
				ofs << "0" << std::endl;
				//sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);//‚¨”æ‚ê‚³‚Ü‚Å‚µ‚½
				//Sleep(2500);//‰¹º‚ª”í‚ç‚È‚¢‚æ‚¤‚É’x‰„
				sndPlaySound("housetenbosu.wav",SND_ASYNC);//ŽŸ‚Í”½‘Î‚Ì‘«‚à[[[
				std::cout << "ˆ—’âŽ~,‚¨”æ‚ê‚³‚Ü‚Å‚µ‚½ " << std::endl;
				break;//ƒ‹[ƒv‚©‚ç”²‚¯o‚·
				}

			if(str1=="0"||colorY5<=300&&colorY17<=600&&skeletontracked==1){ //‹Ù‹}I—¹ˆ—‹Lq•”(0‚ª“ü—Í‚³‚ê‚é‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é
				int tokuten2=tokuten;//‚±‚±‚ÅdoubleŒ^‚©‚çintŒ^‚É•ÏŠ·‚µ‚Ä‚¢‚é
				printf("%d\n",tokuten2);
				skeletontracked=0;
				pastSec=0;//ƒ^ƒCƒ}[‚ð‰Šú‰»
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚éB
				writing_file.open(filename, std::ios::out);
				kataashi=0;//ˆ—‚ªI—¹‚µ‚½‚½‚ß‹éŒ`‚ð•\Ž¦‚³‚¹‚éƒgƒŠƒK[‚ð‰Šú‰»‚·‚éB
				tokuten=0;//“¾“_‚ð‰Šú‰»
				kataashikensyutu=0;//•Ð‘«ŒŸo‚Ì‚½‚ß‚ÌƒgƒŠƒK[‚ð‰Šú‰»
				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv‚³‚¹‚é
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðæ“ª‚ÉŠª‚«–ß‚·
				mciSendCommand(mop.wDeviceID,MCI_CLOSE,0,0);//mci‚ðƒNƒ[ƒY‚³‚¹‚é
				sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);//‚¨”æ‚ê‚³‚Ü‚Å‚µ‚½
				std::ofstream ofs("tokuten.csv");
				ofs << "0" << std::endl;
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				std::cout << "‹Ù‹}’âŽ~ " << std::endl;
				break;//ƒ‹[ƒv‚©‚ç”²‚¯o‚·
				}
                
		}

    //////////////////////‚±‚±‚©‚ç‚ª•Ð‘«—§‚¿‰E‘«/////////////////////////////////////////////////////////////////////////////////////////////    
	
	}else if(str1=="2"||pastSec2==120||colorY9<=300&&colorY17<=500&&skeletontracked==1){
		printf("‚©‚½‚ ‚µ‚¾‚¿‚Ý‚¬[\n");
		sndPlaySound("rightstart.wav",SND_ASYNC);
		std::ofstream ofs("macro1.csv");
		ofs << "1" << std::endl;
		Sleep(4000);//BGM‚ÆƒZƒŠƒt‚ª”í‚ç‚È‚¢‚æ‚¤‚É’x‰„
		static MCI_OPEN_PARMS mop;//mci‚ðƒZƒbƒg
		mop.lpstrDeviceType="WaveAudio";//ƒtƒ@ƒCƒ‹‚ÌŽí—Þ‚ðÝ’è
		mop.lpstrElementName="newdays.wav";//ƒtƒ@ƒCƒ‹‚ðÝ’è
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mop);
		mciSendCommand(mop.wDeviceID,MCI_PLAY,0,0);//ƒtƒ@ƒCƒ‹‚ðÄ¶
		std::string filename = "start.csv";
		std::ofstream writing_file;//ƒ}ƒNƒ‚É‰½“x‚à‚P‚ª“ü‚ç‚È‚¢‚æ‚¤‚Éstart.csv‚ð‰Šú‰»‚·‚éB
		writing_file.open(filename, std::ios::out);
		Sleep(3000);//”FŽ¯‚ªˆÀ’è‚·‚é‚Ü‚Å‚Ì‘Ò‚¿ŽžŠÔ
		int j;
		time_t timer;//Œ»ÝŽžŽæ“¾—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
		time_t last = time(0);//ƒ^ƒCƒ}[—p‚Ì\‘¢‘Ì‚ðƒZƒbƒg
		time_t next;
		time_t SEC;
		
		for(j = 0; j < 20000000; j++) {
			kataashi=1;//‹éŒ`‚ð•\Ž¦‚³‚¹‚é‚½‚ß‚ÌƒgƒŠƒK[
			Sleep(40);//‚±‚±‚Å1„‚ÌƒTƒCƒNƒ‹‚ðŒˆ‚ß‚é
			/* Œ»ÝŽž‚ÌŽæ“¾ */
			time(&timer);
			/* Œ»ÝŽž‚ð•¶Žš—ñ‚É•ÏŠ·‚µ‚Ä•\Ž¦ */
			printf("Œ»ÝŽž: %s\n", ctime(&timer));
			//ŽžŠÔŒv‘ªiƒ^ƒCƒ}[ˆ—j
			if (time(&next) != last){
				last = next;
				pastSec++;
				}
			//‚±‚±‚©‚ç‰º‚ª•Ð‘«—§‚¿‰E‘«‚Ì”»’èˆ—•”
			if(((colorX15-colorX19)!=0)&&((colorY15-colorY19)>=2)&&((colorY13-colorY17)>=1)){//if•¶‚Í¶‘«‚Æ^‹t,‚“¾“_ˆ—
				tokuten=tokuten+0.071;//1„‚²‚Æ‚É“_”‚ªˆê“_‰ÁŽZ‚³‚ê‚é
				tokuten2=tokuten;//‚±‚±‚ÅdoubleŒ^‚©‚çintŒ^‚É•ÏŠ·‚µ‚Ä‚¢‚é
				printf("%d\n",tokuten2);
				kataashikensyutu=6;//—Î˜g‚ð•\Ž¦‚³‚¹‚é‚½‚ß‚ÌƒgƒŠƒK[
             

			if(((colorX15-colorX19)!=0)&&((colorY15-colorY19)<0)&&((colorY13-colorY17)<0)){
				kataashikensyutu=4;//Ô˜g‚ð•\Ž¦‚³‚¹‚é‚½‚ß‚ÌƒgƒŠƒK[
				}
			std::ofstream ofs("tokuten.csv");
				ofs << tokuten2 << std::endl;
				//////////////////////////‰E‘«part1///////////////////////////////////
			struct tm *ltm;
			time( &SEC );
			ltm = localtime( &SEC );

			printf("%d\n",ltm->tm_sec );
			if(ltm->tm_sec<=30&&pastSec==7){//7•b–Ú
				std::string filename = "macro1.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚éB
				writing_file.open(filename, std::ios::trunc);
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("iityousi.wav",SND_ASYNC);
				
				};
			if(ltm->tm_sec<=30&&pastSec==15){//15•b–Ú
			std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("nikonikoegao.wav",SND_ASYNC);
			};
				
			if(ltm->tm_sec<=30&&pastSec==22){//22•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "4" << std::endl;
				sndPlaySound("puronolocotorewomitayo.wav",SND_ASYNC);
				};
		
			if(ltm->tm_sec<=30&&pastSec==30){//‚¿‚å‚¤‚Ç”¼•ª
				std::ofstream ofs("macro1.csv");
				ofs << "5" << std::endl;
				sndPlaySound("halfendhappy.wav",SND_ASYNC);
				};
			if(ltm->tm_sec<=30&&pastSec==37){//37•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "1" << std::endl;
				sndPlaySound("konomamaganbatte.wav",SND_ASYNC);
				};
			if(ltm->tm_sec<=30&&pastSec==45){//45•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("murisuna.wav",SND_ASYNC);
				};

			if(ltm->tm_sec<=30&&pastSec==53){//53•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("last.wav",SND_ASYNC);
				};

			/////////////////////////////‰E‘«part2/////////////////////////////////////

			if(ltm->tm_sec>30&&pastSec==7){//7•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("goodcondition.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==15){//15•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("kiotuketene.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==22){//22•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "4" << std::endl;
				sndPlaySound("iine1.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==30){//30•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "5" << std::endl;
				sndPlaySound("foothalf.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==37){//37•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "1" << std::endl;
				sndPlaySound("iinesono.wav",SND_ASYNC);
				};
			if(ltm->tm_sec>30&&pastSec==45){//45•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "2" << std::endl;
				sndPlaySound("konotyouside.wav",SND_ASYNC);
				};
			
			if(ltm->tm_sec>30&&pastSec==53){//53•b–Ú
				std::ofstream ofs("macro1.csv");
				ofs << "3" << std::endl;
				sndPlaySound("atochotto.wav",SND_ASYNC);
				};
			std::ifstream ifs( "start.csv" );
			std::string str1;
			ifs >> str1;
			if(pastSec==60){       //I—¹ˆ—‹Lq•”(0‚ª“ü—Í‚³‚ê‚é‚©ˆ—‚ª1•ªŒo‚Â‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é
				int tokuten2=tokuten;//‚±‚±‚ÅdoubleŒ^(¬”“_‚ ‚è)‚¾‚Á‚½“¾“_‚ðintŒ^(®”)‚É•ÏŠ·‚µ‚Ä‚¢‚é
				printf("%d\n",tokuten2);
				skeletontracked=0;
				pastSec=0;
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚éB
				writing_file.open(filename, std::ios::out);
				kataashi=0;//ˆ—‚ªI—¹‚µ‚½‚½‚ß‹éŒ`‚ð•\Ž¦‚³‚¹‚éƒgƒŠƒK[‚ð‰Šú‰»‚·‚éB
				tokuten=0;
				kataashikensyutu=0;
				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðÅ‰‚ÉŠª‚«–ß‚·
				mciSendCommand(mop.wDeviceID,MCI_CLOSE,0,0);//mci‚ðƒNƒ[ƒY‚³‚¹‚é
				
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				if(tokuten2>=77){
					sndPlaySound("omedeto.wav",SND_ASYNC);
					Sleep(3000);
				}
				if(tokuten2<77&&tokuten>33){
					sndPlaySound("maamaa2.wav",SND_ASYNC);
					Sleep(6200);
				}
				if(tokuten2<=33){
					sndPlaySound("mouchoi.wav",SND_ASYNC);
					Sleep(3500);
				}
				std::ofstream ofs("tokuten.csv");
				ofs << "0" << std::endl;
				
				//sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);
				//Sleep(2500);//‰¹º‚ª”í‚ç‚È‚¢‚æ‚¤‚É’x‰„
				sndPlaySound("housetenbosu.wav",SND_ASYNC);
				std::cout << "ˆ—’âŽ~,‚¨”æ‚ê‚³‚Ü‚Å‚µ‚½ " << std::endl;
				break;
				}
			if(str1=="0"||colorY5<=300&&colorY17<=600&&skeletontracked==1){       //‹Ù‹}I—¹ˆ—‹Lq•”(0‚ª“ü—Í‚³‚ê‚é‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é
				int tokuten2=tokuten;//‚±‚±‚ÅdoubleŒ^(¬”“_‚ ‚è)‚¾‚Á‚½“¾“_‚ðintŒ^(®”)‚É•ÏŠ·‚µ‚Ä‚¢‚é
				printf("%d\n",tokuten2);
				skeletontracked=0;
				pastSec=0;
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚éB
				writing_file.open(filename, std::ios::out);
				kataashi=0;//ˆ—‚ªI—¹‚µ‚½‚½‚ß‹éŒ`‚ð•\Ž¦‚³‚¹‚éƒgƒŠƒK[‚ð‰Šú‰»‚·‚éB
				tokuten=0;
				kataashikensyutu=0;
				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðÅ‰‚ÉŠª‚«–ß‚·
				mciSendCommand(mop.wDeviceID,MCI_CLOSE,0,0);//mci‚ðƒNƒ[ƒY‚³‚¹‚é
				sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);
				std::ofstream ofs("tokuten.csv");
				ofs << "0" << std::endl;
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				std::cout << "‹Ù‹}’âŽ~ " << std::endl;
				break;
				}
			
                
   }

        




   /////////////////////////////////‚±‚±‚©‚ç‚ªƒXƒNƒƒbƒg///////////////////////////////////////////////////////////////////////////////////////////////


	}else if(str1=="3"||pastSec2==180||colorY9<=300&&colorY5<=300&&skeletontracked==1){//ƒXƒNƒƒbƒgˆ—‹Lq•”
		printf("‚·‚­‚í‚Á‚Æ[\n");
		sndPlaySound("squatstart.wav",SND_ASYNC);
		std::ofstream ofs1("macro1.csv");
		ofs1 << "3" << std::endl;
		Sleep(4000);//ˆ—‚ðˆÀ’è‚³‚¹‚é‚½‚ß‚Ì’x‰„
		std::string filename = "start.csv";
		std::ofstream writing_file;//ƒ}ƒNƒ‚É‰½“x‚à‚P‚ª“ü‚ç‚È‚¢‚æ‚¤‚Éstart.csv‚ð‰Šú‰»‚·‚éB
		writing_file.open(filename, std::ios::out);
		static MCI_OPEN_PARMS mop;
		mop.lpstrDeviceType="WaveAudio";
		mop.lpstrElementName="grand.wav";
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mop);
		mciSendCommand(mop.wDeviceID,MCI_PLAY,0,0);
		squatcounterkaisuub=0;//‰Šú‰»
		int k; 
		Sleep(3000);
		printf("‚Í‚¶‚ß[");
		squatonseistopper=0;

		for(k=0;k<10000;k++){
			//hipcentersyokitix=colorX0;//‚±‚ÌŽž“_‚Å‚Ì•Ï”ƒf[ƒ^‚ð•Û‘¶‚µ‚Ä‚¨‚­
			hipcentersyokitiy=colorY0;
			kneeleftsyokitix=colorX17;
			kneeleftsyokitiy=colorY17;
			kneerightsyokitix=colorX13;
			kneerightsyokitiy=colorY13;
			printf("‚·‚­‚í‚Á‚Æ\n");
			printf("%d\n",k);
			Sleep(300);//sleep‚ð‚©‚¯‚é‚±‚Æ‚É‚æ‚Á‚Ä”»’è‚µ‚â‚·‚­‚·‚é
//˜‚ð‰º‚°‚½Û‚Ìˆ—
			if((colorY0-hipcentersyokitiy)>=8)//&&(((colorX17-colorX13)-(kneeleftsyokitix-kneerightsyokitix))>=1))
			{
				squatdown=1;
				}
//˜‚ðã‚°‚½Û‚Ìˆ—
			else if(squatdown==1&&((colorY0-hipcentersyokitiy)<8))//&&(((colorX17-colorX13)-(kneeleftsyokitix-kneerightsyokitix))<1))
			{
				squatup=1;
				}
//˜‚Ìã‚°‰º‚°1‰ñ•ª‚ªI‚í‚Á‚½Û‚Ìˆ—
			if(squatdown==1&&squatup==1&&squatcounterkaisuua==0){
				squatcounterkaisuua++;//ƒXƒNƒƒbƒg1‰ñ•ª‚ÌˆêŽž“I‚ÈƒJƒEƒ“ƒ^[
				}
			if(squatcounterkaisuua==1){
				squatdown=0;//˜‰º‚°‰Šú‰»
				squatup=0;//˜ã‚°‰Šú‰»
				squatcounterkaisuub++;//ƒXƒNƒƒbƒg‰ñ”ƒJƒEƒ“ƒ^[‚ð‘‚â‚·
				}
			if(squatcounterkaisuub==1){//ƒXƒNƒƒbƒg1‰ñ–Ú
				printf("‚¢[‚¿\n");
				if(squatonseistopper==0){//‰¹º‚ðˆê‰ñ‚¾‚¯Ä¶‚·‚é‚½‚ß‚ÌƒXƒgƒbƒp[
					sndPlaySound("1.wav",SND_ASYNC);
					squatonseistopper=1;
					std::ofstream ofs1("macro1.csv");
		ofs1 << "2" << std::endl;
				}
				squatcounterkaisuua=0;
				}
			if(squatcounterkaisuub==2){//ƒXƒNƒƒbƒg2‰ñ–Ú
				printf("‚É[\n");
				if(squatonseistopper==1){
					sndPlaySound("2.wav",SND_ASYNC);
					squatonseistopper=2;
				}
				squatcounterkaisuua=0;
				}
			if(squatcounterkaisuub==3){//ƒXƒNƒƒbƒg3‰ñ–Ú
				printf("‚³[‚ñ\n");
				if(squatonseistopper==2){
					sndPlaySound("3.wav",SND_ASYNC);
					squatonseistopper=3;
					std::ofstream ofs1("macro1.csv");
		ofs1 << "1" << std::endl;
				}
				squatcounterkaisuua=0;
				}
			if(squatcounterkaisuub==4){//ƒXƒNƒƒbƒg4‰ñ–Ú
				printf("‚æ[‚ñ\n");
				if(squatonseistopper==3){
					sndPlaySound("4.wav",SND_ASYNC);
					squatonseistopper=4;
				}
				squatcounterkaisuua=0;
				}
			if(squatcounterkaisuub==5){//ƒXƒNƒƒbƒg5‰ñ–Ú
				printf("‚²[\n");
				if(squatonseistopper==4){
					sndPlaySound("5end.wav",SND_ASYNC);
					Sleep(3000);
					squatonseistopper=0;//‰Šú‰»
				}
				squatcounterkaisuua=0;
				end=1;
				}
				
			std::ifstream ifs( "start.csv" );
			std::string str1;
			ifs >> str1;
			if(end==1){//I—¹ˆ—‹Lq•”(ƒXƒNƒƒbƒg‚ª5‰ñs‚í‚ê‚Äend‚É‚P‚ª“ü‚é‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é)
				skeletontracked=0;
				squatcounterkaisuua=0;
				squatcounterkaisuub=0;
				squatup=0;
				squatdown=0;
				end=0;
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚é
				writing_file.open(filename, std::ios::out);
				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðÅ‰‚ÉŠª‚«–ß‚·
				mciSendCommand(mop.wDeviceID,MCI_CLOSE,0,0);//mci‚ðƒNƒ[ƒY‚³‚¹‚é
				sndPlaySound("wonderful.wav",SND_ASYNC);
				Sleep(1500);
				sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);
				std::cout << "ˆ—’âŽ~,‚¨‚Â‚©‚ê‚³‚Ü‚Å‚µ‚½ " << std::endl;
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				break;
	            }

			if(str1=="0"||colorY5<=300&&colorY17<=500&&skeletontracked==1){//‹Ù‹}I—¹ˆ—‹Lq•”(0‚ª“ü—Í‚³‚ê‚é‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é)
				skeletontracked=0;
				squatcounterkaisuua=0;
				squatcounterkaisuub=0;
				squatup=0;
				squatdown=0;
				end=0;
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚é
				writing_file.open(filename, std::ios::out);

				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðÅ‰‚ÉŠª‚«–ß‚·
				sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);
				std::cout << "‹Ù‹}’âŽ~, " << std::endl;
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				break;
	            }
			if(k>300){//‹Ù‹}I—¹ˆ—‹Lq•”(0‚ª“ü—Í‚³‚ê‚é‚Æˆ—‚ðI—¹‚µÅ‰‚Ìcsvƒtƒ@ƒCƒ‹ŠÄŽ‹ˆ—‚É–ß‚é)
				skeletontracked=0;
				squatcounterkaisuua=0;
				squatcounterkaisuub=0;
				squatup=0;
				squatdown=0;
				end=0;
				std::string filename = "start.csv";
				std::ofstream writing_file;//ˆ—‚ªI—¹‚µ‚½‚½‚ßstart.csv‚ð‰Šú‰»‚·‚é
				writing_file.open(filename, std::ios::out);
				mciSendCommand(mop.wDeviceID,MCI_STOP,0,0);//BGM‚ðƒXƒgƒbƒv
				mciSendCommand(mop.wDeviceID,MCI_SEEK,MCI_SEEK_TO_START,0);//BGM‚ðÅ‰‚ÉŠª‚«–ß‚·
				sndPlaySound("otsukaresamadeshita.wav",SND_ASYNC);
				std::cout << "’âŽ~, " << std::endl;
				std::ofstream ofs1("macro1.csv");
				ofs1 << "0" << std::endl;
				break;
	            }
		}
}
}
return 0;

 }
//‚±‚±‚Ü‚Å‚ª•Àsˆ—•”•ª



void main()//ƒƒCƒ“ŠÖ”
{
	
	HANDLE th;
	th = (HANDLE)_beginthreadex(NULL, 0,&tocco , NULL, 0, NULL);//•À—ñˆ—•”•ª‚ðŒÄ‚Ño‚µ‚Ä‚¢‚éB
	try{
	KinectSample kinect;
    kinect.initialize();
	kinect.run();
	 }
  catch ( std::exception& ex ) {
    std::cout << ex.what() << std::endl;
  }
};
