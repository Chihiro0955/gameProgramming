#ifndef CMODELX_H //�C���N���[�h�K�[�h
#define CMODELX_H

#define MODEL_FILE "sample.blend.x" //���̓t�@�C����

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a){if(a) delete[] a;a=0;}

#define ARRAY_SIZE(a)(sizeof(a)/sizeof(0))



#include <vector>        //vector�N���X�̃C���N���[�h
#include "CMatrix.h"     //�}�g���N�X�N���X�̃C���N���[�h
class CModelX;           //CModelX�N���X�̐錾


#include "CVector.h"

#include "CMaterial.h"

class CMaterial;

//CMesh�N���X�̒�`
class CMesh{
public:
	int mVertexNum;        //���_��
	CVector *mpVertex;     //���_�f�[�^
	int mFaceNum;          //�ʐ�
	int *mpVertexIndex;    //�ʂ��\�����钸�_�ԍ�
	int mNormalNum;        //�@����
	CVector *mpNormal;     //�@���f�[�^
	int mMaterialNum;      //�}�e���A����
	int mMaterialIndexNum; //�}�e���A���ԍ���(�ʐ�)
	int *mpMaterialIndex;  //�}�e���A���ԍ�
	std::vector <CMaterial*> mMaterial; //�}�e���A���f�[�^
	//�R���X�g���N�^
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
	}
	//�ǂݍ��ݏ���
	void Init(CModelX *model);
	void Render();
};

//CModelXFrame�N���X�̒�`
class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild; //�q�t���[���̔z��
	CMatrix mTransformMatrix;    //�ϊ��s��
	char* mpName;         //�t���[�����O
	int mIndex;           //�t���[���ԍ�
	CMesh mMesh;          //Mesh�f�[�^
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame(){
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete *itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
};

/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/

class CModelX{
public: 
	//�����f�[�^�̎擾
	int GetIntToken();
	char* mpPointer;      //�ǂݍ��݈ʒu
	char mToken[1024];    //���o�����P��̗̈�
	std::vector<CModelXFrame*> mFrame; //�t���[���̔z��
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	CModelX()
		: mpPointer(nullptr)
	{}

	~CModelX(){
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
	}

	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	void Render();
};

#endif
