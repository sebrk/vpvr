// Decal.h: interface for the Decal class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#if !defined(AFX_DECAL_H__447B3CE2_C9EA_4ED1_AA3D_A8328F6DFD48__INCLUDED_)
#define AFX_DECAL_H__447B3CE2_C9EA_4ED1_AA3D_A8328F6DFD48__INCLUDED_

class DecalData
{
public:
   Vertex2D m_vCenter;
   float m_width, m_height;
   float m_rotation;
   char m_szImage[MAXTOKEN];
   char m_szSurface[MAXTOKEN];
   DecalType m_decaltype;
   char m_sztext[MAXSTRING];
   SizingType m_sizingtype;
   COLORREF m_color;
   char m_szMaterial[32];
   bool m_fVerticalText;
};

class Decal :
   public IDispatchImpl<IDecal, &IID_IDecal, &LIBID_VPinballLib>,
   public CComObjectRoot,
   public ISelect,
   public IEditable,
   public Hitable,
   public IScriptable,
   public IPerPropertyBrowsing // Ability to fill in dropdown in property browser
{
public:
   STDMETHOD(get_HasVerticalText)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_HasVerticalText)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(get_Font)(/*[out, retval]*/ IFontDisp **pVal);
   STDMETHOD(putref_Font)(/*[in]*/ IFontDisp *newVal);
   STDMETHOD(get_FontColor)(/*[out, retval]*/ OLE_COLOR *pVal);
   STDMETHOD(put_FontColor)(/*[in]*/ OLE_COLOR newVal);
   STDMETHOD(get_Material)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_Material)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_SizingType)(/*[out, retval]*/ SizingType *pVal);
   STDMETHOD(put_SizingType)(/*[in]*/ SizingType newVal);
   STDMETHOD(get_Text)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_Text)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_Type)(/*[out, retval]*/ DecalType *pVal);
   STDMETHOD(put_Type)(/*[in]*/ DecalType newVal);
   STDMETHOD(get_Surface)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_Surface)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_Y)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Y)(/*[in]*/ float newVal);
   STDMETHOD(get_X)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_X)(/*[in]*/ float newVal);
   STDMETHOD(get_Height)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Height)(/*[in]*/ float newVal);
   STDMETHOD(get_Width)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Width)(/*[in]*/ float newVal);
   STDMETHOD(get_Image)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_Image)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_Rotation)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Rotation)(/*[in]*/ float newVal);
   Decal();
   virtual ~Decal();

   BEGIN_COM_MAP(Decal)
      COM_INTERFACE_ENTRY(IDispatch)
      COM_INTERFACE_ENTRY(IDecal)
      COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
   END_COM_MAP()

   STANDARD_NOSCRIPT_EDITABLE_DECLARES(Decal, eItemDecal, DECAL, VIEW_PLAYFIELD | VIEW_BACKGLASS)

   virtual void MoveOffset(const float dx, const float dy);
   virtual void SetObjectPos();
   // Multi-object manipulation
   virtual Vertex2D GetCenter() const;
   virtual void PutCenter(const Vertex2D& pv);
   virtual float GetDepth(const Vertex3Ds& viewDir) const;
   virtual bool IsTransparent() const;

   virtual void Rotate(const float ang, const Vertex2D& pvCenter, const bool useElementCenter);

   STDMETHOD(get_Name)(BSTR *pVal) { return E_FAIL; }

   virtual void WriteRegDefaults();
   virtual void GetDialogPanes(vector<PropertyPane*> &pvproppane);

   virtual ItemTypeEnum HitableGetItemType() const { return eItemDecal; }

   DecalData m_d;

private:
   void EnsureSize();
   HFONT GetFont();
   void GetTextSize(int * const px, int * const py);

   void PreRenderText();
   void RenderObject();

   IFont *m_pIFont;

   PinTable *m_ptable;


   BaseTexture *m_textImg;
   float m_leading, m_descent;

   float m_realwidth, m_realheight;
   VertexBuffer *vertexBuffer;
};

#endif // !defined(AFX_DECAL_H__447B3CE2_C9EA_4ED1_AA3D_A8328F6DFD48__INCLUDED_)
