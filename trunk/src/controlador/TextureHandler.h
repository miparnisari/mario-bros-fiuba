#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include "../other/Logger.h"
#include <string>
#include <map>
using namespace std;
class TextureHandler
{
	public:
		TextureHandler(string texError);
		~TextureHandler();
		string getTextura(string tag);
		void addTextura(string tag, string ruta);
		
	
	private:
		string error;
		static const string TAG;
		map <string, string>* texturas;
};

#endif /* TEXTUREHANDLER_H */ 
