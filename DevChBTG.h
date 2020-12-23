/*
=====================================================================
Автор: Писанка Юрій Валентинович
Псевдонім: botemm
Опис: Класс призначений для створення інтерфейсу OpenGL старий стандарт C++
Зауваження: Вироблено християнином
Оновлено 23,6,2018
*/


//void (*func)(std::string Name,int id);



#pragma once

#include <string>       //Рядки
#include <vector>       //Вектор
#include <fstream>      //Робота з файлами
#include<GL\gl.h>      //Графіка
#include <GL\glu.h>     //Графіка
#include <GL\GLAUX.H>//Графіка
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
//================Внутрішні_класси======================================================Початок========

//2019 Font

public:
//Класс для роботи з текстом
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
	//Відповідність кодувань Для перетворень і порівнянь індекс коду відповідає індексу відповідної картинки
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


	//Структура плитки
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
		//Нарізка картинки
		std::vector<fragment>frag;

		//Коди символів
		std::vector<Cv2x>CodeChar;
		//Текстура
		Texture texture;
	};

	//Масив з завантаженими шрифтами
	std::vector<font>FontsArray;

	
	

	//Перетворити Юнікод в нормальний чар якщо неможливо вернути другий аргумент
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


//Отримати ширину тексту в пікселях
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


//Знайти id символа у файлі шрифта
				for(int i = 0;i<FontsArray[fontID].CodeChar.size(); i++){if(FontsArray[fontID].CodeChar[i].code == (int)CHARone){fragID = i;break;}}
		
				//Знаходжу який еквывалент OpenGL в 1 пікселі окремо по х і у  при множені піксельної величини на цей еквіваленти ми по факту конвертуємо пікселі в значення системи координат OpenGL
				float cofX = 2.0f / ((float)WindowsData.ViewportWidth  );
				float cofY = 2.0f / (float)WindowsData.ViewportHeight;


				//Перетворити піксельний розмір в значення OpenGL
				float  SizeX = (size*cofX);
				float  SizeY = (size*cofY);

				//Перетворити кокординати елемента з піксильної системи в систеу OpenGL
				//x=cofX;
				//y=cofY;

				//Так як початок системи координат OpenGL в центрі екрана Я змышуюю її в лівий нижній куток
			//	x-=1;
				//y-=1;


				//float X_CORD,Y_CORD;
				float PosX = 0;
				float PosY = 0;




				//Тут я отримую різницю текстурних координат букви система координат від 0 до 1. Для того щоб знати на скільки розтянути букву щоб вона не була спотвореною.
				float wi = FontsArray[fontID].frag[fragID].kX - FontsArray[fontID].frag[fragID].pX;
				float hi = FontsArray[fontID].frag[fragID].kY - FontsArray[fontID].frag[fragID].pY;

				//Розраховую кефіцієнт розтягнення букви з урахуванням початкового розміру текстури і розміру букви
				float cof = (FontsArray[fontID].texture.width/FontsArray[fontID].texture.height) * (wi/hi);
	
				

				/*DrawPlane(PosX,PosY, //Вказую початкові координати в системі OpenGL
					PosX + SizeX*cof,PosY + SizeY, //Вказую кінцеві координати в системі OpenGL
					FontsArray[fontID].frag[fragID].pX,-FontsArray[fontID].frag[fragID].pY,FontsArray[fontID].frag[fragID].kX,-FontsArray[fontID].frag[fragID].kY); //Далі текстурні координати

		*/
				//Розраховую Ширину букви переведену в піксельні координати На відміну від Y значення Х змінюється через коефіцієнт У залишається таким самим
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


//Знайти id символа у файлі шрифта
				for(int i = 0;i<FontsArray[fontID].CodeChar.size(); i++){if(FontsArray[fontID].CodeChar[i].code == (int)CHARone){fragID = i;break;}}
		
				//Знаходжу який еквывалент OpenGL в 1 пікселі окремо по х і у  при множені піксельної величини на цей еквіваленти ми по факту конвертуємо пікселі в значення системи координат OpenGL
				float cofX = 2.0f / ((float)WindowsData.ViewportWidth  );
				float cofY = 2.0f / (float)WindowsData.ViewportHeight;


				//Перетворити піксельний розмір в значення OpenGL
				float  SizeX = (size*cofX);
				float  SizeY = (size*cofY);

				//Перетворити кокординати елемента з піксильної системи в систеу OpenGL
				x*=cofX;
				y*=cofY;

				//Так як початок системи координат OpenGL в центрі екрана Я змышуюю її в лівий нижній куток
				x-=1;
				y-=1;


				//float X_CORD,Y_CORD;
				float PosX = x;
				float PosY = y;




				//Тут я отримую різницю текстурних координат букви система координат від 0 до 1. Для того щоб знати на скільки розтянути букву щоб вона не була спотвореною.
				float wi = FontsArray[fontID].frag[fragID].kX - FontsArray[fontID].frag[fragID].pX;
				float hi = FontsArray[fontID].frag[fragID].kY - FontsArray[fontID].frag[fragID].pY;

				//Розраховую кефіцієнт розтягнення букви з урахуванням початкового розміру текстури і розміру букви
				float cof = (FontsArray[fontID].texture.width/FontsArray[fontID].texture.height) * (wi/hi);
	
				

				DrawPlane(PosX,PosY, //Вказую початкові координати в системі OpenGL
					PosX + SizeX*cof,PosY + SizeY, //Вказую кінцеві координати в системі OpenGL
					FontsArray[fontID].frag[fragID].pX,-FontsArray[fontID].frag[fragID].pY,FontsArray[fontID].frag[fragID].kX,-FontsArray[fontID].frag[fragID].kY); //Далі текстурні координати

		
				//Розраховую Ширину букви переведену в піксельні координати На відміну від Y значення Х змінюється через коефіцієнт У залишається таким самим
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


		 if(!INp) {ErrorList += "Файл відсутній\n"; return false;}

		 //Читання Коду фалу для перевірки чи коректний файл відкрито============================================
				int CodeFiles = 0; //1546534
				INp.read((char*)&CodeFiles,sizeof(CodeFiles)); //Код файлу

				if(CodeFiles != 1546534) {ErrorList += "Непідтримуваний формат\n"; return false;}



		//Читання Версії файлу==================================================================================
				short Version = 0; //1
				INp.read((char*)&Version,sizeof(Version)); //Версія файлу

				if(Version < 1 || Version == 0) {ErrorList += "Непідтримувана версія файлу\n"; return false;}

		//Читання розмітки======================================================================================
				if(INp.eof()) std::cout<<"Кінець файлу що за:"<<std::endl; else  std::cout<<"Ще все норм:"<<std::endl;
		int SS = 0; 
		INp.read((char*)&SS,sizeof(SS)); //Довжина 
		std::cout<<"SizeFrag:"<<SS<<std::endl;
		DEF.frag.resize(SS);
		INp.read((char*)&DEF.frag[0],sizeof(fragment)*SS);

		//Коди відповідності кодування=======================================================================
				

				int sz = 0; //Розмір масиву
				INp.read((char*)&sz,sizeof(sz));    //Довжина масиву
				std::cout<<"SizeKode:"<<sz<<std::endl;

				//if(INp.eof()) std::cout<<"Кінець файлу що за:"<<std::endl; else  std::cout<<"Ще все норм:"<<std::endl;


				DEF.CodeChar.resize(sz);
				INp.read((char*)&DEF.CodeChar[0],sizeof(Cv2x)*sz);    //Масив
				


	
	 
		
				//Запис зобрадення====================================================================================
				//Спочатку читаю інформацію про зображення
				INp.read((char*)&DEF.texture.width,sizeof(DEF.texture.width));                //Висота
				INp.read((char*)&DEF.texture.height,sizeof(DEF.texture.height));              //Ширина
				INp.read((char*)&DEF.texture.nrComponents,sizeof(DEF.texture.nrComponents));  //Кількість компонент в 1 пікселі

				int size = DEF.texture.width*DEF.texture.height*DEF.texture.nrComponents;				//Кількість всіх пікселів


				std::cout<<"wi = "<<DEF.texture.width<<"   hi = "<<DEF.texture.height<<"  mod:"<<DEF.texture.nrComponents<<std::endl;
	            

				

				vector<char> image1(size);
				INp.read(&image1[0],size*sizeof(unsigned char));						//Читаємо масив пікселів

				//Компілюємо текстуру-----------
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
				



				//Зберігти до всіх шрифтів
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
	bool ISusTextureLoader; //Чи призначав користувач функцію завантаження текстур
	//Функція для завантажена текстур при потребі розширити підтримук типів текстур визначається користувачем
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
  glGenTextures(1, &Idtexture);  // Сгенерировать OpenGL текстуру IDs
  glBindTexture(GL_TEXTURE_2D,Idtexture); // Привязать нашу текстуру

  // Линейная фильтрация
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // Линейная фильтрация 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 
  glTexImage2D(GL_TEXTURE_2D, 0, type, width, height,0, type, GL_UNSIGNED_BYTE, image);
 return Idtexture;
}


	public:
		typedef   struct                      // Структура для завантаження в неї текстур, система загрузки вбудована для зручності
		 { 
			   unsigned char  *imageData;                  // Данные изображения (до 32 бит)
			   GLuint   bpp;                         // Глубина цвета в битах на пиксель
			   GLuint   width;                       // Ширина изображения 
		       GLuint   height;                      // Высота изображения
			   GLuint   texID;                       // texID используется для выбора // текстуры
		 } Knopka_TextureImage;                       // Имя структуры

struct TExtureHistory
		{
			std::string url;
			GLuint TextureID;
		};
		std::vector<TExtureHistory>TExtureHistory_; //Список заантажених текстур цим інтерфейсомж

bool  Knopka_LoadTga(GLuint &texID,std::string filename)  // Загружаем TGA файл в память
{  
Knopka_TextureImage teIm;
Knopka_TextureImage *texture = &teIm;
	
GLubyte  TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0}; // Заголовок несжатого TGA файла
GLubyte  TGAcompare[12]; // Используется для сравнения заголовка TGA файла
GLubyte  header[6];      // Первые 6 полезных байт заголовка
GLuint   bytesPerPixel;  // Количество байтов на пиксель используемое в TGA файле
GLuint   imageSize;      // Количество байтов, необходимое для хранения изображения в памяти
GLuint   temp;           // Временная переменная
GLuint   type=GL_RGBA;   // Установим по умолчанию режим RBGA (32 BPP)
  FILE *file = fopen(filename.c_str(), "rb");         // Открытие TGA файла
  if(file==NULL ||                            // Существует ли файл
fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||  // Если прочитаны 12 байтов заголовка

     memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0 || // Если заголовок правильный

     fread(header,1,sizeof(header),file)!=sizeof(header)) // Если прочитаны следующие 6 байтов

  {

         if (file == NULL)                      // Если ошибка

                return false;                   // Возвращаем false

         else

         {

                fclose(file);                   // Если ошибка, закрываем файл

                return false;                   // Возвращаем false

         }

  }


  // Определяем ширину TGA (старший байт*256+младший байт)

  texture->width  = header[1] * 256 + header[0]; 

  // Определяем высоту TGA (старший байт*256+младший байт)

  texture->height = header[3] * 256 + header[2];

  

  if(texture->width  <=0 ||            // Если ширина меньше или равна нулю

   texture->height <=0 ||            // Если высота меньше или равна нулю    

  (header[4]!=24 && header[4]!=32))  // Является ли TGA 24 или 32 битным?

  {

    fclose(file);                    // Если где-то ошибка, закрываем файл

    return false;                    // Возвращаем false

  }


  texture->bpp  = header[4];        // Получаем TGA бит/пиксель (24 or 32)

  bytesPerPixel = texture->bpp/8;   // Делим на 8 для получения байт/пиксель  

  // Подсчитываем размер памяти для данных TGA

  imageSize = texture->width*texture->height*bytesPerPixel;
  texture->imageData=(GLubyte *)malloc(imageSize); // Резервируем память для хранения данных TGA 
  if(texture->imageData==NULL ||           // Удалось ли выделить память?
   fread(texture->imageData, 1, imageSize, file)!=imageSize)
  // Размер выделенной памяти равен  imageSize?
  {
    if(texture->imageData!=NULL)       // Были ли загружены данные?

      free(texture->imageData);        // Если да, то освобождаем память

  

    fclose(file);                      // Закрываем файл

	texID = texture->texID;

    return false;                      // Возвращаем false

  } 


  for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)  // Цикл по данным, описывающим изображение

  {                                                    // Обмена 1го и 3го байтов ('R'ed и 'B'lue)

    temp=texture->imageData[i];                        // Временно сохраняем значение imageData[i]

    texture->imageData[i] = texture->imageData[i + 2]; // Устанавливаем 1й байт в значение 3го байта

    texture->imageData[i + 2] = temp;                  // Устанавливаем 3й байт в значение,

                                                       // хранящееся в temp (значение 1го байта)

  }

  fclose (file);                                       // Закрываем файл

/*
  // Строим текстуру из данных

  glGenTextures(1, &texture[0].texID);  // Сгенерировать OpenGL текстуру IDs

  glBindTexture(GL_TEXTURE_2D, texture[0].texID); // Привязать нашу текстуру

  // Линейная фильтрация

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // Линейная фильтрация 

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (texture[0].bpp==24)                      // Если TGA 24 битный

  {
     type=GL_RGB;                            // Установим 'type' в GL_RGB
  }
  glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height,0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
  texID = texture->texID;
  */
  
  if (texture[0].bpp==24)                      // Если TGA 24 битный

  {
     type=GL_RGB;                            // Установим 'type' в GL_RGB
  }
  texID = CreateTexture(texture[0].imageData,type, texture[0].width, texture[0].height);
  return true;              // Построение текстуры прошло Ok, возвратим true
  
}

bool  LoadBMP(GLuint &out_img,string filename) //загрузка bmp
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





bool  Knopka_LoadTexture(GLuint &texture,std::string filename)  // Загружаем TGA файл в память
{    
	//int wi
	//DevChBTG::ISusTextureLoader;

	
  


	//Запобігання завантаження текстур по два рази
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
		 Rez = Knopka_LoadTga(texture,filename);  // Загружаем TGA файл в память
		}
		else
		if(filename[filename.size()-4] == '.' && (filename[filename.size()-3] == 'B' || filename[filename.size()-3] == 'b')  &&  (filename[filename.size()-2] == 'M' || filename[filename.size()-2] == 'm') && (filename[filename.size()-1] == 'P' || filename[filename.size()-1] == 'p'))
		{
		  Rez = LoadBMP(texture,filename); //загрузка bmp
		}
	}




	if(Rez) //Якщо текстура була завантажена правильно то вкидаємо її до історії
	{
	TExtureHistory IS;
	TExtureHistory_.push_back(IS);
	TExtureHistory_[TExtureHistory_.size()-1].url = filename;
	TExtureHistory_[TExtureHistory_.size()-1].TextureID = texture;
	}

  return Rez;              // Построение текстуры прошло Ok, возвратим true

}



};

//=====================================================================================================
//=====================================================================================================
//================Внутрішні_класси======================================================Кінець=========
//=====================================================================================================
//=====================================================================================================

public:
TEXTURE textureLoader;



//=================
//Функції які можна переназначити на свої
public:
	//Функція для завантажена текстур при потребі розширити підтримук типів текстур визначається користувачем
	void setVoidTextureLoader(bool (TextureLoaderA)(std::string url, int &width, int &height, GLuint &TxID))
	{
		textureLoader.setVoidTextureLoader(TextureLoaderA);
		return;
	}


public:
	







//2019 Mode Aspiranska========

//Функція роботу якої програміст може перейняти на себе

//Функція малювання площин перехват програмістом
bool isVoidDrawPlane;
void (*VoidDrawPlane)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid);
void setVoidDrawPlane(void (*VoidDrawPlaneA)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid))
{
	VoidDrawPlane = VoidDrawPlaneA;
	Enable(isVoidDrawPlane);
}




//Малювати елементи головна функція
void DrawStyleElements(int id, float x,float y, float width, float height)
{
	//Не малювати не видиму кнопку
	if(!mObgects[id].Vizual) return;



	glBindTexture(GL_TEXTURE_2D,mObgects[id].ImageKnopki);
	float SizeX , SizeY ,PosX ,PosY;
	float HoverSizeX,HoverSizeY;//,HoverPosY,HoverPosX;
	//Розрахунок коефіцієнту розміру 
				float cofX = 2.0f / (float)windows_data.ViewportWidth ;
				float cofY = 2.0f / (float)windows_data.ViewportHeight ;
			{
				

				//Ширина і висота графічного елементу
				 SizeX = ((float)mObgects[id].SizeX*cofX);
				 SizeY = ((float)mObgects[id].SizeY*cofY);
				


				 PosY =  ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY/2)*cofY)-1;
                 PosX =  ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].SizeX/2)*cofX)-1;



				 //Ширина і висота графічного елементу
				 HoverSizeX = ((float)mObgects[id].HoverSizeX*cofX);
				 HoverSizeY = ((float)mObgects[id].HoverSizeY*cofY);
				
				/* HoverPosY =  ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].HoverSizeY/2)*cofY)-1;
				 HoverPosX =  ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].HoverSizeX/2)*cofX)-1;*/
			}
			//draw


			

			
			//glBindTexture(GL_TEXTURE_2D,mObgects[id].ImageKnopki);

			//float

			//Колір залежно від активності
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




					//Початак І кінець руху каретки
				float EndPos = ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].SizeX - (float)mObgects[id].trackBarKaretkaSizeX/2)*cofX )-1;
				float StartPos = ((X_CORD-(float)windows_data.ViewportPosX+(float)mObgects[id].trackBarKaretkaSizeX/2)*cofX)-1;
				float MaxValue = EndPos - StartPos;

				
				float VEnd = mObgects[id].MaxValue - mObgects[id].MinValue;
				float Val = mObgects[id].Value - mObgects[id].MinValue;
				//float vStart = 0;

				//Розмір у відцотках від 0 до 1
				float Value = Val/VEnd;
				
				DrawPlane(mObgects[id].trackBarKaretkaSizeX*cofX,mObgects[id].trackBarKaretkaSizeY*cofY,StartPos+MaxValue*Value,PosY,1,1,0,0,mObgects[id].RotationMode);

				}
				else //======================================================================================================
				if(mObgects[id].RotationMode == 'W') //Вертикальний трек бар
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




					//Початак І кінець руху каретки
				float EndPos = ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].SizeY - (float)mObgects[id].trackBarKaretkaSizeY/2)*cofY )-1;
				float StartPos = ((Y_CORD-(float)windows_data.ViewportPosY+(float)mObgects[id].trackBarKaretkaSizeY/2)*cofY)-1;
				float MaxValue = EndPos - StartPos;

				
				float VEnd = mObgects[id].MaxValue - mObgects[id].MinValue;
				float Val = mObgects[id].Value - mObgects[id].MinValue;
				//float vStart = 0;

				//Розмір у відцотках від 0 до 1
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
			if(mObgects[id].Type == "Label" || mObgects[id].Type == "label") // Для лейбелів підкладинка не потрібна
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


			//Малювати текст
			FontSystems.print(mObgects[id].Text	,PosTextRealX	,PosTextRealY	,FontSystems.DefaultFonts,mObgects[id].TextSize);

			//Малювати курсор введення для текст бокса
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


//2018 Спрощене додавання кнопок в групи
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

	bool textEnable; //Чи відображати текст
	//int DirFIX;      //Змінна вказує скільки кроків назад зробити щоб запрацювали зображення (Вона не функціональна тобто інформація в ній зберігається але клас нічого з нею не робить)













	private:
	int Y_CORD1;
	int X_CORD1;
	
public:
	std::string korin_dir; //Корнева папка
	    
	    struct ComandVector       //Структура для збереження команд
		{
			std::string Comand_FUNC;
			std::vector<std::string> ComandLine; //фУНКЦІЯ І ЇЇ АРГУМЕНТИ
			std::vector<int> ArgLine; //Числові аргументи
		};
		ComandVector ComandVectorIN()
		{
			ComandVector A;
			A.Comand_FUNC = "";
			return A;
		}
		ComandVector ComandVectorTemp; //допоміже змінна 

	    struct GrupSetVievport    //Дані які повертатиме функція 
		 {
			 int PosX;
			 int PosY;
		 };

	     struct Maus_Data         //Структура інформації про мишу
         {
	           int MausX_W ,MausY_W;// ,MausX,  MausY;
               int PressState;  int MausBT;
         };

		 struct windows_info      //Віконна інформація для вирахувань розміщення кнопок  дані заносятся вручну
		 {
	           Maus_Data  Maus_Data_;
			   //Ширина і висота вікна цілком
			   int WindowsHeight;
			   int WindowsWidth;

	           int ViewportWidth;  //Ширина Області промальовки
               int ViewportHeight; //Висота Області промальовки
			  
			   int ViewportPosX; //Зміщення по х та у якщо потрібно змістити систему з країв вікна
			   int ViewportPosY;
		 };

		 struct  PixelRGBA        //Структура збереження коряру
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


		 struct PrivateBT                     //Згруповані дані для структури кнопок, до яких користувач не лізе, змінні обробляются на автоматі
		 {
			   PSSTEXT F; //Temp
			   bool activ;      //Активність кнопки
			   bool Clic;
			   bool Clic_Temp; 
			   bool TiskActiv;
			   bool Klik;
			   bool Temp_obrob; //Кнопка вже оброблялась чи ні
			   std::string URL; //Адреса Картинки
			   std::string URL2; //Адреса допоміжної Картинки
			   bool Perehvat; //Вказує що кнопка була перезхвачена і не малює її
		 };

		 struct OBGECT						//Структура інформації про кнопку (Правила створення кнопки)
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
			   int TextSize;			//Висота тексту
			   char TextPositionAlignX;		//Позиціонування відносно елемента по Х
			   char TextPositionAlignY;		//Позиціонування відносно елемента по Y
			   std::string FontName;	//Назва щрифта або по іншому Стиль вибирається з завантажених
			   PixelRGBA TextColor;		//Колір тексту
			   //====================================================================================


			   //Global Setling
			   int ObjectType; //Тип Об'єкта  Label Button CheckBox ....

			   //Check and Radio Box
			   bool Checked;
			   int RadioGrup;


			   //RagioBox
			   int GrupRadioBox;


			   //Hover
			   int HoverSizeX,HoverSizeY;
			   PixelRGBA HoverColor;
			   PixelRGBA HoverTextColor;


			   //Додаткове зображення наприклад для Бігунка полоси прокрутки trackBar
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

			   //Вертикально чи горизонтальо відображати елемет
			   char RotationMode;


			   //#2019
			   //Яцщо на кнопку натиснули і не відпускали кнопку ця змінна буде одиницею, і неважливо активна кнопка чи ні
			   bool ClickPress;



			   
			   std::vector<ComandVector>Comanda; //Список зчитаних командsaw
			   //new
			   bool static_func;  //Чи використовувати команди зчитані з форми

			   //Позиція при введенні тексту
			   int PosTextCursor;
		};

		struct Grup //Система груп
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

			   //Полоска яку тягнути
			    std::string bacgroundHeaderImageURL;
				GLuint backgroundHeaderImage;
			   int heightHeader;
			   int sizeX;
			   int sizeY;

			  char CWertical;
			  char CHorizontal;

		};

 


OBGECT Knopka_IN()     //Стандартні налаштування кнопки
{
	//Об'єкт нова кнопка
	OBGECT A;

	A.RotationMode = 'H';

	//По замовчуванню на кнопку не натискали
	A.ClickPress = false;

	//Темчасові дані
	A.Temp.Temp_obrob = 0;

	//Адреса текстурки
	A.Temp.URL = "";

	//Позиція кнопки на екрані (Реальна позиція буде розрахована відносно позиціонування)
	A.PosX = 0;
	A.PosY = 0;

	//Розмір кнопки
	A.SizeX = 50;
	A.SizeY = 50;

	A.Type = "Button";
	A.Enabled = true;

	//Колір
	A.Color.A = 255;
	A.Color.R = 255;
	A.Color.G = 255;
	A.Color.B = 255;

	//Колір Активного елемента
	A.HoverColor.A = 200;
	A.HoverColor.R = 255;
	A.HoverColor.G = 255;
	A.HoverColor.B = 100;

	//Текст
	A.Text = "";

	//Ім'я по ньому обробляються кліки
	A.Names = "ButtonEnemy";

	//Темчасові змінні для кліків
	A.Temp.activ = 0;
	A.Temp.Clic = 0;
	A.Temp.Clic_Temp = 0;
	A.Temp.TiskActiv = 0;
	A.Temp.Klik = 0;


	//Видимість
	A.Vizual = true;
	
	//Позиціонування
	A.CHorizontal = 'L';
	A.CWertical = 'W';

	
	
	
	//Якщо увімкнено подія буде викликатися кожного кадра
	A.Avtomatic = false;

	//Адреса текстури
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



	//Про всяк випадок очистити список внутрішніх оманд
	A.Comanda.~vector();
    return A;
}


Grup  Grup_IN()     //Стандартні налаштування Групи
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

int BT_MAUSE_KLIK_KNOPKA; //Яка кнопка (сигнал) відповідає за натиск

//##2019
//Знайти елемент по назві і записанти посилання на нього
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
GrupSetVievport  Get_Position_glViewport(int SizeX,int SizeY,int PosX,int PosY,char CWertical,char CHorizontal)  //функція заповнює змінні розрахування положення Для віэвпорта
{
	GrupSetVievport A;
	//Налаштування по вертикалі
	if(CWertical == 'W' || CWertical == 'w')  
	A.PosY = (-PosY+windows_data.ViewportHeight - SizeY) +  windows_data.ViewportPosY ; 
	else 
	if(CWertical == 'C' || CWertical == 'c')    
	A.PosY = (-PosY+windows_data.ViewportHeight/2 - SizeY/2) +  windows_data.ViewportPosY ; 
	else 
	A.PosY = PosY +  windows_data.ViewportPosY;

    //Налаштування по горизонталі
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
	





	windows_info windows_data;        //Змінна в яку потрібно заносити дані про вікно і клавішні натиски
	std::vector<OBGECT>mObgects;       //Векторна змінна в якій зберігаются кнопки
	OBGECT BT_K_TEMP;                 //Допоміжна змінна яка налаштовуєтся а потім вкидаєтся її копія в вектор кнопок
	bool kyrsor_na_cnopci;            //Показує що одна із кнопок активна
	std::vector<Grup>Grups_;          //Вектор груп
	Grup  BT_G_TEMP;   


//Темчасові дані
int Y_CORD;
int X_CORD;


//bmp
/* размер заголовка BMP-файла */ 
 
#define BMP_SIZE_FILEHEADER 14  
 
/* размер информационного заголовка BMP-файла */ 
#define BMP_SIZE_INFOHEADER 40   
 
#define BMP_COLOR_BITS_24 24  
 
/* вспомогательные функции */ 
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
	
	//Модифікація промальовки кнопок, дозволяє при малюванні не використовувати Viewport що дозволяэ ховати панельки
	bool MODglViewport;
 

//Останній натиск по ід Кнопка яку останню нажимали
int IdTheLastPush;
double Time;


//Темчасові змінні які дозволять переміщати вікна
int idTheLastPushWindow; //На якому вікні було клікнуто мишею
int IdGrupsHoverHight;
int IdGrupsHoverMain; //На якому вікні зараз миша, запобігання клікабельності опо перекритим вікнам
//Запамятовує координати миші в момент кліку що дозволяє розраховувати тільки зміщення
int TheLastXpsMAuse;
int TheLastYpsMAuse;
//Позиція вікна в момент кліку
int TheLastXPosWin;
int TheLastYPosWin;



//(2019.12 - point 20)
//Знайти обєкт в групі
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


//(2019.12 - point 20) //Дуюлювати вікно зі всіма його елементами (Додати приставку до імені кожного елемента)
bool DuplicateGrup(int idGrup,std::string SubText,int &newGrup, bool CopyElements)
{
	//Якщо група не існує то то відправляємо помилку
	if(idGrup >= Grups_.size() || idGrup < 0)
	{
		return false;
	}


	//Скопіювати групу 
	Grup tGrup =  Grups_[idGrup];
	//і з нової видалити посилання на старі елемети
	tGrup.ID_Objects.clear();
	//Додати до імені приставку
	tGrup.Name = SubText + tGrup.Name;

	//Скопіювати всі елемети групи
	if(CopyElements)
	for(int i = 0; i < Grups_[idGrup].ID_Objects.size() ; i++)
	{
		{
		//Скопіювати в змінну обект
		OBGECT tObjects = mObgects[  Grups_[idGrup].ID_Objects[i]  ];
		//Додати суб назву
		tObjects.Names = SubText + tObjects.Names;
		//Зберегти в масив обєкт

		//tObjects.Comanda.clear();
		mObgects.push_back(tObjects);

		//BT_NEW_Knopka(BT_K_TEMP,BT_K_TEMP.Names,BT_K_TEMP.Temp.URL); BT_K_TEMP.Comanda.clear(); 



		//Зберегти ідентифікатор скопійованого обекта в нову групу
		tGrup.ID_Objects.push_back(mObgects.size()-1);
		}
	}


	Grups_.push_back(tGrup);

	//Записую ід нової групи
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
	//Вимикаємо користувацьку функцію на правах конструктора
	Disable(textureLoader.ISusTextureLoader);
	//Disable(isVoidDrawPlane);
	Disable(isVoidDrawPlane);
	Disable(isVoidGlobalDrawPlane);
	
	//Функція для завантажена текстур при потребі розширити підтримук типів текстур визначається користувачем
	bool (*usTextureLoader)(std::string url, int &width, int &height, GLuint &TxID);

	string vertexS = "";

	//StandartShader.ShaderS();



	textEnable = 1;
	OBGECT BT_K_TEMP = Knopka_IN();                 //Допоміжна змінна яка налаштовуєтся а потім вкидаєтся її копія в вектор кнопок
	Grup  BT_G_TEMP = Grup_IN();
	BT_MAUSE_KLIK_KNOPKA = 0;                       //якщо сигнал від glut то ліва кнопка миші по стандарту
	windows_data.Maus_Data_ .PressState = 0;
	windows_data.Maus_Data_ .MausBT = -1;

}


//Функції роботи з клавіатурою
//Функція в яку потрібно передавати aspi натисненої кнопки
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

//Функція в яку потрібно передавати Символ натиснутої кнопки
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



//2019 Отримати позицію кнопки з урахуванням позиціювання
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



	

	 //Налаштування по вертикалі
	if(CWertical == 'W' || CWertical == 'w')  
	y = -PosY+windows_data.ViewportHeight - SizeY ; 
	else 
	if(CWertical == 'C' || CWertical == 'c')    
	y = -PosY+windows_data.ViewportHeight/2 - SizeY/2 ; 
	else 
	y = PosY;

    //Налаштування по горизонталі
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





void BPrivate_Rozmis(int i)  //функція заповнює змінні розрахування положення
{
	GetPosBT(i,X_CORD1,Y_CORD1);
}

void FixWindow_Private_Size(int iBt,int IdG,int &x,int &y)  //функція заповнює змінні розрахування положення
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
	

	
	

	 //Налаштування по вертикалі
	if(CWertical == 'W' || CWertical == 'w')  
	y = -PosY+WindowHeight - SizeY ; 
	else 
	if(CWertical == 'C' || CWertical == 'c')    
	y = -PosY+WindowHeight/2 - SizeY/2 ; 
	else 
	y = PosY;

    //Налаштування по горизонталі
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




void  VSTAN_ZMIN_T_OBROB(bool Stan) //Вказує чи ооброблялись усі кнопки Приватна
{

	//MD_ Модифыкувати під активні групи
		/*int i = 0;
		while(i<KNopka_.size())
		{
				KNopka_[i].Temp.Temp_obrob = Stan;
			i++;
		}*/

			int j = 0;
		while(j<Grups_.size()) //пройтись по всім групам
		{
			if(Grups_[j].vizual == 1) //якщо група видима і активна
			{
							int i = 0;
							while(i<Grups_[j].ID_Objects.size()) //обробити записані ідентифікатори
								{
										mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob = Stan; //Вказуємо що кнопка оброблена
                                        i++;
							    }
			}
			j++;
		}

}

int  ID_GRUP_NAME(std::string Name) //Функція повертає ІД знаходячи його за назвою
{
	int i = 0;
	while(Grups_.size()>i)
	{
		if(Grups_[i].Name == Name)
		return i;
		i++;
	}
	return -1; //Групу з такою назвою не знайдено
}
bool IStheProcessReform;//Змінна яка дозволяє зупинити обробку кнопок якщо при натиску на кнопку виконано завантаження іншої форми
void  MSG_BT(void (*func)(std::string Name,int idObject,int idGrup))   //Цю функцю потрібно викликати в циклі з назфою функції куди потрібно надіслати назву натисненої кнопки.
{
	IStheProcessReform = false;
	VSTAN_ZMIN_T_OBROB(0); //всі кнопки не оброблені По замовчуваню

	    kyrsor_na_cnopci = 0;
	

		int j = 0;
		while(j<Grups_.size()) //пройтись по всім групам
		{
			if(Grups_[j].vizual == 1 && Grups_[j].Enable == 1) //якщо група видима і активна
			{
							int i = 0;
							while(i<Grups_[j].ID_Objects.size()) //обробити записані ідентифікатори
								{
									//if(mObgects.size() > Grups_[j].ID_Objects[i] && Grups_[j].ID_Objects[i]>=0)

									if(mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob == 0) //Якщо кнопка не оброблялася
									{//**Обробити кнопку

										mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob = 1; //Вказуємо що кнопка оброблена

									if(mObgects[Grups_[j].ID_Objects[i]].Temp.Klik == 1)
									{
										
										//Надіслати в користувацьку функцію імя і ід
										func(mObgects[Grups_[j].ID_Objects[i]].Names,Grups_[j].ID_Objects[i] ,j );
										if(IStheProcessReform == true) return; //Терміново зупинити обробку було завантажено нову форму або оновлено
										mObgects[Grups_[j].ID_Objects[i]].PosTextCursor = mObgects[Grups_[j].ID_Objects[i]].Text.size();

										//if(Grups_.size() == 0 && mObgects.size() == 0) return;

										//if(Grups_[j].ID_Objects.size() < j) return;

										IdTheLastPush = Grups_[j].ID_Objects[i]; //Запомнити останню натиснену кнопку


										mObgects[Grups_[j].ID_Objects[i]].Temp.Klik = 0;

										//Якщо натиснено на радіобокс зняти всы галочки з групи цього радыобокса і поставити на цьому галочку якщо її не було
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



										
				//===========================Обробка внутрішніх команд кнопок
										int i_t = 0;
										while(i_t < mObgects[Grups_[j].ID_Objects[i]].Comanda.size())
										{
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnable")  ////Активувати групи = груповий пакет
											{
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1);
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,1);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisable")   ////Деактивувати групи = груповий пакет
											{
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											GrupEnable(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,0);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOn") //Робить видимими вказані групи
											{
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1);
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,1);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOff") //Робить не видимими вказані групи
											{
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											GrupVisual(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,0);
											}
											else

											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOnInsert") //GrupVisualOnInsert –робить видимими всі не вказані групи (вказані не зачіпає). Приймає наступні дані (int кількість, *(string  та int)).
											{
											GrupVisualInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOffInsert") //GrupVisualOnInsert –робить видимими всі не вказані групи (вказані не зачіпає). Приймає наступні дані (int кількість, *(string  та int)).
											{
										    GrupVisualInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											}
											else
												
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableInsert")
											{
											GrupEnableInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,1); //– робить активними всі не вказані групи (вказані не зачіпає). Приймає наступні дані (int кількість, *(string  та int)).
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableInsert")  //– робить неактивними всі не вказані групи (вказані не зачіпає). Приймає наступні дані (int кількість, *(string  та int)).
											{
											GrupEnableInsert(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine,0);
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableAll") //Активувати всі групи
											GrupEnableAll(1);
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableAll") //Деактивувати всі групи
											GrupEnableAll(0);
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOnAll") //Зробити видимими всі
											GrupVisualAll(1);
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualOffAll") //Зробити не видимими всі
											GrupVisualAll(0);



											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableInsertRevers" || mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableInsertRevers") // змінити значення активності не вказаних груп на протилежні. ). Приймає наступні дані (int кількість, *(string  та int)).
											GrupEnableInsertRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //Видимість = груповий пакет Всі окрім
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualInsertRevers")
											GrupVisualInsertRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //Видимість = груповий пакет Всі окрім
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupEnableRevers" || mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupDisableRevers")
											{
											GrupEnableRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //Видимість = груповий пакет Всі окрім
											}
											else
											if(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].Comand_FUNC == "GrupVisualRevers")
											{
											GrupVisualRevers(mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ComandLine,mObgects[Grups_[j].ID_Objects[i]].Comanda[i_t].ArgLine); //Видимість = груповий пакет Всі окрім
											}








											i_t++;
										}

										
				//===========================================================



									}
			
											//-----------
											if(mObgects[Grups_[j].ID_Objects[i]].Temp.activ == 0) //Якщо кнопка не активна дані про натиск затираются
											{
												mObgects[Grups_[j].ID_Objects[i]].Temp.Clic = 0;
												mObgects[Grups_[j].ID_Objects[i]].Temp.Clic_Temp = 0;
											}
												else
											kyrsor_na_cnopci = 1; //Якщо хоч одна кнопка активна
											//-----------
									}//**
			i++;
		}
			}
			j++;
		}


}


 



//Система вкидання в пам'ять нової кнопки
int  BT_NEW_Knopka(OBGECT A,std::string Name)
{
	A.ClickPress = false;
mObgects.push_back(A);
mObgects[mObgects.size()-1].Names = Name;
return mObgects.size()-1;
}

//Система вкидання в пам'ять нової кнопки з завантаження вказаної текстури
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

void  PanelDisableVizual(int *a,int size) //Панелі які потрібно Вимкнути
{
	int i = 0;
	while(i<size)
	{
	PAneli_Visual(a[i],0);
	i++;
	}
}

void  PanelDisableVizualR(int *a,int size) 
{//Панелі які не потрібно вимкнути
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
void  Private_Rozmis(int i)  //функція заповнює змінні розрахування положення
{
	GetPosBT(i,X_CORD,Y_CORD);
}




public:

	
//Глобальна функція малювання
bool isVoidGlobalDrawPlane;

void (*VoidGlobalDrawPlane)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid);
void setVoidGlobalDrawPlane(void (*VoidGlobalDrawPlane)(float SizeX,float SizeY,float TX,float TY,float R,float G, float B,float A,GLuint TextuteID,int styleNum,int ISactive,bool Enable, bool Vis,int BTid))
{
	this->VoidGlobalDrawPlane = VoidGlobalDrawPlane;
	Enable(isVoidGlobalDrawPlane);
}

//Якщо яка небуть кнопка  зараз зажата іншу не зажимати
bool PressKnopkaONE;

/*

void  PRIVATE_DRAW_MOD(int i, float x,float y,float width, float heigth) //Саме малювання виведено окремо, для зручності створення нових стилів приватна функція
{
	//2019 mod
	// glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,KNopka_[i].ImageKnopki);

	if(isVoidDrawPlane == false) //Якщо 
	DrawPlane(1,1,0,0,KNopka_[i].Color.R,KNopka_[i].Color.G,KNopka_[i].Color.B,KNopka_[i].Color.A,KNopka_[i].ImageKnopki,KNopka_[i].Tip,KNopka_[i].Temp.activ,KNopka_[i].Enabled,KNopka_[i].Vizual,i);
	else
	VoidDrawPlane(1,1,0,0,KNopka_[i].Color.R,KNopka_[i].Color.G,KNopka_[i].Color.B,KNopka_[i].Color.A,KNopka_[i].ImageKnopki,KNopka_[i].Tip,KNopka_[i].Temp.activ,KNopka_[i].Enabled,KNopka_[i].Vizual,i);
	
	return;
}*/

void  PRIVATE_DRAW(int i, float x,float y,float width, float heigth) //Саме малювання виведено окремо, для зручності створення нових стилів приватна функція
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
	if(isVoidDrawPlane == false) //Якщо 
	DrawPlane(1,1,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	else
	VoidDrawPlane(1,1,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	
	return;
}




void  PRIVATE_DRAW(int i) //Саме малювання виведено окремо, для зручності створення нових стилів приватна функція
{
	//2019 mod
	// glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,mObgects[i].ImageKnopki);

	if(isVoidDrawPlane == false) //Якщо 
	DrawPlane(2,2,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	else
	VoidDrawPlane(2,2,0,0,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	
	return;
}


//void  Draw() 
//{
void  Draw(void (*func)(std::string Name,int idObject,int idGrup)) //Малює всі кнопки що зареєстровані в видимих групах і зразу обробляє
{
	Draw();
	MSG_BT(func);
    
}


//Примінити колір
void USColor(PixelRGBA &Color)
{
	glColor4ub(Color.R,Color.G,Color.B,Color.A);
}



//2019 Перевірити чи миша попадає в квадрат
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
			//Розрахунок коефіцієнту розміру 
				float cofX = 2.0f / (float)windows_data.ViewportWidth ;
				float cofY = 2.0f / (float)windows_data.ViewportHeight ;
				float SizeX , SizeY ,PosX ,PosY;
				{
				//Ширина і висота графічного елементу
				 SizeX = ((float)Grups_[id].sizeX*cofX);
				 SizeY = ((float)Grups_[id].sizeY*cofY);
				
				 int pX,pY;
				 GetPosGrup(id,pX,pY);
				// std::cout<<"===========\n";
				// std::cout<<pX<<'\n'<<pY<<'\n';
				 PosX = (((float)pX -(float)windows_data.ViewportPosX + (float)Grups_[id].sizeX/2) * cofX)-1;
				 PosY = (((float)pY -(float)windows_data.ViewportPosY + (float)Grups_[id].sizeY/2) * cofY)-1;

				 //Малюю Тіло вікна========================================================Window===========================================
				 USColor(Grups_[id].BackgroundColor);
				 if(Grups_[id].bacgroundImageURL == "" || Grups_[id].bacgroundImageURL == "NUL" || Grups_[id].bacgroundImageURL == "null")
				 glDisable(GL_TEXTURE_2D);
				 else
				 glBindTexture(GL_TEXTURE_2D,Grups_[id].backgroundImage);
				 DrawPlane(SizeX,SizeY,PosX,PosY,1,1,0,0,mObgects[id].RotationMode);
				 glEnable(GL_TEXTURE_2D);

				 USColor(Grups_[id].HeaderColor);
				 
				 //Розрахувати позицію Хадера
			
				 PosY += SizeY/2;
				 SizeY = (float)Grups_[id].heightHeader *cofY;

				 PosY+=SizeY/2;
				 //Малювати Хеадер
				   if(Grups_[id].bacgroundHeaderImageURL == "" || Grups_[id].bacgroundHeaderImageURL == "NUL" || Grups_[id].bacgroundHeaderImageURL == "null")
					glDisable(GL_TEXTURE_2D);
				   else
				   glBindTexture(GL_TEXTURE_2D,Grups_[id].backgroundHeaderImage);

	
					GetPosGrup(id,pX,pY);



				  // if(ISmauseCvadrat(pX,pY,Grups_[id].sizeX,Grups_[id].PosY))

					{
					
						int mY  = windows_data.WindowsHeight-windows_data.Maus_Data_.MausY_W;
						int mX =  windows_data.Maus_Data_.MausX_W;

						//Перевіряє чи миша над вікном основною облаастю
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY && mY<pY+Grups_[id].sizeY + Grups_[id].heightHeader    )
						{
							if(IdGrupsHoverMain == -1)
							{
								IdGrupsHoverMain = id;
								glColor4f(255,255,0,255);
							}
						}



						if(IdGrupsHoverMain == id)
						//Перевіряє чи курсор миші над полосою вікна 
						if(IdGrupsHoverHight == -1 ) //При умові що ніяке вікно не перекриває
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY+Grups_[id].sizeY && mY<pY+Grups_[id].sizeY+Grups_[id].heightHeader  
							&& windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA  //І Мишкою клікнуто
							&& windows_data.Maus_Data_.PressState == true)
						{
						 //std::cout<<"MouseCLock\n";
							//Ця частина коду виконується тільки в момент кліку
						 TheLastXpsMAuse = windows_data.Maus_Data_.MausX_W;
						 TheLastYpsMAuse = windows_data.Maus_Data_.MausY_W;

						 TheLastXPosWin = Grups_[id].PosX;
						 TheLastYPosWin = Grups_[id].PosY;

						 IdGrupsHoverHight = id;
						}
					}

					if(IdGrupsHoverHight == id)
					{
						//Розраховую зміщення вікна мишею в різних системах координат

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
void DrawGrup(int id) //Тільки промальовка
{

	if(Grups_[id].type == "Window" || Grups_[id].type  == "window")
	{
			//Розрахунок коефіцієнту розміру 
				float cofX = 2.0f / (float)windows_data.ViewportWidth ;
				float cofY = 2.0f / (float)windows_data.ViewportHeight ;
				float SizeX , SizeY ,PosX ,PosY;
				
				//Ширина і висота графічного елементу
				 SizeX = ((float)Grups_[id].sizeX*cofX);
				 SizeY = ((float)Grups_[id].sizeY*cofY);
				
				 int pX,pY;
				 GetPosGrup(id,pX,pY);


				 PosX = (((float)pX -(float)windows_data.ViewportPosX + (float)Grups_[id].sizeX/2) * cofX)-1;
				 PosY = (((float)pY -(float)windows_data.ViewportPosY + (float)Grups_[id].sizeY/2) * cofY)-1;

				 //Малюю Тіло вікна========================================================Window===========================================
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
				 
					 //Розрахувати позицію Хадера
					 PosY += SizeY/2;
					 SizeY = (float)Grups_[id].heightHeader *cofY;
					 PosY+=SizeY/2;

					 //Малювати Хеадер
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
//Для групи обробляю чисто події зміщення взаємодію з користувачем
void EventGrup(int id)
{

	if(Grups_[id].type == "Window" || Grups_[id].type  == "window")
	{
		
				
				 int pX,pY;
				GetPosGrup(id,pX,pY);


					{
					
						int mY  = windows_data.WindowsHeight-windows_data.Maus_Data_.MausY_W;
						int mX =  windows_data.Maus_Data_.MausX_W;

						//Перевіряє чи миша над вікном основною облаастю
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY && mY<pY+Grups_[id].sizeY + Grups_[id].heightHeader    )
						{
							if(IdGrupsHoverMain == -1)
							{
								IdGrupsHoverMain = id;
							}
						}



						if(IdGrupsHoverMain == id)
						//Перевіряє чи курсор миші над полосою вікна 
						if(IdGrupsHoverHight == -1 /*|| IdGrupsHoverHight == id*/) //При умові що ніяке вікно не перекриває
						if(mX>pX && mX<pX+Grups_[id].sizeX   &&    mY>pY+Grups_[id].sizeY && mY<pY+Grups_[id].sizeY+Grups_[id].heightHeader  
							&& windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA  //І Мишкою клікнуто
							&& windows_data.Maus_Data_.PressState == true)
						{
						 //std::cout<<"MouseCLock\n";
							//Ця частина коду виконується тільки в момент кліку
						 TheLastXpsMAuse = windows_data.Maus_Data_.MausX_W;
						 TheLastYpsMAuse = windows_data.Maus_Data_.MausY_W;

						 TheLastXPosWin = Grups_[id].PosX;
						 TheLastYPosWin = Grups_[id].PosY;

						 IdGrupsHoverHight = id;
						
						}
					}


					//std::cout<<IdGrupsHoverMain<<std::endl;

					//Обробка кліків по тілу вікна
					if(IdGrupsHoverMain == id && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA  && windows_data.Maus_Data_.PressState == true)
						 idTheLastPushWindow = id;

					if(IdGrupsHoverHight == id && Grups_[id].ISheader)
					{
						//Розраховую зміщення вікна мишею в різних системах координат

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


void Button_Events(int ID,int idGrup) //Намалювати одну кнопку за ІД
{
 	int i = ID;
	//Private_Rozmis(ID); //Функція розраховує актуальну позицію кнопки і зразу обновлює дані в ній
    mObgects[i].Temp.activ = 0; //Скинути активність 
	mObgects[i].trackBarKaretkaActiv = 0; //Скинути активність для каретки



	if(IdGrupsHoverMain==-1 || IdGrupsHoverMain == idGrup) //Тільки якщо група не перекриває кнопку (група типу вікно)
	{}else return;

	//Розрахувати розміщення кнопки активність і натиски=====================================================================+
	if(mObgects[i].Vizual && mObgects[i].Enabled) //Продовжити тільки якщо кнопка Не вимкнена і Видима
	{	


	if(!kyrsor_na_cnopci) //Продожити якщо протягом цикла ніяку кнопку ще не активували
	{
		//Розраховує и мишку наведено на каретку
		float EndX = mObgects[i].MaxValue - mObgects[i].MinValue;
		float pixVal = (mObgects[i].Value/EndX)*(mObgects[i].SizeX - mObgects[i].trackBarKaretkaSizeX);
		float KaretkaStartX = X_CORD+pixVal ;
		float KaretkaEndX = X_CORD +  mObgects[i].trackBarKaretkaSizeX+pixVal ; 
		float RizN = mObgects[i].trackBarKaretkaSizeY - mObgects[i].SizeY;
		float KaretkaStartY =  (windows_data.ViewportHeight - Y_CORD1) - RizN/2;
		float KaretkaEndY = (windows_data.ViewportHeight - Y_CORD1 + mObgects[i].SizeY) + RizN/2 ; 


		if(windows_data.Maus_Data_.MausX_W> KaretkaStartX && windows_data.Maus_Data_.MausX_W < KaretkaEndX && windows_data.Maus_Data_.MausY_W> KaretkaStartY  && windows_data.Maus_Data_.MausY_W < KaretkaEndY)
		{
			//if(IdGrupsHoverMain==-1 || IdGrupsHoverMain == idGrup) //Тільки якщо група не перекриває кнопку (група типу вікно)
			{
				mObgects[i].trackBarKaretkaActiv = 1;               //Вказує що ця кнопна активна
				kyrsor_na_cnopci = 1;					 //Вказує що ця кнопка активована, і за рахунок цього відбирає право на активацію інших за цей цикл  Тобто робим так щоб не існувало двох активних кнопок одночасно    
			}
		}
		//ENd
	}

	if(!kyrsor_na_cnopci) //Продожити якщо протягом цикла ніяку кнопку ще не активували і каретку
	{

	//Стандартна система для всіх
		float RX =( (float)windows_data.WindowsWidth - (float)windows_data.ViewportWidth)/2;
		float RY =( (float)windows_data.WindowsHeight - (float)windows_data.ViewportHeight);

		int Y_CORD1= Y_CORD - RY + mObgects[i].SizeY;
		if(windows_data.Maus_Data_.MausX_W>X_CORD && windows_data.Maus_Data_.MausX_W < X_CORD +  mObgects[i].SizeX 	&& windows_data.Maus_Data_.MausY_W>   windows_data.ViewportHeight - Y_CORD1 && windows_data.Maus_Data_.MausY_W < windows_data.ViewportHeight - Y_CORD1 + mObgects[i].SizeY)
		{
			//if(IdGrupsHoverMain==-1 || IdGrupsHoverMain == idGrup) //Тільки якщо група не перекриває кнопку (група типу вікно)
			{
				mObgects[i].Temp.activ = 1;               //Вказує що ця кнопна активна
				kyrsor_na_cnopci = true;					 //Вказує що ця кнопка активована, і за рахунок цього відбирає право на активацію інших за цей цикл  Тобто робим так щоб не існувало двох активних кнопок одночасно    
			}
		}

	
		

	}


	
	//Подія затиску
	if(!mObgects[i].Temp.Clic_Temp && mObgects[i].Temp.activ && windows_data.Maus_Data_.PressState == 0 && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA)
	{
		mObgects[i].Temp.Clic_Temp = 1;
		//cout<<i<<"clic\n";
	}



	
	//Якщо активний режим безперепивного подання сигналів
	if(mObgects[i].Avtomatic)
	{
		//Якщо на кнопці зажали кнопку миші
		if(mObgects[i].ClickPress)
		{
			//Ці стрічки провокують сигнал натиску 
			mObgects[i].Temp.Clic_Temp = 0; 
			mObgects[i].Temp.Clic = 0;	
			mObgects[i].Temp.Klik = 1;
		}
	}
	//Якщо активний режим деактивовано для даної кнопки
	else
	//Подія відпуску, але тільки у випадку якщо перед тим був затиск
	if(mObgects[i].Temp.Clic_Temp && mObgects[i].Temp.activ && windows_data.Maus_Data_.PressState == 1 && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA)
	{	
		//Ці стрічки провокують сигнал натиску 
		mObgects[i].Temp.Clic_Temp = 0;
		mObgects[i].Temp.Clic = 0;
		mObgects[i].Temp.Klik = 1;	
	}
	
	}
	//Розрахувати розміщення кнопки активність і натиски=====================================================================-

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



		//Розрахунок зміщення каретки за допомогою миші
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

	



			//Обмежити По максимальному і мінімальному значенню каретку
			if(mObgects[i].Value > mObgects[i].MaxValue)
			mObgects[i].Value = mObgects[i].MaxValue;
			if(mObgects[i].Value < mObgects[i].MinValue)
			mObgects[i].Value = mObgects[i].MinValue;

	//===============================================================Функція виведення на екран і резервування===============+

}

void  Button_Draw(int ID) //Намалювати одну кнопку за ІД
{
 	int i = ID;
	//Private_Rozmis(ID); //Функція розраховує актуальну позицію кнопки і зразу обновлює дані в ній
   

	if(isVoidGlobalDrawPlane)
	{
		VoidGlobalDrawPlane(X_CORD,Y_CORD,mObgects[i].SizeX,mObgects[i].SizeY,mObgects[i].Color.R,mObgects[i].Color.G,mObgects[i].Color.B,mObgects[i].Color.A,mObgects[i].ImageKnopki,0,mObgects[i].Temp.activ,mObgects[i].Enabled,mObgects[i].Vizual,i);
	}
	else
	{
		
		if(!mObgects[i].Temp.Perehvat) //Якщо кнопка не була перехвачена,малюю її
		{
				DrawStyleElements(i,X_CORD,Y_CORD,mObgects[i].SizeX,mObgects[i].SizeY);		
		}
	}





	mObgects[i].Temp.Perehvat = 0; //Скидання
}



void draw_grup_and_button(int idG)
{
	int j = idG;


	//Якщо група не видима допобачення
	if(!Grups_[j].vizual) return;

	//Тіло вікна
	DrawGrup(j); //Малювати вікно якщо група являється вікном

	

									//Цикл обробки подій (Внутрішні події обробляються окремо у зворотньому напрямку для того щоб натиски спрацьовували не на тих кнопка що на задньому плані а на кнопках переднього плану)
									if(Grups_[j].Enable == 1 )
									{
										for(int i = Grups_[j].ID_Objects.size()-1;i>=0;i--) //Обробити всі кнопки з групи в зворотьньому напрямку
										{
											if(mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob == 0) //Якщо кнопка не оброблялася
											{
												if(Grups_[j].type == "Window" || Grups_[j].type == "window")
													FixWindow_Private_Size(Grups_[j].ID_Objects[i],j, X_CORD , Y_CORD);
												else
													Private_Rozmis(Grups_[j].ID_Objects[i]);

												Button_Events(Grups_[j].ID_Objects[i],j); 
											}
										}
									}


									//Цикл Промальвки
									for(int i = 0;i<Grups_[j].ID_Objects.size();i++) //обробити записані ідентифікатори
									if(mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob == 0) //Якщо кнопка не оброблялася
									{//**Обробити кнопку
										//mObgects[Grups_[j].ID_Objects[i]].Temp.Temp_obrob = 1; //Вказуємо що кнопка оброблена (Запобігає малюванню кнопки двічі Якщо вона зареєстрована в двох групах)
										//Button_Events(Grups_[j].ID_Objects[i]); 
										//
									if(Grups_[j].type == "Window" || Grups_[j].type == "window")
										FixWindow_Private_Size(Grups_[j].ID_Objects[i],j, X_CORD , Y_CORD);
									else
										Private_Rozmis(Grups_[j].ID_Objects[i]);

										Button_Draw(Grups_[j].ID_Objects[i]); 
									}//**
									
	

}

void  Draw() //Валює всі кнопки що зареєстровані в видимих групах
{
	//Передаю параметри вікна классу шрифтів
	FontSystems.WindowsData.ViewportHeight = windows_data.ViewportHeight;
	FontSystems.WindowsData.ViewportWidth =  windows_data.ViewportWidth;
	FontSystems.WindowsData.ViewportPosX =   windows_data.ViewportPosX;
	FontSystems.WindowsData.ViewportPosY =   windows_data.ViewportPosY;
	FontSystems.WindowsData.WindowsHeight =  windows_data.WindowsHeight;
	FontSystems.WindowsData.WindowsWidth =   windows_data.WindowsHeight;

	if(windows_data.Maus_Data_.PressState == false && windows_data.Maus_Data_.MausBT == BT_MAUSE_KLIK_KNOPKA) //Обнуляти Ід активного вікна тільки при умові що кнопку миші не зажато
	{
		IdGrupsHoverHight = -1;
		IdGrupsHoverMain = -1;
	}


	//Цикл обробки подій внутрішніх

	//Спочатку обробляємо активну групу
	if(idTheLastPushWindow != -1)
		if(Grups_[idTheLastPushWindow].vizual == 1)
			EventGrup(idTheLastPushWindow);

	for(int j = Grups_.size()-1;j>=0;j--)
		{
			if(Grups_[j].vizual == 1) //якщо група видима і активна
			{
				if(idTheLastPushWindow != j)
				EventGrup(j);
			}
		}
	
 
	//Активую Прозорість
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	kyrsor_na_cnopci = 0;
	VSTAN_ZMIN_T_OBROB(0); //Onul

		//int j = 0;
		//while(j<Grups_.size()) //пройтись по всім групам
		
	
		for(int j = 0;j<Grups_.size();j++)
		{
			if(Grups_[j].vizual == 1) //якщо група видима і активна
			{
				if(j != idTheLastPushWindow)
				draw_grup_and_button(j); //Малювати групу  і її вміст
			}
		}

		if(idTheLastPushWindow != -1)
			draw_grup_and_button(idTheLastPushWindow);



		//2019 comment
		//if(textEnable)  //Якщо вказано що текст потрібен
		//TextDraw();  	//Вивидення тексту

}



bool  SaveToFile_BT(std::string URL_name) //Функція зберігає всю графічну систему у файл, для змоги подальшого використання для ініціалізації
{
	std::ofstream Strim1(URL_name.c_str());
	if(!Strim1) return 0; //eror create file
	Strim1<<"Version 1.6\n";

	//======================Записую групи======================//
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
		while(J < Grups_[i].ID_Objects.size()) //Записую кылькількість і ідентифікатори
		{
		Strim1<<' '<<Grups_[i].ID_Objects[J];
		J++;
		}
		Strim1<<'\n'<<"Grup_End"<<"\n\n";
		i++;
	}

	Strim1<<"\n";
	//======================Записую Кнопки======================//
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
	//=======================Закінчти читання
	Strim1<<"Form_Init_End";



	Strim1.close();
	return 1;
}

bool chislo_znp(char A) //перевіряє чи символ це число
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


//Список прочитаних слів які можуть бути командами або аргументами до команд

//Запис всіх помилок
std::vector<std::string> ErrorLog;

std::vector<std::string> ReadFile;
bool ReadWordComands(std::string URL)
{
	URL = korin_dir + URL;
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
		ReadFile.push_back(Comand); //Записую команду у вектор для подальшої обробки

		if(ReadFile.size()>=2)
		{
			if(ReadFile[ReadFile.size()-2] == "include")
			{
				std::string tempURL =  ReadFile[ReadFile.size()-1];
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
	//Вимикаємо користувацьку функцію на правах конструктора
	//Disable(textureLoader.ISusTextureLoader);
	//Disable(isVoidDrawPlane);
	Disable(isVoidDrawPlane);
	Disable(isVoidGlobalDrawPlane);
	
	//Функція для завантажена текстур при потребі розширити підтримук типів текстур визначається користувачем
	//bool (*usTextureLoader)(std::string url, int &width, int &height, GLuint &TxID);

	string vertexS = "";


	textEnable = 1;
	OBGECT BT_K_TEMP = Knopka_IN();                 //Допоміжна змінна яка налаштовуєтся а потім вкидаєтся її копія в вектор кнопок
	Grup  BT_G_TEMP = Grup_IN();
	BT_MAUSE_KLIK_KNOPKA = 0;                       //якщо сигнал від glut то ліва кнопка миші по стандарту
	windows_data.Maus_Data_ .PressState = 0;
	windows_data.Maus_Data_ .MausBT = -1;







}

/*
bool  Open(std::string dir, std::string name)
{
	korin_dir = dir;
	return Open(name);
}*/

bool  Open(std::string URL_name) //Функція читатимефаіл форм
{
	

	//Алгоритм розділення адреси кориневої папки і назви фалу
	{
	std::string Dir = URL_name;
	std::string File = "";
	while(Dir.size()>0 && Dir[Dir.size()-1] != '\\')
	{
		File+=Dir[Dir.size()-1];
		Dir.erase(Dir.size()-1);
	}

	std::string RFile = "";
	while(File.size()>0)
	{
		RFile+=File[File.size()-1];
		File.erase(File.size()-1);
	}
	

	korin_dir = Dir;
	URL_name = RFile;

	
	}
	
	



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

	//Область Ініціалізації
	int i = 0;
	while(i < ReadFile.size())
	{

		//============================================================================================
		//======================14.11.2017============================================================
		//============================================================================================


		
	//Кнопки
		if(ReadFile[i] == "Object_Begin")                                       {BT_K_TEMP = Knopka_IN();}
		else
			//2019
			if(ReadFile[i] == "Object_Copy")										  {i++;      for(int j = 0; j < mObgects.size(); j++) {if(mObgects[j].Names == ReadFile[i]){BT_K_TEMP = mObgects[j]; break;}}  } //Скопіювати властивості з іншої кнопки по назві якщо така уже є
		
			
			
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
				if(ReadFile[i] == "Object_HoverFix") //Параметри змін при наведенні устанивити такими як і стандартні
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
				i++;                                                   //Наступне значення
				ComandVector ComandVectorTemp1;                        //Темчасова змінна для збереження
				ComandVectorTemp1.Comand_FUNC = ReadFile[i];           //Зберегти назву функції
				i++;                                                   //Наступне значення

				int SizeMax = StringToInt(ReadFile[i]);                //Кількість значень
				int U = 0;
				while(U<SizeMax)                                       //Пойти по всім значенням
				{
					i++;                                               //Наступне значення
					if(chislo_znp(ReadFile[i][0]))                     //Якщо значення число
						ComandVectorTemp1.ArgLine.push_back(StringToInt(ReadFile[i]));          //Зберегти числове значення
					else                             
						ComandVectorTemp1.ComandLine.push_back(ReadFile[i]);                    //Зберегти текстове значення*/
					U++;		
				}
				

				if(ComandVectorTemp1.ComandLine.size()+ComandVectorTemp1.ArgLine.size() >0)
				{	
					BT_K_TEMP.Comanda.push_back(ComandVectorTemp1);     //Зберегти команду
				}
		    }//Читання команд
			

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
        //Групи
		if(ReadFile[i] == "GrupNew_Begin" || ReadFile[i] == "Grup_Begin")                    BT_G_TEMP = Grup_IN();													//Стандартні налаштування сброс
		else
		if(ReadFile[i] == "GrupName" || ReadFile[i] == "Grup_Name")                         {i++; BT_G_TEMP.Name = ReadFile[i]; }										//Ім'я групи
		else
		if(ReadFile[i] == "GrupEnable" || ReadFile[i] == "Grup_Enable")						  {i++; BT_G_TEMP.Enable = StringToBool(ReadFile[i]);}						//Активність
		else
		if(ReadFile[i] == "GrupVizual" || ReadFile[i] == "Grup_Vizual")                       {i++; BT_G_TEMP.vizual = StringToBool(ReadFile[i]);}						//Видимість
		
		//=======================================2019
		/////////////////////////////////////////////
		else
		if(ReadFile[i] == "Grup_Type" || ReadFile[i] == "Grup_type")                         {i++; BT_G_TEMP.type = ReadFile[i]; }	 //Тип групи

		if(ReadFile[i] == "Grup_PosX")                                           {i++;   BT_G_TEMP.PosX = StringToInt(ReadFile[i]);} //Позиція якщо група вважається вікном або панеллю
		else
		if(ReadFile[i] == "Grup_PosY")                                           {i++;   BT_G_TEMP.PosY = StringToInt(ReadFile[i]);}
		else
			if(ReadFile[i] == "Grup_ISheader")						  {i++; BT_G_TEMP.ISheader = StringToBool(ReadFile[i]);}						//Чи показувати допоміжну полосу вікна
		else
			if(ReadFile[i] == "Grup_IStitle")                       {i++; BT_G_TEMP.IStitle = StringToBool(ReadFile[i]);}						//Чи показувати назву вікна
		else
			if(ReadFile[i] == "Grup_Title")                         {i++; BT_G_TEMP.title = ReadFile[i]; }	 //Назва вікна
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
		if(ReadFile[i] == "Grup_Copy")										  {i++;      for(int j = 0; j < Grups_.size(); j++) {if(Grups_[j].Name == ReadFile[i]){  BT_G_TEMP = Grups_[j]; break;}}   BT_G_TEMP.ID_Objects.clear();  } //Скопіювати властивості з іншої групи по назві якщо така уже є
		
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
		if(ReadFile[i] == "GrupID_Objects")			          {																			//Читання зареєстрованих ідентифікаторів кнопок
																 i++;
			                                                     int j = 0, k = StringToInt(ReadFile[i]);
																 																 
																 while(k > j)
																 {
																	 i++;  
																	 
																	 if(chislo_znp(ReadFile[i][0]))    //Обробити залежно від того чи число надійшло чи назва
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
																	//Додати кнопку в групу по параметру при створенны кнопки 2018
																	for(int g = 0;g < TlogBtToGrupsLog.size();g++)
																	{
																		if(TlogBtToGrupsLog[g].NameGrup == BT_G_TEMP.Name) //Шукаємо групу по імені
																		{
																		 int ID_T =  ID_names(TlogBtToGrupsLog[g].NameBT); //Шукаємо об'єкт по назві
																	    
																		 if(ID_T >= 0) //Якщо ідентифікатор більше -1 Обеэт знайдено 
																		 {
																			 bool vvvv = 1;
																			 for(int t = 0; t < BT_G_TEMP.ID_Objects.size();t++) //Пройдемоя по записаних індефікаторах в групи
																			 {
																				 if(BT_G_TEMP.ID_Objects[t] == ID_T)  //і якщо цей індефікатор там вже є
																				 {
																					 vvvv = 0; //Вказуэмо що йог зберыгати не потрыбно вдруге
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
																	//Завантажую текстуру вікна якщо вона є
																	
																	if(BT_G_TEMP.bacgroundImageURL != "" && BT_G_TEMP.bacgroundImageURL != "NULL" && BT_G_TEMP.bacgroundImageURL != "null")
																	{
																	bool Suses = textureLoader.Knopka_LoadTexture(BT_G_TEMP.backgroundImage,    korin_dir +     BT_G_TEMP.bacgroundImageURL.c_str());
																	}

																	if(BT_G_TEMP.bacgroundHeaderImageURL != "" && BT_G_TEMP.bacgroundHeaderImageURL != "NULL" && BT_G_TEMP.bacgroundHeaderImageURL != "null")
																	{
																	bool Suses = textureLoader.Knopka_LoadTexture(BT_G_TEMP.backgroundHeaderImage,    korin_dir +     BT_G_TEMP.bacgroundHeaderImageURL.c_str());
																	}
			
																	Grups_.push_back(BT_G_TEMP); BT_G_TEMP.ID_Objects.clear();
																	
		}											//Зберігаю групу
		else
		if(ReadFile[i] == "Form_Init_End")                                         break;
	//=================================================================================================
		i++;
	}
	

	
	return 1;
}



//Функції для отримання порту перегляду
int  Get_glViewport_BT(std::string Name,bool Avto_Perspective,int fovy,int Zfar)
{
	int ID = ID_names(Name);
	if(ID < mObgects.size() && ID >=0)
	Get_glViewport_BT(ID,Avto_Perspective,fovy,Zfar);
	else
	return -1;

	return ID;
}
	//Функції для отримання порту перегляду
	int  Get_glViewport_BT(int ID,bool Avto_Perspective,int fovy,int Zfar)
	{
		if(Avto_Perspective) 
		gluPerspective(fovy,(float)mObgects[ID].SizeX/(float)mObgects[ID].SizeY,1,Zfar);

		//gluPerspective(30,1,1,200);

	    Private_Rozmis(ID);
		glViewport(X_CORD,Y_CORD,mObgects[ID].SizeX,mObgects[ID].SizeY);
		mObgects[ID].Temp.Perehvat = 1; //Вказую що область цієї кнопки була вжевикористана
		return ID;
	}


	void  GrupEnable(std::vector<int>ID,bool State) //Активувати або деактивувати групи = груповий пакет
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].Enable = State;
			i++;
		}
		//return ID;
	}
	/*void  GrupEnable(int ID,bool State) //Активувати або деактивувати групи
	{
		Grups_[ID].Enable = State;
	}*/


		void  GrupVisual(std::vector<int>ID,bool State) //Видимість = груповий пакет
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].vizual = State;
			i++;
		}
	}
/*	void  GrupVisual(int ID,bool State) //Видимість групи
	{
		Grups_[ID].vizual = State;
	}*/














		void  GrupEnableInsert(std::vector<int>ID,bool State) //Активувати або деактивувати групи = груповий пакет Всі окрім
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

		void  GrupVisualInsert(std::vector<int>ID,bool State) //Видимість = груповий пакет Всі окрім
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



	void  GrupEnableAll(bool State) //Задіяти команду для усіх груп
	{
		int j = 0;
		while(Grups_.size() > j)
		{ 
			Grups_[j].Enable = State;
			j++;
	    }
		//return ID;
	}

		void  GrupVisualAll(bool State) //Задіяти команду для усіх груп
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
	void  GrupEnable(std::vector<std::string>ID,bool State) //Активувати або деактивувати групи = груповий пакет
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].Enable = State;
			i++;
		}
		//return ID;
	}
	/*void  GrupEnable(int ID,bool State) //Активувати або деактивувати групи
	{
		Grups_[ID].Enable = State;
	}
	

	void  GrupVisual(std::vector<int>ID,bool State) //Видимість = груповий пакет
	{
		int i = 0;
		while(ID.size()>i)
		{
			Grups_[ID[i]].vizual = State;
			i++;
		}
		//return ID;
	}
	/*void  GrupVisual(int ID,bool State) //Видимість групи
	{
		Grups_[ID].vizual = State;
	}*/












	// ID_GRUP_NAME(std::string Name)
	
		void  GrupEnableInsert(std::vector<std::string>ID,bool State) //Активувати або деактивувати групи = груповий пакет Всі окрім
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
		
		void  GrupVisualInsert(std::vector<std::string>ID,bool State) //Видимість = груповий пакет Всі окрім
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
	
		void  GrupEnable(std::vector<std::string>ID,bool State) //Активувати або деактивувати групи = груповий пакет
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

		

	void  GrupVisual(std::vector<std::string>ID,bool State) //Видимість = груповий пакет
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








void  GrupVisualInsert(std::vector<std::string>ID,std::vector<int>ID1,bool State) //Видимість = груповий пакет Всі окрім
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
	




void  GrupEnableInsert(std::vector<std::string>ID,std::vector<int>ID1,bool State) //Видимість = груповий пакет Всі окрім
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

	


void  GrupEnableInsertRevers(std::vector<std::string>ID,std::vector<int>ID1) //Видимість = груповий пакет Всі окрім
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

void  GrupVisualInsertRevers(std::vector<std::string>ID,std::vector<int>ID1) //Видимість = груповий пакет Всі окрім
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


	void  GrupEnableRevers(std::vector<std::string>ID,std::vector<int>ID1) //Активувати або деактивувати групи = груповий пакет
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

		

	void  GrupVisualRevers(std::vector<std::string>ID,std::vector<int>ID1) //Видимість = груповий пакет
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



