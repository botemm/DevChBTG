/*
=====================================================================
�����: ������� ��� ������������
��������: botemm
����: ����� ����������� ��� ��������� ���������� OpenGL ������ �������� C++
����������: ��������� ������������
�������� 23,6,2018
*/


//void (*func)(std::string Name,int id);



#pragma once

#include <string>       //�����
#include <vector>       //������
#include <fstream>      //������ � �������
#include<GL\gl.h>      //�������
#include <GL\glu.h>     //�������
#include <GL\GLAUX.H>//�������
#include<stdio.h>

#pragma comment(lib,"Glaux.lib")
#pragma comment(lib,"Glu32.lib")
#pragma comment(lib,"glui32.lib")

#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
 
#include<iostream>

class DevChBTG
{
//=====================================================================================================
//================�������_������======================================================�������========

//2019 Font

public:
//����� ��� ������ � �������
class fonts
{
public:
	struct // windowsInfo
	{
		int WindowsHeight;
		int WindowsWidth;

		int ViewportWidth;
		int ViewportHeight;

		int ViewportPosX;
		int ViewportPosY;
	}WindowsData;
	

public:



	//struct convert
	//³��������� �������� ��� ����������� � �������� ������ ���� ������� ������� �������� ��������
	struct Cv2x
	{
		int code;
		int unicode;
	};

	
	//2d point
	struct d2
	{
		float x,y;
	};


	//��������� ������
	struct fragment
	{
		float pX,kX,pY,kY;
	};

	struct Texture
	{
		int width,height;
		GLuint texture;
		int nrComponents;
	};

	struct font
	{
		//name
		std::string name;
		//������ ��������
		std::vector<fragment>frag;

		//���� �������
		std::vector<Cv2x>CodeChar;
		//��������
		Texture texture;
	};

	//����� � ������������� ��������
	std::vector<font>FontsArray;

	
	

	//����������� ����� � ���������� ��� ���� ��������� ������� ������ ��������
	int UnicodeToCharCode(int code,int defCH,font &Sh)
	{
		for(int i = 0; i < Sh.CodeChar.size();i++)
		{
			if(Sh.CodeChar[i].unicode == code)
				return Sh.CodeChar[i].code;
		}
		return defCH;
	}

	int UnicodeToCharCode(int code,int defCH)
	{
		return UnicodeToCharCode(code,defCH,FontsArray[DefaultFonts]);
	}


	int CharCodeToUnicode(int code,int defCH,font &Sh)
	{
		for(int i = 0; i < Sh.CodeChar.size();i++)
		{
			if(Sh.CodeChar[i].code == code)
				return Sh.CodeChar[i].unicode;
		}
		return defCH;
	}

	int CharCodeToUnicode(int code,int defCH)
	{
		return CharCodeToUnicode(code,defCH,FontsArray[DefaultFonts]);
	}


	


	

int  DefaultFonts;
	fonts()
	{	
	  DefaultFonts = 0;
	}

	std::string ErrorList;	




	void Init()
	{
	}
		
    
	private:
	float HeightLine;

	public:


struct POINT2D
{
	float x,y;
};


//�������� ������ ������ � �������
float getWigthText(std::string text,float Style,float size)
{

		float fontID = Style;
		//

		float zm = 0;
		for(int i = 0; i < text.size();i++ )
		{
			 zm+=getWigthText((char)text[i],fontID,size);
			
		}
		
		return zm;
}

float getWigthText(std::string text,float Style,float size,int EndCar)
{

		float fontID = Style;
		//

		float zm = 0;
		for(int i = 0; i < text.size() && i < EndCar;i++ )
		{
			 zm+=getWigthText((char)text[i],fontID,size);
			
		}
		
		return zm;
}

float getWigthText(char CHARone,int fontStyle,int size)
{
		
	if(FontsArray.size()<= fontStyle)
	return 0;
	
		int fontID = fontStyle;
		int fragID = 0;


//������ id ������� � ���� ������
				for(int i = 0;i<FontsArray[fontID].CodeChar.size(); i++){if(FontsArray[fontID].CodeChar[i].code == (int)CHARone){fragID = i;break;}}
		
				//�������� ���� ���������� OpenGL � 1 ����� ������ �� � � �  ��� ������ �������� �������� �� ��� ���������� �� �� ����� ���������� ����� � �������� ������� ��������� OpenGL
				float cofX = 2.0f / ((float)WindowsData.ViewportWidth  );
				float cofY = 2.0f / (float)WindowsData.ViewportHeight;


				//����������� ��������� ����� � �������� OpenGL
				float  SizeX = (size*cofX);
				float  SizeY = (size*cofY);

				//����������� ����������� �������� � �������� ������� � ������ OpenGL
				//x=cofX;
				//y=cofY;

				//��� �� ������� ������� ��������� OpenGL � ����� ������ � ������� �� � ���� ����� �����
			//	x-=1;
				//y-=1;


				//float X_CORD,Y_CORD;
				float PosX = 0;
				float PosY = 0;




				//��� � ������� ������ ���������� ��������� ����� ������� ��������� �� 0 �� 1. ��� ���� ��� ����� �� ������ ��������� ����� ��� ���� �� ���� �����������.
				float wi = FontsArray[fontID].frag[fragID].kX - FontsArray[fontID].frag[fragID].pX;
				float hi = FontsArray[fontID].frag[fragID].kY - FontsArray[fontID].frag[fragID].pY;

				//���������� ��������� ����������� ����� � ����������� ����������� ������ �������� � ������ �����
				float cof = (FontsArray[fontID].texture.width/FontsArray[fontID].texture.height) * (wi/hi);
	
				

				/*DrawPlane(PosX,PosY, //������ �������� ���������� � ������ OpenGL
					PosX + SizeX*cof,PosY + SizeY, //������ ����� ���������� � ������ OpenGL
					FontsArray[fontID].frag[fragID].pX,-FontsArray[fontID].frag[fragID].pY,FontsArray[fontID].frag[fragID].kX,-FontsArray[fontID].frag[fragID].kY); //��� �������� ����������

		*/
				//���������� ������ ����� ���������� � ������� ���������� �� ����� �� Y �������� � ��������� ����� ���������� � ���������� ����� �����
				float WidthText = (SizeX*cof)/cofX;
				return WidthText;
}




	float print(std::string text,float x,float y,int fontStyle, int size)
	{
		if(FontsArray.size() <= fontStyle) return 0;
		//y = - y;
		float fontID = fontStyle;
		//
		glBindTexture(GL_TEXTURE_2D,FontsArray[fontID].texture.texture);
		//glColor4ub(255,255,255,255);

		for(int i = 0; i < text.size();i++ )
		{
			float zm =print((char)text[i],x,y,fontID,size);
			x+=zm;
		}

		return x;
	}

	float print(char CHARone,float x,float y,int fontStyle, int size)
	{
		
		int fontID = fontStyle;
		int fragID = 0;


//������ id ������� � ���� ������
				for(int i = 0;i<FontsArray[fontID].CodeChar.size(); i++){if(FontsArray[fontID].CodeChar[i].code == (int)CHARone){fragID = i;break;}}
		
				//�������� ���� ���������� OpenGL � 1 ����� ������ �� � � �  ��� ������ �������� �������� �� ��� ���������� �� �� ����� ���������� ����� � �������� ������� ��������� OpenGL
				float cofX = 2.0f / ((float)WindowsData.ViewportWidth  );
				float cofY = 2.0f / (float)WindowsData.ViewportHeight;


				//����������� ��������� ����� � �������� OpenGL
				float  SizeX = (size*cofX);
				float  SizeY = (size*cofY);

				//����������� ����������� �������� � �������� ������� � ������ OpenGL
				x*=cofX;
				y*=cofY;

				//��� �� ������� ������� ��������� OpenGL � ����� ������ � ������� �� � ���� ����� �����
				x-=1;
				y-=1;


				//float X_CORD,Y_CORD;
				float PosX = x;
				float PosY = y;




				//��� � ������� ������ ���������� ��������� ����� ������� ��������� �� 0 �� 1. ��� ���� ��� ����� �� ������ ��������� ����� ��� ���� �� ���� �����������.
				float wi = FontsArray[fontID].frag[fragID].kX - FontsArray[fontID].frag[fragID].pX;
				float hi = FontsArray[fontID].frag[fragID].kY - FontsArray[fontID].frag[fragID].pY;

				//���������� ��������� ����������� ����� � ����������� ����������� ������ �������� � ������ �����
				float cof = (FontsArray[fontID].texture.width/FontsArray[fontID].texture.height) * (wi/hi);
	
				

				DrawPlane(PosX,PosY, //������ �������� ���������� � ������ OpenGL
					PosX + SizeX*cof,PosY + SizeY, //������ ����� ���������� � ������ OpenGL
					FontsArray[fontID].frag[fragID].pX,-FontsArray[fontID].frag[fragID].pY,FontsArray[fontID].frag[fragID].kX,-FontsArray[fontID].frag[fragID].kY); //��� �������� ����������

		
				//���������� ������ ����� ���������� � ������� ���������� �� ����� �� Y �������� � ��������� ����� ���������� � ���������� ����� �����
				float WidthText = (SizeX*cof)/cofX;
				return WidthText;

				
	}



	float DrawPlane(float px,float py,float kx, float ky, float Tpx,float Tpy,float Tkx, float Tky)
	{
	
				/*glDisable(GL_TEXTURE_2D);
				glBegin(GL_LINE_LOOP);
			    glVertex2f(px,py);
				glVertex2f(kx,py);
				glVertex2f(kx,ky);
				glVertex2f(px,ky);
				glEnd();
				glEnable(GL_TEXTURE_2D);*/

				glBegin(GL_QUADS);
					glTexCoord2f(Tpx,Tpy);	glVertex2f(px,py);
					glTexCoord2f(Tkx,Tpy);	glVertex2f(kx,py);
					glTexCoord2f(Tkx,Tky);   glVertex2f(kx,ky);
					glTexCoord2f(Tpx,Tky);   glVertex2f(px,ky);
				glEnd();

	
	
	return 0;
	}


	 bool load(string url)
	 {
		 font DEF;
		 std::ifstream INp(url.c_str(), ios::binary | ios::in);


		 if(!INp) {ErrorList += "���� �������\n"; return false;}

		 //������� ���� ���� ��� �������� �� ��������� ���� �������============================================
				int CodeFiles = 0; //1546534
				INp.read((char*)&CodeFiles,sizeof(CodeFiles)); //��� �����

				if(CodeFiles != 1546534) {ErrorList += "�������������� ������\n"; return false;}



		//������� ���� �����==================================================================================
				short Version = 0; //1
				INp.read((char*)&Version,sizeof(Version)); //����� �����

				if(Version < 1 || Version == 0) {ErrorList += "������������� ����� �����\n"; return false;}

		//������� �������======================================================================================
				if(INp.eof()) std::cout<<"ʳ���� ����� �� ��:"<<std::endl; else  std::cout<<"�� ��� ����:"<<std::endl;
		int SS = 0; 
		INp.read((char*)&SS,sizeof(SS)); //������� 
		std::cout<<"SizeFrag:"<<SS<<std::endl;
		DEF.frag.resize(SS);
		INp.read((char*)&DEF.frag[0],sizeof(fragment)*SS);

		//���� ���������� ���������=======================================================================
				

				int sz = 0; //����� ������
				INp.read((char*)&sz,sizeof(sz));    //������� ������
				std::cout<<"SizeKode:"<<sz<<std::endl;

				//if(INp.eof()) std::cout<<"ʳ���� ����� �� ��:"<<std::endl; else  std::cout<<"�� ��� ����:"<<std::endl;


				DEF.CodeChar.resize(sz);
				INp.read((char*)&DEF.CodeChar[0],sizeof(Cv2x)*sz);    //�����
				


	
	 
		
				//����� ����������====================================================================================
				//�������� ����� ���������� ��� ����������
				INp.read((char*)&DEF.texture.width,sizeof(DEF.texture.width));                //������
				INp.read((char*)&DEF.texture.height,sizeof(DEF.texture.height));              //������
				INp.read((char*)&DEF.texture.nrComponents,sizeof(DEF.texture.nrComponents));  //ʳ������ ��������� � 1 �����

				int size = DEF.texture.width*DEF.texture.height*DEF.texture.nrComponents;				//ʳ������ ��� ������


				std::cout<<"wi = "<<DEF.texture.width<<"   hi = "<<DEF.texture.height<<"  mod:"<<DEF.texture.nrComponents<<std::endl;
	            

				

				vector<char> image1(size);
				INp.read(&image1[0],size*sizeof(unsigned char));						//������ ����� ������

				//��������� ��������-----------
				GLenum format;
				if (DEF.texture.nrComponents == 1)
					format = GL_RED;
				else if (DEF.texture.nrComponents == 3)
					format = GL_RGB;
				else if (DEF.texture.nrComponents == 4)
					format = GL_RGBA;

				glBindTexture(GL_TEXTURE_2D, DEF.texture.texture);
				glTexImage2D(GL_TEXTURE_2D, 0, format,  DEF.texture.width,  DEF.texture.height, 0, format, GL_UNSIGNED_BYTE, &image1[0]);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				



				//������� �� ��� ������
				FontsArray.push_back(DEF);
	            return true;
				
	 }

	bool loadPR(string url)
	{
		   /* font DEF;
			LoTEinfo t = loadTexture(url.c_str());
			DEF.texture.texture = t.textureID;
			DEF.texture.width = t.width;
			DEF.texture.height = t.height;

	
				string urlN = url;
				urlN += ".conf";
				ifstream in(urlN,ios::binary);
				int SS;
				in.read((char*)&SS,sizeof(SS));
				cout<<"SIZE "<<SS<<endl;
				for(int i = 0; i < SS ; i++)
				{
					fragment Temp;
					in.read((char*)&Temp,sizeof(Temp) );	
					DEF.frag.push_back(Temp);
				}

				
				in.close();


				{
				string U1 = url;
				string U2 = U1;

				U1+=".charCode.txt";
				U2+=".unicode.txt";

				ifstream InChar(U1.c_str());
				ifstream InUni(U2.c_str());

				while(!InChar.eof())
				{
					Cv2x T;
					InChar>>T.code;
					InUni>>T.unicode;
					DEF.CodeChar.push_back(T);
				}

				InUni.close();
				InChar.close();

			
				}


				FontsArray.push_back(DEF);
				return true;
				*/
		return false;
	}
	

};
fonts FontSystems;


//=====================================================================================================


public:
	void Enable(bool &param)
	{
		param = true;
	}

	void Disable(bool &param)
	{
		param = false;
	}

//=====================================================================================================



public:
//GLuint *TexLoad(char *url);

private:






private:
class TEXTURE
{
public:
	bool ISusTextureLoader; //�� ��������� ���������� ������� ������������ �������
	//������� ��� ����������� ������� ��� ������ ��������� �������� ���� ������� ����������� ������������
	bool (*usTextureLoader)(std::string url, int &width, int &height, GLuint &TxID);
	void setVoidTextureLoader(bool (TextureLoaderA)(std::string url, int &width, int &height, GLuint &TxID))
	{
		usTextureLoader = TextureLoaderA;
		ISusTextureLoader = true;
		return;
	}


	TEXTURE()
	{
		ISusTextureLoader = false;
	}
private:

GLuint CreateTexture(unsigned char* image,GLuint   type, int width, int height)
{
  GLuint Idtexture;
  glGenTextures(1, &Idtexture);  // ������������� OpenGL �������� IDs
  glBindTexture(GL_TEXTURE_2D,Idtexture); // ��������� ���� ��������

  // �������� ����������
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // �������� ���������� 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 
  glTexImage2D(GL_TEXTURE_2D, 0, type, width, height,0, type, GL_UNSIGNED_BYTE, image);
 return Idtexture;
}


	public:
		typedef   struct                      // ��������� ��� ������������ � �� �������, ������� �������� ��������� ��� ��������
		 { 
			   unsigned char  *imageData;                  // ������ ����������� (�� 32 ���)
			   GLuint   bpp;                         // ������� ����� � ����� �� �������
			   GLuint   width;                       // ������ ����������� 
		       GLuint   height;                      // ������ �����������
			   GLuint   texID;                       // texID ������������ ��� ������ // ��������
		 } Knopka_TextureImage;                       // ��� ���������

struct TExtureHistory
		{
			std::string url;
			GLuint TextureID;
		};
		std::vector<TExtureHistory>TExtureHistory_; //������ ����������� ������� ��� ������������

bool  Knopka_LoadTga(GLuint &texID,std::string filename)  // ��������� TGA ���� � ������
{  
Knopka_TextureImage teIm;
Knopka_TextureImage *texture = &teIm;
	
GLubyte  TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0}; // ��������� ��������� TGA �����
GLubyte  TGAcompare[12]; // ������������ ��� ��������� ��������� TGA �����
GLubyte  header[6];      // ������ 6 �������� ���� ���������
GLuint   bytesPerPixel;  // ���������� ������ �� ������� ������������ � TGA �����
GLuint   imageSize;      // ���������� ������, ����������� ��� �������� ����������� � ������
GLuint   temp;           // ��������� ����������
GLuint   type=GL_RGBA;   // ��������� �� ��������� ����� RBGA (32 BPP)
  FILE *file = fopen(filename.c_str(), "rb");         // �������� TGA �����
  if(file==NULL ||                            // ���������� �� ����
fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||  // ���� ��������� 12 ������ ���������

     memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0 || // ���� ��������� ����������

     fread(header,1,sizeof(header),file)!=sizeof(header)) // ���� ��������� ��������� 6 ������

  {

         if (file == NULL)                      // ���� ������

                return false;                   // ���������� false

         else

         {

                fclose(file);                   // ���� ������, ��������� ����

                return false;                   // ���������� false

         }

  }


  // ���������� ������ TGA (������� ����*256+������� ����)

  texture->width  = header[1] * 256 + header[0]; 

  // ���������� ������ TGA (������� ����*256+������� ����)

  texture->height = header[3] * 256 + header[2];

  

  if(texture->width  <=0 ||            // ���� ������ ������ ��� ����� ����

   texture->height <=0 ||            // ���� ������ ������ ��� ����� ����    

  (header[4]!=24 && header[4]!=32))  // �������� �� TGA 24 ��� 32 ������?

  {

    fclose(file);                    // ���� ���-�� ������, ��������� ����

    return false;                    // ���������� false

  }


  texture->bpp  = header[4];        // �������� TGA ���/������� (24 or 32)

  bytesPerPixel = texture->bpp/8;   // ����� �� 8 ��� ��������� ����/�������  

  // ������������ ������ ������ ��� ������ TGA

  imageSize = texture->width*texture->height*bytesPerPixel;
  texture->imageData=(GLubyte *)malloc(imageSize); // ����������� ������ ��� �������� ������ TGA 
  if(texture->imageData==NULL ||           // ������� �� �������� ������?
   fread(texture->imageData, 1, imageSize, file)!=imageSize)
  // ������ ���������� ������ �����  imageSize?
  {
    if(texture->imageData!=NULL)       // ���� �� ��������� ������?

      free(texture->imageData);        // ���� ��, �� ����������� ������

  

    fclose(file);                      // ��������� ����

	texID = texture->texID;

    return false;                      // ���������� false

  } 


  for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)  // ���� �� ������, ����������� �����������

  {                                                    // ������ 1�� � 3�� ������ ('R'ed � 'B'lue)

    temp=texture->imageData[i];                        // �������� ��������� �������� imageData[i]

    texture->imageData[i] = texture->imageData[i + 2]; // ������������� 1� ���� � �������� 3�� �����

    texture->imageData[i + 2] = temp;                  // ������������� 3� ���� � ��������,

                                                       // ���������� � temp (�������� 1�� �����)

  }

  fclose (file);                                       // ��������� ����

/*
  // ������ �������� �� ������

  glGenTextures(1, &texture[0].texID);  // ������������� OpenGL �������� IDs

  glBindTexture(GL_TEXTURE_2D, texture[0].texID); // ��������� ���� ��������

  // �������� ����������

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // �������� ���������� 

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (texture[0].bpp==24)                      // ���� TGA 24 ������

  {
     type=GL_RGB;                            // ��������� 'type' � GL_RGB
  }
  glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height,0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
  texID = texture->texID;
  */
  
  if (texture[0].bpp==24)                      // ���� TGA 24 ������

  {
     type=GL_RGB;                            // ��������� 'type' � GL_RGB
  }
  texID = CreateTexture(texture[0].imageData,type, texture[0].width, texture[0].height);
  return true;              // ���������� �������� ������ Ok, ��������� true
  
}

bool  LoadBMP(GLuint &out_img,string filename) //�������� bmp
{ 


   GLuint texture;
/*
  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename.c_str(), "rb" );

  if ( file == NULL ) return 0;
  width = 1024/2;
  height = 512/2;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}
*/


   AUX_RGBImageRec *texture1;
   texture1 = auxDIBImageLoad(filename.c_str());

out_img = CreateTexture(texture1->data, GL_RGB, texture1->sizeX, texture1->sizeY);


  return 1; 
} 





bool  Knopka_LoadTexture(GLuint &texture,std::string filename)  // ��������� TGA ���� � ������
{    
	//int wi
	//DevChBTG::ISusTextureLoader;

	
  


	//���������� ������������ ������� �� ��� ����
	int i = 0;
	while(i < TExtureHistory_.size())
	{
		if(TExtureHistory_[i].url == filename)
		{
			texture = TExtureHistory_[i].TextureID;
			return 1;
		}
		i++;
	}


	
	
	bool Rez = 0;


	if(ISusTextureLoader)
	{
		int w,h;
		GLuint id;
		Rez = usTextureLoader(filename,w,h,texture);
	}
	 else
	{
		if(filename[filename.size()-4] == '.' && (filename[filename.size()-3] == 'T' || filename[filename.size()-3] == 't')  &&  (filename[filename.size()-2] == 'G' || filename[filename.size()-2] == 'g') && (filename[filename.size()-1] == 'A' || filename[filename.size()-1] == 'a'))
		{
		 Rez = Knopka_LoadTga(texture,filename);  // ��������� TGA ���� � ������
		}
		else
		if(filename[filename.size()-4] == '.' && (filename[filename.size()-3] == 'B' || filename[filename.size()-3] == 'b')  &&  (filename[filename.size()-2] == 'M' || filename[filename.size()-2] == 'm') && (filename[filename.size()-1] == 'P' || filename[filename.size()-1] == 'p'))
		{
		  Rez = LoadBMP(texture,filename); //�������� bmp
		}
	}




	if(Rez) //���� �������� ���� ����������� ��������� �� ������� �� �� �����
	{
	TExtureHistory IS;
	TExtureHistory_.push_back(IS);
	TExtureHistory_[TExtureHistory_.size()-1].url = filename;
	TExtureHistory_[TExtureHistory_.size()-1].TextureID = texture;
	}

  return Rez;              // ���������� �������� ������ Ok, ��������� true

}



};

//=====================================================================================================
//=====================================================================================================
//================�������_������======================================================ʳ����=========
//=====================================================================================================
//=====================================================================================================

public:
TEXTURE textureLoader;



//=================
//������� �� ����� ������������� �� ���
public:
	//������� ��� ����������� ������� ��� ������ ��������� �������� ���� ������� ����������� ������������
	void setVoidTextureLoader(bool (TextureLoaderA)(std::string url, int &width, int &height, GLuint &TxID))
	{
		textureLoader.setVoidTextureLoader(TextureLoaderA);
		return;
	}


public:
	







//2019 Mode Aspiranska========

//������� ������ ��� ��������� ���� ��������� �� ����

//������� ��������� ������ �������� �����������
bool isVoidDrawPlane;
void (*VoidDrawPlane)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid);
void setVoidDrawPlane(void (*VoidDrawPlaneA)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid))
{
	VoidDrawPlane = VoidDrawPlaneA;
	Enable(isVoidDrawPlane);
}




//�������� �������� ������� �������
void DrawStyleElements(int id, float x,float y, float width, float height)
{
	//�� �������� �� ������ ������
	if(!mObgects[id].Vizual) return;



	glBindTexture(GL_TEXTURE_2D,mObgects[id].ImageKnopki);
	float SizeX , SizeY ,PosX ,PosY;
	float HoverSizeX,HoverSizeY;//,HoverPosY,HoverPosX;
	//���������� ����������� ������ 
				float cofX = 2.0f / (float)windows_data.ViewportWidth ;
				float cofY = 2.0f / (float)windows_data.ViewportHeight ;
			{
				

				//������ � ������ ���������� ��������
				 SizeX = ((float)mObgects[id].SizeX*cofX);
				 SizeY = ((float)mObgects[id].SizeY*cofY);
				


				 PosY =  ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY/2)*cofY)-1;
                 PosX =  ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].SizeX/2)*cofX)-1;



				 //������ � ������ ���������� ��������
				 HoverSizeX = ((float)mObgects[id].HoverSizeX*cofX);
				 HoverSizeY = ((float)mObgects[id].HoverSizeY*cofY);
				
				/* HoverPosY =  ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].HoverSizeY/2)*cofY)-1;
				 HoverPosX =  ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].HoverSizeX/2)*cofX)-1;*/
			}
			//draw


			

			
			//glBindTexture(GL_TEXTURE_2D,mObgects[id].ImageKnopki);

			//float

			//���� ������� �� ���������
				if(mObgects[id].Temp.activ)
					glColor4ub(mObgects[id].HoverColor.R ,mObgects[id].HoverColor.G,mObgects[id].HoverColor.B,mObgects[id].HoverColor.A);
				else
					glColor4ub(mObgects[id].Color.R ,mObgects[id].Color.G,mObgects[id].Color.B,mObgects[id].Color.A);


			if(mObgects[id].Type == "checkBox" || mObgects[id].Type == "radioBox")
			{
				
				
				float Typos;
				if(mObgects[id].Checked)
					Typos = 0;
				else
					Typos = 0.5;


				if(mObgects[id].Temp.activ)
					DrawPlane(HoverSizeX,HoverSizeY,PosX,PosY,1,0.5,0,Typos,mObgects[id].RotationMode);
				else
					DrawPlane(SizeX,SizeY,PosX,PosY,1,0.5,0,Typos,mObgects[id].RotationMode);
			}
			else
			if(mObgects[id].Type == "trackBar")
			{


				if(mObgects[id].RotationMode == 'H')
				{


				if(mObgects[id].Temp.activ)
					DrawPlane(HoverSizeX,HoverSizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				else
					DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);



				
				if(mObgects[id].trackBarKaretkaActiv)
				glColor4ub(mObgects[id].trackBarKaretkaHoverColor.R,mObgects[id].trackBarKaretkaHoverColor.G,mObgects[id].trackBarKaretkaHoverColor.B,mObgects[id].trackBarKaretkaHoverColor.A);
				else
				glColor4ub(mObgects[id].trackBarKaretkaColor.R,mObgects[id].trackBarKaretkaColor.G,mObgects[id].trackBarKaretkaColor.B,mObgects[id].trackBarKaretkaColor.A);
				glBindTexture(GL_TEXTURE_2D,mObgects[id].Image2);




					//������� � ����� ���� �������
				float EndPos = ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].SizeX - (float)mObgects[id].trackBarKaretkaSizeX/2)*cofX )-1;
				float StartPos = ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].trackBarKaretkaSizeX/2)*cofX)-1;
				float MaxValue = EndPos - StartPos;

				
				float VEnd = mObgects[id].MaxValue - mObgects[id].MinValue;
				float Val = mObgects[id].Value - mObgects[id].MinValue;
				//float vStart = 0;

				//����� � �������� �� 0 �� 1
				float Value = Val/VEnd;
				
				DrawPlane(mObgects[id].trackBarKaretkaSizeX*cofX,mObgects[id].trackBarKaretkaSizeY*cofY,StartPos+MaxValue*Value,PosY,1,1,0,0,mObgects[id].RotationMode);

				}
				else //======================================================================================================
				if(mObgects[id].RotationMode == 'W') //������������ ���� ���
				{


				if(mObgects[id].Temp.activ)
					DrawPlane(HoverSizeX,HoverSizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				else
					DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);



				
				if(mObgects[id].trackBarKaretkaActiv)
				glColor4ub(mObgects[id].trackBarKaretkaHoverColor.R,mObgects[id].trackBarKaretkaHoverColor.G,mObgects[id].trackBarKaretkaHoverColor.B,mObgects[id].trackBarKaretkaHoverColor.A);
				else
				glColor4ub(mObgects[id].trackBarKaretkaColor.R,mObgects[id].trackBarKaretkaColor.G,mObgects[id].trackBarKaretkaColor.B,mObgects[id].trackBarKaretkaColor.A);
				glBindTexture(GL_TEXTURE_2D,mObgects[id].Image2);




					//������� � ����� ���� �������
				float EndPos = ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY - (float)mObgects[id].trackBarKaretkaSizeY/2)*cofY )-1;
				float StartPos = ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].trackBarKaretkaSizeY/2)*cofY)-1;
				float MaxValue = EndPos - StartPos;

				
				float VEnd = mObgects[id].MaxValue - mObgects[id].MinValue;
				float Val = mObgects[id].Value - mObgects[id].MinValue;
				//float vStart = 0;

				//����� � �������� �� 0 �� 1
				float Value = Val/VEnd;
				
				DrawPlane(mObgects[id].trackBarKaretkaSizeX*cofX,mObgects[id].trackBarKaretkaSizeY*cofY,PosX,StartPos+MaxValue*Value,1,1,0,0,mObgects[id].RotationMode);

				}

				//PosY =  ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY/2)*cofY)-1;
                 
				

				/*glColor4ub(255,255,255,255);//EndLine
				DrawPlane(3 * cofX,50*cofY,
					EndPos
					,
					((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY/2 )*cofY)-1
					,1,1,0,0);

				//StartLine
				DrawPlane(3 * cofX,50*cofY,
					StartPos
					,
					((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY/2)*cofY)-1
					,1,1,0,0);*/


			}
			else
			if(mObgects[id].Type == "Label" || mObgects[id].Type == "label") // ��� ������� ���������� �� �������
			{

				

				/*if(mObgects[id].Temp.activ)
					DrawPlane(HoverSizeX,HoverSizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				else
					DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
					*/
				

			}
			else

				
			//if(mObgects[id].Type == "Button") && if(mObgects[id].Type == "textBox")
			{
				if(mObgects[id].Temp.activ)
					DrawPlane(HoverSizeX,HoverSizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				else
					DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
			}




			float Xx = (X_CORD - windows_data.ViewportPosX)   + (float)mObgects[id].SizeX/2;
			float Yy = (Y_CORD  - windows_data.ViewportPosY)  + (float)mObgects[id].SizeY/2;

			float WidthFont = FontSystems.getWigthText(mObgects[id].Text,FontSystems.DefaultFonts,(float)mObgects[id].TextSize);

			if(!mObgects[id].Temp.activ)
			{
				glColor4ub(mObgects[id].TextColor.R,mObgects[id].TextColor.G,mObgects[id].TextColor.B,mObgects[id].TextColor.A);		
			}
			else
			{
				glColor4ub(mObgects[id].HoverTextColor.R,mObgects[id].
					TextColor.G,mObgects[id].HoverTextColor.B,mObgects[id].HoverTextColor.A);	
			}
		
			
			float PosTextRealX,PosTextRealY;
			PosTextRealX = Xx - WidthFont/2;
			PosTextRealY = Yy - (float)mObgects[id].TextSize/2;

			if(mObgects[id].TextPositionAlignX == 'R' || mObgects[id].TextPositionAlignX == 'r') 
				PosTextRealX = Xx + mObgects[id].SizeX/2;
			else
			if(mObgects[id].TextPositionAlignX == 'L' || mObgects[id].TextPositionAlignX == 'l') 
				PosTextRealX = Xx - WidthFont - mObgects[id].SizeX/2;

			if(mObgects[id].TextPositionAlignY == 'N' || mObgects[id].TextPositionAlignY == 'n') 
				PosTextRealY = Yy - (float)mObgects[id].TextSize - mObgects[id].SizeY/2;
			else
			if(mObgects[id].TextPositionAlignY == 'W' || mObgects[id].TextPositionAlignY == 'w') 
				PosTextRealY = Yy + mObgects[id].SizeY/2;


			//�������� �����
			FontSystems.print(mObgects[id].Text	,PosTextRealX	,PosTextRealY	,FontSystems.DefaultFonts,mObgects[id].TextSize);

			//�������� ������ �������� ��� ����� �����
			if(IdTheLastPush == id)
			{
			if(mObgects[IdTheLastPush].Type == "textBox")
			if(sin(Time*7)>0)
				{
					float WidthFontCursorRead = FontSystems.getWigthText(mObgects[id].Text,FontSystems.DefaultFonts,(float)mObgects[id].TextSize,mObgects[id].PosTextCursor);
					glDisable(GL_TEXTURE_2D);
			
					DrawPlane((float)mObgects[id].TextSize/15*cofX,(float)mObgects[id].TextSize*cofY,PosTextRealX*cofX-1 + (WidthFontCursorRead*cofX),PosY,0,0,0,0,mObgects[id].RotationMode);
					glEnable(GL_TEXTURE_2D);
				}
			}

			
}




void DrawPlane(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid)
{
	

	glUseProgram(0);

	glColor4ub(R,G,B,A);
	glBindTexture(GL_TEXTURE_2D,TextuteID);
	DrawPlane();
}



void DrawPlane()
{
	DrawPlane(2,2,0,0,1,1,0,0,'H');
}

void DrawPlane(float SizeX,float SizeY,float PosX,float PosY,float SizeTX,float SizeTY,float posTX,float posTY,char RotMode)
{
	SizeX/=2;
	SizeY/=2;

	//glColor4f(1,1,1,0.5);
	if(RotMode == 'H' || RotMode == 'h')	
	{
	glBegin(GL_QUADS);
											glTexCoord2f(0+posTX,0+posTY);
	glVertex2f(-SizeX+PosX,-SizeY+PosY);
											glTexCoord2f(SizeTX+posTX,0+posTY);
	glVertex2f(SizeX+PosX,-SizeY+PosY);
											glTexCoord2f(SizeTX+posTX,SizeTY+posTY);
	glVertex2f(SizeX+PosX,SizeY+PosY);
											glTexCoord2f(0+posTX,SizeTY+posTY);
	glVertex2f(-SizeX+PosX,SizeY+PosY);
	glEnd();
	}
	else
	if(RotMode == 'W' || RotMode == 'w')	
	{
		glBegin(GL_QUADS);
												glTexCoord2f(0+posTX,SizeTY+posTY);
		
		glVertex2f(-SizeX+PosX,-SizeY+PosY);
												glTexCoord2f(0+posTX,0+posTY);
												
		glVertex2f(SizeX+PosX,-SizeY+PosY);
												glTexCoord2f(SizeTX+posTX,0+posTY);
												
		glVertex2f(SizeX+PosX,SizeY+PosY);
												glTexCoord2f(SizeTX+posTX,SizeTY+posTY);
												
		glVertex2f(-SizeX+PosX,SizeY+PosY);
		glEnd();
	}
}

public:


//2018 �������� ��������� ������ � �����
struct TlogBtToGrups
{
	std::string NameBT;
	std::string NameGrup;
};
std::vector<TlogBtToGrups>TlogBtToGrupsLog;
//*

//2018 fix Vidnos Pos
int tempSSX;
int tempSSY;
public:
	//====================================
	//========14_11_2017==================
	//====================================

	bool textEnable; //�� ���������� �����
	//int DirFIX;      //����� ����� ������ ����� ����� ������� ��� ����������� ���������� (���� �� ������������� ����� ���������� � �� ���������� ��� ���� ����� � ��� �� ������)













	private:
	int Y_CORD1;
	int X_CORD1;
	
public:
	std::string korin_dir; //������� �����
	    
	    struct ComandVector       //��������� ��� ���������� ������
		{
			std::string Comand_FUNC;
			std::vector<std::string> ComandLine; //����ֲ� � �� ���������
			std::vector<int> ArgLine; //������ ���������
		};
		ComandVector ComandVectorIN()
		{
			ComandVector A;
			A.Comand_FUNC = "";
			return A;
		}
		ComandVector ComandVectorTemp; //������� ����� 

	    struct GrupSetVievport    //��� �� ����������� ������� 
		 {
			 int PosX;
			 int PosY;
		 };

	     struct Maus_Data         //��������� ���������� ��� ����
         {
	           int MausX_W ,MausY_W;// ,MausX,  MausY;
               int PressState;  int MausBT;
         };

		 struct windows_info      //³����� ���������� ��� ���������� ��������� ������  ��� ��������� ������
		 {
	           Maus_Data  Maus_Data_;
			   //������ � ������ ���� ������
			   int WindowsHeight;
			   int WindowsWidth;

	           int ViewportWidth;  //������ ������ �����������
               int ViewportHeight; //������ ������ �����������
			  
			   int ViewportPosX; //������� �� � �� � ���� ������� ������� ������� � ���� ����
			   int ViewportPosY;
		 };

		 struct  PixelRGBA        //��������� ���������� ������
		 {
		       short R;
			   short G;
		       short B;
			   short A;
		 };

		 struct PSSTEXT
		 {
			   float PX,KX;
			   float PY,KY;
		 };


		 struct PrivateBT                     //��������� ��� ��� ��������� ������, �� ���� ���������� �� ���, ���� ����������� �� �������
		 {
			   PSSTEXT F; //Temp
			   bool activ;      //��������� ������
			   bool Clic;
			   bool Clic_Temp; 
			   bool TiskActiv;
			   bool Klik;
			   bool Temp_obrob; //������ ��� ����������� �� �
			   std::string URL; //������ ��������
			   std::string URL2; //������ �������� ��������
			   bool Perehvat; //����� �� ������ ���� ������������ � �� ����� ��
		 };

		 struct OBGECT						//��������� ���������� ��� ������ (������� ��������� ������)
		 {
			   PrivateBT Temp;
		       GLuint ImageKnopki;
			   std::string Type;
			   int PosX,PosY;
			   bool Enabled;
			   PixelRGBA Color;
			   int SizeX,SizeY;
			   std::string Text;
			   std::string Names;
			   bool Vizual;
			   char CHorizontal;
			   int Panel;
			   char CWertical;
			   
			   bool Avtomatic;

			  



			   //2019=============

			   //=============================================FontSetling============================
			   int TextSize;			//������ ������
			   char TextPositionAlignX;		//�������������� ������� �������� �� �
			   char TextPositionAlignY;		//�������������� ������� �������� �� Y
			   std::string FontName;	//����� ������ ��� �� ������ ����� ���������� � ������������
			   PixelRGBA TextColor;		//���� ������
			   //====================================================================================


			   //Global Setling
			   int ObjectType; //��� ��'����  Label Button CheckBox ....

			   //Check and Radio Box
			   bool Checked;
			   int RadioGrup;


			   //RagioBox
			   int GrupRadioBox;


			   //Hover
			   int HoverSizeX,HoverSizeY;
			   PixelRGBA HoverColor;
			   PixelRGBA HoverTextColor;


			   //��������� ���������� ��������� ��� ������� ������ ��������� trackBar
			   GLuint Image2;
			   float Value;
			   float MinValue;
			   float MaxValue;
			   float trackBarKaretkaSizeX;
			   float trackBarKaretkaSizeY;
			   float trackBarKaretkaHoverSizeX;
			   float trackBarKaretkaHoverSizeY;
			   bool trackBarKaretkaActiv;
			   PixelRGBA trackBarKaretkaColor;
			   PixelRGBA trackBarKaretkaHoverColor;

			   //����������� �� ������������ ���������� ������
			   char RotationMode;


			   //#2019
			   //���� �� ������ ��������� � �� ��������� ������ �� ����� ���� ��������, � ��������� ������� ������ �� �
			   bool ClickPress;



			   
			   std::vector<ComandVector>Comanda; //������ �������� ������saw
			   //new
			   bool static_func;  //�� ��������������� ������� ������ � �����

			   //������� ��� ������� ������
			   int PosTextCursor;
		};

		struct Grup //������� ����
		{
			   std::string Name;
			   std::vector<int>ID_Objects;
			   bool vizual;
			   bool Enable;

			   //2019
			   std::string type; //grup || window || panel
			   int PosX,PosY;
			   bool ISheader;
			   bool IStitle;
			   std::string title;
			   bool CloseButton;
			   bool HidentButton;
			   PixelRGBA HeaderColor;
			   PixelRGBA BackgroundColor;
			   PixelRGBA TextColor;
			   GLuint backgroundImage;
			   std::string bacgroundImageURL;

			   //������� ��� �������
			    std::string bacgroundHeaderImageURL;
				GLuint backgroundHeaderImage;
			   int heightHeader;
			   int sizeX;
			   int sizeY;

			  char CWertical;
			  char CHorizontal;

		};

 


OBGECT Knopka_IN()     //��������� ������������ ������
{
	//��'��� ���� ������
	OBGECT A;

	A.RotationMode = 'H';

	//�� ������������ �� ������ �� ���������
	A.ClickPress = false;

	//�������� ���
	A.Temp.Temp_obrob = 0;

	//������ ���������
	A.Temp.URL = "";

	//������� ������ �� ����� (������� ������� ���� ����������� ������� ��������������)
	A.PosX = 0;
	A.PosY = 0;

	//����� ������
	A.SizeX = 50;
	A.SizeY = 50;

	A.Type = "Button";
	A.Enabled = true;

	//����
	A.Color.A = 255;
	A.Color.R = 255;
	A.Color.G = 255;
	A.Color.B = 255;

	//���� ��������� ��������
	A.HoverColor.A = 200;
	A.HoverColor.R = 255;
	A.HoverColor.G = 255;
	A.HoverColor.B = 100;

	//�����
	A.Text = "";

	//��'� �� ����� ������������ ����
	A.Names = "ButtonEnemy";

	//�������� ���� ��� ����
	A.Temp.activ = 0;
	A.Temp.Clic = 0;
	A.Temp.Clic_Temp = 0;
	A.Temp.TiskActiv = 0;
	A.Temp.Klik = 0;


	//��������
	A.Vizual = true;
	
	//��������������
	A.CHorizontal = 'L';
	A.CWertical = 'W';

	
	
	
	//���� �������� ���� ���� ����������� ������� �����
	A.Avtomatic = false;

	//������ ��������
	A.Temp.URL = "";

	//#2019
	A.FontName = "Default";
	A.TextPositionAlignX = 'C';
	A.TextPositionAlignY = 'C';
	A.TextColor.R = 0;
	A.TextColor.G = 0;
	A.TextColor.B = 0;
	A.TextColor.A = 255;
	A.TextSize = 20;

	A.HoverTextColor.R = 255;
	A.HoverTextColor.G = 255;
	A.HoverTextColor.B = 0;
	A.HoverTextColor.A = 255;
	

	A.HoverSizeX = 47;
	A.HoverSizeY = 47;



	//��� ���� ������� �������� ������ �������� �����
	A.Comanda.~vector();
    return A;
}


Grup  Grup_IN()     //��������� ������������ �����
{
	Grup A;
	A.Name = "no name";
	A.vizual = 1;
	A.Enable = 1;

	A.BackgroundColor.R = 200;
	A.BackgroundColor.G = 100;
	A.BackgroundColor.B = 200;
	A.BackgroundColor.A = 200;
	A.title = "Window";

	A.TextColor.R = 0;
	A.TextColor.G = 0;
	A.TextColor.B = 0;
	A.TextColor.A = 150;



	A.HeaderColor.R = 255;
	A.HeaderColor.G = 255;
	A.HeaderColor.B = 255;
	A.HeaderColor.A = 255;

	A.heightHeader = 30;
	A.ISheader = true;
	A.type = "grup";

	A.IStitle = true;
	A.PosX = 50;
	A.PosY = 50;
	A.sizeX = 300;
	A.sizeY = 450;
	A.bacgroundImageURL = "";

	A.CWertical = 'C';
	A.CHorizontal = 'C';
	A.bacgroundHeaderImageURL = "";
		


	/*

	*/

    return A;
}

int BT_MAUSE_KLIK_KNOPKA; //��� ������ (������) ������� �� ������

//##2019
//������ ������� �� ���� � ��������� ��������� �� �����
				OBGECT& Get_Object(std::string name,bool &suces)
				{
					for(int i = 0; i < mObgects.size(); i++)
					{
						if(mObgects[i].Names == name)
						{
							 
							suces =  true;
							return mObgects[i];
						}
					}
					
					suces =  false;
				}



//Pos Ok
GrupSetVievport  Get_Position_glViewport(int SizeX,int SizeY,int PosX,int PosY,char CWertical,char CHorizontal)  //������� �������� ���� ������������ ��������� ��� ��������
{
	GrupSetVievport A;
	//������������ �� ��������
	if(CWertical == 'W' || CWertical == 'w')  
	A.PosY = (-PosY+windows_data.ViewportHeight - SizeY) +  windows_data.ViewportPosY ; 
	else 
	if(CWertical == 'C' || CWertical == 'c')    
	A.PosY = (-PosY+windows_data.ViewportHeight/2 - SizeY/2) +  windows_data.ViewportPosY ; 
	else 
	A.PosY = PosY +  windows_data.ViewportPosY;

    //������������ �� ����������
	if(CHorizontal == 'R' || CHorizontal == 'r')    
	A.PosX = -PosX+windows_data.ViewportWidth - SizeX  + windows_data.ViewportPosX; 
	else 
	if(CHorizontal == 'C' || CHorizontal == 'c')
	A.PosX = -PosX+windows_data.ViewportWidth/2 - SizeX/2 +  windows_data.ViewportPosX;  
	else 
	A.PosX = PosX +  windows_data.ViewportPosX;
	return A;
}



public:
	





	windows_info windows_data;        //����� � ��� ������� �������� ��� ��� ���� � ������ �������
	std::vector<OBGECT>mObgects;       //�������� ����� � ��� ���������� ������
	OBGECT BT_K_TEMP;                 //�������� ����� ��� ������������ � ���� �������� �� ���� � ������ ������
	bool kyrsor_na_cnopci;            //������ �� ���� �� ������ �������
	std::vector<Grup>Grups_;          //������ ����
	Grup  BT_G_TEMP;   


//�������� ���
int Y_CORD;
int X_CORD;


//bmp
/* ������ ��������� BMP-����� */ 
 
#define BMP_SIZE_FILEHEADER 14  
 
/* ������ ��������������� ��������� BMP-����� */ 
#define BMP_SIZE_INFOHEADER 40   
 
#define BMP_COLOR_BITS_24 24  
 
/* ��������������� ������� */ 
/* <<<<<<<<<<<<<<<<<<<<<<< */ 
 
static unsigned int uInt16Number(unsigned char buf[2]) 
{ 
  return (buf[1] << 8) | buf[0]; 
} 
 
static unsigned int uInt32Number(unsigned char buf[4]) 
{ 
  unsigned numb = buf[3]; 
  numb = (numb << 8) | buf[2]; 
  numb = (numb << 8) | buf[1]; 
  numb = (numb << 8) | buf[0];
  return numb; 
} 
 
int ReadFileHeader(FILE* f, int* bitmap_pos)  
{ 
  unsigned char header[BMP_SIZE_FILEHEADER]; 
  int numb = 0;   
  int offset = 0; 
 
  if (fseek(f, 0, SEEK_SET)) 
    return 0; 
  
  numb = fread(header, BMP_SIZE_FILEHEADER, 1, f); 
  if (numb != 1) 
    return 0; 
 
  if (header[0] != 'B' || header[1] != 'M')  
    return 0; 
   
  offset = uInt32Number(header + 10); 
   
  numb = fread(header, 4, 1, f); 
  if (numb != 1) 
    return 0; 
   
  if (uInt32Number(header) != 40) 
    return 0; 
  
  *bitmap_pos  = offset; 
  return 1; 
} 
  
/* <<<<<<<<<<<<<<<<<<<<<<< */ 

public:
	
	//����������� ����������� ������, �������� ��� �������� �� ��������������� Viewport �� �������� ������ ��������
	bool MODglViewport;
 

//������� ������ �� �� ������ ��� ������� ��������
int IdTheLastPush;
double Time;


//�������� ���� �� ��������� ��������� ����
int idTheLastPushWindow; //�� ����� ��� ���� ������� �����
int IdGrupsHoverHight;
int IdGrupsHoverMain; //�� ����� ��� ����� ����, ���������� ������������ ��� ���������� �����
//���������� ���������� ���� � ������ ���� �� �������� ������������� ����� �������
int TheLastXpsMAuse;
int TheLastYpsMAuse;
//������� ���� � ������ ����
int TheLastXPosWin;
int TheLastYPosWin;



//(2019.12 - point 20)
//������ ���� � ����
int FindIdObject(std::string ObjectName,int GrupID)
{
	if(GrupID<0 || GrupID >= Grups_.size()) return -1;


	//GrupID

	for(int i = 0 ; i < Grups_[GrupID].ID_Objects.size() ; i++)
	{
		
		if(mObgects[Grups_[GrupID].ID_Objects[i] ].Names == ObjectName)
		{
			return Grups_[GrupID].ID_Objects[i];
		}
		else
		{
			//std::cout<<"'"<<ObjectName<<"' != '"<<mObgects[Grups_[GrupID].ID_Objects[i] ].Names<<"' ("<<Grups_[GrupID].ID_Objects[i]<<")"<<std::endl;
		}
	}
	return -1;
}


//(2019.12 - point 20)
int FindIdObject(std::string ObjectName)
{
	for(int i = 0 ; i < mObgects.size() ; i++)
	{
		if(mObgects[i].Names == ObjectName)
		{
			return i;
		}
	}
	return -1;
}



//(2019.12 - point 20)
int FindIdGrup(std::string GrupName)
{
	for(int i = 0 ; i < Grups_.size() ; i++)
	{
		if(Grups_[i].Name == GrupName)
		{
			return i;
		}
	}
	return -1;
}


//(2019.12 - point 20) //��������� ���� � ���� ���� ���������� (������ ��������� �� ���� ������� ��������)
bool DuplicateGrup(int idGrup,std::string SubText,int &newGrup, bool CopyElements)
{
	//���� ����� �� ���� �� �� ����������� �������
	if(idGrup >= Grups_.size() || idGrup < 0)
	{
		return false;
	}


	//��������� ����� 
	Grup tGrup =  Grups_[idGrup];
	//� � ���� �������� ��������� �� ���� �������
	tGrup.ID_Objects.clear();
	//������ �� ���� ���������
	tGrup.Name = SubText + tGrup.Name;

	//��������� �� ������� �����
	if(CopyElements)
	for(int i = 0; i < Grups_[idGrup].ID_Objects.size() ; i++)
	{
		{
		//��������� � ����� �����
		OBGECT tObjects = mObgects[  Grups_[idGrup].ID_Objects[i]  ];
		//������ ��� �����
		tObjects.Names = SubText + tObjects.Names;
		//�������� � ����� ����

		//tObjects.Comanda.clear();
		mObgects.push_back(tObjects);

		//BT_NEW_Knopka(BT_K_TEMP,BT_K_TEMP.Names,BT_K_TEMP.Temp.URL); BT_K_TEMP.Comanda.clear(); 



		//�������� ������������� ������������ ������ � ���� �����
		tGrup.ID_Objects.push_back(mObgects.size()-1);
		}
	}


	Grups_.push_back(tGrup);

	//������� �� ���� �����
	newGrup = Grups_.size() - 1;

	return true;
}


//void Clear

DevChBTG()
{
	ReadFile.clear();
	ErrorLog.clear();
	IdGrupsHoverHight = -1;
	IdGrupsHoverMain = -1;
	idTheLastPushWindow = -1;

	Time = 0;
	IdTheLastPush = -1;

	BT_K_TEMP.Checked = false;
	BT_K_TEMP.RotationMode = 'H';

	BT_K_TEMP.PosTextCursor = 0;


	PressKnopkaONE = false;

	Enable(MODglViewport);
	windows_data.ViewportPosX = 0;
	windows_data.ViewportPosY = 0;
	//�������� ������������� ������� �� ������ ������������
	Disable(textureLoader.ISusTextureLoader);
	//Disable(isVoidDrawPlane);
	Disable(isVoidDrawPlane);
	Disable(isVoidGlobalDrawPlane);
	
	//������� ��� ����������� ������� ��� ������ ��������� �������� ���� ������� ����������� ������������
	bool (*usTextureLoader)(std::string url, int &width, int &height, GLuint &TxID);

	string vertexS = "";

	//StandartShader.ShaderS();



	textEnable = 1;
	OBGECT BT_K_TEMP = Knopka_IN();                 //�������� ����� ��� ������������ � ���� �������� �� ���� � ������ ������
	Grup  BT_G_TEMP = Grup_IN();
	BT_MAUSE_KLIK_KNOPKA = 0;                       //���� ������ �� glut �� ��� ������ ���� �� ���������
	windows_data.Maus_Data_ .PressState = 0;
	windows_data.Maus_Data_ .MausBT = -1;

}


//������� ������ � ����������
//������� � ��� ������� ���������� aspi ��������� ������
void VoidSetKeyEvent(int key, int action, int mode)
{
	//r 262
	//l 263

	//std::cout<<key<<std::endl;

	if(IdTheLastPush>=0)
	{
		if(mObgects[IdTheLastPush].Type == "textBox")
		{

		//BackSpake
		if(mObgects[IdTheLastPush].Text.size()>0 && key == 259 && (action == 1 ||  action == 2))
		{
			if(mObgects[IdTheLastPush].PosTextCursor>=0)
			{
				mObgects[IdTheLastPush].PosTextCursor--;

				if(mObgects[IdTheLastPush].PosTextCursor>=0)
				mObgects[IdTheLastPush].Text.erase(mObgects[IdTheLastPush].Text.begin()+mObgects[IdTheLastPush].PosTextCursor);
			}

			if(mObgects[IdTheLastPush].PosTextCursor<0) mObgects[IdTheLastPush].PosTextCursor = 0;
			//std::cout<<mObgects[IdTheLastPush].PosTextCursor<<std::endl;
			//mObgects[IdTheLastPush].PosTextCursor--;
		}

		//Delete
		if(mObgects[IdTheLastPush].Text.size()>0 && key == 261 && (action == 1 ||  action == 2))
		{
			if(mObgects[IdTheLastPush].PosTextCursor<= mObgects[IdTheLastPush].Text.size()-1)

			mObgects[IdTheLastPush].Text.erase(mObgects[IdTheLastPush].Text.begin()+mObgects[IdTheLastPush].PosTextCursor);

			//std::cout<<mObgects[IdTheLastPush].PosTextCursor<<std::endl;
			//mObgects[IdTheLastPush].PosTextCursor--;
		}

		if(key == 262 && (action == 1 ||  action == 2)) if(mObgects[IdTheLastPush].PosTextCursor+1 <= mObgects[IdTheLastPush].Text.size()) mObgects[IdTheLastPush].PosTextCursor++;
		if(key == 263 && (action == 1 ||  action == 2)) if(mObgects[IdTheLastPush].PosTextCursor-1 >= 0) mObgects[IdTheLastPush].PosTextCursor--;
		}
	}
}

//������� � ��� ������� ���������� ������ ��������� ������
void VoidSetKeyEventText(unsigned char ch)
{
	if(IdTheLastPush>0)
	{
		if(mObgects[IdTheLastPush].Type == "textBox")
		//mObgects[IdTheLastPush].Text+=ch;
		mObgects[IdTheLastPush].Text.insert(mObgects[IdTheLastPush].PosTextCursor,1,ch);
		mObgects[IdTheLastPush].PosTextCursor++;
	}
}



//2019 �������� ������� ������ � ����������� ������������
 void GetPosBT(int id,int &x,int &y)
 {

	 GetPos(x,y,mObgects[id].PosX,mObgects[id].PosY,mObgects[id].SizeX,mObgects[id].SizeY,mObgects[id].CWertical,mObgects[id].CHorizontal);
	 return;

 }


  void GetPosGrup(int id,int &x,int &y)
 {
	 GetPos(x,y,Grups_[id].PosX,Grups_[id].PosY,Grups_[id].sizeX,Grups_[id].sizeY,Grups_[id].CWertical,Grups_[id].CHorizontal);
	

	 return;
 }




 void GetPos(int &x,int &y,float PosX,float PosY,float SizeX,float SizeY,char CWertical,char CHorizontal)
 {



	

	 //������������ �� ��������
	if(CWertical == 'W' || CWertical == 'w')  
	y = -PosY+windows_data.ViewportHeight - SizeY ; 
	else 
	if(CWertical == 'C' || CWertical == 'c')    
	y = -PosY+windows_data.ViewportHeight/2 - SizeY/2 ; 
	else 
	y = PosY;

    //������������ �� ����������
	if(CHorizontal == 'R' || CHorizontal == 'r')    
	x = -PosX+windows_data.ViewportWidth - SizeX ; 
	else 
	if(CHorizontal == 'C' || CHorizontal == 'c')
	x = -PosX+windows_data.ViewportWidth/2 - SizeX/2 ;  
	else 
	x = PosX;
	
	y += windows_data.ViewportPosY;
	x += windows_data.ViewportPosX;

	 return;
 }





void BPrivate_Rozmis(int i)  //������� �������� ���� ������������ ���������
{
	GetPosBT(i,X_CORD1,Y_CORD1);
}

void FixWindow_Private_Size(int iBt,int IdG,int &x,int &y)  //������� �������� ���� ������������ ���������
{

 //int x,int y;


	float PosX = mObgects[iBt].PosX;
	float PosY = mObgects[iBt].PosY;
	float SizeX = mObgects[iBt].SizeX;
	float SizeY = mObgects[iBt].SizeY;
	char CWertical = mObgects[iBt].CWertical;
	char CHorizontal = mObgects[iBt].CHorizontal;

	int WindowHeight = Grups_[IdG].sizeY;
	int WindowWidth = Grups_[IdG].sizeX;
	int WindowPosX,WindowPosY;
	GetPosGrup(IdG,WindowPosX,WindowPosY);
	

	
	

	 //������������ �� ��������
	if(CWertical == 'W' || CWertical == 'w')  
	y = -PosY+WindowHeight - SizeY ; 
	else 
	if(CWertical == 'C' || CWertical == 'c')    
	y = -PosY+WindowHeight/2 - SizeY/2 ; 
	else 
	y = PosY;

    //������������ �� ����������
	if(CHorizontal == 'R' || CHorizontal == 'r')    
	x = -PosX+WindowWidth - SizeX ; 
	else 
	if(CHorizontal == 'C' || CHorizontal == 'c')
	x = -PosX+WindowWidth/2 - SizeX/2 ;  
	else 
	x = PosX;
	
	y += WindowPosY;
	x += WindowPosX;

	 return;
}




void  VSTAN_ZMIN_T_OBROB(bool Stan) //����� �� ������������ �� ������ ��������
{

	//MD_ ������������ �� ������ �����
		/*int i = 0;
		while(i<KNopka_.size())
		{
				KNopka_[i].Temp.Temp_obrob = Stan;
			i++;
		}*/

			int j = 0;
		while(j<Grups_.size()) //�������� �� ��� ������
		{
			if(Grups_[j].vizual == 1) //���� ����� ������ � �������
			{
							int i = 0;
							while(i<Grups_[j].ID_Objects.size()) //�������� ������� ��������������
								{
										mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob = Stan; //������� �� ������ ���������
                                        i++;
							    }
			}
			j++;
		}

}

int  ID_GRUP_NAME(std::string Name) //������� ������� �� ��������� ���� �� ������
{
	int i = 0;
	while(Grups_.size()>i)
	{
		if(Grups_[i].Name == Name)
		return i;
		i++;
	}
	return -1; //����� � ����� ������ �� ��������
}
bool IStheProcessReform;//����� ��� �������� �������� ������� ������ ���� ��� ������� �� ������ �������� ������������ ���� �����
void  MSG_BT(void (*func)(std::string Name,int idObject,int idGrup))   //�� ������ ������� ��������� � ���� � ������ ������� ���� ������� �������� ����� ��������� ������.
{
	IStheProcessReform = false;
	VSTAN_ZMIN_T_OBROB(0); //�� ������ �� �������� �� �����������

	    kyrsor_na_cnopci = 0;
	

		int j = 0;
		while(j<Grups_.size()) //�������� �� ��� ������
		{
			if(Grups_[j].vizual == 1 && Grups_[j].Enable == 1) //���� ����� ������ � �������
			{
							int i = 0;
							while(i<Grups_[j].ID_Objects.size()) //�������� ������� ��������������
								{
									//if(mObgects.size() > Grups_[j].ID_Objects[i] && Grups_[j].ID_Objects[i]>=0)

									if(mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob == 0) //���� ������ �� �����������
									{//**�������� ������

										mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob = 1; //������� �� ������ ���������

									if(mObgects[Grups_[j].ID_Objects[i]].Temp.Klik == 1)
									{
										
										//�������� � ������������� ������� ��� � ��
										func(mObgects[Grups_[j].ID_Objects[i]].Names,Grups_[j].ID_Objects[i] ,j );
										if(IStheProcessReform == true) return; //�������� �������� ������� ���� ����������� ���� ����� ��� ��������
										mObgects[Grups_[j].ID_Objects[i]].PosTextCursor = mObgects[Grups_[j].ID_Objects[i]].Text.size();

										//if(Grups_.size() == 0 && mObgects.size() == 0) return;

										//if(Grups_[j].ID_Objects.size() < j) return;

										IdTheLastPush = Grups_[j].ID_Objects[i]; //��������� ������� ��������� ������


										mObgects[Grups_[j].ID_Objects[i]].Temp.Klik = 0;

										//���� ��������� �� �������� ����� ��� ������� � ����� ����� ���������� � ��������� �� ����� ������� ���� �� �� ����
										if(mObgects[Grups_[j].ID_Objects[i]].Type == "radioBox" && mObgects[Grups_[j].ID_Objects[i]].Checked == false)
											for(int i1 = 0; i1 < mObgects.size();i1++)
											{
												if(i1 != Grups_[j].ID_Objects[i])
												if(mObgects[i1].RadioGrup ==  mObgects[Grups_[j].ID_Objects[i]].RadioGrup)
												{
													mObgects[i1].Checked = false;
												}
											}
											

										mObgects[Grups_[j].ID_Objects[i]].Checked = !mObgects[Grups_[j].ID_Objects[i]].Checked;



										
				//===========================������� �������� ������ ������
										int i_t = 0;
										while(i_t < mObgects[Grups_[j].ID_Objects[i]].Comanda.size())
										{
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnable")  ////���������� ����� = �������� �����
											{
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1);
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,1);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisable")   ////������������ ����� = �������� �����
											{
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,0);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOn") //������ �������� ������ �����
											{
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1);
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,1);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOff") //������ �� �������� ������ �����
											{
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,0);
											}
											else

											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOnInsert") //GrupVisualOnInsert ������� �������� �� �� ������ ����� (������ �� ������). ������ ������� ��� (int �������, *(string  �� int)).
											{
											GrupVisualInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOffInsert") //GrupVisualOnInsert ������� �������� �� �� ������ ����� (������ �� ������). ������ ������� ��� (int �������, *(string  �� int)).
											{
										    GrupVisualInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											}
											else
												
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableInsert")
											{
											GrupEnableInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1); //� ������ ��������� �� �� ������ ����� (������ �� ������). ������ ������� ��� (int �������, *(string  �� int)).
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableInsert")  //� ������ ����������� �� �� ������ ����� (������ �� ������). ������ ������� ��� (int �������, *(string  �� int)).
											{
											GrupEnableInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableAll") //���������� �� �����
											GrupEnableAll(1);
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableAll") //������������ �� �����
											GrupEnableAll(0);
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOnAll") //������� �������� ��
											GrupVisualAll(1);
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOffAll") //������� �� �������� ��
											GrupVisualAll(0);



											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableInsertRevers" || mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableInsertRevers") // ������ �������� ��������� �� �������� ���� �� ���������. ). ������ ������� ��� (int �������, *(string  �� int)).
											GrupEnableInsertRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //�������� = �������� ����� �� ����
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualInsertRevers")
											GrupVisualInsertRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //�������� = �������� ����� �� ����
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableRevers" || mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableRevers")
											{
											GrupEnableRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //�������� = �������� ����� �� ����
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualRevers")
											{
											GrupVisualRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //�������� = �������� ����� �� ����
											}








											i_t++;
										}

										
				//===========================================================



									}
			
											//-----------
											if(mObgects[Grups_[j].ID_Objects[i]].Temp.activ == 0) //���� ������ �� ������� ��� ��� ������ ����������
											{
												mObgects[Grups_[j].ID_Objects[i]].Temp.Clic = 0;
												mObgects[Grups_[j].ID_Objects[i]].Temp.Clic_Temp = 0;
											}
												else
											kyrsor_na_cnopci = 1; //���� ��� ���� ������ �������
											//-----------
									}//**
			i++;
		}
			}
			j++;
		}


}


 



//������� �������� � ���'��� ���� ������
int  BT_NEW_Knopka(OBGECT A,std::string Name)
{
	A.ClickPress = false;
mObgects.push_back(A);
mObgects[mObgects.size()-1].Names = Name;
return mObgects.size()-1;
}

//������� �������� � ���'��� ���� ������ � ������������ ������� ��������
int  BT_NEW_Knopka(OBGECT A,std::string Name, std::string Url_TGA_INEG)
{
A.ClickPress = false;
A.Temp.URL = Url_TGA_INEG;
mObgects.push_back(A);
textureLoader.Knopka_LoadTexture(mObgects[mObgects.size()-1].ImageKnopki,    korin_dir +     Url_TGA_INEG.c_str());

textureLoader.Knopka_LoadTexture(mObgects[mObgects.size()-1].Image2,    korin_dir +     A.Temp.URL2.c_str());

mObgects[mObgects.size()-1].Names = Name;
return mObgects.size()-1;
}

int  ID_names(std::string a)
{
	int i = 0;
	while(i<mObgects.size())
	{
		if(mObgects[i].Names == a)
		return i;
		i++;
	}
	return -1;
}

void  PanelDisableVizual(int *a,int size) //����� �� ������� ��������
{
	int i = 0;
	while(i<size)
	{
	PAneli_Visual(a[i],0);
	i++;
	}
}

void  PanelDisableVizualR(int *a,int size) 
{//����� �� �� ������� ��������
	int j=0;

	while(j<mObgects.size())
	{
	bool OK = 1;

	int i = 0; while(i<size) { if(j == a[i]) {OK = 0; break;} i++; }


	if(OK) PAneli_Visual(j,0);
	j++;
	}
}

void  PAneli_Visual(int Panalka,bool Visual)
{
	int i = 0;
	while(i < mObgects.size())
	{
		if(mObgects[i].Panel == Panalka)
		   mObgects[i].Vizual = Visual;
		i++;
	}
}

private:
void  Private_Rozmis(int i)  //������� �������� ���� ������������ ���������
{
	GetPosBT(i,X_CORD,Y_CORD);
}




public:

	
//��������� ������� ���������
bool isVoidGlobalDrawPlane;

void (*VoidGlobalDrawPlane)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid);
void setVoidGlobalDrawPlane(void (*VoidGlobalDrawPlane)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid))
{
	this->VoidGlobalDrawPlane = VoidGlobalDrawPlane;
	Enable(isVoidGlobalDrawPlane);
}

//���� ��� ������ ������  ����� ������ ���� �� ��������
bool PressKnopkaONE;

/*

void  PRIVATE_DRAW_MOD(int i, float x,float y,float width, float heigth) //���� ��������� �������� ������, ��� �������� ��������� ����� ����� �������� �������
{
	//2019 mod
	// glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,KNopka_[i].ImageKnopki);

	if(isVoidDrawPlane == false) //���� 
	DrawPlane(1,1,0,0,KNopka_[i].Color.R,KNopka_[i].Color.G,KNopka_[i].Color.B,KNopka_[i].Color.A,KNopka_[i].ImageKnopki,KNopka_[i].Tip,KNopka_[i].Temp.activ,KNopka_[i].Enabled,KNopka_[i].Vizual,i);
	else
	VoidDrawPlane(1,1,0,0,KNopka_[i].Color.R,KNopka_[i].Color.G,KNopka_[i].Color.B,KNopka_[i].Color.A,KNopka_[i].ImageKnopki,KNopka_[i].Tip,KNopka_[i].Temp.activ,KNopka_[i].Enabled,KNopka_[i].Vizual,i);
	
	return;
}*/

void  PRIVATE_DRAW(int i, float x,float y,float width, float heigth) //���� ��������� �������� ������, ��� �������� ��������� ����� ����� �������� �������
{
	//2019 mod
	// glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,mObgects[i].ImageKnopki);

	/*	float cofX = 1.0f / ((float)windows_data.ViewportWidth  ) * 2;
				float cofY = 1.0f / (float)windows_data.WindowsHeight * 2;

				//float cofX = 1.0f / ((float)windows_data.WindowsWidth  ) * 2;
				//float cofY = 1.0f / (float)windows_data.WindowsHeight * 2;

				float RX =( (float)windows_data.WindowsWidth - (float)windows_data.ViewportWidth)/2;
				float RY =( (float)windows_data.WindowsHeight - (float)windows_data.ViewportHeight)/2;
			

				glBindTexture(GL_TEXTURE_2D,KNopka_[i].ImageKnopki);
				DrawPlane(((float)KNopka_[i].SizeX*cofX),((float)KNopka_[i].SizeY*cofY),((X_CORD-RX)*cofX-1)+(((float)KNopka_[i].SizeX*cofX))/2,((Y_CORD-RY)*cofY-1)+(((float)KNopka_[i].SizeY*cofY))/2,1,1,0,0);
				*/
				//				
	if(isVoidDrawPlane == false) //���� 
	DrawPlane(1,1,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	else
	VoidDrawPlane(1,1,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	
	return;
}




void  PRIVATE_DRAW(int i) //���� ��������� �������� ������, ��� �������� ��������� ����� ����� �������� �������
{
	//2019 mod
	// glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,mObgects[i].ImageKnopki);

	if(isVoidDrawPlane == false) //���� 
	DrawPlane(2,2,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	else
	VoidDrawPlane(2,2,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	
	return;
}


//void  Draw() 
//{
void  Draw(void (*func)(std::string Name,int idObject,int idGrup)) //����� �� ������ �� ����������� � ������� ������ � ����� ��������
{
	Draw();
	MSG_BT(func);
    
}


//�������� ����
void USColor(PixelRGBA &Color)
{
	glColor4ub(Color.R,Color.G,Color.B,Color.A);
}



//2019 ��������� �� ���� ������ � �������
/*bool ISmauseCvadrat(int X,int Y,int SizeX,int SizeY)
{
	int mY  = windows_data.WindowsHeight-windows_data.Maus_Data_.MausY_W;
	int mX =  windows_data.Maus_Data_.MausX_W;

	//std::cout<<mY;
	//std::cout<<Y<<"\n-----\n";

	if(mX>X && mX<X+SizeX    &&    mY + SizeY > Y  )
	return true;
		else
	return false;
}*/

//###2019
/*
void DrawGrup(int id)
{
	//Grups_[id];
	if(Grups_[id].type == "Window")
	{
			//���������� ����������� ������ 
				float cofX = 2.0f / (float)windows_data.ViewportWidth ;
				float cofY = 2.0f / (float)windows_data.ViewportHeight ;
				float SizeX , SizeY ,PosX ,PosY;
				{
				//������ � ������ ���������� ��������
				 SizeX = ((float)Grups_[id].sizeX*cofX);
				 SizeY = ((float)Grups_[id].sizeY*cofY);
				
				 int pX,pY;
				 GetPosGrup(id,pX,pY);
				// std::cout<<"===========\n";
				// std::cout<<pX<<'\n'<<pY<<'\n';
				 PosX = (((float)pX -(float)windows_data.ViewportPosX + (float)Grups_[id].sizeX/2) * cofX)-1;
				 PosY = (((float)pY -(float)windows_data.ViewportPosY + (float)Grups_[id].sizeY/2) * cofY)-1;

				 //����� ҳ�� ����========================================================Window===========================================
				 USColor(Grups_[id].BackgroundColor);
				 if(Grups_[id].bacgroundImageURL == "" || Grups_[id].bacgroundImageURL == "NUL" || Grups_[id].bacgroundImageURL == "null")
				 glDisable(GL_TEXTURE_2D);
				 else
				 glBindTexture(GL_TEXTURE_2D,Grups_[id].backgroundImage);
				 DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				 glEnable(GL_TEXTURE_2D);

				 USColor(Grups_[id].HeaderColor);
				 
				 //����������� ������� ������
			
				 PosY += SizeY/2;
				 SizeY = (float)Grups_[id].heightHeader *cofY;

				 PosY+=SizeY/2;
				 //�������� ������
				   if(Grups_[id].bacgroundHeaderImageURL == "" || Grups_[id].bacgroundHeaderImageURL == "NUL" || Grups_[id].bacgroundHeaderImageURL == "null")
					glDisable(GL_TEXTURE_2D);
				   else
				   glBindTexture(GL_TEXTURE_2D,Grups_[id].backgroundHeaderImage);

	
					GetPosGrup(id,pX,pY);



				  // if(ISmauseCvadrat(pX,pY,Grups_[id].sizeX,Grups_[id].PosY))

					{
					
						int mY  = windows_data.WindowsHeight-windows_data.Maus_Data_.MausY_W;
						int mX =  windows_data.Maus_Data_.MausX_W;

						//�������� �� ���� ��� ����� �������� ��������
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY && mY<pY+Grups_[id].sizeY + Grups_[id].heightHeader    )
						{
							if(IdGrupsHoverMain == -1)
							{
								IdGrupsHoverMain = id;
								glColor4f(255,255,0,255);
							}
						}



						if(IdGrupsHoverMain == id)
						//�������� �� ������ ���� ��� ������� ���� 
						if(IdGrupsHoverHight == -1 ) //��� ���� �� ���� ���� �� ���������
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY+Grups_[id].sizeY && mY<pY+Grups_[id].sizeY+Grups_[id].heightHeader  
							&& windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA  //� ������ �������
							&& windows_data.Maus_Data_.PressState == true)
						{
						 //std::cout<<"MouseCLock\n";
							//�� ������� ���� ���������� ����� � ������ ����
						 TheLastXpsMAuse = windows_data.Maus_Data_.MausX_W;
						 TheLastYpsMAuse = windows_data.Maus_Data_.MausY_W;

						 TheLastXPosWin = Grups_[id].PosX;
						 TheLastYPosWin = Grups_[id].PosY;

						 IdGrupsHoverHight = id;
						}
					}

					if(IdGrupsHoverHight == id)
					{
						//���������� ������� ���� ����� � ����� �������� ���������

						//=======X======
						if(Grups_[id].CHorizontal == 'L' || Grups_[id].CHorizontal == 'l')
						Grups_[id].PosX = TheLastXPosWin     -  (TheLastXpsMAuse - windows_data.Maus_Data_.MausX_W);
						else
						if(Grups_[id].CHorizontal == 'R' || Grups_[id].CHorizontal == 'r'    ||  Grups_[id].CHorizontal == 'C' || Grups_[id].CHorizontal == 'c')
						Grups_[id].PosX = TheLastXPosWin     +  (TheLastXpsMAuse - windows_data.Maus_Data_.MausX_W);

						//=======Y======
						if(Grups_[id].CWertical == 'W' || Grups_[id].CWertical == 'w' ||  Grups_[id].CWertical == 'C' || Grups_[id].CWertical == 'c')
						Grups_[id].PosY = TheLastYPosWin     -  (TheLastYpsMAuse - windows_data.Maus_Data_.MausY_W);
						else
						if(Grups_[id].CWertical == 'N' || Grups_[id].CWertical == 'n'    )
						Grups_[id].PosY = TheLastYPosWin     +  (TheLastYpsMAuse - windows_data.Maus_Data_.MausY_W);
						



					//	Grups_[id].PosY = TheLastYPosWin +  TheLastYpsMAuse - windows_data.Maus_Data_.MausY_W;
						glColor4f(255,0,0,255);

					}
					  
				  DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				  glEnable(GL_TEXTURE_2D);
			

				  


				  //IdGrupsClick
			}
			

		//DrawPlane(0.5f,0.5f,0,30.0f*cofY,1,1,0,0,'h');
	}

}*/



//###2019
void DrawGrup(int id) //ҳ���� �����������
{

	if(Grups_[id].type == "Window" || Grups_[id].type  == "window")
	{
			//���������� ����������� ������ 
				float cofX = 2.0f / (float)windows_data.ViewportWidth ;
				float cofY = 2.0f / (float)windows_data.ViewportHeight ;
				float SizeX , SizeY ,PosX ,PosY;
				
				//������ � ������ ���������� ��������
				 SizeX = ((float)Grups_[id].sizeX*cofX);
				 SizeY = ((float)Grups_[id].sizeY*cofY);
				
				 int pX,pY;
				 GetPosGrup(id,pX,pY);


				 PosX = (((float)pX -(float)windows_data.ViewportPosX + (float)Grups_[id].sizeX/2) * cofX)-1;
				 PosY = (((float)pY -(float)windows_data.ViewportPosY + (float)Grups_[id].sizeY/2) * cofY)-1;

				 //����� ҳ�� ����========================================================Window===========================================
				 USColor(Grups_[id].BackgroundColor);
				 if(Grups_[id].bacgroundImageURL == "" || Grups_[id].bacgroundImageURL == "NUL" || Grups_[id].bacgroundImageURL == "null")
					 glDisable(GL_TEXTURE_2D);
				 else
					 glBindTexture(GL_TEXTURE_2D,Grups_[id].backgroundImage);

				 DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,'H');
				 glEnable(GL_TEXTURE_2D);


				 if(Grups_[id].ISheader)
				 {
					 USColor(Grups_[id].HeaderColor);
				 
					 //����������� ������� ������
					 PosY += SizeY/2;
					 SizeY = (float)Grups_[id].heightHeader *cofY;
					 PosY+=SizeY/2;

					 //�������� ������
					 if(Grups_[id].bacgroundHeaderImageURL == "" || Grups_[id].bacgroundHeaderImageURL == "NUL" || Grups_[id].bacgroundHeaderImageURL == "null")
						 glDisable(GL_TEXTURE_2D);
					  else
						 glBindTexture(GL_TEXTURE_2D,Grups_[id].backgroundHeaderImage);
  
					  DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,'H');
					 
					  glEnable(GL_TEXTURE_2D);

					  pX-=windows_data.ViewportPosX;
					  pY-=windows_data.ViewportPosY;


					  //DrawTitle
					  if(Grups_[id].IStitle)
					  {
						  USColor(Grups_[id].TextColor);
						  FontSystems.print(Grups_[id].title	,pX + (Grups_[id].heightHeader/2)	,pY + Grups_[id].sizeY	,FontSystems.DefaultFonts,Grups_[id].heightHeader - (Grups_[id].heightHeader/7));
					  }
				 }


	}

}



//###2019
//��� ����� �������� ����� ��䳿 ������� ������� � ������������
void EventGrup(int id)
{

	if(Grups_[id].type == "Window" || Grups_[id].type  == "window")
	{
		
				
				 int pX,pY;
				GetPosGrup(id,pX,pY);


					{
					
						int mY  = windows_data.WindowsHeight-windows_data.Maus_Data_.MausY_W;
						int mX =  windows_data.Maus_Data_.MausX_W;

						//�������� �� ���� ��� ����� �������� ��������
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY && mY<pY+Grups_[id].sizeY + Grups_[id].heightHeader    )
						{
							if(IdGrupsHoverMain == -1)
							{
								IdGrupsHoverMain = id;
							}
						}



						if(IdGrupsHoverMain == id)
						//�������� �� ������ ���� ��� ������� ���� 
						if(IdGrupsHoverHight == -1 /*|| IdGrupsHoverHight == id*/) //��� ���� �� ���� ���� �� ���������
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY+Grups_[id].sizeY && mY<pY+Grups_[id].sizeY+Grups_[id].heightHeader  
							&& windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA  //� ������ �������
							&& windows_data.Maus_Data_.PressState == true)
						{
						 //std::cout<<"MouseCLock\n";
							//�� ������� ���� ���������� ����� � ������ ����
						 TheLastXpsMAuse = windows_data.Maus_Data_.MausX_W;
						 TheLastYpsMAuse = windows_data.Maus_Data_.MausY_W;

						 TheLastXPosWin = Grups_[id].PosX;
						 TheLastYPosWin = Grups_[id].PosY;

						 IdGrupsHoverHight = id;
						
						}
					}


					//std::cout<<IdGrupsHoverMain<<std::endl;

					//������� ���� �� ��� ����
					if(IdGrupsHoverMain == id && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA  && windows_data.Maus_Data_.PressState == true)
						 idTheLastPushWindow = id;

					if(IdGrupsHoverHight == id && Grups_[id].ISheader)
					{
						//���������� ������� ���� ����� � ����� �������� ���������

						//=======X======
						if(Grups_[id].CHorizontal == 'L' || Grups_[id].CHorizontal == 'l')
						Grups_[id].PosX = TheLastXPosWin     -  (TheLastXpsMAuse - windows_data.Maus_Data_.MausX_W);
						else
						if(Grups_[id].CHorizontal == 'R' || Grups_[id].CHorizontal == 'r'    ||  Grups_[id].CHorizontal == 'C' || Grups_[id].CHorizontal == 'c')
						Grups_[id].PosX = TheLastXPosWin     +  (TheLastXpsMAuse - windows_data.Maus_Data_.MausX_W);

						//=======Y======
						if(Grups_[id].CWertical == 'W' || Grups_[id].CWertical == 'w' ||  Grups_[id].CWertical == 'C' || Grups_[id].CWertical == 'c')
						Grups_[id].PosY = TheLastYPosWin     -  (TheLastYpsMAuse - windows_data.Maus_Data_.MausY_W);
						else
						if(Grups_[id].CWertical == 'N' || Grups_[id].CWertical == 'n'    )
						Grups_[id].PosY = TheLastYPosWin     +  (TheLastYpsMAuse - windows_data.Maus_Data_.MausY_W);
						

					}
			}

}


void Button_Events(int ID,int idGrup) //���������� ���� ������ �� ��
{
 	int i = ID;
	//Private_Rozmis(ID); //������� ��������� ��������� ������� ������ � ����� �������� ��� � ��
    mObgects[i].Temp.activ = 0; //������� ��������� 
	mObgects[i].trackBarKaretkaActiv = 0; //������� ��������� ��� �������



	if(IdGrupsHoverMain==-1 || IdGrupsHoverMain == idGrup) //ҳ���� ���� ����� �� ��������� ������ (����� ���� ����)
	{}else return;

	//����������� ��������� ������ ��������� � �������=====================================================================+
	if(mObgects[i].Vizual && mObgects[i].Enabled) //���������� ����� ���� ������ �� �������� � ������
	{	


	if(!kyrsor_na_cnopci) //��������� ���� �������� ����� ���� ������ �� �� ����������
	{
		//��������� � ����� �������� �� �������
		float EndX = mObgects[i].MaxValue - mObgects[i].MinValue;
		float pixVal = (mObgects[i].Value/EndX)*(mObgects[i].SizeX - mObgects[i].trackBarKaretkaSizeX);
		float KaretkaStartX = X_CORD+pixVal ;
		float KaretkaEndX = X_CORD +  mObgects[i].trackBarKaretkaSizeX+pixVal ; 
		float RizN = mObgects[i].trackBarKaretkaSizeY - mObgects[i].SizeY;
		float KaretkaStartY =  (windows_data.ViewportHeight - Y_CORD1) - RizN/2;
		float KaretkaEndY = (windows_data.ViewportHeight - Y_CORD1 + mObgects[i].SizeY) + RizN/2 ; 


		if(windows_data.Maus_Data_.MausX_W> KaretkaStartX && windows_data.Maus_Data_.MausX_W < KaretkaEndX && windows_data.Maus_Data_.MausY_W> KaretkaStartY  && windows_data.Maus_Data_.MausY_W < KaretkaEndY)
		{
			//if(IdGrupsHoverMain==-1 || IdGrupsHoverMain == idGrup) //ҳ���� ���� ����� �� ��������� ������ (����� ���� ����)
			{
				mObgects[i].trackBarKaretkaActiv = 1;               //����� �� �� ������ �������
				kyrsor_na_cnopci = 1;					 //����� �� �� ������ ����������, � �� ������� ����� ������ ����� �� ��������� ����� �� ��� ����  ����� ����� ��� ��� �� �������� ���� �������� ������ ���������    
			}
		}
		//ENd
	}

	if(!kyrsor_na_cnopci) //��������� ���� �������� ����� ���� ������ �� �� ���������� � �������
	{

	//���������� ������� ��� ���
		float RX =( (float)windows_data.WindowsWidth - (float)windows_data.ViewportWidth)/2;
		float RY =( (float)windows_data.WindowsHeight - (float)windows_data.ViewportHeight);

		int Y_CORD1= Y_CORD - RY + mObgects[i].SizeY;
		if(windows_data.Maus_Data_.MausX_W>X_CORD && windows_data.Maus_Data_.MausX_W < X_CORD +  mObgects[i].SizeX 	&& windows_data.Maus_Data_.MausY_W>   windows_data.ViewportHeight - Y_CORD1 && windows_data.Maus_Data_.MausY_W < windows_data.ViewportHeight - Y_CORD1 + mObgects[i].SizeY)
		{
			//if(IdGrupsHoverMain==-1 || IdGrupsHoverMain == idGrup) //ҳ���� ���� ����� �� ��������� ������ (����� ���� ����)
			{
				mObgects[i].Temp.activ = 1;               //����� �� �� ������ �������
				kyrsor_na_cnopci = true;					 //����� �� �� ������ ����������, � �� ������� ����� ������ ����� �� ��������� ����� �� ��� ����  ����� ����� ��� ��� �� �������� ���� �������� ������ ���������    
			}
		}

	
		

	}


	
	//���� �������
	if(!mObgects[i].Temp.Clic_Temp && mObgects[i].Temp.activ && windows_data.Maus_Data_.PressState == 0 && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA)
	{
		mObgects[i].Temp.Clic_Temp = 1;
		//cout<<i<<"clic\n";
	}



	
	//���� �������� ����� �������������� ������� �������
	if(mObgects[i].Avtomatic)
	{
		//���� �� ������ ������ ������ ����
		if(mObgects[i].ClickPress)
		{
			//ֳ ������ ���������� ������ ������� 
			mObgects[i].Temp.Clic_Temp = 0; 
			mObgects[i].Temp.Clic = 0;	
			mObgects[i].Temp.Klik = 1;
		}
	}
	//���� �������� ����� ������������ ��� ���� ������
	else
	//���� �������, ��� ����� � ������� ���� ����� ��� ��� ������
	if(mObgects[i].Temp.Clic_Temp && mObgects[i].Temp.activ && windows_data.Maus_Data_.PressState == 1 && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA)
	{	
		//ֳ ������ ���������� ������ ������� 
		mObgects[i].Temp.Clic_Temp = 0;
		mObgects[i].Temp.Clic = 0;
		mObgects[i].Temp.Klik = 1;	
	}
	
	}
	//����������� ��������� ������ ��������� � �������=====================================================================-

	//std::cout<<windows_data.Maus_Data_.PressState <<std::endl;

	if(!PressKnopkaONE && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA && windows_data.Maus_Data_.PressState == true  && (mObgects[i].Temp.activ || mObgects[i].trackBarKaretkaActiv)  )
	{
		mObgects[i].ClickPress = true;
		PressKnopkaONE = true;
	}

		if(windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA && windows_data.Maus_Data_.PressState == false)
		{
			mObgects[i].ClickPress = false; 
			PressKnopkaONE = false;
		} 



		//���������� ������� ������� �� ��������� ����
		//if(mObgects[i].Temp.Clic_Temp)
	if( mObgects[i].ClickPress  )
		{
			if( mObgects[i].RotationMode == 'H'  || mObgects[i].RotationMode == 'h' )
			{
			float StartPositionPixelsElements = X_CORD + mObgects[i].trackBarKaretkaSizeX/2 ;
			float EndPositionPixelsElements = X_CORD + (float)mObgects[i].SizeX - mObgects[i].trackBarKaretkaSizeX/2 ;
			float MauseValue = (float)windows_data.Maus_Data_.MausX_W - StartPositionPixelsElements;
			float ValOt0to1 = (MauseValue/(mObgects[i].SizeX - mObgects[i].trackBarKaretkaSizeX)) ;
			mObgects[i].Value =  (ValOt0to1 * (mObgects[i].MaxValue - mObgects[i].MinValue) ) + mObgects[i].MinValue;
			}
			else
				if( mObgects[i].RotationMode == 'W' || mObgects[i].RotationMode == 'w'  )
				{
					float StartPositionPixelsElements = Y_CORD + mObgects[i].trackBarKaretkaSizeY/2 ;
					float EndPositionPixelsElements = Y_CORD + (float)mObgects[i].SizeY - mObgects[i].trackBarKaretkaSizeY/2 ;
					float MauseValue = (float)windows_data.WindowsHeight - (float)windows_data.Maus_Data_.MausY_W - StartPositionPixelsElements;

					std::cout<<Y_CORD<<"-----"<< (float)windows_data.Maus_Data_.MausY_W<<std::endl;
					float ValOt0to1 = (MauseValue/(mObgects[i].SizeY - mObgects[i].trackBarKaretkaSizeY)) ;
					mObgects[i].Value =  (ValOt0to1 * (mObgects[i].MaxValue - mObgects[i].MinValue) ) + mObgects[i].MinValue;
				}

		}

	



			//�������� �� ������������� � ���������� �������� �������
			if(mObgects[i].Value > mObgects[i].MaxValue)
			mObgects[i].Value = mObgects[i].MaxValue;
			if(mObgects[i].Value < mObgects[i].MinValue)
			mObgects[i].Value = mObgects[i].MinValue;

	//===============================================================������� ��������� �� ����� � ������������===============+

}

void  Button_Draw(int ID) //���������� ���� ������ �� ��
{
 	int i = ID;
	//Private_Rozmis(ID); //������� ��������� ��������� ������� ������ � ����� �������� ��� � ��
   

	if(isVoidGlobalDrawPlane)
	{
		VoidGlobalDrawPlane(X_CORD,Y_CORD,mObgects[i].SizeX,mObgects[i].SizeY,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	}
	else
	{
		
		if(!mObgects[i].Temp.Perehvat) //���� ������ �� ���� �����������,����� ��
		{
				DrawStyleElements(i,X_CORD,Y_CORD,mObgects[i].SizeX,mObgects[i].SizeY);		
		}
	}





	mObgects[i].Temp.Perehvat = 0; //��������
}



void draw_grup_and_button(int idG)
{
	int j = idG;


	//���� ����� �� ������ �����������
	if(!Grups_[j].vizual) return;

	//ҳ�� ����
	DrawGrup(j); //�������� ���� ���� ����� ��������� �����

	

									//���� ������� ���� (������� ��䳿 ������������ ������ � ����������� �������� ��� ���� ��� ������� ������������� �� �� ��� ������ �� �� �������� ���� � �� ������� ���������� �����)
									if(Grups_[j].Enable == 1 )
									{
										for(int i = Grups_[j].ID_Objects.size()-1;i>=0;i--) //�������� �� ������ � ����� � ������������ ��������
										{
											if(mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob == 0) //���� ������ �� �����������
											{
												if(Grups_[j].type == "Window" || Grups_[j].type == "window")
													FixWindow_Private_Size(Grups_[j].ID_Objects[i],j, X_CORD , Y_CORD);
												else
													Private_Rozmis(Grups_[j].ID_Objects[i]);

												Button_Events(Grups_[j].ID_Objects[i],j); 
											}
										}
									}


									//���� ����������
									for(int i = 0;i<Grups_[j].ID_Objects.size();i++) //�������� ������� ��������������
									if(mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob == 0) //���� ������ �� �����������
									{//**�������� ������
										//mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob = 1; //������� �� ������ ��������� (������� ��������� ������ ���� ���� ���� ������������ � ���� ������)
										//Button_Events(Grups_[j].ID_Objects[i]); 
										//
									if(Grups_[j].type == "Window" || Grups_[j].type == "window")
										FixWindow_Private_Size(Grups_[j].ID_Objects[i],j, X_CORD , Y_CORD);
									else
										Private_Rozmis(Grups_[j].ID_Objects[i]);

										Button_Draw(Grups_[j].ID_Objects[i]); 
									}//**
									
	

}

void  Draw() //����� �� ������ �� ����������� � ������� ������
{
	//������� ��������� ���� ������ ������
	FontSystems.WindowsData.ViewportHeight = windows_data.ViewportHeight;
	FontSystems.WindowsData.ViewportWidth =  windows_data.ViewportWidth;
	FontSystems.WindowsData.ViewportPosX =   windows_data.ViewportPosX;
	FontSystems.WindowsData.ViewportPosY =   windows_data.ViewportPosY;
	FontSystems.WindowsData.WindowsHeight =  windows_data.WindowsHeight;
	FontSystems.WindowsData.WindowsWidth =   windows_data.WindowsHeight;

	if(windows_data.Maus_Data_.PressState == false && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA) //�������� �� ��������� ���� ����� ��� ���� �� ������ ���� �� ������
	{
		IdGrupsHoverHight = -1;
		IdGrupsHoverMain = -1;
	}


	//���� ������� ���� ��������

	//�������� ���������� ������� �����
	if(idTheLastPushWindow != -1)
		if(Grups_[idTheLastPushWindow].vizual == 1)
			EventGrup(idTheLastPushWindow);

	for(int j = Grups_.size()-1;j>=0;j--)
		{
			if(Grups_[j].vizual == 1) //���� ����� ������ � �������
			{
				if(idTheLastPushWindow != j)
				EventGrup(j);
			}
		}
	
 
	//������� ���������
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	kyrsor_na_cnopci = 0;
	VSTAN_ZMIN_T_OBROB(0); //Onul

		//int j = 0;
		//while(j<Grups_.size()) //�������� �� ��� ������
		
	
		for(int j = 0;j<Grups_.size();j++)
		{
			if(Grups_[j].vizual == 1) //���� ����� ������ � �������
			{
				if(j != idTheLastPushWindow)
				draw_grup_and_button(j); //�������� �����  � �� ����
			}
		}

		if(idTheLastPushWindow != -1)
			draw_grup_and_button(idTheLastPushWindow);



		//2019 comment
		//if(textEnable)  //���� ������� �� ����� �������
		//TextDraw();  	//��������� ������

}



bool  SaveToFile_BT(std::string URL_name) //������� ������ ��� �������� ������� � ����, ��� ����� ���������� ������������ ��� �����������
{
	std::ofstream Strim1(URL_name.c_str());
	if(!Strim1) return 0; //eror create file
	Strim1<<"Version 1.6\n";

	//======================������� �����======================//
	int i = 0;
	while(i < Grups_.size())
	{
		//
		Strim1<<"#  ID_GRUP "<<i<<'\n';
		Strim1<<"GrupNew_Begin\n";
		Strim1<<"GrupName "<<Grups_[i].Name<<'\n';
		Strim1<<"GrupEnable "<<Grups_[i].Enable<<'\n';
		Strim1<<"GrupVizual "<<Grups_[i].vizual<<'\n';
		Strim1<<"GrupID_Objects "<<Grups_[i].ID_Objects.size();
		int J = 0;
		while(J < Grups_[i].ID_Objects.size()) //������� ����������� � ��������������
		{
		Strim1<<' '<<Grups_[i].ID_Objects[J];
		J++;
		}
		Strim1<<'\n'<<"Grup_End"<<"\n\n";
		i++;
	}

	Strim1<<"\n";
	//======================������� ������======================//
	i = 0;
	while(i < mObgects.size())
	{
		//
		Strim1<<"#  ID_Objects "<<i<<'\n';
		Strim1<<"KnopkaNew_Begin\n";
		Strim1<<"Knopka_Names "<<mObgects[i].Names<<'\n';
		Strim1<<"Knopka_Text "<<mObgects[i].Text<<'\n';
		Strim1<<"Knopka_CHorizontal "<<mObgects[i].CHorizontal<<'\n';
		Strim1<<"Knopka_CWertical "<<mObgects[i].CWertical<<'\n';
		Strim1<<"Knopka_Avtomatic "<<mObgects[i].Avtomatic<<'\n';
		Strim1<<"Knopka_Color "<<mObgects[i].Color.R<<' '<<mObgects[i].Color.G<<' '<<mObgects[i].Color.B<<' '<<mObgects[i].Color.A<<'\n';
		Strim1<<"Knopka_Enabled "<<mObgects[i].Enabled<<'\n';
		Strim1<<"Knopka_Vizual "<<mObgects[i].Vizual<<'\n';
		Strim1<<"Knopka_Panel "<<mObgects[i].Panel<<'\n';
		Strim1<<"Knopka_PosX "<<mObgects[i].PosX<<'\n';
		Strim1<<"Knopka_PosY "<<mObgects[i].PosY<<'\n';
		Strim1<<"Knopka_SizeX "<<mObgects[i].SizeX<<'\n';
		Strim1<<"Knopka_SizeY "<<mObgects[i].SizeY<<'\n';
		//Strim1<<"Knopka_Tip "<<mObgects[i].Tip<<'\n';
		Strim1<<"Knopka_URL "<<mObgects[i].Temp.URL<<'\n';


		

		int LC = 0;
		while(LC < mObgects[i].Comanda.size())
		{
			//Beep(5000,500);
			//if(KNopka_[i].Comanda[LC].Comand_FUNC != "")
			{
			//==================================================
			Strim1<<"Comanda "<<mObgects[i].Comanda[LC].Comand_FUNC<<' '<<mObgects[i].Comanda[LC].ComandLine.size() + mObgects[i].Comanda[LC].ArgLine.size()<<' ';
			int LC_S = 0;
			while(LC_S < mObgects[i].Comanda[LC].ComandLine.size())
			{
				Strim1<<mObgects[i].Comanda[LC].ComandLine[LC_S]<<' ';
				LC_S++;
			}


			LC_S = 0;
			while(LC_S < mObgects[i].Comanda[LC].ArgLine.size())
			{
				Strim1<<mObgects[i].Comanda[LC].ArgLine[LC_S]<<' ';
				LC_S++;
			}
			//==================================================
			LC++;
			}
			Strim1<<'\n';
		}
		

		Strim1<<"Knopka_End"<<"\n\n";
		i++;
	}
	//=======================������� �������
	Strim1<<"Form_Init_End";



	Strim1.close();
	return 1;
}

bool chislo_znp(char A) //�������� �� ������ �� �����
{
		return (A == '1' || A == '2' || A == '3' || A == '4' || A == '5' || A == '6' || A == '7' || A == '8' || A == '9' || A == '0');
}

bool StringToBool(std::string Text)
{
  if(Text == "0")
	return 0;
  else
	return 1;
}
int StringToInt(std::string Text)
{
	int T__ = atoi(Text.c_str());
	//std::sprintf(T__,"%c",Text.c_str());
	return T__;
}
/*
float StringToFloat(std::string Text)
{
	return std::sprintf(Text.c_str(),"%f");;
}*/


//������ ���������� ��� �� ������ ���� ��������� ��� ����������� �� ������

//����� ��� �������
std::vector<std::string> ErrorLog;

std::vector<std::string> ReadFile;
bool ReadWordComands(std::string URL)
{
	std::ifstream Strim1(URL.c_str());
	if(!Strim1)
	{
		ErrorLog.push_back("Error open form: "); 
		ErrorLog[ErrorLog.size()-1]+=URL;
		return false; 
	}//test eror create file

	std::cout<<"OpenForm: "<<URL<<"\n";

	//Start read file while dont end
	while(!Strim1.eof())
	{
		//Temp char 
		char t;
		//Temp word comand
		std::string Comand = "";

		//Read word
		while(!Strim1.eof())
		{
			//Read temp char
			t = Strim1.get();

			//if end word then stop read
			if(t == '\n' || t == ' ' || Strim1.eof())
			break;

			//if coment line to thesh
			if(t == '#')
			{
				char M[500];
				Strim1.getline(M,500);
			}

			if(t == '"') //Read grup text
				while(!Strim1.eof())
				{
					t = Strim1.get();
					if(t == '\n' || t == '"')
					break;
					Comand.push_back(t);
				}
			else
					Comand.push_back(t);
			

		}

		//if(Comand.size() > 0)
		ReadFile.push_back(Comand); //������� ������� � ������ ��� �������� �������

		if(ReadFile.size()>=2)
		{
			if(ReadFile[ReadFile.size()-2] == "include")
			{
				std::string tempURL = ReadFile[ReadFile.size()-1];
				//delete arg include
				ReadFile.erase(ReadFile.begin()+(ReadFile.size()-1));
				//delete include
				ReadFile.erase(ReadFile.begin()+(ReadFile.size()-1));
				//recurse read lib
				ReadWordComands(tempURL);

			}
		}

		if(Comand == "Form_Init_End")
		{
			//delete end form comand
			ReadFile.erase(ReadFile.begin()+(ReadFile.size()-1));
			break; //read end	
		}
	}
	Strim1.close();
	return true;

}


void Clear()
{
	ReadFile.clear();
	ErrorLog.clear();
	mObgects.clear();
	Grups_.clear();

	BT_G_TEMP.ID_Objects.clear();
	BT_K_TEMP.Comanda.clear();

	IdTheLastPush = -1;
	IdGrupsHoverHight = -1;
	IdGrupsHoverMain = -1;
	idTheLastPushWindow = -1;
	Time = 0;
	BT_K_TEMP.Checked = false;
	BT_K_TEMP.RotationMode = 'H';
	BT_K_TEMP.PosTextCursor = 0;
	PressKnopkaONE = false;
	windows_data.ViewportPosX = 0;
	windows_data.ViewportPosY = 0;
	//�������� ������������� ������� �� ������ ������������
	//Disable(textureLoader.ISusTextureLoader);
	//Disable(isVoidDrawPlane);
	Disable(isVoidDrawPlane);
	Disable(isVoidGlobalDrawPlane);
	
	//������� ��� ����������� ������� ��� ������ ��������� �������� ���� ������� ����������� ������������
	//bool (*usTextureLoader)(std::string url, int &width, int &height, GLuint &TxID);

	string vertexS = "";


	textEnable = 1;
	OBGECT BT_K_TEMP = Knopka_IN();                 //�������� ����� ��� ������������ � ���� �������� �� ���� � ������ ������
	Grup  BT_G_TEMP = Grup_IN();
	BT_MAUSE_KLIK_KNOPKA = 0;                       //���� ������ �� glut �� ��� ������ ���� �� ���������
	windows_data.Maus_Data_ .PressState = 0;
	windows_data.Maus_Data_ .MausBT = -1;







}


bool  Open(std::string URL_name) //������� ����������� ����
{
	IStheProcessReform = true;
	Clear();
	DevChBTG();
	

	TlogBtToGrupsLog.clear();
	ReadFile.clear();
	

	ReadWordComands(URL_name);
	
	/*std::ofstream out("log.txt");
	for(int i = 0; i < ReadFile.size();i++)
	{
		out<<ReadFile[i]<<'\n';
	}
	out.close();

	system("Log.txt");*/
	//float Version;
	//Strim1<<"Version 1.2\n";

	//������� �����������
	int i = 0;
	while(i < ReadFile.size())
	{

		//============================================================================================
		//======================14.11.2017============================================================
		//============================================================================================


		
	//������
		if(ReadFile[i] == "Object_Begin")                                       {BT_K_TEMP = Knopka_IN();}
		else
			//2019
			if(ReadFile[i] == "Object_Copy")										  {i++;      for(int j = 0; j < mObgects.size(); j++) {if(mObgects[j].Names == ReadFile[i]){BT_K_TEMP = mObgects[j]; break;}}  } //��������� ���������� � ���� ������ �� ���� ���� ���� ��� �
		
			
			
		else
		if(ReadFile[i] == "Object_Checked")                                    {i++; BT_K_TEMP.Checked = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_RadioGrup")                                      {i++; BT_K_TEMP.RadioGrup = StringToInt(ReadFile[i]);}
		
			
			
			
			else
		if(ReadFile[i] == "Object_Name")                                          {i++;   BT_K_TEMP.Names = ReadFile[i];}
		else
		if(ReadFile[i] == "Object_Text")                                           {i++;   BT_K_TEMP.Text = ReadFile[i]; if(BT_K_TEMP.Text == "\"\"" || BT_K_TEMP.Text == "''") BT_K_TEMP.Text = "";}
		else
		if(ReadFile[i] == "Object_CHorizontal")                                    {i++; BT_K_TEMP.CHorizontal = ReadFile[i][0];}
		else
		if(ReadFile[i] == "Object_CWertical")                                      {i++; BT_K_TEMP.CWertical = ReadFile[i][0];}
		



		else
		if(ReadFile[i] == "Object_TextAlignX")                                    {i++; BT_K_TEMP.TextPositionAlignX = ReadFile[i][0];}
		else
		if(ReadFile[i] == "Object_TextAlignY")                                      {i++; BT_K_TEMP.TextPositionAlignY = ReadFile[i][0];}
		
		else
		if(ReadFile[i] == "Object_RotationMode")                /*RotationMode*/                    {i++;   BT_K_TEMP.RotationMode = ReadFile[i][0]; }
		
		 
		
		else
		if(ReadFile[i] == "Object_Avtomatic")                                      {i++;   BT_K_TEMP.Avtomatic = StringToBool(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_Color")                                          {{i++;   BT_K_TEMP.Color.R = StringToInt(ReadFile[i]); }   {i++;   BT_K_TEMP.Color.G = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.Color.B = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.Color.A = StringToInt(ReadFile[i]); }}
		else
		if(ReadFile[i] == "Object_Enabled") 									   {i++;   BT_K_TEMP.Enabled = StringToBool(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_Vizual")                                         {i++;   BT_K_TEMP.Vizual = StringToBool(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_Panel")                                          {i++;   BT_K_TEMP.Panel = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_PosX")                                           {i++;   BT_K_TEMP.PosX = StringToInt(ReadFile[i]); tempSSX = BT_K_TEMP.PosX;}
		else
		if(ReadFile[i] == "Object_PosY")                                           {i++;   BT_K_TEMP.PosY = StringToInt(ReadFile[i]); tempSSY = BT_K_TEMP.PosY;}
		else
		if(ReadFile[i] == "Object_SizeX")                                          {i++;   BT_K_TEMP.SizeX = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_SizeY")                                          {i++;   BT_K_TEMP.SizeY = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_Type")                                            {i++;   BT_K_TEMP.Type = ReadFile[i]; }
		else
		if(ReadFile[i] == "Object_URL")                                            {i++;   BT_K_TEMP.Temp.URL = ReadFile[i];}
		else
//#2019

		if(ReadFile[i] == "Object_URL2")                                            {i++;   BT_K_TEMP.Temp.URL2 = ReadFile[i];}
		else
		if(ReadFile[i] == "Object_Value")                                          {i++;   BT_K_TEMP.Value = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_MaxValue")                                          {i++;   BT_K_TEMP.MaxValue = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_MinValue")                                          {i++;   BT_K_TEMP.MinValue = StringToInt(ReadFile[i]);}

		else

		if(ReadFile[i] == "Object_trackBarKaretkaSizeX")                                          {i++;   BT_K_TEMP.trackBarKaretkaSizeX = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_trackBarKaretkaSizeY")                                          {i++;   BT_K_TEMP.trackBarKaretkaSizeY = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_trackBarKaretkaHoverSizeX")                                          {i++;   BT_K_TEMP.trackBarKaretkaHoverSizeX = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_trackBarKaretkaHoverSizeY")                                          {i++;   BT_K_TEMP.trackBarKaretkaHoverSizeY = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_trackBarKaretkaColor")                                          {{i++;   BT_K_TEMP.trackBarKaretkaColor.R = StringToInt(ReadFile[i]); }   {i++;   BT_K_TEMP.trackBarKaretkaColor.G = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.trackBarKaretkaColor.B = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.trackBarKaretkaColor.A = StringToInt(ReadFile[i]); }}
		
		else
		if(ReadFile[i] == "Object_trackBarKaretkaHoverColor")                                          {{i++;   BT_K_TEMP.trackBarKaretkaHoverColor.R = StringToInt(ReadFile[i]); }   {i++;   BT_K_TEMP.trackBarKaretkaHoverColor.G = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.trackBarKaretkaHoverColor.B = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.trackBarKaretkaHoverColor.A = StringToInt(ReadFile[i]); }}
		
		/*
		
			   float trackBarKaretkaSizeX;
			   float trackBarKaretkaSizeY;
			   float trackBarKaretkaHoverSizeX;
			   float trackBarKaretkaHoverSizeY;
			   PixelRGBA trackBarKaretkaColor;
			   PixelRGBA trackBarKaretkaHoverColor;
		
		*/



		//#2019
		else		
			if(ReadFile[i] == "Object_TextSize")                                            {i++;   BT_K_TEMP.TextSize = StringToInt(ReadFile[i]);}
		else
			if(ReadFile[i] == "Object_TextColor")                                          {{i++;   BT_K_TEMP.TextColor.R= StringToInt(ReadFile[i]); }   {i++;   BT_K_TEMP.TextColor.G = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.TextColor.B = StringToInt(ReadFile[i]); } {i++;  BT_K_TEMP.TextColor.A = StringToInt(ReadFile[i]); }}
		else
			if(ReadFile[i] == "Object_TextHorizontalAlign")                                    {i++; BT_K_TEMP.TextPositionAlignX= ReadFile[i][0];}
		else
			if(ReadFile[i] == "Object_TextVerticalAlign")                                    {i++; BT_K_TEMP.TextPositionAlignY = ReadFile[i][0];}
		else
		if(ReadFile[i] == "Object_HoverSizeX")                                            {i++;   BT_K_TEMP.HoverSizeX = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_HoverSizeY")                                            {i++;   BT_K_TEMP.HoverSizeY = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Object_HoverColor")                                          {{i++;   BT_K_TEMP.HoverColor.R= StringToInt(ReadFile[i]); }   {i++;   BT_K_TEMP.HoverColor.G = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.HoverColor.B = StringToInt(ReadFile[i]); } {i++;  BT_K_TEMP.HoverColor.A = StringToInt(ReadFile[i]); }}
		else
		if(ReadFile[i] == "Object_HoverTextColor")                                          {{i++;   BT_K_TEMP.HoverTextColor.R= StringToInt(ReadFile[i]); }   {i++;   BT_K_TEMP.HoverTextColor.G = StringToInt(ReadFile[i]); } {i++;   BT_K_TEMP.HoverTextColor.B = StringToInt(ReadFile[i]); } {i++;  BT_K_TEMP.HoverTextColor.A = StringToInt(ReadFile[i]); }}
		
		
		

		//2018 fix
		else
		if(ReadFile[i] == "Object_VidnosPosX")                                           {i++;  BT_K_TEMP.PosX = tempSSX; BT_K_TEMP.PosX += StringToInt(ReadFile[i]); tempSSX = BT_K_TEMP.PosX;}
		else
			if(ReadFile[i] == "Object_VidnosPosY")                                           {i++;   BT_K_TEMP.PosY = tempSSY; BT_K_TEMP.PosY += StringToInt(ReadFile[i]); tempSSY = BT_K_TEMP.PosY; }
		
			
			
			else
				if(ReadFile[i] == "Object_HoverFix") //��������� ��� ��� �������� ���������� ������ �� � ���������
				{
					i++;
					BT_K_TEMP.HoverColor = BT_K_TEMP.Color;
					BT_K_TEMP.HoverTextColor = BT_K_TEMP.TextColor;
					BT_K_TEMP.HoverSizeX = BT_K_TEMP.SizeX;
					BT_K_TEMP.HoverSizeY = BT_K_TEMP.SizeY;
					BT_K_TEMP.trackBarKaretkaHoverColor = BT_K_TEMP.trackBarKaretkaColor;
					BT_K_TEMP.trackBarKaretkaHoverSizeX = BT_K_TEMP.trackBarKaretkaSizeX;
					BT_K_TEMP.trackBarKaretkaHoverSizeY = BT_K_TEMP.trackBarKaretkaSizeY;
					//BT_K_TEMP.trackBarKaretkaHover = BT_K_TEMP.trackBarKaretkaSizeX;
				}
			
			
			
			//2018 new TlogBtToGrups
		



			else
			if(ReadFile[i] == "Object_grup" || ReadFile[i] == "Object_grup")                                           {i++; TlogBtToGrups T; T.NameGrup = ReadFile[i]; T.NameBT = BT_K_TEMP.Names; TlogBtToGrupsLog.push_back(T); }
		

		else
			if(ReadFile[i] == "Comanda")                                         
			{
				i++;                                                   //�������� ��������
				ComandVector ComandVectorTemp1;                        //��������� ����� ��� ����������
				ComandVectorTemp1.Comand_FUNC = ReadFile[i];           //�������� ����� �������
				i++;                                                   //�������� ��������

				int SizeMax = StringToInt(ReadFile[i]);                //ʳ������ �������
				int U = 0;
				while(U<SizeMax)                                       //����� �� ��� ���������
				{
					i++;                                               //�������� ��������
					if(chislo_znp(ReadFile[i][0]))                     //���� �������� �����
						ComandVectorTemp1.ArgLine.push_back(StringToInt(ReadFile[i]));          //�������� ������� ��������
					else                             
						ComandVectorTemp1.ComandLine.push_back(ReadFile[i]);                    //�������� �������� ��������*/
					U++;		
				}
				

				if(ComandVectorTemp1.ComandLine.size()+ComandVectorTemp1.ArgLine.size() >0)
				{	
					BT_K_TEMP.Comanda.push_back(ComandVectorTemp1);     //�������� �������
				}
		    }//������� ������
			

		else
		if(ReadFile[i] == "Object_End")                                            {i++;   BT_NEW_Knopka(BT_K_TEMP,BT_K_TEMP.Names,BT_K_TEMP.Temp.URL); BT_K_TEMP.Comanda.clear(); }
		else
		if(ReadFile[i] == "Form_Init_End")                                         break;
	//=================================================================================================
		i++;
	}
	
	i = 0;
	while(i < ReadFile.size())
	{	
        //�����
		if(ReadFile[i] == "GrupNew_Begin" || ReadFile[i] == "Grup_Begin")                    BT_G_TEMP = Grup_IN();													//��������� ������������ �����
		else
		if(ReadFile[i] == "GrupName" || ReadFile[i] == "Grup_Name")                         {i++; BT_G_TEMP.Name = ReadFile[i]; }										//��'� �����
		else
		if(ReadFile[i] == "GrupEnable" || ReadFile[i] == "Grup_Enable")						  {i++; BT_G_TEMP.Enable = StringToBool(ReadFile[i]);}						//���������
		else
		if(ReadFile[i] == "GrupVizual" || ReadFile[i] == "Grup_Vizual")                       {i++; BT_G_TEMP.vizual = StringToBool(ReadFile[i]);}						//��������
		
		//=======================================2019
		/////////////////////////////////////////////
		else
		if(ReadFile[i] == "Grup_Type" || ReadFile[i] == "Grup_type")                         {i++; BT_G_TEMP.type = ReadFile[i]; }	 //��� �����

		if(ReadFile[i] == "Grup_PosX")                                           {i++;   BT_G_TEMP.PosX = StringToInt(ReadFile[i]);} //������� ���� ����� ��������� ����� ��� �������
		else
		if(ReadFile[i] == "Grup_PosY")                                           {i++;   BT_G_TEMP.PosY = StringToInt(ReadFile[i]);}
		else
			if(ReadFile[i] == "Grup_ISheader")						  {i++; BT_G_TEMP.ISheader = StringToBool(ReadFile[i]);}						//�� ���������� �������� ������ ����
		else
			if(ReadFile[i] == "Grup_IStitle")                       {i++; BT_G_TEMP.IStitle = StringToBool(ReadFile[i]);}						//�� ���������� ����� ����
		else
			if(ReadFile[i] == "Grup_Title")                         {i++; BT_G_TEMP.title = ReadFile[i]; }	 //����� ����
			else
			if(ReadFile[i] == "Grup_IsCloseButton")						  {i++; BT_G_TEMP.CloseButton = StringToBool(ReadFile[i]);}	
			else
			if(ReadFile[i] == "Grup_IsHidentButton")						  {i++; BT_G_TEMP.HidentButton = StringToBool(ReadFile[i]);}	

		else
			if(ReadFile[i] == "Grup_HeaderColor")                                          {{i++;   BT_G_TEMP.HeaderColor.R = StringToInt(ReadFile[i]); }   {i++;   BT_G_TEMP.HeaderColor.G = StringToInt(ReadFile[i]); } {i++;   BT_G_TEMP.HeaderColor.B = StringToInt(ReadFile[i]); } {i++;   BT_G_TEMP.HeaderColor.A = StringToInt(ReadFile[i]); }}
			else
			if(ReadFile[i] == "Grup_BackgroundColor")                                          {{i++;   BT_G_TEMP.BackgroundColor.R = StringToInt(ReadFile[i]); }   {i++;   BT_G_TEMP.BackgroundColor.G = StringToInt(ReadFile[i]); } {i++;   BT_G_TEMP.BackgroundColor.B = StringToInt(ReadFile[i]); } {i++;   BT_G_TEMP.BackgroundColor.A = StringToInt(ReadFile[i]); }}
			else
			if(ReadFile[i] == "Grup_TextColor")                                          {{i++;   BT_G_TEMP.TextColor.R = StringToInt(ReadFile[i]); }   {i++;   BT_G_TEMP.TextColor.G = StringToInt(ReadFile[i]); } {i++;   BT_G_TEMP.TextColor.B = StringToInt(ReadFile[i]); } {i++;   BT_G_TEMP.TextColor.A = StringToInt(ReadFile[i]); }}
			else
			if(ReadFile[i] == "Grup_BacgroundImageURL")                                            {i++;      BT_G_TEMP.bacgroundImageURL = ReadFile[i];}
			else
				if(ReadFile[i] == "Grup_BacgroundHeaderImageURL")                                            {i++;      BT_G_TEMP.bacgroundHeaderImageURL = ReadFile[i];}
				else
	//backgroundImage
	//bacgroundImageURL
		if(ReadFile[i] == "Grup_heightHeader")                                           {i++;   BT_G_TEMP.heightHeader = StringToInt(ReadFile[i]);} 
		else
		if(ReadFile[i] == "Grup_SizeX")                                           {i++;   BT_G_TEMP.sizeX = StringToInt(ReadFile[i]);}
		else
		if(ReadFile[i] == "Grup_SizeY")                                           {i++;   BT_G_TEMP.sizeY = StringToInt(ReadFile[i]);}

		if(ReadFile[i] == "Grup_CHorizontal")                                    {i++; BT_G_TEMP.CHorizontal = ReadFile[i][0];}
		else
		if(ReadFile[i] == "Grup_CWertical")                                      {i++; BT_G_TEMP.CWertical = ReadFile[i][0];}

		else
		//2019
		if(ReadFile[i] == "Grup_Copy")										  {i++;      for(int j = 0; j < Grups_.size(); j++) {if(Grups_[j].Name == ReadFile[i]){  BT_G_TEMP = Grups_[j]; break;}}   BT_G_TEMP.ID_Objects.clear();  } //��������� ���������� � ���� ����� �� ���� ���� ���� ��� �
		
		/*
		/*
		  std::string type; //grup || window || panel
			   int PosX,PosY;
			   bool ISheader;
			   bool IStitle;
			   std::string title;
			   bool CloseButton;
			   bool HidentButton;
			   PixelRGBA HeaderColor;
			   PixelRGBA BackgroundColor;
			   GLuint backgroundImage;
			   std::string bacgroundImageURL;
			   int heightHeader;
			   int sizeX;
			   int sizeY;
		*/

		//=======================================2019end
		/////////////////////////////////////////////
		
		
		
		
		
		
		
		
		else
		if(ReadFile[i] == "GrupID_Objects")			          {																			//������� ������������� �������������� ������
																 i++;
			                                                     int j = 0, k = StringToInt(ReadFile[i]);
																 																 
																 while(k > j)
																 {
																	 i++;  
																	 
																	 if(chislo_znp(ReadFile[i][0]))    //�������� ������� �� ���� �� ����� ������� �� �����
																	 {
																	 BT_G_TEMP.ID_Objects.push_back(StringToInt(ReadFile[i]));
																	 }
																	 else
																	 {
																		 int ID_T =  ID_names(ReadFile[i]);
																	     if(ID_T >= 0)  BT_G_TEMP.ID_Objects.push_back(ID_T);
																	 }

																	 j++;
																 }
															   }
		else
		if(ReadFile[i] == "Grup_End")						   {
																	std::cout<<"\n<"<<BT_G_TEMP.Name<<">\n";
			//i++;
																	//������ ������ � ����� �� ��������� ��� ��������� ������ 2018
																	for(int g = 0;g < TlogBtToGrupsLog.size();g++)
																	{
																		if(TlogBtToGrupsLog[g].NameGrup == BT_G_TEMP.Name) //������ ����� �� ����
																		{
																		 int ID_T =  ID_names(TlogBtToGrupsLog[g].NameBT); //������ ��'��� �� ����
																	    
																		 if(ID_T >= 0) //���� ������������� ����� -1 ����� �������� 
																		 {
																			 bool vvvv = 1;
																			 for(int t = 0; t < BT_G_TEMP.ID_Objects.size();t++) //��������� �� ��������� ������������� � �����
																			 {
																				 if(BT_G_TEMP.ID_Objects[t] == ID_T)  //� ���� ��� ����������� ��� ��� �
																				 {
																					 vvvv = 0; //�������� �� ��� ��������� �� �������� ������
																					 break;
																				 }
																			 }

																			 if(vvvv)
																			 {
																				 std::cout<<"'"<<mObgects[ID_T].Names<<"'\n";
																				 BT_G_TEMP.ID_Objects.push_back(ID_T);
																				 
																			 }
																			 
																		 }

																		}
				
																	}
																	//���������� �������� ���� ���� ���� �
																	
																	if(BT_G_TEMP.bacgroundImageURL != "" && BT_G_TEMP.bacgroundImageURL != "NULL" && BT_G_TEMP.bacgroundImageURL != "null")
																	{
																	bool Suses = textureLoader.Knopka_LoadTexture(BT_G_TEMP.backgroundImage,    korin_dir +     BT_G_TEMP.bacgroundImageURL.c_str());
																	}

																	if(BT_G_TEMP.bacgroundHeaderImageURL != "" && BT_G_TEMP.bacgroundHeaderImageURL != "NULL" && BT_G_TEMP.bacgroundHeaderImageURL != "null")
																	{
																	bool Suses = textureLoader.Knopka_LoadTexture(BT_G_TEMP.backgroundHeaderImage,    korin_dir +     BT_G_TEMP.bacgroundHeaderImageURL.c_str());
																	}
			
																	Grups_.push_back(BT_G_TEMP); BT_G_TEMP.ID_Objects.clear();
																	
		}											//������� �����
		else
		if(ReadFile[i] == "Form_Init_End")                                         break;
	//=================================================================================================
		i++;
	}
	

	
	return 1;
}



//������� ��� ��������� ����� ���������
int  Get_glViewport_BT(std::string Name,bool Avto_Perspective,int fovy,int Zfar)
{
	int ID = ID_names(Name);
	if(ID < mObgects.size() && ID >=0)
	Get_glViewport_BT(ID,Avto_Perspective,fovy,Zfar);
	else
	return -1;

	return ID;
}
	//������� ��� ��������� ����� ���������
	int  Get_glViewport_BT(int ID,bool Avto_Perspective,int fovy,int Zfar)
	{
		if(Avto_Perspective) 
		gluPerspective(fovy,(float)mObgects[ID].SizeX/(float)mObgects[ID].SizeY,1,Zfar);

		//gluPerspective(30,1,1,200);

	    Private_Rozmis(ID);
		glViewport(X_CORD,Y_CORD,mObgects[ID].SizeX,mObgects[ID].SizeY);
		mObgects[ID].Temp.Perehvat = 1; //������ �� ������� ���� ������ ���� ��������������
		return ID;
	}


	void  GrupEnable(std::vector<int>ID,bool State) //���������� ��� ������������ ����� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].Enable = State;
			i++;
		}
		//return ID;
	}
	/*void  GrupEnable(int ID,bool State) //���������� ��� ������������ �����
	{
		Grups_[ID].Enable = State;
	}*/


		void  GrupVisual(std::vector<int>ID,bool State) //�������� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].vizual = State;
			i++;
		}
	}
/*	void  GrupVisual(int ID,bool State) //�������� �����
	{
		Grups_[ID].vizual = State;
	}*/














		void  GrupEnableInsert(std::vector<int>ID,bool State) //���������� ��� ������������ ����� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 0; int i = 0; while(ID.size()>i) { if(ID[i] == j) {A = 1; break;} i++; }  
			if(!A) Grups_[j].Enable = State;
			j++;
	    }
		//return ID;
	}

		void  GrupVisualInsert(std::vector<int>ID,bool State) //�������� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 0; int i = 0; while(ID.size()>i) { if(ID[i] == j) {A = 1; break;} i++; }  
			if(!A) Grups_[j].vizual = State;
			j++;
	    }
		//return ID;
	}



	void  GrupEnableAll(bool State) //������ ������� ��� ��� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{ 
			Grups_[j].Enable = State;
			j++;
	    }
		//return ID;
	}

		void  GrupVisualAll(bool State) //������ ������� ��� ��� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			Grups_[j].vizual = State;
			j++;
	    }
		//return ID;
	}



















































/*
	void  GrupEnable(std::vector<std::string>ID,bool State) //���������� ��� ������������ ����� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].Enable = State;
			i++;
		}
		//return ID;
	}
	/*void  GrupEnable(int ID,bool State) //���������� ��� ������������ �����
	{
		Grups_[ID].Enable = State;
	}
	

	void  GrupVisual(std::vector<int>ID,bool State) //�������� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].vizual = State;
			i++;
		}
		//return ID;
	}
	/*void  GrupVisual(int ID,bool State) //�������� �����
	{
		Grups_[ID].vizual = State;
	}*/












	// ID_GRUP_NAME(std::string Name)
	
		void  GrupEnableInsert(std::vector<std::string>ID,bool State) //���������� ��� ������������ ����� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 0; int i = 0; while(ID.size()>i) {if( ID_GRUP_NAME(ID[i]) == j) {A = 1; break;} i++; }  
			if(!A) Grups_[j].Enable = State;
			j++;
	    }
		//return ID;
	}
		
		void  GrupVisualInsert(std::vector<std::string>ID,bool State) //�������� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{



			bool A = 1; 
			int i = 0; 
			while(ID.size()>i) 
			{ 
				if(ID_GRUP_NAME(ID[i]) == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			}  


			if(A) Grups_[j].vizual = State;
			j++;
	    }
		//return ID;
	}
	
		void  GrupEnable(std::vector<std::string>ID,bool State) //���������� ��� ������������ ����� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			int ID_t =  ID_GRUP_NAME(ID[i]);
			if(ID_t >= 0)
			Grups_[ID_t].Enable = State;
			i++;
		}
		//return ID;
	}

		

	void  GrupVisual(std::vector<std::string>ID,bool State) //�������� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			int ID_t =  ID_GRUP_NAME(ID[i]);
			if(ID_t >= 0)
			Grups_[ID_t].vizual = State;
			i++;
		}
		//return ID;
	}








void  GrupVisualInsert(std::vector<std::string>ID,std::vector<int>ID1,bool State) //�������� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 1; 
			int i = 0; 
			while(ID.size()>i) 
			{ 
				if(ID_GRUP_NAME(ID[i]) == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			}  

			i = 0;
			while(ID1.size()>i) 
			{ 
				if(ID1[i] == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			} 

			if(A) Grups_[j].vizual = State;
			j++;
	    }
		//return ID;
	}

		//return ID;
	




void  GrupEnableInsert(std::vector<std::string>ID,std::vector<int>ID1,bool State) //�������� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 1; 
			int i = 0; 
			while(ID.size()>i) 
			{ 
				if(ID_GRUP_NAME(ID[i]) == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			}  

			i = 0;
			while(ID1.size()>i) 
			{ 
				if(ID1[i] == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			} 

			if(A) Grups_[j].Enable = State;
			j++;
	    }
		//return ID;
	}

	


void  GrupEnableInsertRevers(std::vector<std::string>ID,std::vector<int>ID1) //�������� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 1; 
			int i = 0; 
			while(ID.size()>i) 
			{ 
				if(ID_GRUP_NAME(ID[i]) == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			}  

			i = 0;
			while(ID1.size()>i) 
			{ 
				if(ID1[i] == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			} 

			if(A) 
			{
				if(Grups_[j].Enable) Grups_[j].Enable = 0; else Grups_[j].Enable = 1;
			}
			j++;
	    }
		//return ID;
	}

void  GrupVisualInsertRevers(std::vector<std::string>ID,std::vector<int>ID1) //�������� = �������� ����� �� ����
	{
		int j = 0;
		while(Grups_.size() > j)
		{
			bool A = 1; 
			int i = 0; 
			while(ID.size()>i) 
			{ 
				if(ID_GRUP_NAME(ID[i]) == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			}  

			i = 0;
			while(ID1.size()>i) 
			{ 
				if(ID1[i] == j) 
				{
					A = 0; 
					break;
				} 
				i++; 
			} 

			if(A) 
			{
				if(Grups_[j].vizual) Grups_[j].vizual = 0; else Grups_[j].vizual = 1;
			}
			j++;
	    }
		//return ID;
	}
	//*/


	void  GrupEnableRevers(std::vector<std::string>ID,std::vector<int>ID1) //���������� ��� ������������ ����� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			int ID_t =  ID_GRUP_NAME(ID[i]);
			if(ID_t >= 0)
			if(Grups_[ID_t].Enable) Grups_[ID_t].Enable = 0; else Grups_[ID_t].Enable = 1;
			i++;
		}

		i = 0;
		while(ID1.size()>i)
		{
			if(Grups_[ID1[i]].Enable) Grups_[ID1[i]].Enable = 0; else Grups_[ID1[i]].Enable = 1;
			i++;
		}
		//return ID;
	}

		

	void  GrupVisualRevers(std::vector<std::string>ID,std::vector<int>ID1) //�������� = �������� �����
	{
		int i = 0;
		while(ID.size()>i)
		{
			int ID_t =  ID_GRUP_NAME(ID[i]);
			if(ID_t >= 0)
			if(Grups_[ID_t].vizual) Grups_[ID_t].vizual = 0; else Grups_[ID_t].vizual = 1;
			i++;
		}

		i = 0;
		while(ID1.size()>i)
		{
			if(Grups_[ID1[i]].vizual) Grups_[ID1[i]].vizual = 0; else Grups_[ID1[i]].vizual = 1;
			i++;
		}
		//return ID;
	}


 ~DevChBTG(void)
{
}



};



