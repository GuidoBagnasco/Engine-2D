#include "Importer.h"
#include "Scene.h"
#include "Sprite.h"
#include "Quad.h"
#include "animation.h"
#include "TileMap.h"
#include "Tile.h"
#include "Renderer.h"

using namespace engine;


Importer* Importer::m_oInstance = NULL;


Importer::Importer() : m_oRenderer(NULL) {

}

bool Importer::Init(Renderer& r) {
	if (&r == NULL) return false;
	m_oRenderer = &r;
	m_oInstance = this;	// Seteo mi singleton a this!
	return true;
}


Renderer* Importer::GetRenderer() const {
	return m_oRenderer;
}


bool Importer::importScene(Scene& mScene, std::string fileName) {
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	if (xmlDoc.Error())
		return false;

	tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("SCENE");
	std::string colGroup;

	importSprite(colGroup, mScene, root);
	importQuad(colGroup, mScene, root);
	importTileMap(colGroup, mScene, fileName.c_str());
	return true;
}


void Importer::importSprite(std::string& colGroup, Scene& mScene, tinyxml2::XMLElement* root) {
	tinyxml2::XMLElement *sprite = root->FirstChildElement("SPRITE");
	tinyxml2::XMLElement *instance = root->FirstChildElement("INSTANCE");

	while (sprite != NULL){
		std::string spriteName = sprite->Attribute("name");
		std::string texturePath = sprite->Attribute("texture");
		int r = sprite->IntAttribute("r");
		int g = sprite->IntAttribute("g");
		int b = sprite->IntAttribute("b");

		engine::Texture texture = loadTexture( texturePath, engine_COLOR_RGB(r, g, b) );

		// Crear animaciones...
		std::vector<Animation*> listAnim;

		importAnimations(listAnim, sprite->FirstChildElement("ANIMATION"));

		instance = root->FirstChildElement("INSTANCE");
		while (instance != NULL){
			
			if (instance->Attribute("sprite") == spriteName){
				std::string sName = instance->Attribute("name");
				float posX = instance->FloatAttribute("posX");
				float posY = instance->FloatAttribute("posY");
				float rotation = instance->FloatAttribute("rotation");
				float scaleX = instance->FloatAttribute("scaleX");
				float scaleY = instance->FloatAttribute("scaleY");
				colGroup = instance->Attribute("layer");

				Sprite* entity = new Sprite();

				entity->setPos(posX, posY);
				entity->setName(sName);
				entity->setRotation(rotation);
				entity->setScale(scaleX, scaleY);
				entity->setTexture(texture);
				entity->setCollisionGroup(colGroup);

				for (int i = 0; i < listAnim.size(); i++){
					entity->AddAnimation(listAnim[i]);
				}

				if (listAnim.size())
					entity->setAnimation(listAnim[0]);
				
				mScene.Add(sName, entity);
				mScene.AddClsGroup(colGroup);
				mScene.AddEntityToClsGroup(entity, colGroup);
			}

			instance = instance->NextSiblingElement("INSTANCE");
		}
		sprite = sprite->NextSiblingElement("SPRITE");
	}
}


void Importer::importQuad(std::string& colGroup, Scene& mScene, tinyxml2::XMLElement* root){
	tinyxml2::XMLElement *quad = root->FirstChildElement("QUAD");

	while (quad != NULL){
		//CREO QUAD
		Quad  * ent_quad = new Quad();

		std::string name = quad->Attribute("name");
		float posX = quad->FloatAttribute("posX");
		float posY = quad->FloatAttribute("posY");
		float rotation = quad->FloatAttribute("rotation");
		float scaleX = quad->FloatAttribute("scaleX");
		float scaleY = quad->FloatAttribute("scaleY");
		int r = quad->IntAttribute("r");
		int g = quad->IntAttribute("g");
		int b = quad->IntAttribute("b");

		ent_quad->setName(name);
		ent_quad->setPos(posX, posY);
		ent_quad->setRotation(rotation);
		ent_quad->setScale(scaleX, scaleY);
		ent_quad->setColor(engine_COLOR_RGB(r, g, b));

		//PUSH_BACK A LISTA ENTITY2D
		mScene.Add(name, ent_quad);

		quad = quad->NextSiblingElement("QUAD");
	}
}


void Importer::importAnimations(std::vector<Animation*>& list, tinyxml2::XMLElement* animations){
	while (animations != NULL)
	{
		//CREATE ANIMATION AUX
		Animation *anim = new Animation();

		std::string name = animations->Attribute("name");
		float lenght = animations->FloatAttribute("length");
		float t_width = animations->FloatAttribute("width");
		float t_height = animations->FloatAttribute("height");

		anim->setName(name);
		anim->setLength(lenght);

		tinyxml2::XMLElement *frame = animations->FirstChildElement("FRAME");
		while (frame != NULL)
		{
			float posX = frame->FloatAttribute("posX");
			float posY = frame->FloatAttribute("posY");
			float width = frame->FloatAttribute("width");
			float height = frame->FloatAttribute("height");

			//ADDFRAME (t_width, t_height, posX, posY, width, height);
			anim->addFrame(t_width, t_height, posX, posY, width, height);

			frame = frame->NextSiblingElement("FRAME");
		}
		// PUSH_BACK ANIMATION
		list.push_back(anim);

		animations = animations->NextSiblingElement("ANIMATION");
	}
}


Texture Importer::loadTexture(std::string path, int KeyCode){
	if (!m_mTextureMap.count(path)){
		Texture t = m_oRenderer->loadTexture(path, KeyCode);
		m_mTextureMap[path] = t;
		return t;
	}

	return m_mTextureMap[path];
}


void Importer::importTileMap(std::string& colGroup, Scene& kScene, const char* path){
	XMLResults r;
        XMLNode kTopNode = XMLNode::parseFile(path, "SCENE", &r);
        //cuento la cantidad de nodos tilemaps

        int iTileMapCount = kTopNode.nChildNode("TILEMAP");

        for (int i = 0 ; i < iTileMapCount; i++)
        {
                XMLNode kTileMapNode = kTopNode.getChildNode("TILEMAP", i);
				TileMap* t = LoadTileMap(colGroup, kScene, kTileMapNode);
				kScene.AddTileMap(t->GetName(), t);
        }
}


TileMap* Importer::LoadTileMap(std::string colGroup, Scene& kScene, XMLNode& kTileMapNode) {
    /* <TILEMAP Name= >
                            <TILESET Texture= "bla bla xml">
                            <TILES Path= blabla.xml>
        <TILEMAP/>*/
    std::vector<Texture> vTileSets;

	struct Vector2{
		int x,y;
	};

	std::vector<Vector2> vTextSizes;

	XMLNode kTilesNode = kTileMapNode.getChildNode("TILES");

	const char* TilesDataPath = kTilesNode.getAttribute("Path");

	//parseo el archivo creado por los editores.
	XMLNode kTileMapDataNode = XMLNode::parseFile(TilesDataPath, "map");
	XMLNode kTilesetNode = kTileMapDataNode.getChildNode("tileset");
	XMLNode kimageNode = kTilesetNode.getChildNode("image");
	int iTileSetsCount = kTilesetNode.nChildNode("image");
	//int iTileSetsCount = kTileMapNode.nChildNode("TILESET");

    // cargo las texturas de los tilesets.
    for (int i = 0 ; i < iTileSetsCount; i++)
    {
		//XMLNode kTileSetNode = kTileMapNode.getChildNode("TILESET", i);
		const char* TextureName = kTilesetNode.getAttribute("name");
		int w = atoi(kimageNode.getAttribute("width"));
		int h = atoi(kimageNode.getAttribute("height"));

		//XMLNode kTextureNode = XMLNode::parseFile(TextureName, "TEXTURE"); // aca deberia ir image
                
		vTileSets.push_back(LoadTexture(kimageNode, TextureName));
		Vector2 v;
		v.x = w;
		v.y = h;
		vTextSizes.push_back(v);
	}

    const char* TMname = kTileMapNode.getAttribute("Name");

    //me fijo si ya existe uno con ese nombre.
    if(m_mTilemaps.count(TMname))
    {
		return m_mTilemaps[TMname];
    }

    TileMap * kTileMap = new TileMap(TMname);
    //lo agrego al mapa
    m_mTilemaps[kTileMap->GetName()] = kTileMap;
       
    const char* mapCols = kTileMapDataNode.getAttribute("width");
    const char* mapRows =kTileMapDataNode.getAttribute("height");

    unsigned int uiMapCols = atoi(mapCols);
    unsigned int uiMapRow = atoi(mapRows);

    kTileMap->SetColRows(uiMapCols, uiMapRow);
        
    const char* tileWidth  = kTileMapDataNode.getAttribute("tilewidth");
    const char* tileHeight = kTileMapDataNode.getAttribute("tileheight");

    //cuento la cantidad de layers
    int iLayercount = kTileMapDataNode.nChildNode("layer");

    for (int i = 0; i < iLayercount; i++) // seguir aca con tiled
    {
        kTileMap->AddLayer();
        XMLNode kLayerNode = kTileMapDataNode.getChildNode("layer",i);
        XMLNode kDataNode = kLayerNode.getChildNode("data");

		std::string sLayerName = kLayerNode.getAttribute("name");

		std::string PropertyD = "Collidable";

		bool Collidable = false;

		int propertiesCount = kLayerNode.nChildNode("properties");
		if (propertiesCount != 0) {	// Tiene properties

			XMLNode kPropertiesNode = kLayerNode.getChildNode("properties");
			propertiesCount = kPropertiesNode.nChildNode("property");

			for (int p = 0; p < propertiesCount; p++) {
				XMLNode Property = kPropertiesNode.getChildNode("property", p);
				const char* propertyName = Property.getAttribute("name"); // Collidable

				if (PropertyD.find(propertyName) != std::string::npos) {
					//Collidable = true;

					kTileMap->AddCollisionLayer(sLayerName, i);

				}
			}
		}

        int iTileCount = kDataNode.nChildNode("tile");

        for (int j = 0; j < iTileCount; j++)
        {
            XMLNode kTileNode = kDataNode.getChildNode("tile",j);
            const char* cId = kTileNode.getAttribute("gid");
            unsigned int uiTileId = atoi(cId);

            //si es 0 no tiene que buscar que textura usa.
            if(uiTileId != 0)
            {
                //busco que textura usa ese tile
                int iTextureId = -1;
                XMLNode kTileSetNode;
                                
                int k = vTileSets.size()-1; 
                while (iTextureId == -1)
                {
                    kTileSetNode = kTileMapDataNode.getChildNode("tileset", k);
                    const char* cFirst = kTileSetNode.getAttribute("firstgid");
                    int iFirstGid = atoi(cFirst);

                    if(uiTileId >= iFirstGid)
                    {
                        uiTileId -= iFirstGid;
                        iTextureId = k;
                    }
                    k--;
                }
								
				Tile * temp = CreateTile(kTileSetNode, vTileSets[iTextureId], uiTileId, vTextSizes[iTextureId].x, vTextSizes[iTextureId].y);
				if (Collidable)
				{
					temp->setCollisionGroup(sLayerName);
					kScene.Add("Tile " + uiTileId, temp);
					kScene.AddClsGroup(sLayerName);
					kScene.AddEntityToClsGroup(temp, sLayerName);
				}
				kTileMap->AddTile(temp, i);
            }
            else //si es 0
                 kTileMap->AddTile(NULL,i);
        }
    }

    return kTileMap;
}

//--------------------------------------------------------------------------------

Tile* Importer::CreateTile(XMLNode& kTileSetNode, Texture pkTexture, unsigned int iId, int textWidth, int textHeight) {
        const char* tileWidth = kTileSetNode.getAttribute("tilewidth");
        const char* tileHeight = kTileSetNode.getAttribute("tileheight");

        unsigned int uiTileWidth = atoi(tileWidth);
        unsigned int uiTileHeight = atoi(tileHeight);

		Tile* kTile = new Tile(iId, uiTileWidth, uiTileHeight);
		kTile->setTexture(pkTexture);
		kTile->setScale(uiTileWidth, uiTileHeight);

        unsigned int uiTextureWidth = textWidth;
        unsigned int uiTextureHeight = textHeight;

        unsigned int uiPosX;
        unsigned int uiPosY;
        
		unsigned int uiSpacing = 0;
		unsigned int uiMargin = 0;

		if(kTileSetNode.isAttributeSet("spacing") != 0){
			const char* Spacing = kTileSetNode.getAttribute("spacing");
			uiSpacing = atoi(Spacing);
		}

		if(kTileSetNode.isAttributeSet("margin") != 0){
			const char* Margin = kTileSetNode.getAttribute("margin");
			uiMargin = atoi(Margin);
		}


        //calcula la cantidad de tiles por fila.
        unsigned int uiTilesPerRow = 0;
        int aux = uiTextureWidth -uiMargin;
        while (aux >= (int)uiTileWidth) {
                aux -= uiTileWidth;
                uiTilesPerRow++;
                aux-= uiSpacing;
        }

        //calculo columna y fila a partir del indice.
        int col = iId;
        int row = 0;
        while(col >= uiTilesPerRow)
        {
            col -= uiTilesPerRow;
            row++;
        }

        uiPosX = uiMargin + col * (uiTileWidth + uiSpacing);
        uiPosY = uiMargin+ row * (uiTileHeight + uiSpacing);

		kTile->SetSpriteArea(uiPosX, uiPosY, uiTileWidth, uiTileHeight, textWidth, textHeight);

        return kTile;
}


Texture Importer::LoadTexture(XMLNode& kTextureNode, const char* textureName)
{
    // se fija si existe, si existe lo retorna, si no lo crea.
    if (m_mTextureMap.count(textureName))
    {
            return m_mTextureMap[textureName];
    }
        
	//toma al path a la imagen en si.
    std::string sFilePath = kTextureNode.getAttribute("source");

	int keycode = 0;

	if (kTextureNode.isAttributeSet("trans") != 0)
	{
		keycode = colorConverter(kTextureNode.getAttribute("trans"));
	}
		
	Texture text = m_oRenderer->loadTexture(sFilePath, keycode);
	m_mTextureMap[textureName] = text;
    return text;
}


int Importer::colorConverter(const char* hexValue) {
	int r, g, b;
	sscanf(hexValue, "%02x%02x%02x", &r, &g, &b);
	return engine_COLOR_RGB(r, g, b);
}