// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MDLL_EXPORTS
#define MDLL_API extern "C"  __declspec(dllexport)
#else
#define MDLL_API extern "C"  __declspec(dllimport)
#endif

extern "C" 
{
  MDLL_API int Encrypt(unsigned char *buf);
  MDLL_API int Decrypt(unsigned char *buf);
}