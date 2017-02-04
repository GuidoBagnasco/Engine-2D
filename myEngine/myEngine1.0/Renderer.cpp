#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"

using namespace engine;


Renderer::Renderer():
d3d(NULL),
d3d_dev(NULL),
p_vb(NULL),
p_vTexture(NULL)
{
	// Again, Nothing to do.
}


Renderer::~Renderer(){
	if(p_vb){
		delete p_vb;
		p_vb = NULL;
	}

	if (p_vTexture){
		delete p_vTexture;
		p_vTexture = NULL;
	}

	if(d3d_dev){
		d3d_dev->Release();
		d3d_dev = NULL;
	}

	if(d3d){
		d3d->Release();
		d3d = NULL;
	}
	
	for (std::vector<Texture>::iterator it = m_vTexture.begin(); it != m_vTexture.end(); it++){
		(*it)->Release();
		(*it) = NULL;
	}
	
	m_vTexture.clear();
}


bool Renderer::Init(HWND _HwnD){
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = _HwnD;
	if(d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _HwnD, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d_dev) == D3D_OK){
		d3d_dev->SetRenderState(D3DRS_LIGHTING,FALSE);
		d3d_dev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

		d3d_dev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3d_dev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3d_dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		d3d_dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
		
		D3DVIEWPORT9 kViewport; //CAMARA 
		d3d_dev->GetViewport(&kViewport);

		float fViewPortWidth = static_cast<float>(kViewport.Width);
		float fViewPortHeight = static_cast<float>(kViewport.Height);
		
		D3DXMATRIX projectionMatrix;  //MATRIX PROYEC...
		D3DXMatrixOrthoLH(&projectionMatrix,fViewPortWidth,fViewPortHeight, -1.0f, 1.0f);
		
		d3d_dev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);


		p_vb = new engine::VertexBuffer(d3d_dev, sizeof(engine::ColorVertex), engine::ColorVertexType);
		p_vTexture = new engine::VertexBuffer(d3d_dev, sizeof(engine::TextureVertex), engine::TextureVertexType);
		
		return true;
	}
	return false;
}


void Renderer::SwitchLightning()
{
	DWORD value;
	d3d_dev->GetRenderState(D3DRS_LIGHTING,&value);
	if ((bool)value)
	{
		d3d_dev->SetRenderState(D3DRS_LIGHTING, false);
	}
	else
	{
		d3d_dev->SetRenderState(D3DRS_LIGHTING, true);
	}
}


void Renderer::BeginFrame(){
	d3d_dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(r,g,b), 1.0f, 0);
	d3d_dev->BeginScene();
}


void Renderer::SetBackgroundColor(short _r,short _g, short _b)
{
	r = _r;
	g = _g;
	b = _b;
}


void Renderer::EndFrame(){
	d3d_dev->EndScene();
	d3d_dev->Present(NULL,NULL,NULL,NULL);
}


D3DPRIMITIVETYPE primitiveMap[engine::PrimitiveCount] = {
        D3DPT_TRIANGLELIST, 
        D3DPT_TRIANGLESTRIP,
        D3DPT_POINTLIST,
        D3DPT_LINELIST,     
        D3DPT_LINESTRIP,
        D3DPT_TRIANGLEFAN
};


D3DTRANSFORMSTATETYPE MatrixTypeMapping[MatrixTypeCount] ={
 D3DTS_VIEW,
 D3DTS_PROJECTION,
 D3DTS_WORLD
};


void Renderer::setMatrix(MatrixType matrixType, const Matrix& matrix){
	d3d_dev->SetTransform(MatrixTypeMapping[matrixType], matrix);
}


void Renderer::Draw(ColorVertex* /*DIBUJA QUAD*/ v, engine::Primitive p, size_t vC){
	p_vb->bind();
	p_vb->draw(v,primitiveMap[p], vC);
}


void Renderer::Draw(TextureVertex*/*DIBUJA LA TEXTURA*/ v, engine::Primitive p, size_t vC){
	p_vTexture->bind();
	p_vTexture->draw(v, primitiveMap[p], vC);
}


const Texture Renderer::loadTexture(const std::string& Fname, int KeyCode){
	IDirect3DTexture9* p_Texture = NULL;
	HRESULT HR = D3DXCreateTextureFromFileEx(d3d_dev,
		Fname.c_str(),
		0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		KeyCode,
		NULL,
		NULL,
		&p_Texture);
	if (HR != D3D_OK){
		return NoTexture;
	}
	else{
		m_vTexture.push_back(p_Texture);
		return p_Texture;
	}
}


void Renderer::setCurrentTexture(const Texture& texture){
	d3d_dev->SetTexture(0, texture);
}